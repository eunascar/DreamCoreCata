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

#define SPELL_BACKSTAB           SPELL_BACKSTAB_A[SPELL_LEVEL]
#define SPELL_DEADLY_POISON      SPELL_DEADLY_POISON_A[SPELL_LEVEL]
#define SPELL_DISMANTLE          SPELL_DISMANTLE_A[SPELL_LEVEL]
#define SPELL_EVISCERATE         SPELL_EVISCERATE_A[SPELL_LEVEL]
#define SPELL_KICK               SPELL_KICK_A[SPELL_LEVEL]
#define SPELL_KIDNEY_SHOT        SPELL_KIDNEY_SHOT_A[SPELL_LEVEL]
#define SPELL_MUTILATE           SPELL_MUTILATE_A[SPELL_LEVEL]
#define SPELL_RUPTURE            SPELL_RUPTURE_A[SPELL_LEVEL]
#define SPELL_SHADOWSTEP         SPELL_SHADOWSTEP_A[SPELL_LEVEL]
#define SPELL_SINISTER_STRIKE    SPELL_SINISTER_STRIKE_A[SPELL_LEVEL]
#define SPELL_SLICE_AND_DICE     SPELL_SLICE_AND_DICE_A[SPELL_LEVEL]
#define SPELL_WOUND_POISON       SPELL_WOUND_POISON_A[SPELL_LEVEL]

uint32 SPELL_BACKSTAB_A        [] = { 53, 2589, 2591, 8721, 11279, 11280, 11281, 25300, 25300 };
uint32 SPELL_DEADLY_POISON_A   [] = { 0, 0, 0, 2818, 2819, 11354, 26968, 57969, 57969 };
uint32 SPELL_DISMANTLE_A       [] = { 0, 0, 51722, 51722, 51722, 51722, 51722, 51722, 51722 };
uint32 SPELL_EVISCERATE_A      [] = { 11300, 11300, 11300, 11300, 11300, 11300, 11300, 11300, 11300 };
uint32 SPELL_KICK_A            [] = { 0, 1766, 1767, 1767, 1768, 1769, 38768, 38768, 38768 };
uint32 SPELL_KIDNEY_SHOT_A     [] = { 0, 0, 0, 0, 0, 0, 8643, 30832, 41389 };
uint32 SPELL_MUTILATE_A        [] = {0, 0, 0, 0, 48664, 48664, 48664,48664, 48664};
uint32 SPELL_RUPTURE_A         [] = { 0, 0, 1943, 8640, 11273, 11274, 11275, 26867, 48672, 48672 };
uint32 SPELL_SHADOWSTEP_A      [] = { 0, 0, 0, 0, 0, 36554, 36554, 36554, 36554 };
uint32 SPELL_SINISTER_STRIKE_A [] = { 1757, 1758, 1759, 8621, 11293, 11294, 26862, 48638, 48638 };
uint32 SPELL_SLICE_AND_DICE_A  [] = { 0, 5171, 5171, 5171, 6774, 6774, 6774, 6774, 6774, 6774 };
uint32 SPELL_WOUND_POISON_A    [] = { 0, 0, 0, 13218, 13222, 13223, 13224, 27189, 57974, 57974 };

class rogue_bot : public CreatureScript
{
    public:
        rogue_bot()
            : CreatureScript("rogue_bot")
        {
        }

        struct rogue_botAI : public bot_ai
        {
            rogue_botAI(Creature *c) : bot_ai(c)
            {
                Reset();
            }

            uint32 uiBackstab_Timer;
            uint32 uiSinisterStrike_Timer;
            uint32 uiEviscerate_Timer;
            uint32 uiSliceAndDice_Timer;
            uint32 uiRupture_Timer;
            uint32 uiKick_Timer;
            uint32 uiPoison_Timer;
            uint32 uiShadowstep_Timer;
            uint32 uiMutilate_Timer;

            uint8 energy;
            uint8 comboPoints;

            Unit* opponent;

