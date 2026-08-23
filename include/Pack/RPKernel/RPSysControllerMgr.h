#ifndef RP_KERNEL_CONTROLLER_MGR_H
#define RP_KERNEL_CONTROLLER_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel/RPSysController.h>
#include <Pack/RPSingleton.h>

#include <egg/core.h>

#include <revolution/WPAD.h>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class RPSysCoreController;
class RPSysPairingMgr;

/**
 * @brief Pack Project controller manager
 */
class RPSysCoreControllerMgr : public EGG::CoreControllerMgr {
    RP_SINGLETON_DECL(RPSysCoreControllerMgr);

public:
    /**
     * @brief Instantiates the controller manager singleton
     */
    static void create();

    /**
     * @brief Performs processing at the beginning of the frame
     */
    virtual void beginFrame() override; // at 0x8

    /**
     * @brief Performs processing at the end of the frame
     */
    virtual void endFrame() override; // at 0xC

    /**
     * @brief Accesses the controller using the specified channel
     *
     * @param chan Remote channel
     */
    RPSysCoreController* getNthController(s32 chan) const;

    void sceneReset();

    /**
     * @brief Enables automatic controller pairing
     */
    void startPairing() const;

    /**
     * @brief Disables automatic controller pairing
     */
    void stopPairing() const;

    static u32 isDpdCtrlEnable(s32 chan) {
        return sDpdCtrlEnableFlag & (1 << chan);
    }

    static RPSysCoreController* getNthController(int index) {
        EGG::CoreController* pController =
            EGG_GET_INSTANCE(EGG::CoreControllerMgr)->getNthController(index);

        return static_cast<RPSysCoreController*>(pController);
    }

private:
    //! Required work memory size
    static const u32 MIN_WORK_SIZE = 0x100000;

private:
    static void connectCallback(const EGG::CoreControllerConnectArg& rArg);
    static void clearDeviceCallback(s32 result);
    static void controlDpdCallback(s32 chan, s32 result);

private:
    static u16 sCtrlConnectedFlag;
    static u16 sPrevCtrlConnectedFlag;
    static u16 sDpdCtrlEnableFlag;
    static bool sClearDeviceFlag;

    // at 0x34

    RPSysPairingMgr* mpPairingMgr; // at 0x64
};

//! @}

#endif
