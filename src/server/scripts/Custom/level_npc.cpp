/*
 * Copyright (C) 2010 Chronos Server <http://chronoserverwow.net/>
 * Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
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

enum eOptions
{
    OPTION_LEVEL         = 1000,
    OPTION_VISIBILITY    = 1001,
    OPTION_EXIT          = 1002
};

#define GOSSIP_GET_LEVEL     "Obtener Nivel 80."
#define GOSSIP_MAX_LEVEL     "Ya eres nivel 80."
#define GOSSIP_EXIT          "No estoy interesado."

class level_npc : public CreatureScript
{
    public:
        level_npc() : CreatureScript("level_npc") { }

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            if (pPlayer->getLevel() == 80)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_MAX_LEVEL, GOSSIP_SENDER_MAIN, OPTION_EXIT);
            else 
            {                     
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_GET_LEVEL, GOSSIP_SENDER_MAIN, OPTION_LEVEL);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_EXIT, GOSSIP_SENDER_MAIN, OPTION_EXIT);
            }

            pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());
            
            return true;
        }

        bool OnGossipSelect(Player* pPlayer, Creature* /*pCreature*/, uint32 uiSender, uint32 uiAction)
        {
            if (uiSender != GOSSIP_SENDER_MAIN) return true;
            if (!pPlayer->getAttackers().empty()) return true;

            switch(uiAction)
            {
                case OPTION_LEVEL:
                    pPlayer->SetLevel(80);
                    pPlayer->resetTalents(true);
                    pPlayer->SendTalentsInfoData(false);
                    pPlayer->InitStatsForLevel(true);
                    pPlayer->InitGlyphsForLevel();
                    pPlayer->SaveToDB();
                    pPlayer->CLOSE_GOSSIP_MENU(); 
                    break;
                case OPTION_EXIT:
                    pPlayer->CLOSE_GOSSIP_MENU(); 
                    break;
            }
            return true;
        }
};

void AddSC_level_npc()
{
    new level_npc();
}
