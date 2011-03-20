-- Achievement criteria for The Lich King
-- Bane of the Fallen King (10 player heroic) 
-- Realm First! Fall of the Lich King (25 player heroic) 
-- The Frozen Throne (10 player) 
-- The Frozen Throne (25 player) 
-- The Light of Dawn (25 player heroic)
DELETE FROM `achievement_criteria_data` where `criteria_id` IN (12825,12818,12764,12909,12826);
INSERT INTO `achievement_criteria_data` (`criteria_id`, `type`, `value1`, `value2`, `ScriptName`) VALUES
(12825, 12, 2, 0, ''),
(12818, 12, 3, 0, ''),
(12764, 12, 0, 0, ''),
(12909, 12, 1, 0, ''),
(12826, 12, 3, 0, '');