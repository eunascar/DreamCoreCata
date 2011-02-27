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

enum Spells
{
    SPELL_CORRUPTION                    = 70904,
    SPELL_DREAM_SLIP                    = 71196,
    SPELL_RAGE                          = 71189,
    SPELL_COLUMN                        = 70704,
    SPELL_DREAM_STATE                   = 70766,
    SPELL_VIGOR                         = 70873,
    SPELL_NIGHTMARE                     = 71941,
    SPELL_CLOUD_VISUAL                  = 70876,
    SPELL_PORTAL_N_PRE                  = 71301,
    SPELL_PORTAL_N_NPC                  = 71305,
    SPELL_PORTAL_H_PRE                  = 71977,
    SPELL_PORTAL_H_NPC                  = 71987,
    SPELL_MOD_DAMAGE                    = 68066,
    SPELL_COPY_DAMAGE                   = 71948,
    SPELL_SUMMON_SUPPRESSOR_PEREODIC    = 70912,
    SPELL_SUMMON_FIRE_SKELETON_PEREODIC = 70913,
    SPELL_SUMMON_ZOMBIE_PEREODIC        = 70914,
    SPELL_SUMMON_ABOMINATION_PEREODIC   = 70915,
    SPELL_SUMMON_ARCHMAGE_PEREODIC      = 70916,
    SPELL_SUMMON_SUPPRESSOR             = 70935,
    SPELL_CLEAR_AURA                    = 75863,
    SPELL_CANCEL_ALL_AURAS              = 71721,
    SPELL_NIGHTMARE_DAMAGE              = 71946
};

enum Creatures
{
    CREATURE_CLOUD                   = 37985,
    CREATURE_COMBAT_TRIGGER          = 38752,
    CREATURE_PORTAL_NORMAL_MODE_PRE  = 38186,
    CREATURE_PORTAL_HEROIC_MODE_PRE  = 38429,
    CREATURE_NIGHMARE                = 38421
};

struct SpawnPos
{
    float x,y,z;
};

const SpawnPos Pos[] =
{
    {4239.579102f, 2566.753418f, 364.868439f},
    {4240.688477f, 2405.794678f, 364.868591f},
    {4165.112305f, 2405.872559f, 364.872925f},
    {4166.216797f, 2564.197266f, 364.873047f}
};

class boss_valithria : public CreatureScript
{
    public:
        boss_valithria() : CreatureScript("boss_valithria") { }

        struct boss_valithriaAI : public BossAI
        {
            boss_valithriaAI(Creature* creature) : BossAI(creature, DATA_VALITHRIA_DREAMWALKER), summons(me)
            {
                instance = me->GetInstanceScript();
            }

            void Reset()
            {
                uiStage = 1;

                DoCast(me, SPELL_CORRUPTION);
                DoCast(me, SPELL_MOD_DAMAGE);
                me->SetHealth(uint32(me->GetMaxHealth() / 3.5));

                uiEndTimer = 1000;
                uiPortalTimer = 30000;

                bIntro = false;
                bEnd = false;
                bAboveHP = false;
                bBelowHP = false;
                SetCombatMovement(false);

                if (SpellEntry* copy = GET_SPELL(SPELL_COPY_DAMAGE))
                    copy->Targets = 18;

                if (SpellEntry* summon = GET_SPELL(SPELL_SUMMON_SUPPRESSOR_PEREODIC)) //prevent console spam
                    summon->EffectTriggerSpell[0] = SPELL_SUMMON_SUPPRESSOR;

                if (instance)
                    instance->SetData(DATA_VALITHRIA_DREAMWALKER, NOT_STARTED);
            }

            void MoveInLineOfSight(Unit* who)
            {
                if (instance && instance->GetData(DATA_VALITHRIA_DREAMWALKER) == NOT_STARTED)
                {
                    instance->SetData(DATA_VALITHRIA_DREAMWALKER, IN_PROGRESS);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ADD, me);
                }

