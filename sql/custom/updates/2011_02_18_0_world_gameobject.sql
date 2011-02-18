---- GameObject Ulduar Data
-- Delete GameObject Chest Spawns (Handled by the Script)
DELETE FROM `gameobject` WHERE `id` IN (195046, 195047, 194307, 194308);

-- Display Instance GameObjects in all instance modes
UPDATE `gameobject` SET `spawnMask` = 3 WHERE `map` = 603;

-- Rare Cache of Winter Spawns
DELETE FROM `gameobject` WHERE `id` IN (194200, 194201);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(NULL, 194200, 603, 1, 1, 2038.29, -200.702, 432.687, 3.12232, 0, 0, 1, 0, 604800, 0, 1),
(NULL, 194201, 603, 2, 1, 2038.29, -200.702, 432.687, 3.12232, 0, 0, 1, 0, 604800, 0, 1);