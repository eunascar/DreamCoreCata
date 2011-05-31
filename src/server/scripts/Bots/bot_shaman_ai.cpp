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

#define SPELL_ANCESTRAL_SPIRIT        SPELL_ANCESTRAL_SPIRIT_A[SPELL_LEVEL]
#define SPELL_CHAIN_HEAL              SPELL_CHAIN_HEAL_A[SPELL_LEVEL]
#define SPELL_EARTH_SHOCK             SPELL_EARTH_SHOCK_A[SPELL_LEVEL]
#define SPELL_FLAME_SHOCK             SPELL_FLAME_SHOCK_A[SPELL_LEVEL]
#define SPELL_HEALING_STREAM_AURA     SPELL_HEALING_STREAM_AURA_A[SPELL_LEVEL]
#define SPELL_HEALING_STREAM_TOTEM    SPELL_HEALING_STREAM_TOTEM_A[SPELL_LEVEL]
#define SPELL_LESSER_HEALING          SPELL_LESSER_HEALING_A[SPELL_LEVEL]
#define SPELL_LIGHTNING_BOLT          SPELL_LIGHTNING_BOLT_A[SPELL_LEVEL]
#define SPELL_LIGHTNING_SHIELD        SPELL_LIGHTNING_SHIELD_A[SPELL_LEVEL]
#define SPELL_MANA_SPRING_AURA        SPELL_MANA_SPRING_AURA_A[SPELL_LEVEL]
#define SPELL_MANA_SPRING_TOTEM       SPELL_MANA_SPRING_TOTEM_A[SPELL_LEVEL]
#define SPELL_SEARING_TOTEM           SPELL_SEARING_TOTEM_A[SPELL_LEVEL]
#define SPELL_STONE_SKIN_AURA         SPELL_STONE_SKIN_AURA_A[SPELL_LEVEL]
#define SPELL_STONE_SKIN_TOTEM        SPELL_STONE_SKIN_TOTEM_A[SPELL_LEVEL]
#define SPELL_WINDFURY_TOTEM          SPELL_WINDFURY_TOTEM_A[SPELL_LEVEL]

uint32 SPELL_ANCESTRAL_SPIRIT_A     [] = {0, 2008, 20609, 20610, 20776, 20776, 20777, 25590, 49277, 49277 };
uint32 SPELL_CHAIN_HEAL_A           [] = { 0, 0, 0, 0, 1064, 10623, 25422, 25423, 55459, 55459 };
uint32 SPELL_EARTH_SHOCK_A          [] = { 8042, 8045, 8046, 10412, 10413, 10414, 10414, 25454, 49230, 49230 };
uint32 SPELL_FLAME_SHOCK_A          [] = { 0, 8050, 8052, 8053, 10447, 10448, 29228, 25457, 49232, 49232 };
uint32 SPELL_HEALING_STREAM_AURA_A  [] = { 0, 0, 5672, 6371, 6372, 10460, 10461, 25566, 58765, 58765 };
uint32 SPELL_HEALING_STREAM_TOTEM_A [] = { 0, 0, 5394, 6375, 6377, 10462, 10463, 25567, 58757, 58757 };
uint32 SPELL_LESSER_HEALING_A       [] = { 0, 0, 8004, 8010, 10466, 10467, 10468, 25420, 49275, 49275 };
uint32 SPELL_LIGHTNING_BOLT_A       [] = { 403, 548, 915, 6041, 10392, 15207, 25448, 45296, 45296 };
uint32 SPELL_LIGHTNING_SHIELD_A     [] = {324, 325, 905, 945, 8134, 10431, 25469, 25472, 49280, 49280 };
uint32 SPELL_MANA_SPRING_AURA_A     [] = { 0, 0, 5677, 10491, 10493, 10494, 25569, 25569, 58775, 58775 };
uint32 SPELL_MANA_SPRING_TOTEM_A    [] = { 0, 0, 5675, 10495, 10496, 10497, 25570, 25570, 58771, 58771 };
uint32 SPELL_SEARING_TOTEM_A        [] = { 0, 3599, 6363, 6364, 6365, 10437, 10438, 25533, 58699, 58699 };
uint32 SPELL_STONE_SKIN_AURA_A      [] = { 8072, 8156, 8156, 10403, 10404, 10405, 25506, 58752, 58752, 58752 };
uint32 SPELL_STONE_SKIN_TOTEM_A     [] = { 8071, 8154, 8155, 10406, 10407, 10408, 25508, 25509, 25509, 25509 };
uint32 SPELL_WINDFURY_TOTEM_A       [] = { 0, 0, 0, 0, 8512, 8512, 8512, 8512, 8512, 8512 };

