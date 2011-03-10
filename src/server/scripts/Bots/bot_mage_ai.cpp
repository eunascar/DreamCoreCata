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

enum Misc
{
    BONUS_DAMAGE    = 986
};

enum Spells
{
    SPELL_COUNTERSPELL        = 2139,
    SPELL_PRESENCE_OF_MIND    = 12043,
    SPELL_EVOCATION           = 12051,
    SPELL_REMCURSE            = 15729,
    SPELL_REJUVEPOTION        = 28517,
    SPELL_ARCANE_TORRENT      = 28730,
    SPELL_MOLTEN_ARMOR        = 30482,
    SPELL_BLINK               = 38932,
    SPELL_ICEBLOCK            = 45438
};

#define SPELL_ARCANE_EXPLOSION    SPELL_ARCANE_EXPLOSION_A[SPELL_LEVEL]
#define SPELL_ARCANE_INTELLECT    SPELL_ARCANE_INTELLECT_A[SPELL_LEVEL]
#define SPELL_ARCANE_MISSILES     SPELL_ARCANE_MISSILES_A[SPELL_LEVEL]
#define SPELL_BLASTWAVE           SPELL_BLASTWAVE_A[SPELL_LEVEL]
#define SPELL_CONE_OF_COLD        SPELL_CONE_OF_COLD_A[SPELL_LEVEL]
#define SPELL_DAMPEN_MAGIC        SPELL_DAMPEN_MAGIC_A[SPELL_LEVEL]
#define SPELL_DRAGONBREATH        SPELL_DRAGONBREATH_A[SPELL_LEVEL]
#define SPELL_ICE_ARMOR           SPELL_ICE_ARMOR_A[SPELL_LEVEL]
#define SPELL_FIREBALL            SPELL_FIREBALL_A[SPELL_LEVEL]
#define SPELL_FIRE_BLAST          SPELL_FIRE_BLAST_A[SPELL_LEVEL]
#define SPELL_FROST_NOVA          SPELL_FROST_NOVA_A[SPELL_LEVEL]
#define SPELL_LIVING_BOMB         SPELL_LIVING_BOMB_A[SPELL_LEVEL]
#define SPELL_MAGE_ARMOR          SPELL_MAGE_ARMOR_A[SPELL_LEVEL]
#define SPELL_MANA_SHIELD         SPELL_MANA_SHIELD_A[SPELL_LEVEL]
#define SPELL_POLYMORPH           SPELL_POLYMORPH_A[SPELL_LEVEL]
#define SPELL_PYROBLAST           SPELL_PYROBLAST_A[SPELL_LEVEL]
#define SPELL_SCORCH              SPELL_SCORCH_A[SPELL_LEVEL]
#define SPELL_SPELLSTEAL          SPELL_SPELLSTEAL_A[SPELL_LEVEL]

uint32 SPELL_ARCANE_EXPLOSION_A [] = { 0, 1449, 8437, 8439, 10201, 10202, 27080, 42990, 42921 };
uint32 SPELL_ARCANE_INTELLECT_A [] = { 1459, 1460, 1461, 1461, 10156, 10157, 10157, 27126, 42995};
uint32 SPELL_ARCANE_MISSILES_A  [] = {5143, 5144, 5145, 8416, 8417, 10212, 27075, 42843, 42846 };
uint32 SPELL_BLASTWAVE_A        [] = { 0, 0, 0, 11113, 13019, 13020, 13021, 42944, 42945 };
uint32 SPELL_CONE_OF_COLD_A     [] = { 0, 0, 120, 8492, 10159, 10161, 27087, 42930, 42931 };
uint32 SPELL_DAMPEN_MAGIC_A     [] = { 0, 8450, 8451, 10173, 10173, 10174, 33944, 43015, 43015 };
uint32 SPELL_DRAGONBREATH_A     [] = { 0, 0, 0, 0, 0, 31661, 31661, 31661, 31661 };
uint32 SPELL_FIREBALL_A         [] = { 143, 145, 8400, 8401, 10148, 25306, 38692, 42834, 42834 };
uint32 SPELL_FIRE_BLAST_A       [] = {2136, 2137, 2138, 8412, 10197, 10199, 10199, 10199, 10199 };
uint32 SPELL_FROST_NOVA_A       [] = {0, 122, 865, 6131, 10230, 27088, 42917, 42917, 42917 };
uint32 SPELL_ICE_ARMOR_A        [] = {0, 0, 0, 7302, 7320, 10219, 10220, 27124, 43008  };
uint32 SPELL_LIVING_BOMB_A      [] = { 0, 0, 0, 0, 0, 44457, 44457, 44457, 44457 };
uint32 SPELL_MAGE_ARMOR_A       [] = { 0, 0, 0, 6117, 22782, 22783, 27125, 43023, 43024 };
uint32 SPELL_MANA_SHIELD_A      [] = { 0, 0, 1463, 8495, 10191, 10192, 27131, 43019, 43020 };
uint32 SPELL_POLYMORPH_A        [] = { 0, 0, 12824, 12824, 12825, 12825, 28271, 28272, 61721 };
uint32 SPELL_PYROBLAST_A        [] = { 0, 0, 11366, 12522, 12525, 12526, 27132, 42890, 42891 };
uint32 SPELL_SCORCH_A           [] = { 0, 0, 2948, 8445, 10205, 10207, 27073, 27074, 42859 };
uint32 SPELL_SPELLSTEAL_A       [] = { 0, 0, 0, 0, 0, 0, 0, 30449, 30449 };

