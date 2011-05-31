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
    SPELL_CAT_FORM                 = 768,
    SPELL_BEAR_FORM_MOD            = 1178,
    SPELL_CAT_FORM_MOD             = 3025,
    SPELL_BEAR_FORM                = 9634,
    SPELL_WARSTOMP                 = 20549
};

#define SPELL_CLAW                 SPELL_CLAW_A[SPELL_LEVEL]
#define SPELL_CURE_POISON          SPELL_CURE_POISON_A[SPELL_LEVEL]
#define SPELL_DEMORALIZING_ROAR    SPELL_DEMORALIZING_ROAR_A[SPELL_LEVEL]
#define SPELL_FAIRIE_FIRE          SPELL_FAIRIE_FIRE_A[SPELL_LEVEL]
#define SPELL_HEALING_TOUCH        SPELL_HEALING_TOUCH_A[SPELL_LEVEL]
#define SPELL_MANGLE_CAT           SPELL_MANGLE_CAT_A[SPELL_LEVEL]
#define SPELL_MARK_OF_THE_WILD     SPELL_MARK_OF_THE_WILD_A[SPELL_LEVEL]
#define SPELL_MOONFIRE             SPELL_MOONFIRE_A[SPELL_LEVEL]
#define SPELL_RAKE                 SPELL_RAKE_A[SPELL_LEVEL]
#define SPELL_REBIRTH              SPELL_REBIRTH_A[SPELL_LEVEL]
#define SPELL_REJUVENATION         SPELL_REJUVENATION_A[SPELL_LEVEL]
#define SPELL_REGROWTH             SPELL_REGROWTH_A[SPELL_LEVEL]
#define SPELL_RIP                  SPELL_RIP_A[SPELL_LEVEL]
#define SPELL_SHRED                SPELL_SHRED_A[SPELL_LEVEL]
#define SPELL_STARFIRE             SPELL_STARFIRE_A[SPELL_LEVEL]
#define SPELL_SWIPE                SPELL_SWIPE_A[SPELL_LEVEL]
#define SPELL_THORNS               SPELL_THORNS_A[SPELL_LEVEL]
#define SPELL_WRATH                SPELL_WRATH_A[SPELL_LEVEL]

uint32 SPELL_CLAW_A              [] = { 0, 0, 1082, 3029, 5201, 9849, 9850, 27000, 48569, 48569 };
uint32 SPELL_CURE_POISON_A       [] = { 0, 8946, 8946, 14253, 14253, 14253, 14253, 14253, 14253 };
uint32 SPELL_DEMORALIZING_ROAR_A [] = { 0, 99, 1735, 9490, 9747, 9898, 26998, 26998, 48559, 48560, 48560 };
uint32 SPELL_FAIRIE_FIRE_A       [] = { 0, 16857, 16857, 17390, 17391, 17392, 27011, 27011, 48475, 48475 };
uint32 SPELL_HEALING_TOUCH_A     [] = { 5185, 5187, 5189, 6778, 9758, 9889, 26978, 26979, 26979 };
uint32 SPELL_MANGLE_CAT_A        [] = { 0, 0, 0, 0, 0, 33982, 33983, 48565, 48566, 48566 };
uint32 SPELL_MARK_OF_THE_WILD_A  [] = { 1126, 5232, 6756, 5234, 8907, 21849, 21850, 26991, 48470 };
uint32 SPELL_MOONFIRE_A          [] = { 8921, 8924, 8925, 8928, 8929, 9834, 26987, 26988, 26988 };
uint32 SPELL_RAKE_A              [] = { 0, 0, 1822, 1823, 1824, 9904, 27003, 27003, 48574, 48574 };
uint32 SPELL_REBIRTH_A           [] = { 0, 0, 2006, 2010, 10880, 10881, 20770, 25435, 25435 };
uint32 SPELL_REGROWTH_A          [] = { 0, 8936, 8939, 8941, 9750, 9857, 9858, 26980, 96980, 48442, 48442 };
uint32 SPELL_REJUVENATION_A      [] = { 774, 1058, 2090, 2091, 3627, 9840, 26981, 26982, 48440, 48440 };
uint32 SPELL_RIP_A               [] = { 0, 0, 1079, 9492, 9493, 9752, 9894, 9896, 27008, 27008 };
uint32 SPELL_SHRED_A             [] = { 0, 0, 5221, 6800, 8992, 9829, 9830, 27001, 27002, 27002 };
uint32 SPELL_STARFIRE_A          [] = { 0, 0, 2912, 8950, 8951, 9875, 25298, 26986, 26986 };
uint32 SPELL_SWIPE_A             [] = { 0, 779, 780, 769, 9754, 9908, 26997, 26997, 26997 };
uint32 SPELL_THORNS_A            [] = { 467, 782, 1075, 8914, 9756, 9910, 26992, 26992, 53307, 53307 };
uint32 SPELL_WRATH_A             [] = { 5176, 5178, 5179, 5180, 8905, 9912, 26984, 26985, 48461, 48461 };

