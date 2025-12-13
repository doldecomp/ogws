#ifndef RP_COMMON_MESSAGE_H
#define RP_COMMON_MESSAGE_H
#include <Pack/types_pack.h>

#define MSG_GROUP(X) (((X) & 0xFFFFFF00) >> 8)
#define MSG_INDEX(X) ((X) & 0xFF)
#define MSG_UNPACK(X) MSG_GROUP(X), MSG_INDEX(X)

struct bmg_message {
    u32 group;
    u32 index;
};

/**
 * @brief common_message.bmg message IDs
 */
enum common_message {
    // clang-format off
    MSG_000_000 = 0x00000000, //!< Yes
    MSG_001_000 = 0x00000010, //!< No
    MSG_002_000 = 0x00000020, //!< Back
    MSG_003_000 = 0x00000030, //!< Wii Menu
    MSG_010_000 = 0x00000100, //!< 
    MSG_011_000 = 0x00000110, //!< 
    MSG_012_000 = 0x00000120, //!< 
    MSG_013_000 = 0x00000130, //!< 
    MSG_014_000 = 0x00000140, //!< 
    MSG_015_000 = 0x00000150, //!< 
    MSG_020_000 = 0x00000200, //!< Wii Sports
    MSG_021_000 = 0x00000210, //!< Wii Play
    MSG_040_000 = 0x00000400, //!< An error has occurred.\nPress the Eject Button，\nremove the Game Disc，\nand turn the power off.\nPlease read the\nWii Operations Manual\nfor help troubleshooting.
    MSG_041_000 = 0x00000410, //!< The Game Disc could not be read.\nPlease read the Wii operations\nmanual for more information.
    MSG_042_000 = 0x00000420, //!< Please insert the {000000}\nGame Disc.
    MSG_043_000 = 0x00000430, //!< Press a button on the Wii Remote\nif you want to continue playing.
    MSG_050_000 = 0x00000500, //!< 
    MSG_051_000 = 0x00000510, //!< 
    MSG_052_000 = 0x00000520, //!< The game could not be saved.\nContinue without saving?{020001 01 00}
    MSG_053_000 = 0x00000530, //!< The Wii System Memory is\ncorrupted. Please refer to the\nWii Operations Manual for help\ntroubleshooting. Continue without\nsaving?{020001 01 00}
    MSG_100_000 = 0x00001000, //!< This game's save data is\ncorrupted and must be formatted.\nFormat the data now?{020001 01 00}
    MSG_101_000 = 0x00001010, //!< Continue without saving?{020001 01 00}
    MSG_102_000 = 0x00001020, //!< 
    MSG_103_000 = 0x00001030, //!< 
    MSG_104_000 = 0x00001040, //!< The Wii System Memory does not\nhave enough free space. Either\nmove files to an SD Card or erase\nfiles to save. This game requires\n{000000} empty blocks.\nOpen the Data Management\nscreen now?{020001 01 00}
    MSG_105_000 = 0x00001050, //!< Create a save file for {000000}?{020001 00 00}
    MSG_106_000 = 0x00001060, //!< 
    MSG_107_000 = 0x00001070, //!< A save file has been created.
    MSG_108_000 = 0x00001080, //!< 
    MSG_110_000 = 0x00001100, //!< The Wii System Memory does not\nhave enough empty files. Either\nmove files to an SD Card or erase\nfiles to save. Open the Data\nManagement screen now?{020001 01 00}
    MSG_150_000 = 0x00001500, //!< The batteries in the Wii Remote\nare running low. Please check the\nbattery level on the HOME Menu.
    MSG_160_000 = 0x00001600, //!< Unable to load Mii Channel data.\nPlease access the Mii Channel\nand check Mii Channel data.
    MSG_161_000 = 0x00001610, //!< Unable to load Mii data stored\nin the Wii Remote.
    MSG_170_000 = 0x00001700, //!< Unable to load saved data.\nPlease try again later.\nIf this problem continues, see\nthe Wii Operations Manual for\nhelp troubleshooting.
    MSG_171_000 = 0x00001710, //!< Unable to save.
    MSG_200_000 = 0x00002000, //!< To play with this many players,\nyou need {000000} Wii Remotes.\nPlease connect more Wii Remotes.{020000 00 3C}
    MSG_210_000 = 0x00002100, //!< Use {000000} Wii Remote with {000000} players.
    MSG_211_000 = 0x00002110, //!< Use {000000} Wii Remotes with {000000} players.
    MSG_250_000 = 0x00002500, //!< You can't select this until you've\ncreated a Mii in the Mii Channel.{020002 00 00}{020001 00 00}
    MSG_250_001 = 0x00002501, //!< Back
    MSG_250_002 = 0x00002502, //!< To Wii Menu
    MSG_251_000 = 0x00002510, //!< There are no Miis stored on this\nWii Remote. Please add a Mii in\nthe Mii Channel.
    MSG_260_000 = 0x00002600, //!< You can't save your records\nwith this Mii. Continue?{020002 01 00}{020001 01 00}
    MSG_261_000 = 0x00002610, //!< You can't save My Record data\nwith this Mii. Continue?{020001 01 00}{020002 01 00}
    MSG_270_000 = 0x00002700, //!< You can't select this Mii today\nbecause it has taken the Wii\nFitness test. Try again tomorrow.
    MSG_271_000 = 0x00002710, //!< The connection between the\nWii Remote and Wii console has\nbeen lost. Press \uE047 and \uE048\nsimultaneously to reconnect...
    MSG_280_000 = 0x00002800, //!< Added {000001} to\nthe player list. If you erase\nthis Mii from the Mii Channel, it\nwill be deleted from your player\nlist, so be careful!{020000 00 B4}
    MSG_281_000 = 0x00002810, //!< Added {000001} to\nthe player list. If you erase\nthis Mii from the Mii Channel, it\nwill be deleted from your player\nlist, so be careful!{020000 00 B4}
    MSG_290_000 = 0x00002900, //!< One or more Miis have been\nerased from the Mii Channel\nand will be removed from your\nplayer list.{020000 00 B4}
    MSG_291_000 = 0x00002910, //!< One or more Miis have been\nerased from the Mii Channel\nand will be removed from your\nplayer list.{020000 00 B4}
    MSG_300_000 = 0x00003000, //!< Which hand do you want to use?
    MSG_301_000 = 0x00003010, //!< Tennis
    MSG_302_000 = 0x00003020, //!< Baseball
    MSG_303_000 = 0x00003030, //!< Bowling
    MSG_304_000 = 0x00003040, //!< Golf
    MSG_305_000 = 0x00003050, //!< Boxing
    MSG_310_000 = 0x00003100, //!< Swing
    MSG_311_000 = 0x00003110, //!< Pitch
    MSG_312_000 = 0x00003120, //!< Bat
    MSG_313_000 = 0x00003130, //!< Bowl
    MSG_314_000 = 0x00003140, //!< Swing
    MSG_315_000 = 0x00003150, //!< Stance
    MSG_320_000 = 0x00003200, //!< L
    MSG_321_000 = 0x00003210, //!< R
    MSG_330_000 = 0x00003300, //!< OK
    MSG_400_000 = 0x00004000, //!< Select Mii
    MSG_401_000 = 0x00004010, //!< Select Players
    MSG_402_000 = 0x00004020, //!< Tennis
    MSG_403_000 = 0x00004030, //!< Baseball
    MSG_404_000 = 0x00004040, //!< Bowling
    MSG_405_000 = 0x00004050, //!< Golf
    MSG_406_000 = 0x00004060, //!< Boxing
    MSG_407_000 = 0x00004070, //!< Training
    MSG_408_000 = 0x00004080, //!< Wii Fitness
    MSG_409_000 = 0x00004090, //!< Main Menu
    MSG_450_000 = 0x00004500, //!< Back
    MSG_450_001 = 0x00004501, //!< Main Menu
    MSG_451_000 = 0x00004510, //!< P1
    MSG_452_000 = 0x00004520, //!< P2
    MSG_453_000 = 0x00004530, //!< P3
    MSG_454_000 = 0x00004540, //!< P4
    MSG_455_000 = 0x00004550, //!< {000001}
    MSG_470_000 = 0x00004700, //!< 
    MSG_500_000 = 0x00005000, //!< Select the number of players.
    MSG_510_000 = 0x00005100, //!< 1
    MSG_511_000 = 0x00005110, //!< 2
    MSG_520_000 = 0x00005200, //!< 1
    MSG_521_000 = 0x00005210, //!< 2
    MSG_522_000 = 0x00005220, //!< 3
    MSG_523_000 = 0x00005230, //!< 4
    MSG_530_000 = 0x00005300, //!< More
    MSG_531_000 = 0x00005310, //!< OK
    MSG_540_000 = 0x00005400, //!< Wii Remotes
    MSG_541_000 = 0x00005410, //!< Press \uE047 and \uE048 at the same time on\neach Wii Remote you want to add.
    MSG_600_000 = 0x00006000, //!< Select a Mii for Player {000000}.
    MSG_600_001 = 0x00006001, //!< Select a Mii.
    MSG_610_000 = 0x00006100, //!< Wii Console
    MSG_611_000 = 0x00006110, //!< Guest
    MSG_612_000 = 0x00006120, //!< Wii Remote
    MSG_613_000 = 0x00006130, //!< Reading Mii data...\nDo not unplug the extension controller.
    MSG_620_000 = 0x00006200, //!< Play with this Mii.
    MSG_620_001 = 0x00006201, //!< Play with these Miis.
    MSG_630_000 = 0x00006300, //!< P1
    MSG_631_000 = 0x00006310, //!< P2
    MSG_632_000 = 0x00006320, //!< 
    MSG_633_000 = 0x00006330, //!< 
    MSG_640_000 = 0x00006400, //!< {000001}
    MSG_650_000 = 0x00006500, //!< Change
    MSG_651_000 = 0x00006510, //!< OK
    MSG_660_000 = 0x00006600, //!< Guest A
    MSG_661_000 = 0x00006610, //!< Guest B
    MSG_662_000 = 0x00006620, //!< Guest C
    MSG_663_000 = 0x00006630, //!< Guest D
    MSG_664_000 = 0x00006640, //!< Guest E
    MSG_665_000 = 0x00006650, //!< Guest F
    MSG_700_000 = 0x00007000, //!< Yes
    MSG_700_001 = 0x00007001, //!< Back
    MSG_701_000 = 0x00007010, //!< No
    MSG_701_001 = 0x00007011, //!< Wii Menu
    MSG_702_000 = 0x00007020, //!< 
    MSG_750_000 = 0x00007500, //!< Continue
    MSG_751_000 = 0x00007510, //!< Start over
    MSG_752_000 = 0x00007520, //!< Quit
    MSG_800_000 = 0x00008000, //!< Attach the Wii Remote wrist strap.
    MSG_850_000 = 0x00008500, //!< Slip the Wii Remote strap\nthrough the connector\nhook of the Nunchuk plug,\nthen connect the Nunchuk.
    MSG_851_000 = 0x00008510, //!< Unplug the extension controller\nconnected to this Wii Remote.
    MSG_860_000 = 0x00008600, //!< Put the Wii Remote strap through\nthe Nunchuk's connector hook.
    MSG_870_000 = 0x00008700, //!< {000001}
    MSG_871_000 = 0x00008710, //!< OK!
    MSG_880_000 = 0x00008800, //!< Starting the game...\n\nHold the Wii Remote\nsecurely in your hand and\npress \uE042 and \uE043.
    MSG_900_000 = 0x00009000, //!< Are you using your Wii Remote\nJacket? Make sure there are\nno people or objects around\nthat you might bump into!
    MSG_901_000 = 0x00009010, //!< Why not take a break?\nYou can pause the game\nby pressing \uE045.
    MSG_999_000 = 0x00009990, //!<
    // clang-format on
};

#endif
