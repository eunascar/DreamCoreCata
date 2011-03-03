/*
 * Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
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

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "icecrown_citadel.h"

enum Creatures
{
    NPC_CLOUD                     = 37985,
    NPC_PORTAL_NORMAL_MODE_PRE    = 38186,
    NPC_PORTAL_HEROIC_MODE_PRE    = 38429,
    NPC_NIGHMARE                  = 38421,
    NPC_ABOMINATION               = 37886,
    NPC_SKELETON                  = 36791,
    NPC_ARCHMAGE                  = 37868,
    NPC_SUPPRESSER                = 37863,
    NPC_ZOMBIE                    = 37934
};

enum Spells
{
    SPELL_CORRUPTION          = 70904,
    SPELL_DREAM_SLIP          = 71196,
    SPELL_RAGE                = 71189,
    SPELL_COLUMN              = 70704,
    SPELL_DREAM_STATE         = 70766,
    SPELL_VIGOR               = 70873,
    SPELL_NIGHTMARE           = 71941,
    SPELL_CLOUD_VISUAL        = 70876,
    SPELL_PORTAL_N_PRE        = 71301,
    SPELL_PORTAL_N_NPC        = 71305,
    SPELL_PORTAL_H_PRE        = 71977,
    SPELL_PORTAL_H_NPC        = 71987,
    SPELL_MOD_DAMAGE          = 68066,
    SPELL_COPY_DAMAGE         = 71948,
    SPELL_NIGHTMARE_DAMAGE    = 71946
};

enum Yells
{
    SAY_AGGRO       = 0,
    SAY_BELOW_25    = 1,
    SAY_ABOVE_75    = 2,
    SAY_DEATH       = 3,
    SAY_PDEATH      = 4,
    SAY_END         = 5,
    SAY_BERSERK     = 6,
    SAY_OPEN_PORTAL = 7
};

const Position Pos[] =
{
    {4239.579102f, 2566.753418f, 364.868439f, 0.0f},
    {4240.688477f, 2405.794678f, 364.868591f, 0.0f},
    {4165.112305f, 2405.872559f, 364.872925f, 0.0f},
    {4166.216797f, 2564.197266f, 364.873047f, 0.0f}
};

Creature* valithria;

class boss_valithria : public CreatureScript
{
    public:
        boss_valithria() : CreatureScript("boss_valithria") { }

        struct boss_valithriaAI : public BossAI
        {
            boss_valithriaAI(Creature* creature) : BossAI(creature, DATA_VALITHRIA_DREAMWALKER)
            {
                instance = me->GetInstanceScript();
                valithria = me;
            }

            void Reset()
            {
                stage = 1;

                DoCast(me, SPELL_CORRUPTION);
                DoCast(me, SPELL_MOD_DAMAGE);
                me->SetHealth(uint32(me->GetMaxHealth() / 1.1));
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                me->SetReactState(REACT_PASSIVE);

                endTimer = 1000;

                intro = false;
                end = false;
                aboveHP = false;
                belowHP = false;

                if (SpellEntry* copy = GET_SPELL(SPELL_COPY_DAMAGE))
                    copy->Targets = 18;

                instance->SetBossState(DATA_VALITHRIA_DREAMWALKER, NOT_STARTED);
            }

            void MoveInLineOfSight(Unit* who)
            {
                if (instance->GetBossState(DATA_VALITHRIA_DREAMWALKER) == NOT_STARTED)
                    instance->SetBossState(DATA_VALITHRIA_DREAMWALKER, IN_PROGRESS);

                instance->SendEncounterUnit(ENCOUNTER_FRAME_ADD, me);

                if (!intro && instance->GetBossState(DATA_VALITHRIA_DREAMWALKER) == IN_PROGRESS)
                {
                    Talk(SAY_AGGRO);
                    DoCast(SPELL_COPY_DAMAGE);

                    if (IsHeroic())
                        DoCast(me, SPELL_NIGHTMARE_DAMAGE);

                    intro = true;

                    ScriptedAI::MoveInLineOfSight(who);
                }
            }

            //void KilledUnit(Unit* /*victim*/)
            /*{
                Talk(SAY_PDEATH);
            }*/

            void EnterCombat(Unit* /*who*/) { }

            void JustDied(Unit* /*pKiller*/)
            {
                Talk(SAY_DEATH);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_REMOVE, me);
                instance->SetBossState(DATA_VALITHRIA_DREAMWALKER, FAIL);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (instance->GetBossState(DATA_VALITHRIA_DREAMWALKER) == IN_PROGRESS)
                {
                    //DoStartNoMovement(me->getVictim());

                    if (!aboveHP && HealthAbovePct(74))
                    {
                        Talk(SAY_ABOVE_75);
                        aboveHP = true;
                    }

                    if (!belowHP && HealthBelowPct(26))
                    {
                        Talk(SAY_BELOW_25);
                        belowHP = true;
                    }

                    if (!end && HealthAbovePct(99))
                    {
                        Talk(SAY_END);

                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                        end = true;
                    }

                    if (end)
                    {
                        if (endTimer <= diff)
                        {
                            switch(stage)
                            {
                                case 1:
                                    Talk(SAY_BERSERK);
                                    DoCast(me, SPELL_RAGE);
                                    endTimer = 6000;
                                    break;
                                case 2:
                                    DoCast(SPELL_DREAM_SLIP);
                                    instance->SetBossState(DATA_VALITHRIA_DREAMWALKER, DONE);
                                    me->ForcedDespawn();
                                    endTimer = 1000;
                                    end = false;
                                    break;
                            }

                            ++stage;
                        } else endTimer -= diff;
                    }

                    /*if (portalTimer <= diff)
                    {
                        if (!IsHeroic())
                            Talk(SAY_OPEN_PORTAL);

                        for(uint8 p = 0; p < RAID_MODE(2,7,2,7); ++p)
                            DoCast(RAID_MODE(SPELL_PORTAL_N_PRE,SPELL_PORTAL_N_PRE,SPELL_PORTAL_H_PRE,SPELL_PORTAL_H_PRE));
                        portalTimer = 50000;
                    } else portalTimer -= diff;*/
                }
            }

        private:
            InstanceScript* instance;

            uint8 stage;
            uint32 endTimer;
            uint32 portalTimer;
            bool intro;
            bool end;
            bool aboveHP;
            bool belowHP;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_valithriaAI(creature);
        }
};

