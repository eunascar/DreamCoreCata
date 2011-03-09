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

enum Auras
{
    NoAura                  = 0,
    DevotionAura            = 1,
    FireResistanceAura      = 2,
    FrostResistanceAura     = 3,
    RetributionAura         = 4,
    ShadowResistanceAura    = 5
};

#define SPELL_BLESSING_OF_KINGS        SPELL_BLESSING_OF_KINGS_A[SPELL_LEVEL]
#define SPELL_BLESSING_OF_SANCTUARY    SPELL_BLESSING_OF_SANCTUARY_A[SPELL_LEVEL]
#define SPELL_BLESSING_OF_WISDOM       SPELL_BLESSING_OF_WISDOM_A[SPELL_LEVEL]
#define SPELL_CLEANSE                  SPELL_CLEANSE_A[SPELL_LEVEL]
#define SPELL_DEVOTION_AURA            SPELL_DEVOTION_AURA_A[SPELL_LEVEL]
#define SPELL_FIRE_RESISTANCE_AURA     SPELL_FIRE_RESISTANCE_AURA_A[SPELL_LEVEL]
#define SPELL_FLASH_OF_LIGHT           SPELL_FLASH_OF_LIGHT_A[SPELL_LEVEL]
#define SPELL_HAMMER_OF_JUSTICE        SPELL_HAMMER_OF_JUSTICE_A[SPELL_LEVEL]
#define SPELL_HOLY_LIGHT               SPELL_HOLY_LIGHT_A[SPELL_LEVEL]
#define SPELL_JUDGEMENT_OF_LIGHT       SPELL_JUDGEMENT_OF_LIGHT_A[SPELL_LEVEL]
#define SPELL_LAY_OF_HANDS             SPELL_LAY_OF_HANDS_A[SPELL_LEVEL]
#define SPELL_REDEMPTION               SPELL_REDEMPTION_A[SPELL_LEVEL]
#define SPELL_SEAL_OF_LIGHT	           SPELL_SEAL_OF_LIGHT_A[SPELL_LEVEL]

uint32 SPELL_BLESSING_OF_KINGS_A     [] = {0, 0, 56525, 56525, 56525, 56525, 56525, 56525, 56525, 56525};
uint32 SPELL_BLESSING_OF_SANCTUARY_A [] = {0, 0, 0, 67480, 67480, 67480, 67480, 67480, 67480, 67480};
uint32 SPELL_BLESSING_OF_WISDOM_A    [] = {0, 19742, 19850, 19852, 19853, 19854, 25290, 48935, 48936, 48936};
uint32 SPELL_CLEANSE_A               [] = {0, 0, 0, 0, 4987, 4987, 4987, 4987, 4987};
uint32 SPELL_DEVOTION_AURA_A         [] = {465, 10290, 643, 10291, 1032, 10292, 10293, 48941, 48942, 48942};
uint32 SPELL_FIRE_RESISTANCE_AURA_A  [] = {0, 0, 0, 19891, 19899, 19899, 19900, 27153, 48947, 48947};
uint32 SPELL_FLASH_OF_LIGHT_A        [] = {0, 0, 19939, 19940, 19941, 19942, 27137, 48784, 48785, 48785};
uint32 SPELL_HAMMER_OF_JUSTICE_A     [] = {0, 853, 5588, 5588, 5589, 10308, 10308, 37369, 37369};
uint32 SPELL_HOLY_LIGHT_A            [] = {635, 647, 1026, 3472, 10328, 10329, 27135, 48781, 48782, 48782};
uint32 SPELL_JUDGEMENT_OF_LIGHT_A    [] = {0, 0, 0, 20185, 20185, 20185, 20185, 20185, 20185, 20185};
uint32 SPELL_LAY_OF_HANDS_A          [] = {0, 633, 633, 2800, 2800, 10310, 10310, 27154, 48788, 48788};
uint32 SPELL_REDEMPTION_A            [] = {0, 7328, 10322, 10324, 20772, 20772, 20773, 48949, 48950, 48950};
uint32 SPELL_SEAL_OF_LIGHT_A         [] = {0, 0, 0, 20165, 20165, 20165, 20165, 20165, 20165, 20165};

