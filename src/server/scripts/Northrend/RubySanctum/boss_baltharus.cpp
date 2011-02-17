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
    SAY_AGGRO           = 0,
    SAY_SLAY1           = 1,
    SAY_SLAY2           = 2,
    SAY_DEATH           = 3,
    SAY_SUMMON_CLONE    = 4,
    SAY_INTRO           = 5,

    SAY_XERESTRASZA_1  = 0,
    SAY_XERESTRASZA_2  = 1,
    SAY_XERESTRASZA_3  = 2,
    SAY_XERESTRASZA_4  = 3,
    SAY_XERESTRASZA_5  = 4,
    SAY_XERESTRASZA_6  = 5,
    SAY_XERESTRASZA_7  = 6,
    SAY_XERESTRASZA_8  = 7,
    SAY_XERESTRASZA_9  = 8
};

enum Spells
{
    SPELL_CLEAVE            = 40504,
    SPELL_REPELLING_WAVE    = 74509,
    SPELL_ENERVATING_BRAND  = 74502,
    SPELL_BLADE_TEMPEST     = 75125,
    SPELL_SUMMON_CLONE      = 74511
};

enum Events
{
    EVENT_CAST_CLEAVE           = 1,
    EVENT_CAST_REPELLING_WAVE   = 2,
    EVENT_CAST_ENERVATING_BRAND = 3,
    EVENT_CAST_BLADE_TEMPEST    = 4,
    EVENT_CAST_SUMMON_CLONE     = 5,
    
    ACTION_START_EVENT          = 6,
    EVENT_XERESTRASZA_3         = 7,
    EVENT_XERESTRASZA_4         = 8,
    EVENT_XERESTRASZA_5         = 9,
    EVENT_XERESTRASZA_6         = 10,
    EVENT_XERESTRASZA_7         = 11,
    EVENT_XERESTRASZA_8         = 12,
    EVENT_XERESTRASZA_9         = 13,

    EVENT_START_PHASE_TWO       = 14
};

enum Phases
{
    PHASE_ALL = 0,
    PHASE_1   = 1,
    PHASE_2   = 2,

    PHASE_1_MASK  = 1 << PHASE_1,
    PHASE_2_MASK  = 1 << PHASE_2
};

Creature* pXerestrasza;

class boss_baltharus : public CreatureScript
{
    public:
        boss_baltharus() : CreatureScript("boss_baltharus") { }

        struct boss_baltharusAI : public BossAI
        {
            boss_baltharusAI(Creature* creature) : BossAI(creature, DATA_BALTHARUS)
            {
                ASSERT(instance);
            }

            void Reset()
            {
                instance->SetBossState(DATA_BALTHARUS, NOT_STARTED);
                events.Reset();
                events.SetPhase(PHASE_1);
                events.ScheduleEvent(EVENT_CAST_CLEAVE, urand(2000,3000));
                events.ScheduleEvent(EVENT_CAST_ENERVATING_BRAND, urand(30000,45000));
                events.ScheduleEvent(EVENT_CAST_BLADE_TEMPEST, urand(7000,7500));
            }

            void EnterCombat(Unit*)
            {
                instance->SetBossState(DATA_BALTHARUS, IN_PROGRESS);
                Talk(SAY_AGGRO);
            }

            void JustSummoned(Creature *summon)
            {
                summons.Summon(summon);
            }

            void KilledUnit(Unit* /*victim*/)
            {
                Talk(RAND(SAY_SLAY1,SAY_SLAY2));
            }

            void JustReachedHome()
            {
                summons.DespawnAll();
                instance->SetData(DATA_BALTHARUS, FAIL);
            }

            void JustDied(Unit*)
            {
                Talk(SAY_DEATH);
                instance->SetData(DATA_BALTHARUS, DONE);
                if (GameObject* flame = GetClosestGameObjectWithEntry(me, GO_FIRE_FIELD, 200.0f))
                    flame->RemoveFromWorld();

                if (instance->GetBossState(DATA_RAGEFIRE) == DONE)
                {
                   if (GameObject* flame = GetClosestGameObjectWithEntry(me, GO_FLAME_WALLS, 200.0f))
                       flame->RemoveFromWorld();
                }
                pXerestrasza->AI()->DoAction(ACTION_START_EVENT);
                _JustDied();
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
                        case EVENT_CAST_CLEAVE:
                            DoCastVictim(SPELL_CLEAVE);
                            events.ScheduleEvent(EVENT_CAST_CLEAVE, urand(2000,3000));
                            break;
                        case EVENT_START_PHASE_TWO:
                            Talk(SAY_SUMMON_CLONE);
                            DoCast(SPELL_SUMMON_CLONE);
                            DoCastAOE(SPELL_REPELLING_WAVE,true);
                            break;
                        case EVENT_CAST_ENERVATING_BRAND:
                            DoCastVictim(SPELL_ENERVATING_BRAND, true);
                            events.ScheduleEvent(EVENT_CAST_ENERVATING_BRAND, urand(30000,45000));
                            break;
                        case EVENT_CAST_BLADE_TEMPEST:
                            DoCastAOE(SPELL_BLADE_TEMPEST);
                            events.ScheduleEvent(EVENT_CAST_BLADE_TEMPEST, urand(30000,35000));
                            break;
                    }
                }

