#include <Pack/RPAudio.h>

#include <revolution/OS.h>
#include <revolution/WPAD.h>

RP_SINGLETON_IMPL_EX(RPSndSpeakerMgr);

/**
 * @brief Resets the state of each remote speaker
 */
void RPSndSpeakerMgr::reset() {
    connectAll();
}

/**
 * @brief Updates the state of each remote speaker
 */
void RPSndSpeakerMgr::calc() {
    s32 chan;

    for (chan = 0; chan < WPAD_MAX_CONTROLLERS; chan++) {
        bool enableNow =
            nw4r::snd::SoundSystem::GetRemoteSpeaker(chan).IsEnabledOutput();

        if (enableNow != mIsEnabledOutput[chan] &&
            mIsEnabledOutput[chan] == true) {

            if (unk3C[chan] < unk1C[chan]) {
                unk3C[chan] = unk1C[chan];
            }

            unk1C[chan] = 0;
        }

        mIsEnabledOutput[chan] = enableNow;
    }

    if (!mIsBusy) {
        if (mTaskFinishCount != mTaskRequestCount) {
            taskSpeakerSw(mTaskQueue[mTaskFinishCount].chan,
                          mTaskQueue[mTaskFinishCount].on);
        }
    } else {
        chan = mTaskQueue[mTaskFinishCount].chan;
        mTaskQueue[mTaskFinishCount].timeOut--;

        if (isTaskFinished(chan) || mTaskQueue[mTaskFinishCount].timeOut == 0) {
            mIsBusy = false;

            if (++mTaskFinishCount >= QUEUE_SIZE) {
                mTaskFinishCount = 0;
            }
        }
    }
}

/**
 * @brief Finalizes the state of each remote speaker
 */
void RPSndSpeakerMgr::exit() {
    disconnectAll();
}

/**
 * @brief Fetches the latest WPAD master volume
 */
void RPSndSpeakerMgr::updateMasterVolume() {
    mMasterVolume = WPADGetSpeakerVolume();
}

/**
 * @brief Toggles enabling output of the specified remote speaker
 *
 * @param chan Remote speaker channel
 * @param enable Whether to enable the speaker output
 * @return Previous enable status
 */
bool RPSndSpeakerMgr::setEnableSw(s32 chan, bool enable) {
    if (!mIsSpeakerSetUp[chan]) {
        return false;
    }

    bool enablePrev =
        nw4r::snd::SoundSystem::GetRemoteSpeaker(chan).IsEnabledOutput();

    if (enable == true && unk2C[chan] != 0) {
        return false;
    }

    if (chan < WPAD_MAX_CONTROLLERS && enablePrev != enable) {
        nw4r::snd::SoundSystem::GetRemoteSpeaker(chan).EnableOutput(enable);

        if (!enable) {
            if (unk3C[chan] < unk1C[chan]) {
                unk3C[chan] = unk1C[chan];
            }

            unk1C[chan] = 0;
            unk2C[chan] = 0;
            unk4C[chan] = 0;
        }

        return enable;
    }

    return enablePrev;
}

/**
 * @brief Configures the main and remote output volumes of the specified
 * sound handle
 *
 * @param pHandle Sound handle
 * @param channelFlag Remote channel output line flags
 * @param mainOut Main output volume
 * @param remoteOut Remote output volume
 * @param muteOut Main output volume when the remote speaker is muted
 */
void RPSndSpeakerMgr::setRemoteSend(nw4r::snd::SoundHandle* pHandle,
                                    u32 channelFlag, f32 mainOut, f32 remoteOut,
                                    f32 muteOut) {
    if (pHandle == NULL) {
        return;
    }

    if (unk14 == 1 || mMasterVolume == 0) {
        remoteOut = 0.0f;
        mainOut = muteOut;
    }

    u32 remoteOutFlag =
        channelFlag == 0 ? 0 : changeBitPlayerToChannel(channelFlag);

    u32 outputFlag = 0;
    u32 mainOutFlag = 0;

    if (remoteOut > 0.0f) {
        for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
            if (!(remoteOutFlag & (1 << i)) || !mIsSpeakerSetUp[i]) {
                continue;
            }

            outputFlag |= 1 << i;
            setEnableSw(i, true);
            pHandle->SetRemoteOutVolume(i, remoteOut);
        }
    }

    if (mainOut != 0.0f) {
        pHandle->SetMainOutVolume(mainOut);
        mainOutFlag = nw4r::snd::OUTPUT_LINE_MAIN;
    }

    pHandle->SetOutputLine(mainOutFlag | (outputFlag << 1));
}

