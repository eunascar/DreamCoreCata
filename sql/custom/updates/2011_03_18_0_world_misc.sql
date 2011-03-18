-- Sindragosa Creature Location
DELETE FROM `creature` WHERE `id` = 36853;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(5049228, 36853, 631, 15, 1, 30362, 0, 4408.3, 2484.5, 203.5, 3.2, 604800, 0, 0, 13945000, 0, 0, 0, 0, 0, 0);
-- Lich King Plataform Entities Spawn Relocation
UPDATE `creature` SET `position_z` = 1064.96, `orientation` = 0.120937 WHERE `id` = 36597;
UPDATE `creature` SET `position_z` = 1040.94, `orientation` = 3.14159 WHERE `id` = 38995;
UPDATE `gameobject` SET `position_z` = 1036.61, `rotation0` = 7.7568, `rotation3` = 0, `animprogress` = 100 WHERE `id` = 202161;
UPDATE `gameobject` SET `position_z` = 1036.61, `rotation0` = 5.855, `animprogress` = 100 WHERE `id` = 202161;
UPDATE `gameobject` SET `position_z` = 1040.52, `animprogress` = 100 WHERE `id` = 202190;
UPDATE `gameobject` SET `position_z` = 1040.86, `animprogress` = 100 WHERE `id` IN (202144, 202141, 202142);
UPDATE `gameobject` SET `position_z` = 1058.68, `animprogress` = 100 WHERE `id` = 202437;
UPDATE `gameobject` SET `position_z` = 1064.89, `animprogress` = 100 WHERE `id` = 202436;
UPDATE `spell_target_position` SET `target_position_z` = `target_position_z` + 10 WHERE `id` = 70860;