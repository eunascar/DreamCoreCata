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
#include "emerald_dream.h"

static Position Locations[] =
{
    {2657.830811f, -3290.226074f, 97.852287f, 2.857381f},      //Punto Inicial
    {-3146.189453f, -3165.305664f, 148.756790f, 6.277785f},    //Laberinto
    {-3224.549805f, -2815.597900f, 124.389885f, 3.153372f},    //Drake Zone
    {-3009.255127f, -3151.516846f, 143.045319f, 1.623513f}     //Final Laberinto
};

#define MAX_ENCOUNTER      7
#define PYRO               200
#define KRITYUS            201
#define HYOTON             202
#define FIREMIST           203
#define SPELL_PARACHUTE    66516

class instance_emerald_dream : public InstanceMapScript
{
    public:
        instance_emerald_dream()
            : InstanceMapScript("instance_emerald_dream", 169)
        {
        }
        
        struct instance_emerald_dream_InstanceMapScript : public InstanceScript
        {
            instance_emerald_dream_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
            {
                uiBossCounter           = 0;
                uiAnnouncerGUID         = 0;
                uiHydroGUID             = 0;
                uiRagnarosGUID          = 0;
                uiRagnarosStaticGUID    = 0;
                uiKalecgosGUID          = 0;
                uiIsidorusGUID          = 0;
                uiHyotonGUID            = 0;
                uiFiremistGUID          = 0;
                uiKrityusGUID           = 0;
                uiUmbraGUID             = 0;
                uiEmeraldDoor           = 0;
                memset(uiEncounter, 0, sizeof(uiEncounter));
            };

            void OnCreatureCreate(Creature* creature)
            {
                switch(creature->GetEntry())
                {
                    case NPC_HYOTON:
                        uiHyotonGUID = creature->GetGUID();
                        creature->SetReactState(REACT_PASSIVE);
                        creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        creature->SetVisible(false);
                        break;
                    case NPC_FIREMIST:
                        uiFiremistGUID = creature->GetGUID();
                        creature->SetReactState(REACT_PASSIVE);
                        creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        creature->SetVisible(false);
                        break;
                    case NPC_KRITYUS:
                        uiKrityusGUID = creature->GetGUID();
                        creature->SetReactState(REACT_PASSIVE);
                        creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        creature->SetVisible(false);
                        break;
                    case NPC_UMBRA:
                        uiUmbraGUID = creature->GetGUID();
                        creature->SetReactState(REACT_PASSIVE);
                        creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        creature->SetVisible(false);
                        break;
                    case NPC_ANNOUNCER:
                        uiAnnouncerGUID = creature->GetGUID();
                        creature->SetVisible(false);
                        break;
                    case NPC_HYDRO:
                        uiHydroGUID = creature->GetGUID();
                        creature->SetVisible(false);
                        break;
                    case NPC_RAGNAROS:
                        uiRagnarosGUID = creature->GetGUID();
                        creature->SetVisible(false);
                        break;
                    case NPC_RAGNAROSSTATIC:
                        uiRagnarosStaticGUID = creature->GetGUID();
                        creature->SetVisible(false);
                        break;
                    case NPC_KALECGOS:
                        uiKalecgosGUID = creature->GetGUID();
                        creature->SetVisible(false);
                        break;
                    case NPC_ISIDORUS:
                        uiIsidorusGUID = creature->GetGUID();
                        creature->SetVisible(false);
                        break;
                }
            }

            void OnGameObjectCreate(GameObject* go)
    	    {
                switch(go->GetEntry())
                {
                    case GAMEOBJECT_EMERALD_DOOR:
                        uiEmeraldDoor = go->GetGUID();
                        go->SetFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
                        HandleGameObject(NULL,false,go);
                        break;
    		    }
            }

