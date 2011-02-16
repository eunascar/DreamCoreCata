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

enum Spells
{
    SPELL_FEAR_WARD       = 6346,
    SPELL_GREATER_HEAL    = 6346
};

#define SPELL_DIVINE_SPIRIT       SPELL_DIVINE_SPIRIT_A[SPELL_LEVEL]
#define SPELL_FADE                SPELL_FADE_A[SPELL_LEVEL]
#define SPELL_HEAL                SPELL_HEAL_A[SPELL_LEVEL]
#define SPELL_INNER_FIRE          SPELL_INNER_FIRE_A[SPELL_LEVEL]
#define SPELL_PRAYER_OF_SHADOW    SPELL_PRAYER_OF_SHADOW_A[SPELL_LEVEL]
#define SPELL_PW_FORTITUDE        SPELL_PW_FORTITUDE_A[SPELL_LEVEL]
#define SPELL_PW_SHIELD           SPELL_PW_SHIELD_A[SPELL_LEVEL]
#define SPELL_RENEW               SPELL_RENEW_A[SPELL_LEVEL]
#define SPELL_RESURRECTION        SPELL_RESURRECTION_A[SPELL_LEVEL]

uint32 SPELL_DIVINE_SPIRIT_A    [] = {0, 0, 0, 14752, 14818, 14819, 27841, 25312, 48073, 48073};
uint32 SPELL_FADE_A             [] = { 586, 586, 586, 586, 586, 586, 586, 586, 586 };
uint32 SPELL_HEAL_A             [] = { 2060, 10963, 10964, 10965, 25314, 25210, 25213, 48062, 48063 };
uint32 SPELL_INNER_FIRE_A       [] = { 588, 7128, 602, 1006, 10951, 10952, 25431, 25431, 48040, 48040 };
uint32 SPELL_PRAYER_OF_SHADOW_A [] = { 0, 0, 0, 0, 0, 27683, 27683, 39374, 39374, 39374 };
uint32 SPELL_PW_FORTITUDE_A     [] = { 1243, 1244, 1245, 2791, 10937, 10938, 25389, 48161, 48161 };
uint32 SPELL_PW_SHIELD_A        [] = { 17, 592, 3747, 6066, 10899, 10900, 10901, 25218, 25218 };
uint32 SPELL_RENEW_A            [] = { 139, 6074, 6075, 6076, 6077, 6078, 10927, 10928, 10929 };
uint32 SPELL_RESURRECTION_A     [] = { 2006, 2006, 2006, 2010, 10880, 10881, 20770, 25435, 25435 };

class priest_bot : public CreatureScript
{
    public:
        priest_bot()
            : CreatureScript("priest_bot")
        {
        }

        struct priest_botAI : public bot_ai
        {
            priest_botAI(Creature *c) :bot_ai(c)
            {
                Reset();
            }

            uint32 uiGreater_Heal_Timer;
            uint32 uiHeal_Timer;
            uint32 uiRenew_Timer;
            uint32 uiSelfRenew_Timer;
            uint32 uiPWS_Timer;
            uint32 uiOthersHeal_Timer;
            uint32 uiOom_Timer;
            uint32 uiFade_Timer;
            uint32 uiRez_Timer;

            Unit* mobsTarget;

            void Reset()
            {
                uiGc_Timer              = 0;
                uiGreater_Heal_Timer    = 0;
                uiHeal_Timer            = 0;
                uiRenew_Timer           = 0;
                uiSelfRenew_Timer       = 0;
                uiPWS_Timer             = 0;
                uiOthersHeal_Timer      = 0;
                uiOom_Timer             = 0;
                uiFade_Timer            = 0;
                uiPotion_Timer          = 0;
                uiRez_Timer             = 0;
            }

            void EnterEvadeMode()
            {
                uiOom_Timer = 0;
            }

            void EnterCombat(Unit* /*who*/) { }

            void AttackStart(Unit* who)
            {
                me->GetMotionMaster()->MoveFollow(master, urand(5, 10), PET_FOLLOW_ANGLE);
            }

