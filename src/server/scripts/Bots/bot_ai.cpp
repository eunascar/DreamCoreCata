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

bot_ai::bot_ai(Creature* creature): ScriptedAI(creature)
{
    me = creature;
    prevCommandState = COMMAND_FOLLOW; // default
}

bot_ai::~bot_ai(){}

bool bot_ai::CureTarget (Unit* target)
{
    return true;
}

bool bot_ai::HealTarget (Unit* target, uint8 hp)
{
    return true;
}

void bot_ai::BuffTarget (Unit* target) { }

void bot_ai::BuffAndHealGroup(Player* gPlayer)
{
    if (me->IsNonMeleeSpellCasted(true))
        return; // if I'm already casting

    std::list <Unit* > unitList;
    gPlayer->GetRaidMember(unitList,30);

    if (!unitList.empty())
    {
        for (std::list <Unit* >::iterator itr = unitList.begin(); itr!=unitList.end(); ++itr)
        {
            Player *tPlayer = ((Player* )master)->GetObjPlayer((*itr)->GetGUID());

            if (tPlayer == NULL)
                continue;

            if (tPlayer->isDead())
                continue;

            if (me->GetAreaId() != gPlayer->GetAreaId())
                continue;

            (HealTarget(tPlayer, tPlayer->GetHealth() * 100 / tPlayer->GetMaxHealth()));
            BuffTarget(tPlayer);
        }
    }
}

void bot_ai::RezGroup(uint32 REZZ, Player* gPlayer)
{
    if (REZZ == 0)
        return;

    if (me->IsNonMeleeSpellCasted(true))
        return; // if I'm already casting

    Group::MemberSlotList const &a =(gPlayer)->GetGroup()->GetMemberSlots();

    for (Group::member_citerator itr = a.begin(); itr != a.end(); itr++)
    {
        Player* tPlayer = ((Player* )master)->GetObjPlayer(itr->guid);

        if (tPlayer == NULL)
            continue;

        if (tPlayer->isAlive())
            continue;

        if (me->GetAreaId() != gPlayer->GetAreaId())
            continue;

        if (me->GetDistance(tPlayer) > 30)
            continue;

        if (tPlayer->IsNonMeleeSpellCasted(true))
            continue; //someone rezzing it already

        if (me->IsNonMeleeSpellCasted(true))
            continue; // if I'm already casting

        doCast(tPlayer, REZZ);
        return;
    }
}

bool bot_ai::IAmDead()
{
    if (master <= 0 || !master->GetGroup() || ( (master->isInCombat() || me->isInCombat()) && me->isDead() ))
        return true; //You're DEAD, stop thinking.

    return false;
}

void bot_ai::BotAttackStart(Unit* victim)
{
    AttackStart(victim);
    me->AttackerStateUpdate(victim);
    me->resetAttackTimer();
    
    if (master->GetBotCommandState() != COMMAND_ATTACK)
        prevCommandState = master->GetBotCommandState();

    master->SetBotCommandState(COMMAND_ATTACK);
}

bool bot_ai::gettingAttacked(AttackerSet m_attackers)
{
    if (!m_attackers.empty())
    {
        for (AttackerSet::iterator iter = m_attackers.begin(); iter != m_attackers.end(); ++iter)
        {
            if (*iter && me->GetDistance((*iter)) < 50 && !master->IsInRaidWith(*iter) && !master->IsInPartyWith(*iter) && (*iter)->GetUInt32Value(UNIT_FIELD_DISPLAYID) != 11686)
            {
                BotAttackStart(*iter);
                return true;
            }
        }
    }

    return false;
}

