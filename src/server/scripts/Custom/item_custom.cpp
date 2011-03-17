/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2010-2011 Chronos Server <http://chronoserverwow.net/>
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

enum MaxValues
{
    MAX_BOSS_MODELS    = 141,
    MAX_NPC_MODELS     = 30
};

enum Spells
{
    SPELL_LIGHTBRINGER    = 73326 
};

class item_boss_morpher : public ItemScript
{
public:
    item_boss_morpher() : ItemScript("item_boss_morpher") { }

    bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/)
    {
        uint32 number = rand() % MAX_BOSS_MODELS + 1;
        QueryResult boss = WorldDatabase.PQuery("SELECT modelid, scale FROM item_models WHERE id = '%u' AND type = 1", number);
        Field *fields = boss->Fetch();
        uint32 model = fields[0].GetUInt32();
        float scale = fields[1].GetFloat();

        Unit* target = player->GetSession()->GetPlayer();
        target->SetDisplayId(model);
        target->SetFloatValue(OBJECT_FIELD_SCALE_X, scale);

        if (!player->HasAura(SPELL_LIGHTBRINGER))
            player->AddAura(SPELL_LIGHTBRINGER,player);

        return true;
    }
};

class item_npc_morpher : public ItemScript
{
public:
    item_npc_morpher() : ItemScript("item_npc_morpher") { }

    bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/)
    {
        uint32 number = rand() % MAX_NPC_MODELS + 1;
        QueryResult boss = WorldDatabase.PQuery("SELECT modelid, scale FROM item_models WHERE id = '%u' AND type = 0", number);
        Field *fields = boss->Fetch();
        uint32 model = fields[0].GetUInt32();
        float scale = fields[1].GetFloat();

        Unit* target = player->GetSession()->GetPlayer();
        target->SetDisplayId(model);
        target->SetFloatValue(OBJECT_FIELD_SCALE_X, scale);

        if (!player->HasAura(SPELL_LIGHTBRINGER))
            player->AddAura(SPELL_LIGHTBRINGER,player);

        return true;
    }
};

void AddSC_item_custom()
{
    new item_boss_morpher();
    new item_npc_morpher();
}