class shaman_bot : public CreatureScript
{
    public:
        shaman_bot()
            : CreatureScript("shaman_bot")
        {
        }

        struct shaman_botAI : public bot_ai
        {
            shaman_botAI(Creature* c) : bot_ai(c)
            {
                Reset();
            }

            uint32 uiHeal_Timer;
            uint32 uiLesserHealing_Timer;
            uint32 uiSelfLesserHealing_Timer;
            uint32 uiFlameShock_Timer;
            uint32 uiEarthShock_Timer;
            uint32 uiLightningBolt_Timer;
            uint32 uiOthersHeal_Timer;
            uint32 uiOom_Timer;
            uint32 uiPotion_Timer;
            uint32 uiRez_Timer;
            uint32 uiEarthTotem_Timer;
            uint32 uiWaterTotem_Timer;
            uint32 uiFireTotem_Timer;
            uint32 uiWindTotem_Timer;

            Unit* mobsTarget;
            Unit* opponent;

            void Reset()
            {
                uiGc_Timer = 0;
                uiHeal_Timer = 0;
                uiLesserHealing_Timer = 0;
                uiSelfLesserHealing_Timer = 0;
                uiFlameShock_Timer = 20;
                uiLightningBolt_Timer = 60;
                uiEarthShock_Timer = 150;
                uiOthersHeal_Timer = 0;
                uiPotion_Timer = 0;
                uiOom_Timer = 0;
                uiEarthTotem_Timer = 0;
                uiFireTotem_Timer = 0;
                uiWaterTotem_Timer = 0;
                uiWindTotem_Timer = 0;
                uiRez_Timer = 0;

                opponent = NULL;
            }

            bool isTimerReady(int32 timer)
            {
                if (timer <= 0 && uiGc_Timer <= 0) 
                    return true;
                else
                    return false;
            }

            void doCast(Unit* victim, uint32 spellId, bool triggered = false)
            {
                if (spellId == 0)
                    return;

                me->SetStandState(UNIT_STAND_STATE_STAND);
                uiGc_Timer = 40;
                DoCast(victim, spellId, triggered);
            }

            void decrementTimers()
            {
                if (uiGc_Timer > 0)
                    --uiGc_Timer;

                if (uiHeal_Timer > 0)
                    --uiHeal_Timer;

                if (uiOthersHeal_Timer > 0)
                    --uiOthersHeal_Timer;

                if (uiFlameShock_Timer > 0)
                    --uiFlameShock_Timer;

                if (uiEarthShock_Timer > 0)
                    --uiEarthShock_Timer;

                if (uiLightningBolt_Timer > 0)
                    --uiLightningBolt_Timer;

                if (uiRez_Timer > 0)
                    --uiRez_Timer;

                if (uiPotion_Timer > 0)
                    --uiPotion_Timer;

                if (uiEarthTotem_Timer > 0)
                    --uiEarthTotem_Timer;

                if (uiFireTotem_Timer > 0)
                    --uiFireTotem_Timer;

                if (uiWaterTotem_Timer > 0)
                    --uiWaterTotem_Timer;

                if (uiWindTotem_Timer > 0)
                    --uiWindTotem_Timer;
            }

            void KilledUnit(Unit* /*who*/)
            {
                ((Player*)master)->SetBotCommandState(COMMAND_FOLLOW);
            }

            void EnterEvadeMode()
            {
                uiOom_Timer = 0;
            }