class mage_bot : public CreatureScript
{
    public:
        mage_bot()
            : CreatureScript("mage_bot")
        {
        }

        struct mage_botAI : public bot_ai
        {
            mage_botAI(Creature *c) :bot_ai(c)
            {
                Reset();
            }

            uint32 uiFireBlast_Timer;
            uint32 uiBlastWave_Timer;
            uint32 uiCounterSpell_Timer;
            uint32 uiFrostNova_Timer;
            uint32 uiPresenceOfMind_Timer;
            uint32 uiBlizzard_Timer;
            uint32 uiDragonBreath_Timer;
            uint32 uiBlink_Timer;
            uint32 uiScorch_Timer;
            uint32 uiEvocation_Timer;
            uint32 uiLivingBomb_Timer;

            bool castedDampenMagic;
            bool castedArcaneIntellect;
            bool castedArmor;
            bool castedBlink;
            bool oom_spam;

            uint8 state;
            uint8 next_state;
            uint32 next_state_timer;
            Unit* opponent;

            void Reset()
            {
                uiBlizzard_Timer         = 0;
                uiFireBlast_Timer        = 0;
                uiBlastWave_Timer        = 0;
                uiCounterSpell_Timer     = 0;
                uiFrostNova_Timer        = 0;
                uiPresenceOfMind_Timer   = 0;
                uiDragonBreath_Timer     = 0;
                uiBlink_Timer            = 0;
                uiEvocation_Timer        = 0;
                uiPotion_Timer           = 0;
                uiGc_Timer               = 0;
                castedArcaneIntellect    = false;
                castedDampenMagic        = false;
                castedArmor              = false;
                castedBlink              = false;
                oom_spam                 = false;

                state                    = 1;
                next_state               = 0;
                next_state_timer         = 0;

                opponent                 = NULL;
            }

            void Armour(const uint32 diff)
            {
                Unit *opponent = SelectTarget(SELECT_TARGET_TOPAGGRO, 0);

                if (!castedArmor && (opponent->getClass() == CLASS_MAGE || opponent->getClass() == CLASS_PRIEST || opponent->getClass() == CLASS_WARLOCK) && isTimerReady(uiGc_Timer))
                {
                    doCast(me, SPELL_MAGE_ARMOR, true);
                    castedArmor = true;
                }
                else if (!castedArmor && isTimerReady(uiGc_Timer))
                {
                    doCast(me, SPELL_ICE_ARMOR, true);
                    castedArmor = true;
                }
                else
                {
                    doCast(me, SPELL_ICE_ARMOR, true);
                    castedArmor = true;
                    return;
                }
            }

            void AttackStart(Unit* who)
            {
                EnterCombat(who);
                ScriptedAI::AttackStartCaster(who, 31);
                me->AddThreat(who, 0.001f);
            }

