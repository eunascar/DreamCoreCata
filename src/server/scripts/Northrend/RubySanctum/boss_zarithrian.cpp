/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2010-2011 Chronos Server <http://chronoserverwow.net/>
 * Copyright (C) 2010 Easy for Trinity <http://trinity-core.ru/>
 * Copyright (C) 2010 Myth Project <http://bitbucket.org/sun/myth-core/>
 * Copyright (C) 2006-2011 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptPCH.h"
#include "ruby_sanctum.h"

enum Texts
{
    SAY_AGGRO     = 0,
    SAY_SLAY1     = 1,
    SAY_SLAY2     = 2,
    SAY_DEATH     = 3,
    SAY_SUMMON    = 4
};

enum Spells
{
    SPELL_CLEAVE_ARMOR          = 74367,
    SPELL_INTIMIDATING_ROAR     = 74384,
    SPELL_SUMMON_FLAMECALLER    = 74398,

    SPELL_BLAST_NOVA_10         = 74392,
    SPELL_BLAST_NOVA_25         = 74393,
    SPELL_LAVA_GOUT_10          = 74394,
    SPELL_LAVA_GOUT_25          = 74395
};

enum Events
{
    EVENT_CAST_CLEAVE_ARMOR         = 1,
    EVENT_CAST_INTIMIDATING_ROAR    = 2,
    EVENT_CAST_SUMMON_FLAMECALLER   = 3,

    EVENT_CAST_BLAST_NOVA           = 4,
    EVENT_CAST_LAVA_GOUT            = 5,
    EVENT_MOVE_TO_RANDOM_PLAYER     = 6
};

static const Position SpawnPos[4] =
{
    {3022.67f, 479.01f, 89.23f, 2.38f},
    {3016.55f, 510.26f, 90.03f, 0.89f},
    {3039.37f, 590.13f, 87.90f, 3.74f},
    {3018.86f, 549.40f, 89.25f, 5.23f}
};

Creature* pZarithrian;

class boss_zarithrian : public CreatureScript
{
    public:
        boss_zarithrian() : CreatureScript("boss_zarithrian") { }

        struct boss_zarithrianAI : public BossAI
        {
            boss_zarithrianAI(Creature* creature) : BossAI(creature, DATA_ZARITHRIAN)
            {
                ASSERT(instance);
                pZarithrian = me;
            }

            void Reset()
            {
                instance->SetBossState(DATA_ZARITHRIAN, NOT_STARTED);
                events.Reset();
                summons.DespawnAll();
                summons.clear();
                events.ScheduleEvent(EVENT_CAST_CLEAVE_ARMOR, urand(3500,4500));
                events.ScheduleEvent(EVENT_CAST_INTIMIDATING_ROAR, urand(10000,11000));
                events.ScheduleEvent(EVENT_CAST_SUMMON_FLAMECALLER, urand(40000,50000));
            }

            void EnterCombat(Unit*)
            {
                instance->SetBossState(DATA_ZARITHRIAN, IN_PROGRESS);
                DoScriptText(SAY_AGGRO, me);
            }

            void KilledUnit(Unit* /*victim*/)
            {
                DoScriptText(RAND(SAY_SLAY1,SAY_SLAY2), me);
            }

            void JustSummoned(Creature *summon)
            {
                summons.Summon(summon);
            }

            void JustReachedHome()
            {
                summons.DespawnAll();
                instance->SetData(DATA_ZARITHRIAN, FAIL);
            }

            void JustDied(Unit*)
            {
                _JustDied();
                instance->SetBossState(DATA_ZARITHRIAN, DONE);
                DoScriptText(SAY_DEATH, me);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim() || !CheckInRoom())
                    return;

                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CAST_CLEAVE_ARMOR:
                            DoCastVictim(SPELL_CLEAVE_ARMOR);
                            events.ScheduleEvent(EVENT_CAST_CLEAVE_ARMOR, urand(3500,4500));
                            break;
                        case EVENT_CAST_INTIMIDATING_ROAR:
                            DoCastAOE(SPELL_INTIMIDATING_ROAR);
                            events.ScheduleEvent(EVENT_CAST_INTIMIDATING_ROAR, urand(10000,11000));
                            break;
                        case EVENT_CAST_SUMMON_FLAMECALLER:
                            if (Creature* creature1 = me->SummonCreature(NPC_ONYX_FLAMECALLER,SpawnPos[0]))
                                creature1->GetMotionMaster()->MovePoint(1,SpawnPos[1]);

                            if (Creature* creature2 = me->SummonCreature(NPC_ONYX_FLAMECALLER,SpawnPos[2]))
                                creature2->GetMotionMaster()->MovePoint(1,SpawnPos[3]);

                            events.ScheduleEvent(EVENT_CAST_SUMMON_FLAMECALLER, urand(40000,50000));
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_zarithrianAI(creature);
        }
};

class npc_onyx_flamecaller : public CreatureScript
{
    public:
        npc_onyx_flamecaller() : CreatureScript("npc_onyx_flamecaller") { }

        struct npc_onyx_flamecallerAI : public ScriptedAI
        {
            npc_onyx_flamecallerAI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = me->GetInstanceScript();
            }

            void Reset()
            {
                events.Reset();
                events.ScheduleEvent(EVENT_MOVE_TO_RANDOM_PLAYER, 3000);
                events.ScheduleEvent(EVENT_CAST_BLAST_NOVA, urand(15000,25000));
                events.ScheduleEvent(EVENT_CAST_LAVA_GOUT, urand(30000,35000));
            }

             void UpdateAI(const uint32 diff)
            {
                events.Update(diff);
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_MOVE_TO_RANDOM_PLAYER:
                            if (pZarithrian)
                                me->GetMotionMaster()->MovePoint(2,pZarithrian->GetPositionX(),pZarithrian->GetPositionY(),pZarithrian->GetPositionZ());
                            break;
                        case EVENT_CAST_BLAST_NOVA:
                            DoCast(RAID_MODE(SPELL_BLAST_NOVA_10,SPELL_BLAST_NOVA_25,SPELL_BLAST_NOVA_10,SPELL_BLAST_NOVA_25));
                            events.ScheduleEvent(EVENT_CAST_BLAST_NOVA, urand(15000,25000));
                            break;
                        case EVENT_CAST_LAVA_GOUT:
                            DoCast(RAID_MODE(SPELL_LAVA_GOUT_10,SPELL_LAVA_GOUT_25,SPELL_LAVA_GOUT_10,SPELL_LAVA_GOUT_25));
                            events.ScheduleEvent(EVENT_CAST_LAVA_GOUT, urand(30000,35000));
                            break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        private:
            EventMap events;
            InstanceScript* pInstance;
        };
        
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_onyx_flamecallerAI(creature);
        }
};

void AddSC_boss_zarithrian()
{
    new boss_zarithrian();
    new npc_onyx_flamecaller();
}
