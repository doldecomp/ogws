#include <Pack/RPAudio.h>
#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <homebuttonMiniLib.h>

#include <nw4r/ut.h>

#include <revolution/GX.h>
#include <revolution/VI.h>

#include <cstring>

RP_SINGLETON_IMPL_EX(RPSysHomeMenuMgr);

/******************************************************************************
 *
 * BanIcon
 *
 ******************************************************************************/

//! X-origin of the ban icon
#define BANICON_X 552.0f
//! Y-origin of the ban icon
#define BANICON_Y 388.0f

//! Width of the ban icon
#define BANICON_SIZE 28.0f

/**
 * @brief Constructor
 */
RPSysHomeMenuMgr::BanIcon::BanIcon()
    : mpTexture(NULL), mState(EState_Hide), mTimer(0), mAlpha(0) {}

/**
 * @brief Updates this icon's state
 */
void RPSysHomeMenuMgr::BanIcon::calc() {
    switch (mState) {
    case EState_Hide: {
        break;
    }

    case EState_FadeIn: {
        if (++mTimer < FADE_LENGTH) {
            mAlpha = mTimer * 255 / FADE_LENGTH;
        } else {
            mState = EState_Disp;
            mTimer = 0;
            mAlpha = 255;
        }
        break;
    }

    case EState_Disp: {
        if (++mTimer >= DISP_LENGTH) {
            mState = EState_FadeOut;
            mTimer = 0;
        }

        mAlpha = 255;
        break;
    }

    case EState_FadeOut: {
        if (++mTimer < FADE_LENGTH) {
            mAlpha = 255 - mTimer * 255 / FADE_LENGTH;
        } else {
            clear();
        }
        break;
    }
    }
}

/**
 * @brief Renders this icon's state
 */
void RPSysHomeMenuMgr::BanIcon::draw() {
    GXColor color;
    color.r = color.g = color.b = 255;
    color.a = mAlpha;

    RPGrpScreen screen;
    screen.SetCanvasMode(RPGrpScreen::CANVAS_CC);
    screen.SetNearZ(-10000.0f);
    screen.SetFarZ(10000.0f);
    screen.SetProjectionType(RPGrpScreen::PROJ_ORTHO);
    screen.SetProjectionGX();

    f32 x = BANICON_X;
    f32 y = BANICON_Y;

    f32 current = RPGrpScreen::GetSizeXMax();
    f32 standard = RPGrpScreen::GetSizeYMax(RPGrpScreen::TV_MODE_STD);

    nw4r::ut::Rect rect(                                //
        x * (current / standard) * 0.5f - BANICON_SIZE, //
        -y * 0.5f + BANICON_SIZE,                       //
        x * (current / standard),                       //
        y                                               //
    );

    screen.BeginDrawQuadTexture(false);

    screen.DrawQuadTexture(       //
        rect.left - BANICON_SIZE, //
        rect.top + BANICON_SIZE,  //
        rect.left + BANICON_SIZE, //
        rect.top - BANICON_SIZE,  //
        mpTexture,                //
        color                     //
    );
}

/******************************************************************************
 *
 * RPSysHomeMenuMgr
 *
 ******************************************************************************/

/**
 * @brief HOME Menu sound archive manager
 */
RPSndHomeMenuArcMgr* RPSysHomeMenuMgr::spHomeMenuArcMgr = NULL;

/**
 * @brief Sound archive heap size
 */
u32 RPSysHomeMenuMgr::sSoundHeapSize = 0x7D000;

/**
 * @brief HBM library sound callback
 *
 * @param event HBM event
 * @param arg Event argument
 * @return Whether this callback handled the playback for HBM
 */
BOOL RPSysHomeMenuMgr::soundCallback(int event, int arg) {
    switch (event) {
    case HBM_SOUND_PLAY: {
        spHomeMenuArcMgr->startSe(static_cast<u32>(arg));
        return TRUE;
    }

    default: {
        return FALSE;
    }
    }
}

/**
 * @brief Constructor
 *
 * @param pHeap Parent heap
 */