void bot_ai::ResetOrGetNextTarget()
{
    if (master->GetBotMustDie())
        return;

    uint64 targetGUID = 0;

    // check if anyone has raid target
    //targetGUID = getTargetWithIcon();
    Group* group = master->GetGroup();
    targetGUID = group->GetTargetWithIconByGroup (me->GetGUID());

    if (targetGUID && targetGUID!=master->GetGUID())
    {
        Unit* target = me->GetCreature(*master, targetGUID);

        if (target && target->isAlive() && target->IsHostileTo(master) && target->isInCombat())
        {
            BotAttackStart(target);
            return;
        }
    }

    AttackerSet m_attackers = master->getAttackers();

    //check if anyone is attacking master
    if (gettingAttacked(m_attackers))
        return;

    //check if anyone is attacking me
    m_attackers = me->getAttackers();

    if (gettingAttacked(m_attackers))
        return;

    //check if master has a victim
    if (master->getVictim() && master->getVictim()->IsHostileTo(master))
    {
        if (me->IsWithinDist(me->getVictim(), 50))
        {
            BotAttackStart(master->getVictim());
            return;
        }
    }

    //lastly check a random victim, including bots, pets, etc
    Unit* target = DoSelectLowestHpFriendly(30);
    if (target != NULL && target->isAlive() && !target->IsHostileToPlayers())
    {
        m_attackers = target->getAttackers();

        if (gettingAttacked(m_attackers))
            return;
    }

    //if there is no one to attack, make sure we are following master
    if (me->getVictim()  ==  NULL && me->GetCharmInfo()->GetCommandState() != COMMAND_STAY && master->GetDistance(me) > 20 && !master->IsBeingTeleported())
    {
        if (!master->isAlive())
            master->SetBotCommandState(COMMAND_STAY);
        else if (master->GetBotCommandState() == COMMAND_ATTACK)
            master->SetBotCommandState(prevCommandState);

        return;
    }
}

std::string bot_ai::GetSpellName(uint32 spellId)
{
    if (spellId == 0)
        return "";

    int loc = master->GetSession()->GetSessionDbcLocale();
    const SpellEntry* const pSpellInfo = GetSpellStore()->LookupEntry (spellId);

    if (pSpellInfo != NULL) 
    {
        const std::string  name = pSpellInfo->SpellName[loc];
        return name;
    }

    return "";
}

bool bot_ai::HasAuraIcon (Unit* unit, uint32 SpellIconID, uint64 casterGuid)
{
    int loc = master->GetSession()->GetSessionDbcLocale();

    if (unit == NULL)
        return false;

    Unit* target = unit;

    if (target->isDead())
        return false;

    Unit::AuraMap &vAuras = (Unit::AuraMap&)target->GetOwnedAuras();

    //save the map of auras b/c it can crash if an aura goes away while looping
    UNORDERED_MAP<uint64, Aura*> auraMap;

    for (Unit::AuraMap::const_iterator iter = vAuras.begin(); iter!= vAuras.end(); ++iter)
    {
        Aura* aura = iter->second;
        (auraMap)[iter->first] = aura;
    }

    // now search our new map
    for (UNORDERED_MAP<uint64, Aura*>::iterator itr = auraMap.begin(); itr!= auraMap.end(); ++itr)
    {
        const SpellEntry* spellInfo = itr->second->GetSpellProto();
        uint32 spelliconId = spellInfo->SpellIconID;

        if (spelliconId == SpellIconID)
        {
            if (casterGuid == 0)
                return true;
            else if (casterGuid == itr->second->GetCasterGUID())
                return true;
        }
    }

    return false;
}

bool bot_ai::HasAuraName (Unit* unit, uint32 spellId, uint64 casterGuid)
{
    const SpellEntry* const pSpellInfo = GetSpellStore()->LookupEntry (spellId);

    if (!pSpellInfo)
        return false;

    int loc = master->GetSession()->GetSessionDbcLocale();
    const std::string  name = pSpellInfo->SpellName[loc];

    if (name.length()  ==  0)
        return false;

    return HasAuraName(unit, name, casterGuid);
}

