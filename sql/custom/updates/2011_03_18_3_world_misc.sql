-- Creature Templates Lich King Script
UPDATE `creature_template` SET `unit_flags` = 0 WHERE `entry` = 36609;
UPDATE `creature_template` SET `vehicleid` = 533 WHERE `entry` IN (36609, 39120, 39121, 39122);
UPDATE `creature` SET `position_z` = 1040 WHERE `id` = 22515 AND `map` = 631;
UPDATE `creature_template` SET `modelid1` = 11686 WHERE `entry` IN (36633, 39305, 39306, 39307);
UPDATE `creature_template` SET `modelid1` = 11686, `modelid2` = 0 WHERE `entry` = 15214;
UPDATE `creature` SET `id` = 36823, `modelid` = 0, `curhealth` = 0, `spawntimesecs` = '604800' WHERE `guid` = 86812;
UPDATE `creature` SET `id` = 36824, `modelid` = 0, `curhealth` = 0, `spawntimesecs` = '604800' WHERE `guid` = 86813;
UPDATE `creature_template` SET `dmg_multiplier` = 52 WHERE `entry` = 36824;
UPDATE `creature_template` SET `dmg_multiplier` = 35 WHERE `entry` = 36823;
-- Fix for Startup Errors
DELETE FROM `creature_addon` WHERE `guid` IN (136250,136251,136252,136274,136407,136408,136409,136410,136411,136412,136413,136414,136415,136416,136417,136418,136419,136420,136433,136434,136435,136436,136446,136447,136448,136449,136450,136451,136452,136455,136456,136457,136458,136459,136460,136461,136462,136463,136464,136465,136466,136467,136468,136469,136470,136471,136472,136473,136474,136475,136476,136477,136478,136479,136480,136481,136482,136483,136484,136485,136486,136487,136488,136489,136490,136491,136492,136493,136494,136495,136496,136497,136498,136499,136500,136501,136502,136503,136504,136505,136506,136507,136508,136509,136510,136511,136512,136513,136514,136515,136516,136517,136518,136555,136770,136771,136772,136773,136774,136775,136776,136777,137619,137621,137622,137623,137624,137625,137626,137627,137628,137629);
UPDATE `creature` SET `MovementType` = 0 WHERE `id` = 32865;