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

#ifndef _BOT_AI_H
#define _BOT_AI_H

#define SPELL_LEVEL ((int)me->getLevel()/10)
#define master ((Player*)me->GetCharmer())

enum GlobalSpells
{
    SPELL_DRINK                    = 1137,
    SPELL_NOGGENFOGGER_SKELETON    = 16591,
    SPELL_NOGGENFOGGER_SMALL       = 16595,
    SPELL_BANDAGE                  = 27031,
    SPELL_HEALING_POTION           = 28495,
    SPELL_MANA_POTION              = 28499,
    SPELL_REJUVENATION_POTION      = 28517,
    SPELL_PETRIFY                  = 34885
};

typedef std::set<Unit *> AttackerSet;

class bot_ai : public ScriptedAI
{
    public:
        bot_ai(Creature *c);

        virtual ~bot_ai();

        //Cure the target
        virtual bool CureTarget (Unit *target);

        //Heal the target
        virtual bool HealTarget (Unit *target, uint8 hp);

        // Buff target
        virtual void BuffTarget(Unit *target);

        // Cycles through the group to heal/buff/rezz
        void BuffAndHealGroup(Player *gPlayer);
        void RezGroup(uint32 REZZ, Player *gPlayer);

        //Debug method to list the auras currently active.
        //Use to find what spells were casted
        bool listAuras(Unit *unit);

        //More generalized method than HasAura().  It looks for
        //any rank of the spell and it doesn't care which
        //spell effect you want.  If it has the spell aura than
        //it returns true
        bool HasAuraName(Unit *unit, std::string spell, uint64 casterGuid=0);
        bool HasAuraName(Unit *unit, uint32 spellId, uint64 casterGuid=0);
        bool HasAuraIcon (Unit *unit, uint32 SpellIconID, uint64 casterGuid=0);

        std::string GetSpellName(uint32 spell_id);

        void doCast(Unit *victim, uint32 spellId, bool triggered = false);
        bool isTimerReady(int32 timer);

        void ResetOrGetNextTarget();

        void DoSay(const std::string& text, const uint32 language,uint64 receiver,Player *player);

        bool IAmDead();

        void GiveManaBack(uint8 amount=25);

        void CureGroup(Unit *pTarget);

        void Feast();

        void BotAttackStart(Unit *victim);

        uint32 uiGc_Timer;
        uint32 uiFirstAid_Timer;
        uint32 uiPotion_Timer;
        uint32 uiNoggenfogger_Timer;

    private:
        bool gettingAttacked(AttackerSet m_attackers);

        CommandStates prevCommandState;

    protected:
        void setStats(uint32 myclass, uint32 myrace, uint32 mylevel);
};
#endif

