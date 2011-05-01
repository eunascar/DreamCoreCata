SET @guid_creature    = XXXX;
SET @guid_go          = XXXX;

-- Spell Script Names Missing for Toc5
DELETE FROM `spell_script_names` WHERE `spell_id` IN (62575, 63010, 66515, 68504);
INSERT INTO `spell_script_names` VALUES
(62575, 'spell_gen_shieldbreaker'),
(63010, 'spell_gen_atcharge'),
(66515, 'spell_gen_reflective_shield'),
(68504, 'spell_gen_npcshieldbreaker');

-- Spell Script Names Missing for Algalon
DELETE FROM `spell_script_names` WHERE `spell_id` IN (62293, 62295, 62301, 64598, 62304, 64597, 62311, 64596);
INSERT INTO `spell_script_names` VALUES
(62301, 'spell_cosmic_smash'),
(64598, 'spell_cosmic_smash'),
(62293, 'spell_cosmic_smash_summon_trigger'),
(62295, 'spell_cosmic_smash_summon_target'),
(62304, 'spell_cosmic_smash_missile_target'),
(64597, 'spell_cosmic_smash_missile_target'),
(62311, 'spell_cosmic_smash_dmg'),
(64596, 'spell_cosmic_smash_dmg');

-- Creature Script Names for Algalon Script
UPDATE `creature_template` SET `ScriptName` = 'npc_living_constellation' WHERE `entry` = 33052;
UPDATE `creature_template` SET `ScriptName` = 'npc_black_hole' WHERE `entry` = 32953;

-- GameObject Script Names for Algalon Script
UPDATE `gameobject_template` SET `ScriptName` = 'go_planetarium_access' WHERE `entry` IN (194767, 194911);

-- Algalon Spawn
DELETE FROM `creature` WHERE `guid` = @guid_creature;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@guid_creature, 32871, 603, 3, 1, 0, 0, 1632.9, -307.9, 417.4, 1.58686, 7200, 0, 0, 8367000, 0, 0, 0, 0, 0, 0);

-- Update Some GO Spawns with YTDB Values
DELETE FROM `gameobject` WHERE `guid` IN (46313, 42917, 34038);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
-- Doodad_UL_UniverseFloor_01
(46313, 194715, 603, 3, 1, 1632.05, -307.654, 417.321, 0, 0, 0, 0, 0, 604800, 100, 0),
-- Doodad_UL_UniverseGlobe01
(42917, 194148, 603, 3, 1, 1632.05, -307.654, 417.321, 0, 0, 0, 0, 0, 604800, 100, 1),
-- Doodad_UL_Ulduar_Trapdoor_03
(34038, 194253, 603, 3, 1, 1631.91, -246.497, 417.321, 0, 0, 0, 0, 0, 604800, 0, 1);

UPDATE `gameobject_template` SET `faction` = 0 WHERE `entry` IN (194767, 194911);
UPDATE `gameobject` SET `spawntimesecs` = 604800, `animprogress` = 100, `state` = 1 WHERE `id` IN (194767, 194911, 194716);

DELETE FROM `gameobject` WHERE `guid` IN (@guid_go, @guid_go+1);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@guid_go, 194821, 603, 2, 65535, 1632.53, -295.983, 417.322, 1.56774, 0, 0, 0.706026, 0.708186, -604800, 100, 1),
(@guid_go+1, 194822, 603, 1, 65535, 1632.53, -295.983, 417.322, 1.56774, 0, 0, 0.706026, 0.708186, -604800, 100, 1);