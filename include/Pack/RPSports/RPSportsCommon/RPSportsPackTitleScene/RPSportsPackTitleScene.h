#ifndef RP_SPORTS_COMMON_PACK_TITLE_SCENE_H
#define RP_SPORTS_COMMON_PACK_TITLE_SCENE_H
#include <Pack/types_pack.h>

#include <Pack/RPUtility.h>

//! @addtogroup rp_sports
//! @{

/**
 * @brief Sports Pack title screen scene
 */
class RPSportsPackTitleScene : public RPUtlLoadSaveDataScene {
private:
    struct UnkStruct {
        u32 unk0;
        u32 unk4;
        u32 unk8;

        UnkStruct() : unk0(0), unk4(0), unk8(0) {}
    };

private:
    char unk44[0x54 - 0x44];
    UnkStruct unk60[(0x84 - 0x54) / sizeof(UnkStruct)];
    char unk84[0xA0 - 0x84];
};

//! @}

#endif
