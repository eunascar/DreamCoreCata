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

static Position Locations[] =
{
    {985.333740f, 1057.043457f, 359.967f, 3.702181f},          //Nexus Portal
    {3874.884521f, 6984.436523f, 106.874405f, 0.190667f},      //Orb of the Nexus
    {3874.442383f, 6982.068848f, 152.780716f, 6.008080f},      //Exit Portal
    {2734.322021f, -3318.330078f, 101.534485f, 5.929857f},     //Emerald Crystal
    {5828.488281f, 474.376862f, 658.325623f, 4.245950f},       //Emerald Exit Portal
    /*{f, f, f, f},    //Zona Drake
    {f, f, f, f},    //Zona Final de Laberinto*/
};

#define NORTHREND_MAP     571
#define EMERALD_DREAM_MAP 169

class go_nexus_portal : public GameObjectScript
{
public:
    go_nexus_portal() : GameObjectScript("go_nexus_portal") { }

    bool OnGossipHello(Player* pPlayer, GameObject* /*pGO*/)
    {   
         pPlayer->TeleportTo(pPlayer->GetMapId(),Locations[0].GetPositionX(),Locations[0].GetPositionY(),Locations[0].GetPositionZ(),Locations[0].GetOrientation());
        return true;
    }
};

class go_orb_of_the_nexus : public GameObjectScript
{
public:
    go_orb_of_the_nexus() : GameObjectScript("go_orb_of_the_nexus") { }

    bool OnGossipHello(Player* pPlayer, GameObject* /*pGO*/)
    {
        pPlayer->TeleportTo(NORTHREND_MAP,Locations[1].GetPositionX(),Locations[1].GetPositionY(),Locations[1].GetPositionZ(),Locations[1].GetOrientation());
        return true;
    }
};

class go_exit_portal : public GameObjectScript
{
public:
    go_exit_portal() : GameObjectScript("go_exit_portal") { }

    bool OnGossipHello(Player* pPlayer, GameObject* /*pGO*/)
    {
        pPlayer->TeleportTo(NORTHREND_MAP,Locations[2].GetPositionX(),Locations[2].GetPositionY(),Locations[2].GetPositionZ(),Locations[2].GetOrientation());
        return true;
    }
};

class go_emerald_crystal : public GameObjectScript
{
public:
    go_emerald_crystal() : GameObjectScript("go_emerald_crystal") { }

    bool OnGossipHello(Player* pPlayer, GameObject* /*pGO*/)
    {   
        pPlayer->TeleportTo(EMERALD_DREAM_MAP,Locations[3].GetPositionX(),Locations[3].GetPositionY(),Locations[3].GetPositionZ(),Locations[3].GetOrientation());
        return true;
    }
};

class go_emerald_exit_portal : public GameObjectScript
{
public:
    go_emerald_exit_portal() : GameObjectScript("go_emerald_exit_portal") { }

    bool OnGossipHello(Player* pPlayer, GameObject* /*pGO*/)
    {   
        pPlayer->TeleportTo(NORTHREND_MAP,Locations[4].GetPositionX(),Locations[4].GetPositionY(),Locations[4].GetPositionZ(),Locations[4].GetOrientation());
        return true;
    }
};

void AddSC_gameobject_custom()
{
    new go_orb_of_the_nexus();
    new go_nexus_portal();
    new go_exit_portal();
    new go_emerald_crystal();
    new go_emerald_exit_portal();
}
