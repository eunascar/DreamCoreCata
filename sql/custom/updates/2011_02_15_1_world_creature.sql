-- Ruby Sanctum: Halion Spawn
DELETE FROM `creature` WHERE `id` = 39863 AND `map` = 724;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
(NULL, 39863, 724, 15, 1, 0, 0, 3144.93, 527.233, 72.8887, 0.110395, 300, 0, 0, 11156000, 0, 0, 0);