            void CheckSpellSteal(const uint32 diff)
            {
                if (opponent == NULL)
                    return;

                if (opponent->isDead())
                    return;
			
                if (HasAuraName(opponent, "Mark of the Wild") || HasAuraName(opponent, "Rejuvenation") || HasAuraName(opponent, "Regrowth") || HasAuraName(opponent, "Demon Armor") || HasAuraName(opponent, "Fel Armor") || HasAuraName(opponent, "Power Word: Shield") || HasAuraName(opponent, "Power Word: Fortitude"))
                    if (isTimerReady(uiGc_Timer))
                        doCast(opponent, SPELL_SPELLSTEAL);
            }

            void Counter(const uint32 diff)
            {
                if (opponent == NULL)
                    return;

				if (opponent->isDead())
                    return;

                if (opponent->IsNonMeleeSpellCasted(true) && isTimerReady(uiCounterSpell_Timer))
                {
                    doCast(opponent, SPELL_COUNTERSPELL);
                    uiCounterSpell_Timer = 240;
                }
            }

            void DoNormalAttack(const uint32 diff)
            {
                AttackerSet m_attackers = master->getAttackers();
                bool defensive = false;

                if (opponent == NULL)
                    return;

                if (opponent->isDead())
                return;

                //opponent is attacking me, go defensive, ie point blank spells
                if (opponent->getVictim() && opponent->getVictim()->GetGUID() == me->GetGUID())
                    defensive = true;

                switch(state)
                {
                    case 0:
                        if (next_state_timer <= 0)
                            state = next_state;
                        else
                            --next_state_timer;
                        break;
                    case 1:
                        if ((opponent->GetHealth() * 100) > 80)
                            state = 6;
                        else
                            state = 5;
                        break;
                    case 2:
                        if (isTimerReady(uiGc_Timer))
                        {
                            next_state_timer = 2;
                            next_state = 3;
                            state = 0;
                        }
                        break;
                    case 3:
                        if (opponent->HasAura(SPELL_POLYMORPH) || me->HasAura(SPELL_PRESENCE_OF_MIND))
                        {
                            next_state_timer = (me->HasAura(SPELL_PRESENCE_OF_MIND)) ? 15 : 61;
                            int damage = 957 + rand() % (1215 - 957 + 1) + 1.15 * BONUS_DAMAGE;
                            doCast(opponent, SPELL_PYROBLAST);
                            next_state = 4;
                            state = 0;
                        }
                        else
                            state = 5;
                        break;
                    case 4:
                        if (isTimerReady(uiPresenceOfMind_Timer))
                        {
                            int damage = 957 + rand() % (1215 - 957 + 1) + 1.15 * BONUS_DAMAGE;
                            doCast(opponent, SPELL_PYROBLAST);
                            uiPresenceOfMind_Timer = 1200;
                            next_state = 5;
                            state = 0;
                            next_state_timer = 5;
                        }
                        else
                            state = 5;
                        break;
                    case 5:
                        if (me->GetPower(POWER_MANA) * 100 / me->GetMaxPower(POWER_MANA) < 25.0)
                        {
                            doCast(opponent, SPELL_FROST_NOVA);
                            GiveManaBack();
                            uiFrostNova_Timer = 250;
                            next_state = 8;
                            next_state_timer = 15;
                            state = 0;
                        }

                        if (SPELL_LIVING_BOMB && isTimerReady(uiLivingBomb_Timer))
                        {
                            doCast(opponent, SPELL_LIVING_BOMB);
                            GiveManaBack();
                            uiLivingBomb_Timer = 600;
                            next_state = 7;
                            next_state_timer = 2;
                            state = 0;
                        }
                        else if (isTimerReady(uiScorch_Timer))
                        {
                            doCast(opponent, SPELL_SCORCH);
                            uiScorch_Timer = 900;
                            next_state = 7;
                            next_state_timer = 5;
                            state = 0;
                        }
                        else if (isTimerReady(uiGc_Timer))
                        {
                            int damage = 377 + rand() % (407 - 377 + 1) + 0.2128 * BONUS_DAMAGE;

                            if (SPELL_ARCANE_EXPLOSION > 0 && defensive)
                                doCast(opponent, SPELL_ARCANE_EXPLOSION);
                            else
                                doCast(opponent, SPELL_FIREBALL);

							GiveManaBack();

                            next_state = 7;
                            next_state_timer = 2;
                            state = 0;
                        }
                        else if (SPELL_FIRE_BLAST && isTimerReady(uiFireBlast_Timer) && !defensive)
                        {
                            int damage = 677 + rand() % (802 - 677 + 1) + 0.4286 * BONUS_DAMAGE;
                            doCast(opponent, SPELL_FIRE_BLAST);
                            GiveManaBack();
                            uiFireBlast_Timer = 650;
                            next_state = 7;
                            next_state_timer = 3;
                            state = 0;
                        }
                        else if (SPELL_BLASTWAVE && isTimerReady(uiBlastWave_Timer) && defensive && !opponent->HasAura(SPELL_BLASTWAVE))
                        {
                            int damage = 628 + rand() % (739 - 628 + 1) + 0.1357 * BONUS_DAMAGE;
                            doCast(opponent, SPELL_BLASTWAVE);
                            GiveManaBack();
                            uiBlastWave_Timer = 350;
                            next_state = 7;
                            next_state_timer = 2;
                            state = 0;
                        }
                        else if (SPELL_DRAGONBREATH && isTimerReady(uiDragonBreath_Timer) && defensive && !opponent->HasAura(SPELL_DRAGONBREATH))
                        {
                            int damage = 693 + rand() % (806 - 693 + 1) + 0.1357 * BONUS_DAMAGE;
                            doCast(opponent, SPELL_DRAGONBREATH);
                            GiveManaBack();
                            uiDragonBreath_Timer = 450;
                            next_state = 6;
                            next_state_timer = 2;
                            state = 0;
                        }
                        break;
                    case 6:
                        if (isTimerReady(uiGc_Timer))
                        {
                            int damage = 645 + rand() % (822 - 645 + 1) + 1.00 * BONUS_DAMAGE;
                            doCast(opponent, SPELL_FIREBALL);
                            GiveManaBack();
                            next_state = 5;
                            next_state_timer = 3;
                            state = 0;
                        }
                        break;
                    case 7:
                        if (HasAuraName(opponent, SPELL_ICEBLOCK) || HasAuraName(opponent, "Divine Shield") || opponent->HasAura(5573))
                        {
                            doCast(me, SPELL_BANDAGE);
                            uiFirstAid_Timer = 60000;
                            state = 9;
                        }
                        else
                            state = 5;
                        break;
                    case 8:
                        doCast(opponent, SPELL_BLINK);   //Needs some serious testing
                        //blink is not working, so comment out for now
                        //blink = true;
                        //me->Say("BLINK", LANG_UNIVERSAL, NULL);
                        //uiGc_Timer = 1500;
                        //MonsterSay("Blink", LANG_UNIVERSAL, NULL);
                        next_state = 9;
                        next_state_timer = 5;
                        state = 0;
                        break;
                    case 9:
                        /*if (blink)
                        {
                            wait = true;
                            wait_timer = 60;
                            doCast(me, BANDAGE);
                            FirstAid_cd = FirstAid_cd;
                            //me->Say("BANDAGE", LANG_UNIVERSAL, NULL);
                            blink = false;
                            //uiGc_Timer = 1500;
                            next_state = 10;
                            next_state_timer = 35;
                        }
                        else*/
                            next_state = 5;
                            state = 0;
                        break;
                    case 10:
                        if (!me->HasAura(SPELL_BANDAGE))
                            state = 5;
                        break;
                    default:
                        state = 1;
                }
            }

