-- Creature Ulduar Data
-- Delete Ulduar Colossus Spawns, now they're handled by the script
DELETE FROM `creature` WHERE `guid` IN (137479, 137480);

-- Steelforged Defender Respawn Time
UPDATE `creature` SET `spawntimesecs` = 604800 WHERE `id` IN (33236, 33838);

-- Display Instance Creatures in all instance modes
UPDATE `creature` SET `spawnMask` = 3 WHERE `map` = 603;

-- Salvaged Chopper has no heroic entry, so delete its spawns
DELETE FROM `creature` WHERE `id` IN (33060, 33062, 33109);
DELETE FROM `creature` WHERE `id` = 33167;