class druid_bot : public CreatureScript
{
    public:
        druid_bot()
            : CreatureScript("druid_bot")
        {
        }

        struct bot_druid_ai : public bot_ai
        {
            bot_druid_ai(Creature *c) : bot_ai(c)
            {
                Reset();
            }

            uint32 uiHeal_Timer;
            uint32 uiRegrowth_Timer;
            uint32 uiSelfRegrowth_Timer;
            uint32 uiSelfRejuvenation_Timer;
            uint32 uiSelfHeal_Timer;
            uint32 uiRejuvenation_Timer;
            uint32 uiOthersHeal_Timer;
            uint32 uiOom_Timer;
            uint32 uiFade_Timer;
            uint32 uiWarstomp_Timer;
            uint32 uiRez_Timer;
            uint32 uiDemoralizingRoar_Timer;
            uint32 uiSwipe_Timer;
            uint32 uiClaw_Timer;
            uint32 uiRake_Timer;
            uint32 uiShred_Timer;
            uint32 uiRip_Timer;
            uint32 uiMangleCat_Timer;
            uint32 uiMoonfire_Timer;
            uint32 uiStarfire_Timer;
            uint32 uiWrath_Timer;
            uint32 uiFairieFire_Timer;

            Unit* mobsTarget;
            Unit* opponent;

            void Reset()
            {
                uiGc_Timer = 0;
                uiPotion_Timer = 0;
                uiHeal_Timer = 0;
                uiRegrowth_Timer = 0;
                uiSelfRegrowth_Timer = 0;
                uiSelfRejuvenation_Timer = 0;
                uiSelfHeal_Timer = 0;
                uiRejuvenation_Timer = 0;
                uiRez_Timer = 0;
                uiOthersHeal_Timer = 0;
                uiOom_Timer = 0;
                uiWarstomp_Timer = 0;
                uiDemoralizingRoar_Timer = 10;
                uiSwipe_Timer = 20;
                uiNoggenfogger_Timer = 0;
                uiClaw_Timer = 0;
                uiRake_Timer = 0;
                uiShred_Timer = 0;
                uiRip_Timer = 0;
                uiMangleCat_Timer = 0;
                uiMoonfire_Timer = 30;
                uiStarfire_Timer = 90;
                uiWrath_Timer = 150;
                uiFairieFire_Timer = 10;

                opponent = NULL;
            }

            void KilledUnit(Unit* /*who*/)
            {
                master->SetBotCommandState(COMMAND_FOLLOW);
            }

            //try to do a warstomp every time I get out of animal form
            void warstomp(const uint32 diff)
            {
                if (master->GetBotRace() != RACE_TAUREN)
                    return;

                if (uiWarstomp_Timer <= 0)
                {
                    if (opponent != NULL)
                    {
                        uiWarstomp_Timer = 1200; //2 minutes
                        doCast(opponent, SPELL_WARSTOMP, true);
                    }
                }
                else if (uiWarstomp_Timer >= 0)
                    --uiWarstomp_Timer;
            }