            void KilledUnit(Unit* /*who*/)
            {
                ((Player*)master)->SetBotCommandState(COMMAND_FOLLOW);
            }

            void MoveInLineOfSight(Unit* target)
            {
                if (master == NULL || master == 0)
                    return;

                if (target->GetGUID()  ==  master->GetGUID())
                    return;

                if (!target->IsFriendlyTo(master))
                    return;

                if (target->isAlive() && ((target->GetHealth() * 100) < 100))
                    me->CastSpell(target, SPELL_HEAL, false);
            }

            bool isTimerReady(int32 timer)
            {
                if (timer <= 0 && uiGc_Timer <= 0)
                    return true;
                else
                    return false;
            }

            void decrementTimers()
            {
                if (uiGc_Timer > 0)
                    --uiGc_Timer;

                if (uiGreater_Heal_Timer > 0)
                    --uiGreater_Heal_Timer;

                if (uiHeal_Timer > 0)
                    --uiHeal_Timer;

                if (uiOthersHeal_Timer > 0)
                    --uiOthersHeal_Timer;

                if (uiFade_Timer > 0)
                    --uiFade_Timer;

                if (uiSelfRenew_Timer > 0)
                    --uiSelfRenew_Timer;

                if (uiRenew_Timer > 0)
                    --uiRenew_Timer;

                if (uiPWS_Timer > 0)
                    --uiPWS_Timer;

                if (uiPotion_Timer > 0)
                    --uiPotion_Timer;
            }

            void UpdateAI(const uint32 diff)
            {
                decrementTimers();

                if (IAmDead())
                    return;

                if (!me->isInCombat())
                    DoNonCombatActions();

                //buff and heal master's group
                BuffAndHealGroup(master);

                //check group members
                Group::MemberSlotList const &a =((Player*)master)->GetGroup()->GetMemberSlots();
                for (Group::member_citerator itr = a.begin(); itr != a.end(); itr++)
                {
                    Player *tPlayer = ((Player *)master)->GetObjPlayer(itr->guid);
                    if (tPlayer == NULL)
                        continue;
                }

                //if low on mana, drink a potion
                if (me->GetPower(POWER_MANA) < 400 && isTimerReady(uiPotion_Timer))
                {
                    doCast(me, SPELL_MANA_POTION, true);
                    uiPotion_Timer = 1500;
                }
                //if after drinking a potion still low on mana
                //let everyone know that you are oom.
                if (me->GetPower(POWER_MANA)/me->GetMaxPower(POWER_MANA) < 10)
                {
                    if (uiOom_Timer == 0)
                        uiOom_Timer = 1;
                }

                // Heal myself
                if (me->GetHealth() * 100 / me->GetMaxHealth() < 90)
                {
                    if (uiFade_Timer <= 0 && me->isInCombat() && isTimerReady(uiFade_Timer))
                    {
                        doCast(me, SPELL_FADE);
                        uiFade_Timer = 30;
                        return;
                    }

                    HealTarget (me, me->GetHealth() * 100 / me->GetMaxHealth());
                }

                //now try to heal bots and pets.  DoSelectLowestHpFriendly will get
                //everyone in group including bots and pets.  Unfortunately it can
                //not be triggered for % of lost HP, so we just set it to -1000.
                //This means low level players wont be healed because they wont have
                //enough HP.
                if (isTimerReady(uiOthersHeal_Timer))
                {
                    Unit* target;

                    if (target = DoSelectLowestHpFriendly(40, 1000))
                    {
                        doCast(target, SPELL_HEAL, false);
                        GiveManaBack();
                        uiOthersHeal_Timer = 50;
                    }
                    else if (target = DoSelectLowestHpFriendly(40, 500))
                    {
                        if (!target->HasAura(SPELL_RENEW, 0))
                        {
                            doCast(target, SPELL_RENEW, false);
                            GiveManaBack();
                            uiOthersHeal_Timer = 100;
                        }
                    }
                }
            }

