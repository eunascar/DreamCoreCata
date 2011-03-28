DROP TABLE IF EXISTS `character_custom_event`;
CREATE TABLE IF NOT EXISTS `character_custom_event` (
  `id` int(10) unsigned NOT NULL DEFAULT '0',
  `event_name` varchar(15) NOT NULL DEFAULT '',
  `max_winners` int(10) unsigned NOT NULL DEFAULT '0',
  `normal_winners` int(10) unsigned NOT NULL DEFAULT '0',
  `premium_winners` int(10) unsigned NOT NULL DEFAULT '0',
  `active` tinyint(3) unsigned NOT NULL DEFAULT '0',
   PRIMARY KEY (`id`)
)  ENGINE=InnoDB DEFAULT CHARSET=utf8;