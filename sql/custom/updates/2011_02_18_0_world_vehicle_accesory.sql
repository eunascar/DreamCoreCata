-- Flame Leviathan Vehicle Accesory Data
DELETE FROM `vehicle_accessory` WHERE `entry` = 33113 AND `seat_id` IN (0, 1);
INSERT INTO `vehicle_accessory` VALUES 
(33113, 33114, 0, 1, "Flame Leviathan"),
(33113, 33114, 1, 1, "Flame Leviathan");