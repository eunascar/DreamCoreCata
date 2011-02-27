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

#define GOSSIP_NO_ITEM         "No se han Encontrado Items de Donacion"
#define GOSSIP_NO_AVAILABLE    "Has alcanzado el Maximo de intentos para realizar esta accion"
#define GOSSIP_ITEM_WEAPONS    "Cambiar Items"
#define GOSSIP_ITEM_AXE        "Poseo un Hacha"
#define GOSSIP_ITEM_DAGGER     "Poseo una Daga"
#define GOSSIP_ITEM_MACE       "Poseo un Mazo"
#define GOSSIP_ITEM_RANGED     "Poseo un Item de Rango"
#define GOSSIP_ITEM_SHIELD     "Poseo un Escudo"
#define GOSSIP_ITEM_STAFF      "Poseo un Baston"
#define GOSSIP_ITEM_SWORD      "Poseo una Espada"
//Realizar verificación de Items que tiene el jugador y según eso mostrar el gossip

// Devastation Axe => Otros Weapons
#define GOSSIP_1H_AXE_TO_SPECTRUM_DAGGER              "*Devastation Axe* => *Spectrum Dagger*"
#define GOSSIP_1H_AXE_TO_DARK_MACE                    "*Devastation Axe* => *Dark Mace*"
#define GOSSIP_1H_AXE_TO_DEVASTATION_SWORD            "*Devastation Axe* => *Devastation Sword*"
#define GOSSIP_1H_AXE_TO_FORTIFIED_SWORD              "*Devastation Axe* => *Fortified Sword*"
#define GOSSIP_1H_AXE_TO_MAGIC_SWORD                  "*Devastation Axe* => *Magic Sword*"
// Brutal Axe => Otros Weapons
#define GOSSIP_2H_AXE_TO_VENGEFUL_MACE                "*Brutal Axe* => *Vengeful Mace*"
#define GOSSIP_2H_AXE_TO_SAVAGE_SWORD                 "*Brutal Axe* => *Savage Sword*"
// Dagger => Otros Weapons
#define GOSSIP_DAGGER_TO_DEVASTATION_AXE              "*Spectrum Dagger* => *Devastation Axe*"
#define GOSSIP_DAGGER_TO_DARK_MACE                    "*Spectrum Dagger* => *Dark Mace*"
#define GOSSIP_DAGGER_TO_DEVASTATION_SWORD            "*Spectrum Dagger* => *Devastation Sword*"
#define GOSSIP_DAGGER_TO_FORTIFIED_SWORD              "*Spectrum Dagger* => *Fortified Sword*"
#define GOSSIP_DAGGER_TO_MAGIC_SWORD                  "*Spectrum Dagger* => *Magic Sword*"
// Dark Mace => Otros Weapons
#define GOSSIP_1H_MACE_TO_DEVASTATION_AXE             "*Dark Mace* => *Devastation Axe*"
#define GOSSIP_1H_MACE_TO_SPECTRUM_DAGGER             "*Dark Mace* => *Spectrum Dagger*"
#define GOSSIP_1H_MACE_TO_DEVASTATION_SWORD           "*Dark Mace* => *Devastation Sword*"
#define GOSSIP_1H_MACE_TO_FORTIFIED_SWORD             "*Dark Mace* => *Fortified Sword*"
#define GOSSIP_1H_MACE_TO_MAGIC_SWORD                 "*Dark Mace* => *Magic Sword*"
// Dark Mace => Otros Weapons
#define GOSSIP_2H_MACE_TO_BRUTAL_AXE                  "*Vengeful Mace* => *Brutal Axe*"
#define GOSSIP_2H_MACE_TO_SAVAGE_SWORD                "*Vengeful Mace* => *Savage Sword*"
// Ranged Weapons
#define GOSSIP_BOW_TO_GUN                             "*Mirkwood Bow* => *Rosario's Gun*"
#define GOSSIP_GUN_TO_BOW                             "*Rosario's Gun* => *Mirkwood Bow*"
// Staves
#define GOSSIP_FERAL_TO_BALANCE                       "*Feral Staff* => *Greatest Staff*"
#define GOSSIP_BALANCE_TO_FERAL                       "*Greatest Staff* => *Feral Staff*"
// Shields
#define GOSSIP_JUSTICE_TO_MAGIC                       "*Justice Wall* => *Magic Wall*"
#define GOSSIP_MAGIC_TO_JUSTICE                       "*Magic Wall* => *Justice Wall*"
// Devastation Sword => Otros Weapons
#define GOSSIP_1H_DPS_SWORD_TO_SPECTRUM_DAGGER        "*Devastation Sword* => *Spectrum Dagger*"
#define GOSSIP_1H_DPS_SWORD_TO_DARK_MACE              "*Devastation Sword* => *Dark Mace*"
#define GOSSIP_1H_DPS_SWORD_TO_DEVASTATION_AXE        "*Devastation Sword* => *Devastation Axe*"
#define GOSSIP_1H_DPS_SWORD_TO_FORTIFIED_SWORD        "*Devastation Sword* => *Fortified Sword*"
#define GOSSIP_1H_DPS_SWORD_TO_MAGIC_SWORD            "*Devastation Sword* => *Magic Sword*"
// Fortified Sword => Otros Weapons
#define GOSSIP_1H_PROT_SWORD_TO_SPECTRUM_DAGGER       "*Fortified Sword* => *Spectrum Dagger*"
#define GOSSIP_1H_PROT_SWORD_TO_DARK_MACE             "*Fortified Sword* => *Dark Mace*"
#define GOSSIP_1H_PROT_SWORD_TO_DEVASTATION_AXE       "*Fortified Sword* => *Devastation Axe*"
#define GOSSIP_1H_PROT_SWORD_TO_DEVASTATION_SWORD     "*Fortified Sword* => *Devastation Sword*"
#define GOSSIP_1H_PROT_SWORD_TO_MAGIC_SWORD           "*Fortified Sword* => *Magic Sword*"
// Magic Sword => Otros Weapons
#define GOSSIP_1H_SPELL_SWORD_TO_SPECTRUM_DAGGER      "*Magic Sword* => *Spectrum Dagger*"
#define GOSSIP_1H_SPELL_SWORD_TO_DARK_MACE            "*Magic Sword* => *Dark Mace*"
#define GOSSIP_1H_SPELL_SWORD_TO_DEVASTATION_AXE      "*Magic Sword* => *Devastation Axe*"
#define GOSSIP_1H_SPELL_SWORD_TO_DEVASTATION_SWORD    "*Magic Sword* => *Devastation Sword*"
#define GOSSIP_1H_SPELL_SWORD_TO_FORTIFIED_SWORD      "*Magic Sword* => *Fortified Sword*"
// Savage Sword => Otros Weapons
#define GOSSIP_2H_SWORD_TO_VENGEFUL_MACE              "*Savage Sword* => *Vengeful Mace*"
#define GOSSIP_2H_SWORD_TO_BRUTAL_AXE                 "*Savage Sword* => *Brutal Axe*"

