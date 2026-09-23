#ifndef RP_PARTY_COMMON_PACK_TITLE_SCENE_H
#define RP_PARTY_COMMON_PACK_TITLE_SCENE_H
#include <Pack/types_pack.h>

#include <Pack/RPUtility.h>

//! @addtogroup rp_party
//! @{

/**
 * @brief Party Pack title screen scene
 */
class RPPartyPackTitleScene : public RPUtlLoadSaveDataScene {
    char unk44[0x68 - 0x44];
};

//! @}

#endif
