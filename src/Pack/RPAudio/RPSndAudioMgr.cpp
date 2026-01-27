#include <Pack/RPAudio.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <egg/audio.h>
#include <egg/core.h>

#include <nw4r/snd.h>

#include <revolution/CNT.h>
#include <revolution/DVD.h>
#include <revolution/OS.h>
#include <revolution/SC.h>

#include <cstring>

RP_SINGLETON_IMPL_EX(RPSndAudioMgr);

/**
 * @brief Constructor
 *
 * @param pHeap Parent heap
 */
RPSndAudioMgr::RPSndAudioMgr(EGG::Heap* pHeap) : mpParentHeap(pHeap) {
    mSoundHeapLevel = 1;
    unk948 = 0;
    mArchivePath[0] = '\0';
    mState = EState_Exited;
    mShutDownStatusRP = SHUTDOWN_STATUS_NONE;
    mResetTimer = 0;
    mPlayerNum = WPAD_MAX_CONTROLLERS;
    mFlags = 0;
    mIsPauseSe = false;
    mFanfareLength = 0;
    mFanfareStart = 0;
    mIsNewDvdError = false;
    mStreamPlayTick = 0;
    mpSetFxCallback = NULL;
    mMenuPauseFrame = 20;
    mMenuPauseFadeInTimer = 0;
    mIsDisableFanfare = false;
}

/**
 * @brief Destructor
 */
RPSndAudioMgr::~RPSndAudioMgr() {}

/**
 * @brief Callback for sound heap deallocation
 *
 * @param pBuffer Memory block buffer
 * @param size Buffer size
 * @param pCallbackArg Callback user argument
 */
static void MemDeallocCallback(void* /* pBuffer */, u32 /* size */,
                               void* /* pCallbackArg */) {}

/**
 * @brief MemDeallocCallback user argument
 */
static void* MemDeallocCallbackArg = NULL;

static u32 DAT_804bf648 = 0;

/**
 * @brief Initializes the audio manager state
 *
 * @param pArg Audio system configuration
 */
void RPSndAudioMgr::initialize(Arg* pArg) {
    ExpAudioMgrArg* pArgExp = static_cast<ExpAudioMgrArg*>(pArg);

    pArgExp->maxVolumeDistance = 10000.0f;

    RPSysSceneCreator::EPackID pack =
        RP_GET_INSTANCE(RPSysProjectLocal)->getPack();

    // TODO(kiwi) How are these calculated?
    if (pack == RPSysSceneCreator::EPackID_SportsPack) {
        pArgExp->heapSize[nw4r::snd::AUX_A] = 0x31400;
        pArgExp->heapSize[nw4r::snd::AUX_B] = 0x400;
        pArgExp->heapSize[nw4r::snd::AUX_C] = 0x400;
    } else if (pack == RPSysSceneCreator::EPackID_PartyPack) {
        pArgExp->heapSize[nw4r::snd::AUX_A] = 0x25000;
        pArgExp->heapSize[nw4r::snd::AUX_B] = 0x9A80;
        pArgExp->heapSize[nw4r::snd::AUX_C] = 0x4080;
    } else {
        pArgExp->heapSize[nw4r::snd::AUX_A] = 0x2D000;
        pArgExp->heapSize[nw4r::snd::AUX_B] = 0x2D000;
        pArgExp->heapSize[nw4r::snd::AUX_C] = 0x2D000;
    }

    u32 soundHeapSize = pArgExp->soundHeapSize;
    pArgExp->soundHeapSize = 0;

    if (RP_GET_INSTANCE(RPSysProjectLocal)->getPack() ==
        RPSysSceneCreator::EPackID_SportsPack) {

        pArgExp->streamBlocks = 3;
    }

    ExpAudioMgr::initialize(pArgExp);
    createSoundHeap(pArgExp->pHeap, soundHeapSize);
    initializeFx(&getSoundHeap(), pArgExp);

    if (RP_GET_INSTANCE(RPSysProjectLocal)->getPack() ==
        RPSysSceneCreator::EPackID_HealthPack) {

        setDefaultFx();
    }

    mStaticMgr.setupArchive();
    saveState();

    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        RPSndObject::setCommonManager(&getSound3DManager(i), i);
    }
    RPSndObject::initList();

    mpBgmVolume = new (pArg->pHeap)
        RPSndMoveParam(RPSndMoveParam::ParamCategory_TrackVolume, mHandleBgm);

    RP_GET_INSTANCE(RPSndSpeakerMgr)->updateMasterVolume();

    mSoundHeapLevel = SoundHeapMgr::getCurrentLevel();
    saveState();
}

