-- Startup Errors
DELETE FROM `creature_addon` WHERE `guid` IN (136048, 136049, 136050, 136051, 136052, 136053, 137532, 137533, 137534, 137535, 137536, 137537);
UPDATE `creature_template` SET `ScriptName` = '' WHERE `entry` = 34332;
DELETE FROM `conditions` WHERE `SourceEntry` = 64468;
-- Update Achivement Criteria for Razorscale
UPDATE `achievement_criteria_data` SET `ScriptName` = 'achievement_quick_shave', `type` = 11, `value1` = 0 WHERE `criteria_id` IN (10062, 10063);
-- Emerald Dream Template Updates
UPDATE `creature_template` SET `Health_mod` = 2000 WHERE `entry` IN (150000 ,150001, 150002);
UPDATE `creature_template` SET `Health_mod` = 3000 WHERE `entry` = 150003;
