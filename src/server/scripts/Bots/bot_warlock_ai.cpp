/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
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
#include "bot_ai.h"
#include "Group.h"

#define PET_ENTRY    100392

#define SPELL_CHAOS_BOLT               SPELL_CHAOS_BOLT_A[SPELL_LEVEL]
#define SPELL_CONFLAGRATE              SPELL_CONFLAGRATE_A[SPELL_LEVEL]
#define SPELL_CORRUPTION               SPELL_CORRUPTION_A[SPELL_LEVEL]
#define SPELL_CURSE_OF_THE_ELEMENTS    SPELL_CURSE_OF_THE_ELEMENTS_A[SPELL_LEVEL]
#define SPELL_HAUNT                    SPELL_HAUNT_A[SPELL_LEVEL]
#define SPELL_IMMOLATE                 SPELL_IMMOLATE_A[SPELL_LEVEL]
#define SPELL_RAIN_OF_FIRE             SPELL_RAIN_OF_FIRE_A[SPELL_LEVEL]
#define SPELL_SHADOW_BOLT              SPELL_SHADOW_BOLT_A[SPELL_LEVEL]
#define SPELL_UNSTABLE_AFFLICTION      SPELL_UNSTABLE_AFFLICTION_A[SPELL_LEVEL]

uint32 SPELL_CHAOS_BOLT_A            [] = { 0, 0, 0, 0, 0, 50796, 50796, 50796, 50796 };
uint32 SPELL_CONFLAGRATE_A           [] = { 0, 0, 0, 0, 17962, 17962, 17962, 17962, 17962 };
uint32 SPELL_CORRUPTION_A            [] = { 172, 6222, 7648, 11671, 11672, 25311, 47812, 47835, 47836 };
uint32 SPELL_CURSE_OF_THE_ELEMENTS_A [] = { 0, 0, 0, 1490, 11721, 11721, 11722, 27728, 47865 };
uint32 SPELL_HAUNT_A                 [] = { 0, 0, 0, 0, 0, 0, 59164, 59164, 59164 };
uint32 SPELL_IMMOLATE_A              [] = { 348, 707, 1094, 2941, 11665, 11667, 25309, 47810, 47811 };
uint32 SPELL_RAIN_OF_FIRE_A          [] = { 0, 0, 5740, 6219, 11677, 11678, 11678, 27212, 27212 };
uint32 SPELL_SHADOW_BOLT_A           [] = { 686, 705, 1088, 7641, 11659, 11660, 25307, 47808, 59575 };
uint32 SPELL_UNSTABLE_AFFLICTION_A   [] = { 0, 0, 0, 0, 0, 30404, 30405, 47843,  47843 };

class warlock_bot : public CreatureScript
{
    public:
        warlock_bot()
            : CreatureScript("warlock_bot")
        {
        }

        struct warlock_botAI : public bot_ai
        {
            warlock_botAI(Creature* c) :bot_ai(c)
            {
                Reset();
                pet = NULL;
            }

            bool oom_spam;

            uint8 state;
            uint8 next_state;
            uint32 next_state_timer;
            uint32 uiConflagrate_Timer;
            uint32 uiChaosBolt_Timer;

            Creature* pet;
            Unit* opponent;

            void Reset()
            {
                uiFirstAid_Timer       = 0;
                uiGc_Timer             = 0;
                uiConflagrate_Timer    = 0;
                uiChaosBolt_Timer      = 0;
                uiPotion_Timer         = 0;  

                oom_spam = false;

                uint8 state = 1;
                next_state = 0;
                next_state_timer = 0;

                opponent = NULL;
            }

            void AttackStart(Unit* who)
            {
                EnterCombat(who);
                ScriptedAI::AttackStartCaster(who, 25);
            }

