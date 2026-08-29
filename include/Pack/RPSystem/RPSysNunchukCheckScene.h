#ifndef RP_SYSTEM_NUNCHUK_CHECK_SCENE_H
#define RP_SYSTEM_NUNCHUK_CHECK_SCENE_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel.h>
#include <Pack/RPSystem/RPSysScene.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Pack Project Nunchuk check scene
 */
class RPSysNunchukCheckScene : public RPSysScene, public IRPSysHostIOSocket {
private:
    char unk48[0x98 - 0x48];
};

//! @}

#endif
