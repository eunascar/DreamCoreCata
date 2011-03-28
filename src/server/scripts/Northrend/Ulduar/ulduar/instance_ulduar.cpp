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
#include "ulduar.h"

static const DoorData doorData[] =
{
    {GO_SHIELD_WALL,        TYPE_LEVIATHAN, DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {GO_LEVIATHAN_DOOR,     TYPE_LEVIATHAN, DOOR_TYPE_PASSAGE,  BOUNDARY_S},
    {GO_XT002_GATE,         TYPE_XT002,     DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {GO_IRON_ENTRANCE_DOOR, TYPE_ASSEMBLY,  DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {GO_ARCHIVUM_DOOR,      TYPE_ASSEMBLY,  DOOR_TYPE_PASSAGE,  BOUNDARY_NONE},
    {GO_KOLOGARN_DOOR,      TYPE_KOLOGARN,  DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {GO_HODIR_ICE_WALL,     TYPE_HODIR,     DOOR_TYPE_PASSAGE,  BOUNDARY_NONE},
    {GO_HODIR_EXIT,         TYPE_HODIR,     DOOR_TYPE_PASSAGE,  BOUNDARY_NONE},
    {GO_HODIR_ENTER,        TYPE_HODIR,     DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {GO_LIGHTNING_FIELD,    TYPE_THORIM,    DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {GO_MIMIRON_DOOR_1,     TYPE_MIMIRON,   DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {GO_MIMIRON_DOOR_2,     TYPE_MIMIRON,   DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {GO_MIMIRON_DOOR_3,     TYPE_MIMIRON,   DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {GO_VEZAX_DOOR,         TYPE_VEZAX,     DOOR_TYPE_PASSAGE,  BOUNDARY_NONE},
    {GO_YOGG_GATE,          TYPE_YOGGSARON, DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {0,                     0,              DOOR_TYPE_ROOM,     BOUNDARY_NONE}
};

class instance_ulduar : public InstanceMapScript
{
public:
    instance_ulduar() : InstanceMapScript("instance_ulduar", 603) { }

    InstanceScript* GetInstanceScript(InstanceMap* pMap) const
    {
        return new instance_ulduar_InstanceMapScript(pMap);
    }

    struct instance_ulduar_InstanceMapScript : public InstanceScript
    {
        instance_ulduar_InstanceMapScript(InstanceMap* map) : InstanceScript(map) { Initialize(); };

        uint32 uiEncounter[MAX_ENCOUNTER];
        std::string m_strInstData;

        uint64 uiLeviathanGUID;
        uint64 uiIgnisGUID;
        uint64 uiRazorscaleGUID;
        uint64 uiRazorscaleController;
        uint64 uiRazorHarpoonGUIDs[4];
        uint64 uiExpCommanderGUID;
        uint64 uiXT002GUID;
        uint64 uiAssemblyGUIDs[3];
        uint64 uiKologarnGUID;
        uint64 uiLeftArmGUID;
        uint64 uiRightArmGUID;
        uint64 uiAuriayaGUID;
        uint64 uiMimironGUID;
        uint64 uiHodirGUID;
        uint64 uiThorimGUID;
        uint64 uiFreyaGUID;
        uint64 uiVezaxGUID;
        uint64 uiYoggSaronGUID;
        uint64 uiAlgalonGUID;
        uint64 uiLeviathanGateGUID;
        uint64 uiVezaxDoorGUID;

        uint64 uiBrightLeaf;
        uint64 uiIronBranch;
        uint64 uiStoneBark;
        uint64 uiLeviathanMkII;
        uint64 uiVx001;
        uint64 uiAerialUnit;
        uint64 uiMagneticCore;
        uint64 uiRunicColossus;
        uint64 uiRuneGiant;
        uint64 uiFreyaYS;
        uint64 uiThorimYS;
        uint64 uiMimironYS;
        uint64 uiHodirYS;
        uint64 uiYoggSaronBrain;
        uint64 uiFreyaImage;
        uint64 uiThorimImage;
        uint64 uiMimironImage;
        uint64 uiHodirImage;

        uint64 uiKologarnChestGUID;
        uint64 uiKologarnBridgeGUID;
        uint64 uiKologarnDoorGUID;
        uint64 uiThorimChestGUID;
        uint64 uiHodirChestGUID;
        uint64 uiFreyaChestGUID;

        uint64 uiHodirRareChestGUID;
        uint64 uiRunicDoorGUID;
        uint64 uiStoneDoorGUID;
        uint64 uiThorimLeverGUID;
        uint64 uiMimironTramGUID;
        uint64 uiMimironElevatorGUID;
        uint64 uiKeepersGateGUID;

        std::set<uint64> mRubbleSpawns;

        void Initialize()
        {
            SetBossNumber(MAX_ENCOUNTER);
            LoadDoorData(doorData);
            uiIgnisGUID             = 0;
            uiRazorscaleGUID        = 0;
            uiRazorscaleController  = 0;
            uiExpCommanderGUID      = 0;
            uiXT002GUID             = 0;
            uiKologarnGUID          = 0;
            uiLeftArmGUID           = 0;
            uiRightArmGUID          = 0;
            uiAuriayaGUID           = 0;
            uiMimironGUID           = 0;
            uiHodirGUID             = 0;
            uiThorimGUID            = 0;
            uiFreyaGUID             = 0;
            uiVezaxGUID             = 0;
            uiYoggSaronGUID         = 0;
            uiAlgalonGUID           = 0;
            uiBrightLeaf            = 0;
            uiIronBranch            = 0;
            uiStoneBark             = 0;
            uiLeviathanMkII         = 0;
            uiVx001                 = 0;
            uiAerialUnit            = 0;
            uiMagneticCore          = 0;
            uiRunicColossus         = 0;
            uiRuneGiant             = 0;
            uiFreyaYS               = 0;
            uiThorimYS              = 0;
            uiMimironYS             = 0;
            uiHodirYS               = 0;
            uiYoggSaronBrain        = 0;
            uiFreyaImage            = 0;
            uiThorimImage           = 0;
            uiMimironImage          = 0;
            uiHodirImage            = 0;
            uiKologarnChestGUID     = 0;
            uiKologarnBridgeGUID    = 0;
            uiKologarnChestGUID     = 0;
            uiThorimChestGUID       = 0;
            uiHodirChestGUID        = 0;
            uiFreyaChestGUID        = 0;
            uiLeviathanGateGUID     = 0;
            uiVezaxDoorGUID         = 0;
            uiHodirRareChestGUID    = 0;
            uiRunicDoorGUID         = 0;
            uiStoneDoorGUID         = 0;
            uiThorimLeverGUID       = 0;
            uiMimironTramGUID       = 0;
            uiMimironElevatorGUID   = 0;
            uiKeepersGateGUID       = 0;

            memset(uiEncounter, 0, sizeof(uiEncounter));
            memset(uiAssemblyGUIDs, 0, sizeof(uiAssemblyGUIDs));
            memset(uiRazorHarpoonGUIDs, 0, sizeof(uiRazorHarpoonGUIDs));
        }

        bool IsEncounterInProgress() const
        {
            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            {
                if (uiEncounter[i] == IN_PROGRESS)
                    return true;
            }

            return false;
        }

        void OnCreatureCreate(Creature* creature)
        {
            Map::PlayerList const& players = instance->GetPlayers();
            uint32 TeamInInstance = 0;

            if (!players.isEmpty())
                if (Player* player = players.begin()->getSource())
                    TeamInInstance = player->GetTeam();

            switch(creature->GetEntry())
            {
                case NPC_LEVIATHAN:
                    uiLeviathanGUID = creature->GetGUID();
                    break;
                case NPC_IGNIS:
                    uiIgnisGUID = creature->GetGUID();
                    break;
                case NPC_RAZORSCALE:
                    uiRazorscaleGUID = creature->GetGUID();
                    break;
                case NPC_RAZORSCALE_CONTROLLER:
                    uiRazorscaleController = creature->GetGUID();
                    break;
                case NPC_EXPEDITION_COMMANDER:
                    uiExpCommanderGUID = creature->GetGUID();
                    return;
                case NPC_XT002:
                    uiXT002GUID = creature->GetGUID();
                    break;

                // Assembly of Iron
                case NPC_STEELBREAKER:
                    uiAssemblyGUIDs[0] = creature->GetGUID();
                    break;
                case NPC_MOLGEIM:
                    uiAssemblyGUIDs[1] = creature->GetGUID();
                    break;
                case NPC_BRUNDIR:
                    uiAssemblyGUIDs[2] = creature->GetGUID();
                    break;

                // Kologarn
                case NPC_KOLOGARN:
                    uiKologarnGUID = creature->GetGUID();
                    break;
                case NPC_KOLOGARN_BRIDGE:
                    // The below hacks are courtesy of the grid/visibilitysystem
                    if (GetBossState(TYPE_KOLOGARN) == DONE)
                    {
                        creature->SetDeadByDefault(true);
                        creature->setDeathState(CORPSE);
                        creature->DestroyForNearbyPlayers();
                        creature->UpdateObjectVisibility(true);
                    }
                    else
                    {
                        creature->SetDeadByDefault(false);
                        creature->setDeathState(CORPSE);
                        creature->RemoveCorpse(true);
                    }
                    break;
                case NPC_AURIAYA:
                    uiAuriayaGUID = creature->GetGUID();
                    break;
                case NPC_MIMIRON:
                    uiMimironGUID = creature->GetGUID();
                    break;
                case NPC_HODIR:
                    uiHodirGUID = creature->GetGUID();
                    break;
                case NPC_THORIM:
                    uiThorimGUID = creature->GetGUID();
                    break;
                case NPC_FREYA:
                    uiFreyaGUID = creature->GetGUID();
                    break;
                case NPC_VEZAX:
                    uiVezaxGUID = creature->GetGUID();
                    break;
                case NPC_YOGGSARON:
                    uiYoggSaronGUID = creature->GetGUID();
                    break;
                case NPC_ALGALON:
                    uiAlgalonGUID = creature->GetGUID();
                    break;
                case NPC_BRIGHTLEAF:
                    uiBrightLeaf = creature->GetGUID();
                    break;
                case NPC_IRONBRANCH:
                    uiIronBranch = creature->GetGUID();
                    break;
                case NPC_STONEBARK:
                    uiStoneBark = creature->GetGUID();
                    break;
                case NPC_LEVIATHAN_MK_II:
                    uiLeviathanMkII = creature->GetGUID();
                    break;
                case NPC_VX_001:
                    uiVx001 = creature->GetGUID();
                    break;
                case NPC_AERIAL_UNIT:
                    uiAerialUnit = creature->GetGUID();
                    break;
                case NPC_MAGNETIC_CORE:
                    uiMagneticCore = creature->GetGUID();
                    break;
                case NPC_RUNIC_COLOSSUS:
                    uiRunicColossus = creature->GetGUID();
                    break;
                case NPC_RUNE_GIANT:
                    uiRuneGiant = creature->GetGUID();
                    break;
                case NPC_FREYA_IMAGE:
                    uiFreyaYS = creature->GetGUID();
                    break;
                case NPC_THORIM_IMAGE:
                    uiThorimYS = creature->GetGUID();
                    break;
                case NPC_MIMIRON_IMAGE:
                    uiMimironYS = creature->GetGUID();
                    break;
                case NPC_HODIR_IMAGE:
                    uiHodirYS = creature->GetGUID();
                    break;
                case NPC_YOGG_BRAIN:
                    uiYoggSaronBrain = creature->GetGUID();
                    break;
                // Keeper's Images
                case NPC_KEEPER_FREYA:
                {
                    uiFreyaImage = creature->GetGUID();
                    creature->SetVisible(false);

                    if (GetBossState(TYPE_VEZAX) == DONE)
                        creature->SetVisible(true);
                    break;
                }
                case NPC_KEEPER_THORIM:
                {
                    uiThorimImage = creature->GetGUID();
                    creature->SetVisible(false);

                    if (GetBossState(TYPE_VEZAX) == DONE)
                        creature->SetVisible(true);
                    break;
                }
                case NPC_KEEPER_MIMIRON:
                {
                    uiMimironImage = creature->GetGUID();
                    creature->SetVisible(false);
					
                    if (GetBossState(TYPE_VEZAX) == DONE)
                        creature->SetVisible(true);
                    break;
                }            
                case NPC_KEEPER_HODIR:
                {
                    uiHodirImage = creature->GetGUID();
                    creature->SetVisible(false);

                    if (GetBossState(TYPE_VEZAX) == DONE)
                        creature->SetVisible(true);
                    break;
                }
            }

            if (TeamInInstance == HORDE)
            {
                switch(creature->GetEntry())
                {
                    case NPC_SALVAGED_CHOPPER:
                        creature->SetDisplayId(25871);
                        break;
                    case NPC_ELVI_NIGHTFEATHER:
                        creature->UpdateEntry(NPC_TOR_GREYCLOUD, HORDE);
                        break;
                    case NPC_ELLIE_NIGHTFEATHER:
                        creature->UpdateEntry(NPC_KAR_GREYCLOUD, HORDE);
                        break;
                    case NPC_ELEMENTALIST_MAHFUUN:
                        creature->UpdateEntry(NPC_SPIRITWALKER_TARA, HORDE);
                        break;
                    case NPC_ELEMENTALIST_AVUUN:
                        creature->UpdateEntry(NPC_SPIRITWALKER_YONA, HORDE);
                        break;
                    case NPC_MISSY_FLAMECUFFS:
                        creature->UpdateEntry(NPC_AMIRA_BLAZEWEAVER, HORDE);
                        break;
                    case NPC_SISSY_FLAMECUFFS:
                        creature->UpdateEntry(NPC_VEESHA_BLAZEWEAVER, HORDE);
                        break;
                    case NPC_FIELD_MEDIC_PENNY:
                        creature->UpdateEntry(NPC_BATTLE_PRIEST_ELIZA, HORDE);
                        break;
                    case NPC_FIELD_MEDIC_JESSI:
                        creature->UpdateEntry(NPC_BATTLE_PRIEST_GINA, HORDE);
                        break;
                    case NPC_MERCENARY_CAPTAIN_A:
                        creature->UpdateEntry(NPC_MERCENARY_CAPTAIN_H, HORDE);
                        break;
                    case NPC_MERCENARY_SOLDIER_A:
                        creature->UpdateEntry(NPC_MERCENARY_SOLDIER_H, HORDE);
                        break;
                }
            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
            switch(go->GetEntry())
            {
                case GO_SHIELD_WALL:
                case GO_LEVIATHAN_DOOR:
                case GO_XT002_GATE:
                case GO_IRON_ENTRANCE_DOOR:
                case GO_ARCHIVUM_DOOR:
                case GO_KOLOGARN_DOOR:
                case GO_HODIR_ICE_WALL:
                case GO_HODIR_EXIT:
                case GO_HODIR_ENTER:
                case GO_LIGHTNING_FIELD:
                case GO_MIMIRON_DOOR_1:
                case GO_MIMIRON_DOOR_2:
                case GO_MIMIRON_DOOR_3:
                case GO_VEZAX_DOOR:
                case GO_YOGG_GATE:
                    AddDoor(go, true);
                    break;
                case GO_KOLOGARN_CHEST_HERO:
                case GO_KOLOGARN_CHEST:
                    uiKologarnChestGUID = go->GetGUID();
                    break;
                case GO_KOLOGARN_BRIDGE:
                    uiKologarnBridgeGUID = go->GetGUID();
                    if (GetBossState(TYPE_KOLOGARN) == DONE)
                        HandleGameObject(0, false, go);
                    break;
                case GO_THORIM_CHEST_HERO:
                case GO_THORIM_CHEST:
                    uiThorimChestGUID =go->GetGUID();
                    break;
                case GO_HODIR_CHEST_HERO:
                case GO_HODIR_CHEST:
                    uiHodirChestGUID = go->GetGUID();
                    break;
                case GO_FREYA_CHEST_HERO:
                case GO_FREYA_CHEST:
                    uiFreyaChestGUID = go->GetGUID();
                    break;
                case GO_LEVIATHAN_GATE:
                    uiLeviathanGateGUID = go->GetGUID();
                    if (GetBossState(TYPE_LEVIATHAN) == DONE)
                        go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                    break;
                case GO_RAZOR_HARPOON_1:
                    uiRazorHarpoonGUIDs[0] = go->GetGUID();
                    break;
                case GO_RAZOR_HARPOON_2:
                    uiRazorHarpoonGUIDs[1] = go->GetGUID();
                    break;
                case GO_RAZOR_HARPOON_3:
                    uiRazorHarpoonGUIDs[2] = go->GetGUID();
                    break;
                case GO_RAZOR_HARPOON_4:
                    uiRazorHarpoonGUIDs[3] = go->GetGUID();
                    break;
                case GO_HODIR_RARE_CHEST_10:
                case GO_HODIR_RARE_CHEST_25:
                    uiHodirRareChestGUID = go->GetGUID();
                    break;
                case GO_RUNIC_DOOR:
                    uiRunicDoorGUID = go->GetGUID();
                    break;
                case GO_STONE_DOOR:
                    uiStoneDoorGUID = go->GetGUID();
                    break;
                case GO_THORIM_LEVER:
                    uiThorimLeverGUID = go->GetGUID();
                    break;
                case GO_MIMIRON_TRAM:
                    uiMimironTramGUID = go->GetGUID();
                    break;
                case GO_MIMIRON_ELEVATOR:
                    uiMimironElevatorGUID = go->GetGUID();
                    break;
                case GO_KEEPERS_DOOR:
                {
                    InstanceScript* instance = go->GetInstanceScript();
                    uiKeepersGateGUID = go->GetGUID();
                    go->RemoveFlag(GAMEOBJECT_FLAGS,GO_FLAG_LOCKED);

                    if (instance)
                    {
                        for (uint32 i = TYPE_MIMIRON; i < TYPE_VEZAX; ++i)
                            if (instance->GetBossState(i) != DONE)
                                go->SetFlag(GAMEOBJECT_FLAGS,GO_FLAG_LOCKED);
                    }
                    break;
                }
            }
        }

        void OnGameObjectRemove(GameObject* go)
        {
            switch (go->GetEntry())
            {
                case GO_SHIELD_WALL:
                case GO_LEVIATHAN_DOOR:
                case GO_XT002_GATE:
                case GO_IRON_ENTRANCE_DOOR:
                case GO_ARCHIVUM_DOOR:
                case GO_KOLOGARN_DOOR:
                case GO_HODIR_ICE_WALL:
                case GO_HODIR_EXIT:
                case GO_HODIR_ENTER:
                case GO_LIGHTNING_FIELD:
                case GO_MIMIRON_DOOR_1:
                case GO_MIMIRON_DOOR_2:
                case GO_MIMIRON_DOOR_3:
                case GO_VEZAX_DOOR:
                case GO_YOGG_GATE:
                    AddDoor(go, false);
                    break;
                default:
                    break;
            }
        }

        void ProcessEvent(GameObject* /*go*/, uint32 eventId)
        {
            // Flame Leviathan's Tower Event triggers
           Creature* pFlameLeviathan = instance->GetCreature(uiLeviathanGUID);

            if (pFlameLeviathan && pFlameLeviathan->isAlive()) //No leviathan, no event triggering ;)
                switch(eventId)
                {
                    case EVENT_TOWER_OF_STORM_DESTROYED:
                        pFlameLeviathan->AI()->DoAction(1);
                        break;
                    case EVENT_TOWER_OF_FROST_DESTROYED:
                        pFlameLeviathan->AI()->DoAction(2);
                        break;
                    case EVENT_TOWER_OF_FLAMES_DESTROYED:
                        pFlameLeviathan->AI()->DoAction(3);
                        break;
                    case EVENT_TOWER_OF_LIFE_DESTROYED:
                        pFlameLeviathan->AI()->DoAction(4);
                        break;
                }
        }

        void ProcessEvent(Unit* /*unit*/, uint32 /*eventId*/)
        {
        }

        bool SetBossState(uint32 type, EncounterState state)
        {
            if (!InstanceScript::SetBossState(type, state))
                return false;

            switch (type)
            {
                case TYPE_LEVIATHAN:
                case TYPE_IGNIS:
                case TYPE_RAZORSCALE:
                case TYPE_XT002:
                case TYPE_ASSEMBLY:
                case TYPE_AURIAYA:
                case TYPE_YOGGSARON:
                case TYPE_KOLOGARN:
                    if (state == DONE)
                    {
                        if (GameObject* go = instance->GetGameObject(uiKologarnChestGUID))
                            go->SetRespawnTime(go->GetRespawnDelay());

                        HandleGameObject(uiKologarnBridgeGUID, false);
                    }
                    break;
                case TYPE_HODIR:
                    if (state == DONE)
                        if (GameObject* go = instance->GetGameObject(uiHodirChestGUID))
                            go->SetRespawnTime(go->GetRespawnDelay());

                    CheckKeepersState();
                    break;
                case TYPE_THORIM:
                    if (state == DONE)
                        if (GameObject* go = instance->GetGameObject(uiThorimChestGUID))
                            go->SetRespawnTime(go->GetRespawnDelay());

                    if (GameObject* pThorimLever = instance->GetGameObject(uiThorimLeverGUID))
                    {
                        if (state == IN_PROGRESS)
                            pThorimLever->RemoveFlag(GAMEOBJECT_FLAGS,GO_FLAG_UNK1);
                    }

                    CheckKeepersState();
                    break;
                case TYPE_FREYA:
                    if (state == DONE)
                        if (GameObject* go = instance->GetGameObject(uiFreyaChestGUID))
                            go->SetRespawnTime(go->GetRespawnDelay());

                    CheckKeepersState();
                    break;
                case TYPE_MIMIRON:
                    CheckKeepersState();
                    break;
                case TYPE_VEZAX:
                    if (state == DONE)
                    {
                        // Keeper's Images
                        if (Creature* pFreya = instance->GetCreature(uiFreyaImage))
                            pFreya->SetVisible(true);
                        if (Creature* pThorim = instance->GetCreature(uiThorimImage))
                            pThorim->SetVisible(true);
                        if (Creature* pMimiron = instance->GetCreature(uiMimironImage))
                            pMimiron->SetVisible(true);
                        if (Creature* pHodir = instance->GetCreature(uiHodirImage))
                            pHodir->SetVisible(true);
                    }
                    break;
             }

             return true;
        }

        void CheckKeepersState()
        {
            if (GameObject* go = instance->GetGameObject(uiKeepersGateGUID))
            {
                InstanceScript* instance = go->GetInstanceScript();
                go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);

                if (instance)
                {
                    for (uint32 i = TYPE_MIMIRON; i < TYPE_VEZAX; ++i)
                        if (instance->GetBossState(i) != DONE)
                            go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
                }
            }
        }

        void SetData(uint32 type, uint32 data)
        {
            switch(type)
            {
                case TYPE_COLOSSUS:
                    uiEncounter[TYPE_COLOSSUS] = data;
                    if (data == 2)
                    {
                        if (Creature* pBoss = instance->GetCreature(uiLeviathanGUID))
                            pBoss->AI()->DoAction(10);
                        if (GameObject* pGate = instance->GetGameObject(uiLeviathanGateGUID))
                            pGate->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                        SaveToDB();
                    }
                    break;
                case DATA_RUNIC_DOOR:
                    if (GameObject* pRunicDoor = instance->GetGameObject(uiRunicDoorGUID))
                        pRunicDoor->SetGoState(GOState(data));
                    break;
                case DATA_STONE_DOOR:
                    if (GameObject* pStoneDoor = instance->GetGameObject(uiStoneDoorGUID))
                        pStoneDoor->SetGoState(GOState(data));
                    break;
                case DATA_CALL_TRAM:
                    if (GameObject* MimironTram = instance->GetGameObject(uiMimironTramGUID))
                    {
                        // Load Mimiron Tram (unfortunally only server side)
                        instance->LoadGrid(2307, 284.632f);
                
                        if (data == 0)
                            MimironTram->SetGoState(GO_STATE_READY);
                        if (data == 1)
                            MimironTram->SetGoState(GO_STATE_ACTIVE);
                    
                        // Send movement update to players
                        if (Map* pMap = MimironTram->GetMap())
                        {
                            if (pMap->IsDungeon())
                            {
                                Map::PlayerList const &PlayerList = pMap->GetPlayers();

                                if (!PlayerList.isEmpty())
                                {
                                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                                    {
                                        if (i->getSource())
                                        {
                                            UpdateData data;
                                            WorldPacket pkt;
                                            MimironTram->BuildValuesUpdateBlockForPlayer(&data, i->getSource());
                                            data.BuildPacket(&pkt);
                                            i->getSource()->GetSession()->SendPacket(&pkt);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                case DATA_MIMIRON_ELEVATOR:
                    if (GameObject* MimironElevator = instance->GetGameObject(uiMimironElevatorGUID))
                        MimironElevator->SetGoState(GOState(data));
                    break;
                case DATA_HODIR_RARE_CHEST:
                    if (GameObject* HodirRareChest = instance->GetGameObject(uiHodirRareChestGUID))
                    {
                        if (data == GO_STATE_READY)
                            HodirRareChest->RemoveFlag(GAMEOBJECT_FLAGS,GO_FLAG_UNK1);
                    }
                    break;
                default:
                    break;
            }
        }

        void SetData64(uint32 type, uint64 data)
        {
            switch (type)
            {
                case DATA_LEFT_ARM:
                    uiLeftArmGUID = data;
                    break;
                case DATA_RIGHT_ARM:
                    uiRightArmGUID = data;
                    break;
            }
        }

        uint64 GetData64(uint32 data)
        {
            switch(data)
            {
                case TYPE_LEVIATHAN:            return uiLeviathanGUID;
                case TYPE_IGNIS:                return uiIgnisGUID;
                case TYPE_RAZORSCALE:           return uiRazorscaleGUID;
                case DATA_RAZORSCALE_CONTROL:   return uiRazorscaleController;
                case TYPE_XT002:                return uiXT002GUID;
                case TYPE_KOLOGARN:             return uiKologarnGUID;
                case DATA_LEFT_ARM:             return uiLeftArmGUID;
                case DATA_RIGHT_ARM:            return uiRightArmGUID;
                case TYPE_AURIAYA:              return uiAuriayaGUID;
                case TYPE_MIMIRON:              return uiMimironGUID;
                case TYPE_HODIR:                return uiHodirGUID;
                case TYPE_THORIM:               return uiThorimGUID;
                case TYPE_FREYA:                return uiFreyaGUID;
                case TYPE_VEZAX:                return uiVezaxGUID;
                case TYPE_YOGGSARON:            return uiYoggSaronGUID;
                case TYPE_ALGALON:              return uiAlgalonGUID;

                // razorscale expedition commander
                case DATA_EXP_COMMANDER:        return uiExpCommanderGUID;
                case GO_RAZOR_HARPOON_1:        return uiRazorHarpoonGUIDs[0];
                case GO_RAZOR_HARPOON_2:        return uiRazorHarpoonGUIDs[1];
                case GO_RAZOR_HARPOON_3:        return uiRazorHarpoonGUIDs[2];
                case GO_RAZOR_HARPOON_4:        return uiRazorHarpoonGUIDs[3];
                // Assembly of Iron
                case DATA_STEELBREAKER:         return uiAssemblyGUIDs[0];
                case DATA_MOLGEIM:              return uiAssemblyGUIDs[1];
                case DATA_BRUNDIR:              return uiAssemblyGUIDs[2];
                // Freya
                case DATA_BRIGHTLEAF:           return uiBrightLeaf;
                case DATA_IRONBRANCH:           return uiIronBranch;
                case DATA_STONEBARK:            return uiStoneBark;
                // Mimiron
                case DATA_LEVIATHAN_MK_II:      return uiLeviathanMkII;
                case DATA_VX_001:               return uiVx001;
                case DATA_AERIAL_UNIT:          return uiAerialUnit;
                case DATA_MAGNETIC_CORE:        return uiMagneticCore;
                // Thorim
                case DATA_RUNIC_COLOSSUS:       return uiRunicColossus;
                case DATA_RUNE_GIANT:           return uiRuneGiant;
                // YoggSaron
                case DATA_YS_FREYA:             return uiFreyaYS;
                case DATA_YS_THORIM:            return uiThorimYS;
                case DATA_YS_MIMIRON:           return uiMimironYS;
                case DATA_YS_HODIR:             return uiHodirYS;
                case DATA_YOGGSARON_BRAIN:      return uiYoggSaronBrain;
            }

            return 0;
        }

        uint32 GetData(uint32 type)
        {
            switch(type)
            {
                case TYPE_COLOSSUS:
                    return uiEncounter[type];
            }

            return 0;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "U U " << GetBossSaveData() << GetData(TYPE_COLOSSUS);

            OUT_SAVE_INST_DATA_COMPLETE;
            return saveStream.str();
        }

        void Load(const char* strIn)
        {
            if (!strIn)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(strIn);

            char dataHead1, dataHead2;

            std::istringstream loadStream(strIn);
            loadStream >> dataHead1 >> dataHead2;

            if (dataHead1 == 'U' && dataHead2 == 'U')
            {
                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                {
                    uint32 tmpState;
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;

                    if (i == TYPE_COLOSSUS)
                        SetData(i, tmpState);
                    else
                        SetBossState(i, EncounterState(tmpState));
                }
            }

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };

};

class go_call_tram : public GameObjectScript
{
public:
    go_call_tram() : GameObjectScript("go_call_tram") { }

    bool OnGossipHello(Player* /*player*/, GameObject* go)
    {
        InstanceScript* instance = go->GetInstanceScript();

        if (!instance)
            return false;

        switch(go->GetEntry())
        {
            case GO_CALL_TRAM_1:
            case GO_ACTIVATE_TRAM_1:
                instance->SetData(DATA_CALL_TRAM, 0);
                break;
            case GO_CALL_TRAM_2:
            case GO_ACTIVATE_TRAM_2:
                instance->SetData(DATA_CALL_TRAM, 1);
                break;
        }
        return true;
    }
};

void AddSC_instance_ulduar()
{
    new instance_ulduar();
    new go_call_tram();
}