enum Items
{
    ITEM_BRUTAL_AXE           = 49886, // 2h
    ITEM_DEVASTATION_AXE      = 49774, // 1h
    ITEM_SPECTRUM_DAGGER      = 49935, // 1h
    ITEM_DARK_MACE            = 49737, // 1h
    ITEM_VENGEFUL_MACE        = 49293, // 2h
    ITEM_MIRKWOOD_BOW_R       = 49761, // Rg
    ITEM_ROSARIO_GUN_R        = 49762, // Rg
    ITEM_FERAL_STAFF          = 49736, // 2h
    ITEM_GREATEST_STAFF       = 49724, // 2h
    ITEM_DEVASTATION_SWORD    = 49931, // 1h
    ITEM_FORTIFIED_SWORD      = 49727, // 1h
    ITEM_MAGIC_SWORD          = 49721, // 1h
    ITEM_SAVAGE_SWORD         = 49984, // 2h
    ITEM_JUSTICE_WALL         = 53938, // Sh
    ITEM_MAGIC_WALL           = 53937  // Sh
};

class npc_donor_service : public CreatureScript
{
public:
    npc_donor_service() : CreatureScript("npc_donor_service") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch(action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                if ((player->HasItemCount(ITEM_BRUTAL_AXE, 1)) || (player->HasItemCount(ITEM_DEVASTATION_AXE, 1)))
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_AXE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

                if (player->HasItemCount(ITEM_SPECTRUM_DAGGER, 1))
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DAGGER, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

                if ((player->HasItemCount(ITEM_DARK_MACE, 1)) || (player->HasItemCount(ITEM_VENGEFUL_MACE, 1)))
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_MACE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);

