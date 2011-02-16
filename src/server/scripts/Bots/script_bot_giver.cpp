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
#include <cstring>
#include "Group.h"

//This function is called when the player opens the gossip menubool
class script_bot_giver : public CreatureScript
{
	public:

		script_bot_giver()
            : CreatureScript("script_bot_giver")
        {
        }

		bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 action)
		{
			switch(sender)
			{
				case 6006: SendCreateNPCBotMenu(player, creature, action); break;
				case 6001: SendCreateNPCBot(player, creature, action); break;
			}
			return true;
		}

		bool OnGossipHello(Player *player, Creature *creature)
		{
			WorldSession *session = player->GetSession();
			uint8 count = 0;

			if (player->HaveBot())
				player->ADD_GOSSIP_ITEM(0, "Deseas abandonar tu bot?", 6001, GOSSIP_ACTION_INFO_DEF + 101);
            else
				player->ADD_GOSSIP_ITEM(0, "Reclutar un Bot", 6006, GOSSIP_ACTION_INFO_DEF + 2);

			player->PlayerTalkClass->SendGossipMenu(907, creature->GetGUID());
			return true;
		}

		void SendCreateNPCBot(Player *player, Creature *creature, uint32 action)
		{
			uint8 bot_class = 0;
			if (action == GOSSIP_ACTION_INFO_DEF + 101) //abandon bot
			{
				if (player->HaveBot())
					player->SetBotMustDie();
				player->CLOSE_GOSSIP_MENU();
				return;
			}
			else if (action == GOSSIP_ACTION_INFO_DEF + 2)
				bot_class = CLASS_WARRIOR;
			else if (action == GOSSIP_ACTION_INFO_DEF + 3)
				bot_class = CLASS_HUNTER;
			else if (action == GOSSIP_ACTION_INFO_DEF + 4)
				bot_class = CLASS_PALADIN;
			else if (action == GOSSIP_ACTION_INFO_DEF + 5)
				bot_class = CLASS_SHAMAN;
			else if (action == GOSSIP_ACTION_INFO_DEF + 6)
				bot_class = CLASS_ROGUE;
			else if (action == GOSSIP_ACTION_INFO_DEF + 7)
				bot_class = CLASS_DRUID;
			else if (action == GOSSIP_ACTION_INFO_DEF + 8)
				bot_class = CLASS_MAGE;
			else if (action == GOSSIP_ACTION_INFO_DEF + 9)
				bot_class = CLASS_PRIEST;
			else if (action == GOSSIP_ACTION_INFO_DEF + 10)
				bot_class = CLASS_WARLOCK;
			//else if (action == GOSSIP_ACTION_INFO_DEF + 11)
				//bot_class = CLASS_DEATH_KNIGHT;

			if (bot_class > 0)
			{
				//sLog->outError("script_bot_giver.SendCreateNPCBot class = %u", bot_class);
				player->CreateNPCBot(bot_class);
			}
			//else
				//creature->Say("Invalid selection.", LANG_UNIVERSAL, NULL);
			player->CLOSE_GOSSIP_MENU();
			return;
		}

		void SendCreateNPCBotMenu(Player *player, Creature *creature, uint32 action)
		{
            player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(9, "Reclutar un Guerrero", 6001, GOSSIP_ACTION_INFO_DEF + 2);
			player->ADD_GOSSIP_ITEM(9, "Reclutar un Cazador", 6001, GOSSIP_ACTION_INFO_DEF + 3);
			player->ADD_GOSSIP_ITEM(9, "Reclutar un Paladin", 6001, GOSSIP_ACTION_INFO_DEF + 4);
			player->ADD_GOSSIP_ITEM(9, "Reclutar un Chaman", 6001, GOSSIP_ACTION_INFO_DEF + 5);
			player->ADD_GOSSIP_ITEM(9, "Reclutar un Picaro", 6001, GOSSIP_ACTION_INFO_DEF + 6);
			player->ADD_GOSSIP_ITEM(3, "Reclutar un Druida", 6001, GOSSIP_ACTION_INFO_DEF + 7);
			player->ADD_GOSSIP_ITEM(3, "Reclutar un Mago", 6001, GOSSIP_ACTION_INFO_DEF + 8);
			player->ADD_GOSSIP_ITEM(3, "Reclutar un Sacerdote", 6001, GOSSIP_ACTION_INFO_DEF + 9);
			player->ADD_GOSSIP_ITEM(3, "Reclutar un Brujo", 6001, GOSSIP_ACTION_INFO_DEF + 10);
			//player->ADD_GOSSIP_ITEM(9, "Recruit a Death Knight", 1, GOSSIP_ACTION_INFO_DEF + 11);
			player->SEND_GOSSIP_MENU(907, creature->GetGUID());
		} //end SendCreateNPCBotMenu
};

//This function is called when the player clicks an option on the gossip menu
void AddSC_script_bot_giver()
{
    new script_bot_giver();
}