bool bot_ai::HasAuraName (Unit* unit, std::string spell, uint64 casterGuid)
{
    if (spell.length() == 0)
        return false;

    int loc = master->GetSession()->GetSessionDbcLocale();;

    if (unit == NULL)
        return false;

    Unit* target = unit;

    if (target->isDead())
        return false;

    Unit::AuraMap &vAuras = (Unit::AuraMap&)target->GetOwnedAuras();

    //save the map of auras b/c it can crash if an aura goes away while looping
    UNORDERED_MAP<uint64, Aura*> auraMap;

    for (Unit::AuraMap::const_iterator iter = vAuras.begin(); iter!= vAuras.end(); ++iter)
    {
        Aura* aura = iter->second;
        (auraMap)[iter->first] = aura;
    }

    // now search our new map
    for (UNORDERED_MAP<uint64, Aura*>::iterator itr = auraMap.begin(); itr!= auraMap.end(); ++itr)
    {
        const SpellEntry* spellInfo = itr->second->GetSpellProto();
        const std::string name = spellInfo->SpellName[loc];

        if (!spell.compare(name))
        {
            if (casterGuid == 0)
                return true;
            else if (casterGuid == itr->second->GetCasterGUID())
                return true;
        }
    }

    return false;
}

bool bot_ai::listAuras (Unit* unit)
{
    int loc = 0;
    Unit* target = unit;
    sLog->outError ("ListAuras for %s", unit->GetName());
    Unit::AuraMap &vAuras = (Unit::AuraMap&)target->GetOwnedAuras();

    for (Unit::AuraMap::const_iterator itr = vAuras.begin(); itr!=vAuras.end(); ++itr)
    {
        SpellEntry const* spellInfo = itr->second->GetSpellProto();
        const std::string name = spellInfo->SpellName[loc];
        sLog->outError("aura = %u %s", spellInfo->Id, name.c_str());
    }

    return false;
}

void bot_ai::doCast(Unit* victim, uint32 spellId, bool triggered)
{
    if (spellId == 0)
        return;

    if (!isTimerReady(uiGc_Timer))
        return;

    if (me->IsNonMeleeSpellCasted(true))
        return;

    me->SetStandState(UNIT_STAND_STATE_STAND);
    uiGc_Timer = 20;
    DoCast(victim, spellId, triggered);
}

bool bot_ai::isTimerReady (int32 timer)
{
    if (timer <= 0 && uiGc_Timer <= 0)
        return true;
    else
        return false;
}

//Since a lot of spell's mana requirement is calculated
//from the base mana, it will be wrong for NPCs because base mana
//is also total mana.  So it uses up too much mana.  So just
//arbitrary give 25% mana back.
//TODO: calculate the correct cost based on the spell used
void bot_ai::GiveManaBack(uint8 amount)
{
    uint32 maxPower =  me->GetMaxPower(POWER_MANA);
    uint32 x =  me->GetPower(POWER_MANA) + maxPower * amount / 100;
    me->SetPower(POWER_MANA, x > maxPower ? maxPower : x);
}

void bot_ai::CureGroup (Unit* pTarget)
{
    Group::MemberSlotList const &a =((Player*)pTarget)->GetGroup()->GetMemberSlots();

    for (Group::member_citerator itr = a.begin(); itr != a.end(); itr++)
    {
        Player* tPlayer = ((Player *)master)->GetObjPlayer(itr->guid);

        if (tPlayer  ==  NULL)
            continue;

        if (tPlayer->isDead())
            continue;

        if (me->GetDistance(tPlayer) > 25)
            continue;

        (CureTarget(tPlayer));
    }
}