RPSysHomeMenuMgr::RPSysHomeMenuMgr(EGG::Heap* pHeap) : mpParentHeap(pHeap) {
    mIsInitialized = false;
    mIsDisabled = false;
    mIsStarting = false;

    mpBanIcon = new (pHeap) BanIcon();
    init();

    std::memset(&mHBMDataInfo, 0, sizeof(mHBMDataInfo));
    std::memset(&mHBMControllerData, 0, sizeof(mHBMControllerData));

    mpProjectLocal = RP_GET_INSTANCE(RPSysProjectLocal);

    mHBMDataInfo.layoutBuf = NULL;
    mHBMDataInfo.spkSeBuf = NULL;
    mHBMDataInfo.msgBuf = NULL;
    mHBMDataInfo.configBuf = NULL;
    mHBMDataInfo.mem = new (pHeap) u8[HBM_WORK_SIZE];
    mHBMDataInfo.sound_callback = soundCallback;
    mHBMDataInfo.backFlag = FALSE;
    mHBMDataInfo.region = SC_LANG_EN;
    mHBMDataInfo.cursor = FALSE;
    mHBMDataInfo.configBufSize = HBM_CONFIG_SIZE;
    mHBMDataInfo.memSize = HBM_WORK_SIZE;
    if (mpProjectLocal->getFrameRate() == RPSysProjectLocal::EFrameRate_50Hz) {
        mHBMDataInfo.frameDelta = 60.0f / 50.0f;
    } else {
        mHBMDataInfo.frameDelta = 60.0f / 60.0f;
    }
    mHBMDataInfo.pAllocator = NULL;
    mHBMDataInfo.adjust.x = 1.0f;
    mHBMDataInfo.adjust.y = 1.0f;

    std::memset(mHBMDataInfo.mem, 0, HBM_WORK_SIZE);

    spHomeMenuArcMgr = new (pHeap) RPSndHomeMenuArcMgr();
    spHomeMenuArcMgr->createSoundHeap(pHeap, sSoundHeapSize);
}

/**
 * @brief Destructor
 */
RPSysHomeMenuMgr::~RPSysHomeMenuMgr() {}

/**
 * @brief Initializes this manager's state
 */
void RPSysHomeMenuMgr::init() {
    mIsDisabled = false;
    mIsActive = false;
    mIsVisible = false;
    mIsSoftReset = false;

    mMenuState = EMenuState_End;
    mStateTimer = 0;

    VISetBlack(FALSE);
    disable(false);
    mpBanIcon->clear();
}

/**
 * @brief Initializes the HBM library
 */
void RPSysHomeMenuMgr::initHomeButtonInfo() {
    // TODO(kiwi) Inline?
    HBMDataInfo* pHBMDataInfo = &mHBMDataInfo;

    EGG::Archive* pCommonArchive =
        RP_GET_INSTANCE(RPSysResourceManager)->GetStaticCommonArchive();

    EGG::Archive* pLocalArchive =
        RP_GET_INSTANCE(RPSysResourceManager)->GetStaticLocalArchive();

    void* pIconTexture =
        RP_GET_INSTANCE(RPSysResourceManager)
            ->GetFileFromArchive(pCommonArchive, "/HomeMenu/homeBtnIcon.bti");

    mpBanIcon->setTexture(static_cast<EGG::ResTIMG*>(pIconTexture));

    switch (mpProjectLocal->getLanguage()) {
    case RPSysProjectLocal::EArea_France: {
        pHBMDataInfo->region = SC_LANG_FR;

        pHBMDataInfo->layoutBuf =
            RP_GET_INSTANCE(RPSysResourceManager)
                ->GetFileFromArchive(pLocalArchive,
                                     "/HomeMenu/homeBtn_FRA.arc");
        break;
    }

    case RPSysProjectLocal::EArea_Germany: {
        pHBMDataInfo->region = SC_LANG_DE;

        pHBMDataInfo->layoutBuf =
            RP_GET_INSTANCE(RPSysResourceManager)
                ->GetFileFromArchive(pLocalArchive,
                                     "/HomeMenu/homeBtn_GER.arc");
        break;
    }

    case RPSysProjectLocal::EArea_Italy: {
        pHBMDataInfo->region = SC_LANG_IT;

        pHBMDataInfo->layoutBuf =
            RP_GET_INSTANCE(RPSysResourceManager)
                ->GetFileFromArchive(pLocalArchive,
                                     "/HomeMenu/homeBtn_ITA.arc");
        break;
    }

    case RPSysProjectLocal::EArea_Spain: {
        pHBMDataInfo->region = SC_LANG_SP;

        pHBMDataInfo->layoutBuf =
            RP_GET_INSTANCE(RPSysResourceManager)
                ->GetFileFromArchive(pLocalArchive,
                                     "/HomeMenu/homeBtn_SPA.arc");
        break;
    }

    case RPSysProjectLocal::EArea_Netherlands: {
        pHBMDataInfo->region = SC_LANG_NL;

        pHBMDataInfo->layoutBuf =
            RP_GET_INSTANCE(RPSysResourceManager)
                ->GetFileFromArchive(pLocalArchive,
                                     "/HomeMenu/homeBtn_NED.arc");
        break;
    }

    case RPSysProjectLocal::EArea_Japan: {
        pHBMDataInfo->region = SC_LANG_JP;

        pHBMDataInfo->layoutBuf =
            RP_GET_INSTANCE(RPSysResourceManager)
                ->GetFileFromArchive(pLocalArchive, "/HomeMenu/homeBtn.arc");
        break;
    }

    default: {
        pHBMDataInfo->region = SC_LANG_EN;

        pHBMDataInfo->layoutBuf =
            RP_GET_INSTANCE(RPSysResourceManager)
                ->GetFileFromArchive(pLocalArchive,
                                     "/HomeMenu/homeBtn_ENG.arc");
        break;
    }
    }

    pHBMDataInfo->spkSeBuf =
        RP_GET_INSTANCE(RPSysResourceManager)
            ->GetFileFromArchive(pCommonArchive, "/HomeMenu/SpeakerSe.arc");

    pHBMDataInfo->msgBuf =
        RP_GET_INSTANCE(RPSysResourceManager)
            ->GetFileFromArchive(pCommonArchive, "/HomeMenu/home_nosave.csv");

    pHBMDataInfo->configBuf =
        RP_GET_INSTANCE(RPSysResourceManager)
            ->GetFileFromArchive(pCommonArchive, "/HomeMenu/config.txt");

    HBMCreate(pHBMDataInfo);
    HBMSetAdjustFlag(TRUE);

    void* pSoundArchive =
        RP_GET_INSTANCE(RPSysResourceManager)
            ->GetFileFromArchive(pCommonArchive,
                                 "/HomeMenu/HomeButtonSe.brsar");

    spHomeMenuArcMgr->setupArchive(pSoundArchive);

    if (mpProjectLocal->getPack() == RPSysSceneCreator::EPackID_HealthPack) {
        HBMSetBlackOutColor(255, 255, 255);
    }

    mIsInitialized = true;
}

