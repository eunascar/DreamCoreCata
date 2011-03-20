-- Dream Portal
UPDATE `creature_template` SET `unit_flags` = 33554432 WHERE `entry` = 38429;
-- Dream Cloud
UPDATE `creature_template` SET `faction_A` = 14, `faction_H` = 14 WHERE `entry` = 37985;
-- Valithria Trigger
DELETE FROM `creature_template` WHERE `entry` = 38752;
INSERT INTO `creature_template` VALUES
(38752, 0, 0, 0, 0, 0, 26623, 0, 0, 0, 'Green Dragon Combat Trigger', '', '', 0, 80, 80, 2, 16, 16, 0, 1, 1.14286, 1, 1, 1, 2, 0, 1, 1, 2000, 2000, 1, 32832, 8, 0, 0, 0, 0, 0, 1, 2, 126, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, '', 0, 3, 1.35, 1, 1, 0, 0, 0, 0, 0, 0, 0,  0, 1, 358, 803160063, 0, 'npc_green_dragon_combat_trigger', 12340);
UPDATE `creature` SET `spawntimesecs` = 604800 WHERE `id` IN (38008, 38752);