            void Reset()
            {
                uiGc_Timer                = 0;
                uiBackstab_Timer          = 50;
                uiMutilate_Timer          = 0;
                uiSinisterStrike_Timer    = 30;
                uiEviscerate_Timer        = 90;
                uiSliceAndDice_Timer      = 75;
                uiRupture_Timer           = 80;
                uiKick_Timer              = 20;
                uiPoison_Timer            = 15;
                uiPotion_Timer            = 0;
                uiShadowstep_Timer        = 0;
                comboPoints               = 0;
                energy                    = 100;

                opponent                  = NULL;

                me->setPowerType(POWER_ENERGY);
                me->SetMaxPower(POWER_ENERGY, 100);
                me->SetPower(POWER_ENERGY, 100);
            }

            bool isTimerReady(int32 timer)
            {
                if (timer <= 0 && uiGc_Timer <= 0) 
                    return true;
                else
                    return false;
            }

            void doCast(Unit *victim, uint32 spellId, bool triggered = false)
            {
                if (spellId == 0)
                    return;

                me->SetStandState(UNIT_STAND_STATE_STAND);
                uiGc_Timer = 10;
                DoCast(victim, spellId, triggered);
            }

            void decrementTimers()
            {
                if (uiGc_Timer > 0)
                    --uiGc_Timer;

                if (uiBackstab_Timer > 0)
                    --uiBackstab_Timer;

                if (uiKick_Timer > 0)
                    --uiKick_Timer;

                if (uiSliceAndDice_Timer > 0)
                    --uiSliceAndDice_Timer;

                if (uiSinisterStrike_Timer > 0)
                    --uiSinisterStrike_Timer;

                if (uiEviscerate_Timer > 0)
                    --uiEviscerate_Timer;

                if (uiRupture_Timer > 0)
                    --uiRupture_Timer;

                if (uiPoison_Timer > 0)
                    --uiPoison_Timer;

                if (uiPotion_Timer > 0)
                    --uiPotion_Timer;

                if (uiShadowstep_Timer > 0)
                    --uiShadowstep_Timer;

                if (uiMutilate_Timer > 0)
                    --uiMutilate_Timer;
            }

            void KilledUnit(Unit* /*who*/)
            {
                ((Player*)master)->SetBotCommandState(COMMAND_FOLLOW);
            }