class npc_valithria_alternative : public CreatureScript
{
    public:
        npc_valithria_alternative() : CreatureScript("npc_valithria_alternative") { }

        struct npc_valithria_alternativeAI : public ScriptedAI
        {
            npc_valithria_alternativeAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            void Reset()
            {
                me->SetPhaseMask(16, true);
                me->SetFlying(true);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                summonPortalTimer = 5000;
            }

            void UpdateAI(const uint32 diff)
            {
                if (instance->GetBossState(DATA_VALITHRIA_DREAMWALKER) != IN_PROGRESS)
                    return;

                if (summonPortalTimer <= diff)
                {
                    float x, y, z;
                    me->GetPosition(x,y,z);
                    for(uint8 i = 0; i <= 8; ++i)
                        me->SummonCreature(NPC_CLOUD, x + (urand(2, 6) * 10), y + (urand(1, 4) * 10), z + urand(2,8), 0, TEMPSUMMON_TIMED_DESPAWN, 15000);
                    summonPortalTimer = 5000;
                } else summonPortalTimer -= diff;
            }
        private:
            InstanceScript* instance;

            uint32 summonPortalTimer;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_valithria_alternativeAI(creature);
        }
};

class npc_dreamportal_icc : public CreatureScript
{
    public:
        npc_dreamportal_icc() : CreatureScript("npc_dreamportal_icc") { }

        struct npc_dreamportal_iccAI : public ScriptedAI
        {
            npc_dreamportal_iccAI(Creature* creature) : ScriptedAI(creature) { }

            void Reset()
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
                changeTimer = 15000;
            }

