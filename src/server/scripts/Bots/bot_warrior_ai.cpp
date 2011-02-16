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
    SPELL_DEFENSIVE_STANCE         = 71,
    SPELL_TAUNT                    = 355,
    SPELL_COMMANDINGSHOUT          = 469,
    SPELL_DISARM                   = 676,
    SPELL_CHALLENGING_SHOUT        = 1161,
    SPELL_BATTLESTANCE             = 7165,
    SPELL_BERSERKER_STANCE         = 7366,
    SPELL_PUMMEL                   = 15615,
    SPELL_BERSERKER_RAGE           = 18499,
    SPELL_INTERCEPT                = 27577,
    SPELL_BLOODRAGE                = 29131,
    SPELL_DEMORALIZING_SHOUT       = 29584,
    SPELL_TAUNT_VISUAL             = 34105,
    SPELL_CHARGE                   = 37511,
    SPELL_EXECUTE                  = 38959,
    SPELL_PVP_TRINKET              = 42292,
};

#define SPELL_BATTLESHOUT      SPELL_BATTLESHOUT_A[SPELL_LEVEL]
#define SPELL_HAMSTRING        SPELL_HAMSTRING_A[SPELL_LEVEL]
#define SPELL_MORTAL_STRIKE    SPELL_MORTAL_STRIKE_A[SPELL_LEVEL]
#define SPELL_REND             SPELL_REND_A[SPELL_LEVEL]
#define SPELL_SUNDER           SPELL_SUNDER_A[SPELL_LEVEL]
#define SPELL_WHIRLWIND        SPELL_WHIRLDWIND_A[SPELL_LEVEL]

uint32 SPELL_BATTLESHOUT_A   [] = { 9128, 9128, 9128, 27578, 27578, 26043, 26043, 26043, 26043 };
uint32 SPELL_CHARGE_A        [] = { 100, 100, 6178, 11578, 11578, 11578, 11578, 11578, 11578 };
uint32 SPELL_EXECUTE_A       [] = { 1715, 1715, 1715, 7372, 7372, 7373, 7373, 25212, 25212 };
uint32 SPELL_HAMSTRING_A     [] = { 1715, 1715, 1715, 7372, 7372, 7373, 7373, 25212, 25212 };
uint32 SPELL_MORTAL_STRIKE_A [] = { 0, 0, 0, 0, 12294, 21552, 21553, 25248, 47485 };
uint32 SPELL_PUMMEL_A        [] = { 0, 0, 0, 0, 6552, 6552, 6552, 6552, 6552 };
uint32 SPELL_REND_A          [] = { 772, 6546, 6547, 6548, 11572, 11573, 11574, 25208, 46845 };
uint32 SPELL_SUNDER_A        [] = { 0, 7386, 7405, 8380, 11596, 11597, 25225, 47467, 47467 };
uint32 SPELL_WHIRLDWIND_A    [] = { 0, 0, 0, 0, 1680, 1680, 1680, 1680, 1680 };

bool castDemoralizingShout;
bool castBattleStance;
bool castDefensiveStance;
bool castBerserkerStance;

class warrior_bot : public CreatureScript
{
    public:
        warrior_bot()
            : CreatureScript("warrior_bot")
        {
        }

        struct warrior_botAI : public bot_ai
        {
            warrior_botAI(Creature *c) : bot_ai(c)
            {
                Reset();
            }

            uint32 uiCharge_Timer;
            uint32 uiMortalStrike_Timer;
            uint32 uiChallengingShout_Timer;
            uint32 uiBattleShout_Timer;
            uint32 uiIntercept_Timer;
            uint32 uiPummel_Timer;
            uint32 uiWhirlwind_Timer;
            uint32 uiBloodrage_Timer;
            uint32 uiDisarm_Timer;
            uint32 uiPvpTrinket_Timer;
            uint32 uiRage;
            uint32 uiGCD;

            void Reset()
            {
                uiCharge_Timer               = 0;
                uiMortalStrike_Timer         = 0;
                uiChallengingShout_Timer     = 0;
                uiBattleShout_Timer          = 0;
                uiIntercept_Timer            = 0;
                uiPummel_Timer               = 0;
                uiWhirlwind_Timer            = 0;
                uiBloodrage_Timer            = 0;
                uiDisarm_Timer               = 0;
                uiPvpTrinket_Timer           = 0;
                uiPotion_Timer               = 0;
                uiRage                       = 0;
                uiGCD                        = 0;
                castDemoralizingShout        = false;
                castBattleStance             = true;
                castDefensiveStance          = false;
                castBerserkerStance          = false;

                uiNoggenfogger_Timer         = 0;
                me->setPowerType(POWER_RAGE);
            }