/**
 * @brief Attempts to open the specified sound archive, using storage
 * settings from the project locale
 *
 * @param pPath Sound archive path
 * @param pHeap Sound heap
 * @param pMultiHandle Multi handle for special storage types
 * @return Archive player
 */
nw4r::snd::SoundArchivePlayer*
RPSndAudioMgr::openArchiveRP(const char* pPath, nw4r::snd::SoundHeap* pHeap,
                             void* pMultiHandle) {

    if (getPlayer().IsAvailable() && std::strcmp(mArchivePath, pPath) == 0) {
        return &getPlayer();
    }

    // @bug Unsafe string operations
#if defined(BUG_FIX)
    std::strncpy(mArchivePath, pPath, ARRAY_SIZE(mArchivePath));
#else
    std::strcpy(mArchivePath, pPath);
#endif

    if (pHeap == NULL) {
        pHeap = &getSoundHeap();
    }

    nw4r::snd::SoundArchivePlayer* pPlayer;

    switch (RP_GET_INSTANCE(RPSysProjectLocal)->getSoundStorage()) {
    case RPSysProjectLocal::EStorage_DVDStream: {
        pPlayer =
            ExpAudioMgr::openArchive(pPath, pHeap, SARC_STORAGE_DVD, NULL);
        break;
    }

    case RPSysProjectLocal::EStorage_NANDBuffer: {
        EGG::CntFile file;
        file.initiate();

        file.open(pPath, static_cast<CNTHandle*>(pMultiHandle));
        u32 fileSize = file.getFileSize();

        void* pBuffer = getSoundHeap().Alloc(fileSize, MemDeallocCallback,
                                             MemDeallocCallbackArg);

        file.readData(pBuffer, fileSize, 0);
        file.close();

        pPlayer = ExpAudioMgr::setupMemoryArchive(pPath, pHeap);
        break;
    }

    case RPSysProjectLocal::EStorage_DVDBuffer: {
        EGG::DvdFile file;
        file.initiate();

        file.open(pPath);
        u32 fileSize = file.getFileSize();

        void* pBuffer = getSoundHeap().Alloc(fileSize, MemDeallocCallback,
                                             MemDeallocCallbackArg);

        file.readData(pBuffer, fileSize, 0);
        file.close();

        pPlayer = ExpAudioMgr::setupMemoryArchive(pPath, pHeap);
        break;
    }
    }

    setArcVolume(1.0f, 0);
    RPSndUtility::setPlayer(&getPlayer());

    return pPlayer;
}

/**
 * @brief Attempts to open and prepare the specified sound archive
 *
 * @param pPath Sound archive path
 * @param staticPath Whether the archive path is relative to the static
 * resource directory
 * @param pHeap Sound heap
 * @return Archive player
 */
nw4r::snd::SoundArchivePlayer*
RPSndAudioMgr::attachArchive(const char* pPath, bool staticPath,
                             nw4r::snd::SoundHeap* pHeap) {

    char commonPath[PATH_MAX];
    char localPath[PATH_MAX];
    char expPath[PATH_MAX];

    RPSysResourceManager* pResMgr = RP_GET_INSTANCE(RPSysResourceManager);

    if (staticPath) {
        pResMgr->GetStaticSoundCommonPath(commonPath, ARRAY_SIZE(commonPath));
        pResMgr->GetStaticSoundLocalPath(localPath, ARRAY_SIZE(localPath));
    } else {
        pResMgr->GetGameSoundCommonPath(commonPath, ARRAY_SIZE(commonPath));
        pResMgr->GetGameSoundLocalPath(localPath, ARRAY_SIZE(localPath));
    }

    // @bug Unsafe string operations
#if defined(BUG_FIX)
    std::strncat(commonPath, pPath, ARRAY_SIZE(commonPath));
    std::strncat(localPath, pPath, ARRAY_SIZE(localPath));
#else
    std::strcat(commonPath, pPath);
    std::strcat(localPath, pPath);
#endif

    void* pMultiHandle = pResMgr->GetMultiHandle();

    if (pResMgr->IsExist(commonPath)) {
        return openArchiveRP(commonPath, pHeap, pMultiHandle);
    }

    if (pResMgr->IsExist(localPath)) {
        return openArchiveRP(localPath, pHeap, pMultiHandle);
    }

    // Fallback to the music experiment scene?
    std::strcpy(expPath, "Sound/RPMpeScene/");

    // @bug Unsafe string operations
#if defined(BUG_FIX)
    std::strcat(expPath, pPath, ARRAY_SIZE(expPath));
#else
    std::strcat(expPath, pPath);
#endif

    if (pResMgr->IsExist(expPath)) {
        return openArchiveRP(expPath, pHeap, pMultiHandle);
    }

    return NULL;
}