                if ((player->HasItemCount(ITEM_MIRKWOOD_BOW_R, 1)) || (player->HasItemCount(ITEM_ROSARIO_GUN_R, 1)))
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RANGED, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);

                if ((player->HasItemCount(ITEM_FERAL_STAFF, 1)) || (player->HasItemCount(ITEM_GREATEST_STAFF, 1)))
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_STAFF, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);

                if ((player->HasItemCount(ITEM_DEVASTATION_SWORD, 1)) || (player->HasItemCount(ITEM_FORTIFIED_SWORD, 1)) || (player->HasItemCount(ITEM_MAGIC_SWORD, 1)) || (player->HasItemCount(ITEM_SAVAGE_SWORD, 1)))
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SWORD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);

                if ((player->HasItemCount(ITEM_JUSTICE_WALL, 1)) || (player->HasItemCount(ITEM_MAGIC_WALL, 1)))
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SHIELD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);

                player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                if (player->HasItemCount(ITEM_DEVASTATION_AXE, 1))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_AXE_TO_SPECTRUM_DAGGER, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_AXE_TO_DARK_MACE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_AXE_TO_DEVASTATION_SWORD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_AXE_TO_FORTIFIED_SWORD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_AXE_TO_MAGIC_SWORD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
                    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }

                if (player->HasItemCount(ITEM_BRUTAL_AXE, 1))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_2H_AXE_TO_VENGEFUL_MACE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_2H_AXE_TO_SAVAGE_SWORD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
                    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                if (player->HasItemCount(ITEM_SPECTRUM_DAGGER, 1))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DAGGER_TO_DEVASTATION_AXE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DAGGER_TO_DARK_MACE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DAGGER_TO_DEVASTATION_SWORD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DAGGER_TO_FORTIFIED_SWORD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DAGGER_TO_MAGIC_SWORD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
                    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                if (player->HasItemCount(ITEM_DARK_MACE, 1))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_MACE_TO_DEVASTATION_AXE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_MACE_TO_SPECTRUM_DAGGER, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_MACE_TO_DEVASTATION_SWORD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_MACE_TO_FORTIFIED_SWORD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 24);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_MACE_TO_MAGIC_SWORD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 25);
                    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }

                if (player->HasItemCount(ITEM_VENGEFUL_MACE, 1))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_2H_MACE_TO_BRUTAL_AXE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 26);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_2H_MACE_TO_SAVAGE_SWORD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 27);
                    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:
                if (player->HasItemCount(ITEM_MIRKWOOD_BOW_R, 1))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BOW_TO_GUN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 28);
                    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }

                if (player->HasItemCount(ITEM_ROSARIO_GUN_R, 1))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_GUN_TO_BOW, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 29);
                    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:
                if (player->HasItemCount(ITEM_FERAL_STAFF, 1))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FERAL_TO_BALANCE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);
                    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }

                if (player->HasItemCount(ITEM_GREATEST_STAFF, 1))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BALANCE_TO_FERAL, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
                    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:
                if (player->HasItemCount(ITEM_DEVASTATION_SWORD, 1))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_DPS_SWORD_TO_SPECTRUM_DAGGER, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 32);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_DPS_SWORD_TO_DARK_MACE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_DPS_SWORD_TO_DEVASTATION_AXE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 34);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_DPS_SWORD_TO_FORTIFIED_SWORD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 35);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_DPS_SWORD_TO_MAGIC_SWORD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 36);
                    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }

                if (player->HasItemCount(ITEM_FORTIFIED_SWORD, 1))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_PROT_SWORD_TO_SPECTRUM_DAGGER, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 37);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_PROT_SWORD_TO_DARK_MACE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 38);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_PROT_SWORD_TO_DEVASTATION_AXE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 39);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_PROT_SWORD_TO_DEVASTATION_SWORD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_PROT_SWORD_TO_MAGIC_SWORD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 41);
                    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }

                if (player->HasItemCount(ITEM_MAGIC_SWORD, 1))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_SPELL_SWORD_TO_SPECTRUM_DAGGER, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 42);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_SPELL_SWORD_TO_DARK_MACE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_SPELL_SWORD_TO_DEVASTATION_AXE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 44);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_SPELL_SWORD_TO_DEVASTATION_SWORD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 45);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_1H_SPELL_SWORD_TO_FORTIFIED_SWORD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 46);
                    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }

                if (player->HasItemCount(ITEM_SAVAGE_SWORD, 1))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_2H_SWORD_TO_VENGEFUL_MACE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 47);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_2H_SWORD_TO_BRUTAL_AXE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 48);
                    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:
                if (player->HasItemCount(ITEM_JUSTICE_WALL, 1))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_JUSTICE_TO_MAGIC, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 49);
                    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }

                if (player->HasItemCount(ITEM_MAGIC_WALL, 1))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_MAGIC_TO_JUSTICE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 50);
                    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_SPECTRUM_DAGGER, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_DEVASTATION_AXE, 1, true, false);
                        player->StoreNewItem(dest, ITEM_SPECTRUM_DAGGER, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 10:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_DARK_MACE, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_DEVASTATION_AXE, 1, true, false);
                        player->StoreNewItem(dest, ITEM_DARK_MACE, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 11:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_DEVASTATION_SWORD, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_DEVASTATION_AXE, 1, true, false);
                        player->StoreNewItem(dest, ITEM_DEVASTATION_SWORD, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 12:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_FORTIFIED_SWORD, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_DEVASTATION_AXE, 1, true, false);
                        player->StoreNewItem(dest, ITEM_FORTIFIED_SWORD, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 13:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_MAGIC_SWORD, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_DEVASTATION_AXE, 1, true, false);
                        player->StoreNewItem(dest, ITEM_MAGIC_SWORD, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 14:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_VENGEFUL_MACE, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_BRUTAL_AXE, 1, true, false);
                        player->StoreNewItem(dest, ITEM_VENGEFUL_MACE, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 15:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_SAVAGE_SWORD, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_BRUTAL_AXE, 1, true, false);
                        player->StoreNewItem(dest, ITEM_SAVAGE_SWORD, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 16:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_DEVASTATION_AXE, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_SPECTRUM_DAGGER, 1, true, false);
                        player->StoreNewItem(dest, ITEM_DEVASTATION_AXE, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 17:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_DARK_MACE, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_SPECTRUM_DAGGER, 1, true, false);
                        player->StoreNewItem(dest, ITEM_DARK_MACE, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 18:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_DEVASTATION_SWORD, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_SPECTRUM_DAGGER, 1, true, false);
                        player->StoreNewItem(dest, ITEM_DEVASTATION_SWORD, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 19:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_FORTIFIED_SWORD, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_SPECTRUM_DAGGER, 1, true, false);
                        player->StoreNewItem(dest, ITEM_FORTIFIED_SWORD, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 20:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_MAGIC_SWORD, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_SPECTRUM_DAGGER, 1, true, false);
                        player->StoreNewItem(dest, ITEM_MAGIC_SWORD, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 21:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_DEVASTATION_AXE, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_DARK_MACE, 1, true, false);
                        player->StoreNewItem(dest, ITEM_DEVASTATION_AXE, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 22:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_SPECTRUM_DAGGER, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_DARK_MACE, 1, true, false);
                        player->StoreNewItem(dest, ITEM_SPECTRUM_DAGGER, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 23:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_DEVASTATION_SWORD, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_DARK_MACE, 1, true, false);
                        player->StoreNewItem(dest, ITEM_DEVASTATION_SWORD, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 24:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_FORTIFIED_SWORD, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_DARK_MACE, 1, true, false);
                        player->StoreNewItem(dest, ITEM_FORTIFIED_SWORD, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 25:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_MAGIC_SWORD, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_DARK_MACE, 1, true, false);
                        player->StoreNewItem(dest, ITEM_MAGIC_SWORD, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 26:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_BRUTAL_AXE, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_VENGEFUL_MACE, 1, true, false);
                        player->StoreNewItem(dest, ITEM_BRUTAL_AXE, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 27:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_SAVAGE_SWORD, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_VENGEFUL_MACE, 1, true, false);
                        player->StoreNewItem(dest, ITEM_SAVAGE_SWORD, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 28:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_ROSARIO_GUN_R, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_MIRKWOOD_BOW_R, 1, true, false);
                        player->StoreNewItem(dest, ITEM_ROSARIO_GUN_R, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 29:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_MIRKWOOD_BOW_R, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_ROSARIO_GUN_R, 1, true, false);
                        player->StoreNewItem(dest, ITEM_MIRKWOOD_BOW_R, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 30:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_GREATEST_STAFF, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_FERAL_STAFF, 1, true, false);
                        player->StoreNewItem(dest, ITEM_GREATEST_STAFF, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 31:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_FERAL_STAFF, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_GREATEST_STAFF, 1, true, false);
                        player->StoreNewItem(dest, ITEM_FERAL_STAFF, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 32:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_SPECTRUM_DAGGER, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_DEVASTATION_SWORD, 1, true, false);
                        player->StoreNewItem(dest, ITEM_SPECTRUM_DAGGER, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 33:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_DARK_MACE, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_DEVASTATION_SWORD, 1, true, false);
                        player->StoreNewItem(dest, ITEM_DARK_MACE, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 34:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_DEVASTATION_AXE, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_DEVASTATION_SWORD, 1, true, false);
                        player->StoreNewItem(dest, ITEM_DEVASTATION_AXE, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 35:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_FORTIFIED_SWORD, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_DEVASTATION_SWORD, 1, true, false);
                        player->StoreNewItem(dest, ITEM_FORTIFIED_SWORD, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 36:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_MAGIC_SWORD, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_DEVASTATION_SWORD, 1, true, false);
                        player->StoreNewItem(dest, ITEM_MAGIC_SWORD, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 37:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_SPECTRUM_DAGGER, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_FORTIFIED_SWORD, 1, true, false);
                        player->StoreNewItem(dest, ITEM_SPECTRUM_DAGGER, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 38:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_DARK_MACE, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_FORTIFIED_SWORD, 1, true, false);
                        player->StoreNewItem(dest, ITEM_DARK_MACE, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 39:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_DEVASTATION_AXE, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_FORTIFIED_SWORD, 1, true, false);
                        player->StoreNewItem(dest, ITEM_DEVASTATION_AXE, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 40:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_DEVASTATION_SWORD, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_FORTIFIED_SWORD, 1, true, false);
                        player->StoreNewItem(dest, ITEM_DEVASTATION_SWORD, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 41:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_MAGIC_SWORD, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_FORTIFIED_SWORD, 1, true, false);
                        player->StoreNewItem(dest, ITEM_MAGIC_SWORD, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 42:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_SPECTRUM_DAGGER, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_MAGIC_SWORD, 1, true, false);
                        player->StoreNewItem(dest, ITEM_SPECTRUM_DAGGER, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 43:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_DARK_MACE, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_MAGIC_SWORD, 1, true, false);
                        player->StoreNewItem(dest, ITEM_DARK_MACE, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 44:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_DEVASTATION_AXE, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_MAGIC_SWORD, 1, true, false);
                        player->StoreNewItem(dest, ITEM_DEVASTATION_AXE, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 45:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_DEVASTATION_SWORD, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_MAGIC_SWORD, 1, true, false);
                        player->StoreNewItem(dest, ITEM_DEVASTATION_SWORD, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 46:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_FORTIFIED_SWORD, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_MAGIC_SWORD, 1, true, false);
                        player->StoreNewItem(dest, ITEM_FORTIFIED_SWORD, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 47:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_VENGEFUL_MACE, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_SAVAGE_SWORD, 1, true, false);
                        player->StoreNewItem(dest, ITEM_VENGEFUL_MACE, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 48:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_BRUTAL_AXE, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_SAVAGE_SWORD, 1, true, false);
                        player->StoreNewItem(dest, ITEM_BRUTAL_AXE, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 49:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_MAGIC_WALL, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_JUSTICE_WALL, 1, true, false);
                        player->StoreNewItem(dest, ITEM_MAGIC_WALL, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 50:
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_JUSTICE_WALL, 1);

                    if (msg == EQUIP_ERR_OK)
                    {
					    player->DestroyItemCount(ITEM_MAGIC_WALL, 1, true, false);
                        player->StoreNewItem(dest, ITEM_JUSTICE_WALL, true);
                    }

                    CharacterDatabase.PExecute("UPDATE character_donor_weapon_changes SET attempts = attempts + 1 WHERE guid = '%u'", player->GetGUIDLow());
                    player->CLOSE_GOSSIP_MENU(); 
                    break;
                }
            case GOSSIP_ACTION_INFO_DEF + 51:
                player->CLOSE_GOSSIP_MENU(); 
                break;
        }

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->HasItemCount(ITEM_MAGIC_SWORD, 1) || player->HasItemCount(ITEM_FORTIFIED_SWORD, 1) || player->HasItemCount(ITEM_DEVASTATION_AXE, 1) || player->HasItemCount(ITEM_DEVASTATION_SWORD, 1) || player->HasItemCount(ITEM_SPECTRUM_DAGGER, 1) || player->HasItemCount(ITEM_MAGIC_WALL, 1) || player->HasItemCount(ITEM_JUSTICE_WALL, 1) || player->HasItemCount(ITEM_MIRKWOOD_BOW_R, 1) || player->HasItemCount(ITEM_VENGEFUL_MACE, 1) || player->HasItemCount(ITEM_GREATEST_STAFF, 1) || player->HasItemCount(ITEM_FERAL_STAFF, 1) || player->HasItemCount(ITEM_BRUTAL_AXE, 1) || player->HasItemCount(ITEM_SAVAGE_SWORD, 1) || player->HasItemCount(ITEM_DARK_MACE, 1) || player->HasItemCount(ITEM_ROSARIO_GUN_R, 1))
        {
            QueryResult result = CharacterDatabase.PQuery("SELECT guid, attempts FROM character_donor_weapon_changes WHERE guid='%u' AND attempts<2", player->GetGUIDLow());

            if (result)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_WEAPONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
            else
            {
                QueryResult result = CharacterDatabase.PQuery("SELECT guid, attempts FROM character_donor_weapon_changes WHERE guid='%u' AND attempts>=2", player->GetGUIDLow());

                if (result)
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_NO_AVAILABLE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 51);
                    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
                else
                {
                    CharacterDatabase.PExecute("INSERT INTO character_donor_weapon_changes (guid, attempts) VALUES ('%u','0')", player->GetGUIDLow());

                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_WEAPONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
            }
        }
        else
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_NO_ITEM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 51);
            player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }

        return true;
    }
};

void AddSC_donor()
{
    new npc_donor_service();
}