            void Attack(const uint32 diff)
            {
                Unit *opponent = me->getVictim();

                if (!opponent)
                    return;

                if ((me->GetDistance(opponent) > 13) && (me->GetDistance(opponent) < 25) && !me->HasAuraType(SPELL_AURA_MOD_ROOT) && !me->HasAuraType(SPELL_AURA_MOD_STUN) && !me->HasAuraType(SPELL_AURA_MOD_CONFUSE) && (uiIntercept_Timer < diff) && (uiRage > 10) && (uiGCD < diff))
                {
                    if (castBerserkerStance  ==  true)
                    {
                        doCast(opponent, SPELL_INTERCEPT, true);
                        uiIntercept_Timer = 15000;
                    } else stanceChange(3);
                }

                if (uiDisarm_Timer < diff && (opponent->GetHealth()*100/opponent->GetMaxHealth()) < 80 && uiRage > 15 && !HasAuraName(opponent, GetSpellName(SPELL_DISARM)) && uiGCD < diff)
                {
                    if (opponent->getClass()  ==  CLASS_ROGUE || opponent->getClass()  ==  CLASS_WARRIOR || opponent->getClass()  ==  CLASS_SHAMAN || opponent->getClass()  ==  CLASS_PALADIN)
                    {
                        if (castDefensiveStance  ==  true)
                        {
                            doCast(opponent, SPELL_DISARM, true);
                            uiDisarm_Timer = 60000;
                        } else stanceChange(2);
                    }
                }

                if ((opponent->GetHealth()*100/opponent->GetMaxHealth()) < 15 && uiRage > 15 && uiGCD < diff)
                {
                    if (castBattleStance  ==  true || castBerserkerStance  ==  true)
                    {
                        int damage = (uiRage * 4 + (me->getLevel() * 10)) / 2;
                        me->CastCustomSpell(opponent, SPELL_EXECUTE, &damage, NULL, NULL, false, NULL, NULL);
                        uiGCD = 20;
                    } else stanceChange(5);
                }

                if (uiMortalStrike_Timer < diff && uiRage > 15 && uiGCD < diff)
                {
                    doCast(opponent, SPELL_MORTAL_STRIKE, true);
                    uiMortalStrike_Timer = 7000;
                }

                if (castDemoralizingShout  ==  true && !opponent->HasAura(SPELL_DEMORALIZING_SHOUT) && uiRage < 10 && uiGCD < diff)
                {
                    doCast(opponent, SPELL_DEMORALIZING_SHOUT, true);
                    castDemoralizingShout = false;
                }

                if (opponent->IsNonMeleeSpellCasted(true) && uiPummel_Timer < diff && uiRage > 10 && uiGCD < diff)
                {
                    if (castBerserkerStance  ==  true)
                    {
                        doCast(opponent, SPELL_PUMMEL, true);
                        uiPummel_Timer = 10000;
                    } else stanceChange(3);
                }

                if (uiWhirlwind_Timer < diff && uiRage > 25 && uiGCD < diff)
                {
                    if (castBerserkerStance  ==  true)
                    {
                        doCast(opponent, SPELL_WHIRLWIND, true);
                        uiWhirlwind_Timer = 10000;
                    } else stanceChange(3);
                }

                if (!opponent->HasAura(SPELL_REND) && uiRage > 10 && uiGCD < diff)
                {
                    if (castBattleStance  ==  true || castDefensiveStance  ==  true)
                        doCast(opponent, SPELL_REND, true);
                    else
                        stanceChange(1);
                }

                if (!opponent->HasAura(SPELL_HAMSTRING, 1) && uiRage > 10 && uiGCD < diff)
                {
                    if (castBattleStance == true || castBerserkerStance == true)
                        doCast(opponent, SPELL_HAMSTRING, true);
				    else
                        stanceChange(5);
                }
            }

            void AttackStart(Unit* who)
            {
                EnterCombat(who);
                ScriptedAI::AttackStart(who);
            }

            void BreakCC(const uint32 diff)
            {
                if (uiPvpTrinket_Timer < diff && uiGCD < diff)
                {
                    if (me->HasAuraType(SPELL_AURA_MOD_ROOT) || me->HasAuraType(SPELL_AURA_MOD_CONFUSE) || me->HasAura(8983) || me->HasAura(27006) || me->HasAura(33786) || me->HasAura(22570, 1) || me->HasAura(10308) || me->HasAura(30414, 1) || me->HasAura(6215) || me->HasAura(17928) || me->HasAura(10890) || me->HasAura(14902) || me->HasAura(8643) || me->HasAura(38764, 2) || me->HasAura(12809))
                    {
                        doCast(me, SPELL_PVP_TRINKET);
                        uiPvpTrinket_Timer = 120000;
                    }

                    if (me->HasAura(11297) && me->GetDistance(me->getVictim()) < 10)
                    {
                        doCast(me, SPELL_PVP_TRINKET);
                        uiPvpTrinket_Timer = 120000;
                        castDemoralizingShout = true;
                    }
                }
            }

            void doCast(Unit *victim, uint32 spellId, bool triggered = false)
            {
                if (spellId  ==  0)
                    return;

                uiGCD = 2000;
                DoCast(victim, spellId, triggered);
            } //end doCast

