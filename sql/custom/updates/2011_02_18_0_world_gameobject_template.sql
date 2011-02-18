---- GameObject Template Ulduar Data
-- Mimiron Cache of Innovation Data
DELETE FROM `gameobject_template` WHERE entry = 194790;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`, `WDBVerified`) VALUES
('194790','3','8686','Cache of Innovation','','','','0','0','1.5','0','0','0','0','0','0','1634','27084','0','1','0','0','0','0','0','0','0','1','0','1','0','1','0','0','0','0','0','0','0','0','','12340');
UPDATE `gameobject_template` SET `size` = 1.5 WHERE `entry` = 194956;

-- Thorim Cache of Storms Data
UPDATE `gameobject_template` SET `faction` = 0, `flags` = 0 WHERE `entry` = 194312;
UPDATE `gameobject_template` SET `size` = 3, `questItem1` = 45817, `data1` = 26956 WHERE `entry` = 194315;

-- Freya
DELETE FROM `gameobject_template` WHERE entry IN (194326, 194329, 194330);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`, `WDBVerified`) VALUES
('194326','3','8628','Freya\'s Gift','','','','0','0','2','0','0','0','0','0','0','1634','27080','0','1','0','0','0','0','0','0','0','1','0','1','0','1','0','0','0','0','0','0','0','0','','12340'),
('194329','3','8628','Freya\'s Gift','','','','0','0','2','0','0','0','0','0','0','1634','27088','0','1','0','0','0','0','0','0','0','1','0','1','0','1','0','0','0','0','0','0','0','0','','12340'),
('194330','3','8628','Freya\'s Gift','','','','0','0','2','0','0','0','0','0','0','1634','27089','0','1','0','0','0','0','0','0','0','1','0','1','0','1','0','0','0','0','0','0','0','0','','12340');
UPDATE `gameobject_template` SET `size` = 2, `data1` = 27087 WHERE `entry` = 194328;
UPDATE `gameobject_template` SET `data1` = 27090, `WDBVerified` = 12340 WHERE `entry` = 194331;

-- Cache of Winter Flags
UPDATE `gameobject_template` SET `flags` = 16 WHERE `entry` = 194201;