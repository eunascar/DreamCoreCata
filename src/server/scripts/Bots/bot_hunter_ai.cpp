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

#define PET_ENTRY          100393
#define SPELL_AUTO_SHOT    75

#define SPELL_AIMED_SHOT            SPELL_AIMED_SHOT_A[SPELL_LEVEL]
#define SPELL_ARCANE_SHOT           SPELL_ARCANE_SHOT_A[SPELL_LEVEL]
#define SPELL_ASPECT_OF_THE_WILD    SPELL_ASPECT_OF_THE_WILD_A[SPELL_LEVEL]
#define SPELL_CHIMERA_SHOT          SPELL_CHIMERA_SHOT_A[SPELL_LEVEL]
#define SPELL_HUNTER_S_MARK         SPELL_HUNTER_S_MARK_A[SPELL_LEVEL]
#define SPELL_SCORPID_STING         SPELL_SCORPID_STING_A[SPELL_LEVEL]
#define SPELL_SILENCING_SHOT        SPELL_SILENCING_SHOT_A[SPELL_LEVEL]
#define SPELL_TRANQUILIZING_SHOT    SPELL_TRANQUILIZING_SHOT_A[SPELL_LEVEL]

uint32 SPELL_AIMED_SHOT_A         [] = { 0, 0, 19434, 20900, 20902, 20903, 20904, 49049, 49050, 49050 };
uint32 SPELL_ARCANE_SHOT_A        [] = { 3044, 14281, 14282, 14284, 14285, 14286, 27019, 49044, 49045, 49045 };
uint32 SPELL_ASPECT_OF_THE_WILD_A [] = {0, 0, 0, 0, 20043, 20190, 27045, 49071, 49071 };
uint32 SPELL_CHIMERA_SHOT_A       [] = { 0, 0, 0, 0, 0, 0, 53209, 53209, 53209, 53209 };
uint32 SPELL_HUNTER_S_MARK_A      [] = { 14325, 14325, 14325, 14325, 14325, 14325, 14325, 14325, 14325, 14325 };
uint32 SPELL_SCORPID_STING_A      [] = { 0, 0, 0, 0, 0, 0, 3043, 3043, 3043, 3043 };
uint32 SPELL_SILENCING_SHOT_A     [] = { 0, 0, 0, 34490, 34490, 34490, 34490, 34490, 34490, 34490 };
uint32 SPELL_TRANQUILIZING_SHOT_A [] = { 0, 0, 19801, 19801, 19801, 19801, 19801, 19801, 19801, 19801 };

class hunter_bot : public CreatureScript
{
    public:
        hunter_bot()
            : CreatureScript("hunter_bot")
        {
        }

        struct hunter_botAI : public bot_ai
        {
            hunter_botAI(Creature *c) :bot_ai(c)
            {
                Reset();
                pet = NULL;
            }

            bool oom_spam;

            Unit* opponent;
            Creature* pet;

            uint32 uiArcaneShot_Timer;
            uint32 uiChimeraShot_Timer;
            uint32 uiSilencingShot_Timer;
            uint32 uiAimedShot_Timer;

            void Reset()
            {
                oom_spam = false;

                opponent = NULL;

                uiArcaneShot_Timer = 0;
                uiChimeraShot_Timer = 0;
                uiSilencingShot_Timer = 0;
                uiAimedShot_Timer = 0;
                uiPotion_Timer = 0;
            }

            void AttackStart(Unit* who)
            {
                EnterCombat(who);
                ScriptedAI::AttackStartCaster(who, 33);
                me->AddThreat(who, 0.001f);
                who->AddThreat(me, 0.001f);
            }

            void CreatePet()
            {
                pet = master->GetBotsPet(PET_ENTRY);

                if (pet  ==  NULL)
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
                uint32 attPowerMultiplier=1;
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

                //try to get rid of enrage
                if (SPELL_TRANQUILIZING_SHOT && HasAuraName(opponent, "Enrage"))
                {
                    me->InterruptNonMeleeSpells(true, SPELL_AUTO_SHOT);
                    doCast(opponent, SPELL_TRANQUILIZING_SHOT);
                    GiveManaBack();
                }

                //silence it
                if (SPELL_SILENCING_SHOT && opponent->IsNonMeleeSpellCasted(true) && isTimerReady(uiSilencingShot_Timer))
                {
                    doCast(opponent, SPELL_SILENCING_SHOT);
                    uiSilencingShot_Timer = 200;
                    GiveManaBack();
                }

                //mark it
                if (!HasAuraName(opponent, "Hunter's Mark"))
                {
                    doCast(opponent, SPELL_HUNTER_S_MARK);
                    GiveManaBack();
                }

                //sting it
                if (SPELL_SCORPID_STING && !opponent->HasAura(SPELL_SCORPID_STING, me->GetGUID()))
                {
                    me->InterruptNonMeleeSpells(true, SPELL_AUTO_SHOT);
                    doCast(opponent, SPELL_SCORPID_STING);
                    GiveManaBack();
                }

                if (SPELL_CHIMERA_SHOT && isTimerReady(uiChimeraShot_Timer))
                {
                    me->InterruptNonMeleeSpells(true, SPELL_AUTO_SHOT);
                    doCast(opponent, SPELL_CHIMERA_SHOT);
                    uiChimeraShot_Timer = 100;
                    GiveManaBack();
                }

                if (SPELL_ARCANE_SHOT && isTimerReady(uiArcaneShot_Timer))
                {
                    me->InterruptNonMeleeSpells( true, SPELL_AUTO_SHOT );
                    doCast(opponent, SPELL_ARCANE_SHOT);
                    uiArcaneShot_Timer = 60;
                    GiveManaBack();
                }

                if (SPELL_AIMED_SHOT && isTimerReady(uiAimedShot_Timer))
                {
                    me->InterruptNonMeleeSpells( true, SPELL_AUTO_SHOT );
                    doCast(opponent, SPELL_AIMED_SHOT);
                    uiAimedShot_Timer = 100;
                    GiveManaBack();
                }

                doCast(opponent, SPELL_AUTO_SHOT);
            }