            void EnterCombat(Unit* who)
            {
                Unit *opponent = who;

                if (!opponent)
                    return;

                if ((me->GetDistance(opponent) > 15) && (me->GetDistance(opponent) < 25) && uiCharge_Timer <= 0)
                {
                    doCast(opponent, SPELL_CHARGE);
                    uiCharge_Timer = 100;
                }

                if (opponent->getClass()  ==  CLASS_ROGUE || opponent->getClass()  ==  CLASS_WARRIOR || opponent->getClass()  ==  CLASS_SHAMAN || opponent->getClass()  ==  CLASS_DRUID || opponent->getClass()  ==  CLASS_PALADIN || opponent->getClass()  ==  CLASS_HUNTER)
                    castDemoralizingShout = true;
            } //end EnterCombat

            bool isTimerReady(int32 timer, uint32 diff)
            {
                if (timer <= 0 && uiGCD < diff)
                    return true;
                else
                    return false;
            }

            void JustDied(Unit* /*who*/)
            {
                DoPlaySoundToSet(me, 8860);
                master->SetBotCommandState(COMMAND_FOLLOW);
		    }

            void KilledUnit(Unit* /*who*/)
            {
                master->SetBotCommandState(COMMAND_FOLLOW);
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
            }

            void ReduceCD(const uint32 diff)
            {
                if (!(uiMortalStrike_Timer < diff))
                    uiMortalStrike_Timer -= diff;

                if (!(uiIntercept_Timer < diff))
                    uiIntercept_Timer -= diff;

                if (!(uiPummel_Timer < diff))
                    uiPummel_Timer -= diff;

                if (!(uiWhirlwind_Timer < diff))
                    uiWhirlwind_Timer -= diff;

                if (!(uiBloodrage_Timer < diff))
                    uiBloodrage_Timer -= diff;

                if (!(uiDisarm_Timer < diff))
                    uiDisarm_Timer -= diff;

                if (!(uiPotion_Timer < diff))
                    uiPotion_Timer -= diff;

                if (!(uiFirstAid_Timer < diff))
                    uiFirstAid_Timer -= diff;

                if (!(uiBattleShout_Timer < diff))
                    uiBattleShout_Timer -= diff;

                if (!(uiGCD < diff))
                    uiGCD -= diff;
                else
                    uiGCD = 0;

                if (uiCharge_Timer > 0)
                    --uiCharge_Timer;

                if (uiNoggenfogger_Timer >= 0)
                    --uiNoggenfogger_Timer;
            }

            void stanceChange(uint32 stance)
            {
                if (stance  ==  5)
                {
                    switch(rand()%2)
                    {
                        case 0:
                            stance = 1;
                            break;
                        case 1:
                            stance = 3;
                            break;
                    }
                }

                castBattleStance = false;
                castDefensiveStance = false;
                castBerserkerStance = false;

                switch(stance)
                {
                    case 1:
                        doCast(me, SPELL_BATTLESTANCE);
                        castBattleStance = true;
                        break;
                    case 2:
                        doCast(me, SPELL_DEFENSIVE_STANCE);
                        castDefensiveStance = true;
                        break;
                    case 3:
                        doCast(me, SPELL_BERSERKER_STANCE);
                        castBerserkerStance = true;
                        break;
                }
            }

            void UpdateAI(const uint32 diff)
            {
                DoMeleeAttackIfReady();

                ReduceCD(diff);

                if (IAmDead())
                    return;

                //Use Noggenfogger potion if a tauren
                if (master->GetBotRace()  ==  RACE_TAUREN && isTimerReady(uiNoggenfogger_Timer, diff))
                {
                    uint64 m_rand = urand(1, 2);

                    switch(m_rand)
                    {
                        case 1:
                            doCast(me, SPELL_NOGGENFOGGER_SKELETON, true);
                            break;
                        case 2:
                            doCast(me, SPELL_NOGGENFOGGER_SMALL, true);
                            break;
                    }

                    uiNoggenfogger_Timer = 6000; //10 minutes
                }

                Unit *opponent = SelectUnit(SELECT_TARGET_TOPAGGRO, 0);

                if (!opponent && !me->getVictim())
                {
                    ResetOrGetNextTarget();

                    if (uiRage > 0)
                        --uiRage;

                    return;
                }

                uiRage = me->GetPower(POWER_RAGE);

                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);

                if (me->GetHealth() < me->GetMaxHealth() * 0.2 && uiPotion_Timer < diff && uiGCD < diff)
                {
                        doCast(me, SPELL_HEALING_POTION);
                        uiPotion_Timer = 60000;
                }

                if (!me->HasAura(SPELL_BATTLESHOUT) && uiRage > 10 && uiGCD < diff && uiBattleShout_Timer < diff)
                {
                    doCast(me, SPELL_BATTLESHOUT);
                    uiBattleShout_Timer = 30000;
                }

                if (uiBloodrage_Timer < diff && me->isInCombat() && opponent && uiGCD < diff)
                {
                    doCast(me, SPELL_BLOODRAGE);
                    uiBloodrage_Timer = 60000;
                }

                if (!me->SelectVictim() || !me->getVictim())
                {
                    ResetOrGetNextTarget();
                    return;
                }

                BreakCC(diff);
                Attack(diff);

                ScriptedAI::UpdateAI(diff);
            }
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new warrior_botAI(pCreature);
        }
};

void AddSC_warrior_bot()
{
    new warrior_bot();
}