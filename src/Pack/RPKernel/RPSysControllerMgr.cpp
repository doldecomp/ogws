#include <Pack/RPAudio.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSingleton.h>

#include <egg/core.h>

#include <revolution/KPAD.h>
#include <revolution/WPAD.h>

u16 RPSysCoreControllerMgr::sCtrlConnectedFlag = 0;

u16 RPSysCoreControllerMgr::sPrevCtrlConnectedFlag = 0;

u16 RPSysCoreControllerMgr::sDpdCtrlEnableFlag = 0;

bool RPSysCoreControllerMgr::sClearDeviceFlag = false;

RP_SINGLETON_IMPL(RPSysCoreControllerMgr);

void RPSysCoreControllerMgr::connectCallback(
    const EGG::CoreControllerConnectArg& rArg) {

    switch (rArg.result) {
    case WPAD_ERR_OK: {
        sCtrlConnectedFlag |= 1 << rArg.chan;
        RPSndSpeakerMgr::setSpeakerOnCallback(rArg.chan, rArg.result);
        break;
    }

    case WPAD_ERR_NO_CONTROLLER: {
        sCtrlConnectedFlag &= ~(1 << rArg.chan);
        RPSndSpeakerMgr::setSpeakerOffCallback(rArg.chan, rArg.result);
        break;
    }
    }
}

void RPSysCoreControllerMgr::clearDeviceCallback(s32 result) {
    switch (result) {
    case WPAD_SYNC_WAITING: {
        WPADStartClearDevice();
        break;
    }

    case WPAD_SYNC_DONE: {
        sClearDeviceFlag = true;
        break;
    }

    case WPAD_SYNC_BUSY:
    default: {
        break;
    }
    }
}

void RPSysCoreControllerMgr::controlDpdCallback(s32 chan, s32 result) {
    switch (result) {
    case WPAD_DPD_BASIC: {
        if (WPADIsDpdEnabled(chan)) {
            sDpdCtrlEnableFlag |= 1 << chan;
        } else {
            sDpdCtrlEnableFlag &= ~(1 << chan);
        }
        break;
    }

    case WPAD_DPD_DISABLE:
    default: {
        break;
    }
    }
}

/**
 * @brief Constructor
 */
RPSysCoreControllerMgr::RPSysCoreControllerMgr() {
    mpPairingMgr = new RPSysPairingMgr();
}

/**
 * @brief Instantiates the controller manager singleton
 */
void RPSysCoreControllerMgr::create() {
    sWPADWorkSize = WPADGetWorkMemorySize();
    if (sWPADWorkSize < MIN_WORK_SIZE) {
        sWPADWorkSize = MIN_WORK_SIZE;
    }

    RPSysCoreControllerMgr* p = new RPSysCoreControllerMgr();

    // Override the EGG manager
    EGG::CoreControllerMgr::sInstance = p;
    spInstance = p;

    WPADSetClearDeviceCallback(clearDeviceCallback);
    setConnectCallback(connectCallback);

    for (s32 i = 0; i < KPAD_MAX_CONTROLLERS; i++) {
        KPADSetControlDpdCallback(i, controlDpdCallback);
    }
}

/**
 * @brief Accesses the controller using the specified channel
 *
 * @param chan Remote channel
 */
RPSysCoreController* RPSysCoreControllerMgr::getNthController(s32 chan) const {
    RPSysCoreController* pController = NULL;

    for (int i = 0; i < mControllers.getSize(); i++) {
        EGG::CoreController* pIt = mControllers.get(i);

        if (pIt->getChannelID() == chan) {
            pController = static_cast<RPSysCoreController*>(pIt);
            break;
        }
    }

    return pController;
}

void RPSysCoreControllerMgr::sceneReset() {
    ;
}

/**
 * @brief Performs processing at the beginning of the frame
 */
void RPSysCoreControllerMgr::beginFrame() {
    ;
}

/**
 * @brief Performs processing at the end of the frame
 */
void RPSysCoreControllerMgr::endFrame() {
    CoreControllerMgr::endFrame();
}

/**
 * @brief Enables automatic controller pairing
 */
void RPSysCoreControllerMgr::startPairing() const {
    mpPairingMgr->setEnabled(true);
}

/**
 * @brief Disables automatic controller pairing
 */
void RPSysCoreControllerMgr::stopPairing() const {
    mpPairingMgr->setEnabled(false);
}
