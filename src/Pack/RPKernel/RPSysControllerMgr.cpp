#include <Pack/RPAudio.h>
#include <Pack/RPAudio/archive/rp_Static_sound.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSingleton.h>
#include <Pack/RPSystem.h>

#include <egg/core.h>

#include <revolution/KPAD.h>
#include <revolution/WPAD.h>

/**
 * @brief Bitfield of controllers currently connected
 */
u16 RPSysCoreControllerMgr::sConnectionFlag = 0;

/**
 * @brief Bitfield of controllers connected during the previous frame
 */
u16 RPSysCoreControllerMgr::sPrevConnectionFlag = 0;

/**
 * @brief Bitfield of controllers with DPD control enabled
 */
u16 RPSysCoreControllerMgr::sDpdCtrlEnableFlag = 0;

/**
 * @brief Whether WPADClearDevice has completed
 */
bool RPSysCoreControllerMgr::sClearDeviceFlag = false;

RP_SINGLETON_IMPL(RPSysCoreControllerMgr);

/**
 * @brief Constructor
 */
RPSysCoreControllerMgr::RPSysCoreControllerMgr()
    : mSearchType(ESearchType_Channel) {

    mpPairingMgr = new RPSysPairingMgr();
}

/**
 * @brief Controller connect callback
 *
 * @param rArg Callback argument
 */
void RPSysCoreControllerMgr::connectCallback(
    const EGG::CoreControllerConnectArg& rArg) {

    switch (rArg.result) {
    case WPAD_ERR_OK: {
        sConnectionFlag |= 1 << rArg.chan;
        RPSndSpeakerMgr::setSpeakerOnCallback(rArg.chan, rArg.result);
        break;
    }

    case WPAD_ERR_NO_CONTROLLER: {
        sConnectionFlag &= ~(1 << rArg.chan);
        RPSndSpeakerMgr::setSpeakerOffCallback(rArg.chan, rArg.result);
        break;
    }
    }
}

/**
 * @brief WPAD clear device callback
 *
 * @param result WPAD sync result
 */
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

/**
 * @brief WPAD DPD control callback
 *
 * @param chan Remote channel
 * @param result WPAD DPD command
 */
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
 * @brief Initializes the controller manager singleton
 */
void RPSysCoreControllerMgr::create() {
    u32 workSize = WPADGetWorkMemorySize();
    if (workSize <= MIN_WORK_SIZE) {
        workSize = MIN_WORK_SIZE;
    }

    sWPADWorkSize = workSize;

    // Override the EGG manager
    RPSysCoreControllerMgr* p = new RPSysCoreControllerMgr();
    EGG::CoreControllerMgr::sInstance = p;
    spInstance = p;

    WPADSetClearDeviceCallback(clearDeviceCallback);
    setConnectCallback(connectCallback);

    for (s32 i = 0; i < RP_MAX_CONTROLLERS; i++) {
        KPADSetControlDpdCallback(i, controlDpdCallback);
    }
}

/**
 * @brief Accesses the controller using the specified channel
 *
 * @param chan Remote channel
 */
RPSysCoreController* RPSysCoreControllerMgr::findController(s32 chan) const {
    RPSysCoreController* pFound = NULL;

    for (int i = 0; i < mControllers.getSize(); i++) {
        RPSysCoreController* pIt =
            static_cast<RPSysCoreController*>(mControllers.get(i));

        if (pIt->getChannelID() == chan) {
            pFound = pIt;
            break;
        }
    }

    return pFound;
}

/**
 * @brief Prepares the controller system for a scene reset
 */
void RPSysCoreControllerMgr::sceneReset() {
    u16 connected = sConnectionFlag;

    for (int i = 0; i < mControllers.getSize(); i++) {
        RPSysCoreController* pIt =
            static_cast<RPSysCoreController*>(mControllers.get(i));

        if (connected & 1 << pIt->getChannelID()) {
            continue;
        }

        pIt->getAddress().reset();

        // Find the next connected controller in the order
        RPSysCoreController* pTarget = NULL;
        for (int j = i + 1; j < mControllers.getSize(); j++) {
            RPSysCoreController* pIt =
                static_cast<RPSysCoreController*>(mControllers.get(j));

            if (connected & 1 << pIt->getChannelID()) {
                pTarget = pIt;
                break;
            }
        }

        // Swap the data, moving all connected controllers towards the front
        if (pTarget != NULL) {
            s32 fromChan = pIt->getChannelID();
            RPSysCoreAddress fromAddr = pIt->getAddress();

            s32 toChan = pTarget->getChannelID();
            RPSysCoreAddress toAddr = pTarget->getAddress();

            pIt->set(toChan, toAddr);
            pTarget->set(fromChan, fromAddr);
        }
    }
}