            void AttackStart(Unit* who)
            {
                EnterCombat(who);
                ScriptedAI::AttackStart(who);
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

            void UpdateAI(const uint32 diff)
            {
                DoMeleeAttackIfReady();

                decrementTimers();

                if (IAmDead())
                    return;

                opponent = SelectTarget(SELECT_TARGET_TOPAGGRO, 0);

                if (!opponent && !me->getVictim())
                {
                    comboPoints = 0;
                    energy = 100;
                    ResetOrGetNextTarget();
                    return;
                }

                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);

                energy += 5;

                if (comboPoints > 5)
                    comboPoints = 5;

                //interrupt any spells
                if (opponent->IsNonMeleeSpellCasted(true) && energy >= 25)
                {
                    if (isTimerReady(uiKick_Timer))
                    {
                        doCast(opponent, SPELL_KICK);
                        uiKick_Timer = 100;
                        energy -= 25;
                    }
                    else if (comboPoints > 0)
                    {
                        switch(comboPoints)
                        {
                            case 1:
                                doCast(opponent, SPELL_KIDNEY_SHOT);
                                --comboPoints;
                                break;
                            case 2:
                                doCast(opponent, SPELL_KIDNEY_SHOT);
                                comboPoints -= 2;
                                break;
                            default:
                                doCast(opponent, SPELL_KIDNEY_SHOT);
                                comboPoints-=3;
                                break;
                        }

                        energy -= 25;
                    }
                }

                if (!opponent->isInFrontInMap(me, 5) && isTimerReady(uiBackstab_Timer))
                {
                    doCast(opponent, SPELL_BACKSTAB);
                    uiBackstab_Timer = 50;
                    energy -= 60;
                }
                /*else if (isTimerReady(Shadowstep_Timer) && energy > 10 && me->GetDistance(opponent) < 25)
                {
                    //doCast(opponent, SHADOWSTEP);
                    Shadowstep_Timer = 300;
                    energy -= 10;

                    //NPCs can't really shadowstep so fake it
                    float x = opponent->GetPositionX();
                    float y = opponent->GetPositionY();
                    float z = opponent->GetPositionZ();
                    float o = opponent->GetOrientation();

                    me->Relocate(x-4, y-4, z, o);
                    me->SendMonsterMoveWithSpeed(x-4, y-4, 1, 0);
                    doCast(opponent, BACKSTAB);
                    return;
                }*/

                if (isTimerReady(uiSliceAndDice_Timer) && comboPoints > 0 && !me->HasAura(SPELL_SLICE_AND_DICE))
                {
                    doCast(opponent, SPELL_SLICE_AND_DICE);

                    // since npcs don't use combo points, they can only case
                    // first level of spell.  So only remove 1 combo point
                    --comboPoints;

                    uiSliceAndDice_Timer = 75;
                    energy -= 25;
                }

                if (isTimerReady(uiMutilate_Timer) && energy>60)
                {
                    // TODO: calculate correct dmg for mutilate (dont forget poison bonus)
                    // for now use same formula as evicerate
                    uint32 base_attPower = me->GetUInt32Value(UNIT_FIELD_ATTACK_POWER);
                    //float minDmg = me->GetFloatValue(UNIT_FIELD_MINDAMAGE);
                    float minDmg = me->GetWeaponDamageRange(BASE_ATTACK, MINDAMAGE);
                    int damage = irand(int32(base_attPower * 5 * 0.03f), int32(base_attPower * 5 * 0.07f)) + minDmg + me->getLevel();

                    // compensate for lack of attack power
                    damage = damage * (rand() % 4 + 1);

                    me->CastCustomSpell(opponent, SPELL_MUTILATE, &damage, NULL, NULL, false, NULL, NULL);

                    //doCast (me, MUTILATE);
                    uiMutilate_Timer = 75;
                    ++comboPoints;
                    energy -= 60;
                }

                if (isTimerReady(uiEviscerate_Timer) && comboPoints>0) 
                { 
                    uint32 base_attPower = me->GetUInt32Value(UNIT_FIELD_ATTACK_POWER);
                    float minDmg = me->GetWeaponDamageRange(BASE_ATTACK, MINDAMAGE);
                    int damage = irand(int32(base_attPower * 5 * 0.03f), int32(base_attPower * 5 * 0.07f)) + minDmg + me->getLevel();
                    // compensate for lack of attack power
                    damage = damage * (rand() % 4 + 1);
                    // Eviscerate and Envenom Bonus Damage (Deathmantle item set effect)
                    if (me->HasAura(37169))
                        damage += comboPoints * 40;

                    me->CastCustomSpell(opponent, SPELL_EVISCERATE, &damage, NULL, NULL, false, NULL, NULL);
                    comboPoints = 0;
                    energy -= 30;
                    uiEviscerate_Timer = 90;
                }

                if (isTimerReady(uiSinisterStrike_Timer) && comboPoints < 5)
                {
                    doCast(opponent, SPELL_SINISTER_STRIKE);
                    ++comboPoints;
                    uiSinisterStrike_Timer = 20;
                    energy -= 40;
                }

                if (isTimerReady(uiRupture_Timer))
                {
                    doCast(opponent, SPELL_RUPTURE);
                    comboPoints = 0;
                    uiRupture_Timer = 80;
                    energy -= 40;
                }

                //since npc can't really use poison, we'll pretend that we were able to poison his blades.
                if (isTimerReady(uiPoison_Timer) && !me->HasAura(SPELL_PETRIFY))
                {
                    //Deadly Poison has 40% chance of proccing
                    switch(rand() % 5)
                    {
                        case 0:
                        case 1:
                        case 2:
                            break;
                        case 4:
                        case 5:
                            if (SPELL_DEADLY_POISON)
                                DoCast(opponent, SPELL_DEADLY_POISON, true);
                                break;
                    }

                    //Wound Poison has 50% chance of procing
                    switch(rand()%2)
                    {
                        case 0:
                            break;
                        case 1:
                            if (SPELL_WOUND_POISON)
                                DoCast(opponent, SPELL_WOUND_POISON, true);
                            break;
                    }

                    uiPoison_Timer = 15;
                }

                //if low on health, drink a potion
                if (me->GetHealth() < me->GetMaxHealth() * 0.6 && isTimerReady(uiPotion_Timer))
                {
                    doCast(me, SPELL_HEALING_POTION);
                    uiPotion_Timer = 1500;
                }

                me->SetPower(POWER_ENERGY, energy);

                ScriptedAI::UpdateAI(diff);
            }
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new rogue_botAI(pCreature);
        }
};

void AddSC_rogue_bot()
{
    new rogue_bot();
}