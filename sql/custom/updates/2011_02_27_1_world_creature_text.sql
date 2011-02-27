-- Valithria Creature Texts
DELETE FROM `creature_text` WHERE `entry` = 36789;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(36789, 0, 0, 'Heroes, lend me your aid! I... I cannot hold them off much longer! You must heal my wounds!', 1, 0, 0, 0, 0, 17064, 'Valithria Dreamwalker - SAY_AGGRO'),
(36789, 1, 0, 'I have opened a portal into the Emerald Dream. Your salvation lies within, heroes.', 1, 0, 0, 0, 0, 17068, 'Valithria Dreamwalker - SAY_OPEN_PORTAL'),
(36789, 2, 0, 'My strength is returning! Press on, heroes!', 1, 0, 0, 0, 0, 17070, 'Valithria Dreamwalker - SAY_ABOVE_75'),
(36789, 3, 0, 'I will not last much longer!', 1, 0, 0, 0, 0, 17069, 'Valithria Dreamwalker - SAY_BELOW_25'),
(36789, 4, 0, 'Forgive me for what I do! I... cannot... stop... ONLY NIGHTMARES REMAIN!', 1, 0, 0, 0, 0, 17072, 'Valithria Dreamwalker - SAY_DEATH'),
(36789, 5, 0, 'A tragic loss...', 1, 0, 0, 0, 0, 17066, 'Valithria Dreamwalker - SAY_PDEATH'),
(36789, 6, 0, 'FAILURES!', 1, 0, 0, 0, 0, 17067, 'Valithria Dreamwalker - SAY_BERSERK'),
(36789, 7, 0, 'I am renewed! Ysera grants me the favor to lay these foul creatures to rest!', 1, 0, 0, 0, 0, 17071, 'Valithria Dreamwalker - SAY_END');