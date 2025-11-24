#include <Pack/RPKernel.h>

#include <revolution/WPAD.h>

/**
 * @brief Whether the simple sync is currently ongoing
 */
bool RPSysControllerSyncMgr::sIsSyncing = false;

/**
 * @brief WPAD simple sync callback
 *
 * @param result WPAD sync result
 * @param num Number of synced controllers
 */
void RPSysControllerSyncMgr::simpleSyncCallback(s32 result, s32 /* num*/) {
    switch (result) {
    case WPAD_SYNC_WAITING: {
        break;
    }

    case WPAD_SYNC_BUSY: {
        sIsSyncing = false;
        break;
    }

    case WPAD_SYNC_DONE: {
        sIsSyncing = false;
        break;
    }

    default: {
        break;
    }
    }
}

/**
 * @brief Constructor
 */
RPSysControllerSyncMgr::RPSysControllerSyncMgr()
    : mSyncState(ESyncState_Start), mIsEnabled(false) {

    WPADSetSimpleSyncCallback(simpleSyncCallback);
}

/**
 * @brief Updates the sync state
 */
void RPSysControllerSyncMgr::calc() {
    switch (mSyncState) {
    case ESyncState_Start: {
        if (!mIsEnabled) {
            break;
        }

        if (WPADStartSimpleSync()) {
            mSyncState = ESyncState_Stop;
            sIsSyncing = true;
        }
        break;
    }

    case ESyncState_Stop: {
        if (mIsEnabled) {
            break;
        }

        if (WPADStopSimpleSync()) {
            mSyncState = ESyncState_Wait;
        }
        break;
    }

    case ESyncState_Wait: {
        if (!sIsSyncing) {
            mSyncState = ESyncState_Start;
        }
        break;
    }
    }
}