/**
 * @brief Updates the state of the audio manager
 */
void RPSndAudioMgr::calc() {
    if (mShutDownStatusRP == SHUTDOWN_STATUS_QUEUED) {
        if (nw4r::snd::SoundSystem::GetMasterVolume() == 0.0f) {
            nw4r::snd::SoundSystem::ShutdownSoundSystem();
            nw4r::snd::SoundSystem::PrepareReset();
            nw4r::snd::SoundSystem::WaitForResetReady();

            mShutDownStatusRP = SHUTDOWN_STATUS_FINISH;
        }
    }

    if (mShutDownStatusRP == SHUTDOWN_STATUS_FINISH) {
        return;
    }

    if (mResetTimer > 0 && --mResetTimer == 0) {
        stopAllSound();
        resetArcVolume();
    }

    if (mHandleStream.IsAttachedSound()) {
        mStreamPlayTick++;
    }

    if (mIsPauseSe) {
        bool startSe = !mPauseSeWaitForDpd ||
                       RPSysCoreControllerMgr::isDpdCtrlEnable(mPauseSeChan);

        if (startSe) {
            startSystemSeWithRemote(mpPauseSeNameRemote, mPauseSePlayerFlag);
            startSystemSe(mpPauseSeName);

            mIsPauseSe = false;
        }
    }

    if (getPlayer().IsAvailable()) {
        RPSndObjMgr::update();
        RPSndMoveParamMgr::update();

        if (mArcVolume.update()) {
            for (u32 i = 0; i < getPlayer().GetSoundPlayerCount(); i++) {
                getPlayer().GetSoundPlayer(i).SetVolume(mArcVolume.getValue());
            }
        }

        SimpleAudioMgr::calc();
    }

    RP_GET_INSTANCE(RPSndSpeakerMgr)->calc();
    mStaticMgr.calc();

    if (mFanfareLength > 0) {
        if (mHandleFanfare.IsAttachedSound()) {
            if (OS_TICKS_TO_MSEC(OSGetTick() - mFanfareStart) >=
                mFanfareLength) {

                mFanfareLength = 0;
            }
        } else {
            mFanfareLength = 0;
        }

        if (mFanfareLength == 0) {
            RPSysSceneCreator::EPackID pack =
                RP_GET_INSTANCE(RPSysProjectLocal)->getPack();

            if (pack == RPSysSceneCreator::EPackID_PartyPack) {
                setBgmVolume(1.0f, 80);
                setStreamVolume(1.0f, 80);
            } else if (pack == RPSysSceneCreator::EPackID_SportsPack) {
                setStreamVolume(1.0f, 72);
            } else if (pack == RPSysSceneCreator::EPackID_HealthPack) {
                setStreamVolume(1.0f, 72);
            }
        }
    }

    bool dvdErrorChange = false;
    s32 dvdStatus = DVDGetDriveStatus();

    switch (dvdStatus) {
    case DVD_STATE_NO_DISK:
    case DVD_STATE_WRONG_DISK_ID: {
        if (!mIsNewDvdError) {
            dvdErrorChange = true;
        }

        mIsNewDvdError = true;
        break;
    }

    case DVD_STATE_COVER_OPENED:
    default: {
        if (mIsNewDvdError) {
            dvdErrorChange = true;
        }

        mIsNewDvdError = false;
        break;
    }
    }

    if (dvdErrorChange) {
        if (mIsNewDvdError) {
            onDvdError();
        } else {
            exitDvdError();
        }
    }

    RPSndMoveParamMgr::update();

    if (mMenuPauseFadeInTimer > 0 && --mMenuPauseFadeInTimer == 0) {
        for (u32 i = 0; i < getPlayer().GetSoundPlayerCount(); i++) {
            // Ignore pause players so the buttons can still be heard
            u32 idx = getSoundArchive().ConvertLabelStringToPlayerId(
                "RP_COM_GAME_PLAYER_PAUSE");

            if (i != idx) {
                getPlayer().GetSoundPlayer(i).PauseAllSound(false,
                                                            EXIT_FADE_TIME);
            }
        }
    }
}

/**
 * @brief Configures the audio system for title scenes
 */
void RPSndAudioMgr::configureTitle() {
    if (mState == EState_MiniGame) {
        exitAudio();
    }

    if (mState != EState_Title) {
        setDefaultFx();
        setArcVolume(1.0f, 1);
        mState = EState_Title;
    }

    mPlayerNum = WPAD_MAX_CONTROLLERS;
    RP_GET_INSTANCE(RPSndSpeakerMgr)->reset();
}

