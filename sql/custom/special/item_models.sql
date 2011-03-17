DROP TABLE IF EXISTS `item_models`;
CREATE TABLE IF NOT EXISTS `item_models` (
  `id` int(11) NOT NULL default '0', -- Identificador de Tamaño
  `type` tinyint(4) NOT NULL default '1', -- Tipo de Modelo NPC = 0, Boss = 1
  `modelid` mediumint(8) unsigned NOT NULL default '0', -- Modelo del NPC
  `scale` float NOT NULL DEFAULT '1',
  PRIMARY KEY  (`modelid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Model Id Character Item Data';