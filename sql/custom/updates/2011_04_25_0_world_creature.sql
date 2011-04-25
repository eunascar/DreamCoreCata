-- Fix Kologarn Doble Spawn
DELETE FROM `creature` WHERE `id` = 34297;
DELETE FROM `creature_addon` WHERE `guid` = 137582;