                if (!bIntro && who->IsWithinDistInMap(me, 40.0f, true))
                {
                    Talk(SAY_AGGRO);
                    DoCast(SPELL_COPY_DAMAGE);
                    DoCast(me, SPELL_SUMMON_SUPPRESSOR_PEREODIC);
                    DoCast(me, SPELL_SUMMON_FIRE_SKELETON_PEREODIC);
                    DoCast(me, SPELL_SUMMON_ZOMBIE_PEREODIC);
                    DoCast(me, SPELL_SUMMON_ABOMINATION_PEREODIC);
                    DoCast(me, SPELL_SUMMON_ARCHMAGE_PEREODIC);
                    if (IsHeroic())
                        DoCast(me, SPELL_NIGHTMARE_DAMAGE);
                    bIntro = true;

                    if (Creature* triger = me->FindNearestCreature(CREATURE_COMBAT_TRIGGER, 25.0f, true))
                        triger->AI()->AttackStart(me);

                    ScriptedAI::MoveInLineOfSight(who);
                }
                if (instance && instance->GetData(DATA_VALITHRIA_DREAMWALKER) == IN_PROGRESS)
                    if (!who->IsWithinDistInMap(me, 60.0f,true))
                        EnterEvadeMode();
            }

            void KilledUnit(Unit* /*victim*/)
            {
                Talk(SAY_PDEATH);
            }

            void JustSummoned(Creature* summoned)
            {
                summons.Summon(summoned);
            }

            void EnterEvadeMode()
            {
                summons.DespawnAll();
                DoCast(me, SPELL_CLEAR_AURA);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_REMOVE, me);

                if (instance)
                    instance->SetData(DATA_VALITHRIA_DREAMWALKER, FAIL);
            }

            void JustDied(Unit* /*pKiller*/)
            {
                Talk(SAY_DEATH);
                DoCast(me, SPELL_CLEAR_AURA);
                summons.DespawnAll();

                if (instance)
                    instance->SetData(DATA_VALITHRIA_DREAMWALKER, FAIL);
            }

            void DamageTaken(Unit* /*done_by*/, uint32& /*damage*/)
            {
                if (!instance || instance->GetData(DATA_VALITHRIA_DREAMWALKER) == DONE)
                    return;

                if (!bAboveHP && HealthAbovePct(74))
                {
                    Talk(SAY_ABOVE_75);
                    bAboveHP = true;
                }
                if (!bBelowHP && HealthBelowPct(26))
                {
                    Talk(SAY_BELOW_25);
                    bBelowHP = true;
                }
                if (!bEnd && HealthAbovePct(99))
                {
                    Talk(SAY_END);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                    me->SetReactState(REACT_PASSIVE);
                    DoCast(me, SPELL_CANCEL_ALL_AURAS);
                    bEnd = true;
                }
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (uiPortalTimer <= diff)
                {
                    if (!IsHeroic())
                        Talk(SAY_OPEN_PORTAL);

                    for(uint8 p = 0; p < RAID_MODE(2,7,2,7); ++p)
                        DoCast(RAID_MODE(SPELL_PORTAL_N_PRE,SPELL_PORTAL_N_PRE,SPELL_PORTAL_H_PRE,SPELL_PORTAL_H_PRE));
                    uiPortalTimer = 50000;
                } else uiPortalTimer -= diff;

                if (!bEnd)
                    return;

                if (uiEndTimer <= diff)
                {
                    switch(uiStage)
                    {
                        case 1:
                            Talk(SAY_BERSERK);
                            DoCast(me, SPELL_RAGE);
                            uiEndTimer = 6000;
                            break;
                        case 2:
                            DoCast(SPELL_DREAM_SLIP);
                            if (instance)
                                instance->SetData(DATA_VALITHRIA_DREAMWALKER, DONE);
                            me->ForcedDespawn();
                            uiEndTimer = 1000;
                            bEnd = false;
                            break;
                    }
                    ++uiStage;
                } else uiEndTimer -= diff;
            }

        private:
            InstanceScript* instance;

            uint8 uiStage;
            uint32 uiEndTimer;
            uint32 uiPortalTimer;
            SummonList summons;
            bool bIntro;
            bool bEnd;
            bool bAboveHP;
            bool bBelowHP;
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

                uiSummonPortalTimer = 5000;
            }

            void UpdateAI(const uint32 diff)
            {
                if (instance && instance->GetData(DATA_VALITHRIA_DREAMWALKER) != IN_PROGRESS)
                    return;

                if (uiSummonPortalTimer <= diff)
                {
                    float x, y, z;
                    me->GetPosition(x,y,z);
                    for(uint8 i = 0; i <= 8; ++i) //need correct count
                        me->SummonCreature(CREATURE_CLOUD, x + (urand(2, 6) * 10), y + (urand(1, 4) * 10), z + urand(2,8), 0, TEMPSUMMON_TIMED_DESPAWN, 15000);
                    uiSummonPortalTimer = 5000;
                } else uiSummonPortalTimer -= diff;
            }
        private:
            InstanceScript* instance;

            uint32 uiSummonPortalTimer;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_valithria_alternativeAI(creature);
        }
};

