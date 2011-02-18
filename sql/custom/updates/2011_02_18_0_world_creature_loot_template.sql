---- Ulduar Creature Loot
-- XT-002
DELETE FROM `creature_loot_template` WHERE `entry`=33293;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('33293','45624','100','1','0','1','1'),
('33293','1','100','1','0','-34121','2'),
('33293','45867','0','2','2','1','1'),
('33293','45868','0','2','2','1','1'),
('33293','45869','0','2','2','1','1'),
('33293','45870','0','2','2','1','1'),
('33293','45871','0','2','2','1','1');

-- Assembly of Iron Hardmode
DELETE FROM `creature_loot_template` WHERE `entry` IN (32857, 32927, 32867);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('32857','45624','100','2','0','1','1'),
('32857','1','100','1','0','-34122','2'),
('32927','45624','100','2','0','2','2'),
('32927','1','100','1','0','-34122','3'),
('32927','45506','100','2','0','1','1'),
('32867','45624','100','4','0','1','1'),
('32867','1','100','1','0','-34122','2'),
('32867','45506','0','4','0','1','1'),
('32867','45447','0','4','2','1','1'),
('32867','45448','0','4','2','1','1'),
('32867','45449','0','4','2','1','1'),
('32867','45455','0','4','2','1','1'),
('32867','45456','0','4','2','1','1');
UPDATE creature_loot_template SET lootmode = 4 WHERE entry = 33693 AND item IN (45506, 45624);
UPDATE creature_loot_template SET lootmode = 2 WHERE entry IN (33694, 33692) AND item = 45624;

-- General Vezax
DELETE FROM `creature_loot_template` WHERE entry = 33271;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('33271','45624','100','1','0','1','1'),
('33271','1','100','1','0','-34131','2'),
('33271','46032','0','2','2','1','1'),
('33271','46033','0','2','2','1','1'),
('33271','46034','0','2','2','1','1'),
('33271','46035','0','2','2','1','1'),
('33271','46036','0','2','2','1','1');