/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2010-2011 Chronos Server <http://chronoserverwow.net/>
 * Copyright (C) 2010 Easy for Trinity <http://trinity-core.ru/>
 * Copyright (C) 2010 Myth Project <http://bitbucket.org/sun/myth-core/>
 * Copyright (C) 2006-2011 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
#include "ruby_sanctum.h"

static const DoorData doorData[5] =
{
    {GO_FIRE_FIELD,   DATA_BALTHARUS,       DOOR_TYPE_PASSAGE, BOUNDARY_NONE},
    {GO_FLAME_WALLS,  DATA_BALTHARUS,       DOOR_TYPE_PASSAGE, BOUNDARY_NONE},
    {GO_FLAME_WALLS,  DATA_RAGEFIRE,        DOOR_TYPE_PASSAGE, BOUNDARY_NONE},
    {GO_FLAME_WALLS,  DATA_ZARITHRIAN,      DOOR_TYPE_ROOM,    BOUNDARY_N   },
    {0,               0,                    DOOR_TYPE_ROOM,    BOUNDARY_NONE}
};

class instance_ruby_sanctum : public InstanceMapScript
{
    public:
        instance_ruby_sanctum() : InstanceMapScript("instance_ruby_sanctum", 724) { }

        struct instance_ruby_sanctum_InstanceMapScript : public InstanceScript
        {
            instance_ruby_sanctum_InstanceMapScript(Map *pMap) : InstanceScript(pMap)
            {
                SetBossNumber(MAX_ENCOUNTER);
                LoadDoorData(doorData);

                m_dataDamage = 0;

                uiXerestrasza = 0;
                uiTwilightHalion = 0;

                uiHalionPortalGUID = 0;
                uiTwilightPortalGUID = 0;
                uiBaltharusGUID = 0;
                uiZarithrianGUID = 0;
                uiRagefireGUID = 0;
                uiHalionGUID = 0;
                uiXerestraszaGUID = 0;
                uiTwilightHalionGUID = 0;
                uiGOFlameWallsGUID = 0;
                uiGOTwilightWallsGUID = 0;
            }

            void OnCreatureCreate(Creature* creature)
            {
                switch(creature->GetEntry())
                {
                    case NPC_BALTHARUS:
                        uiBaltharusGUID = creature->GetGUID();
                        break;
                    case NPC_RAGEFIRE:
                        uiRagefireGUID = creature->GetGUID();
                        break;
                    case NPC_XERESTRASZA:
                        uiXerestraszaGUID = creature->GetGUID();
                        break;
                    case NPC_ZARITHRIAN:
                        uiZarithrianGUID = creature->GetGUID();

                        if (GetBossState(DATA_RAGEFIRE) == DONE && GetBossState(DATA_BALTHARUS) == DONE)
                        {
                            creature->SetReactState(REACT_AGGRESSIVE);
                            creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        }
                        else
                        {
                            creature->SetReactState(REACT_PASSIVE);
                            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        }
                        break;
                    case NPC_HALION:        
                        uiHalionGUID = creature->GetGUID();

                        if (GetBossState(DATA_ZARITHRIAN) == DONE && GetBossState(DATA_RAGEFIRE) == DONE && GetBossState(DATA_BALTHARUS) == DONE)
                        {
                            creature->SetVisible(true);
                            creature->SetReactState(REACT_AGGRESSIVE);
                            creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        }
                        else
                        {
                            creature->SetVisible(false);
                            creature->SetReactState(REACT_PASSIVE);
                            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        }
                        break;
                    case NPC_TWILIGHT_HALION:
                        uiTwilightHalionGUID = creature->GetGUID();
                        break;
                }
            }

            void OnGameObjectCreate(GameObject* go, bool add)
            {
                switch (go->GetEntry())
                {
                    case GO_FIRE_FIELD:
                    case GO_FLAME_WALLS:
                    //case GO_FLAME_WALLS2:
                        AddDoor(go, add);
                        break;
                    case GO_TWILIGHT_PORTAL1:
                        uiHalionPortalGUID = go->GetGUID();
                        break;
                    case GO_TWILIGHT_PORTAL2:
                        uiTwilightPortalGUID = go->GetGUID();
                        break;
                    case GO_FLAME_WALLS2:
                        uiGOFlameWallsGUID = go->GetGUID();
                        break;
                    case GO_FLAME_WALLS3:
                        uiGOTwilightWallsGUID = go->GetGUID();
                        break;
                    default:
                        break;
                }
            }

