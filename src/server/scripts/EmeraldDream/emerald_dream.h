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

enum Data
{
    DATA_HYOTON_EVENT         = 0,
    DATA_FIREMIST_EVENT       = 1,
    DATA_KRITYUS_EVENT        = 2,
    DATA_UMBRA_EVENT          = 3,
    DATA_AQUA_GHOST           = 4,
    DATA_AQUA_LEKION          = 5,
    DATA_PYRO_DRAKE           = 6
};

enum Data64
{
    DATA_HYOTON        = 1,
    DATA_FIREMIST      = 2,
    DATA_KRITYUS       = 3,
    DATA_UMBRA         = 4
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
    NPC_RAGNAROSSTATIC    = 100005
};

enum Gameobjects
{
    GAMEOBJECT_EMERALD_DOOR    = 1000004
};

#endif