/**
 * @brief Configures the audio system for scenes without BGM
 */
void RPSndAudioMgr::configureNoBgm() {
    for (u32 i = 0; i < getPlayer().GetSoundPlayerCount(); i++) {
        getPlayer().GetSoundPlayer(i).StopAllSound(0);
    }

    mState = EState_NoBgm;

    mPlayerNum = WPAD_MAX_CONTROLLERS;
    RP_GET_INSTANCE(RPSndSpeakerMgr)->reset();

    setArcVolume(1.0f, 1);
}

/**
 * @brief Configures the audio system for game scenes
 *
 * @param cameraNum 3D audio camera count
 */
void RPSndAudioMgr::configureMiniGame(s32 cameraNum) {
    if (mState == EState_Title || mState == EState_NoBgm) {
        exitAudio();
    }

    mState = EState_MiniGame;
    setCameraCount(cameraNum);

    mPlayerNum = WPAD_MAX_CONTROLLERS;
    RP_GET_INSTANCE(RPSndSpeakerMgr)->reset();
}

/**
 * @brief Fades out all audio in the specified number of frames
 *
 * @param frames Fade out length
 */
void RPSndAudioMgr::fadeOutAllSound(u16 frames) {
    RPSysSceneCreator::EPackID pack =
        RP_GET_INSTANCE(RPSysProjectLocal)->getPack();

    if (pack == RPSysSceneCreator::EPackID_MusicPack) {
        return;
    }

    if (pack == RPSysSceneCreator::EPackID_HealthPack) {
        return;
    }

    setArcVolume(0.0f, frames);
}

/**
 * @brief Applies the fade out for game Retry buttons
 */
void RPSndAudioMgr::setAutoFadeOnRetry() {
    for (u32 i = 0; i < getPlayer().GetSoundPlayerCount(); i++) {
        // Ignore pause players so the buttons can still be heard
        if (i == getSoundArchive().ConvertLabelStringToPlayerId(
                     "RP_COM_GAME_PLAYER_PAUSE")) {
            continue;
        }

        getPlayer().GetSoundPlayer(i).StopAllSound(RETRY_FADE_TIME);
    }
}

/**
 * @brief Prepares the audio system for a scene change
 */
void RPSndAudioMgr::changeScene() {
    exitAudio();
    mState = EState_Exited;
}

/**
 * @brief Resets the audio system configuration
 */
void RPSndAudioMgr::exitAudio() {
    for (u32 i = 0; i < getPlayer().GetSoundPlayerCount(); i++) {
        getPlayer().GetSoundPlayer(i).StopAllSound(0);
    }

    ArcPlayer::closeArchive();

    loadState(mSoundHeapLevel);
    saveState();

    TAudioSound3DMgrArg arg;
    arg.maxPrioReduction = 32;
    arg.interiorSize = 1.0f;
    arg.unitDistance = 1.0f;
    arg.maxVolumeDistance = 10000.0f;
    setParam3D(&arg);

    RP_GET_INSTANCE(RPSndSpeakerMgr)->exit();
    exitMenu();
    exitPause();

    mFanfareLength = 0;
    mIsPauseSe = false;
}

/**
 * @brief Attempts to restore the specified sound heap state
 *
 * @param id State ID
 * @return Success
 */
bool RPSndAudioMgr::loadState(s32 id) {
    nw4r::snd::SoundHeap* pHeap = &getSoundHeap();
    s32 level = pHeap->GetCurrentLevel();

    // Mostly EGG code, but prevents re-loading the current state?
    if (id > 0 && level > id) {
        pHeap->LoadState(id);
        return true;
    }

    return false;
}

/**
 * @brief Attempts to start the specified sound
 *
 * @param pHandle Sound handle
 * @param id Sound ID
 * @return Success
 */
bool RPSndAudioMgr::startSound(nw4r::snd::SoundHandle* pHandle, u32 id) {
    return getPlayer().StartSound(pHandle, id);
}

/**
 * @brief Attempts to start the specified sound
 *
 * @param pHandle Sound handle
 * @param id Sound ID
 * @return Success
 */
bool RPSndAudioMgr::startSound(nw4r::snd::SoundHandle* pHandle,
                               unsigned int id) {
    return getPlayer().StartSound(pHandle, id);
}

/**
 * @brief Attempts to start the specified sound
 *
 * @param pHandle Sound handle
 * @param pName Sound name
 * @return Success
 */