            void UpdateAI(const uint32 diff)
            {
                DoMeleeAttackIfReady();

                decrementTimers();

                if (IAmDead())
                    return;

                if (me->GetPower(POWER_MANA) < 400 && isTimerReady(uiPotion_Timer))
                {
                    doCast(me, SPELL_MANA_POTION);
                    uiPotion_Timer = 150;
                }

                if (me->GetPower(POWER_MANA)/me->GetMaxPower(POWER_MANA) < 10)
                {
                    if (uiOom_Timer == 0)
                        uiOom_Timer = 1;
                }

                BuffAndHealGroup(master);

                // Heal myself
                HealTarget (me, me->GetHealth() * 100 / me->GetMaxHealth());

                //the rest are combat so return if not fighting
                opponent = SelectTarget(SELECT_TARGET_TOPAGGRO, 0);

                if (!opponent && !me->getVictim())
                {
                    DoNonCombatActions();
                    ResetOrGetNextTarget();
                    return;
                }

                //Cast totems.
                if (me->isInCombat() && isTimerReady(uiEarthTotem_Timer) && !master->HasAura(SPELL_STONE_SKIN_AURA, 0))
                {
                    doCast(me, SPELL_STONE_SKIN_TOTEM);
                    GiveManaBack();
                    uiEarthTotem_Timer = 90;
                    return;
                }

                if (me->isInCombat() && isTimerReady(uiFireTotem_Timer))
                {
                    doCast(me, SPELL_SEARING_TOTEM);
                    GiveManaBack();
                    uiFireTotem_Timer = 180;
                    return;
                }

                if (me->isInCombat() && isTimerReady(uiWindTotem_Timer))
                {
                    doCast(me, SPELL_WINDFURY_TOTEM);
                    GiveManaBack();
                    uiWindTotem_Timer = 180;
                    return;
                }

                if (me->isInCombat())
                {
                    switch(master->getClass())
                    {
                        case CLASS_WARRIOR:
                        case CLASS_DEATH_KNIGHT:
                        case CLASS_ROGUE:
                            if (isTimerReady(uiWaterTotem_Timer) && !master->HasAura(SPELL_HEALING_STREAM_AURA))
                            {
                                doCast(me, SPELL_HEALING_STREAM_TOTEM);
                                uiWaterTotem_Timer = 90;
                                GiveManaBack();
                                return;
                            }
                            break;
                        default: //everyone else gets a mana totem
                            if (isTimerReady (uiWaterTotem_Timer) && !master->HasAura(SPELL_MANA_SPRING_AURA, 0))
                            {
                                doCast(me, SPELL_MANA_SPRING_TOTEM);
                                uiWaterTotem_Timer = 90;
                                GiveManaBack();
                                return;
                            }
                    }
                }

                if (isTimerReady(uiFlameShock_Timer))
                {
                    doCast(opponent, SPELL_FLAME_SHOCK);
                    uiFlameShock_Timer = 120;
                    return;
                }

                if (isTimerReady(uiLightningBolt_Timer))
                {
                    doCast(opponent, SPELL_LIGHTNING_BOLT);
                    uiLightningBolt_Timer = 180;
                    return;
                }

                if (isTimerReady(uiEarthShock_Timer))
                {
                    doCast(opponent, SPELL_EARTH_SHOCK);
                    uiEarthShock_Timer = 250;
                    return;
                }

                //now try to heal bots and pets.  DoSelectLowestHpFriendly will get
                //everyone in group including bots and pets.  Unfortunately it can
                //not be triggered for % of lost HP, so we just set it to -1000.
                //This means low level players wont be healed because they wont have
                //enough HP.
                Unit* target = DoSelectLowestHpFriendly(40, 1000);

                if (target)
                {
                    if (CanCast(target, GetSpellStore()->LookupEntry (SPELL_CHAIN_HEAL)))
                    {
                        doCast(target, SPELL_CHAIN_HEAL, false);
                        uiOthersHeal_Timer = 50;
                    }
                }
                else
                {
                    target = DoSelectLowestHpFriendly(40, 500); //now try someone with less HP lost

                    if (target)
                    {
                        if (CanCast(target, GetSpellStore()->LookupEntry (SPELL_CHAIN_HEAL)))
                        {
                            doCast(target, SPELL_CHAIN_HEAL, false);
                            uiOthersHeal_Timer = 100;
                        }
                    }
                }

                ScriptedAI::UpdateAI(diff);
            }