Auras Aura;

class paladin_bot : public CreatureScript
{
    public:
        paladin_bot()
            : CreatureScript("paladin_bot")
        {
        }

        struct paladin_botAI : public bot_ai
        {
            paladin_botAI(Creature *c) :bot_ai(c)
            {
                Reset();
            }

            bool oom_spam;

            Unit* opponent;

            uint32 uiLayOfHands_Timer;
            uint32 uiHammerOfJustice_Timer;

            void Reset()
            {
                oom_spam = false;

                opponent = NULL;

                uiGc_Timer                 = 0;
                uiLayOfHands_Timer         = 0;
                uiHammerOfJustice_Timer    = 0;
                uiPotion_Timer             = 0;
            }

            bool CureTarget(Unit* target)
            {
                if (!isTimerReady(uiGc_Timer))
                    return false;

                if (HasAuraName(target, "Withering Heat"))
                    doCast(target, SPELL_CLEANSE);

                if (HasAuraName(target, "Ancient Dread"))
                    doCast(target, SPELL_CLEANSE);

                if (HasAuraName(target, "Ancient Dread"))
                    doCast(target, SPELL_CLEANSE);

                if (HasAuraName(target, "Arcane Buffet"))
                    doCast(target, SPELL_CLEANSE);

                if (HasAuraName(target, "Shadow Buffet"))
                    doCast(target, SPELL_CLEANSE);

                if (HasAuraName(target, "Flame Buffet"))
                    doCast(target, SPELL_CLEANSE);

                if (HasAuraName(target, "Frost Buffet"))
                doCast(target, SPELL_CLEANSE);

                return true;
            }

            bool HealTarget(Unit* target, uint8 hp)
            {
                if (!isTimerReady(uiGc_Timer))
                    return false;

                if (me->IsNonMeleeSpellCasted(true))
                    return false;

                if (!target || target->isDead())
                    return false;

                if (hp < 25 && isTimerReady(uiLayOfHands_Timer))
                {
                    // 33% to cast loh, else just do a fast heal
                    uint64 m_rand = urand(1, 3);

                    switch(m_rand)
                    {
                        case 1:
                        {
                            std::string loh = "Lay of Hands on ";
                            loh += target->GetName();
                            loh += ".";

                            me->MonsterSay(loh.c_str(), LANG_UNIVERSAL, NULL);

                            doCast(target, SPELL_LAY_OF_HANDS);
                            uiLayOfHands_Timer = 1600;
                            return true;
                        }
                        case 2:
                        case 3:
                            doCast(target, SPELL_FLASH_OF_LIGHT);
                            GiveManaBack(15);
                            return true;
                    }

                }

                if (hp < 60)
                {
                    doCast(target, SPELL_FLASH_OF_LIGHT);
                    GiveManaBack(15);
                    return true;
                }

                if (hp < 80)
                {
                    doCast(target, SPELL_HOLY_LIGHT);
                    GiveManaBack(20);
                    return true;
                }

                return true;
            }

            void UpdateAI(const uint32 diff)
            {
                DoMeleeAttackIfReady();

                if (IAmDead())
                    return;

                ReduceCD(diff);

                opponent = me->getVictim();

                if (!opponent )
                {
                    ResetOrGetNextTarget();
                    DoNonCombatActions();
                    return;
                }

                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);

                if (me->GetHealth() < me->GetMaxHealth()*0.5 && isTimerReady(uiPotion_Timer))
                {
                    doCast(me, SPELL_HEALING_POTION);
                    uiPotion_Timer = 60000;
                }

                oom_spam = false;

                //buff and heal master's group
                if (master->GetGroup())
                {
                    BuffAndHealGroup(master);
                    CureGroup(master);
                }

                // Heal myself
                HealTarget (me, me->GetHealth() * 100 / me->GetMaxHealth());
                DoNormalAttack(diff);
                Counter(diff);