            void SetData(uint32 type, uint32 data)
            {
                switch(type)
                {
                    case DATA_HYOTON_EVENT:
                        uiEncounter[DATA_HYOTON_EVENT] = data;

                        if(data == 4)
                        {
                            if (Creature* pHyoton = instance->GetCreature(uiHyotonGUID))
                            {
                                pHyoton->SetReactState(REACT_AGGRESSIVE);
                                pHyoton->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                pHyoton->SetVisible(true);
                            }
                        }
                        break;
                    case DATA_FIREMIST_EVENT:
                        uiEncounter[DATA_FIREMIST_EVENT] = data;
                        if (data == DONE)
                        {
                            if (Creature* pKalecgos = instance->GetCreature(uiKalecgosGUID))
                            {
                                pKalecgos->SetReactState(REACT_AGGRESSIVE);
                                pKalecgos->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                pKalecgos->SetVisible(true);
                            }
                        }
                        break;
                    case DATA_KRITYUS_EVENT:
                        uiEncounter[DATA_KRITYUS_EVENT] = data;
                        if(data == 2)
                        {
                            if (Creature* pKrityus = instance->GetCreature(uiKrityusGUID))
                            {
                                pKrityus->SetReactState(REACT_AGGRESSIVE);
                                pKrityus->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                pKrityus->SetVisible(true);
                            }
                        }
                        
                        if (data == DONE)
                        {
                            if (Creature* pIsidorus = instance->GetCreature(uiIsidorusGUID))
                            {
                                pIsidorus->SetReactState(REACT_AGGRESSIVE);
                                pIsidorus->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                pIsidorus->SetVisible(true);
                            }
                        }
                        break;
                    case DATA_UMBRA_EVENT:
                        uiEncounter[DATA_UMBRA_EVENT] = data;
                        break;
                    case DATA_AQUA_GHOST:
                        uiEncounter[DATA_AQUA_GHOST] = data;
                        if (data >= 5 && uiEncounter[DATA_AQUA_LEKION] >= 5)
                        {
                            if (Creature* pAnnouncer = instance->GetCreature(uiAnnouncerGUID))
                                pAnnouncer->SetVisible(true);
                             
                            if (Creature* pHydro = instance->GetCreature(uiHydroGUID))
                                pHydro->SetVisible(true);
 
                            SetData(DATA_HYOTON_EVENT, 2);
                        }
                        break;
                    case DATA_AQUA_LEKION:
                        uiEncounter[DATA_AQUA_LEKION] = data;
                        if (uiEncounter[DATA_AQUA_GHOST] >= 5 && data >= 5)
                        {
                            if (Creature* pAnnouncer = instance->GetCreature(uiAnnouncerGUID))
                                pAnnouncer->SetVisible(true);
                             
                            if (Creature* pHydro = instance->GetCreature(uiHydroGUID))
                                pHydro->SetVisible(true);

                            SetData(DATA_HYOTON_EVENT, 2);
                        }
                        break;
                    case DATA_PYRO_DRAKE:
                        uiEncounter[DATA_PYRO_DRAKE] = data;
                        if (data == 16)
                        {
                            HandleGameObject(uiEmeraldDoor,true);
                            if (Creature* pRagnaros = instance->GetCreature(uiRagnarosGUID))
                                pRagnaros->SetVisible(true);
                            if (Creature* pRagnarosStatic = instance->GetCreature(uiRagnarosStaticGUID))
                                pRagnarosStatic->SetVisible(true);
                        }
                        if (data == 2)
                        {
                            if (Creature* pFiremist = instance->GetCreature(uiFiremistGUID))
                            {
                                pFiremist->SetReactState(REACT_AGGRESSIVE);
                                pFiremist->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                pFiremist->SetVisible(true);
                            }
                        }
                        break;
                }
                
                if (data == DONE || data == IN_PROGRESS || data == 2 || data == 5 || data == 16)
                    SaveToDB();
            }

