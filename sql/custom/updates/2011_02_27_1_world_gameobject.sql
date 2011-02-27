SET @guid =  5003807;

-- Cache of Dreamwalker GameObject Spawns
DELETE FROM `gameobject` WHERE `id` IN (201959, 202338, 202339, 202340);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@guid, 201959, 631, 1, 1, 4221.01, 2484.39, 364.872, 6.20305, 0, 0, 0.0400554, -0.999197, -604800, 100, 1),
(@guid+1, 202338, 631, 4, 1, 4221.01, 2484.39, 364.872, 6.20305, 0, 0, 0.0400554, -0.999197, -604800, 100, 1),
(@guid+2, 202339, 631, 2, 1, 4221.01, 2484.39, 364.872, 6.20305, 0, 0, 0.0400554, -0.999197, -604800, 100, 1),
(@guid+3, 202340, 631, 8, 1, 4221.01, 2484.39, 364.872, 6.20305, 0, 0, 0.0400554, -0.999197, -604800, 100, 1);
