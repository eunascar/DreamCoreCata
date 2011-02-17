-- Ruby Sanctum Script Names
UPDATE `instance_template` SET `script` = 'instance_ruby_sanctum' WHERE `map` = 724;
UPDATE `creature_template` SET `ScriptName` = 'boss_baltharus' WHERE `entry` = 39751;
UPDATE `creature_template` SET `ScriptName` = 'boss_baltharus_summon' WHERE `entry` = 39899;
UPDATE `creature_template` SET `ScriptName` = 'npc_xerestrasza' WHERE `entry` = 40429;
UPDATE `creature_template` SET `ScriptName` = 'boss_zarithrian' WHERE `entry` = 39746;
UPDATE `creature_template` SET `ScriptName` = 'boss_ragefire' WHERE `entry` = 39747;
UPDATE `creature_template` SET `ScriptName` = 'boss_halion' WHERE `entry` = 39863;
UPDATE `creature_template` SET `ScriptName` = 'boss_twilight_halion' WHERE `entry` = 40142;
UPDATE `creature_template` SET `ScriptName` = 'npc_onyx_flamecaller' WHERE `entry` = 39814;
UPDATE `creature_template` SET `ScriptName` = 'npc_meteor_strike', `flags_extra` = 128 WHERE `entry` = 40041;
UPDATE `creature_template` SET `ScriptName` = 'npc_meteor_flame', `flags_extra` = 128 WHERE `entry` = 40042;
UPDATE `creature_template` SET `ScriptName` = 'npc_spell_meteor_strike', `flags_extra` = 128 WHERE `entry` = 40029;
UPDATE `creature_template` SET `name` = 'summon halion', `ScriptName` = 'npc_summon_halion', `flags_extra` = 128 WHERE `entry` = 40044;
