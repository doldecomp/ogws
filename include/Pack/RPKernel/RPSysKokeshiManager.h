#ifndef RP_KERNEL_KOKESHI_MANAGER_H
#define RP_KERNEL_KOKESHI_MANAGER_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

#include <revolution/WPAD.h>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class RPSysKokeshiCtrlMgr;
class RPSysKokeshiCtrlDataLoader;

/**
 * @brief Mii manager
 */
class RPSysKokeshiManager {
    RP_SINGLETON_DECL(RPSysKokeshiManager);

public:
    /**
     * @brief Sets the active controller manager
     *
     * @param pCtrlMgr Controller manager
     */
    void SetCtrlMgr(RPSysKokeshiCtrlMgr* pCtrlMgr);

    /**
     * @brief Clears the active controller manager
     */
    void ClearCtrlMgr();

    /**
     * @brief Accesses the specified controller data loader
     *
     * @param chan WPAD channel
     */
    RPSysKokeshiCtrlDataLoader* GetCtrlDataLoader(s32 chan) const {
        return mppCtrlDataLoaders[chan];
    }

private:
    char unk04[0x44 - 0x4];

    RPSysKokeshiCtrlDataLoader*
        mppCtrlDataLoaders[WPAD_MAX_CONTROLLERS]; // at 0x44
};

//! @}

#endif
