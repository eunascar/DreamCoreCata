 /*
 * Copyright (C) 2010-2011 Chronos Server <http://chronoserverwow.net/>
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

// Verificación de cuentas premium, para que no hallan desventajas
#define GOSSIP_LEVEL_80             "Haz Alcanzado nivel 80. Felicitaciones!"
#define GOSSIP_LEVEL_YET_80         "Ya has reclamado tu premio."
#define GOSSIP_LEVEL_NOT_80         "Aun no has alcanzado el nivel necesario para reclamar tu premio"
#define GOSSIP_LEVEL_COMPLETE_80    "Ya se han copado el maximo de los puestos del evento. Gracias por participar"
#define GOSSIP_NO_EVENTS            "No hay Eventos Disponibles"

//Realizar verificación de clase de cada jugador

#define GOSSIP_DK_MELEE          "*Melee Armor*"
#define GOSSIP_DK_PROTECTION     "*Protection Armor*"
#define GOSSIP_DK_SPELL          "*Spell Armor*"

#define GOSSIP_DR_MELEE          "*Melee Armor*"
#define GOSSIP_DR_SPELL_DMG      "*Spell DMG Armor*"
#define GOSSIP_DR_SPELL_RESTO    "*Spell Restoration Armor*"

#define GOSSIP_HT_DPS            "*DPS Armor*"

#define GOSSIP_MG_SPELL          "*Spell Armor*"

#define GOSSIP_PL_MELEE          "*Melee Armor*"
#define GOSSIP_PL_PROTECTION     "*Protection Armor*"
#define GOSSIP_PL_SPELL          "*Spell Armor*"

#define GOSSIP_PR_SPELL_DMG      "*Spell DMG Armor*"
#define GOSSIP_PR_SPELL_RESTO    "*Spell Resto Armor*"

#define GOSSIP_RG_MELEE          "*Melee Armor*"

#define GOSSIP_SH_MELEE          "*Melee Armor*"
#define GOSSIP_SH_SPELL_DMG      "*Spell DMG Armor*"
#define GOSSIP_SH_SPELL_RESTO    "*Spell Resto Armor*"

#define GOSSIP_WL_SPELL          "*Spell Armor*"

#define GOSSIP_WR_MELEE         "*Melee Armor*"
#define GOSSIP_WR_PROTECTION    "*Protection Armor*"

static int DeathKnightArmor[] =
{
    46111, 46113, 46115, 46116, 46117, // Melee
    46118, 46119, 46120, 46121, 46122  // Protection
};

static int DruidArmor[] =
{
    46157, 46158, 46159, 46160, 46161, // Melee
    46189, 46191, 46192, 46194, 46196, // SpellDMG
    46183, 46184, 46185, 46186, 46187  // Resto
};

static int HunterArmor[] =
{
    46141, 46142, 46143, 46144, 46145
};

static int MageArmor[] =
{
    46129, 46130, 46132, 46133, 46134
};

static int PaladinArmor[] =
{
    46152, 46153, 46154, 46155, 46156, // Melee
    46173, 46174, 46175, 46176, 46177, // Protection
    46178, 46179, 46180, 46181, 46182  // Spell
};

static int PriestArmor[] =
{
    46163, 46165, 46168, 46170, 46172, // Spell DMG
    46188, 46190, 46193, 46195, 46197  // Resto
};

static int RogueArmor[] =
{
    46123, 46124, 46125, 46126, 46127
};

static int ShamanArmor[] =
{
    46200, 46203, 46205, 46208, 46212, // Melee
    46206, 46207, 46209, 46210, 46211, // Spell DMG
    46198, 46199, 46201, 46202, 46204  // Resto
};

static int WarlockArmor[] =
{
    46135, 46136, 46137, 46139, 46140
};

static int WarriorArmor[] =
{
    46146, 46148, 46149, 46150, 46151, // Melee
    46162, 46164, 46166, 46167, 46169  // Protection
};

class npc_prize_giver : public CreatureScript
{
public:
    npc_prize_giver() : CreatureScript("npc_prize_giver") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch(action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                if (player->getClass() == CLASS_DEATH_KNIGHT)
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DK_MELEE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DK_PROTECTION, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                }

                if (player->getClass() == CLASS_DRUID)
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DR_MELEE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DR_SPELL_DMG, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DR_SPELL_RESTO, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                }

                if (player->getClass() == CLASS_HUNTER)
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HT_DPS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);

                if (player->getClass() == CLASS_MAGE)
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_MG_SPELL, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);

                if (player->getClass() == CLASS_PALADIN)
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_PL_MELEE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_PL_PROTECTION, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_PL_SPELL, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                }

                if (player->getClass() == CLASS_PRIEST)
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_PR_SPELL_DMG, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_PR_SPELL_RESTO, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
                }

                if (player->getClass() == CLASS_ROGUE)
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_RG_MELEE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);

                if (player->getClass() == CLASS_SHAMAN)
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SH_MELEE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SH_SPELL_DMG, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SH_SPELL_RESTO, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
                }

                if (player->getClass() == CLASS_WARLOCK)
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_WL_SPELL, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);

                if (player->getClass() == CLASS_WARRIOR)
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_WR_MELEE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_WR_PROTECTION, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
                }

                player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
            {
                for (uint32 id = 0; id < 5; id++)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, DeathKnightArmor[id], 1);

                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, DeathKnightArmor[id], true);
                        player->SendNewItem(item, 1, false, true);
                    }
                }

                CharacterDatabase.PExecute("UPDATE character_custom_event_winner SET prize = 1 WHERE character_guid = '%u' AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 3:
            {
                for (uint32 id = 5; id < 10; id++)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, DeathKnightArmor[id], 1);

                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, DeathKnightArmor[id], true);
                        player->SendNewItem(item, 1, false, true);
                    }
                }

                CharacterDatabase.PExecute("UPDATE character_custom_event_winner SET prize = 1 WHERE character_guid = '%u' AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 4:
            {
                for (uint32 id = 0; id < 5; id++)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, DruidArmor[id], 1);

                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, DruidArmor[id], true);
                        player->SendNewItem(item, 1, false, true);
                    }
                }

                CharacterDatabase.PExecute("UPDATE character_custom_event_winner SET prize = 1 WHERE character_guid = '%u' AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 5:
            {
                for (uint32 id = 5; id < 10; id++)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, DruidArmor[id], 1);

                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, DruidArmor[id], true);
                        player->SendNewItem(item, 1, false, true);
                    }
                }

                CharacterDatabase.PExecute("UPDATE character_custom_event_winner SET prize = 1 WHERE character_guid = '%u' AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 6:
            {
                for (uint32 id = 10; id < 15; id++)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, DruidArmor[id], 1);

                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, DruidArmor[id], true);
                        player->SendNewItem(item, 1, false, true);
                    }
                }

                CharacterDatabase.PExecute("UPDATE character_custom_event_winner SET prize = 1 WHERE character_guid = '%u' AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 7:
            {
                for (uint32 id = 0; id < 5; id++)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, HunterArmor[id], 1);

                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, HunterArmor[id], true);
                        player->SendNewItem(item, 1, false, true);
                    }
                }

                CharacterDatabase.PExecute("UPDATE character_custom_event_winner SET prize = 1 WHERE character_guid = '%u' AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 8:
            {
                for (uint32 id = 0; id < 5; id++)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, MageArmor[id], 1);

                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, MageArmor[id], true);
                        player->SendNewItem(item, 1, false, true);
                    }
                }

                CharacterDatabase.PExecute("UPDATE character_custom_event_winner SET prize = 1 WHERE character_guid = '%u' AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 9:
            {
                for (uint32 id = 0; id < 5; id++)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, PaladinArmor[id], 1);

                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, PaladinArmor[id], true);
                        player->SendNewItem(item, 1, false, true);
                    }
                }

                CharacterDatabase.PExecute("UPDATE character_custom_event_winner SET prize = 1 WHERE character_guid = '%u' AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 10:
            {
                for (uint32 id = 5; id < 10; id++)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, PaladinArmor[id], 1);

                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, PaladinArmor[id], true);
                        player->SendNewItem(item, 1, false, true);
                    }
                }

                CharacterDatabase.PExecute("UPDATE character_custom_event_winner SET prize = 1 WHERE character_guid = '%u' AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 11:
            {
                for (uint32 id = 10; id < 15; id++)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, PaladinArmor[id], 1);

                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, PaladinArmor[id], true);
                        player->SendNewItem(item, 1, false, true);
                    }
                }

                CharacterDatabase.PExecute("UPDATE character_custom_event_winner SET prize = 1 WHERE character_guid = '%u' AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 12:
            {
                for (uint32 id = 0; id < 5; id++)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, PriestArmor[id], 1);

                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, PriestArmor[id], true);
                        player->SendNewItem(item, 1, false, true);
                    }
                }

                CharacterDatabase.PExecute("UPDATE character_custom_event_winner SET prize = 1 WHERE character_guid = '%u' AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 13:
            {
                for (uint32 id = 5; id < 10; id++)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, PriestArmor[id], 1);

                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, PriestArmor[id], true);
                        player->SendNewItem(item, 1, false, true);
                    }
                }

                CharacterDatabase.PExecute("UPDATE character_custom_event_winner SET prize = 1 WHERE character_guid = '%u' AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 14:
            {
                for (uint32 id = 0; id < 5; id++)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RogueArmor[id], 1);

                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, RogueArmor[id], true);
                        player->SendNewItem(item, 1, false, true);
                    }
                }

                CharacterDatabase.PExecute("UPDATE character_custom_event_winner SET prize = 1 WHERE character_guid = '%u' AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 15:
            {
                for (uint32 id = 0; id < 5; id++)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ShamanArmor[id], 1);

                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, ShamanArmor[id], true);
                        player->SendNewItem(item, 1, false, true);
                    }
                }

                CharacterDatabase.PExecute("UPDATE character_custom_event_winner SET prize = 1 WHERE character_guid = '%u' AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 16:
            {
                for (uint32 id = 5; id < 10; id++)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ShamanArmor[id], 1);

                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, ShamanArmor[id], true);
                        player->SendNewItem(item, 1, false, true);
                    }
                }

                CharacterDatabase.PExecute("UPDATE character_custom_event_winner SET prize = 1 WHERE character_guid = '%u' AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 17:
            {
                for (uint32 id = 10; id < 15; id++)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ShamanArmor[id], 1);

                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, ShamanArmor[id], true);
                        player->SendNewItem(item, 1, false, true);
                    }
                }

                CharacterDatabase.PExecute("UPDATE character_custom_event_winner SET prize = 1 WHERE character_guid = '%u' AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 18:
            {
                for (uint32 id = 0; id < 5; id++)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, WarlockArmor[id], 1);

                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, WarlockArmor[id], true);
                        player->SendNewItem(item, 1, false, true);
                    }
                }

                CharacterDatabase.PExecute("UPDATE character_custom_event_winner SET prize = 1 WHERE character_guid = '%u' AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 19:
            {
                for (uint32 id = 0; id < 5; id++)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, WarriorArmor[id], 1);

                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, WarriorArmor[id], true);
                        player->SendNewItem(item, 1, false, true);
                    }
                }

                CharacterDatabase.PExecute("UPDATE character_custom_event_winner SET prize = 1 WHERE character_guid = '%u' AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 20:
            {
                for (uint32 id = 5; id < 10; id++)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, WarriorArmor[id], 1);

                    if (msg == EQUIP_ERR_OK)
                    {
                        Item* item = player->StoreNewItem(dest, WarriorArmor[id], true);
                        player->SendNewItem(item, 1, false, true);
                    }
                }

                CharacterDatabase.PExecute("UPDATE character_custom_event_winner SET prize = 1 WHERE character_guid = '%u' AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 21:
                player->CLOSE_GOSSIP_MENU(); 
                break;
        }

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        QueryResult active_events = CharacterDatabase.PQuery("SELECT active FROM character_custom_event WHERE active = 1");

        if (active_events)
        {
            if (player->getLevel() == 80)
            {
                QueryResult premium = LoginDatabase.PQuery("SELECT id FROM account_premium WHERE id='%u' AND active=1", player->GetSession()->GetAccountId());

                if (premium)
                {
                    // Case: Premium Account
                    QueryResult max_winners = CharacterDatabase.PQuery("SELECT max_winners FROM character_custom_event WHERE max_winners = premium_winners");

                    if (!max_winners)
                    {
                        QueryResult event = CharacterDatabase.PQuery("SELECT id, premium_winners FROM character_custom_event WHERE premium_winners < max_winners AND active = 1");
                        Field *fields = event->Fetch();
                        uint32 event_id = fields[0].GetUInt32();
                        uint32 evento;
                        evento = event_id;
                        uint32 position = fields[1].GetUInt32();
                        QueryResult exist = CharacterDatabase.PQuery("SELECT character_guid FROM character_custom_event_winner WHERE character_guid = '%u' AND event_id = '%u'", player->GetGUIDLow(), event_id);

                        if (event && !exist)
                        {
                            CharacterDatabase.PExecute("INSERT INTO character_custom_event_winner (position, premium, character_guid, character_name, event_id, prize) VALUES ('%u', 1, '%u', '%s', '%u', 0)", position + 1, player->GetGUIDLow(), player->GetName(), event_id);
                            CharacterDatabase.PExecute("UPDATE character_custom_event SET premium_winners = premium_winners + 1 WHERE id = '%u'", event_id);
                            QueryResult prize = CharacterDatabase.PQuery("SELECT prize FROM character_custom_event_winner WHERE character_guid = '%u' AND prize = 1 AND event_id = '%u'", player->GetGUIDLow(), event_id);

                            if (!prize)
                            {
                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEVEL_80, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                                player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                            }
                        }
                        else
                        {
                            QueryResult prize = CharacterDatabase.PQuery("SELECT prize FROM character_custom_event_winner WHERE character_guid = '%u' AND prize = 1 AND event_id = '%u'", player->GetGUIDLow(), event_id);

                            if (!prize)
                            {
                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEVEL_80, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                                player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                            }
			                else // Prize received yet
                            {
                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEVEL_YET_80, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
                                player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                            }
                        }
                    }
                    else
                    {
                        QueryResult prize = CharacterDatabase.PQuery("SELECT prize FROM character_custom_event_winner WHERE character_guid = '%u' AND prize = 1 AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());

                        if (!prize)
                        {
                            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEVEL_80, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                            player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                        }
                        
                        if (max_winners)
                        {
                            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEVEL_COMPLETE_80, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
                            player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                        }
                    }
                }
                else
                {
                    // Case: Normal Account
                    QueryResult max_winners = CharacterDatabase.PQuery("SELECT max_winners FROM character_custom_event WHERE max_winners = normal_winners");

                    if (!max_winners)
                    {
                        QueryResult event = CharacterDatabase.PQuery("SELECT id, normal_winners FROM character_custom_event WHERE normal_winners < max_winners AND active = 1");
                        Field *fields = event->Fetch();
                        uint32 event_id = fields[0].GetUInt32();
                        uint32 evento;
                        evento = event_id;
                        uint32 position = fields[1].GetUInt32();
                        QueryResult exist = CharacterDatabase.PQuery("SELECT character_guid FROM character_custom_event_winner WHERE character_guid = '%u' AND event_id = '%u'", player->GetGUIDLow(), event_id);

                        if (event && !exist)
                        {
                            CharacterDatabase.PExecute("INSERT INTO character_custom_event_winner (position, premium, character_guid, character_name, event_id, prize) VALUES ('%u', 0, '%u', '%s', '%u', 0)", position + 1, player->GetGUIDLow(), player->GetName(), event_id);
                            CharacterDatabase.PExecute("UPDATE character_custom_event SET normal_winners = normal_winners + 1 WHERE id = '%u'", event_id);
                            QueryResult prize = CharacterDatabase.PQuery("SELECT prize FROM character_custom_event_winner WHERE character_guid = '%u' AND prize = 1 AND event_id = '%u'", player->GetGUIDLow(), event_id);

                            if (!prize)
                            {
                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEVEL_80, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                                player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                            }
                        }
                        else
                        {
                            QueryResult prize = CharacterDatabase.PQuery("SELECT prize FROM character_custom_event_winner WHERE character_guid = '%u' AND prize = 1 AND event_id = '%u'", player->GetGUIDLow(), event_id);

                            if (!prize)
                            {
                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEVEL_80, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                                player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                            }
			                else // Prize received yet
                            {
                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEVEL_YET_80, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
                                player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                            }
                        }
                    }
                    else
                    {
                        QueryResult prize = CharacterDatabase.PQuery("SELECT prize FROM character_custom_event_winner WHERE character_guid = '%u' AND prize = 1 AND event_id = (SELECT id FROM character_custom_event WHERE active = 1)", player->GetGUIDLow());

                        if (!prize)
                        {
                            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEVEL_80, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                            player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                        }
                        
                        if (max_winners)
                        {
                            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEVEL_COMPLETE_80, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
                            player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                        }
                    }
                }
            }
            else
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEVEL_NOT_80, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
                player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
        }
        else
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_NO_EVENTS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
            player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }

        return true;
    }
};

void AddSC_event()
{
    new npc_prize_giver();
}