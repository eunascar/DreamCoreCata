-- Auriaya
UPDATE `creature_template` SET `baseattacktime` = 1500, `equipment_id` = 2422 WHERE `entry` IN (33515, 34175);
UPDATE `creature_model_info` SET `bounding_radius` = 0.775, `combat_reach` = 5 WHERE `modelid` = 28651;
UPDATE `creature_template` SET `mechanic_immune_mask` = 536870912 WHERE `entry` IN (34014, 34166);
UPDATE `creature_template` SET `speed_walk` = 2, `dmg_multiplier` = 3.5 WHERE `entry` = 34035;
UPDATE `creature_template` SET `speed_walk` = 2, `dmg_multiplier` = 5, `baseattacktime` = 1500 WHERE `entry` = 34171;
UPDATE `creature_template` SET `dmg_multiplier` = 1.5, `baseattacktime` = 1500 WHERE `entry` = 34169;

-- Hodir
UPDATE `creature_template` SET `mechanic_immune_mask` = 650854239 WHERE `entry` = 32845;
UPDATE `creature_template` SET `equipment_id` = 1843, `mechanic_immune_mask` = 650854239 WHERE `entry` = 32846;
UPDATE `creature_template` SET `difficulty_entry_1` = 33352, `mechanic_immune_mask` = 612597599 WHERE `entry` = 32926;
UPDATE `creature_template` SET `difficulty_entry_1` = 33353, `mechanic_immune_mask` = 612597599 WHERE `entry` = 32938;
UPDATE `creature_template` SET `mechanic_immune_mask` = 612597599 WHERE `entry` IN (33352, 33353);
UPDATE `gameobject_template` SET `flags` = 4 WHERE `entry` = 194173;
-- Delete Spawns Handled by the Script
DELETE FROM `creature` WHERE `id` IN (32950, 32941, 32948, 32946, 32938);