class npc_dreamportal_icc : public CreatureScript //портал в комнате
{
    public:
        npc_dreamportal_icc() : CreatureScript("npc_dreamportal_icc") { }

        struct npc_dreamportal_iccAI : public ScriptedAI
        {
            npc_dreamportal_iccAI(Creature* creature) : ScriptedAI(creature) { }

            void Reset()
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
                uiChangeTimer = 15000;
            }

            void UpdateAI(const uint32 diff)
            {
                if (me->GetEntry() == CREATURE_PORTAL_NORMAL_MODE_PRE)
                {
                    if (uiChangeTimer <= diff)
                    {
                        DoCast(me, SPELL_PORTAL_N_NPC);
                        me->ForcedDespawn();
                        //me->UpdateEntry(CREATURE_PORTAL_NORMAL_MODE_NPC);
                    } else uiChangeTimer -= diff;
                }

                if (me->GetEntry() == CREATURE_PORTAL_HEROIC_MODE_PRE)
                {
                    if (uiChangeTimer <= diff)
                    {
                        DoCast(me, SPELL_PORTAL_H_NPC);
                        me->ForcedDespawn();
                        //me->UpdateEntry(CREATURE_PORTAL_HEROIC_MODE_NPC);
                    } else uiChangeTimer -= diff;
                }
            }

        private:
            uint32 uiChangeTimer;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_dreamportal_iccAI(creature);
        }
};

class npc_dreamcloud_icc : public CreatureScript //облако в комнате
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
                        case CREATURE_NIGHMARE:
                            DoCast(SPELL_NIGHTMARE);
                            break;
                        case CREATURE_CLOUD:
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

class spell_valithria_adds_summon : public SpellScriptLoader
{
    public:
        spell_valithria_adds_summon() : SpellScriptLoader("spell_valithria_adds_summon") { }


        class spell_valithria_adds_summon_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_valithria_adds_summon_AuraScript);

            void OnPereodic(AuraEffect const* aurEff)
            {
                PreventDefaultAction();
                if (Unit* caster = GetTargetApplication()->GetBase()->GetCaster())
                {
                    int triggerSpellId = GetSpellProto()->EffectTriggerSpell[aurEff->GetEffIndex()];
                    for(uint8 i = 0; i < caster->GetMap()->GetSpawnMode(); ++i)
                        if (urand(0,1))
                            if (triggerSpellId)
                                caster->CastSpell(Pos[i].x, Pos[i].y, Pos[i].z, triggerSpellId, true, NULL, NULL, GetCasterGUID(), caster);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_valithria_adds_summon_AuraScript::OnPereodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_valithria_adds_summon_AuraScript();
        }
};

class spell_cancel_all_aura : public SpellScriptLoader
{
    public:
        spell_cancel_all_aura() : SpellScriptLoader("spell_cancel_all_aura") { }


        class spell_cancel_all_aura_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_cancel_all_aura_SpellScript);

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                if (!(GetHitUnit() && GetHitUnit()->isAlive()))
                    return;

                if (Unit* caster = GetCaster())
                    caster->RemoveAllAuras();
            }

            void Register()
            {
                OnEffect += SpellEffectFn(spell_cancel_all_aura_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_cancel_all_aura_SpellScript();
        }
};

void AddSC_boss_valithria_dreamwalker()
{
    new boss_valithria();
    new npc_dreamportal_icc();
    new npc_dreamcloud_icc();
    new npc_valithria_alternative();
    new spell_valithria_adds_summon();
    new spell_cancel_all_aura();
}