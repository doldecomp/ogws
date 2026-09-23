#ifndef RP_SYSTEM_BOOT_SCENE_H
#define RP_SYSTEM_BOOT_SCENE_H
#include <Pack/types_pack.h>

#include <Pack/RPSystem/RPSysScene.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Pack Project bootup scene
 */
class RPSysBootScene : public RPSysScene {
private:
    char unk44[0x58 - 0x44];
};

//! @}

#endif
