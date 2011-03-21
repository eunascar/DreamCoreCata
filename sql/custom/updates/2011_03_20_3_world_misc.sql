-- Startup Errors Fix
UPDATE `smart_scripts` SET `event_param1` = 0, `event_param2` = 15 WHERE `entryorguid` = 29129 AND `id` = 4;
UPDATE `smart_scripts` SET `event_param1` = 30, `event_param2` = 100 WHERE `entryorguid` = 29129 AND `id` = 8;

-- Script Texts Modification
DELETE FROM `script_texts` WHERE `npc_entry` = 36789;
INSERT INTO `script_texts`(`npc_entry`, `entry`, `content_default`, `sound`, `type`, `language`, `emote`, `comment`) VALUES
(36789, -1666068, 'A tragic loss...', 17066, 1, 0, 0, 'Valithria Dreamwalker - SAY_PDEATH'),
(36789, -1666069, 'FAILURES!', 17067, 1, 0, 0, 'Valithria Dreamwalker - SAY_BERSERK');
DELETE FROM `creature_text` WHERE `entry` = 36789 AND `comment` = 'Valithria Dreamwalker - SAY_PDEATH';
DELETE FROM `creature_text` WHERE `entry` = 36789 AND `comment` = 'Valithria Dreamwalker - SAY_BERSERK';
UPDATE `creature_text` SET `groupid` = 5 WHERE `entry` = 36789 AND `comment` = 'Valithria Dreamwalker - SAY_END';

-- Dream State Portal Data
UPDATE `creature_template` SET `npcflag` = 16777216 WHERE `entry` IN (37945, 38430);
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (37945, 38430);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `quest_start`, `quest_start_active`, `quest_end`, `cast_flags`, `aura_required`, `aura_forbidden`, `user_type`) VALUES
(37945, 70766, 0, 0, 0, 3, 0, 0, 0),
(38430, 70766, 0, 0, 0, 3, 0, 0, 0);

-- Fix Combat Trigger Display Model
UPDATE `creature_template` SET `modelid1` = 15294 WHERE `entry` = 38752;
-- Make "The Lich King" Invisible
UPDATE `creature_template` SET `flags_extra` = 128 WHERE `entry` = 16980;
-- Delete Risen Archmage Spawns
DELETE FROM `creature` WHERE `id` = 37868;