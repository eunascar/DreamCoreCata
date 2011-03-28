DROP TABLE IF EXISTS character_inventory_copy;
CREATE TABLE character_inventory_copy (
guid int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier', bag int(10) unsigned NOT NULL DEFAULT '0', slot tinyint(3) unsigned NOT NULL DEFAULT '0', item int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Item Global Unique Identifier', count int(2) DEFAULT NULL, PRIMARY KEY (item), KEY idx_guid (guid) ) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Player System';

-- Execute next block 3 or more times to remove all duplicates until DELETE block - Query OK, 0 rows affected
INSERT INTO character_inventory_copy SELECT guid, bag, slot, item, COUNT(*) AS count
FROM character_inventory
GROUP BY guid, bag, slot
HAVING count > 1;
DELETE c1 FROM character_inventory AS c1, character_inventory_copy AS c2
WHERE c1.guid=c2.guid AND c1.bag=c2.bag AND c1.slot=c2.slot AND c1.item=c2.item;

DELETE FROM item_instance WHERE guid IN (SELECT item FROM character_inventory_copy);
DROP TABLE IF EXISTS character_inventory_copy;

ALTER TABLE character_inventory
ADD UNIQUE KEY (guid,bag,slot);