            uint32 GetData(uint32 type)
            {
                switch (type)
                {
                    case DATA_HYOTON_EVENT:
                    case DATA_FIREMIST_EVENT:
                    case DATA_KRITYUS_EVENT:
                    case DATA_UMBRA_EVENT:
                    case DATA_AQUA_GHOST:
                    case DATA_AQUA_LEKION:
                    case DATA_PYRO_DRAKE:
                        return uiEncounter[type];
                }
    		return 0;
            }

            uint64 GetData64(uint32 type)
            {
                switch (type)
                {
                    case DATA_HYOTON:            return uiHyotonGUID;
                    case DATA_FIREMIST:          return uiFiremistGUID;
                    case DATA_KRITYUS:           return uiKrityusGUID;
                    case DATA_UMBRA:             return uiUmbraGUID;
    		    }		
                return 0;
            }

            std::string GetSaveData()
            {
                 OUT_SAVE_INST_DATA;

                 std::ostringstream saveStream;
				 saveStream << "E D " << uiEncounter[0] << " " << uiEncounter[1] << " " << uiEncounter[2] << " " << uiEncounter[3] << " " << uiEncounter[4] << " " << uiEncounter[5] << " " << uiEncounter[6];

                 str_data = saveStream.str();

                 OUT_SAVE_INST_DATA_COMPLETE;
                 return str_data;
             }

             void Load(const char* in)
             {
                 if (!in)
                 {
                     OUT_LOAD_INST_DATA_FAIL;
                     return;
                 }

                 OUT_LOAD_INST_DATA(in);

                 char dataHead1, dataHead2;
                 uint16 data0, data1, data2, data3, data4, data5, data6;

                 std::istringstream loadStream(in);
                 loadStream >> dataHead1 >> dataHead2 >> data0 >> data1 >> data2 >> data3 >> data4 >> data5 >> data6;

                 if (dataHead1 == 'E' && dataHead2 == 'D')
                 {
                     uiEncounter[0] = data0;
                     uiEncounter[1] = data1;
                     uiEncounter[2] = data2;
                     uiEncounter[3] = data3;
                     uiEncounter[4] = data4;
                     uiEncounter[5] = data5;
                     uiEncounter[6] = data6;

                     for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                         if (uiEncounter[i] == IN_PROGRESS)
                             uiEncounter[i] = NOT_STARTED;

                 } else OUT_LOAD_INST_DATA_FAIL;

                 OUT_LOAD_INST_DATA_COMPLETE;
             }
          
          private:
               uint16 uiEncounter[MAX_ENCOUNTER];
               std::string str_data;

               uint32 uiBossCounter;
               
               uint64 uiAnnouncerGUID;
               uint64 uiHydroGUID;
               uint64 uiRagnarosGUID;
               uint64 uiRagnarosStaticGUID;
               uint64 uiKalecgosGUID;
               uint64 uiIsidorusGUID; 
               uint64 uiHyotonGUID;
               uint64 uiFiremistGUID;
               uint64 uiKrityusGUID;
               uint64 uiUmbraGUID;
               uint64 uiEmeraldDoor;
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_emerald_dream_InstanceMapScript(map);
        }
};

class npc_emerald_announcer : public CreatureScript
{
    public:
        npc_emerald_announcer() : CreatureScript("npc_emerald_announcer") { }

        struct npc_emerald_announcerAI : public ScriptedAI
        {
    	    npc_emerald_announcerAI(Creature* creature) : ScriptedAI(creature)
    	    {
    	        instance = me->GetInstanceScript();
    	    }
         
            void UpdateAI(const uint32 /*diff*/) { }

        private:
            InstanceScript* instance;
        };