void bot_ai::Feast()
{
    uint8 myClass = me->getClass();

    //if low on mana, take a drink (only check for classes with custom AI)
    //because they are the only ones currently using mana
    if (myClass == CLASS_SHAMAN || myClass == CLASS_DRUID || myClass == CLASS_PRIEST || myClass == CLASS_MAGE || myClass == CLASS_WARLOCK || myClass == CLASS_PALADIN)
    {
        if (me->GetPower(POWER_MANA) * 100 / me->GetMaxPower(POWER_MANA) < 80 && !me->HasAura(1137) && master->GetBotMustWaitForSpell3() <= 0 && !me->isInCombat())
        {
            me->CastSpell(me, 1137, true);
            master->SetBotMustWaitForSpell3(1000);
            me->SetStandState(1);
            return;
        }
    }
    //if drinking, have to fake mana regen because charmed NPCs
    //do not regen mana
    if (me->HasAura(1137))
    {
        uint32 addvalue = 0;
        uint32 maxValue = me->GetMaxPower(POWER_MANA);
        uint32 curValue = me->GetPower(POWER_MANA);

        if (curValue <= maxValue)
        {
            addvalue = maxValue / 20;
            me->ModifyPower(POWER_MANA, addvalue);
        }
    }

    if (me->HasAura(1137) && me->GetPower(POWER_MANA) >= me->GetMaxPower(POWER_MANA))
        me->RemoveAurasDueToSpell(1137);

    //eat
    if (me->GetHealth() * 100 / me->GetMaxHealth() < 80 && !me->HasAura(10256) && master->GetBotMustWaitForSpell3() <= 0 && !me->isInCombat())
    {
        master->SetBotMustWaitForSpell3(1000);
        me->CastSpell(me, 10256, true);
        me->SetStandState(1);
        return;
    }

    //if eating, have to fake regen because charmed NPCs
    //do not regen
    if (me->HasAura(10256))
    {
        uint32 addvalue = 0;
        uint32 maxValue = me->GetMaxHealth();
        uint32 curValue = me->GetHealth();

        if (curValue <= maxValue)
        {
            addvalue = maxValue / 20;
            me->SetHealth(curValue + addvalue);
        }
    }

    if (me->GetHealth()  ==  me->GetMaxHealth() && me->HasAura(10256))
        me->RemoveAurasDueToSpell(10256);
}

