-- Creature Script Names
UPDATE `creature_template` SET `ScriptName`='boss_valithria' WHERE `entry` = 36789;
UPDATE `creature_template` SET `ScriptName`='npc_dreamcloud_icc' WHERE `entry` = 37985;
UPDATE `creature_template` SET `ScriptName`='npc_dreamportal_icc' WHERE `entry` IN (38186,37945,38429,38430);
UPDATE `creature_template` SET `ScriptName`='npc_valithria_alternative' WHERE `entry` = 37950;

-- Spell Script Names
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(70912,'spell_valithria_adds_summon'),
(70913,'spell_valithria_adds_summon'),
(70914,'spell_valithria_adds_summon'),
(70915,'spell_valithria_adds_summon'),
(70916,'spell_valithria_adds_summon'),
(71721,'spell_cancel_all_aura');