            bool HealTarget(Unit* target, uint8 hp)
            {
                if (!isTimerReady(uiGc_Timer))
                    return false;

                if (me->IsNonMeleeSpellCasted(true))
                    return false;

                if (!target || target->isDead())
                    return false;

                if ((hp < 50) && isTimerReady(uiPWS_Timer) && !target->isDead())
                {
                    doCast(target, SPELL_PW_SHIELD);
                    uiPWS_Timer = 120;
                }

                if ((hp < 90) && hp > 75 && isTimerReady(uiRenew_Timer))
                {
                    doCast(target, SPELL_RENEW, true);
                    GiveManaBack();
                    uiRenew_Timer = 90;
                    uiHeal_Timer = uiHeal_Timer + 5; //wait 5 seconds before casting a real heal
                    return true;
                }

                if (hp < 75 && hp > 5 && isTimerReady(uiHeal_Timer) && !target->isDead())
                {
                    doCast(target, SPELL_HEAL);
                    GiveManaBack();
                    uiHeal_Timer = 10;
                    return true;
                }

                if (hp < 5 && isTimerReady(uiGreater_Heal_Timer) && !target->isDead())
                {
                    doCast(target, SPELL_GREATER_HEAL);
                    GiveManaBack();
                    uiGreater_Heal_Timer = uiGreater_Heal_Timer + 900;
                    return true;
                }

                return true;
            }

            void BuffTarget(Unit* target)
            {
                if (!HasAuraName(target, GetSpellName(SPELL_PW_FORTITUDE)))
                {
                    doCast(target, SPELL_PW_FORTITUDE, false);
                    GiveManaBack();
                }

                if (!HasAuraName(target, GetSpellName(SPELL_PRAYER_OF_SHADOW)))
                {
                    doCast(target, SPELL_PRAYER_OF_SHADOW, false);
                    GiveManaBack();
                }
            }

            void DoNonCombatActions()
            {
                //if eating or drinking don't do anything
                if (me->HasAura(10256) || me->HasAura(1137))
                    return;

                Feast();

                //buff master
                if (!HasAuraName(master, SPELL_PRAYER_OF_SHADOW, 0) && isTimerReady(uiGc_Timer))
                    doCast(master, SPELL_PRAYER_OF_SHADOW, true);

                if (!HasAuraName(master, SPELL_FEAR_WARD, 0) && isTimerReady(uiGc_Timer))
                    doCast(master, SPELL_FEAR_WARD, true);

                if (!HasAuraName(master, SPELL_DIVINE_SPIRIT, 0) && isTimerReady(uiGc_Timer))
                {
                    doCast(master, SPELL_DIVINE_SPIRIT, true);
                    GiveManaBack();
                }

                //buff myself
                if (!me->HasAura(SPELL_INNER_FIRE, 0) && isTimerReady(uiGc_Timer))
                    doCast(me, SPELL_INNER_FIRE, true);

                if (!me->HasAura(SPELL_PW_FORTITUDE, 0) && isTimerReady(uiGc_Timer))
                    doCast(me, SPELL_PW_FORTITUDE, true);

                //buff and heal master's group
                if (master->GetGroup())
                    RezGroup(SPELL_RESURRECTION, master);
            }

            void ReceiveEmote(Player* player, uint32 emote)
            {
                if (emote == TEXTEMOTE_RUDE)
                {
                    me->AttackStop();
	                me->SetReactState(REACT_PASSIVE);
                }

                if (emote == TEXTEMOTE_ROAR)
        	        me->SetReactState(REACT_AGGRESSIVE);

                if (emote == TEXTEMOTE_WAVE)
                    player->SetBotCommandState(COMMAND_FOLLOW);

                if (emote == TEXTEMOTE_BOW)
                {
                    ((priest_botAI*)me->AI())->doCast(player, SPELL_PW_FORTITUDE, true);
                    ((priest_botAI*)me->AI())->doCast(player, SPELL_PRAYER_OF_SHADOW, false);
                }
            }
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new priest_botAI(pCreature);
        }
};

void AddSC_priest_bot()
{
    new priest_bot();
}