void bot_ai::setStats(uint32 myclass, uint32 myrace, uint32 mylevel)
{
    if (myrace == 0)
        return;

    PlayerLevelInfo info;
    master->GetBotLevelInfo(myrace,myclass,mylevel,&info);

    PlayerClassLevelInfo classInfo;

    me->SetLevel(mylevel);
    UnitMods unitMod = UNIT_MOD_ATTACK_POWER;

    for (int i = STAT_STRENGTH; i < MAX_STATS; i++)
        me->SetStat(Stats(i), info.stats[i]);

    me->UpdateAttackPowerAndDamage();
    float val2 = 0.0f;
    float level = float(mylevel);

    uint16 index = UNIT_FIELD_ATTACK_POWER;
    uint16 index_mod = UNIT_FIELD_ATTACK_POWER_MODS;
    uint16 index_mult = UNIT_FIELD_ATTACK_POWER_MULTIPLIER;

    float mLevelMult = 0.0;

    if (level >= 40)
        mLevelMult = 1.5;

    if (level >= 50)
        mLevelMult = 2.0;

    if (level >= 60)
        mLevelMult = 3.0;

    if (level >= 70)
        mLevelMult = 4.0;

    if (level >= 80)
        mLevelMult = 5.0;

    switch(myclass)
    {
        case CLASS_WARRIOR:
            val2 = level * mLevelMult * 4.0f + me->GetStat(STAT_STRENGTH) * 2.0f;
            break;
        case CLASS_DEATH_KNIGHT:
            val2 = level * mLevelMult * 4.0f + me->GetStat(STAT_STRENGTH) * 2.0f;
            break;
        case CLASS_PALADIN:
            val2 = level * mLevelMult * 3.0f + me->GetStat(STAT_STRENGTH) * 2.0f - 20.0f;
            break;
        case CLASS_ROGUE:
            val2 = level * mLevelMult * 6.0f + me->GetStat(STAT_STRENGTH) + me->GetStat(STAT_AGILITY);
            break;
        case CLASS_HUNTER:
            val2 = level * mLevelMult * 2.0f + me->GetStat(STAT_STRENGTH) + me->GetStat(STAT_AGILITY) - 20.0f; 
            break;
        case CLASS_SHAMAN:
            val2 = level * mLevelMult * 2.0f + me->GetStat(STAT_STRENGTH) * 2.0f - 20.0f;
            break;
        case CLASS_DRUID:
            val2 = me->GetStat(STAT_STRENGTH) * 2.0f - 20.0f;
            break;
        case CLASS_MAGE:
            val2 = me->GetStat(STAT_STRENGTH) - 10.0f;
            break;
        case CLASS_PRIEST:
            val2 = me->GetStat(STAT_STRENGTH) - 10.0f;
            break;
        case CLASS_WARLOCK:
            val2 = me->GetStat(STAT_STRENGTH) - 10.0f;
            break;
    }

    //Custom weapon system
    val2 = abs(val2 + (val2 * (level / 80)));
    me->SetModifierValue(unitMod, BASE_VALUE, val2);
    float base_attPower  = me->GetModifierValue(unitMod, BASE_VALUE) * me->GetModifierValue(unitMod, BASE_PCT) * mLevelMult;

    float attPowerMod = me->GetModifierValue(unitMod, TOTAL_VALUE);

    float attPowerMultiplier = me->GetModifierValue(unitMod, TOTAL_PCT) - 1.0f;
    attPowerMod = attPowerMod ?  attPowerMod : 1;
    attPowerMultiplier = attPowerMultiplier ?  attPowerMultiplier : 0.1f;

    me->SetUInt32Value(UNIT_FIELD_ATTACK_POWER, (uint32)base_attPower);           //UNIT_FIELD_(RANGED)_ATTACK_POWER field
    me->SetUInt32Value(UNIT_FIELD_ATTACK_POWER_MODS, (uint32)attPowerMod);        //UNIT_FIELD_(RANGED)_ATTACK_POWER_MODS field
    me->SetFloatValue(UNIT_FIELD_ATTACK_POWER_MULTIPLIER, attPowerMultiplier);    //UNIT_FIELD_(RANGED)_ATTACK_POWER_MULTIPLIER field

    me->UpdateDamagePhysical(BASE_ATTACK);
    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, uint32(val2 * attPowerMultiplier) + level);
    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, uint32(val2 * attPowerMultiplier) * 2+level);

    me->UpdateDamagePhysical(BASE_ATTACK);
    me->SetFloatValue(UNIT_FIELD_MINRANGEDDAMAGE,uint32(val2 * attPowerMultiplier) + level);
    me->SetFloatValue(UNIT_FIELD_MAXRANGEDDAMAGE,uint32(val2 * attPowerMultiplier) * 2 + level);
    me->SetModifierValue(UNIT_MOD_ATTACK_POWER, BASE_VALUE, uint32(val2 * attPowerMultiplier));

    float value = 0.0f;
    unitMod = UNIT_MOD_ARMOR;

    value  = me->GetModifierValue(unitMod, BASE_VALUE);         // base armor (from items)
    value *= me->GetModifierValue(unitMod, BASE_PCT);           // armor percent from items
    value += me->GetStat(STAT_AGILITY) * 2.0f;                  // armor bonus from stats
    value += me->GetModifierValue(unitMod, TOTAL_VALUE);
    value *= me->GetModifierValue(unitMod, TOTAL_PCT);
    me->UpdateAttackPowerAndDamage();

    //Custom armor system
    value = value + (value * (level / 100));
    me->SetModifierValue(UNIT_MOD_ARMOR, BASE_VALUE, value);
}

void bot_ai::DoSay(const std::string& text, const uint32 language,uint64 receiver,Player* player) { }
