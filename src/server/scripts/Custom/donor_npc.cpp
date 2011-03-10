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

#define GOSSIP_ACTIVATION      "Activar Cuenta Premium"
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

enum Weapons
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

/*enum DeathKnightArmor
{
};

enum DruidArmor
{
};

enum HunterArmor
{
};

enum MageArmor
{
};

enum PaladinArmor
{
};

enum PriestArmor
{
};

enum RogueArmor
{
};

enum ShamanArmor
{
};

enum WarlockArmor
{
};

enum WarriorArmor
{
};*/

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
                LoginDatabase.PExecute("INSERT INTO account_premium (id, active) VALUES ('%u','1')", player->GetSession()->GetAccountId());
                player->CLOSE_GOSSIP_MENU(); 
                break;
            case GOSSIP_ACTION_INFO_DEF + 52:
                player->CLOSE_GOSSIP_MENU(); 
                break;
        }

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        QueryResult result = LoginDatabase.PQuery("SELECT id FROM account_premium WHERE id='%u' AND active=1", player->GetSession()->GetAccountId());

        if (result)
        {
            QueryResult result = CharacterDatabase.PQuery("SELECT guid, attempts FROM character_donor_weapon_changes WHERE guid='%u' AND attempts<2", player->GetGUIDLow());

            if (result || player->isGameMaster())
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_WEAPONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
            else
            {
                QueryResult result = CharacterDatabase.PQuery("SELECT guid, attempts FROM character_donor_weapon_changes WHERE guid='%u' AND attempts>=2", player->GetGUIDLow());

                if (result)
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_NO_AVAILABLE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 52);
                    player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
                else
                {
                    if (player->HasItemCount(ITEM_MAGIC_SWORD, 1) || player->HasItemCount(ITEM_FORTIFIED_SWORD, 1) || player->HasItemCount(ITEM_DEVASTATION_AXE, 1) || player->HasItemCount(ITEM_DEVASTATION_SWORD, 1) || player->HasItemCount(ITEM_SPECTRUM_DAGGER, 1) || player->HasItemCount(ITEM_MAGIC_WALL, 1) || player->HasItemCount(ITEM_JUSTICE_WALL, 1) || player->HasItemCount(ITEM_MIRKWOOD_BOW_R, 1) || player->HasItemCount(ITEM_VENGEFUL_MACE, 1) || player->HasItemCount(ITEM_GREATEST_STAFF, 1) || player->HasItemCount(ITEM_FERAL_STAFF, 1) || player->HasItemCount(ITEM_BRUTAL_AXE, 1) || player->HasItemCount(ITEM_SAVAGE_SWORD, 1) || player->HasItemCount(ITEM_DARK_MACE, 1) || player->HasItemCount(ITEM_ROSARIO_GUN_R, 1))
                    {
                        CharacterDatabase.PExecute("INSERT INTO character_donor_weapon_changes (guid, attempts) VALUES ('%u','0')", player->GetGUIDLow());

                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_WEAPONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                        player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                    }
                }
            }
        }
        else
        {
                //Weapons
            if (player->HasItemCount(ITEM_MAGIC_SWORD, 1) || player->HasItemCount(ITEM_FORTIFIED_SWORD, 1) || player->HasItemCount(ITEM_DEVASTATION_AXE, 1) || player->HasItemCount(ITEM_DEVASTATION_SWORD, 1) || player->HasItemCount(ITEM_SPECTRUM_DAGGER, 1) || player->HasItemCount(ITEM_MAGIC_WALL, 1) || player->HasItemCount(ITEM_JUSTICE_WALL, 1) || player->HasItemCount(ITEM_MIRKWOOD_BOW_R, 1) || player->HasItemCount(ITEM_VENGEFUL_MACE, 1) || player->HasItemCount(ITEM_GREATEST_STAFF, 1) || player->HasItemCount(ITEM_FERAL_STAFF, 1) || player->HasItemCount(ITEM_BRUTAL_AXE, 1) || player->HasItemCount(ITEM_SAVAGE_SWORD, 1) || player->HasItemCount(ITEM_DARK_MACE, 1) || player->HasItemCount(ITEM_ROSARIO_GUN_R, 1) ||
                // Armor
                player->HasItemCount(200000, 1) || player->HasItemCount(200001, 1) || player->HasItemCount(200002, 1) || player->HasItemCount(200003, 1) || player->HasItemCount(200004, 1) || player->HasItemCount(200005, 1) || player->HasItemCount(200006, 1) || player->HasItemCount(200007, 1) ||
                player->HasItemCount(200008, 1) || player->HasItemCount(200009, 1) || player->HasItemCount(200010, 1) || player->HasItemCount(200011, 1) || player->HasItemCount(200012, 1) || player->HasItemCount(200013, 1) || player->HasItemCount(200014, 1) || player->HasItemCount(200015, 1) ||
                player->HasItemCount(200016, 1) || player->HasItemCount(200017, 1) || player->HasItemCount(200018, 1) || player->HasItemCount(200019, 1) || player->HasItemCount(200020, 1) || player->HasItemCount(200021, 1) || player->HasItemCount(200022, 1) || player->HasItemCount(200023, 1) ||
                player->HasItemCount(200024, 1) || player->HasItemCount(200025, 1) || player->HasItemCount(200026, 1) || player->HasItemCount(200027, 1) || player->HasItemCount(200028, 1) || player->HasItemCount(200029, 1) || player->HasItemCount(200030, 1) || player->HasItemCount(200031, 1) ||
                player->HasItemCount(200032, 1) || player->HasItemCount(200033, 1) || player->HasItemCount(200034, 1) || player->HasItemCount(200035, 1) || player->HasItemCount(200036, 1) || player->HasItemCount(200037, 1) || player->HasItemCount(200038, 1) || player->HasItemCount(200039, 1) ||
                player->HasItemCount(200040, 1) || player->HasItemCount(200041, 1) || player->HasItemCount(200042, 1) || player->HasItemCount(200043, 1) || player->HasItemCount(200044, 1) || player->HasItemCount(200045, 1) || player->HasItemCount(200046, 1) || player->HasItemCount(200047, 1) ||
                player->HasItemCount(200048, 1) || player->HasItemCount(200049, 1) || player->HasItemCount(200050, 1) || player->HasItemCount(200051, 1) || player->HasItemCount(200052, 1) || player->HasItemCount(200053, 1) || player->HasItemCount(200054, 1) || player->HasItemCount(200055, 1) ||
                player->HasItemCount(200056, 1) || player->HasItemCount(200057, 1) || player->HasItemCount(200058, 1) || player->HasItemCount(200059, 1) || player->HasItemCount(200060, 1) || player->HasItemCount(200061, 1) || player->HasItemCount(200062, 1) || player->HasItemCount(200063, 1) ||
                player->HasItemCount(200064, 1) || player->HasItemCount(200065, 1) || player->HasItemCount(200066, 1) || player->HasItemCount(200067, 1) || player->HasItemCount(200068, 1) || player->HasItemCount(200069, 1) || player->HasItemCount(200070, 1) || player->HasItemCount(200071, 1) ||
                player->HasItemCount(200072, 1) || player->HasItemCount(200073, 1) || player->HasItemCount(200074, 1) || player->HasItemCount(200075, 1) || player->HasItemCount(200076, 1) || player->HasItemCount(200077, 1) || player->HasItemCount(200078, 1) || player->HasItemCount(200079, 1) ||
                player->HasItemCount(200080, 1) || player->HasItemCount(200081, 1) || player->HasItemCount(200082, 1) || player->HasItemCount(200083, 1) || player->HasItemCount(200084, 1) || player->HasItemCount(200085, 1) || player->HasItemCount(200086, 1) || player->HasItemCount(200087, 1) ||
                player->HasItemCount(200088, 1) || player->HasItemCount(200089, 1) || player->HasItemCount(200090, 1) || player->HasItemCount(200091, 1) || player->HasItemCount(200092, 1) || player->HasItemCount(200093, 1) || player->HasItemCount(200094, 1) || player->HasItemCount(200095, 1) ||
                player->HasItemCount(200096, 1) || player->HasItemCount(200097, 1) || player->HasItemCount(200098, 1) || player->HasItemCount(200099, 1) || player->HasItemCount(200100, 1) || player->HasItemCount(200101, 1) || player->HasItemCount(200102, 1) || player->HasItemCount(200103, 1) ||
                player->HasItemCount(200104, 1) || player->HasItemCount(200105, 1) || player->HasItemCount(200106, 1) || player->HasItemCount(200107, 1) || player->HasItemCount(200108, 1) || player->HasItemCount(200109, 1) || player->HasItemCount(200110, 1) || player->HasItemCount(200111, 1) ||
                player->HasItemCount(200112, 1) || player->HasItemCount(200113, 1) || player->HasItemCount(200114, 1) || player->HasItemCount(200115, 1) || player->HasItemCount(200116, 1) || player->HasItemCount(200117, 1) || player->HasItemCount(200118, 1) || player->HasItemCount(200119, 1) ||
                player->HasItemCount(200120, 1) || player->HasItemCount(200121, 1) || player->HasItemCount(200122, 1) || player->HasItemCount(200123, 1) || player->HasItemCount(200124, 1) || player->HasItemCount(200125, 1) || player->HasItemCount(200126, 1) || player->HasItemCount(200127, 1) ||
                player->HasItemCount(200128, 1) || player->HasItemCount(200129, 1) || player->HasItemCount(200130, 1) || player->HasItemCount(200131, 1) || player->HasItemCount(200132, 1) || player->HasItemCount(200133, 1) || player->HasItemCount(200134, 1) || player->HasItemCount(200135, 1) ||
                player->HasItemCount(200136, 1) || player->HasItemCount(200137, 1) || player->HasItemCount(200138, 1) || player->HasItemCount(200139, 1) || player->HasItemCount(200140, 1) || player->HasItemCount(200141, 1) || player->HasItemCount(200142, 1) || player->HasItemCount(200143, 1) ||
                player->HasItemCount(200144, 1) || player->HasItemCount(200145, 1) || player->HasItemCount(200146, 1) || player->HasItemCount(200147, 1) || player->HasItemCount(200148, 1) || player->HasItemCount(200149, 1) || player->HasItemCount(200150, 1) || player->HasItemCount(200151, 1) ||
                // Accesories
                player->HasItemCount(200500, 1) || player->HasItemCount(200501, 1) || player->HasItemCount(200502, 1) || player->HasItemCount(200503, 1) || player->HasItemCount(200504, 1) || player->HasItemCount(200505, 1) || player->HasItemCount(200506, 1) || player->HasItemCount(200507, 1) ||
                player->HasItemCount(200508, 1) || player->HasItemCount(200509, 1) || player->HasItemCount(200510, 1) || player->HasItemCount(200511, 1) || player->HasItemCount(200512, 1) || player->HasItemCount(200513, 1) || player->HasItemCount(200514, 1) || player->HasItemCount(200515, 1) ||
                player->HasItemCount(200516, 1) || player->HasItemCount(200517, 1) || player->HasItemCount(200518, 1) || player->HasItemCount(200519, 1) || player->HasItemCount(200520, 1) || player->HasItemCount(200521, 1) || player->HasItemCount(200522, 1) || player->HasItemCount(200523, 1) ||
                player->HasItemCount(200524, 1) || player->HasItemCount(200525, 1) || player->HasItemCount(200526, 1) || player->HasItemCount(200527, 1) || player->HasItemCount(200528, 1) || player->HasItemCount(200529, 1) || player->HasItemCount(200530, 1) || player->HasItemCount(200531, 1) ||
                player->HasItemCount(200532, 1) || player->HasItemCount(200600, 1))
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ACTIVATION, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 51);
                player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
            else
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_NO_ITEM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 52);
                player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
        }

        return true;
    }
};

void AddSC_donor()
{
    new npc_donor_service();
}