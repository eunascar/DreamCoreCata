-- Creature Template Ulduar Data
UPDATE `creature_template` SET `baseattacktime` = 1000 WHERE `entry` IN (33824, 33831);
UPDATE `creature_template` SET `baseattacktime` = 1500 WHERE `entry` IN (33754, 33755, 33757, 33758, 34166);

UPDATE `creature_template` SET `difficulty_entry_1` = 0 WHERE `entry` = 33062;
DELETE FROM `creature_template` WHERE `entry` = 34045;
UPDATE `creature_template` SET `difficulty_entry_1` = 34114 WHERE `entry` = 33855;

UPDATE `creature_template` SET `equipment_id` = 870  WHERE `entry` IN (34237, 34199);
UPDATE `creature_template` SET `equipment_id` = 1847 WHERE `entry` IN (33823, 33832);
UPDATE `creature_template` SET `equipment_id` = 1848 WHERE `entry` IN (33820, 33830, 33818, 33827);
UPDATE `creature_template` SET `equipment_id` = 1849 WHERE `entry` IN (33819, 33829, 32885);
UPDATE `creature_template` SET `equipment_id` = 1850 WHERE `entry` = 32908;
UPDATE `creature_template` SET `equipment_id` = 1852 WHERE `entry` IN (33822, 33828);
UPDATE `creature_template` SET `equipment_id` = 1862 WHERE `entry` IN (33824, 33831);

UPDATE `creature_template` SET `exp` = 0 WHERE `entry` IN (33432, 34106);

UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` = 34114;

UPDATE `creature_template` SET `flags_extra` = 2 WHERE `entry` IN (33215, 33264, 33377, 33406, 33500, 33575, 33742, 34286);
UPDATE `creature_template` SET `flags_extra` = 256 WHERE `entry` IN (33524,34152,33449);

UPDATE `creature_template` SET `mechanic_immune_mask` = 1 WHERE `entry` IN (34198, 34236);
UPDATE `creature_template` SET `mechanic_immune_mask` = 5 WHERE `entry` IN (34199, 34237);
UPDATE `creature_template` SET `mechanic_immune_mask` = 64 WHERE `entry` IN (34190, 34196, 34229, 34245);
UPDATE `creature_template` SET `mechanic_immune_mask` = 2128 WHERE `entry` IN (34134, 34141);
UPDATE `creature_template` SET `mechanic_immune_mask` = 131072 WHERE `entry` IN (34086, 34201);
UPDATE `creature_template` SET `mechanic_immune_mask` = 8388625 WHERE `entry` IN (33829, 33830);
UPDATE `creature_template` SET `mechanic_immune_mask` = 8405008 WHERE `entry` IN (34085, 34186, 34274, 34268, 34272, 34270,34214,34183,34184,34219,34216,34192,34191,34217,34220,34193);
UPDATE `creature_template` SET `mechanic_immune_mask` = 8519697 WHERE `entry` = 33839;
UPDATE `creature_template` SET `mechanic_immune_mask` = 33554432 WHERE `entry` IN (34267, 34142, 34135);
UPDATE `creature_template` SET `mechanic_immune_mask` = 33554496 WHERE `entry` IN (34197, 33430, 33354, 33732, 33729, 34226);
UPDATE `creature_template` SET `mechanic_immune_mask` = 33554512 WHERE `entry` = 33773;
UPDATE `creature_template` SET `mechanic_immune_mask` = 33554513 WHERE `entry` IN (33772, 33820, 33819, 33838);
UPDATE `creature_template` SET `mechanic_immune_mask` = 536872986 WHERE `entry` IN (34234, 34235, 33237, 34105);
UPDATE `creature_template` SET `mechanic_immune_mask` = 545259541 WHERE `entry` IN (33754, 33755, 33757, 33758);
UPDATE `creature_template` SET `mechanic_immune_mask` = 545260304 WHERE `entry` IN (33700, 33723, 33699, 33722);
UPDATE `creature_template` SET `mechanic_immune_mask` = 545267736 WHERE `entry` IN (34139, 34133);
UPDATE `creature_template` SET `mechanic_immune_mask` = 570425425 WHERE `entry` IN (33818, 33822, 33824, 33823, 33827, 33828, 33831, 33832);
UPDATE `creature_template` SET `mechanic_immune_mask` = 617299803 WHERE `entry` = 33449;
UPDATE `creature_template` SET `mechanic_immune_mask` = 617299807 WHERE `entry` IN (33515, 34175);
UPDATE `creature_template` SET `mechanic_immune_mask` = 650854235 WHERE `entry` IN (33113, 34003, 33293, 33885, 33329, 33995, 32914, 32913, 33393, 33392, 33391, 33789, 33524, 34152);

UPDATE `creature_template` SET `mingold` = 0, `maxgold` = 0 WHERE `entry` IN (32845, 32846);
UPDATE `creature_template` SET `mingold` = 7100, `maxgold` = 7600  WHERE `entry` IN (34273, 34271, 34199, 33431, 33528, 33527, 33526, 33525, 33355, 33820, 33819, 34267, 34269, 33430, 33354, 34085, 34086, 34069);
UPDATE `creature_template` SET `mingold` = 10300, `maxgold` = 12000 WHERE `entry` = 34135;
UPDATE `creature_template` SET `mingold` = 14200, `maxgold` = 15600 WHERE `entry` IN (34274, 34272, 34237, 34268, 34186, 34201, 34185);
UPDATE `creature_template` SET `mingold` = 14200, `maxgold` = 16200 WHERE `entry` IN (34190, 34198, 34196);
UPDATE `creature_template` SET `mingold` = 14600, `maxgold` = 18200 WHERE `entry` IN (34226, 34197);
UPDATE `creature_template` SET `mingold` = 17000, `maxgold` = 18200 WHERE `entry` = 34193;
UPDATE `creature_template` SET `mingold` = 17200, `maxgold` = 17600 WHERE `entry` = 34184;
UPDATE `creature_template` SET `mingold` = 24200, `maxgold` = 26200 WHERE `entry` IN (34229, 34236, 34245);
UPDATE `creature_template` SET `mingold` = 27200, `maxgold` = 27600 WHERE `entry` = 34219;
UPDATE `creature_template` SET `mingold` = 30300, `maxgold` = 32000 WHERE `entry` = 34142;
UPDATE `creature_template` SET `mingold` = 37000, `maxgold` = 38200 WHERE `entry` = 34220;
UPDATE `creature_template` SET `mingold` = 41000, `maxgold` = 46000 WHERE `entry` = 33839;
UPDATE `creature_template` SET `mingold` = 71000, `maxgold` = 76000 WHERE `entry` IN (33699, 33722, 34134, 33757, 33758);
UPDATE `creature_template` SET `mingold` = 72000, `maxgold` = 76000 WHERE `entry` IN (33818, 33822, 33824, 33823, 33828, 33831, 33832, 33830, 33829);
UPDATE `creature_template` SET `mingold` = 75000, `maxgold` = 95000 WHERE `entry` = 33731;
UPDATE `creature_template` SET `mingold` = 76000, `maxgold` = 79000 WHERE `entry` = 33773;
UPDATE `creature_template` SET `mingold` = 105000, `maxgold` = 125000 WHERE `entry` = 34183;
UPDATE `creature_template` SET `mingold` = 125000, `maxgold` = 155000 WHERE `entry` IN (33733, 33734, 33741, 33729, 33735, 33737);
UPDATE `creature_template` SET `mingold` = 171000, `maxgold` = 176000 WHERE `entry` IN (34133, 34141);
UPDATE `creature_template` SET `mingold` = 205000, `maxgold` = 225000 WHERE `entry` = 34214;
UPDATE `creature_template` SET `mingold` = 271000, `maxgold` = 276000 WHERE `entry` IN (33700, 33723);
UPDATE `creature_template` SET `mingold` = 272000, `maxgold` = 276000 WHERE `entry` = 33827;
UPDATE `creature_template` SET `mingold` = 371000, `maxgold` = 376000 WHERE `entry` = 34139;
UPDATE `creature_template` SET `mingold` = 625000, `maxgold` = 655000 WHERE `entry` = 33732;
UPDATE `creature_template` SET `mingold` = 625000, `maxgold` = 665000 WHERE `entry` IN (32914, 32913);
UPDATE `creature_template` SET `mingold` = 1450000, `maxgold` = 1750000 WHERE `entry` IN (33113, 33186, 33118, 33293, 33271);
UPDATE `creature_template` SET `mingold` = 1460000, `maxgold` = 1520000  WHERE `entry` = 33515;
UPDATE `creature_template` SET `mingold` = 1805000, `maxgold` = 1855000 WHERE `entry` IN (33393, 33392, 33391);
UPDATE `creature_template` SET `mingold` = 2450000, `maxgold` = 2750000 WHERE `entry` IN (34003, 33724, 33190);
UPDATE `creature_template` SET `mingold` = 3450000, `maxgold` = 3750000 WHERE entry IN (33885, 33449);
UPDATE `creature_template` SET `mingold` = 3460000, `maxgold` = 3520000  WHERE `entry` = 34175;

UPDATE `creature_template` SET `modelid1` = 11686, `modelid2` = 0 WHERE `entry` = 34194;
UPDATE `creature_template` SET `modelid1` = 11686, `modelid2` = 0 WHERE `entry` IN (33364, 33369, 33108, 33366);

UPDATE `creature_template` SET `speed_walk` = 2 WHERE `entry` IN (33370, 33212);
UPDATE `creature_template` SET `speed_walk` = 1.66667 WHERE `entry` IN (34014, 34166);

UPDATE `creature_template` SET `unit_class` = 2 WHERE `entry` IN (33820, 33830, 33819, 33829, 33818, 33827); 

UPDATE `creature_template` SET `unit_flags` = 33718790 WHERE `entry` = 34194;