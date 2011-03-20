-- Lavaman GameObjects Spawn Fixes
UPDATE `gameobject` SET `rotation3` = 1, `spawntimesecs` = 604800 WHERE `id` = 202437;
UPDATE `gameobject` SET `spawntimesecs` = -604800 WHERE `id` = 202436;