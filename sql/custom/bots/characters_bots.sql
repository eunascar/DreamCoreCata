DROP TABLE IF EXISTS `character_npcbot`;
CREATE TABLE IF NOT EXISTS `character_npcbot` (
  `owner` int(11) default NULL,
  `entry` int(11) default NULL,
  `race` tinyint(4) default NULL,
  `class` tinyint(4) default NULL
)  ENGINE=InnoDB DEFAULT CHARSET=utf8;