            void JustDied(Unit* /*who*/)
            {
                master->SetBotCommandState(COMMAND_FOLLOW);
                state = 1;
                next_state = 0;
                next_state_timer = 0;
            }

            void KilledUnit(Unit* /*who*/)
            {
                ((Player*)master)->SetBotCommandState(COMMAND_FOLLOW);
                state = 1;
                next_state = 0;
                next_state_timer = 0;
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

                if (emote == TEXTEMOTE_BOW)
                    ((mage_botAI*)me->AI())->doCast(player, SPELL_ARCANE_INTELLECT, true );
            }
		
            void ReduceCD()
            {
                if (uiLivingBomb_Timer > 0)
                    --uiLivingBomb_Timer;

                if (uiFireBlast_Timer > 0)
                    --uiFireBlast_Timer;

                if (uiBlizzard_Timer > 0)
                    --uiBlizzard_Timer;

                if (uiBlastWave_Timer > 0)
                    --uiBlastWave_Timer;

                if (uiCounterSpell_Timer > 0)
                    --uiCounterSpell_Timer;

                if (uiFrostNova_Timer > 0)
                    --uiFrostNova_Timer;

                if (uiPresenceOfMind_Timer > 0)
                    --uiPresenceOfMind_Timer;

                if (uiScorch_Timer > 0)
                    --uiScorch_Timer;

                if (uiDragonBreath_Timer > 0)
                    --uiDragonBreath_Timer;

                if (uiBlink_Timer > 0)
                    --uiBlink_Timer;

                if (uiEvocation_Timer > 0)
                    --uiEvocation_Timer;

                if (uiFirstAid_Timer > 0)
                    --uiFirstAid_Timer;

                if (uiGc_Timer > 0)
                    --uiGc_Timer;
            }