        bool OnGossipHello(Player* player, Creature* creature)
        {
            InstanceScript* instance = creature->GetInstanceScript();
            if (!instance)
                return false;

            if (instance->GetData(DATA_HYOTON_EVENT) == DONE || player->isGameMaster())
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Siguiente Desafio: Pyro Emerald Legion", GOSSIP_SENDER_MAIN, PYRO);

            if ((instance->GetData(DATA_HYOTON_EVENT) == DONE && instance->GetData(DATA_FIREMIST_EVENT) == DONE && instance->GetData(DATA_KRITYUS_EVENT) == DONE && instance->GetData(DATA_UMBRA_EVENT) == DONE) || player->isGameMaster())
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Evento Especial (Aun en Desarrollo)", GOSSIP_SENDER_MAIN, SPECIAL);
            
            player->SEND_GOSSIP_MENU(10600, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
        {
            player->PlayerTalkClass->ClearMenus();
            if (uiSender != GOSSIP_SENDER_MAIN)
                return false;
            if (!player->getAttackers().empty())
                return false;

            switch(uiAction)
            {
	        case PYRO:
                    player->TeleportTo(player->GetMapId(),Locations[1].GetPositionX(),Locations[1].GetPositionY(),Locations[1].GetPositionZ(),Locations[1].GetOrientation());
                    player->CLOSE_GOSSIP_MENU();
                    creature->CastSpell(player,SPELL_PARACHUTE, true);
                    break;
                case SPECIAL:                   
                    player->CLOSE_GOSSIP_MENU();
                    break;
            }
            return true;
        }

        CreatureAI* GetAI(Creature* creature) const
        {
    	    return new npc_emerald_announcerAI(creature);
        }
};

class npc_emerald_hydro : public CreatureScript
{
    public:
        npc_emerald_hydro() : CreatureScript("npc_emerald_hydro") { }

        struct npc_emerald_hydroAI : public ScriptedAI
        {
    	    npc_emerald_hydroAI(Creature* creature) : ScriptedAI(creature)
    	    {
    	        instance = me->GetInstanceScript();
    	    }
           
            void UpdateAI(const uint32 /*diff*/) { }

        private:
            InstanceScript* instance;
        };

        bool OnGossipHello(Player* player, Creature* creature)
        {
            InstanceScript* instance = creature->GetInstanceScript();
            if (!instance)
                return false;

            if (instance->GetData(DATA_HYOTON_EVENT) == 2 || player->isGameMaster())
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Enfrentar a Hyoton: Boss de la Legion Aqua", GOSSIP_SENDER_MAIN, HYOTON);
            
            player->SEND_GOSSIP_MENU(10600, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
        {
            InstanceScript* instance = creature->GetInstanceScript();
            player->PlayerTalkClass->ClearMenus();
            if (uiSender != GOSSIP_SENDER_MAIN)
                return false;
            if (!player->getAttackers().empty())
                return false;

            switch(uiAction)
            {
	        case HYOTON:
                    instance->SetData(DATA_HYOTON_EVENT,4);
                    player->CLOSE_GOSSIP_MENU();
                    break;
            }
            return true;
        }

        CreatureAI* GetAI(Creature* creature) const
        {
    	    return new npc_emerald_hydroAI(creature);
        }
};

class npc_emerald_ragnaros : public CreatureScript
{
    public:
        npc_emerald_ragnaros() : CreatureScript("npc_emerald_ragnaros") { }

        struct npc_emerald_ragnarosAI : public ScriptedAI
        {
    	    npc_emerald_ragnarosAI(Creature* creature) : ScriptedAI(creature)
    	    {
    	        instance = me->GetInstanceScript();
    	    }
           
            void UpdateAI(const uint32 /*diff*/) { }

        private:
            InstanceScript* instance;
        };

        bool OnGossipHello(Player* player, Creature* creature)
        {
            InstanceScript* instance = creature->GetInstanceScript();
            if (!instance)
                return false;

            if (instance->GetData(DATA_PYRO_DRAKE) == 16 || instance->GetData(DATA_PYRO_DRAKE) == 2 || player->isGameMaster())
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Enfrentar a Firemist: Boss de la Legion de Fuego", GOSSIP_SENDER_MAIN, FIREMIST);
            
            player->SEND_GOSSIP_MENU(10600, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
        {
            InstanceScript* instance = creature->GetInstanceScript();
            player->PlayerTalkClass->ClearMenus();
            if (uiSender != GOSSIP_SENDER_MAIN)
                return false;
            if (!player->getAttackers().empty())
                return false;

            switch(uiAction)
            {
	            case FIREMIST:
                    if (instance->GetData(DATA_PYRO_DRAKE) == 2)
                    {
                        player->TeleportTo(player->GetMapId(),Locations[0].GetPositionX(),Locations[0].GetPositionY(),Locations[0].GetPositionZ(),Locations[0].GetOrientation());
                    }
                    else
                    {
                        player->TeleportTo(player->GetMapId(),Locations[0].GetPositionX(),Locations[0].GetPositionY(),Locations[0].GetPositionZ(),Locations[0].GetOrientation());		
                        instance->SetData(DATA_PYRO_DRAKE,2);
                    }
                    player->CLOSE_GOSSIP_MENU();
                    break;
            }
            return true;
        }

        CreatureAI* GetAI(Creature* creature) const
        {
    	    return new npc_emerald_ragnarosAI(creature);
        }
};

class npc_emerald_kalecgos : public CreatureScript
{
    public:
        npc_emerald_kalecgos() : CreatureScript("npc_emerald_kalecgos") { }

        struct npc_emerald_kalecgosAI : public ScriptedAI
        {
    	    npc_emerald_kalecgosAI(Creature* creature) : ScriptedAI(creature)
    	    {
    	        instance = me->GetInstanceScript();
    	    }
           
            void UpdateAI(const uint32 /*diff*/) { }

        private:
            InstanceScript* instance;
        };

        bool OnGossipHello(Player* player, Creature* creature)
        {
            InstanceScript* instance = creature->GetInstanceScript();
            if (!instance)
                return false;

            if ((instance->GetData(DATA_HYOTON_EVENT) == DONE && instance->GetData(DATA_FIREMIST_EVENT) == DONE && instance->GetData(DATA_KRITYUS_EVENT) == NOT_STARTED) || player->isGameMaster())
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Enfrentar a Krityus: Boss de la Legion del Aire", GOSSIP_SENDER_MAIN, KRITYUS);
            
            player->SEND_GOSSIP_MENU(10600, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
        {
            InstanceScript* instance = creature->GetInstanceScript();
            player->PlayerTalkClass->ClearMenus();
            if (uiSender != GOSSIP_SENDER_MAIN)
                return false;

            if (!player->getAttackers().empty())
                return false;

            switch(uiAction)
            {
	            case KRITYUS:
                    instance->SetData(DATA_KRITYUS_EVENT,2);
                    player->CLOSE_GOSSIP_MENU();
                    break;
            }
            return true;
        }

        CreatureAI* GetAI(Creature* creature) const
        {
    	    return new npc_emerald_kalecgosAI(creature);
        }
};

class go_emerald_pyro_legion : public GameObjectScript
{
public:
    go_emerald_pyro_legion() : GameObjectScript("go_emerald_pyro_legion") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {   
        InstanceScript* instance = go->GetInstanceScript();
            if (!instance)
                return false;

            if (instance->GetData(DATA_PYRO_DRAKE) == 16)
            { 
                player->TeleportTo(player->GetMapId(),Locations[3].GetPositionX(),Locations[3].GetPositionY(),Locations[3].GetPositionZ(),Locations[3].GetOrientation());
                go->CastSpell(player,SPELL_PARACHUTE);
            }
            else
            {
                player->TeleportTo(player->GetMapId(),Locations[2].GetPositionX(),Locations[2].GetPositionY(),Locations[2].GetPositionZ(),Locations[2].GetOrientation());
            }
            
        return true;
    }
};

void AddSC_instance_emerald_dream()
{
    new instance_emerald_dream();
    new npc_emerald_announcer();
    new npc_emerald_hydro();
    new npc_emerald_ragnaros();
    new npc_emerald_kalecgos();
    new go_emerald_pyro_legion();
}
