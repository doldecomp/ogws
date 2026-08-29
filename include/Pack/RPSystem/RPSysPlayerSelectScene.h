#ifndef RP_SYSTEM_PLAYER_SELECT_SCENE_H
#define RP_SYSTEM_PLAYER_SELECT_SCENE_H
#include <Pack/types_pack.h>

#include <Pack/RPSystem/RPSysScene.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Pack Project player select scene
 */
class RPSysPlayerSelectScene : public RPSysScene {
private:
    char unk44[0x8C - 0x44];
};

//! @}

#endif
