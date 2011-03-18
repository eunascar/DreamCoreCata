-- Lich King Additional Script Names
UPDATE `creature_template` SET `ScriptName` = 'npc_shambling_horror_icc' WHERE `entry` = 37698;
UPDATE `creature_template` SET `ScriptName` = 'npc_raging_spirit_icc' WHERE `entry` = 36701;
UPDATE `creature_template` SET `ScriptName` = 'npc_ice_sphere_icc' WHERE `entry` = 36633;
UPDATE `creature_template` SET `ScriptName` = 'npc_defile_icc' WHERE `entry` = 38757;
UPDATE `creature_template` SET `ScriptName` = 'npc_terenas_fighter_icc' WHERE `entry` = 36823;
UPDATE `creature_template` SET `ScriptName` = 'npc_spirit_warden_icc' WHERE `entry` = 36824;
-- Lich King Additional Spell Script Names
DELETE FROM `spell_script_names` WHERE `spell_id` = 68765;
INSERT INTO `spell_script_names` VALUES
(72743, 'spell_lich_king_defile'),
(72429, 'spell_lich_king_tirion_mass_resurrection'),
(74115, 'spell_lich_king_pain_and_suffering'),
(68576, 'spell_valkyr_eject_passenger'),
(72133, 'spell_lich_king_pain_and_suffering_effect'),
(73789, 'spell_lich_king_pain_and_suffering_effect'),
(73788, 'spell_lich_king_pain_and_suffering_effect'),
(73790, 'spell_lich_king_pain_and_suffering_effect'),
(70498, 'spell_lich_king_vile_spirit_summon'),
(70500, 'spell_lich_king_vile_spirit_summon_visual'),
(68980, 'spell_lich_king_harvest_soul'),
(74325, 'spell_lich_king_harvest_soul');