/**
 * @brief Checks whether the HOME Menu should be opened
 */
void RPSysHomeMenuMgr::checkMenuStart() {
    bool pressedBtn = false;

    for (int index = 0; index < RP_MAX_CONTROLLERS; index++) {
        if (RP_GET_CORE_CTRL(index)->getCoreStatus()->getTrigger() &
            EGG::cCORE_BUTTON_HOME) {

            pressedBtn = true;
            break;
        }
    }

    if (!pressedBtn && !mIsStarting) {
        return;
    }

    if (RP_GET_INSTANCE(RPSysSceneMgr)
            ->getCurrentSceneRP()
            ->isSceneChangeEnable()) {

        if (!mIsDisabled &&
            !RP_GET_INSTANCE(RPSysDvdStatus)->isErrorOccured()) {

            mMenuState = EMenuState_Start;
            mStateTimer = 0;
            mIsActive = true;
            mIsVisible = false;

            RP_GET_INSTANCE(RPSndAudioMgr)->enterMenu();

        } else {
            mpBanIcon->switchOn();
        }

        mIsStarting = false;

    } else if (RP_GET_INSTANCE(RPSysDvdStatus)->isErrorOccured()) {
        mpBanIcon->switchOn();

    } else {
        mIsStarting = true;
    }
}

/**
 * @brief Checks whether the HOME Menu should be closed
 */
void RPSysHomeMenuMgr::checkMenuEnd() {
    mIsVisible = true;

    switch (HBMCalc(&mHBMControllerData)) {
    case HBM_SELECT_BTN2: {
        mMenuState = EMenuState_Reset;
        RP_GET_INSTANCE(RPSysSceneMgr)->softReset(true);
        RP_GET_INSTANCE(RPSndAudioMgr)->stopAllSoundOnPauseOff();
        break;
    }

    case HBM_SELECT_BTN1: {
        RP_GET_INSTANCE(RPSysSceneMgr)->returnToMenu(true);

        mMenuState = EMenuState_End;
        mIsActive = false;
        mIsVisible = false;

        RP_GET_INSTANCE(RPSndAudioMgr)->exitMenu();

        RPSysCoreController::popDpdCtrlStackAll();
        RPSysCoreController::popKPADParamStackAll();

        // Avoid firing pauseCallback if it would be untrue
        if (!RP_GET_INSTANCE(RPSysPauseMgr)->isPause()) {
            RP_GET_INSTANCE(RPSysSceneMgr)
                ->getCurrentSceneRP()
                ->pauseCallBack(false);
        }
        break;
    }

    case HBM_SELECT_HOMEBTN: {
        mMenuState = EMenuState_End;
        mIsActive = false;
        mIsVisible = false;

        RP_GET_INSTANCE(RPSndAudioMgr)->exitMenu();

        RPSysCoreController::popDpdCtrlStackAll();
        RPSysCoreController::popKPADParamStackAll();

        // Avoid firing pauseCallback if it would be untrue
        if (!RP_GET_INSTANCE(RPSysPauseMgr)->isPause()) {
            RP_GET_INSTANCE(RPSysSceneMgr)
                ->getCurrentSceneRP()
                ->pauseCallBack(false);
        }
        break;
    }

    case HBM_SELECT_NULL:
    default: {
        break;
    }
    }
}

