DELETE FROM `spell_linked_spell` WHERE (`spell_trigger` = -74562) AND (`spell_effect` = 74610);
DELETE FROM `spell_linked_spell` WHERE (`spell_trigger` = -74792) AND (`spell_effect` = 74800);
INSERT INTO `spell_linked_spell` VALUES (-74562, 74610, 0, 'Fiery Combustion removed -> Combustion');
INSERT INTO `spell_linked_spell` VALUES (-74792, 74800, 0, 'Soul Consumption removed -> Consumption');