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

enum Locations
{
    PYRO        = 200,
    HYOTON      = 201,
    KRITYUS     = 202,
    FIREMIST    = 203
};

enum EmeraldStates
{
    EMERALD_AQUA_DONE        = 1,
    EMERALD_HYOTON_START     = 2,
    EMERALD_HYOTON_DONE      = 3,
    EMERALD_DRAKE_ZONE       = 4,
    EMERALD_DRAKE_DONE       = 5,
    EMERALD_MAZE_DONE        = 6,
    EMERALD_FIREMIST_DONE    = 7,
    EMERALD_KRITYUS_DONE     = 8,
    EMERALD_UMBRA_DONE       = 9,    
};

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
                SetBossNumber(EncounterCount);
                announcerGUID         = 0;
                hydroGUID             = 0;
                ragnarosGUID          = 0;
                ragnarosStaticGUID    = 0;
                kalecgosGUID          = 0;
                isidorusGUID          = 0;
                hyotonGUID            = 0;
                firemistGUID          = 0;
                krityusGUID           = 0;
                umbraGUID             = 0;
                emeraldDoor           = 0;
                aquaGhostData         = 0;
                aquaLekionData        = 0;
                pyroDrakeData         = 0;
                emeraldInstanceData   = NOT_STARTED;
            };

            void OnCreatureCreate(Creature* creature)
            {
                switch(creature->GetEntry())
                {
                    case NPC_HYOTON:
                        hyotonGUID = creature->GetGUID();
                        creature->SetReactState(REACT_PASSIVE);
                        creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        creature->SetVisible(false);
                        break;
                    case NPC_FIREMIST:
                        firemistGUID = creature->GetGUID();
                        creature->SetReactState(REACT_PASSIVE);
                        creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        creature->SetVisible(false);
                        break;
                    case NPC_KRITYUS:
                        krityusGUID = creature->GetGUID();
                        creature->SetReactState(REACT_PASSIVE);
                        creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        creature->SetVisible(false);
                        break;
                    case NPC_UMBRA:
                        umbraGUID = creature->GetGUID();
                        creature->SetReactState(REACT_PASSIVE);
                        creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        creature->SetVisible(false);
                        break;
                    case NPC_ANNOUNCER:
                        announcerGUID = creature->GetGUID();
                        creature->SetVisible(false);
                        break;
                    case NPC_HYDRO:
                        hydroGUID = creature->GetGUID();
                        creature->SetVisible(false);
                        break;
                    case NPC_RAGNAROS:
                        ragnarosGUID = creature->GetGUID();
                        creature->SetVisible(false);
                        break;
                    case NPC_RAGNAROSSTATIC:
                        ragnarosStaticGUID = creature->GetGUID();
                        creature->SetVisible(false);
                        break;
                    case NPC_KALECGOS:
                        kalecgosGUID = creature->GetGUID();
                        creature->SetVisible(false);
                        break;
                    case NPC_ISIDORUS:
                        isidorusGUID = creature->GetGUID();
                        creature->SetVisible(false);
                        break;
                }
            }

            void OnGameObjectCreate(GameObject* go)
    	    {
                switch(go->GetEntry())
                {
                    case GO_EMERALD_DOOR:
                        emeraldDoor = go->GetGUID();
                        go->SetFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
                        HandleGameObject(NULL,false,go);
                        break;
    		    }
            }

            bool SetBossState(uint32 type, EncounterState state)
            {
                if (!InstanceScript::SetBossState(type, state))
                    return false;

                switch(type)
                {
                    case DATA_HYOTON:
                        if (state == DONE)
                            SetData(DATA_EMERALD_DREAM, EMERALD_HYOTON_DONE);
                        break;
                    case DATA_FIREMIST:
                        if (state == DONE)
                        {
                            if (Creature* pKalecgos = instance->GetCreature(kalecgosGUID))
                            {
                                pKalecgos->SetReactState(REACT_AGGRESSIVE);
                                pKalecgos->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                pKalecgos->SetVisible(true);
                            }
                        }
                        break;
                    case DATA_KRITYUS:
                        if (state == DONE)
                        {
                            if (Creature* pIsidorus = instance->GetCreature(isidorusGUID))
                            {
                                pIsidorus->SetReactState(REACT_AGGRESSIVE);
                                pIsidorus->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                pIsidorus->SetVisible(true);
                            }
                        }
                        break;
                    case DATA_UMBRA:
                        break;
                }

                return true;
            }

            uint32 GetData(uint32 type)
            {
                switch (type)
                {
                    case DATA_AQUA_GHOST:
                        return aquaGhostData;
                    case DATA_AQUA_LEKION:
                        return aquaLekionData;
                    case DATA_PYRO_DRAKE:
                        return pyroDrakeData;
                    case DATA_EMERALD_DREAM:
                        return emeraldInstanceData;
                    default:
                        break;
                }

                return 0;
            }

            uint64 GetData64(uint32 type)
            {
                switch (type)
                {
                    case DATA_HYOTON:
                        return hyotonGUID;
                    case DATA_FIREMIST:
                        return firemistGUID;
                    case DATA_KRITYUS:
                        return krityusGUID;
                    case DATA_UMBRA:
                        return umbraGUID;
    		    }
                return 0;
            }

            void SetData(uint32 type, uint32 data)
            {
                switch (type)
                {
                    case DATA_AQUA_GHOST:
                        if (data >= 5 && GetData(DATA_AQUA_LEKION) >= 5)
                        {
                            if (Creature* pAnnouncer = instance->GetCreature(announcerGUID))
                                pAnnouncer->SetVisible(true);
                             
                            if (Creature* pHydro = instance->GetCreature(hydroGUID))
                                pHydro->SetVisible(true);
 
                            SetData(DATA_EMERALD_DREAM, EMERALD_AQUA_DONE);
                        }
                        
                        aquaGhostData = data;
                        break;
                    case DATA_AQUA_LEKION:
                        if (GetData(DATA_AQUA_GHOST) >= 5 && data >= 5)
                        {
                            if (Creature* pAnnouncer = instance->GetCreature(announcerGUID))
                                pAnnouncer->SetVisible(true);
                             
                            if (Creature* pHydro = instance->GetCreature(hydroGUID))
                                pHydro->SetVisible(true);

                            SetData(DATA_EMERALD_DREAM, EMERALD_AQUA_DONE);
                        }

                        aquaLekionData = data;
                        break;
                    case DATA_PYRO_DRAKE:
                        if (data == 4)
                            SetData(DATA_EMERALD_DREAM, EMERALD_DRAKE_DONE);
                        
                        pyroDrakeData = data;
                        break;
                    case DATA_EMERALD_DREAM:
                        switch (data)
                        {
                            case EMERALD_HYOTON_START:
                                if (Creature* pHyoton = instance->GetCreature(hyotonGUID))
                                {
                                    pHyoton->SetReactState(REACT_AGGRESSIVE);
                                    pHyoton->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                    pHyoton->SetVisible(true);
                                }
                                break;
                            case EMERALD_DRAKE_DONE:
                                HandleGameObject(emeraldDoor,true);

                                if (Creature* pRagnaros = instance->GetCreature(ragnarosGUID))
                                    pRagnaros->SetVisible(true);

                                if (Creature* pRagnarosStatic = instance->GetCreature(ragnarosStaticGUID))
                                    pRagnarosStatic->SetVisible(true);
                                break;
                            case EMERALD_MAZE_DONE:
                                if (Creature* pFiremist = instance->GetCreature(firemistGUID))
                                {
                                    pFiremist->SetReactState(REACT_AGGRESSIVE);
                                    pFiremist->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                    pFiremist->SetVisible(true);
                                }
                                break;
                            case EMERALD_FIREMIST_DONE:
                                if (Creature* pKrityus = instance->GetCreature(krityusGUID))
                                {
                                    pKrityus->SetReactState(REACT_AGGRESSIVE);
                                    pKrityus->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                    pKrityus->SetVisible(true);
                                }
                                break;
                        }

                        emeraldInstanceData = data;
                        break;
                    default:
                        break;
                }

                SaveToDB();
            }

            std::string GetSaveData()
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << "E D " << GetBossSaveData() << aquaGhostData << " " << aquaLekionData << " " << pyroDrakeData << " " << emeraldInstanceData;

                OUT_SAVE_INST_DATA_COMPLETE;
                return saveStream.str();
            }

            void Load(const char* str)
            {
                if (!str)
                {
                    OUT_LOAD_INST_DATA_FAIL;
                    return;
                }

                OUT_LOAD_INST_DATA(str);

                char dataHead1, dataHead2;

                std::istringstream loadStream(str);
                loadStream >> dataHead1 >> dataHead2;

                if (dataHead1 == 'E' && dataHead2 == 'D')
                {
                    for (uint32 i = 0; i < EncounterCount; ++i)
                    {
                        uint32 tmpState;
                        loadStream >> tmpState;
                        if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                            tmpState = NOT_STARTED;
                        SetBossState(i, EncounterState(tmpState));
                    }

                    uint32 temp = 0;
                    loadStream >> temp;
                    aquaGhostData = temp;
                    temp = 0;
                    loadStream >> temp;
                    aquaLekionData = temp;
                    temp = 0;
                    loadStream >> temp;
                    pyroDrakeData = temp;
                    temp = 0;
                    loadStream >> temp;
                    emeraldInstanceData = temp;
                }
                else
                    OUT_LOAD_INST_DATA_FAIL;

                OUT_LOAD_INST_DATA_COMPLETE;
            }
          
          private:
               uint32 aquaGhostData;
               uint32 aquaLekionData;
               uint32 pyroDrakeData;
               uint32 emeraldInstanceData;
               uint64 announcerGUID;
               uint64 hydroGUID;
               uint64 ragnarosGUID;
               uint64 ragnarosStaticGUID;
               uint64 kalecgosGUID;
               uint64 isidorusGUID; 
               uint64 hyotonGUID;
               uint64 firemistGUID;
               uint64 krityusGUID;
               uint64 umbraGUID;
               uint64 emeraldDoor;
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

            if (instance->GetBossState(DATA_HYOTON) == DONE || player->isGameMaster())
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Siguiente Desafio: Pyro Emerald Legion", GOSSIP_SENDER_MAIN, PYRO);

            if ((instance->GetBossState(DATA_HYOTON) == DONE && instance->GetBossState(DATA_FIREMIST) == DONE && instance->GetBossState(DATA_KRITYUS) == DONE && instance->GetBossState(DATA_UMBRA) == DONE) || player->isGameMaster())
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

            if (instance->GetData(DATA_EMERALD_DREAM) == EMERALD_AQUA_DONE || player->isGameMaster())
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
                    instance->SetData(DATA_EMERALD_DREAM, EMERALD_HYOTON_START);
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

            if (instance->GetData(DATA_EMERALD_DREAM) == EMERALD_DRAKE_DONE || player->isGameMaster())
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
                    if (instance->GetData(DATA_EMERALD_DREAM) == EMERALD_MAZE_DONE)
                        player->TeleportTo(player->GetMapId(), Locations[0].GetPositionX(), Locations[0].GetPositionY(), Locations[0].GetPositionZ(), Locations[0].GetOrientation());
                    else
                    {
                        player->TeleportTo(player->GetMapId(), Locations[0].GetPositionX(), Locations[0].GetPositionY(), Locations[0].GetPositionZ(), Locations[0].GetOrientation());		
                        instance->SetData(DATA_EMERALD_DREAM, EMERALD_MAZE_DONE);
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

            if ((instance->GetBossState(DATA_HYOTON) == DONE && instance->GetBossState(DATA_FIREMIST) == DONE && instance->GetBossState(DATA_KRITYUS) == NOT_STARTED) || player->isGameMaster())
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
                    instance->SetData(DATA_EMERALD_DREAM, EMERALD_FIREMIST_DONE);
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

            if (instance->GetData(DATA_EMERALD_DREAM) == EMERALD_DRAKE_ZONE)
                player->TeleportTo(player->GetMapId(), Locations[2].GetPositionX(), Locations[2].GetPositionY(), Locations[2].GetPositionZ(), Locations[2].GetOrientation());
            else
            {
                if (instance->GetData(DATA_EMERALD_DREAM) == EMERALD_DRAKE_DONE)
                { 
                    player->TeleportTo(player->GetMapId(), Locations[3].GetPositionX(), Locations[3].GetPositionY(), Locations[3].GetPositionZ(), Locations[3].GetOrientation());
                    go->CastSpell(player, SPELL_PARACHUTE);
                }
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