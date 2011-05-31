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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "InstanceScript.h"
#include "ObjectMgr.h"
#include "ulduar.h"

static const DoorData doorData[] =
{
    {GO_SHIELD_WALL,        BOSS_LEVIATHAN, DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {GO_LEVIATHAN_DOOR,     BOSS_LEVIATHAN, DOOR_TYPE_ROOM,     BOUNDARY_S},
    {GO_XT002_GATE,         BOSS_XT002,     DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {GO_HODIR_ICE_WALL,     BOSS_HODIR,     DOOR_TYPE_PASSAGE,  BOUNDARY_NONE},
    {GO_HODIR_EXIT,         BOSS_HODIR,     DOOR_TYPE_PASSAGE,  BOUNDARY_NONE},
    {GO_HODIR_ENTER,        BOSS_HODIR,     DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {GO_LIGHTNING_FIELD,    BOSS_THORIM,    DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {GO_MIMIRON_DOOR_1,     BOSS_MIMIRON,   DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {GO_MIMIRON_DOOR_2,     BOSS_MIMIRON,   DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {GO_MIMIRON_DOOR_3,     BOSS_MIMIRON,   DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {GO_VEZAX_DOOR,         BOSS_VEZAX,     DOOR_TYPE_PASSAGE,  BOUNDARY_NONE},
    {GO_YOGG_GATE,          BOSS_YOGGSARON, DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {0,                     0,              DOOR_TYPE_ROOM,     BOUNDARY_NONE}
};

class instance_ulduar : public InstanceMapScript
{
public:
    instance_ulduar() : InstanceMapScript("instance_ulduar", 603) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_ulduar_InstanceMapScript(map);
    }

    struct instance_ulduar_InstanceMapScript : public InstanceScript
    {
        instance_ulduar_InstanceMapScript(InstanceMap* map) : InstanceScript(map) { }

        uint32 Encounter[MAX_ENCOUNTER];
        std::string m_strInstData;

        uint64 LeviathanGUID;
        uint64 IgnisGUID;
        uint64 RazorscaleGUID;
        uint64 RazorscaleController;
        uint64 RazorHarpoonGUIDs[4];
        uint64 ExpeditionCommanderGUID;
        uint64 XT002GUID;
        uint64 AssemblyGUIDs[3];
        uint64 KologarnGUID;
        uint64 LeftArmGUID;
        uint64 RightArmGUID;
        uint64 AuriayaGUID;
        uint64 MimironGUID;
        uint64 HodirGUID;
        uint64 ThorimGUID;
        uint64 FreyaGUID;
        uint64 KeeperGUIDs[3];
        uint64 VezaxGUID;
        uint64 YoggSaronGUID;
        uint64 AlgalonGUID;
        uint64 LeviathanGateGUID;
        uint64 VezaxDoorGUID;

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

        uint64 AlgalonChestGUID;
        uint64 KologarnChestGUID;
        uint64 KologarnBridgeGUID;
        uint64 KologarnDoorGUID;
        uint64 ThorimChestGUID;
        uint64 HodirChestGUID;
        uint64 FreyaChestGUID;
        uint64 HodirDoorGUID;
        uint64 HodirIceDoorGUID;
        uint64 MimironChestGUID;

        uint32 TeamInInstance;

        uint64 uiHodirRareChestGUID;
        uint64 uiRunicDoorGUID;
        uint64 uiStoneDoorGUID;
        uint64 uiThorimLeverGUID;
        uint64 uiMimironTramGUID;
        uint64 uiMimironElevatorGUID;
        uint64 uiDoNotPushGUID;
        uint64 uiKeepersGateGUID;

        std::set<uint64> mRubbleSpawns;

        void Initialize()
        {
            SetBossNumber(MAX_ENCOUNTER);
            LoadDoorData(doorData);
            IgnisGUID                            = 0;
            RazorscaleGUID                       = 0;
            RazorscaleController                 = 0;
            ExpeditionCommanderGUID              = 0;
            XT002GUID                            = 0;
            KologarnGUID                         = 0;
            LeftArmGUID                          = 0;
            RightArmGUID                         = 0;
            AuriayaGUID                          = 0;
            MimironGUID                          = 0;
            HodirGUID                            = 0;
            ThorimGUID                           = 0;
            FreyaGUID                            = 0;
            VezaxGUID                            = 0;
            YoggSaronGUID                        = 0;
            AlgalonGUID                          = 0;
            KologarnChestGUID                    = 0;
            KologarnBridgeGUID                   = 0;
            KologarnChestGUID                    = 0;
            ThorimChestGUID                      = 0;
            HodirChestGUID                       = 0;
            FreyaChestGUID                       = 0;
            LeviathanGateGUID                    = 0;
            VezaxDoorGUID                        = 0;
            HodirDoorGUID                        = 0;
            HodirIceDoorGUID                     = 0;
            TeamInInstance                       = 0;
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
            uiRunicDoorGUID         = 0;
            uiStoneDoorGUID         = 0;
            uiThorimLeverGUID       = 0;
            uiMimironTramGUID       = 0;
            uiMimironElevatorGUID   = 0;
            uiDoNotPushGUID         = 0;
            uiKeepersGateGUID       = 0;

            memset(Encounter, 0, sizeof(Encounter));
            memset(AssemblyGUIDs, 0, sizeof(AssemblyGUIDs));
            memset(RazorHarpoonGUIDs, 0, sizeof(RazorHarpoonGUIDs));
            memset(KeeperGUIDs, 0, sizeof(KeeperGUIDs));
        }

        bool IsEncounterInProgress() const
        {
            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            {
                if (Encounter[i] == IN_PROGRESS)
                    return true;
            }

            return false;
        }

        void OnPlayerEnter(Player* player)
        {
            if (!TeamInInstance)
                TeamInInstance = player->GetTeam();
        }

        void OnCreatureCreate(Creature* creature)
        {
            if (!TeamInInstance)
            {
                Map::PlayerList const& Players = instance->GetPlayers();
                if (!Players.isEmpty())
                    if (Player* player = Players.begin()->getSource())
                        TeamInInstance = player->GetTeam();
            }

            switch (creature->GetEntry())
            {
                case NPC_LEVIATHAN:
                    LeviathanGUID = creature->GetGUID();
                    break;
                case NPC_IGNIS:
                    IgnisGUID = creature->GetGUID();
                    break;
                case NPC_RAZORSCALE:
                    RazorscaleGUID = creature->GetGUID();
                    break;
                case NPC_RAZORSCALE_CONTROLLER:
                    RazorscaleController = creature->GetGUID();
                    break;
                case NPC_EXPEDITION_COMMANDER:
                    ExpeditionCommanderGUID = creature->GetGUID();
                    break;
                case NPC_XT002:
                    XT002GUID = creature->GetGUID();
                    break;

                // Assembly of Iron
                case NPC_STEELBREAKER:
                    AssemblyGUIDs[0] = creature->GetGUID();
                    break;
                case NPC_MOLGEIM:
                    AssemblyGUIDs[1] = creature->GetGUID();
                    break;
                case NPC_BRUNDIR:
                    AssemblyGUIDs[2] = creature->GetGUID();
                    break;

                // Freya's Keeper
                case NPC_IRONBRANCH:
                    KeeperGUIDs[0] = creature->GetGUID();
                    if (GetBossState(BOSS_FREYA) == DONE)
                        creature->DespawnOrUnsummon();
                    break;
                case NPC_BRIGHTLEAF:
                    KeeperGUIDs[1] = creature->GetGUID();
                    if (GetBossState(BOSS_FREYA) == DONE)
                        creature->DespawnOrUnsummon();
                    break;
                case NPC_STONEBARK:
                    KeeperGUIDs[2] = creature->GetGUID();
                    if (GetBossState(BOSS_FREYA) == DONE)
                        creature->DespawnOrUnsummon();
                     break;

                // Kologarn
                case NPC_KOLOGARN:
                    KologarnGUID = creature->GetGUID();
                    break;
                case NPC_KOLOGARN_BRIDGE:
                    // The below hacks are courtesy of the grid/visibilitysystem
                    if (GetBossState(BOSS_KOLOGARN) == DONE)
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
                    AuriayaGUID = creature->GetGUID();
                    break;
                case NPC_MIMIRON:
                    MimironGUID = creature->GetGUID();
                    break;
                case NPC_HODIR:
                    HodirGUID = creature->GetGUID();
                    break;
                case NPC_THORIM:
                    ThorimGUID = creature->GetGUID();
                    break;
                case NPC_FREYA:
                    FreyaGUID = creature->GetGUID();
                    break;
                case NPC_VEZAX:
                    VezaxGUID = creature->GetGUID();
                    break;
                case NPC_YOGGSARON:
                    YoggSaronGUID = creature->GetGUID();
                    break;
                case NPC_ALGALON:
                    AlgalonGUID = creature->GetGUID();
                    break;

                // Hodir's Helper NPCs
                case NPC_EIVI_NIGHTFEATHER:
                    if (TeamInInstance == HORDE)
                        creature->UpdateEntry(NPC_TOR_GREYCLOUD, HORDE);
                    break;
                case NPC_ELLIE_NIGHTFEATHER:
                    if (TeamInInstance == HORDE)
                        creature->UpdateEntry(NPC_KAR_GREYCLOUD, HORDE);
                    break;
                case NPC_ELEMENTALIST_MAHFUUN:
                    if (TeamInInstance == HORDE)
                        creature->UpdateEntry(NPC_SPIRITWALKER_TARA, HORDE);
                    break;
                case NPC_ELEMENTALIST_AVUUN:
                    if (TeamInInstance == HORDE)
                        creature->UpdateEntry(NPC_SPIRITWALKER_YONA, HORDE);
                    break;
                case NPC_MISSY_FLAMECUFFS:
                    if (TeamInInstance == HORDE)
                        creature->UpdateEntry(NPC_AMIRA_BLAZEWEAVER, HORDE);
                    break;
                case NPC_SISSY_FLAMECUFFS:
                    if (TeamInInstance == HORDE)
                        creature->UpdateEntry(NPC_VEESHA_BLAZEWEAVER, HORDE);
                    break;
                case NPC_FIELD_MEDIC_PENNY:
                    if (TeamInInstance == HORDE)
                        creature->UpdateEntry(NPC_BATTLE_PRIEST_ELIZA, HORDE);
                    break;
                case NPC_FIELD_MEDIC_JESSI:
                    if (TeamInInstance == HORDE)
                        creature->UpdateEntry(NPC_BATTLE_PRIEST_GINA, HORDE);
                    break;
                case NPC_LEVIATHAN_MKII:
                    uiLeviathanMkII = creature->GetGUID();
                    break;
                case NPC_VX_001:
                    uiVx001 = creature->GetGUID();
                    break;
                case NPC_AERIAL_COMMAND_UNIT:
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

                    if (GetBossState(BOSS_VEZAX) == DONE)
                        creature->SetVisible(true);
                    break;
                }
                case NPC_KEEPER_THORIM:
                {
                    uiThorimImage = creature->GetGUID();
                    creature->SetVisible(false);

                    if (GetBossState(BOSS_VEZAX) == DONE)
                        creature->SetVisible(true);
                    break;
                }
                case NPC_KEEPER_MIMIRON:
                {
                    uiMimironImage = creature->GetGUID();
                    creature->SetVisible(false);
					
                    if (GetBossState(BOSS_VEZAX) == DONE)
                        creature->SetVisible(true);
                    break;
                }            
                case NPC_KEEPER_HODIR:
                {
                    uiHodirImage = creature->GetGUID();
                    creature->SetVisible(false);

                    if (GetBossState(BOSS_VEZAX) == DONE)
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

        void OnGameObjectCreate(GameObject* gameObject)
        {
            switch (gameObject->GetEntry())
            {
                case GO_SHIELD_WALL:
                case GO_XT002_GATE:
                case GO_IRON_ENTRANCE_DOOR:
                case GO_ARCHIVUM_DOOR:
                case GO_HODIR_ICE_WALL:
                case GO_HODIR_EXIT:
                case GO_HODIR_ENTER:
                case GO_LIGHTNING_FIELD:
                case GO_MIMIRON_DOOR_1:
                case GO_MIMIRON_DOOR_2:
                case GO_MIMIRON_DOOR_3:
                case GO_VEZAX_DOOR:
                case GO_YOGG_GATE:
                    AddDoor(gameObject, true);
                    break;
                case GO_ALGALON_CHEST_HERO:
                case GO_ALGALON_CHEST:
                    AlgalonChestGUID = gameObject->GetGUID();
                    break;
                case GO_KOLOGARN_CHEST_HERO:
                case GO_KOLOGARN_CHEST:
                    KologarnChestGUID = gameObject->GetGUID();
                    break;
                case GO_KOLOGARN_BRIDGE:
                    KologarnBridgeGUID = gameObject->GetGUID();
                    if (GetBossState(BOSS_KOLOGARN) == DONE)
                        HandleGameObject(0, false, gameObject);
                    break;
                case GO_KOLOGARN_DOOR:
                    KologarnDoorGUID = gameObject->GetGUID();
                    break;
                case GO_THORIM_CHEST_HERO:
                case GO_THORIM_CHEST:
                    ThorimChestGUID = gameObject->GetGUID();
                    break;
                case GO_HODIR_CHEST_HERO:
                case GO_HODIR_CHEST:
                    HodirChestGUID = gameObject->GetGUID();
                    break;
                case GO_MIMIRON_CHEST_HERO:
                case GO_MIMIRON_CHEST:
                    MimironChestGUID = gameObject->GetGUID();
                    break;
                case GO_FREYA_CHEST_HERO:
                case GO_FREYA_CHEST:
                    FreyaChestGUID = gameObject->GetGUID();
                    break;
                case GO_LEVIATHAN_DOOR:
                    AddDoor(gameObject, true);
                    break;
                case GO_LEVIATHAN_GATE:
                    LeviathanGateGUID = gameObject->GetGUID();
                    if (GetBossState(BOSS_LEVIATHAN) == DONE)
                        gameObject->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                    break;
                case GO_RAZOR_HARPOON_1:
                    RazorHarpoonGUIDs[0] = gameObject->GetGUID();
                    break;
                case GO_RAZOR_HARPOON_2:
                    RazorHarpoonGUIDs[1] = gameObject->GetGUID();
                    break;
                case GO_RAZOR_HARPOON_3:
                    RazorHarpoonGUIDs[2] = gameObject->GetGUID();
                    break;
                case GO_RAZOR_HARPOON_4:
                    RazorHarpoonGUIDs[3] = gameObject->GetGUID();
                    break;
                case GO_MOLE_MACHINE:
                    if (GetBossState(BOSS_RAZORSCALE) == IN_PROGRESS)
                        gameObject->SetGoState(GO_STATE_ACTIVE);
                case GO_RUNIC_DOOR:
                    uiRunicDoorGUID = gameObject->GetGUID();
                    break;
                case GO_STONE_DOOR:
                    uiStoneDoorGUID = gameObject->GetGUID();
                    break;
                case GO_THORIM_LEVER:
                    uiThorimLeverGUID = gameObject->GetGUID();
                    break;
                case GO_MIMIRON_TRAM:
                    uiMimironTramGUID = gameObject->GetGUID();
                    break;
                case GO_MIMIRON_ELEVATOR:
                    uiMimironElevatorGUID = gameObject->GetGUID();
                    break;
                case GO_DO_NOT_PUSH:
                    uiDoNotPushGUID = gameObject->GetGUID();
                    break;
                case GO_KEEPERS_DOOR:
                {
                    InstanceScript* instance = gameObject->GetInstanceScript();
                    uiKeepersGateGUID = gameObject->GetGUID();
                    gameObject->RemoveFlag(GAMEOBJECT_FLAGS,GO_FLAG_LOCKED);

                    if (instance)
                    {
                        for (uint32 i = BOSS_MIMIRON; i < BOSS_VEZAX; ++i)
                            if (instance->GetBossState(i) != DONE)
                                gameObject->SetFlag(GAMEOBJECT_FLAGS,GO_FLAG_LOCKED);
                    }
                    break;
                }
            }
        }

        void OnGameObjectRemove(GameObject* gameObject)
        {
            switch (gameObject->GetEntry())
            {
                case GO_SHIELD_WALL:
                case GO_LEVIATHAN_DOOR:
                case GO_XT002_GATE:
                case GO_IRON_ENTRANCE_DOOR:
                case GO_ARCHIVUM_DOOR:
                case GO_HODIR_ICE_WALL:
                case GO_HODIR_EXIT:
                case GO_HODIR_ENTER:
                case GO_LIGHTNING_FIELD:
                case GO_MIMIRON_DOOR_1:
                case GO_MIMIRON_DOOR_2:
                case GO_MIMIRON_DOOR_3:
                case GO_VEZAX_DOOR:
                case GO_YOGG_GATE:
                    AddDoor(gameObject, false);
                    break;
                default:
                    break;
            }
        }

        void ProcessEvent(GameObject* /*go*/, uint32 eventId)
        {
            // Flame Leviathan's Tower Event triggers
            Creature* FlameLeviathan = instance->GetCreature(LeviathanGUID);

            if (FlameLeviathan && FlameLeviathan->isAlive()) //No leviathan, no event triggering ;)
                switch (eventId)
                {
                    case EVENT_TOWER_OF_STORM_DESTROYED:
                        FlameLeviathan->AI()->DoAction(1);
                        break;
                    case EVENT_TOWER_OF_FROST_DESTROYED:
                        FlameLeviathan->AI()->DoAction(2);
                        break;
                    case EVENT_TOWER_OF_FLAMES_DESTROYED:
                        FlameLeviathan->AI()->DoAction(3);
                        break;
                    case EVENT_TOWER_OF_LIFE_DESTROYED:
                        FlameLeviathan->AI()->DoAction(4);
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
                case BOSS_LEVIATHAN:
                case BOSS_IGNIS:
                case BOSS_RAZORSCALE:
                case BOSS_XT002:
                case BOSS_ASSEMBLY_OF_IRON:
                case BOSS_AURIAYA:
                case BOSS_ALGALON:
                    if (state == DONE)
                        if (GameObject* go = instance->GetGameObject(AlgalonChestGUID))
                            go->SetRespawnTime(go->GetRespawnDelay());
                    break;
                case BOSS_VEZAX:
                    if (state == DONE)
                    {
                        HandleGameObject(VezaxDoorGUID, true);

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
                case BOSS_YOGGSARON:
                    break;
                case BOSS_KOLOGARN:
                    if (state == DONE)
                    {
                        if (GameObject* gameObject = instance->GetGameObject(KologarnChestGUID))
                            gameObject->SetRespawnTime(gameObject->GetRespawnDelay());
                        HandleGameObject(KologarnBridgeGUID, false);
                    }
                    if (state == IN_PROGRESS)
                        HandleGameObject(KologarnDoorGUID, false);
                    else
                        HandleGameObject(KologarnDoorGUID, true);
                    break;
                case BOSS_HODIR:
                    {
                        if (GameObject* gameObject = instance->GetGameObject(HodirChestGUID))
                            gameObject->SetRespawnTime(gameObject->GetRespawnDelay());
                        HandleGameObject(HodirDoorGUID, true);
                        HandleGameObject(HodirIceDoorGUID, true);
                        CheckKeepersState();
                    }
                    break;
                case BOSS_THORIM:
                    if (state == DONE)
                        if (GameObject* go = instance->GetGameObject(ThorimChestGUID))
                            go->SetRespawnTime(go->GetRespawnDelay());

                    if (GameObject* pThorimLever = instance->GetGameObject(uiThorimLeverGUID))
                    {
                        if (state == IN_PROGRESS)
                            pThorimLever->RemoveFlag(GAMEOBJECT_FLAGS,GO_FLAG_UNK1);
                    }

                    CheckKeepersState();
                    break;
                case BOSS_FREYA:
                    if (state == DONE)
                        if (GameObject* go = instance->GetGameObject(FreyaChestGUID))
                            go->SetRespawnTime(go->GetRespawnDelay());

                    CheckKeepersState();
                    break;
                case BOSS_MIMIRON:
                    if (state == NOT_STARTED || state == FAIL)
                        if (GameObject* go = instance->GetGameObject(uiDoNotPushGUID))
                        {
                            go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
                            HandleGameObject(uiDoNotPushGUID, true);
                        }

                    if (state == IN_PROGRESS)
                        if (GameObject* go = instance->GetGameObject(uiDoNotPushGUID))
                        {
                            go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
                            HandleGameObject(uiDoNotPushGUID, false);
                        }

                    if (state == DONE)
                        if (GameObject* go = instance->GetGameObject(MimironChestGUID))
                            go->SetRespawnTime(go->GetRespawnDelay());

                        if (GameObject* go = instance->GetGameObject(uiDoNotPushGUID))
                        {
                            go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
                            HandleGameObject(uiDoNotPushGUID, false);
                        }

                    CheckKeepersState();
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
                    for (uint32 i = BOSS_MIMIRON; i < BOSS_VEZAX; ++i)
                        if (instance->GetBossState(i) != DONE)
                            go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
                }
            }
        }

        void SetData(uint32 type, uint32 data)
        {
            switch (type)
            {
                case TYPE_COLOSSUS:
                    Encounter[TYPE_COLOSSUS] = data;
                    if (data == 2)
                    {
                        if (Creature* Leviathan = instance->GetCreature(LeviathanGUID))
                            Leviathan->AI()->DoAction(10);
                        if (GameObject* gameObject = instance->GetGameObject(LeviathanGateGUID))
                            gameObject->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
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
                    LeftArmGUID = data;
                    break;
                case DATA_RIGHT_ARM:
                    RightArmGUID = data;
                    break;
            }
        }

        uint64 GetData64(uint32 data)
        {
            switch (data)
            {
                case BOSS_LEVIATHAN:
                    return LeviathanGUID;
                case BOSS_IGNIS:
                    return IgnisGUID;
                case BOSS_RAZORSCALE:
                    return RazorscaleGUID;
                case DATA_RAZORSCALE_CONTROL:
                    return RazorscaleController;
                case BOSS_XT002:
                    return XT002GUID;
                case BOSS_KOLOGARN:
                    return KologarnGUID;
                case DATA_LEFT_ARM:
                    return LeftArmGUID;
                case DATA_RIGHT_ARM:
                    return RightArmGUID;
                case BOSS_AURIAYA:
                    return AuriayaGUID;
                case BOSS_MIMIRON:
                    return MimironGUID;
                case BOSS_HODIR:
                    return HodirGUID;
                case BOSS_THORIM:
                    return ThorimGUID;
                case BOSS_FREYA:
                    return FreyaGUID;
                case BOSS_VEZAX:
                    return VezaxGUID;
                case BOSS_YOGGSARON:
                    return YoggSaronGUID;
                case BOSS_ALGALON:
                    return AlgalonGUID;

                // Razorscale expedition commander
                case DATA_EXPEDITION_COMMANDER:
                    return ExpeditionCommanderGUID;
                case GO_RAZOR_HARPOON_1:
                    return RazorHarpoonGUIDs[0];
                case GO_RAZOR_HARPOON_2:
                    return RazorHarpoonGUIDs[1];
                case GO_RAZOR_HARPOON_3:
                    return RazorHarpoonGUIDs[2];
                case GO_RAZOR_HARPOON_4:
                    return RazorHarpoonGUIDs[3];

                // Assembly of Iron
                case BOSS_STEELBREAKER:
                    return AssemblyGUIDs[0];
                case BOSS_MOLGEIM:
                    return AssemblyGUIDs[1];
                case BOSS_BRUNDIR:
                    return AssemblyGUIDs[2];

                // Freya's Keepers
                case BOSS_BRIGHTLEAF:
                    return KeeperGUIDs[0];
                case BOSS_IRONBRANCH:
                    return KeeperGUIDs[1];
                case BOSS_STONEBARK:
                    return KeeperGUIDs[2];
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
            switch (type)
            {
                case TYPE_COLOSSUS:
                    return Encounter[type];
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
