#ifndef RP_PARTY_BOM_SCENE_H
#define RP_PARTY_BOM_SCENE_H
#include <Pack/types_pack.h>

#include <Pack/RPSystem.h>

//! @addtogroup rp_bom
//! @{

/**
 * @brief Party Pack Pose Mii scene
 */
class RPBomScene : public RPSysScene {
    char unk44[0x8C - 0x44];
};

//! @}

#endif