bool RPSndAudioMgr::startSound(nw4r::snd::SoundHandle* pHandle,
                               const char* pName) {
    u32 id = changeNameToIdRP(pName);
    return getPlayer().StartSound(pHandle, id);
}

/**
 * @brief Sets the volume of all sound players
 *
 * @param volume New volume
 * @param frames Interpolation time
 */
void RPSndAudioMgr::setArcVolume(f32 volume, u32 frames) {
    mArcVolume.moveValue(volume, frames);
}

/**
 * @brief Resets the volume of all sound players
 */
void RPSndAudioMgr::resetArcVolume() {
    setArcVolume(1.0f, 0);

    for (u32 i = 0; i < getPlayer().GetSoundPlayerCount(); i++) {
        getPlayer().GetSoundPlayer(i).SetVolume(1.0f);
    }
}

/**
 * @brief Sets the volume of the current BGM
 *
 * @param volume New volume
 * @param frames Interpolation time
 */
void RPSndAudioMgr::setBgmVolume(f32 volume, int frames) {
    mHandleBgm.SetVolume(volume, frames);
}

/**
 * @brief Sets the volume of the current stream
 *
 * @param volume New volume
 * @param frames Interpolation time
 */
void RPSndAudioMgr::setStreamVolume(f32 volume, int frames) {
    mHandleStream.SetVolume(volume, frames);
}

/**
 * @brief Gets the position of the current stream, in seconds
 */
u32 RPSndAudioMgr::getStreamPlaySecond() {
    if (mHandleStream.IsAttachedSound()) {
        return mStreamPlayTick / STREAM_TICKRATE;
    }

    return 0;
}

/**
 * @brief Attempts to start a cursor sound effect
 *
 * @param pName Sound name
 * @param rDpdPos Cursor DPD/IR position
 * @param pan Sound pan
 * @param playerFlag Player output line flag
 * @return Success
 */
bool RPSndAudioMgr::startPointCursorSe(const char* pName,
                                       const nw4r::math::VEC2& rDpdPos, f32 pan,
                                       u32 playerFlag) {
    bool success = startSound(&mHandleSystemSe, pName);

    if (success) {
        RPSndUtility::setHandleDpdPan(mHandleSystemSe, rDpdPos, pan);
        setRemote(playerFlag);
    }

    return success;
}

/**
 * @brief Attempts to start a pause sound effect
 *
 * @param pNameRemote Remote speaker sound name
 * @param pNameTV TV speaker sound name
 * @param waitForDpd Whether to wait until the controller reconnects
 * @param player Player whose remote speaker should be used
 */
void RPSndAudioMgr::startPauseSe(const char* pNameRemote, const char* pNameTV,
                                 bool waitForDpd, s32 player) {

    mpPauseSeNameRemote = pNameRemote;
    mPauseSeWaitForDpd = waitForDpd;
    mIsPauseSe = true;
    mpPauseSeName = pNameTV;

    s32 chan = EGG_GET_INSTANCE(EGG::CoreControllerMgr)
                   ->getNthController(player)
                   ->getChannelID();

    mPauseSePlayerFlag = 1 << player;
    mPauseSeChan = chan;

    RPSysCoreController* pControllerRP = static_cast<RPSysCoreController*>(
        EGG_GET_INSTANCE(EGG::CoreControllerMgr)->getNthController(player));

    mPauseSePrevDpdEnable = pControllerRP->isPrevDpdCtrlEnable();
    DAT_804bf648 = 0;
}

/**
 * @brief Applies the default audio effect configuration
 */
void RPSndAudioMgr::setDefaultFx() {
    RPSysSceneCreator::EPackID pack =
        RP_GET_INSTANCE(RPSysProjectLocal)->getPack();

    if (pack == RPSysSceneCreator::EPackID_PartyPack) {
        static const nw4r::snd::FxReverbHi::ReverbHiParam reverbHiParam = {
            0.03f, // preDelayTime
            1.5f,  // fusedTime
            0.0f,  // coloration
            0.1f,  // damping
            0.2f,  // crossTalk
            0.5f   // outGain
        };

        static const nw4r::snd::FxChorus::ChorusParam chorusParam = {
            5.0f, // delayTime
            1.0f, // depth
            0.6f  // rate
        };

        static const nw4r::snd::FxDelay::DelayParam delayParam = {
            40.0f, // delay
            0.0f,  // feedback
            0.6f   // outGain
        };

        setFxReverbHi(nw4r::snd::AUX_A, &reverbHiParam);
        setFxChorus(nw4r::snd::AUX_B, &chorusParam);
        setFxDelay(nw4r::snd::AUX_C, &delayParam);

    } else if (pack == RPSysSceneCreator::EPackID_SportsPack) {
        if (nw4r::snd::SoundSystem::GetOutputMode() ==
            nw4r::snd::OUTPUT_MODE_DPL2) {

            setFxReverbHiDpl2(nw4r::snd::AUX_A, getDefaultFxReverbHiDpl2());
        } else {
            setFxReverbHi(nw4r::snd::AUX_A, getDefaultFxReverbHi());
        }

        clearFx(nw4r::snd::AUX_B);
        clearFx(nw4r::snd::AUX_C);

    } else /* EPackID_HealthPack, EPackID_MusicPack */ {
        setFxReverbHi(nw4r::snd::AUX_A, getDefaultFxReverbHi());
        setFxChorus(nw4r::snd::AUX_B, getDefaultFxChorus());
        setFxDelay(nw4r::snd::AUX_C, getDefaultFxDelay());
    }
}