/**
 * @brief Constructor
 *
 * @param pHeap Parent heap
 */
RPSndSpeakerMgr::RPSndSpeakerMgr(EGG::Heap* pHeap) : mpParentHeap(pHeap) {
    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        unk1C[i] = 0;
        unk3C[i] = 0;
        unk2C[i] = 0;
        mIsSpeakerSetUp[i] = false;
        unk4C[i] = 0;
        mIsEnabledOutput[i] = false;
        unk68[i] = 0;
    }

    unk18 = 0;
    mTaskRequestCount = 0;
    mTaskFinishCount = 0;
    mIsBusy = false;
    unk114 = 0;
    mMasterVolume = WPAD_MAX_SPEAKER_VOLUME;
    unk14 = 0;
    mIsDisconnected = false;
}

/**
 * @brief Destructor
 */
RPSndSpeakerMgr::~RPSndSpeakerMgr() {}

/**
 * @brief Callback for new remote connections
 *
 * @param chan Remote channel
 * @param result WPAD library result
 */
void RPSndSpeakerMgr::setSpeakerOnCallback(s32 chan, s32 result) {
    if (RP_GET_INSTANCE(RPSndSpeakerMgr)->mIsDisconnected) {
        RP_GET_INSTANCE(RPSndSpeakerMgr)->mIsSpeakerOn[chan] = true;
    } else if (result == WPAD_ERR_OK) {
        setSpeakerSw(chan, true);
    }
}

/**
 * @brief Callback for remote disconnections
 *
 * @param chan Remote channel
 * @param result WPAD library result
 */
void RPSndSpeakerMgr::setSpeakerOffCallback(s32 chan, s32 result) {
    if (RP_GET_INSTANCE(RPSndSpeakerMgr)->mIsDisconnected) {
        RP_GET_INSTANCE(RPSndSpeakerMgr)->mIsSpeakerOn[chan] = false;
    } else if (result == WPAD_ERR_NO_CONTROLLER) {
        setSpeakerSw(chan, false);
    }
}

/**
 * @brief Callback for initializing remote speaker connections
 *
 * @param chan Remote channel
 * @param result WPAD library result
 */
void RPSndSpeakerMgr::setSpeakerSetupCallback(s32 chan, s32 result) {
    if (result == WPAD_ERR_OK) {
        RP_GET_INSTANCE(RPSndSpeakerMgr)->mIsSpeakerSetUp[chan] = true;
    }

    RP_GET_INSTANCE(RPSndSpeakerMgr)->mTaskQueue[chan].finish = true;
}

/**
 * @brief Callback for finalizing remote speaker connections
 *
 * @param chan Remote channel
 * @param result WPAD library result
 */
void RPSndSpeakerMgr::setSpeakerShutdownCallback(s32 chan, s32 result) {
    if (result == WPAD_ERR_OK || result == WPAD_ERR_NO_CONTROLLER) {
        RP_GET_INSTANCE(RPSndSpeakerMgr)->mIsSpeakerSetUp[chan] = false;
    }

    RP_GET_INSTANCE(RPSndSpeakerMgr)->mTaskQueue[chan].finish = true;
}

/**
 * @brief Attempts to connect to all remote speakers
 */
