SET @guid = 5000717;

-- Correct Valithria Dreamwalker Spawn Location (Source YTDB)
DELETE FROM `creature` WHERE `id` = 36789;
DELETE FROM `creature` WHERE `guid` BETWEEN @guid AND @guid+1;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@guid, 36789, 631, 15, 1, 0, 0, 4203.65, 2483.89, 364.961, 5.51524, 604800, 0, 0, 6000003, 0, 0, 0, 0, 0, 0),
(@guid+1, 37950, 631, 15, 16, 0, 0, 4203.65, 2483.89, 390.961, 5.51524, 604800, 0, 0, 6000003, 0, 0, 0, 0, 33540, 8);
-- Update Linked Respawn
UPDATE `linked_respawn` SET `guid` = @guid WHERE `guid` = 137746;
DELETE FROM `linked_respawn` WHERE `guid` = 137747;