/**
 * @brief Attempts to load the specified sound group
 *
 * @param id Group ID
 * @param pHeap Sound heap to use for allocations
 * @param blockSize Read block size (zero tries to read it all at once)
 * @return Success
 */
bool RPSndAudioMgr::loadGroup(unsigned int id,
                              nw4r::snd::SoundHeap* /* pHeap */,
                              u32 /* blockSize */) {
    if (mStorage != SARC_STORAGE_DVD) {
        return true;
    }

    (void)mHeap.GetFreeSize(); // unused

    return getPlayer().LoadGroup(id, &getSoundHeap(), 0);
}

/**
 * @brief Attempts to load the specified sound group
 *
 * @param id Group ID
 * @param pHeap Sound heap to use for allocations
 * @param blockSize Read block size (zero tries to read it all at once)
 * @return Success
 */
bool RPSndAudioMgr::loadGroup(int id, nw4r::snd::SoundHeap* /* pHeap */,
                              u32 /* blockSize */) {
    if (mStorage != SARC_STORAGE_DVD) {
        return true;
    }

    (void)mHeap.GetFreeSize(); // unused

    return getPlayer().LoadGroup(id, &getSoundHeap(), 0);
}

/**
 * @brief Attempts to load the specified sound group
 *
 * @param pName Group name
 * @param pHeap Sound heap to use for allocations
 * @param blockSize Read block size (zero tries to read it all at once)
 * @return Success
 */
bool RPSndAudioMgr::loadGroup(const char* pName,
                              nw4r::snd::SoundHeap* /* pHeap */,
                              u32 /* blockSize */) {
    if (mStorage != SARC_STORAGE_DVD) {
        return true;
    }

    (void)mHeap.GetFreeSize(); // unused

    u32 id = getSoundArchive().ConvertLabelStringToGroupId(pName);
    return getPlayer().LoadGroup(id, &getSoundHeap(), 0);
}

/**
 * @brief Configures the specified remote speaker(s) for the current system
 * sound effect
 *
 * @param playerFlag Player output line flags
 */
void RPSndAudioMgr::setRemote(u32 playerFlag) {
    if (!mHandleSystemSe.IsAttachedSound()) {
        return;
    }

    u32 param = getSoundArchive().GetSoundUserParam(mHandleSystemSe.GetId());
    if (!(param & 0xFFFF0000)) {
        return;
    }

    // clang-format off
    f32 mainOut =   static_cast<f32>(param >> 16 & 0x7F) / WPAD_MAX_SPEAKER_VOLUME;
    f32 muteOut =   static_cast<f32>(param >> 8  & 0x7F) / WPAD_MAX_SPEAKER_VOLUME;
    f32 remoteOut = static_cast<f32>(param >> 24)        / WPAD_MAX_SPEAKER_VOLUME;
    // clang-format on

    RP_GET_INSTANCE(RPSndSpeakerMgr)
        ->setRemoteSend(&mHandleSystemSe, playerFlag, mainOut, remoteOut,
                        muteOut);
}

/**
 * @brief Prepares the audio system for entering the home button menu
 */
void RPSndAudioMgr::enterMenu() {
    if (mFlags == 0) {
        mMenuPauseFadeInTimer = 0;

        for (u32 i = 0; i < getPlayer().GetSoundPlayerCount(); i++) {
            // Ignore pause players so the buttons can still be heard
            if (i == getSoundArchive().ConvertLabelStringToPlayerId(
                         "RP_COM_GAME_PLAYER_PAUSE")) {
                continue;
            }

            getPlayer().GetSoundPlayer(i).PauseAllSound(true, mMenuPauseFrame);
        }
    }

    setFlag(EFlag_IsMenu);

    nw4r::snd::SoundSystem::ClearEffect(nw4r::snd::AUX_A, MENU_FX_CLEAR_TIME);
    nw4r::snd::SoundSystem::ClearEffect(nw4r::snd::AUX_B, MENU_FX_CLEAR_TIME);
    nw4r::snd::SoundSystem::ClearEffect(nw4r::snd::AUX_C, MENU_FX_CLEAR_TIME);

    RP_GET_INSTANCE(RPSndSpeakerMgr)->disconnectAll();
}