-- Mimiron Tram
SET @guid = 5003811;
DELETE FROM gameobject_template WHERE entry = 194438;
DELETE FROM gameobject WHERE id IN (194437, 194438);
UPDATE `gameobject_template` SET `flags` = 32 WHERE `entry` IN (194914, 194912, 194437);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`, `WDBVerified`) VALUES
(194438, 1, 8504, 'Activate Tram', '', '', '', 0, 32, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'go_call_tram', 12340);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(45164, 194437, 603, 1, 1, 2306.87, 274.237, 424.288, 1.52255, 0, 0, 0.689847, 0.723956, 300, 0, 1),
(@guid, 194438, 603, 1, 1, 2306.99, 2589.35, 424.382, 4.71676, 0, 0, 0.705559, -0.708651, 300, 0, 1);

-- Mimiron
UPDATE `creature_template` SET `mechanic_immune_mask` = 650854235 WHERE `entry` IN (33350, 34071);
-- Leviathan Mk II
UPDATE `creature_template` SET `vehicleid` = 370, `mechanic_immune_mask` = 650854235 WHERE `entry` = 33432;
UPDATE `creature_template` SET `minlevel` = 83, `maxlevel` = 83, `vehicleid` = 370, `mechanic_immune_mask` = 650854235 WHERE `entry` = 34106;
-- Ulduar Vehicle Spells for Mimiron Encounter
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (33432, 33651);
INSERT INTO `npc_spellclick_spells` (`npc_entry`,`spell_id`,`quest_start`,`quest_start_active`,`quest_end`,`cast_flags`,`aura_required`,`aura_forbidden`,`user_type`) VALUES
(33432,46598,0,0,0,0,0,0,0), -- Leviathan MK II
(33651,46598,0,0,0,0,0,0,0); -- VX-001
-- Vehicle for Leviathan Mk II
DELETE FROM vehicle_template_accessory WHERE entry = 33432;
INSERT INTO vehicle_template_accessory VALUE (33432, 34071, 3, 1, 'Leviathan Mk II turret', 8, 0);
UPDATE `creature_model_info` SET `bounding_radius` = 0.5 WHERE `modelid` = 28831;
-- VX-001
UPDATE `creature_template` SET `mechanic_immune_mask` = 650854235, `vehicleid` = 371 WHERE `entry` = 33651;
UPDATE `creature_template` SET `minlevel` = 83, `maxlevel` = 83, `vehicleid` = 371 ,`mechanic_immune_mask` = 650854235 WHERE `entry` = 34108;
UPDATE `creature_template` SET `faction_A` = 35, `faction_H` = 35 WHERE `entry` = 34050;
UPDATE `creature_template` SET `unit_flags` = 33686020, `flags_extra` = 2 WHERE `entry` = 34211;
-- Aerial Command Unit
UPDATE `creature_template` SET `mechanic_immune_mask` = 650854235 WHERE `entry` = 33670;
UPDATE `creature_template` SET `minlevel` = 83, `maxlevel` = 83, `mechanic_immune_mask` = 650854235 WHERE `entry` = 34109;
UPDATE `creature_template` SET `difficulty_entry_1` = 34148 WHERE `entry` = 34147;
-- HardMode
UPDATE `gameobject_template` SET `flags` = 32 WHERE `entry` = 194739;
UPDATE `creature_template` SET `difficulty_entry_1` = 34361 WHERE `entry` = 34149;
UPDATE `creature_template` SET `speed_walk` = 0.15, `speed_run` = 0.15 WHERE `entry` = 34363;
-- CleanUp
DELETE FROM creature WHERE id IN (34071, 33856);
UPDATE `creature_template` SET `flags_extra` = 2 WHERE `entry` = 34143;

-- Freya
UPDATE `creature_template` SET `baseattacktime` = 1500, `mechanic_immune_mask` = 650854235 WHERE `entry` IN (32906, 33360);
-- Elders
UPDATE `creature_template` SET `mechanic_immune_mask` = 650854235 WHERE `entry` IN (32915, 32913, 32914);
UPDATE `creature_template` SET `speed_walk` = 1.66666 WHERE `entry` IN (33393, 33392, 33391);
-- Iron roots
UPDATE `creature_template` SET `difficulty_entry_1` = 33397, `mechanic_immune_mask` = 650854239 WHERE `entry` = 33168;
UPDATE `creature_template` SET `difficulty_entry_1` = 33396, `mechanic_immune_mask` = 650854239 WHERE `entry` = 33088;
UPDATE `creature_template` SET `mechanic_immune_mask` = 650854239 WHERE `entry` IN (33396, 33397);
-- Eonar Gift
UPDATE `creature_template` SET `mechanic_immune_mask` = 650854235 WHERE `entry` IN (33228, 33385);
-- Nature Bomb
UPDATE `gameobject_template` SET `flags` = 4 WHERE `entry` = 194902;
-- Detonating Lasher
UPDATE `creature_template` SET `flags_extra` = 256 WHERE `entry` IN (32918, 33399);
-- Ancient Conservator
UPDATE `creature_template` SET `mechanic_immune_mask` = 650853979 WHERE `entry` IN (33203, 33376);
-- Cleanup
DELETE FROM `creature` WHERE id = 33575;

-- Thorim
UPDATE `creature_template` SET `speed_walk` = 1.66667, `mechanic_immune_mask` = 650854239 WHERE `entry` = 32865;
UPDATE `creature_template` SET `speed_walk` = 1.66667, `baseattacktime` = 1500, `equipment_id` = 1844, `mechanic_immune_mask` = 650854239 WHERE `entry` = 33147;
DELETE FROM `creature` WHERE `id` = 32865;
INSERT INTO `creature` (`guid`, `id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(136384, 32865, 603, 3, 1, 28977, 0, 2134.967, -298.962, 438.331, 1.57, 604800, 0, 0, 4183500, 425800, 0, 1);
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = 62042;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
('62042','62470','1','Thorim: Deafening Thunder');
-- Charge Orb
DELETE FROM conditions WHERE SourceEntry = 62016;
INSERT INTO `conditions` VALUES
('13','0','62016','0','18','1','33378','0','0','',NULL);
UPDATE `creature_template` SET `unit_flags` = 33685508 WHERE `entry` = 33378;
-- Gate
DELETE FROM `gameobject_scripts` WHERE `id` = 55194;
INSERT INTO `gameobject_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`) VALUES 
(55194, 0, 11, 34155, 15, 0, 0, 0, 0, 0);
DELETE FROM `gameobject_template` WHERE `entry` = 194265;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`, `WDBVerified`) VALUES
(194265, 1, 295, 'Lever', '', '', '', 0, 16, 3, 0, 0, 0, 0, 0, 0, 0, 0, 6000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0);
UPDATE `gameobject` SET `id` = 194265, `rotation2` = 1, `rotation3` = 0, `spawntimesecs` = 7200, `animprogress` = 100 WHERE `guid` = 55194;
-- Cleanup
DELETE FROM `creature` WHERE `id` IN (32885, 32883, 32908, 32907, 32882, 33110, 32886, 32879, 32892, 33140, 33141, 33378, 32874, 32875);
-- Pre adds
UPDATE `creature_template` SET `equipment_id` = 1849 WHERE `entry` = 33153;
UPDATE `creature_template` SET `equipment_id` = 1847 WHERE `entry` = 33152;
UPDATE `creature_template` SET `equipment_id` = 1850 WHERE `entry` = 33151;
UPDATE `creature_template` SET `equipment_id` = 1852 WHERE `entry` = 33150;
UPDATE `creature_template` SET `modelid1` = 16925, `modelid2` = 0 WHERE `entry`IN (33378, 32892);
-- Thorim Mini bosses
UPDATE `creature_template` SET `mechanic_immune_mask` = 650854239 WHERE `entry` IN (32872, 32873, 33196);
DELETE FROM `creature_addon` WHERE `guid` IN (136059, 136816);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
('136059','0','0','0','1','0','40775 0'),
('136816','0','0','0','1','0','40775 0');