/**
 * @brief Performs a soft reset
 *
 * @return Whether HBM will perform the reset
 */
bool RPSysHomeMenuMgr::softReset() {
    if (mIsActive && !mIsSoftReset) {
        HBMStartBlackOut();
        mIsSoftReset = true;
    }

    mIsStarting = false;
    return mIsActive;
}

/**
 * @brief Updates this manager's state
 */
void RPSysHomeMenuMgr::update() {
    f32 current = RPGrpScreen::GetSizeXMax();
    f32 standard = RPGrpScreen::GetSizeXMax(RPGrpScreen::TV_MODE_STD);

    mHBMDataInfo.adjust.x = current / standard;
    mHBMDataInfo.adjust.y = 1.0f;

    if (mIsActive) {
        for (s32 chan = 0; chan < KPAD_MAX_CONTROLLERS; chan++) {
            RPSysCoreController* pController =
                RP_GET_INSTANCE(RPSysCoreControllerMgr)->findController(chan);

            if (pController != NULL && pController->isCoreBaseDevice()) {
                switch (mKPADStatus[chan].wpad_err) {
                case WPAD_ERR_COMMUNICATION_ERROR: {
                    std::memset(&mKPADStatus[chan], 0,
                                sizeof(mKPADStatus[chan]));

                    mKPADStatus[chan].horizon =
                        pController->getCoreStatus()->horizon;
                    break;
                }

                default: {
                    mKPADStatus[chan] = *pController->getCoreStatus();
                    break;
                }
                }

                mHBMControllerData.wiiCon[chan].kpad = &mKPADStatus[chan];
                mHBMControllerData.wiiCon[chan].pos = mKPADStatus[chan].pos;

            } else {
                mHBMControllerData.wiiCon[chan].kpad = NULL;
                mHBMControllerData.wiiCon[chan].pos.x = 10000.0f;
                mHBMControllerData.wiiCon[chan].pos.y = 10000.0f;
            }
        }
    }

    if (mIsInitialized) {
        switch (mMenuState) {
        case EMenuState_End: {
            checkMenuStart();
            break;
        }

        case EMenuState_Start: {
            mStateTimer++;

            if (!RP_GET_INSTANCE(RPSndSpeakerMgr)->isDisconnectAllFinished()) {
                break;
            }

            mMenuState = EMenuState_Open;
            mStateTimer = 0;

            HBMInit();

            RPSysCoreController::stopMotorAll();
            RPSysCoreController::pushDpdCtrlStackAll(true);
            RPSysCoreController::pushKPADParamStackAll();

            // Avoid firing pauseCallback if it would be untrue
            if (!RP_GET_INSTANCE(RPSysPauseMgr)->isPause()) {
                RP_GET_INSTANCE(RPSysSceneMgr)
                    ->getCurrentSceneRP()
                    ->pauseCallBack(true);
            }
            break;
        }

        case EMenuState_Open: {
            checkMenuEnd();
            break;
        }

        case EMenuState_Reset: {
            mMenuState = EMenuState_End;
            mIsActive = false;
            mIsVisible = false;

            RP_GET_INSTANCE(RPSndAudioMgr)->exitMenu();

            RPSysCoreController::popDpdCtrlStackAll();
            RPSysCoreController::popKPADParamStackAll();

            // Avoid firing pauseCallback if it would be untrue
            if (!RP_GET_INSTANCE(RPSysPauseMgr)->isPause()) {
                RP_GET_INSTANCE(RPSysSceneMgr)
                    ->getCurrentSceneRP()
                    ->pauseCallBack(false);
            }
            break;
        }

        default: {
            break;
        }
        }

        mpBanIcon->calc();
        spHomeMenuArcMgr->calc();
    }
}

/**
 * @brief Renders the HOME Menu if it is visible
 */
void RPSysHomeMenuMgr::draw() {
    if (!mIsInitialized) {
        return;
    }

    if (isActive() && mIsVisible) {
        HBMDraw();
    }
}

/**
 * @brief Renders the ban icon if it is visible
 */
void RPSysHomeMenuMgr::drawBanIcon() {
    if (!mIsInitialized) {
        return;
    }

    if (mpBanIcon->isDisp()) {
        mpBanIcon->draw();
    }
}
