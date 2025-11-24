#ifndef RP_KERNEL_CONTROLLER_SYNC_MGR_H
#define RP_KERNEL_CONTROLLER_SYNC_MGR_H
#include <Pack/types_pack.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Controller synchronization manager
 */
class RPSysControllerSyncMgr {
public:
    /**
     * @brief Constructor
     */
    RPSysControllerSyncMgr();

    /**
     * @brief Updates the sync state
     */
    void calc();

    /**
     * @brief Sets whether syncing is enabled
     *
     * @param enabled Whether to enable syncing
     */
    void setEnabled(bool enabled) {
        mIsEnabled = enabled;
    }

private:
    /**
     * @brief Synchronization state
     */
    enum ESyncState {
        ESyncState_Start, //! Begin sync search
        ESyncState_Stop,  //!< End sync search
        ESyncState_Wait,  //!< Wait for results
    };

private:
    /**
     * @brief WPAD simple sync callback
     *
     * @param result WPAD sync result
     * @param num Number of synced controllers
     */
    static void simpleSyncCallback(s32 result, s32 num);

private:
    //! Whether the simple sync is currently ongoing
    static bool sIsSyncing;

    //! Current sync state
    ESyncState mSyncState; // at 0x0
    //! Whether syncing is enabled
    bool mIsEnabled; // at 0x4
};

//! @}

#endif
