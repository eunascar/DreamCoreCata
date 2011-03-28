DROP TABLE IF EXISTS `character_custom_event_winner`;
CREATE TABLE IF NOT EXISTS `character_custom_event_winner` (
  `character_guid` int(10) unsigned NOT NULL DEFAULT '0',
  `event_id` int(10) unsigned NOT NULL DEFAULT '0',
  `position` int(10) unsigned NOT NULL DEFAULT '0',
  `character_name` varchar(12) NOT NULL DEFAULT '',
  `premium` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `prize` tinyint(3) unsigned NOT NULL DEFAULT '0',
   PRIMARY KEY (`character_guid`)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8;