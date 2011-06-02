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

#ifndef DEF_EMERALD_DREAM_H
#define DEF_EMERALD_DREAM_H

uint32 const EncounterCount = 4;

enum Data
{
    DATA_HYOTON           = 0,
    DATA_FIREMIST         = 1,
    DATA_KRITYUS          = 2,
    DATA_UMBRA            = 3,
    DATA_AQUA_GHOST       = 4,
    DATA_AQUA_LEKION      = 5,
    DATA_PYRO_DRAKE       = 6,
    DATA_ISIDORUS         = 7,
    DATA_EMERALD_DREAM    = 8,
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

enum Creatures
{
    NPC_HYOTON            = 150000,
    NPC_FIREMIST          = 150001,
    NPC_KRITYUS           = 150002,
    NPC_UMBRA             = 150003,
    NPC_ANNOUNCER         = 100000,
    NPC_AQUA_SUMMON       = 155049,
    NPC_PYRO_SUMMON       = 155050,
    NPC_AQUA_LEKION       = 200002,
    NPC_AQUA_GHOST        = 200003,
    NPC_HYDRO             = 100001,
    NPC_RAGNAROS          = 100002,
    NPC_KALECGOS          = 100003,
    NPC_ISIDORUS          = 100004,
    NPC_RAGNAROSSTATIC    = 100005,
};

enum Gameobjects
{
    GO_EMERALD_DOOR    = 1000004
};

enum Spells
{
    SPELL_PARACHUTE    = 66516
};

#endif