            void DoNonCombatActions()
            {
                Feast();

                if (isTimerReady(uiGc_Timer) && !me->HasAura(SPELL_LIGHTNING_SHIELD, 0))
                doCast(me, SPELL_LIGHTNING_SHIELD);

                if (master->GetGroup())
                {
                    RezGroup(SPELL_ANCESTRAL_SPIRIT, master);
                    BuffAndHealGroup(master);
                }

                /* TESTING */
                Group::MemberSlotList const &a =((Player*)master)->GetGroup()->GetMemberSlots();

                for (Group::member_citerator itr = a.begin(); itr != a.end(); itr++)
                {
                    Player* tPlayer = ((Player *)master)->GetObjPlayer(itr->guid);
            
                    if (tPlayer == NULL)
                        continue;
            
                    //healing others
                    if (tPlayer->isAlive() && isTimerReady(uiOthersHeal_Timer) && tPlayer->GetGUID() != master->GetGUID() && tPlayer->GetHealth() * 100 / tPlayer->GetMaxHealth() < 75 && CanCast(tPlayer, GetSpellStore()->LookupEntry(SPELL_CHAIN_HEAL)))
                    {
                        doCast(tPlayer, SPELL_CHAIN_HEAL, false);
                        uiOthersHeal_Timer = 100;
                    }

                    //rezzes
                    if (tPlayer->isDead() && !me->isInCombat() && me->GetDistance(tPlayer) < 40 && isTimerReady(uiRez_Timer))
                    {
                        char* str = (char *)malloc(32);
                        sprintf(str, "Resucitando a %s", tPlayer->GetName());
                        me->MonsterSay(str, LANG_UNIVERSAL, NULL);
                        free(str);
                        doCast(tPlayer, SPELL_ANCESTRAL_SPIRIT, false);
                        uiRez_Timer = 160;
                    }
                }

                /* TESTING */
                if ((master->GetHealth() * 100 / master->GetMaxHealth() < 90) && uiLesserHealing_Timer <= 0)
                {
                    doCast(master, SPELL_LESSER_HEALING);
                    uiLesserHealing_Timer = 90;
                    uiHeal_Timer = uiHeal_Timer + 5; //wait 5 seconds before casting a real heal
                    return;
                }
                else if (uiLesserHealing_Timer >= 0)
                    --uiLesserHealing_Timer;

                if ((master->GetHealth() * 100 / master->GetMaxHealth() < 75) && isTimerReady(uiHeal_Timer))
                {
                    doCast(master, SPELL_CHAIN_HEAL);
                    uiHeal_Timer = 10;
                }

                if (me->GetHealth() * 100 / me->GetMaxHealth() < 90)
                {
                    if (uiSelfLesserHealing_Timer <= 0)
                    {
                        doCast(me, SPELL_LESSER_HEALING);
                        uiSelfLesserHealing_Timer = 90;
                        return;
                    }
                    else if (uiSelfLesserHealing_Timer >= 0)
                    --uiSelfLesserHealing_Timer;
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

                if (hp < 90 && uiLesserHealing_Timer <= 0)
                {
                    doCast(target, SPELL_LESSER_HEALING);
                    uiLesserHealing_Timer = 90;
                    uiHeal_Timer = uiHeal_Timer + 5; //wait 5 seconds before casting a real heal
                    return true;
                }
                else if (uiLesserHealing_Timer >= 0)
                    --uiLesserHealing_Timer;

                if (hp < 75 && isTimerReady(uiHeal_Timer))
                {
                    doCast(target, SPELL_CHAIN_HEAL);
                    uiHeal_Timer = 10;
                }

                return true;
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

                if (emote == TEXT_EMOTE_BOW)
                    doCast(me, SPELL_MANA_SPRING_TOTEM);
            }
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new shaman_botAI(pCreature);
        }
};

void AddSC_shaman_bot()
{
    new shaman_bot();
}