                if (!(events.GetPhaseMask() & PHASE_2_MASK))
                {
                    if (me->GetHealth() <= ((me->GetMaxHealth() / 100) * 50))
                    {
                        events.SetPhase(PHASE_2);
                        events.ScheduleEvent(EVENT_START_PHASE_TWO, 1000,0,PHASE_2);
                    }
                }

                DoMeleeAttackIfReady();
            }

        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_baltharusAI(creature);
        }

};

class boss_baltharus_summon : public CreatureScript
{
    public:
        boss_baltharus_summon() : CreatureScript("boss_baltharus_summon") { }

        struct boss_baltharus_summonAI : public ScriptedAI
        {
            boss_baltharus_summonAI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = me->GetInstanceScript();
            }

            void Reset()
            {
                events.Reset();
                events.ScheduleEvent(EVENT_CAST_CLEAVE, urand(2000,3000));
                events.ScheduleEvent(EVENT_CAST_ENERVATING_BRAND, urand(30000,45000));
                events.ScheduleEvent(EVENT_CAST_BLADE_TEMPEST, urand(20000,25000));
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CAST_CLEAVE:
                            DoCastVictim(SPELL_CLEAVE);
                            events.ScheduleEvent(EVENT_CAST_CLEAVE, urand(2000,3000));
                            break;
                        case EVENT_CAST_ENERVATING_BRAND:
                            DoCastVictim(SPELL_ENERVATING_BRAND);
                            events.ScheduleEvent(EVENT_CAST_ENERVATING_BRAND, urand(30000,45000));
                            break;
                        case EVENT_CAST_BLADE_TEMPEST:
                            DoCast(SPELL_BLADE_TEMPEST);
                            events.ScheduleEvent(EVENT_CAST_BLADE_TEMPEST, urand(30000,45000));
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
            return new boss_baltharus_summonAI(creature);
        }

};

class npc_xerestrasza : public CreatureScript
{
    public:
        npc_xerestrasza() : CreatureScript("npc_xerestrasza") { }

        struct npc_xerestraszaAI : public ScriptedAI
        {
            npc_xerestraszaAI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = me->GetInstanceScript();
                pXerestrasza = me;
            }

            void Reset()
            {
                events.Reset();
                bIntro = false;
                pInstance->SetData(DATA_XERESTRASZA,NOT_STARTED);
            }

            void MoveInLineOfSight(Unit*)
            {
                if (!bIntro)
                {
                    Talk(SAY_XERESTRASZA_1);
                    pInstance->SetData(DATA_XERESTRASZA,NOT_STARTED);
                    bIntro = true;
                }
            }

            void DoAction(const int32 action)
            {
                if (action == ACTION_START_EVENT)
                {
                    me->GetMotionMaster()->MovePoint(1, 3153.5490f, 385.53f, 86.33f);
                    pInstance->SetData(DATA_XERESTRASZA,IN_PROGRESS);
                    Talk(SAY_XERESTRASZA_2);
                    events.ScheduleEvent(EVENT_XERESTRASZA_3,9000); 
                    events.ScheduleEvent(EVENT_XERESTRASZA_4,20000); 
                    events.ScheduleEvent(EVENT_XERESTRASZA_5,31000); 
                    events.ScheduleEvent(EVENT_XERESTRASZA_6,42000); 
                    events.ScheduleEvent(EVENT_XERESTRASZA_7,53000); 
                    events.ScheduleEvent(EVENT_XERESTRASZA_8,64000); 
                    events.ScheduleEvent(EVENT_XERESTRASZA_9,75000); 
                }
            }

            void UpdateAI(const uint32 diff)
            {
                events.Update(diff);
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_XERESTRASZA_3:
                            Talk(SAY_XERESTRASZA_3);
                            break;
                        case EVENT_XERESTRASZA_4:
                            Talk(SAY_XERESTRASZA_4);
                            break;
                        case EVENT_XERESTRASZA_5:
                            Talk(SAY_XERESTRASZA_5);
                            break;
                        case EVENT_XERESTRASZA_6:
                            Talk(SAY_XERESTRASZA_6);
                            break;
                        case EVENT_XERESTRASZA_7:
                            Talk(SAY_XERESTRASZA_7);
                            break;
                        case EVENT_XERESTRASZA_8:
                            Talk(SAY_XERESTRASZA_8);
                            break;
                        case EVENT_XERESTRASZA_9:
                            Talk(SAY_XERESTRASZA_9);
                            pInstance->SetData(DATA_XERESTRASZA,DONE);
                            break;
                    }
                }
            }
        private:
            bool bIntro;
            EventMap events;
            InstanceScript* pInstance;
        };
        
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_xerestraszaAI(creature);
        }
};


void AddSC_boss_baltharus()
{
    new boss_baltharus();
    new boss_baltharus_summon();
    new npc_xerestrasza();
}