            void removeFeralForm(Player* m = 0)
            {
                if (!m)
                    m = master; //if m is set than use it, else use master

                if (me->HasAura(SPELL_BEAR_FORM, 0))
                {
                    me->RemoveAurasDueToSpell(SPELL_BEAR_FORM);
                    me->RemoveAurasDueToSpell(SPELL_BEAR_FORM_MOD);
                    m->SetBotMustWaitForSpell1(3000);
                }

                if (me->HasAura(SPELL_CAT_FORM, 0))
                {
                    me->RemoveAurasDueToSpell(SPELL_CAT_FORM);
                    me->RemoveAurasDueToSpell(SPELL_CAT_FORM_MOD);
                    m->SetBotMustWaitForSpell1(3000);
                }

                me->setPowerType(POWER_MANA);
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
                if (uiGc_Timer >= 0)
                    --uiGc_Timer;

                if (uiDemoralizingRoar_Timer >= 0)
                    --uiDemoralizingRoar_Timer;

                if (uiSwipe_Timer >= 0)
                    --uiSwipe_Timer;

                if (uiClaw_Timer >= 0)
                    --uiClaw_Timer;

                if (uiRake_Timer >= 0)
                    --uiRake_Timer;

                if (uiShred_Timer >= 0)
                    --uiShred_Timer;

                if (uiRip_Timer >= 0)
                    --uiRip_Timer;

                if (uiMangleCat_Timer >= 0)
                    --uiMangleCat_Timer;

                if (uiMoonfire_Timer >= 0)
                    --uiMoonfire_Timer;

                if (uiStarfire_Timer >= 0)
                    --uiStarfire_Timer;

                if (uiWrath_Timer >= 0)
                    --uiWrath_Timer;

                if (uiRip_Timer >= 0)
                    --uiFairieFire_Timer;

                if (uiPotion_Timer >= 0)
                    --uiPotion_Timer;

                if (uiRejuvenation_Timer >= 0)
                    --uiRejuvenation_Timer;

                if (uiRegrowth_Timer >= 0)
                    --uiRegrowth_Timer;

                if (uiHeal_Timer > 0)
                    --uiHeal_Timer;

                if (uiSelfRegrowth_Timer >= 0)
                    --uiSelfRegrowth_Timer;

                if (uiSelfRejuvenation_Timer >= 0)
                    --uiSelfRejuvenation_Timer;

                if (uiSelfHeal_Timer >= 0)
                    --uiSelfHeal_Timer;

                if (uiOthersHeal_Timer >= 0)
                    --uiOthersHeal_Timer;

                if (uiRez_Timer >= 0)
                    --uiRez_Timer;

                if (uiNoggenfogger_Timer >= 0)
                    --uiNoggenfogger_Timer;
            }

            void doCast(Unit *victim, uint32 spellId, bool triggered = false)
            {
                if (spellId == 0)
                    return;

                uiGc_Timer = 20;
                me->SetStandState(UNIT_STAND_STATE_STAND);
                DoCast(victim, spellId, triggered);
            }

            void doBearActions(const uint32 diff)
            {
                me->setPowerType(POWER_RAGE);

                if (isTimerReady(uiDemoralizingRoar_Timer) && opponent != NULL)
                {
                    uiDemoralizingRoar_Timer = 150;
                    doCast(opponent, SPELL_DEMORALIZING_ROAR, true);
                }

                if (isTimerReady(uiSwipe_Timer) && opponent != NULL)
                {
                    uiSwipe_Timer = 50;
                    doCast(opponent, SPELL_SWIPE, true);
                }
            }

            void doCatActions(/*Player* master, Creature *me,*/ const uint32 diff)
            {
                me->SetPower(POWER_ENERGY, 100);

                if (isTimerReady(uiClaw_Timer) && opponent != NULL)
                {
                    uiClaw_Timer = 70;
                    doCast(opponent, SPELL_CLAW, true);
                }

                if (isTimerReady(uiMangleCat_Timer) && opponent != NULL)
                {
                    uiMangleCat_Timer = 70;
                    doCast(opponent, SPELL_MANGLE_CAT, true);
                }

                if (isTimerReady(uiRake_Timer) && opponent != NULL)
                {
                    uiRake_Timer = 100;
                    doCast(opponent, SPELL_RAKE, true);
                }

                if (isTimerReady(uiShred_Timer) && opponent != NULL)
                {
                    uiShred_Timer = 120;
                    doCast(opponent, SPELL_SHRED, true);
                }

                if (isTimerReady(uiRip_Timer) && opponent != NULL)
                {
                    uiRip_Timer = 150;
                    doCast(opponent, SPELL_RIP, true);
                }
            }