            void UpdateAI(const uint32 diff)
            {
                if (me->GetEntry() == NPC_PORTAL_NORMAL_MODE_PRE)
                {
                    if (changeTimer <= diff)
                    {
                        DoCast(me, SPELL_PORTAL_N_NPC);
                        me->ForcedDespawn();
                    } else changeTimer -= diff;
                }

                if (me->GetEntry() == NPC_PORTAL_HEROIC_MODE_PRE)
                {
                    if (changeTimer <= diff)
                    {
                        DoCast(me, SPELL_PORTAL_H_NPC);
                        me->ForcedDespawn();
                    } else changeTimer -= diff;
                }
            }

        private:
            uint32 changeTimer;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_dreamportal_iccAI(creature);
        }
};

class npc_dreamcloud_icc : public CreatureScript
{
    public:
        npc_dreamcloud_icc() : CreatureScript("npc_dreamcloud_icc") { }

        struct npc_dreamcloud_iccAI : public ScriptedAI
        {
            npc_dreamcloud_iccAI(Creature* creature) : ScriptedAI(creature) { }

            void Reset()
            {
                me->SetPhaseMask(16, true);
                me->SetFlying(true);
            }

            void MoveInLineOfSight(Unit *who)
            {
                if (me->IsWithinDistInMap(who, 5.0f, true))
                {
                    switch(me->GetEntry())
                    {
                        case NPC_NIGHMARE:
                            DoCast(SPELL_NIGHTMARE);
                            break;
                        case NPC_CLOUD:
                            DoCast(SPELL_VIGOR);
                            break;
                    }
                }

                ScriptedAI::MoveInLineOfSight(who);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_dreamcloud_iccAI(creature);
        }
};

class npc_icc_combat_stalker : public CreatureScript
{
    public:
        npc_icc_combat_stalker() : CreatureScript("npc_icc_combat_stalker") { }

        struct npc_icc_combat_stalkerAI : public ScriptedAI
        {
            npc_icc_combat_stalkerAI(Creature* creature) : ScriptedAI(creature), summons(me)
            {
                instance = me->GetInstanceScript();
            }

            void Reset()
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetInCombatWithZone();
                DoStartNoMovement(me->getVictim());
                combat = false;
                summonTimer = 10000;
                summons.DespawnAll();
            }

            void JustSummoned(Creature* summon)
            {
                summon->AI()->AttackStart(valithria);
                summons.Summon(summon);
            }

            void EnterCombat(Unit* /*who*/) { }

            void UpdateAI(const uint32 diff)
            {
                /*if (!UpdateVictim())
                    return;*/

                if (instance->GetBossState(DATA_VALITHRIA_DREAMWALKER) == DONE || instance->GetBossState(DATA_VALITHRIA_DREAMWALKER) == FAIL)
                {
                    summons.DespawnAll();
                    me->ForcedDespawn();
                }

                if (summonTimer <= diff)
                {
                    for (uint8 coords = 0; coords <= RAID_MODE(1,3,1,3); ++coords)
                    {
                        me->SummonCreature(NPC_ZOMBIE, Pos[coords].GetPositionX(), Pos[coords].GetPositionY(), Pos[coords].GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                        me->SummonCreature(NPC_SKELETON, Pos[coords].GetPositionX(), Pos[coords].GetPositionY(), Pos[coords].GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                        me->SummonCreature(NPC_ARCHMAGE, Pos[coords].GetPositionX(), Pos[coords].GetPositionY(), Pos[coords].GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                        me->SummonCreature(NPC_SUPPRESSER, Pos[coords].GetPositionX(), Pos[coords].GetPositionY(), Pos[coords].GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                        me->SummonCreature(NPC_ABOMINATION, Pos[coords].GetPositionX(), Pos[coords].GetPositionY(), Pos[coords].GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                    }

                    summonTimer = /*1*/20000;
                } else summonTimer -= diff;
            }
            private:
                InstanceScript* instance;
                uint32 summonTimer;
                bool combat;
                SummonList summons;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_icc_combat_stalkerAI(creature);
        }
};

void AddSC_boss_valithria_dreamwalker()
{
    new boss_valithria();
    new npc_dreamportal_icc();
    new npc_dreamcloud_icc();
    new npc_valithria_alternative();
    new npc_icc_combat_stalker();
}