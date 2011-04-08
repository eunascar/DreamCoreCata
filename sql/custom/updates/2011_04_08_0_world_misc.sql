SET @guid = XXXX;

-- Mimiron Chests Spawn
DELETE FROM `gameobject` WHERE `id` IN (194789, 194956);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@guid, 194789, 603, 1, 65535, 2737.86, 2568.98, 364.314, 0.0139475, 0, 0, 0.00697369, 0.999976, -604800, 100, 1),
(@guid+1, 194956, 603, 2, 65535, 2737.86, 2568.98, 364.314, 0.0139475, 0, 0, 0.00697369, 0.999976, -604800, 100, 1);

-- Aerial Unit VehicleId
UPDATE `creature_template` SET `VehicleId` = 373 WHERE `entry` IN (33670, 34109);

-- Leviathan Mk Flags
UPDATE `creature_template` SET `unit_flags` = 33570816 WHERE `entry` = 34071;