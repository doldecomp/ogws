#ifndef RP_KERNEL_CONTROLLER_MGR_H
#define RP_KERNEL_CONTROLLER_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

#include <egg/core.h>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class RPSysCoreController;
class RPSysPairingMgr;

/**
 * @brief Wii Remote controller manager
 */
class RPSysCoreControllerMgr : public EGG::CoreControllerMgr {
    RP_SINGLETON_DECL(RPSysCoreControllerMgr);

public:
    /**
     * @brief Initializes the controller manager singleton
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
    RPSysCoreController* findController(s32 chan) const;

    /**
     * @brief Prepares the controller system for a scene reset
     */
    void sceneReset();

    /**
     * @brief Enables pairing of controllers
     */
    void enableConnection() const;

    /**
     * @brief Disables pairing of controllers
     */
    void disableConnection() const;

    /**
     * @brief Tests whether DPD control is enabled for the specified remote
     * channel
     *
     * @param chan Remote channel
     */
    static bool isDpdCtrlEnable(s32 chan) {
        return sDpdCtrlEnableFlag & (1 << chan);
    }

private:
    /**
     * @brief Controller search type
     */
    enum ESearchType {
        ESearchType_Address, //!< Find controllers by their address
        ESearchType_Channel, //!< Find controllers by their remote channel
    };

    //! Required work memory size
    static const u32 MIN_WORK_SIZE = 0x100000;

private:
    /**
     * @brief Controller connect callback
     *
     * @param rArg Callback argument
     */
    static void connectCallback(const EGG::CoreControllerConnectArg& rArg);

    /**
     * @brief WPAD clear device callback
     *
     * @param result WPAD sync result
     */
    static void clearDeviceCallback(s32 result);

    /**
     * @brief WPAD DPD control callback
     *
     * @param chan Remote channel
     * @param result WPAD DPD command
     */
    static void controlDpdCallback(s32 chan, s32 result);

private:
    //! Bitfield of controllers currently connected
    static u16 sConnectionFlag;
    //! Bitfield of controllers connected during the previous frame
    static u16 sPrevConnectionFlag;

    //! Bitfield of controllers with DPD control enabled
    static u16 sDpdCtrlEnableFlag;

    //! Whether WPADClearDevice has completed
    static bool sClearDeviceFlag;

    char unk30[0x60 - 0x30];

    //! Controller search type
    ESearchType mSearchType; // at 0x60

    //! Controller pairing manager
    RPSysPairingMgr* mpPairingMgr; // at 0x64
};

//! @}

#endif
