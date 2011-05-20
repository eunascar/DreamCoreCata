SET @guid = XXXX;

-- Kologarn Triggers Data
UPDATE `creature_template` SET `flags_extra` = 130 WHERE `entry` IN (33632, 33802, 33906, 33907, 33809, 33942);
UPDATE `creature_template` SET `modelid1` = 11686, `modelid2` = 11686 WHERE `entry` IN (33632, 33802, 33906, 33907, 33809, 33942, 33661);
UPDATE `creature_template` SET `flags_extra` = 128 WHERE `entry` = 33661;

-- VehicleId for Kologarn Arms
UPDATE `creature_template` SET `VehicleId` = 380 WHERE `entry` IN (33911, 32933, 33910);

-- Kologarn Chest Spawns
DELETE FROM `gameobject` WHERE `guid` IN (@guid, @guid+1);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@guid, 195046, 603, 1, 1, 1837.59, -35.6824, 448.808, 3.18959, 0, 0, 0.999712, -0.0239958, -604800, 100, 1),
(@guid+1, 195047, 603, 2, 1, 1859.45, -24.099, 448.809, 3.18959, 0, 0, 0.999712, -0.0239958, -604800, 100, 1);