void RPSndSpeakerMgr::connectAll() {
    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        s32 dev;
        if (WPADProbe(i, &dev) == WPAD_ERR_NO_CONTROLLER) {
            continue;
        }

        bool success = nw4r::snd::SoundSystem::GetRemoteSpeaker(i).Setup(
            setSpeakerSetupCallback);

        if (!success) {
            setSpeakerSw(i, true);
        }
    }

    mIsDisconnected = false;
}
/**
 * @brief Attempts to disconnect from all remote speakers
 */
void RPSndSpeakerMgr::disconnectAll() {
    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        nw4r::snd::SoundSystem::GetRemoteSpeaker(i).Shutdown(NULL);

        mIsSpeakerSetUp[i] = false;
        mIsSpeakerOn[i] = true;
    }

    mIsDisconnected = true;
}

/**
 * @brief Tests whether the manager has no connections and is in an idle
 * state
 */
bool RPSndSpeakerMgr::isDisconnectAllFinished() {
    if (mIsDisconnected == false) {
        return false;
    }

    return mTaskRequestCount == mTaskFinishCount;
}

/**
 * @brief Converts player-indexed bitflags to remote channel output flags
 *
 * @param playerFlag Player flags
 * @return Remote channel output line flags
 */
u32 RPSndSpeakerMgr::changeBitPlayerToChannel(u32 playerFlag) {
    u32 channelFlag = 0;

    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        if (!(playerFlag & (1 << i))) {
            continue;
        }

        if (i >= RP_GET_INSTANCE(RPSndAudioMgr)->getPlayerNum()) {
            continue;
        }

        s32 chan = EGG_GET_INSTANCE(EGG::CoreControllerMgr)
                       ->getNthController(i)
                       ->getChannelID();

        channelFlag |= 1 << chan;
    }

    return channelFlag;
}

/**
 * @brief Requests a change in the specified remote speaker's state
 *
 * @param chan Remote speaker channel
 * @param on Whether to turn the speaker on
 */
void RPSndSpeakerMgr::setSpeakerSw(s32 chan, bool on) {
    BOOL enabled = OSDisableInterrupts();

    // clang-format off
    RP_GET_INSTANCE(RPSndSpeakerMgr)
        ->mTaskQueue[RP_GET_INSTANCE(RPSndSpeakerMgr)->mTaskRequestCount].chan = chan;

    RP_GET_INSTANCE(RPSndSpeakerMgr)
        ->mTaskQueue[RP_GET_INSTANCE(RPSndSpeakerMgr)->mTaskRequestCount].on = on;

    RP_GET_INSTANCE(RPSndSpeakerMgr)
        ->mTaskQueue[RP_GET_INSTANCE(RPSndSpeakerMgr)->mTaskRequestCount].finish = false;

    RP_GET_INSTANCE(RPSndSpeakerMgr)
        ->mTaskQueue[RP_GET_INSTANCE(RPSndSpeakerMgr)->mTaskRequestCount].timeOut = TIMEOUT;
    // clang-format on

    if (++RP_GET_INSTANCE(RPSndSpeakerMgr)->mTaskRequestCount >= QUEUE_SIZE) {
        RP_GET_INSTANCE(RPSndSpeakerMgr)->mTaskRequestCount = 0;
    }

    OSRestoreInterrupts(enabled);
}

/**
 * @brief Processes the specified remote speaker connection
 *
 * @param chan Remote speaker channel
 * @param on Whether to turn the speaker on
 */
void RPSndSpeakerMgr::taskSpeakerSw(s32 chan, bool on) {
    mIsBusy = true;

    if (on) {
        bool success = nw4r::snd::SoundSystem::GetRemoteSpeaker(chan).Setup(
            setSpeakerSetupCallback);

        if (!success) {
            setSpeakerSw(chan, true);
        }
    } else {
        nw4r::snd::SoundSystem::GetRemoteSpeaker(chan).Shutdown(
            setSpeakerShutdownCallback);
    }
}

/**
 * @brief Tests whether the specified connection task has completed
 *
 * @param chan Remote speaker channel
 */
bool RPSndSpeakerMgr::isTaskFinished(s32 chan) {
    return RP_GET_INSTANCE(RPSndSpeakerMgr)->mTaskQueue[chan].finish == true;
}
