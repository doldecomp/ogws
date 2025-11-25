#ifndef RP_KERNEL_I_KOKESHI_CTRL_DATA_CALLBACK_H
#define RP_KERNEL_I_KOKESHI_CTRL_DATA_CALLBACK_H
#include <Pack/types_pack.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Controller Mii data callback
 */
class IRPSysKokeshiCtrlDataCallback {
public:
    /**
     * @brief Called when new controller Mii data is available
     *
     * @param chan WPAD channel of the owner remote
     * @param index Controller database index
     */
    virtual void onCreateResource(s32 chan, u8 index) = 0;

    /**
     * @brief Called when controller Mii resources are being released
     *
     * @param chan WPAD channel of the owner remote
     * @param index Controller database index
     */
    virtual void onReleaseResource(s32 chan, u8 index) = 0;
};

//! @}

#endif
