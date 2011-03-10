SET @guid = 5000719;

-- Salvage Chopper Creature Template + Spawn
DELETE FROM `creature_template` WHERE `entry` IN (33062,34045);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(33062, 34045, 0, 0, 0, 0, 25870, 25871, 0, 0, 'Salvaged Chopper', '', 'vehichleCursor', 0, 80, 80, 2, 2105, 2105, 0, 1, 2, 1, 0, 349, 522, 0, 131, 1, 2000, 2000, 4, 16384, 8, 0, 0, 0, 0, 0, 279, 418, 105, 9, 262176, 0, 0, 0, 0, 0, 0, 0, 0, 0, 62974, 62286, 62299, 64660, 0, 0, 0, 0, 0, 335, 0, 0, '', 0, 3, 40, 1, 1, 0, 0, 0, 0, 0, 0, 0, 180, 1, 0, 0, 0, '', 12340),
(34045, 0, 0, 0, 33062, 0, 25870, 25871, 0, 0, 'Salvaged Chopper (1)', '', 'vehichleCursor', 0, 80, 80, 2, 2105, 2105, 0, 1, 2, 1, 0, 349, 522, 0, 131, 1, 2000, 2000, 4, 16384, 8, 0, 0, 0, 0, 0, 279, 418, 105, 9, 262176, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 335, 0, 0, '', 0, 3, 40, 1, 1, 0, 0, 0, 0, 0, 0, 0, 180, 1, 0, 0, 0, '', 12340);
DELETE FROM `creature` WHERE `id` = 33062;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@guid, 33062, 603, 3, 65535, 0, 0, -718.451, -118.248, 430.37, 0.0523599, 7200, 0, 0, 504000, 0, 0, 0, 0, 0, 0),
(@guid+1, 33062, 603, 3, 65535, 0, 0, -717.833, -106.567, 430.124, 0.122173, 7200, 0, 0, 504000, 0, 0, 0, 0, 0, 0);

-- No Spawn Data
DELETE FROM `creature_addon` WHERE `guid` IN (101966, 102039);

-- Add Quest NpcFlag
UPDATE `creature_template` SET `npcflag` = 2 WHERE `entry` = 888;