/**
 * @brief Performs processing at the beginning of the frame
 */
void RPSysCoreControllerMgr::beginFrame() {
    u16 connected = sConnectionFlag;
    u16 prevConnected = sPrevConnectionFlag;

    // Newly connected controllers
    u16 connectOn = connected & (connected ^ prevConnected);
    // Newly disconnected controllers
    u16 connectOff = prevConnected & (connected ^ prevConnected);

    sPrevConnectionFlag = connected;

    if (sClearDeviceFlag) {
        sClearDeviceFlag = false;
    }

    for (int i = 0; i < mControllers.getSize(); i++) {
        RPSysCoreController* pIt =
            static_cast<RPSysCoreController*>(mControllers.get(i));

        pIt->mEvent = RPSysCoreController::EEvent_None;
    }

    s32 chan = 0;

    do {
        if (connectOn & 1 << chan) {
            RPSysCoreAddress addr;
            addr.read(chan);

            if (addr.isValid()) {
                RPSysCoreController* pConnected;

                // Try to find the controller that belongs to this connection
                switch (mSearchType) {
                case ESearchType_Channel: {
                    pConnected = findController(chan);
                    break;
                }

                default: /* ESearchType_Address */ {
                    int players = mControllers.getSize();

                    if (RP_GET_INSTANCE(RPSysProjectLocal) != NULL) {
                        switch (RP_GET_INSTANCE(RPSysProjectLocal)->getPack()) {
                        case RPSysSceneCreator::EPackID_PartyPack: {
                            players = RP_PARTY_MAX_PLAYERS;
                            break;
                        }

                        default: {
                            break;
                        }
                        }
                    }

                    pConnected = NULL;

                    for (int i = 0; i < players; i++) {
                        if (i >= mControllers.getSize()) {
                            continue; // ???
                        }

                        RPSysCoreController* pIt =
                            static_cast<RPSysCoreController*>(
                                mControllers.get(i));

                        if (pIt->getAddress().isEqual(addr)) {
                            pConnected = pIt;
                            break;
                        }
                    }
                    break;
                }
                }

                // Take the first available controller instead
                if (pConnected == NULL) {
                    pConnected = NULL; // ???

                    for (int i = 0; i < mControllers.getSize(); i++) {
                        RPSysCoreController* pIt =
                            static_cast<RPSysCoreController*>(
                                mControllers.get(i));

                        if ((connectOn & 1 << pIt->getChannelID()) ||
                            !(prevConnected & 1 << pIt->getChannelID())) {

                            pConnected = pIt;
                            break;
                        }
                    }
                }

                // Swap the controller assignment
                if (pConnected != NULL) {
                    RPSysCoreController* pChanOwner = findController(chan);

                    if (pChanOwner != pConnected) {
                        RPSysCoreAddress foundAddr = pConnected->getAddress();
                        pChanOwner->set(pConnected->getChannelID(), foundAddr);
                    }

                    pConnected->set(chan, addr);

                    if (pConnected->mPlayerNo == 0) {
                        pConnected->becomeMainController();
                    }

                    pConnected->rumble(
                        RPSysCoreController::ERumblePattern_Connect);

                    RP_GET_INSTANCE(RPSndAudioMgr)
                        ->getStaticMgr()
                        .startSe(rp_STATIC_CONNECT_01_CTSP,
                                 pConnected->mPlayerNo);

                    pConnected->mEvent = RPSysCoreController::EEvent_Connect;
                }
            }

            RPSysCoreController::forceSensorBarPowerOn();
        }

        if (connectOff & 1 << chan) {
            RPSysCoreController* pDisconnected = findController(chan);
            pDisconnected->mEvent = RPSysCoreController::EEvent_Disconnect;

            RPSysCoreController::sDisconnectOccurred = true;
        }

    } while (++chan < RP_MAX_CONTROLLERS);

    EGG::CoreControllerMgr::beginFrame();
    mpPairingMgr->calc();

    // Old data becomes invalid when controller configuration changes
    if (connectOff & (1 << RP_MAX_CONTROLLERS) - 1) {
        RP_GET_INSTANCE(RPSysPlayerMgr)->resetOldData();
    }
}

/**
 * @brief Performs processing at the end of the frame
 */
void RPSysCoreControllerMgr::endFrame() {
    EGG::CoreControllerMgr::endFrame();
}

/**
 * @brief Enables pairing of controllers
 */
void RPSysCoreControllerMgr::enableConnection() const {
    mpPairingMgr->setEnabled(true);
}

/**
 * @brief Disables pairing of controllers
 */
void RPSysCoreControllerMgr::disableConnection() const {
    mpPairingMgr->setEnabled(false);
}