/**
 * @brief Prepares the audio system for returning from the home button menu
 */
void RPSndAudioMgr::exitMenu() {
    if (!testFlag(EFlag_IsMenu)) {
        return;
    }

    clearFlag(EFlag_IsMenu);

    if (mFlags == 0) {
        if (mMenuPauseFrame > 0) {
            for (u32 i = 0; i < getPlayer().GetSoundPlayerCount(); i++) {
                // Ignore pause players so the buttons can still be heard
                if (i == getSoundArchive().ConvertLabelStringToPlayerId(
                             "RP_COM_GAME_PLAYER_PAUSE")) {
                    continue;
                }

                getPlayer().GetSoundPlayer(i).PauseAllSound(false,
                                                            EXIT_FADE_TIME);
            }
        } else {
            mMenuPauseFadeInTimer = 1;
        }
    }

    // Re-apply original audio effect configuration
    if (mpSetFxCallback != NULL) {
        mpSetFxCallback();
    } else {
        setDefaultFx();
    }

    RP_GET_INSTANCE(RPSndSpeakerMgr)->updateMasterVolume();
    RP_GET_INSTANCE(RPSndSpeakerMgr)->connectAll();
}

/**
 * @brief Prepares the audio system for entering the pause menu
 */
void RPSndAudioMgr::enterPause() {
    if (testFlag(EFlag_IsPause)) {
        return;
    }

    if (mFlags == 0) {
        mMenuPauseFadeInTimer = 0;

        for (u32 i = 0; i < getPlayer().GetSoundPlayerCount(); i++) {
            // Ignore pause players so the buttons can still be heard
            if (i == getSoundArchive().ConvertLabelStringToPlayerId(
                         "RP_COM_GAME_PLAYER_PAUSE")) {
                continue;
            }

            getPlayer().GetSoundPlayer(i).PauseAllSound(true, mMenuPauseFrame);
        }
    }

    setFlag(EFlag_IsPause);
}

/**
 * @brief Prepares the audio system for returning from the pause menu
 */
void RPSndAudioMgr::exitPause() {
    if (!testFlag(EFlag_IsPause)) {
        return;
    }

    clearFlag(EFlag_IsPause);

    if (mFlags == 0) {
        if (mMenuPauseFrame > 0) {
            for (u32 i = 0; i < getPlayer().GetSoundPlayerCount(); i++) {
                // Ignore pause players so the buttons can still be heard
                if (i == getSoundArchive().ConvertLabelStringToPlayerId(
                             "RP_COM_GAME_PLAYER_PAUSE")) {
                    continue;
                }

                getPlayer().GetSoundPlayer(i).PauseAllSound(false, 0);
            }
        } else {
            mMenuPauseFadeInTimer = 1;
        }
    }
}

/**
 * @brief Pauses the audio system when a DVD error occurs
 */
void RPSndAudioMgr::onDvdError() {
    if (mFlags == 0) {
        for (u32 i = 0; i < getPlayer().GetSoundPlayerCount(); i++) {
            // Ignore pause players so the buttons can still be heard
            if (i == getSoundArchive().ConvertLabelStringToPlayerId(
                         "RP_COM_GAME_PLAYER_PAUSE")) {
                continue;
            }

            getPlayer().GetSoundPlayer(i).PauseAllSound(true, 0);
        }
    }

    setFlag(EFlag_IsDvdError);
}

/**
 * @brief Resumes the audio system after a DVD error
 */
void RPSndAudioMgr::exitDvdError() {
    clearFlag(EFlag_IsDvdError);

    if (mFlags == 0) {
        for (u32 i = 0; i < getPlayer().GetSoundPlayerCount(); i++) {
            // Ignore pause players so the buttons can still be heard
            if (i == getSoundArchive().ConvertLabelStringToPlayerId(
                         "RP_COM_GAME_PLAYER_PAUSE")) {
                continue;
            }

            getPlayer().GetSoundPlayer(i).PauseAllSound(false, 0);
        }
    }
}

/**
 * @brief Stops all sounds when exiting the scene from the pause menu
 */
