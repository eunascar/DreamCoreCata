-- Lich King Script Names
UPDATE `creature_template` SET `ScriptName`='boss_the_lich_king' WHERE `entry` = 36597;
UPDATE `creature_template` SET `ScriptName`='npc_tirion_icc' WHERE `entry`= 38995;
UPDATE `creature_template` SET `ScriptName`='npc_valkyr_icc' WHERE `entry` = 36609;
UPDATE `creature_template` SET `ScriptName`='npc_vile_spirit_icc' WHERE `entry`= 37799;
-- Spell Script Names
DELETE FROM `spell_script_names` WHERE `ScriptName` IN ('spell_lich_king_necrotic_plague', 'spell_lich_king_infection', 'spell_lich_king_valkyr_summon', 'spell_lich_king_winter', 'spell_vile_spirit_distance_check', 'spell_ice_burst_distance_check', 'spell_lich_king_quake', 'spell_lich_king_play_movie', 'spell_valkyr_carry_can_cast', 'spell_valkyr_target_search', 'spell_valkyr_eject_passanger', 'spell_vile_spirit_target_search');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(70338,'spell_lich_king_necrotic_plague'),
(73785,'spell_lich_king_necrotic_plague'),
(73786,'spell_lich_king_necrotic_plague'),
(73787,'spell_lich_king_necrotic_plague'),
(70541,'spell_lich_king_infection'),
(73779,'spell_lich_king_infection'),
(73780,'spell_lich_king_infection'),
(73781,'spell_lich_king_infection'),
(74361,'spell_lich_king_valkyr_summon'),
(68981,'spell_lich_king_winter'),
(74270,'spell_lich_king_winter'),
(74271,'spell_lich_king_winter'),
(74272,'spell_lich_king_winter'),
(70534,'spell_vile_spirit_distance_check'),
(69110,'spell_ice_burst_distance_check'),
(72262,'spell_lich_king_quake'),
(73159,'spell_lich_king_play_movie'),
(74506,'spell_valkyr_carry_can_cast'),
(69030,'spell_valkyr_target_search'),
(68765,'spell_valkyr_eject_passanger'),
(70501,'spell_vile_spirit_target_search');