                ScriptedAI::UpdateAI(diff);
            }

            void DoNonCombatActions()
            {
                if (me->HasAura(SPELL_DEVOTION_AURA))
                Aura = DevotionAura;
                else if (me->HasAura(SPELL_FIRE_RESISTANCE_AURA))
                    Aura = FireResistanceAura;
                else
                    Aura = NoAura;

                //buff myself
                if (!master->HasAura(SPELL_DEVOTION_AURA) && isTimerReady(uiGc_Timer))
                    doCast(me, SPELL_DEVOTION_AURA, true);
                else
                    // I already have devotion aura and its not mine, cast different aura
                    if (master->HasAura(SPELL_DEVOTION_AURA) && !master->HasAura(SPELL_DEVOTION_AURA, me->GetGUID()) && Aura == NoAura && isTimerReady(uiGc_Timer))
                    doCast(me, SPELL_FIRE_RESISTANCE_AURA, true);

                if (!me->HasAura(SPELL_SEAL_OF_LIGHT) && isTimerReady(uiGc_Timer))
                    doCast(me, SPELL_SEAL_OF_LIGHT, true);

                //buff and heal master's group
                if (master->GetGroup())
                {
                    RezGroup(SPELL_REDEMPTION, master);
                    BuffAndHealGroup(master);
                    CureGroup(master);
                }
            }

            void BuffTarget(Unit* target)
            {
                if (!target)
                    return;

                switch(target->getClass())
                {
                    case CLASS_MAGE:
                    case CLASS_PRIEST:
                    case CLASS_WARLOCK:
                        if (!HasAuraName(target, GetSpellName(SPELL_BLESSING_OF_WISDOM)))
                            doCast(target, SPELL_BLESSING_OF_WISDOM, true);
                        break;
                    case CLASS_PALADIN:
                        if (!HasAuraName(target, GetSpellName(SPELL_BLESSING_OF_SANCTUARY)))
                            doCast(target, SPELL_BLESSING_OF_SANCTUARY, true);
                        break;
                    default:
                        if (!HasAuraName(target, GetSpellName(SPELL_BLESSING_OF_KINGS)))
                            doCast(target, SPELL_BLESSING_OF_KINGS, true);
                        break;
                }
            }

            void JustDied(Unit* /*who*/)
            {
                master->SetBotCommandState(COMMAND_FOLLOW);
            }

            void AttackStart(Unit* who)
            {
                EnterCombat(who);
                ScriptedAI::AttackStart(who);
            }

            void KilledUnit(Unit* /*who*/)
            {
                ((Player*)master)->SetBotCommandState(COMMAND_FOLLOW);
            }

            void Counter(const uint32 diff)
            {
                if (opponent  ==  NULL)
                    return;

                if (opponent->isDead())
                    return;

                if (opponent->IsNonMeleeSpellCasted(true) && isTimerReady(uiHammerOfJustice_Timer))
                {
                    doCast(opponent, SPELL_HAMMER_OF_JUSTICE);
                    uiHammerOfJustice_Timer = 600;
                }
            }

            void DoNormalAttack(const uint32 diff)
            {
                if (!opponent->HasAura(SPELL_JUDGEMENT_OF_LIGHT) && isTimerReady(uiGc_Timer))
                    doCast(opponent, SPELL_JUDGEMENT_OF_LIGHT, true);
            }

            void ReduceCD(const uint32 diff)
            {
                if (uiGc_Timer > 0)
                    --uiGc_Timer;

                if (uiLayOfHands_Timer > 0)
                    --uiLayOfHands_Timer;

                if (uiHammerOfJustice_Timer > 0)
                    --uiHammerOfJustice_Timer;
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
                {
                    player->SetBotCommandState(COMMAND_FOLLOW);
                    BuffTarget(player);
                }
            }
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new paladin_botAI(pCreature);
        }
};

void AddSC_paladin_bot()
{
    new paladin_bot();
}