            void DoNonCombatActions()
            {
                if (SPELL_ASPECT_OF_THE_WILD && !HasAuraName(me, "Aspect of the Wild"))
                    doCast(master, SPELL_ASPECT_OF_THE_WILD);
            }

            void JustDied(Unit* /*who*/)
            {
                master->SetBotCommandState(COMMAND_FOLLOW);
            }

            void KilledUnit(Unit* /*who*/)
            {
                ((Player*)master)->SetBotCommandState(COMMAND_FOLLOW);
            }

            void ReduceCD(const uint32 diff)
            {
                if (uiGc_Timer > 0)
                    --uiGc_Timer;

                if (uiArcaneShot_Timer > 0)
                    --uiArcaneShot_Timer;

                if (uiChimeraShot_Timer > 0)
                    --uiChimeraShot_Timer;

                if (uiSilencingShot_Timer > 0)
                    --uiSilencingShot_Timer;

                if (uiAimedShot_Timer > 0)
                    --uiAimedShot_Timer;
            }

            void ReceiveEmote(Player* player, uint32 emote)
            {
                if (emote == TEXTEMOTE_RUDE)
                {
                    me->AttackStop();
                    me->SetReactState(REACT_PASSIVE);
                    DoCast(me, SPELL_PETRIFY);
                }

                if (emote == TEXTEMOTE_ROAR)
                {
                    me->RemoveAurasDueToSpell(SPELL_PETRIFY);
                    me->SetReactState(REACT_AGGRESSIVE);
                }

                if (emote == TEXTEMOTE_WAVE)
                    player->SetBotCommandState(COMMAND_FOLLOW);
            }

            void UpdateAI(const uint32 diff)
            {
                DoMeleeAttackIfReady();

                ReduceCD(diff);

                if (IAmDead())
                    return;

                if (!me->isInCombat())
                {
                    DoNonCombatActions();
                }

                if (pet && pet != NULL && pet->isDead())
                {
                    master->SetBotsPetDied();
                    pet = NULL;
                }

                //if we think we have a pet, but master doesn't, it means we teleported
                if (pet && master->m_botHasPet == false)
                {
                    master->SetBotsPetDied();
                    pet = NULL;
                }

                DoNormalAttack(diff);
                ScriptedAI::UpdateAI(diff);

                //if low on health, drink a potion
                if (me->GetHealth() < me->GetMaxHealth() * 0.6 && isTimerReady(uiPotion_Timer))
                {
                    doCast(me, SPELL_HEALING_POTION);
                    uiPotion_Timer = 1500;
                }

                //if low on mana, drink a potion
                if (me->GetPower(POWER_MANA) < me->GetMaxPower(POWER_MANA) * 0.2)
                {
                    if (isTimerReady(uiPotion_Timer))
                    {
                        doCast(me, SPELL_MANA_POTION);
                        uiPotion_Timer = 1500;
                    }
                }

                opponent = SelectUnit(SELECT_TARGET_TOPAGGRO, 0);

                if (!opponent && !me->getVictim())
                {
                    ResetOrGetNextTarget();

                    //to reduce the number of crashes, remove pet whenever we are not in combat
                    if (pet != NULL && pet->isAlive())
                    {
                        master->SetBotsPetDied();
                        pet = NULL;
                    }

                    return;
                }

                if (pet  ==  NULL)
                    CreatePet();

                if (pet && pet->isAlive() && !pet->isInCombat() && me->getVictim())
                {
                    pet->Attack (me->getVictim(), true);
                    pet->GetMotionMaster()->MoveChase(me->getVictim(), 1, 0);
                }
            }
	    };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new hunter_botAI(pCreature);
        }
};

void AddSC_hunter_bot()
{
    new hunter_bot();
}