            void CreatePet()
            {
                pet = master->GetBotsPet(PET_ENTRY);

                if (pet == NULL)
                    return;

                pet->UpdateCharmAI();
                pet->setFaction(me->getFaction());
                pet->SetReactState(REACT_DEFENSIVE);
                pet->GetMotionMaster()->MoveFollow(me, PET_FOLLOW_DIST * urand(1, 2), PET_FOLLOW_ANGLE);
                CharmInfo* charmInfonewbot = pet->InitCharmInfo();
                pet->GetCharmInfo()->SetCommandState(COMMAND_FOLLOW);
                pet->UpdateStats(STAT_STRENGTH);
                pet->UpdateStats(STAT_AGILITY);
                pet->SetLevel(master->getLevel());

                float val2 = master->getLevel() * 4.0f + pet->GetStat(STAT_STRENGTH) * 2.0f;

                val2 = 100.0;
                uint32 attPowerMultiplier = 1;
                pet->SetModifierValue(UNIT_MOD_ATTACK_POWER, BASE_VALUE, uint32(val2));
                pet->UpdateAttackPowerAndDamage();
                pet->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, uint32(val2 * attPowerMultiplier));
                pet->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, uint32(val2 * attPowerMultiplier) * 2 + master->getLevel());
                pet->UpdateDamagePhysical(BASE_ATTACK);
            }

            void DoNormalAttack(const uint32 diff)
            {
                AttackerSet m_attackers = master->getAttackers();

                if (opponent == NULL)
                    return;

                if (opponent->isDead())
                    return;

                if (pet && pet != NULL && pet->isDead())
                {
                    master->SetBotsPetDied();
                    pet = NULL;
                }

                if (pet && pet != NULL && pet->isAlive() && !pet->isInCombat())
                    pet->AI()->AttackStart(opponent);

                if (!isTimerReady(uiGc_Timer))
                    return;

                if (opponent->HasUnitMovementFlag(UNIT_FLAG_FLEEING))
                    return;

                if (SPELL_CURSE_OF_THE_ELEMENTS && !HasAuraName(opponent, SPELL_CURSE_OF_THE_ELEMENTS))
                {
                    doCast(opponent, SPELL_CURSE_OF_THE_ELEMENTS);
                    GiveManaBack();
                }

                if (SPELL_CORRUPTION && !HasAuraName (opponent, SPELL_CORRUPTION, me->GetGUID()))
                {
                    doCast(opponent, SPELL_CORRUPTION);
                    GiveManaBack();
                }

                if (SPELL_HAUNT && !HasAuraName (opponent, SPELL_HAUNT, me->GetGUID()))
                {
                    doCast(opponent, SPELL_HAUNT);
                    GiveManaBack();
                    return;
                }

                if (SPELL_UNSTABLE_AFFLICTION && !HasAuraName (opponent, SPELL_UNSTABLE_AFFLICTION, me->GetGUID()))
                {
                    doCast(opponent, SPELL_UNSTABLE_AFFLICTION);
                    GiveManaBack();
                    return;
                }

                if (!HasAuraName(opponent, SPELL_IMMOLATE, me->GetGUID()))
                {
                    doCast(opponent, SPELL_IMMOLATE);
                    GiveManaBack();
                    return;
                } 
                else if (SPELL_CONFLAGRATE && isTimerReady(uiConflagrate_Timer))
                {
                    doCast(opponent, SPELL_CONFLAGRATE);
                    uiConflagrate_Timer = 100;
                    GiveManaBack();
                    return;
                }

                if (SPELL_CHAOS_BOLT && isTimerReady(uiChaosBolt_Timer))
                {
                    doCast(opponent, SPELL_CHAOS_BOLT);
                    GiveManaBack();
                    uiChaosBolt_Timer = 120;
                    return;
			    }
                else
                    doCast(opponent, SPELL_SHADOW_BOLT);

                GiveManaBack();
            } //DoNormalAttack

            void JustDied(Unit* /*who*/)
            {
                master->SetBotCommandState(COMMAND_FOLLOW);
                state = 1;
                next_state = 0;
                next_state_timer = 0;

                if (pet && pet != NULL)
                {
                    master->SetBotsPetDied();
                    pet = NULL;
                }
            }

            void KilledUnit(Unit* /*who*/)
            {
                ((Player*)master)->SetBotCommandState(COMMAND_FOLLOW);
			
                if (pet && pet->isAlive()) 
                    pet->GetMotionMaster()->MoveFollow(me, PET_FOLLOW_DIST * urand(1, 2), PET_FOLLOW_ANGLE);
            }

            void ReceiveEmote(Player* player, uint32 emote)
            {
                if (emote == TEXT_EMOTE_RUDE)
                {
                    me->AttackStop();
                    me->SetReactState(REACT_PASSIVE);
                    DoCast(me, SPELL_PETRIFY);
                }

                if (emote == TEXT_EMOTE_ROAR)
                {
                    me->RemoveAurasDueToSpell(SPELL_PETRIFY);
                    me->SetReactState(REACT_AGGRESSIVE);
                }

                if (emote == TEXT_EMOTE_WAVE)
                    player->SetBotCommandState(COMMAND_FOLLOW);
            }

            void ReduceCD()
            {
                if (uiPotion_Timer > 0)
                    --uiPotion_Timer;

			    if (uiFirstAid_Timer > 0)
                    --uiFirstAid_Timer;

			    if (uiGc_Timer > 0)
                    --uiGc_Timer;

                if (uiConflagrate_Timer > 0)
                    --uiConflagrate_Timer;

			    if (uiChaosBolt_Timer > 0)
                    --uiChaosBolt_Timer;
            }
		
            void UpdateAI(const uint32 diff)
            {
                ReduceCD();

                if (IAmDead()) 
                    return;

                if (pet && pet != NULL && pet->isDead())
                {
                    master->SetBotsPetDied();
                    pet = NULL;
                }

                if (pet && master->m_botHasPet == false)
                {
                    master->SetBotsPetDied();
                    pet = NULL;
                }

                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);

                if (me->GetHealth() < me->GetMaxHealth()*0.3 && isTimerReady(uiPotion_Timer))
                {
                    doCast(me, SPELL_HEALING_POTION);
                    uiPotion_Timer = 60000;
                }
			
                if (me->GetPower(POWER_MANA) < me->GetMaxPower(POWER_MANA)*0.2)
                {
                    if (isTimerReady(uiPotion_Timer))
                    {
                        doCast(me, SPELL_MANA_POTION);
                        uiPotion_Timer = 60000;
                    }
                    else
                    {
                        if (oom_spam == false)
                            oom_spam = true;

                        ScriptedAI::UpdateAI(diff);
                    }
                }
            
                oom_spam = false;

                ScriptedAI::UpdateAI(diff);

                opponent = SelectTarget(SELECT_TARGET_TOPAGGRO, 0);
			
                if (!opponent && !me->getVictim())
                {
                    ResetOrGetNextTarget();

                    if (pet != NULL && pet->isAlive())
                    {
                        master->SetBotsPetDied();
                        pet = NULL;
                    }

                    return;
                }

                if (pet == NULL)
                    CreatePet();

                if (pet && pet->isAlive() && !pet->isInCombat() && me->getVictim()) 
                {
                    pet->Attack (me->getVictim(), true);
                    pet->GetMotionMaster()->MoveChase(me->getVictim(), 1, 0);
                }

                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;

                DoNormalAttack(diff);
            }
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new warlock_botAI(pCreature);
        }
};

void AddSC_warlock_bot()
{
    new warlock_bot();
}