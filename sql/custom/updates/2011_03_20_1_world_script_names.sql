-- Valithria Dreamwalker
-- Creature Script Names
UPDATE `creature_template` SET `ScriptName` = 'boss_valithria_dreamwalker' WHERE `entry` = 36789;
UPDATE `creature_template` SET `ScriptName` = 'npc_dream_portal' WHERE `entry` IN (38186,37945,38429,38430);
UPDATE `creature_template` SET `ScriptName` = 'npc_dream_cloud' WHERE `entry` IN (37985, 38421);
UPDATE `creature_template` SET `ScriptName` = 'npc_column_of_frost' WHERE `entry` = 37918;
UPDATE `creature_template` SET `ScriptName` = 'npc_gluttonous_abomination' WHERE `entry` = 37886;
UPDATE `creature_template` SET `ScriptName` = 'npc_rot_worm' WHERE `entry` = 37907;
UPDATE `creature_template` SET `ScriptName` = 'npc_blistering_zombie' WHERE `entry` = 37934;
UPDATE `creature_template` SET `Scriptname` = 'npc_supresser' WHERE `entry` = 37863;
UPDATE `creature_template` SET `ScriptName` = 'npc_risen_archmage' WHERE `entry` = 37868;
UPDATE `creature_template` SET `ScriptName` = 'npc_blazing_skeleton' WHERE `entry` = 36791;
UPDATE `creature_template` SET `ScriptName` = 'npc_mana_void' WHERE `entry` = 38068;
-- Spell Script Names
DELETE FROM `spell_script_names` WHERE `spell_id` IN (70766, 70873, 71941);
INSERT INTO `spell_script_names` VALUES
(70766, 'spell_dream_state'),
(70873, 'spell_valithria_vigor'),
(71941, 'spell_valithria_vigor');