            void SetData(uint32 type, uint32 data)
            {
                switch(type)
                {
                    case DATA_XERESTRASZA:
                        uiXerestrasza = data;
                        break;
                    case DATA_TWILIGHT_HALION:
                        uiTwilightHalion = data;
                        break;
                    case DATA_DAMAGE:
                        m_dataDamage = data;
                        break;   
                }
            }

            uint32 GetData(uint32 type)
            {
                switch(type)
                {
                    case DATA_XERESTRASZA:
                        return uiXerestrasza;
                        break;
                    case DATA_TWILIGHT_HALION:
                        return uiTwilightHalion;
                        break;
                    case DATA_DAMAGE:
                        return m_dataDamage;
                        break;
                }
                return 0;
            }

            void BossZarithrian()
            {
                if (Creature* Zarithrian = instance->GetCreature(GetData64(DATA_ZARITHRIAN)))
                {
                    Zarithrian->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    Zarithrian->SetReactState(REACT_AGGRESSIVE);
                }
            }

            bool SetBossState(uint32 type, EncounterState state)
            {
                if (!InstanceScript::SetBossState(type, state))
                    return false;

                switch (type)
                {
                    case DATA_BALTHARUS:
                        if (state == DONE)
                            if (GetBossState(DATA_RAGEFIRE)==DONE)
                                BossZarithrian();
                        break;
                    case DATA_RAGEFIRE: 
                        if (state == DONE)
                            if (GetBossState(DATA_BALTHARUS) == DONE)
                                BossZarithrian();
                        break;
                    case DATA_ZARITHRIAN:
                        if (GetBossState(DATA_BALTHARUS)==DONE && GetBossState(DATA_RAGEFIRE)==DONE)
                            if (state == DONE)
                                if (Creature* halion = instance->GetCreature(GetData64(DATA_HALION)))
                                    halion->SummonCreature(NPC_SUMMON_HALIOH,SpawnPosHalion,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,20000);
                        break;
                    case DATA_HALION: break;
                }

                return true;
            }

            uint64 GetData64(uint32 data)
            {
                switch(data)
                {
                    case DATA_BALTHARUS:
                        return uiBaltharusGUID;
                        break;
                    case DATA_ZARITHRIAN:
                        return uiZarithrianGUID;
                        break;
                    case DATA_RAGEFIRE:
                        return uiRagefireGUID;
                        break;
                    case DATA_HALION:
                        return uiHalionGUID;
                        break;
                    case DATA_TWILIGHT_HALION:
                        return uiTwilightHalionGUID;
                        break;
                    case DATA_XERESTRASZA:
                        return uiXerestraszaGUID;
                        break;
                    case GO_TWILIGHT_PORTAL1:
                        return uiHalionPortalGUID;
                        break;
                    case GO_TWILIGHT_PORTAL2:
                        return uiTwilightPortalGUID;
                        break;
                    case GO_FLAME_WALLS2:
                        return uiGOFlameWallsGUID;
                        break; 
                    case GO_FLAME_WALLS3:
                        return uiGOTwilightWallsGUID;
                        break; 
                    default: break;
                }

                return 0;
            }

            std::string GetSaveData()
            {
                std::ostringstream saveStream;
                saveStream << GetBossSaveData() << " " << uiXerestrasza;
                return saveStream.str();
            }

            void Load(const char* strIn)
            {
                if (!strIn)
                {
                    return;
                }

                std::istringstream loadStream(strIn);

                uint32 tmpState;
                
                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                {
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;
                    SetBossState(i, EncounterState(tmpState));
                }

                loadStream >> uiXerestrasza;
            }

            private:
                uint32 uiXerestrasza;
                uint32 uiTwilightHalion;
                uint32 m_dataDamage;

                uint64 uiBaltharusGUID;
                uint64 uiZarithrianGUID;
                uint64 uiRagefireGUID;
                uint64 uiHalionGUID;
                uint64 uiXerestraszaGUID;
                uint64 uiTwilightHalionGUID;
                uint64 uiHalionPortalGUID;
                uint64 uiTwilightPortalGUID;
                uint64 uiGOFlameWallsGUID;
                uint64 uiGOTwilightWallsGUID;
        };
        
        InstanceScript* GetInstanceScript (InstanceMap *pMap) const
        {
            return new instance_ruby_sanctum_InstanceMapScript(pMap);
        }
};

void AddSC_instance_ruby_sanctum()
{
    new instance_ruby_sanctum();
}