            void UpdateAI(const uint32 diff)
            {
                if (IAmDead())
                    return;

                ReduceCD();

                if (!me->isInCombat())
                {
                    //buff master because master might be in different group
                    if (!HasAuraName(master, GetSpellName(SPELL_ARCANE_INTELLECT)) && master->isAlive() && isTimerReady(uiGc_Timer))
                        doCast(master, SPELL_ARCANE_INTELLECT, true);

                    //buff myself
                    if (!me->HasAura(SPELL_ARCANE_INTELLECT) && isTimerReady(uiGc_Timer))
                        doCast(me, SPELL_ARCANE_INTELLECT, true);

                    //check group members
                    Group::MemberSlotList const &a = ((Player*)master)->GetGroup()->GetMemberSlots();
                    for (Group::member_citerator itr = a.begin(); itr != a.end(); itr++)
                    {
                        Player *tPlayer = ((Player *)master)->GetObjPlayer(itr->guid);

                        if (tPlayer == NULL)
                            continue;

                        //buff group
                        if (tPlayer->isAlive() && !me->isInCombat() && isTimerReady(uiGc_Timer) && !HasAuraName(tPlayer, SPELL_ARCANE_INTELLECT))
                            doCast(tPlayer, SPELL_ARCANE_INTELLECT, true);
                    }

                    //no other buffs till full mana
                    if (me->GetPower(POWER_MANA) == me->GetMaxPower(POWER_MANA))
                    {
                        if (!HasAuraName(me, SPELL_DAMPEN_MAGIC) && isTimerReady(uiGc_Timer))
                        {
                            doCast(me, SPELL_DAMPEN_MAGIC, true);
                            GiveManaBack();
                            castedDampenMagic = true;
                        }

                        if (!HasAuraName(me, SPELL_ICE_ARMOR) && isTimerReady(uiGc_Timer))
                        {
                            doCast(me, SPELL_ICE_ARMOR, true);
                            GiveManaBack();
                            castedArmor = true;
                        }
                    }
                } //end if !isInCombat

                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);

                if (me->GetHealth() < me->GetMaxHealth() * 0.5 && isTimerReady(uiPotion_Timer))
                {
                    doCast(me, SPELL_HEALING_POTION);
                    uiPotion_Timer = 60000;
                }

                if (me->GetPower(POWER_MANA) < me->GetMaxPower(POWER_MANA) * 0.3 && isTimerReady(uiEvocation_Timer))
                {
                    doCast(me, SPELL_EVOCATION);
                    uiEvocation_Timer = 4800;
                }

                if (me->GetPower(POWER_MANA) < me->GetMaxPower(POWER_MANA) * 0.2)
                {
                    if (isTimerReady(uiPotion_Timer))
                    {
                        doCast(me, SPELL_MANA_POTION);
                        uiPotion_Timer = 60000;
                    }
                    else
                    {
                        if (oom_spam  ==  false)
                            oom_spam = true;

                        ScriptedAI::UpdateAI(diff);
                        //return; //can't do anything without mana
                    }
                }

                oom_spam = false;
                ScriptedAI::UpdateAI(diff);
                opponent = SelectTarget(SELECT_TARGET_TOPAGGRO, 0);

                if (!opponent && !me->getVictim())
                {
                    ResetOrGetNextTarget();
                    return;
                }

                //Armour(diff);
                CheckSpellSteal(diff);
                DoNormalAttack(diff);
                Counter(diff);
            }
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new mage_botAI(pCreature);
        }
};

void AddSC_mage_bot()
{
    new mage_bot();
}