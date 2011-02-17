-- Ruby Sanctum Creatures
SET @entry_baltharus      = 39751;
SET @entry_zarithrian     = 39746;
SET @entry_ragefire       = 39747;
SET @entry_halion         = 39863;
SET @entry_xerestrasza    = 40429;

-- Ruby Sanctum Script Texts
DELETE FROM `creature_text` WHERE `entry` IN (@entry_baltharus, @entry_zarithrian, @entry_ragefire, @entry_halion, @entry_xerestrasza);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `emote`, `sound`, `comment`) VALUES
-- Xerestrasza
(@entry_xerestrasza, 0, 0, 'Help! I am trapped within this tree! I require aid!', 1, 0, 0, 17490, 'Sanctum Guardian Xerestrasza - SAY_XERESTRASZA_1'),
(@entry_xerestrasza, 1, 0, 'Thank you! I could not have held out for much longer.... A terrible thing has happened here.', 1, 0, 0, 17491, 'Sanctum Guardian Xerestrasza - SAY_XERESTRASZA_2'),
(@entry_xerestrasza, 2, 0, 'We believed the Sanctum was well-fortified, but we were not prepared for the nature of this assault.', 0, 0, 0, 17492, 'Sanctum Guardian Xerestrasza - SAY_XERESTRASZA_3'),
(@entry_xerestrasza, 3, 0, 'The Black dragonkin materialized from thin air, and set upon us before we could react.', 0, 0, 0, 17493, 'Sanctum Guardian Xerestrasza - SAY_XERESTRASZA_4'),
(@entry_xerestrasza, 4, 0, 'We did not stand a chance. As my brethren perished around me, I managed to retreat here and bar the entrance.', 0, 0, 0, 17494, 'Sanctum Guardian Xerestrasza - SAY_XERESTRASZA_5'),
(@entry_xerestrasza, 5, 0, 'They slaughtered us with cold efficiency, but the true focus of their interest seemed to be the eggs kept here in the Sanctum.', 0, 0, 0, 17495, 'Sanctum Guardian Xerestrasza - SAY_XERESTRASZA_6'),
(@entry_xerestrasza, 6, 0, 'The commander of the forces on the ground here is a cruel brute named Zarithrian, but I fear there are greater powers at work.', 0, 0, 0, 17496, 'Sanctum Guardian Xerestrasza - SAY_XERESTRASZA_7'),
(@entry_xerestrasza, 7, 0, 'In their initial assault, I caught a glimpse of their true leader, a fearsome full-grown twilight dragon.', 0, 0, 0, 17497, 'Sanctum Guardian Xerestrasza - SAY_XERESTRASZA_8'),
(@entry_xerestrasza, 8, 0, 'I know not the extent of their plans, heroes, but I know this: They cannot be allowed to succeed!', 0, 0, 0, 17498, 'Sanctum Guardian Xerestrasza - SAY_XERESTRASZA_9'),
-- Baltharus
(@entry_baltharus, 0, 0, 'Ah, the entertainment has arrived.', 1, 0, 0, 17520, 'Baltharus the Warborn - SAY_AGGRO'),
(@entry_baltharus, 1, 0, 'Baltharus leaves no survivors!', 1, 0, 0, 17521, 'Baltharus the Warborn - SAY_SLAY1'),
(@entry_baltharus, 2, 0, 'This world has enough heroes.', 1, 0, 0, 17522, 'Baltharus the Warborn - SAY_SLAY2'),
(@entry_baltharus, 3, 0, 'I..Didn''t saw...that coming...', 1, 0, 0, 17523, 'Baltharus the Warborn - SAY_DEATH'),
(@entry_baltharus, 4, 0, 'Twice the pain and half the fun.', 1, 0, 0, 17524, 'Baltharus the Warborn - SAY_SUMMON_CLONE'),
(@entry_baltharus, 5, 0, 'Your power wanes, ancient one.... Soon you will join your friends.', 1, 0, 0, 17525, 'Baltharus the Warborn - SAY_INTRO'),
-- Zarithrian
(@entry_zarithrian, 0, 0, 'Alexstrasza has chosen capable allies... A pity that I must END YOU!', 1, 0, 0, 17512, 'General Zarithrian - SAY_AGGRO'),
(@entry_zarithrian, 1, 0, 'You thought you stood a chance?', 1, 0, 0, 17513, 'General Zarithrian - SAY_SLAY1'),
(@entry_zarithrian, 2, 0, 'It''s for the best.', 1, 0, 0, 17514, 'General Zarithrian - SAY_SLAY2'),
(@entry_zarithrian, 3, 0, 'HALION! I...', 1, 0, 0, 17515, 'General Zarithrian - SAY_DEATH'),
(@entry_zarithrian, 4, 0, 'Turn them to ash, minions!', 1, 0, 0, 17516, 'General Zarithrian - SAY_SUMMON'),
-- Ragefire
(@entry_ragefire, 0, 0, 'You will sssuffer for this intrusion!', 1, 0, 0, 17528, 'Saviana Ragefire - SAY_AGGRO'),
(@entry_ragefire, 1, 0, 'As it should be...', 1, 0, 0, 17529, 'Saviana Ragefire - SAY_SLAY1'),
(@entry_ragefire, 2, 0, 'Halion will be pleased', 1, 0, 0, 17530, 'Saviana Ragefire - SAY_SLAY2'),
(@entry_ragefire, 3, 0, 'Hhrr...Grr..', 1, 0, 0, 17531, 'Saviana Ragefire - SAY_DEATH'),
(@entry_ragefire, 4, 0, 'Burn in the master\'s flame!', 1, 0, 0, 17532, 'Saviana Ragefire - SAY_SPECIAL'),
-- Halion
(@entry_halion, 0, 0, 'Insects! You\'re too late. The Ruby Sanctum is lost.', 0, 0, 0, 17499, 'Halion - SAY_SPAWN'),
(@entry_halion, 1, 0, 'Your world teeters on the brink of annihilation. You will ALL bear witness to the coming of a new age of DESTRUCTION!', 0, 0, 0, 17500, 'Halion - SAY_AGGRO'),
(@entry_halion, 2, 0, 'Another hero falls.', 0, 0, 0, 17501, 'Halion - SAY_SLAY1'),
(@entry_halion, 3, 0, 'Hahahahaha.', 0, 0, 0, 17502, 'Halion - SAY_SLAY2'),
(@entry_halion, 4, 0, 'Relish this victory, mortals, for it will be your last! This world will burn with the master\'s return!', 0, 0, 0, 17503, 'Halion - SAY_DEATH'),
(@entry_halion, 5, 0, 'Not good enough.', 0, 0, 0, 17504, 'Halion - SAY_BERSERK'),
(@entry_halion, 6, 0, 'The heavens burn!', 0, 0, 0, 17505, 'Halion - SAY_SPECIAL1'),
(@entry_halion, 7, 0, 'Beware the shadow!', 0, 0, 0, 17506, 'Halion - SAY_SPECIAL2'),
(@entry_halion, 8, 0, 'You will find only suffering within the realm of twilight! Enter if you dare!', 0, 0, 0, 17507, 'Halion - SAY_PHASE2'),
(@entry_halion, 9, 0, 'I am the light and the darkness! Cower, mortals, before the herald of Deathwing!', 0, 0, 0, 17508, 'Halion - SAY_PHASE3');