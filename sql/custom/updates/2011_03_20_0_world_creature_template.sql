UPDATE `creature_template` SET `npcflag` = 3, `baseattacktime` = 2000, `dynamicflags` = 0, `equipment_id` = 1290, `flags_extra` = 2 WHERE `entry` = 3759601;
-- Drudge Ghoul
UPDATE `creature_template` SET `mindmg` = 420, `maxdmg` = 630, `attackpower` = 157, `rangeattacktime` = 2000, `minrangedmg` = 336, `maxrangedmg` = 504, `rangedattackpower` = 126 WHERE `entry` IN (37695, 39309, 39310, 39311);
UPDATE `creature_template` SET `dmg_multiplier` = 10 WHERE `entry` = 37695;
UPDATE `creature_template` SET `dmg_multiplier` = 15 WHERE `entry` IN (39309, 39310);
UPDATE `creature_template` SET `dmg_multiplier` = 20 WHERE `entry` =  39311;
-- Remove Unused Spell Script
DELETE FROM `spell_script_names` WHERE `spell_id` = 73159;