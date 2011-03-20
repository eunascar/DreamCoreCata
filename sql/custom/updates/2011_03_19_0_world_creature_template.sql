-- The Lich King
UPDATE `creature_template` SET `exp` = 2, `faction_A` = 974, `faction_H` = 974, `speed_walk` = 2, `speed_run` = 1.71429, `unit_flags` = 768, `mechanic_immune_mask` = 667631615 WHERE `entry` IN (36597, 39166, 39167, 39168);
UPDATE `creature_template` SET `mindmg` = 351, `maxdmg` = 526, `attackpower` = 132, `dmg_multiplier` = 133.4, `rangeattacktime` = 1500, `minrangedmg` = 281, `maxrangedmg` = 421, `rangedattackpower` = 106 WHERE `entry` = 36597;
UPDATE `creature_template` SET `mindmg` = 468, `maxdmg` = 702, `attackpower` = 175, `dmg_multiplier` = 150, `minrangedmg` = 374, `maxrangedmg` = 562, `rangedattackpower` = 140 WHERE `entry` IN (39166, 39167, 39168);
-- Tirion Fordring
UPDATE `creature_template` SET `exp` = 2, `mindmg` = 468, `maxdmg` = 702, `attackpower` = 175, `dmg_multiplier` = 47.2, `rangeattacktime` = 2000, `unit_class` = 2, `minrangedmg` = 374, `maxrangedmg` = 562, `rangedattackpower` = 140, `mechanic_immune_mask` = 12584976 WHERE `entry` = 38995;
-- Val'kyr Shadowguard
UPDATE `creature_template` SET `minlevel` = 81, `maxlevel` = 81, `exp` = 2, `faction_A` = 14, `faction_H` = 14, `speed_walk` = 2, `speed_run` = 1.71429, `mindmg` = 318, `maxdmg` = 478, `attackpower` = 119, `dmg_multiplier` = 2, `baseattacktime` = 2000, `rangeattacktime` = 2000, `unit_class` = 8, `unit_flags` = 33554944, `dynamicflags` = 8, `minrangedmg` = 254, `maxrangedmg` = 382, `rangedattackpower` = 95, `mechanic_immune_mask` = 12584976 WHERE `entry` IN (36609, 39120, 39121, 39122);
-- Vile Spirit
UPDATE `creature_template` SET `mindmg` = 391, `maxdmg` = 585, `attackpower` = 146, `dmg_multiplier` = 2, `baseattacktime` = 2000, `rangeattacktime` = 2000, `unit_class` = 2, `dynamicflags` = 8, `minrangedmg` = 313, `maxrangedmg` = 468, `rangedattackpower` = 117 WHERE `entry` IN (37799, 39284, 39285, 39286);
-- Shambling Horror
UPDATE `creature_template` SET `mindmg` = 468, `maxdmg` = 702, `attackpower` = 175, `dmg_multiplier` = 2, `baseattacktime` = 2000, `rangeattacktime` = 2000, `dynamicflags` = 8, `minrangedmg` = 313, `maxrangedmg` = 562, `rangedattackpower` = 140 WHERE `entry` IN (37698, 39299, 39300, 39301);
UPDATE `creature_template` SET `dmg_multiplier` = 47.2 WHERE `entry` = 37698;
UPDATE `creature_template` SET `dmg_multiplier` = 70.8 WHERE `entry` = 39299;
UPDATE `creature_template` SET `dmg_multiplier` = 70.8 WHERE `entry` = 39300;
UPDATE `creature_template` SET `dmg_multiplier` = 94.4 WHERE `entry` = 39301;
-- Raging Spirit
UPDATE `creature_template` SET `difficulty_entry_1` = 39302 WHERE `entry` = 36701;
UPDATE `creature_template` SET `difficulty_entry_2` = 39303 WHERE `entry` = 36701;
UPDATE `creature_template` SET `difficulty_entry_3` = 39304 WHERE `entry` = 36701;
UPDATE `creature_template` SET `minlevel` = 83, `maxlevel` = 83, `exp` = 2, `faction_A` = 14, `faction_H` = 14, `speed_walk` = 2, `speed_run` = 1.42857, `mindmg` = 468, `maxdmg` = 702, `attackpower` = 175, `dmg_multiplier` = 47.2, `baseattacktime` = 2000, `rangeattacktime` = 2000, `dynamicflags` = 8, `minrangedmg` = 374, `maxrangedmg` = 562, `rangedattackpower` = 140, `mechanic_immune_mask` = 12584976 WHERE `entry` IN (36701, 39302, 39303, 39304);
-- Ice Sphere
UPDATE `creature_template` SET `minlevel` = 83, `maxlevel` = 83, `exp` = 2, `faction_A` = 14, `faction_H` = 14, `speed_walk` = 1.2, `speed_run` = 0.428571, `mindmg` = 468, `maxdmg` = 702, `attackpower` = 175, `dmg_multiplier` = 47.2, `baseattacktime` = 2000, `rangeattacktime` = 2000, `dynamicflags` = 8, `minrangedmg` = 374, `maxrangedmg` = 562, `rangedattackpower` = 140, `mechanic_immune_mask` = 12584976 WHERE `entry` IN (36633, 39305, 39306, 39307);
-- Defile
UPDATE `creature_template` SET `minlevel` = 81, `maxlevel` = 81, `exp` = 2, `faction_A` = 14, `faction_H` = 14, `speed_walk` = 1.2, `speed_run` = 0.428571, `mindmg` = 436, `maxdmg` = 654, `attackpower` = 163, `dmg_multiplier` = 2, `baseattacktime` = 2000, `rangeattacktime` = 2000, `unit_flags` = 33554944, `minrangedmg` = 349, `maxrangedmg` = 523, `rangedattackpower` = 130, `mechanic_immune_mask` = 12584976 WHERE `entry` = 38757;
-- Spirit Warden
UPDATE `creature_template` SET `difficulty_entry_1` = 39296 WHERE `entry` = 36824;
UPDATE `creature_template` SET `minlevel` = 80, `maxlevel` = 80, `exp` = 2, `faction_A` = 14, `faction_H` = 14, `speed_walk` = 1, `speed_run` = 1.14286, `mindmg` = 420, `maxdmg` = 630, `attackpower` = 157, `dmg_multiplier` = 2, `baseattacktime` = 2000, `rangeattacktime` = 2000, `dynamicflags` = 8, `minrangedmg` = 336, `maxrangedmg` = 504, `rangedattackpower` = 126 WHERE `entry` IN (36824, 39296);
-- Terenas Menethil
UPDATE `creature_template` SET `speed_walk` = 2, `speed_run` = 1.14286, `mindmg` = 391, `maxdmg` = 585, `attackpower` = 146, `dmg_multiplier` = 2.2, `baseattacktime` = 2000, `rangeattacktime` = 2000, `minrangedmg` = 313, `maxrangedmg` = 468, `rangedattackpower` = 117 WHERE `entry` IN (36824, 39296);