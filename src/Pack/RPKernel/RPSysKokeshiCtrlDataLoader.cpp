#include <Pack/RPKernel.h>

#include <RVLFaceLib.h>

/**
 * @brief Constructor
 *
 * @param chan WPAD channel to use
 */
RPSysKokeshiCtrlDataLoader::RPSysKokeshiCtrlDataLoader(s32 chan)
    : mChannel(chan), mLoadState(ELoadState_Start) {}

/**
 * @brief Destructor
 */
RPSysKokeshiCtrlDataLoader::~RPSysKokeshiCtrlDataLoader() {}

/**
 * @brief Tests whether an error occurred during loading
 */
BOOL RPSysKokeshiCtrlDataLoader::isError() const {
    return mLoadState != ELoadState_Finish ? TRUE : FALSE;
}

/**
 * @brief Begins loading Mii data from the controller
 */
void RPSysKokeshiCtrlDataLoader::load() {
    if (mLoadState == ELoadState_Wait) {
        return;
    }

    mLoadState = ELoadState_Wait;

    switch (RFLLoadControllerAsync(mChannel)) {
    case RFLErrcode_Controllerfail: {
        mLoadState = ELoadState_Start;
        break;
    }

    case RFLErrcode_Busy: {
        break;
    }

    default: {
        mLoadState = ELoadState_Start;
        break;
    }
    }
}

/**
 * @brief Tests whether the loader is in an idle state
 */
BOOL RPSysKokeshiCtrlDataLoader::isIdle() const {
    return mLoadState != ELoadState_Wait ? TRUE : FALSE;
}

/**
 * @brief Updates the loader state
 */
void RPSysKokeshiCtrlDataLoader::calc() {
    switch (mLoadState) {
    case ELoadState_Start: {
        break;
    }

    case ELoadState_Wait: {
        switch (RFLGetAsyncStatus()) {
        case RFLErrcode_Success:
        case RFLErrcode_NANDCommandfail: {
            mLoadState = ELoadState_Finish;
            break;
        }

        case RFLErrcode_Loadfail:
        case RFLErrcode_Controllerfail: {
            mLoadState = ELoadState_Start;
            break;
        }

        case RFLErrcode_Busy: {
            break;
        }

        default: {
            mLoadState = ELoadState_Start;
            break;
        }
        }

        break;
    }

    case ELoadState_Finish: {
        break;
    }
    }
}