            void doBalanceActions(const uint32 diff)
            {
                removeFeralForm();
                me->setPowerType (POWER_MANA);

                if (isTimerReady(uiMoonfire_Timer) && opponent != NULL)
                {
                    uiMoonfire_Timer = 150;
                    doCast(opponent, SPELL_MOONFIRE, true);
                }

                if (isTimerReady(uiStarfire_Timer) && opponent != NULL)
                {
                    uiStarfire_Timer = 200;
                    doCast(opponent, SPELL_STARFIRE, true);
                }

                if (isTimerReady(uiWrath_Timer) && opponent != NULL)
                {
                    uiWrath_Timer = 180;
                    doCast(opponent, SPELL_WRATH, true);
                }

                if (isTimerReady(uiFairieFire_Timer) && opponent != NULL)
                {
                    uiFairieFire_Timer = 200;
                    doCast(opponent, SPELL_FAIRIE_FIRE, true);
                }
            }

            bool CureTarget(Unit* target)
            {
                if (HasAuraIcon(target, 68) && !HasAuraName(target, SPELL_CURE_POISON))
                {
                    removeFeralForm();
                    doCast(target, SPELL_CURE_POISON);
                }

                return true;
            }

            void UpdateAI(const uint32 diff)
            {
                DoMeleeAttackIfReady();

                decrementTimers();

                if (IAmDead())
                    return;

                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;

                if (!me->isInCombat())
                {
                    if (!me->HasAura(SPELL_THORNS))
                    {
                        removeFeralForm();
                        doCast(me, SPELL_THORNS, true);
                    }
                }

                if (me->GetPower(POWER_MANA) < 400 && isTimerReady(uiPotion_Timer))
                {
                    doCast(me, SPELL_REJUVENATION_POTION, true);
                    uiPotion_Timer = 150;
                    uiOom_Timer = 0;
                }

                if (me->GetPower(POWER_MANA)/me->GetMaxPower(POWER_MANA) < 10)
                {
                    if (uiOom_Timer == 0)
                        uiOom_Timer = 1;
                }

                //Heal master
                if ((master->GetHealth() * 100 / master->GetMaxHealth() < 90) && isTimerReady(uiRejuvenation_Timer) && master->isAlive())
                {
                    removeFeralForm();
                    warstomp(diff);
                    doCast(master, SPELL_REJUVENATION, true);
                    uiRejuvenation_Timer = 300;
                    uiHeal_Timer = uiHeal_Timer + 30; //wait 3 seconds before casting a real heal
                    uiRegrowth_Timer = uiRegrowth_Timer + 20; //wait 2 seconds before casting a regrowth
                    return;
                }

                if ((master->GetHealth() * 100 / master->GetMaxHealth() < 90) && isTimerReady(uiRegrowth_Timer) && master->isAlive())
                {
                    removeFeralForm();
                    warstomp(diff);
                    doCast(master, SPELL_REGROWTH, true);
                    uiRegrowth_Timer = 200;
                    uiHeal_Timer = uiHeal_Timer + 20; //wait 2 seconds before casting a real heal
                    return;
                }

                if ((master->GetHealth() * 100 / master->GetMaxHealth() < 75) && isTimerReady(uiHeal_Timer) && master->isAlive())
                {
                    removeFeralForm();
                    warstomp(diff);
                    doCast(master, SPELL_HEALING_TOUCH, false);
                    uiHeal_Timer = 100;
                    return;
                }

                //Heal myself
                if (me->GetHealth() * 100 / me->GetMaxHealth() < 80 && !me->HasAura(SPELL_REGROWTH, 1) && isTimerReady(uiSelfRegrowth_Timer))
                {
                    removeFeralForm();
                    warstomp(diff);
                    doCast(me, SPELL_REGROWTH, false);

                    uiSelfRegrowth_Timer = 120;
                    return;
                }

                if (me->GetHealth() * 100 / me->GetMaxHealth() < 80 && !me->HasAura(SPELL_REJUVENATION, 0) && isTimerReady(uiSelfRejuvenation_Timer))
                {
                    removeFeralForm();
                    warstomp(diff);
                    doCast(me, SPELL_REJUVENATION, false);

                    uiSelfRejuvenation_Timer = 120;
                    return;
                }

                if ((me->GetHealth() * 100 / me->GetMaxHealth() < 75) && isTimerReady(uiSelfHeal_Timer))
                {
                    removeFeralForm();
                    warstomp(diff);

                    doCast(me, SPELL_HEALING_TOUCH, false);
                    uiSelfHeal_Timer = 100;
                    return;
                }

                //Heal others
                //check group members, this doesn't check bots/pets.  They will be done later.  Preference
                //goes to real players first.
                Group::MemberSlotList const &a =((Player*)master)->GetGroup()->GetMemberSlots();
                for (Group::member_citerator itr = a.begin(); itr != a.end(); itr++)
                {
                    Player *tPlayer = ((Player *)master)->GetObjPlayer(itr->guid);

                    if (tPlayer == NULL)
                        continue;

                    //healing others
                    if (tPlayer->isAlive() && isTimerReady(uiOthersHeal_Timer) && tPlayer->GetHealth()*100 / tPlayer->GetMaxHealth() < 75)
                    {
                        doCast(tPlayer, SPELL_HEALING_TOUCH, false);
                        uiOthersHeal_Timer = 250;
                    }

                    //rezzes
                    if (tPlayer->isDead() && me->getLevel() >= 20 && me->GetDistance(tPlayer) < 40 && (isTimerReady(uiRez_Timer)))
                    {
                        char *str = (char *)malloc(32);
                        sprintf(str, "Rezzing %s", tPlayer->GetName());
                        me->MonsterSay(str, LANG_UNIVERSAL, NULL);
                        free(str);
                        doCast(tPlayer, SPELL_REBIRTH, false);
                        uiRez_Timer = 1600;
                    }

                    //buff group
                    if (tPlayer->isAlive())
                    {
                        if (!HasAuraName(tPlayer, GetSpellName(SPELL_MARK_OF_THE_WILD)) && !HasAuraName(tPlayer, "Gift of the Wild") && isTimerReady(uiGc_Timer))
                        {
                            removeFeralForm();
                            doCast(tPlayer, SPELL_MARK_OF_THE_WILD);
                        }

                        if (!HasAuraName(tPlayer, SPELL_THORNS) && isTimerReady(uiGc_Timer))
                        {
                            removeFeralForm();
                            doCast(tPlayer, SPELL_THORNS);
                        }
                    }
                }

                if (isTimerReady(uiNoggenfogger_Timer))
                {
                    uint64 m_rand = urand(1, 2);

                    switch(m_rand)
                    {
                        case 1:
                            doCast(me, SPELL_NOGGENFOGGER_SKELETON, true);
                            break;
                        case 2:
                            // Don't change forms b/c it crashes in GetModelForForm().  It checks
                            // PLAYER_BYTES and since its an npc it does not have this value.
                            //doCast(me, SPELL_NOGGENFOGGER_SMALL, true);
                            break;
                    }

                    uiNoggenfogger_Timer = 6000; //10 minutes
                }

                //The rest is combat stuff, so if not in combat just return
                opponent = SelectTarget(SELECT_TARGET_TOPAGGRO, 0);

                if (!opponent && !me->getVictim())
                {
                    CureGroup(master);
                    ResetOrGetNextTarget();
                    return;
                }

                //default value
                float val2 = me->GetStat(STAT_STRENGTH)*2.0f;

                //only go Feral if we are "small" from the noggenfogger spell
                if (me->HasAura(SPELL_NOGGENFOGGER_SMALL))
                {
                    //if the target is attacking us, we want to go bear
                    if (opponent && opponent->getVictim() && opponent->getVictim()->GetGUID()  ==  me->GetGUID())
                    {
                        //if we don't have bear yet
                        if (!me->HasAura(SPELL_BEAR_FORM))
                        {
                            me->RemoveAurasDueToSpell(SPELL_CAT_FORM); //remove cat
                            me->RemoveAurasDueToSpell(SPELL_CAT_FORM_MOD);
                            doCast(me, SPELL_BEAR_FORM, true);
                            doCast(me, SPELL_BEAR_FORM_MOD, true);
                            master->SetBotMustWaitForSpell1(3000);
                            me->setPowerType(POWER_RAGE);
                            me->SetMaxPower(POWER_RAGE, 1000);
                            me->SetPower(POWER_RAGE, 1000);
                            val2 = me->getLevel() * 3.0f + me->GetStat(STAT_STRENGTH) * 2.0f;

                            //update attack power based on form
                            val2 = val2 + (val2 * (me->getLevel()/50));
                            me->SetModifierValue(UNIT_MOD_ATTACK_POWER, BASE_VALUE, val2);
                            me->UpdateDamagePhysical(BASE_ATTACK);
                        }

                        doBearActions(diff);
                    }
                    else
                    {
                        //if we don't have cat yet
                        if (!me->HasAura(SPELL_CAT_FORM))
                        {
                            me->RemoveAurasDueToSpell(SPELL_BEAR_FORM); //remove bear
                            me->RemoveAurasDueToSpell(SPELL_BEAR_FORM_MOD);
                            doCast(me, SPELL_CAT_FORM, true);
                            doCast(me, SPELL_CAT_FORM_MOD, true);
                            master->SetBotMustWaitForSpell1(3000);
                            me->setPowerType(POWER_ENERGY);
                            me->SetMaxPower(POWER_ENERGY, 1000);
                            me->SetPower(POWER_ENERGY, 1000);
                            me->SetSpeed(MOVE_RUN, me->GetSpeed(MOVE_RUN) - 0.1f, true);
                            val2 = me->getLevel() * 5.0f + me->GetStat(STAT_STRENGTH) * 2.0f + me->GetStat(STAT_AGILITY) - 20.0f;

                            //update attack power based on form
                            val2 = val2 + (val2 * (me->getLevel() / 50));
                            me->SetModifierValue(UNIT_MOD_ATTACK_POWER, BASE_VALUE, val2);
                            me->UpdateDamagePhysical(BASE_ATTACK);
                        }

                        doCatActions(diff);
                    }
                }
                else
                {
                    val2 = me->GetStat(STAT_STRENGTH) * 2.0f;
                    val2 = val2 + (val2 * (me->getLevel() / 50));
                    me->SetModifierValue(UNIT_MOD_ATTACK_POWER, BASE_VALUE, val2);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    doBalanceActions(diff);
                }

                //now try to heal bots and pets.  DoSelectLowestHpFriendly will get
                //everyone in group including bots and pets.  Unfortunately it can
                //not be triggered for % of lost HP, so we just set it to -1000.
                //This means low level players wont be healed because they wont have
                //enough HP.
                Unit* target = DoSelectLowestHpFriendly(40, 1000);

                if (target && isTimerReady(uiOthersHeal_Timer))
                {
                    doCast(target, SPELL_HEALING_TOUCH, false);
                    uiOthersHeal_Timer = 50;
                }
                else
                {
                    target = DoSelectLowestHpFriendly(40, 500);  //now try someone with less HP lost

                    if (target && isTimerReady(uiOthersHeal_Timer))
                    {
                        if (!target->HasAura(SPELL_REGROWTH, 1))
                        {
                            doCast(target, SPELL_REGROWTH, false);
                            uiOthersHeal_Timer = 100;
                        }
                    }
                }

                ScriptedAI::UpdateAI(diff);
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
                {
                    player->SetBotCommandState(COMMAND_FOLLOW);
                    ((bot_druid_ai*)me->AI())->removeFeralForm((Player*) me->GetCharmer());
                    ((bot_druid_ai*)me->AI())->doCast(player, SPELL_THORNS, true );
                    ((bot_druid_ai*)me->AI())->doCast(player, SPELL_MARK_OF_THE_WILD, false );
                }
            }
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new bot_druid_ai(pCreature);
        }
};

void AddSC_druid_bot()
{
    new druid_bot();
}
