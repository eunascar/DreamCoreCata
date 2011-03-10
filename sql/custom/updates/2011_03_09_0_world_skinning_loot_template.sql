-- Missing Skinning Loot Templates for Ruby Sanctum
DELETE FROM `skinning_loot_template` WHERE `entry` IN (39746,39747,39751,39863);
INSERT INTO `skinning_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(39746, 33568, 55, 1, 0, 1, 3),
(39746, 38557, 25, 1, 0, 1, 2),
(39747, 33568, 55, 1, 0, 1, 3),
(39747, 38557, 25, 1, 0, 1, 2),
(39751, 33568, 55, 1, 0, 1, 3),
(39751, 38557, 25, 1, 0, 1, 2),
(39751, 44128, 1, 1, 0, 1, 1),
(39863, 33568, 75, 1, 0, 8, 12),
(39863, 38557, 75, 1, 0, 8, 12);