void RPSndAudioMgr::stopAllSoundOnPauseOff() {
    for (u32 i = 0; i < getPlayer().GetSoundPlayerCount(); i++) {
        // Ignore pause players so the buttons can still be heard
        if (i == getSoundArchive().ConvertLabelStringToPlayerId(
                     "RP_COM_GAME_PLAYER_PAUSE")) {
            continue;
        }

        getPlayer().GetSoundPlayer(i).StopAllSound(0);
    }
}

/**
 * @brief Requests the audio system to shutdown
 *
 * @param frames Time to fade out the master volume
 */
void RPSndAudioMgr::shutdownSystem(int frames) {
    mShutDownStatusRP = SHUTDOWN_STATUS_QUEUED;
    nw4r::snd::SoundSystem::SetMasterVolume(0.0f, frames);
}

/**
 * @brief Requests the audio system to reset
 *
 * @param frames Time to fade out the archive volume
 */
void RPSndAudioMgr::resetSystem(int frames) {
    setArcVolume(0.0f, frames);
    mResetTimer = frames;
    RP_GET_INSTANCE(RPSndSpeakerMgr)->updateMasterVolume();
}

/**
 * @brief Attempts to start the specified fanfare sound effect
 *
 * @param id Sound ID
 * @return Success
 */
bool RPSndAudioMgr::startFanfare(u32 id) {
    const char* pName = getSoundArchive().GetSoundLabelString(id);
    return pName != NULL ? startFanfare(pName) : false;
}

/**
 * @brief Attempts to start the specified fanfare sound effect
 *
 * @param pName Sound name
 * @return Success
 */
bool RPSndAudioMgr::startFanfare(const char* pName) {
    if (mIsDisableFanfare) {
        return false;
    }

    bool success = startSound(&mHandleFanfare, pName);

    if (success) {
        mFanfareStart = OSGetTick();
        mFanfareLength = getFanfareLength(pName);

        RPSysSceneCreator::EPackID pack =
            RP_GET_INSTANCE(RPSysProjectLocal)->getPack();

        if (pack == RPSysSceneCreator::EPackID_PartyPack) {
            setBgmVolume(0.3f, 3);
            setStreamVolume(0.3f, 3);

        } else if (pack == RPSysSceneCreator::EPackID_SportsPack) {
            u32 param = getUserParam(getSoundArchive(), mHandleFanfare.GetId());

            // @bug Overwritten with zero?? Maybe intentional
#if !defined(BUG_FIX)
            param = 0;
#endif

            f32 volume = param / 127.0f;
            setStreamVolume(volume, 3);

        } else if (pack == RPSysSceneCreator::EPackID_HealthPack) {
            setStreamVolume(0.3f, 20);
        }
    }

    return success;
}

/**
 * @brief Gets the user parameters attached to the specified sound
 *
 * @param rArchive Sound archive
 * @param id Sound ID
 */
u32 RPSndAudioMgr::getUserParam(const nw4r::snd::SoundArchive& rArchive,
                                u32 id) {
    return rArchive.GetSoundUserParam(id);
}

/**
 * @brief Sets the output mode of the audio system
 *
 * @param confMode Sound mode from the SYSCONF
 */
void RPSndAudioMgr::setOutputMode(u8 confMode) {
    nw4r::snd::OutputMode outputMode = nw4r::snd::OUTPUT_MODE_STEREO;

    switch (confMode) {
    case SC_SND_MONO: {
        outputMode = nw4r::snd::OUTPUT_MODE_MONO;
        break;
    }

    case SC_SND_STEREO: {
        outputMode = nw4r::snd::OUTPUT_MODE_STEREO;
        break;
    }

    case SC_SND_SURROUND: {
        RPSysSceneCreator::EPackID pack =
            RP_GET_INSTANCE(RPSysProjectLocal)->getPack();

        if (pack == RPSysSceneCreator::EPackID_PartyPack ||
            pack == RPSysSceneCreator::EPackID_HealthPack) {

            outputMode = nw4r::snd::OUTPUT_MODE_STEREO;
        } else {
            outputMode = nw4r::snd::OUTPUT_MODE_DPL2;
        }
        break;
    }
    }

    nw4r::snd::SoundSystem::SetOutputMode(outputMode);

    if (RP_GET_INSTANCE(RPSysProjectLocal)->getPack() ==
        RPSysSceneCreator::EPackID_SportsPack) {

        s16 variable = 0;
        if (outputMode == nw4r::snd::OUTPUT_MODE_DPL2) {
            variable = 1;
        } else if (outputMode == nw4r::snd::OUTPUT_MODE_MONO) {
            variable = 2;
        }

        nw4r::snd::SeqSoundHandle::WriteGlobalVariable(0, variable);
    }
}
