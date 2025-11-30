#include <homeButtonMiniLib.h>
#include <homeButtonMiniLib/HBMGUIManager.h>
#include <homeButtonMiniLib/HBMRes.h>
#include <homeButtonMiniLib/HBMTypes.h>

#include <nw4r/lyt.h>
#include <nw4r/ut.h>

#include <revolution/AX.h>
#include <revolution/AXFX.h>
#include <revolution/GX.h>
#include <revolution/OS.h>
#include <revolution/VI.h>
#include <revolution/WPAD.h>
#include <revolution/version.h>

#include <cstring>

/******************************************************************************
 *
 * API
 *
 ******************************************************************************/

RVL_LIB_VERSION(HBM, "May  7 2007", "18:28:39", "0x4199_60726");

enum HBMAllocatorType {
    HBM_ALLOCATOR_APPLI,
    HBM_ALLOCATOR_LOCAL,
    HBM_ALLOCATOR_NW4R,
};

static MEMAllocator sAllocator;
static MEMAllocator* spAllocator = &sAllocator;

DECOMP_FORCEACTIVE(HBMBase_cpp, (GXColor){0, 0, 0, 255});

void* HBMAllocMem(u32 size) {
    return MEMAllocFromAllocator(spAllocator, size);
}

void HBMFreeMem(void* mem) {
    MEMFreeToAllocator(spAllocator, mem);
}

static HBMAllocatorType getAllocatorType(const HBMDataInfo* pHBInfo) {
    if (pHBInfo->pAllocator != NULL) {
        return HBM_ALLOCATOR_APPLI;
    }

    if (pHBInfo->mem != NULL) {
        return HBM_ALLOCATOR_LOCAL;
    }

    return HBM_ALLOCATOR_NW4R;
}

void HBMCreate(const HBMDataInfo* pHBInfo) {
    MEMiHeapHead* hExpHeap;

    if (getAllocatorType(pHBInfo) == HBM_ALLOCATOR_LOCAL) {
        hExpHeap = MEMCreateExpHeap(pHBInfo->mem, pHBInfo->memSize);
        MEMInitAllocatorForExpHeap(&sAllocator, hExpHeap, 32);
        spAllocator = &sAllocator;
    }

    switch (getAllocatorType(pHBInfo)) {
    case HBM_ALLOCATOR_APPLI: {
        nw4r::lyt::Layout::SetAllocator(pHBInfo->pAllocator);
        spAllocator = pHBInfo->pAllocator;
        break;
    }

    case HBM_ALLOCATOR_LOCAL: {
        nw4r::lyt::Layout::SetAllocator(spAllocator);
        break;
    }

    case HBM_ALLOCATOR_NW4R: {
        spAllocator = nw4r::lyt::Layout::GetAllocator();
        break;
    }
    }

    homebutton::HomeButton::createInstance(pHBInfo);
    homebutton::HomeButton::getInstance()->create();
}

void HBMInit() {
    OSRegisterVersion(__HBMVersion);
    homebutton::HomeButton::getInstance()->init();
}

HBMSelectBtnNum HBMCalc(const HBMControllerData* pController) {
    homebutton::HomeButton::getInstance()->calc(pController);
    return homebutton::HomeButton::getInstance()->getSelectBtnNum();
}

void HBMDraw() {
    homebutton::HomeButton::getInstance()->draw();
}

HBMSelectBtnNum HBMGetSelectBtnNum() {
    return homebutton::HomeButton::getInstance()->getSelectBtnNum();
}

void HBMSetAdjustFlag(BOOL flag) {
    homebutton::HomeButton::getInstance()->setAdjustFlag(flag);
}

void HBMStartBlackOut() {
    homebutton::HomeButton::getInstance()->startBlackOut();
}

void HBMSetBlackOutColor(u8 r, u8 g, u8 b) {
    homebutton::HomeButton::getInstance()->setBlackOutColor(r, g, b);
}

BOOL HBMIsReassignedControllers() {
    return homebutton::HomeButton::getInstance()->getReassignedFlag();
}

/******************************************************************************
 *
 * Implementation details
 *
 ******************************************************************************/

#define HBM_MAX_VOLUME 10

namespace homebutton {

// Prototypes
static void SimpleSyncCallback(s32 result, s32 num);

struct AnmControllerTable {
    int pane; // at 0x0
    int anm;  // at 0x4
};

#define X(Y, Z) {res::eGr_##Y, res::eAnim_##Z},
static const AnmControllerTable scAnmTable[] = {HBM_ANIM_TABLE};
#undef X

#define X(Y, Z) {res::eGroup_##Y, res::eGroupAnim_##Z},
static const AnmControllerTable scGroupAnmTable[] = {HBM_GROUP_ANIM_TABLE};
#undef X

HomeButton* HomeButton::spHomeButtonObj = NULL;
OSMutex HomeButton::sMutex;

const int HomeButton::scReConnectTime = 3600;
const int HomeButton::scReConnectTime2 = 3570;
const int HomeButton::scPadDrawWaitTime = 5;
const int HomeButton::scGetPadInfoTime = 100;
const int HomeButton::scForcusSEWaitTime = 2;
const f32 HomeButton::scOnPaneVibTime = 3.0f;
const f32 HomeButton::scOnPaneVibWaitTime = 9.0f;
const int HomeButton::scWaitStopMotorTime = 30;
const int HomeButton::scWaitDisConnectTime = 180;

#define X(Y) #Y ".brlyt",
const char* HomeButton::scCursorLytName[res::eCursorLyt_Max] = {
    HBM_CURSOR_LYT_NAME_LIST //
};
#undef X

const char* HomeButton::scCursorPaneName = HBM_CURSOR_PANE_NAME;
const char* HomeButton::scCursorRotPaneName = HBM_CURSOR_ROT_PANE_NAME;
const char* HomeButton::scCursorSRotPaneName = HBM_CURSOR_SROT_PANE_NAME;

#define X(Y) #Y,
const char* HomeButton::scBtnName[res::eBtn_Max] = {HBM_BTN_NAME_LIST};
#undef X

#define X(Y) #Y,
const char* HomeButton::scTxtName[res::eTxt_Max] = {HBM_TXT_NAME_LIST};
#undef X

#define X(Y) #Y,
const char* HomeButton::scGrName[res::eGr_Max] = {HBM_GR_NAME_LIST};
#undef X

#define X(Y) "_" #Y ".brlan",
const char* HomeButton::scAnimName[res::eAnim_Max] = {HBM_ANIM_NAME_LIST};
#undef X

#define X(Y) "_" #Y ".brlan",
const char* HomeButton::scPairGroupAnimName[res::ePairGroup_Max] = {
    HBM_PAIR_GROUP_NAME_LIST};
#undef X

#define X(Y) #Y,
const char* HomeButton::scPairGroupName[res::ePairGroup_Max] = {
    HBM_PAIR_GROUP_NAME_LIST};
#undef X

#define X(Y) "_" #Y ".brlan",
const char* HomeButton::scGroupAnimName[res::eGroupAnim_Max] = {
    HBM_GROUP_ANIM_NAME_LIST};
#undef X

#define X(Y) #Y,
const char* HomeButton::scGroupName[res::eGroup_Max] = {HBM_GROUP_NAME_LIST};
#undef X

#define X(Y) #Y,
const char* HomeButton::scFuncPaneName[res::eFuncPane_Max] = {
    HBM_FUNC_PANE_NAME_LIST};
#undef X

#define X(Y) #Y,
const char* HomeButton::scFuncTouchPaneName[res::eFuncTouchPane_Max] = {
    HBM_FUNC_TOUCH_PANE_NAME_LIST};
#undef X

#define X(Y) #Y,
const char* HomeButton::scFuncTextPaneName[res::eFuncTextPane_Max] = {
    HBM_FUNC_TEXT_PANE_NAME_LIST};
#undef X

#define X(Y) #Y,
const char* HomeButton::scBatteryPaneName //
    [WPAD_MAX_CONTROLLERS][res::eBatteryPane_Max] = {
        HBM_BATTERY_PANE_NAME_LIST(00_) //
        HBM_BATTERY_PANE_NAME_LIST(01_) //
        HBM_BATTERY_PANE_NAME_LIST(02_) //
        HBM_BATTERY_PANE_NAME_LIST(03_) //
};
#undef X

HomeButton::HomeButton(const HBMDataInfo* pHBInfo)
    : mpHBInfo(pHBInfo), mpLayout(NULL), mpPaneManager(NULL), mFader(30) {

    mState = 2;
    mSelectBtnNum = HBM_SELECT_NULL;
    mSelectAnmNum = -1;
    mMsgCount = 0;
    mSequence = eSeq_Normal;
    mForcusSEWaitTime = 0;
    mLetterFlag = false;
    mBar0AnmRev = 0;
    mBar1AnmRev = 0;
    mBar0AnmRevHold = 0;
    mBar1AnmRevHold = 0;
    mAdjustFlag = false;
    mReassignedFlag = false;

    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        OSCreateAlarm(&mAlarm[i]);
        OSCreateAlarm(&mSpeakerAlarm[i]);
    }

    OSCreateAlarm(&mSimpleSyncAlarm);
    OSInitMutex(&sMutex);

    mpSoundArchivePlayer = NULL;
    mpDvdSoundArchive = NULL;
    mpMemorySoundArchive = NULL;
    mpNandSoundArchive = NULL;
    mpSoundHeap = NULL;
    mpSoundHandle = NULL;
}

void HomeButton::createInstance(const HBMDataInfo* pHBInfo) {
    if (void* pMem = HBMAllocMem(sizeof(HomeButton))) {
        spHomeButtonObj = new (pMem) HomeButton(pHBInfo);
    }
}

void HomeButton::deleteInstance() {
    spHomeButtonObj->~HomeButton();
    HBMFreeMem(spHomeButtonObj);
    spHomeButtonObj = NULL;
}

HomeButton* HomeButton::getInstance() {
    return spHomeButtonObj;
}

void HomeButton::create() {
    int i;
    char anmNameBuf[64];

    mInitFlag = false;
    mForceSttInitProcFlag = false;
    mForceSttFadeInProcFlag = false;

    set_config();
    set_text();

    if (void* pMem = HBMAllocMem(sizeof(nw4r::lyt::ArcResourceAccessor))) {
        mpResAccessor = new (pMem) nw4r::lyt::ArcResourceAccessor();
    }

    mpResAccessor->Attach(mpHBInfo->layoutBuf, "arc");

    if (!mpHBInfo->cursor) {
        for (i = 0; i < res::eCursorLyt_Max; i++) {
            if (void* pMem = HBMAllocMem(sizeof(nw4r::lyt::Layout))) {
                mpCursorLayout[i] = new (pMem) nw4r::lyt::Layout();
            }

            void* lytRes = mpResAccessor->GetResource(
                nw4r::lyt::ArcResourceAccessor::RES_TYPE_NAME,
                scCursorLytName[i], NULL);

            mpCursorLayout[i]->Build(lytRes, mpResAccessor);
        }
    }

    if (void* pMem = HBMAllocMem(sizeof(nw4r::lyt::Layout))) {
        mpLayout = new (pMem) nw4r::lyt::Layout();
    }

    {
        void* lytRes = mpResAccessor->GetResource(
            nw4r::lyt::ArcResourceAccessor::RES_TYPE_NAME, mpLayoutName, NULL);

        mpLayout->Build(lytRes, mpResAccessor);
    }

    nw4r::lyt::Pane* proot = mpLayout->GetRootPane();

    NW4R_UT_LINKLIST_FOREACH(it, proot->GetChildList(), {
        if (std::strcmp(it->GetName(), "back_01") == 0) {
            it->SetScale(nw4r::math::VEC2(1.2f, 1.2f));
            break;
        }
    })

    for (i = 0; i < mAnmNum; i++) {
        std::strcpy(anmNameBuf, mpAnmName);
        std::strcat(anmNameBuf, scAnimName[scAnmTable[i].anm]);

        void* lpaRes = mpResAccessor->GetResource(
            nw4r::lyt::ArcResourceAccessor::RES_TYPE_NAME, anmNameBuf, NULL);

        if (void* pMem = HBMAllocMem(sizeof(GroupAnmController))) {
            mpAnmController[i] = new (pMem) GroupAnmController();
        }

        mpAnmController[i]->mpAnimGroup =
            mpLayout->CreateAnimTransform(lpaRes, mpResAccessor);

        mpAnmController[i]->mpGroup =
            mpLayout->GetGroupContainer()->FindGroupByName(
                scGrName[scAnmTable[i].pane]);

        nw4r::lyt::detail::PaneLinkList& list =
            mpAnmController[i]->mpGroup->GetPaneList();

        NW4R_UT_LINKLIST_FOREACH(it, list, {
            it->mTarget->BindAnimation(mpAnmController[i]->mpAnimGroup, false);
        })

        mpAnmController[i]->init(FrameController::eAnmType_Forward,
                                 mpAnmController[i]->mpAnimGroup->GetFrameMax(),
                                 0.0f, mpHBInfo->frameDelta);
    }

    for (i = 0; i < res::eGrAnimator_Max; i++) {
        std::strcpy(anmNameBuf, mpAnmName);
        std::strcat(anmNameBuf, scGroupAnimName[scGroupAnmTable[i].anm]);

        void* lpaRes = mpResAccessor->GetResource(
            nw4r::lyt::ArcResourceAccessor::RES_TYPE_NAME, anmNameBuf, NULL);

        if (void* pMem = HBMAllocMem(sizeof(GroupAnmController))) {
            mpGroupAnmController[i] = new (pMem) GroupAnmController();
        }

        mpGroupAnmController[i]->mpAnimGroup =
            mpLayout->CreateAnimTransform(lpaRes, mpResAccessor);

        mpGroupAnmController[i]->mpGroup =
            mpLayout->GetGroupContainer()->FindGroupByName(
                scGroupName[scGroupAnmTable[i].pane]);

        nw4r::lyt::detail::PaneLinkList& list =
            mpGroupAnmController[i]->mpGroup->GetPaneList();

        NW4R_UT_LINKLIST_FOREACH(it, list, {
             it->mTarget->BindAnimation(mpGroupAnmController[i]->mpAnimGroup,
                                       false);
        })

        mpGroupAnmController[i]->init(
            FrameController::eAnmType_Forward,
            mpGroupAnmController[i]->mpAnimGroup->GetFrameMax(), 0.0f,
            mpHBInfo->frameDelta);
    }

    for (i = 0; i < res::ePairGroup_Max; i++) {
        std::strcpy(anmNameBuf, mpAnmName);
        std::strcat(anmNameBuf, scPairGroupAnimName[i]);

        void* lpaRes = mpResAccessor->GetResource(
            nw4r::lyt::ArcResourceAccessor::RES_TYPE_NAME, anmNameBuf, NULL);

        if (void* pMem = HBMAllocMem(sizeof(GroupAnmController))) {
            mpPairGroupAnmController[i] = new (pMem) GroupAnmController();
        }

        mpPairGroupAnmController[i]->mpAnimGroup =
            mpLayout->CreateAnimTransform(lpaRes, mpResAccessor);

        mpPairGroupAnmController[i]->mpGroup =
            mpLayout->GetGroupContainer()->FindGroupByName(scPairGroupName[i]);

        nw4r::lyt::detail::PaneLinkList& list =
            mpPairGroupAnmController[i]->mpGroup->GetPaneList();

        NW4R_UT_LINKLIST_FOREACH(it, list, {
            it->mTarget->BindAnimation(mpPairGroupAnmController[i]->mpAnimGroup,
                false);
        })

        mpPairGroupAnmController[i]->init(
            FrameController::eAnmType_Forward,
            mpPairGroupAnmController[i]->mpAnimGroup->GetFrameMax(), 0.0f,
            mpHBInfo->frameDelta);
    }

    if (void* pMem = HBMAllocMem(sizeof(HomeButtonEventHandler))) {
        mpHomeButtonEventHandler = new (pMem) HomeButtonEventHandler(this);
    }

    if (void* pMem = HBMAllocMem(sizeof(gui::PaneManager))) {
        mpPaneManager = new (pMem)
            gui::PaneManager(mpHomeButtonEventHandler, NULL, spAllocator);
    }

    mpPaneManager->createLayoutScene(*mpLayout);
    mpPaneManager->setAllComponentTriggerTarget(false);

    for (i = 0; i < mButtonNum; i++) {
        nw4r::lyt::Pane* pTouchPane =
            mpLayout->GetRootPane()->FindPaneByName(scBtnName[i], true);

        mpPaneManager->getPaneComponentByPane(pTouchPane)
            ->setTriggerTarget(true);
    }

    if (void* pMem = HBMAllocMem(sizeof(RemoteSpk))) {
        mpRemoteSpk = new (pMem) RemoteSpk(mpHBInfo->spkSeBuf);
    }

    for (i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        if (void* pMem = HBMAllocMem(sizeof(Controller))) {
            mpController[i] = new (pMem) Controller(i, mpRemoteSpk);
        }
    }

    mpPaneManager->setDrawInfo(&mDrawInfo);

    nw4r::math::VEC2 ad_v(1.0f / mpHBInfo->adjust.x, 1.0f);
    mDrawInfo.SetLocationAdjustScale(ad_v);
    mDrawInfo.SetLocationAdjust(mAdjustFlag);

    nw4r::math::MTX34 viewMtx;
    nw4r::math::MTX34Identity(&viewMtx);
    mDrawInfo.SetViewMtx(viewMtx);

    init_msg();
}

static u32 get_comma_length(char* pBuf) {
    u32 len;

    for (len = 0; pBuf[len] != '\0'; len++) {
        if (pBuf[len] == ',') {
            break;
        }
    }

    return len;
}

void HomeButton::set_config() {
    int i = 0, j = 0;

    char* pConfig = static_cast<char*>(mpHBInfo->configBuf);
    char* pEnd =
        static_cast<char*>(mpHBInfo->configBuf) + mpHBInfo->configBufSize;

    u32 len = get_comma_length(pConfig);
    mpLayoutName = static_cast<char*>(HBMAllocMem(len + 1));

    std::strncpy(mpLayoutName, pConfig, len);
    mpLayoutName[len] = '\0';

    pConfig += len + 1;

    len = get_comma_length(pConfig);
    mpAnmName = static_cast<char*>(HBMAllocMem(len + 1));

    std::strncpy(mpAnmName, pConfig, len);
    mpAnmName[len] = '\0';

    pConfig += len;

    // comma operator generates a temporary
    i = 0;
    j = 0;
    for (; pConfig[i] != '\0' && &pConfig[i] < pEnd; i++) {
        if (pConfig[i] == ',') {
            if (pConfig[i + 1] == '1') {
                mDialogFlag[j] = true;
            } else {
                mDialogFlag[j] = false;
            }

            j++;
        }
    }

    mButtonNum = j;
    mAnmNum = mButtonNum * 3;
}

void HomeButton::set_text() {
    int i = 0, j = 0, k = 0;
    bool flag = false; // more accurately insideStringFlag
    wchar_t* message = static_cast<wchar_t*>(mpHBInfo->msgBuf);

    for (; message[i] != '\0'; i++) {
        if (message[i] == L'\"') {
            if (!flag) {
                flag = true;

                mpText[j][k] = &message[i + 1];
                j++;

                if (j == 7) {
                    j = 0;
                    k++;
                }
            } else {
                flag = false;
            }
        }
    }
}

void HomeButton::init() {
    int i;

    if (mInitFlag) {
        return;
    }

    mInitFlag = true;

    mForceSttInitProcFlag = false;
    mForceSttFadeInProcFlag = false;
    mStartBlackOutFlag = false;
    mForceStopSyncFlag = false;
    mSimpleSyncCallback = NULL;

    iReConnectTime =
        scReConnectTime / getInstance()->getHBMDataInfo()->frameDelta;
    iReConnectTime2 =
        scReConnectTime2 / getInstance()->getHBMDataInfo()->frameDelta;

    if (mSelectBtnNum != HBM_SELECT_BTN3) {
        mEndInitSoundFlag = false;
    }

    for (i = 0; i < (int)ARRAY_SIZE(mPaneCounter); i++) {
        mPaneCounter[i] = 0;
    }

    mState = 0;
    mSequence = eSeq_Normal;
    mReassignedFlag = false;

    mpPaneManager->init();
    updateTrigPane();

    nw4r::ut::Rect layoutRect = mpLayout->GetLayoutRect();
    mDrawInfo.SetViewRect(layoutRect);
    mpLayout->CalculateMtx(mDrawInfo);

    for (i = 0; i < (int)ARRAY_SIZE(mpCursorLayout); i++) {
        mpCursorLayout[i]->CalculateMtx(mDrawInfo);
    }

    reset_guiManager(-1);

    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        mPadDrawTime[i] = 0;

        mpController[i]->setInValidPos();
        mpController[i]->clrKpadButton();
        mpController[i]->disconnect();
        mpController[i]->clrBatteryFlag();
        mpController[i]->initCallback();
        mpController[i]->initSound();

        mOnPaneVibFrame[i] = 0.0f;
        mOnPaneVibWaitFrame[i] = 0.0f;
    }

    mpLayout->GetRootPane()
        ->FindPaneByName(scFuncPaneName[res::eFuncPane_let_icn_00], true)
        ->SetVisible(false);

    for (i = res::eFuncTouchPane_B_optnBtn_00;
         i < res::eFuncTouchPane_B_optnBtn_20 + 1; i++) {

        mpLayout->GetRootPane()
            ->FindPaneByName(scFuncTouchPaneName[i], true)
            ->SetVisible(false);
    }

    for (i = 0; i < res::eFuncTextPane_Max; i++) {
        mpLayout->GetRootPane()
            ->FindPaneByName(scFuncTextPaneName[i], true)
            ->SetVisible(false);
    }

    mpRemoteSpk->Start();

    if (mpSoundArchivePlayer != NULL) {
        nw4r::ut::detail::AutoLock<OSMutex> lock(sMutex);

        for (i = 0; i < mpSoundArchivePlayer->GetSoundPlayerCount(); i++) {
            mpSoundArchivePlayer->GetSoundPlayer(i).SetVolume(1.0f);
        }
    }

    calc(NULL);

    mFader.init(30.0f / getInstance()->getHBMDataInfo()->frameDelta);
}

void HomeButton::init_msg() {
    int i, len;

    for (i = 0; i < res::eFuncTextPane_Max; i++) {
        nw4r::lyt::Pane* p_pane = mpLayout->GetRootPane()->FindPaneByName(
            scFuncTextPaneName[i], true);

        nw4r::lyt::TextBox* p_text =
            nw4r::ut::DynamicCast<nw4r::lyt::TextBox*, nw4r::lyt::Pane>(p_pane);

        for (len = 0;; len++) {
            if (mpText[mpHBInfo->region][i][len] == L'\"') {
                break;
            }
        }

        p_text->SetString(mpText[mpHBInfo->region][i], 0, len);
    }
}

void HomeButton::init_volume() {
    int i, anm_no;

    mVolumeNum = getVolume();
    setVolume(HBM_MAX_VOLUME);

    for (i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        getController(i)->setSpeakerVol(mVolumeNum /
                                        static_cast<f32>(HBM_MAX_VOLUME));

        getController(i)->connect();
    }

    for (i = 0; i < res::eGroup_vol_09 - res::eGroup_vol_00 + 1; i++) {
        if (i < mVolumeNum) {
            anm_no = findGroupAnimator(i + res::eGroup_vol_00,
                                       res::eGroupAnim_sound_ylw);
            mpGroupAnmController[anm_no]->start();
        } else {
            anm_no = findGroupAnimator(i + res::eGroup_vol_00,
                                       res::eGroupAnim_sound_gry);
            mpGroupAnmController[anm_no]->start();
        }
    }
}

void HomeButton::init_vib() {
    int anm_no;

    mVibFlag = getVibFlag();

    if (mVibFlag) {
        anm_no = findGroupAnimator(res::eGroup_optnBtn_10_psh,
                                   res::eGroupAnim_vb_btn_wht_psh);
        mpGroupAnmController[anm_no]->start();

        anm_no = findGroupAnimator(res::eGroup_optnBtn_11_psh,
                                   res::eGroupAnim_vb_btn_ylw_psh);
        mpGroupAnmController[anm_no]->start();
    } else {
        anm_no = findGroupAnimator(res::eGroup_optnBtn_10_psh,
                                   res::eGroupAnim_vb_btn_ylw_psh);
        mpGroupAnmController[anm_no]->start();

        anm_no = findGroupAnimator(res::eGroup_optnBtn_11_psh,
                                   res::eGroupAnim_vb_btn_wht_psh);
        mpGroupAnmController[anm_no]->start();
    }
}

void HomeButton::init_sound() {
    if (mpHBInfo->sound_callback != NULL) {
        mpHBInfo->sound_callback(HBM_SE_HOME_BUTTON, 0);
    }

    mAppVolume[nw4r::snd::AUX_A] = AXGetAuxAReturnVolume();
    mAppVolume[nw4r::snd::AUX_B] = AXGetAuxBReturnVolume();
    mAppVolume[nw4r::snd::AUX_C] = AXGetAuxCReturnVolume();

    AXFXGetHooks(&mAxFxAlloc, &mAxFxFree);
    AXGetAuxACallback(&mAuxCallback, &mpAuxContext);
    AXFXSetHooks(&HBMAllocMem, &HBMFreeMem);

    mAxFxReverb.preDelay = 0.0f;
    mAxFxReverb.time = 2.5f;
    mAxFxReverb.coloration = 0.5f;
    mAxFxReverb.damping = 0.0f;
    mAxFxReverb.crosstalk = 0.0f;
    mAxFxReverb.mix = 1.0f;

    AXFXReverbHiInit(&mAxFxReverb);
    AXRegisterAuxACallback(&AXFXReverbHiCallback, &mAxFxReverb);

    AXSetAuxAReturnVolume(AX_MAX_VOLUME);
    AXSetAuxBReturnVolume(0);
    AXSetAuxCReturnVolume(0);

    if (mpHBInfo->sound_callback != NULL) {
        mpHBInfo->sound_callback(HBM_SE_RETURN_APP, 0);
    }

    mEndInitSoundFlag = true;
}

void HomeButton::init_battery(const HBMControllerData* pController) {
    int anm_no;

    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        if (pController->wiiCon[i].kpad) {
            if (!mpHBInfo->cursor) {
                mpCursorLayout[i]
                    ->GetRootPane()
                    ->FindPaneByName(scCursorPaneName, true)
                    ->SetVisible(true);
            }

            anm_no = findGroupAnimator(i + res::eGroup_plyr_00,
                                       res::eGroupAnim_btry_wht);
            mpGroupAnmController[anm_no]->start();
            mControllerFlag[i] = true;

            getController(i)->getInfoAsync(&mWpadInfo[i]);
        } else {
            if (!mpHBInfo->cursor) {
                mpCursorLayout[i]
                    ->GetRootPane()
                    ->FindPaneByName(scCursorPaneName, true)
                    ->SetVisible(false);
            }

            anm_no = findGroupAnimator(i + res::eGroup_plyr_00,
                                       res::eGroupAnim_btry_gry);
            mpGroupAnmController[anm_no]->start();
            mControllerFlag[i] = false;
        }
    }

    reset_battery();
    mGetPadInfoTime = 0;
}

void HomeButton::calc(const HBMControllerData* pController) {
    int i;

    mpPaneManager->calc();

    for (i = 0; i < mAnmNum; i++) {
        mpAnmController[i]->do_calc();
    }

    for (i = 0; i < res::ePairGroup_Max; i++) {
        mpPairGroupAnmController[i]->do_calc();
    }

    for (i = 0; i < res::eGrAnimator_Max; i++) {
        mpGroupAnmController[i]->do_calc();
    }

    for (i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        if (mOnPaneVibFrame[i] > 0.0f) {
            if (!mControllerFlag[i] || !getController(i)->isRumbling()) {
                mOnPaneVibFrame[i] = 0.0f;
                mOnPaneVibWaitFrame[i] = 0.0f;

                if (getController(i)->isRumbling()) {
                    getController(i)->stopMotor();
                }
            } else {
                mOnPaneVibFrame[i] -= mpHBInfo->frameDelta;

                if (mOnPaneVibFrame[i] <= 0.0f || mState == 17) {
                    getController(i)->stopMotor();
                    mOnPaneVibFrame[i] = 0.0f;
                    mOnPaneVibWaitFrame[i] = scOnPaneVibWaitTime;
                }
            }
        } else if (mOnPaneVibWaitFrame[i] > 0.0f) {
            mOnPaneVibWaitFrame[i] -= mpHBInfo->frameDelta;

            if (mOnPaneVibWaitFrame[i] <= 0.0f)
                mOnPaneVibWaitFrame[i] = 0.0f;
        }
    }

    switch (mState) {
    case 0:
        if (mpHBInfo->backFlag) {
            mSelectAnmNum = findGroupAnimator(2, 0);

            mpLayout->GetRootPane()
                ->FindPaneByName("back_00", true)
                ->SetVisible(false);

            mpLayout->GetRootPane()
                ->FindPaneByName("back_02", true)
                ->SetVisible(true);
        } else {
            mSelectAnmNum = findGroupAnimator(0, 0);

            mpLayout->GetRootPane()
                ->FindPaneByName("back_00", true)
                ->SetVisible(true);

            mpLayout->GetRootPane()
                ->FindPaneByName("back_02", true)
                ->SetVisible(false);
        }

        mpGroupAnmController[mSelectAnmNum]->start();

        if (pController) {
            mState = 1;
            init_battery(pController);
        }

        break;

    case 1:
        if (!mpGroupAnmController[mSelectAnmNum]->isPlaying()) {
            init_volume();
            init_vib();
            init_sound();
            play_sound(0);

            mState = 2;
        }

        break;

    case 2:
        calc_letter();
        break;

    case 3:
        if (!mpGroupAnmController[mSelectAnmNum]->isPlaying() &&
            mSelectAnmNum != 5) {
            reset_battery();
            mSelectAnmNum = 5;
            mpPairGroupAnmController[mSelectAnmNum]->start();
        }

        mWaitStopMotorCount--;
        if (mWaitStopMotorCount <= 0) {
            for (i = 0; i < WPAD_MAX_CONTROLLERS; i++)
                WPADDisconnect(i);

            mState = 4;
            mDisConnectCount =
                180.0f / getInstance()->getHBMDataInfo()->frameDelta; // ?
        }

        break;

    case 4:
        if (mpGroupAnmController[mSelectAnmNum]->isPlaying())
            break;

        if (mDisConnectCount > 0) {
            for (i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
                s32 type;
                if (WPADProbe(i, &type) != WPAD_ERR_NO_CONTROLLER)
                    break;
            }

            if (i < WPAD_MAX_CONTROLLERS) {
                --mDisConnectCount;
                break;
            }

            mDisConnectCount = 0;
        }

        mState = 5;
        mMsgCount = 0;
        mSoundRetryCnt = 0;
        mSimpleSyncCallback = WPADSetSimpleSyncCallback(&SimpleSyncCallback);
        mEndSimpleSyncFlag = false;

        for (i = 0; i < WPAD_MAX_CONTROLLERS; i++)
            getController(i)->setEnableRumble(true);

        mSimpleSyncFlag = WPADStartFastSimpleSync();

        if (!mSimpleSyncFlag)
            setSimpleSyncAlarm(0);

        break;

    case 5:
    case 6:
        if (!mSimpleSyncFlag ||
            mpPairGroupAnmController[mSelectAnmNum]->isPlaying()) {
            break;
        }

        if (mMsgCount == 0) {
            reset_control();
            reset_btn();
            mpPairGroupAnmController[14]->setAnmType(2);
            mpPairGroupAnmController[14]->start();
        }

        if (mControllerFlag[3]) {
            if (mState != 6) {
                if (getController(3)->isPlayingSoundId(5)) {
                    mState = 6;
                    mMsgCount = iReConnectTime2;
                }

                ++mSoundRetryCnt;
                if (mSoundRetryCnt <= iReConnectTime2)
                    break;

                mState = 6;
                mMsgCount = iReConnectTime2;
                break;
            }

            ++mMsgCount;
            if (mMsgCount <= iReConnectTime)
                break;

            mState = 7;
        } else {
            ++mMsgCount;
            if (mMsgCount <= iReConnectTime)
                break;

            mState = 7;

            if (!WPADStopSimpleSync()) {
                setSimpleSyncAlarm(1);
            }

            mEndSimpleSyncFlag = true;
        }

        break;

    case 7:
        if (!mEndSimpleSyncFlag)
            break;

        WPADSetSimpleSyncCallback(mSimpleSyncCallback);
        mpRemoteSpk->ClearPcm();
        reset_guiManager(-1);

        mSelectAnmNum = 6;
        mpPairGroupAnmController[mSelectAnmNum]->start();

        mState = 8;
        mpPairGroupAnmController[14]->setAnmType(0);

        play_sound(21);

        break;

    case 8:
        if (mpPairGroupAnmController[mSelectAnmNum]->isPlaying())
            break;

        if (mSelectAnmNum == 13) {
            reset_window();

            mpLayout->GetRootPane()
                ->FindPaneByName(scFuncTextPaneName[2], true)
                ->SetVisible(false);
        } else if (mSelectAnmNum == 6) {
            mpLayout->GetRootPane()
                ->FindPaneByName(scFuncTextPaneName[0], true)
                ->SetVisible(false);

            mpLayout->GetRootPane()
                ->FindPaneByName(scFuncTextPaneName[1], true)
                ->SetVisible(false);
        }

        mState = 2;
        break;

    case 9:
        if (mpGroupAnmController[mSelectAnmNum]->isPlaying())
            break;

        if (mVibFlag) {
            for (i = 0; i < WPAD_MAX_CONTROLLERS; i++)
                getController(i)->stopMotor();
        }

        mState = 2;

        break;

    case 10:
        if (mpPairGroupAnmController[mSelectAnmNum]->isPlaying())
            break;

        mBar0AnmRev = 0;
        mBar1AnmRev = 0;
        mBar0AnmRevHold = 0;
        mBar1AnmRevHold = 0;

        if (mSequence != eSeq_Control) {
            // 2-6: "B_optnBtn_XX" entries in scFuncTouchPaneName
            for (i = 2; i < 7; i++) {
                mpLayout->GetRootPane()
                    ->FindPaneByName(scFuncTouchPaneName[i], true)
                    ->SetVisible(false);
            }

            mState = 2;
        } else if (mSequence == eSeq_Control) {
            mSelectAnmNum = 10;
            mpPairGroupAnmController[mSelectAnmNum]->start();

            mSelectAnmNum = 1;
            play_sound(7);

            mState = 8;
        }

        updateTrigPane();

        break;

    case 11:
        if (mpAnmController[mSelectAnmNum]->isPlaying())
            break;

        mSelectAnmNum = 7;
        mpPairGroupAnmController[mSelectAnmNum]->start();

        mState = 12;

        break;

    case 12:
        if (mpPairGroupAnmController[mSelectAnmNum]->isPlaying())
            break;

        updateTrigPane();
        reset_btn();
        mState = 2;

        break;

    case 13: {
        if (mpGroupAnmController[mSelectAnmNum]->isPlaying())
            break;

        // only case is SELECT_NULL
        if (mSelectBtnNum >= 0) {
            mFader.start();
            mState = 19;
            mFadeOutSeTime = mFader.getMaxFrame();

            if (mSelectBtnNum != HBM_SELECT_BTN3 && mpHBInfo->sound_callback)
                mpHBInfo->sound_callback(3, mFadeOutSeTime);
        } else {
            updateTrigPane();
            mSelectAnmNum = 13;
            mpPairGroupAnmController[mSelectAnmNum]->start();
            mState = 8;
        }

        reset_guiManager(-1);
    } break;

    case 14:
        if (mpPairGroupAnmController[mSelectAnmNum]->isPlaying())
            break;

        calc_fadeoutAnm();
        break;

    case 15:
        if (mpAnmController[mSelectAnmNum]->isPlaying())
            break;

        mFader.start();
        mStartBlackOutFlag = true;
        mState = 19;
        mFadeOutSeTime = mFader.getMaxFrame();

        if (mSelectBtnNum != HBM_SELECT_BTN3 && mpHBInfo->sound_callback)
            mpHBInfo->sound_callback(3, mFadeOutSeTime);

        break;

    case 16: {
        GroupAnmController* anim = mpGroupAnmController[mSelectAnmNum];

        if (!anim->isPlaying()) {
            mState = 17;
            fadeout_sound(0.0f);
        } else {
            f32 restFrame = anim->getMaxFrame() - anim->getCurrentFrame();
            fadeout_sound(restFrame / mFadeOutSeTime);
        }
    } break;

    case 17:
        mState = 18;

        if (mSelectBtnNum != HBM_SELECT_BTN3) {
            if (mpSoundArchivePlayer != NULL) {
                nw4r::ut::detail::AutoLock<OSMutex> lock(sMutex);

                for (int i = 0; i < mpSoundArchivePlayer->GetSoundPlayerCount();
                     i++) {

                    mpSoundArchivePlayer->GetSoundPlayer(i).StopAllSound(0);
                }
            }

            if (mEndInitSoundFlag) {
                AXFXReverbHiShutdown(&mAxFxReverb);
                AXRegisterAuxACallback(mAuxCallback, mpAuxContext);
                AXFXSetHooks(mAxFxAlloc, mAxFxFree);

                AXSetAuxAReturnVolume(mAppVolume[nw4r::snd::AUX_A]);
                AXSetAuxBReturnVolume(mAppVolume[nw4r::snd::AUX_B]);
                AXSetAuxCReturnVolume(mAppVolume[nw4r::snd::AUX_C]);
            }
        }

        setVolume(mVolumeNum);
        WPADSaveConfig(NULL);

        mpRemoteSpk->Stop();
        for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
            mpController[i]->clearCallback();
        }

        if (mSelectBtnNum != HBM_SELECT_BTN3 && mpHBInfo->sound_callback) {
            mpHBInfo->sound_callback(4, 0);
        }

        mInitFlag = false;
        break;

    case 18:
        mState = 2;
        break;

    case 19:
        if (mForceSttInitProcFlag) {
            init_battery(pController);
            mForceSttInitProcFlag = false;
        }

        if (mForceSttFadeInProcFlag) {
            init_volume();
            init_vib();
            mForceSttFadeInProcFlag = false;
        }

        if (mFader.isDone()) {
            if (mForceStopSyncFlag) {
                if (!mEndSimpleSyncFlag)
                    break;

                WPADSetSimpleSyncCallback(mSimpleSyncCallback);
                mForceStopSyncFlag = false;
            }

            if (mForceEndMsgAnmFlag) {
                int anm_no;

                anm_no = 5;
                mpPairGroupAnmController[anm_no]->initFrame();
                mpPairGroupAnmController[anm_no]->stop();

                mpLayout->GetRootPane()
                    ->FindPaneByName(scFuncTextPaneName[0], true)
                    ->SetVisible(false);
                mpLayout->GetRootPane()
                    ->FindPaneByName(scFuncTextPaneName[1], true)
                    ->SetVisible(false);

                anm_no = 14;
                if (mpPairGroupAnmController[anm_no]->isPlaying()) {
                    mpPairGroupAnmController[anm_no]->initFrame();
                    mpPairGroupAnmController[anm_no]->stop();
                }
            }

            mState = 17;

            VISetBlack(TRUE);
            VIFlush();

            fadeout_sound(0.0f);
        } else {
            f32 restFrame = mFader.getMaxFrame() - mFader.getFrame();

            fadeout_sound(restFrame / mFadeOutSeTime);
        }

        break;

    default: {
        break;
    }
    }

    if (mBar0AnmRev && isUpBarActive()) {
        if (mBar0AnmRev && mBar0AnmRev != mBar0AnmRevHold) {
            mpPairGroupAnmController[mBar0AnmRev]->start();
            mBar0AnmRevHold = mBar0AnmRev;
        }

        mBar0AnmRev = 0;
    }

    if (mBar1AnmRev && isDownBarActive()) {
        if (mBar1AnmRev && mBar1AnmRev != mBar1AnmRevHold) {
            mpGroupAnmController[mBar1AnmRev]->start();
            mBar1AnmRevHold = mBar1AnmRev;
        }

        mBar1AnmRev = 0;
    }

    if (pController != NULL) {
        update(pController);
    }

    mpLayout->Animate(0);
    mpLayout->CalculateMtx(mDrawInfo);

    if (!mpHBInfo->cursor) {
        for (i = 0; i < WPAD_MAX_CONTROLLERS; i++)
            mpCursorLayout[i]->CalculateMtx(mDrawInfo);
    }

    if (mForcusSEWaitTime <= 2)
        mForcusSEWaitTime++;
}

void HomeButton::calc_fadeoutAnm() {
    mpLayout->GetRootPane()
        ->FindPaneByName(scFuncTextPaneName[2], true)
        ->SetVisible(false);

    if (mpHBInfo->backFlag)
        mSelectAnmNum = findGroupAnimator(3, 1);
    else
        mSelectAnmNum = findGroupAnimator(1, 1);

    mpGroupAnmController[mSelectAnmNum]->start();
    mState = 16;
    mFadeOutSeTime = mpGroupAnmController[mSelectAnmNum]->getMaxFrame();

    if (mpHBInfo->sound_callback)
        mpHBInfo->sound_callback(2, mFadeOutSeTime);
}

void HomeButton::calc_letter() {
    if (mLetterFlag &&
        !mpPairGroupAnmController[res::ePairGroup_ltrIcn_on]->isPlaying()) {

        mpLayout->GetRootPane()
            ->FindPaneByName(scFuncPaneName[res::eFuncPane_let_icn_00], true)
            ->SetVisible(true);

        mpPairGroupAnmController[res::ePairGroup_ltrIcn_on]->setAnmType(
            FrameController::eAnmType_Wrap);

        mpPairGroupAnmController[res::ePairGroup_ltrIcn_on]->start();
    } else if (!mLetterFlag) {
        mpLayout->GetRootPane()
            ->FindPaneByName(scFuncPaneName[res::eFuncPane_let_icn_00], true)
            ->SetVisible(false);

        mpPairGroupAnmController[res::ePairGroup_ltrIcn_on]->stop();
    }
}

void HomeButton::calc_battery(int chan) {
    // presumably j because it is the second index
    for (int j = 0; j < (int)ARRAY_SIZE(scBatteryPaneName[chan]); j++) {
        if (j < mWpadInfo[chan].battery) {
            mpLayout->GetRootPane()
                ->FindPaneByName(scBatteryPaneName[chan][j], true)
                ->SetVisible(true);
        } else {
            mpLayout->GetRootPane()
                ->FindPaneByName(scBatteryPaneName[chan][j], true)
                ->SetVisible(false);
        }
    }

    if (mWpadInfo[chan].battery < 2) {
        int anm_no = findGroupAnimator(chan + 31, 21);
        mpGroupAnmController[anm_no]->start();
    } else {
        int anm_no = findGroupAnimator(chan + 31, 17);
        mpGroupAnmController[anm_no]->start();
    }

    if (mGetPadInfoTime < 100)
        mGetPadInfoTime = 0;

    getController(chan)->clrBatteryFlag();
}

void HomeButton::draw() {
    mpLayout->Draw(mDrawInfo);

    if (!mpHBInfo->cursor) {
        for (int i = WPAD_MAX_CONTROLLERS - 1; i >= 0; i--)
            mpCursorLayout[i]->Draw(mDrawInfo);
    }

    mFader.draw();
}

static void SpeakerCallback(OSAlarm* alm, OSContext*) {
    u32 data = reinterpret_cast<u32>(OSGetAlarmUserData(alm));
    int chan = (data >> 16) & 0xffff;
    int id = data & 0xffff;

    HomeButton* pHBObj = HomeButton::getInstance();

    if (!WPADIsSpeakerEnabled(chan) ||
        !pHBObj->getController(chan)->isPlayReady()) {
        pHBObj->setSpeakerAlarm(chan, 50);
    } else {
        pHBObj->getController(chan)->playSound(pHBObj->getSoundArchivePlayer(),
                                               id);
    }
}

static void MotorCallback(OSAlarm* alm, OSContext*) {
    Controller* pController =
        reinterpret_cast<Controller*>(OSGetAlarmUserData(alm));

    pController->stopMotor();
}

void HomeButton::setSpeakerAlarm(int chan, int msec) {
    OSSetAlarmUserData(&mSpeakerAlarm[chan],
                       reinterpret_cast<void*>((chan << 16) | (chan + 2)));

    OSCancelAlarm(&mSpeakerAlarm[chan]);
    OSSetAlarm(&mSpeakerAlarm[chan], OS_MSEC_TO_TICKS(msec), &SpeakerCallback);
}

static void RetrySimpleSyncCallback(OSAlarm* alm, OSContext*) {
    HomeButton* pHBObj = HomeButton::getInstance();
    int type = reinterpret_cast<int>(OSGetAlarmUserData(alm));
    bool retrySuccessFlag = false;

    if (type == 0) {
        if (WPADStartFastSimpleSync()) {
            pHBObj->setSimpleSyncFlag(true);
            retrySuccessFlag = true;
        }
    } else {
        if (WPADStopSimpleSync())
            retrySuccessFlag = true;
    }

    if (!retrySuccessFlag)
        pHBObj->setSimpleSyncAlarm(type);
}

static void SimpleSyncCallback(s32 result, s32 num) {
    if (result == 1)
        HomeButton::getInstance()->setEndSimpleSyncFlag(true);

    HomeButton::getInstance()->callSimpleSyncCallback(result, num);
}

void HomeButton::setSimpleSyncAlarm(int type) {
    OSCancelAlarm(&mSimpleSyncAlarm);
    OSSetAlarmUserData(&mSimpleSyncAlarm, reinterpret_cast<void*>(type));
    OSSetAlarm(&mSimpleSyncAlarm, OS_MSEC_TO_TICKS(100),
               &RetrySimpleSyncCallback);
}

void HomeButton::callSimpleSyncCallback(s32 result, s32 num) {
    if (mSimpleSyncCallback)
        (*mSimpleSyncCallback)(result, num);
}

void HomeButton::update(const HBMControllerData* pController) {
#define IsValidDevType_(x)                                                     \
    ((x)->use_devtype == WPAD_DEV_CLASSIC ||                                   \
     (x)->kpad->dev_type == WPAD_DEV_CLASSIC)

    int i, anm_no;

    mFader.calc();

    for (i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        if (pController->wiiCon[i].kpad) {
            if (pController->wiiCon[i].kpad->wpad_err !=
                WPAD_ERR_NO_CONTROLLER) {
                if (mPadDrawTime[i] >
                    static_cast<int>(
                        5.0f / getInstance()->getHBMDataInfo()->frameDelta +
                        0.5f)) {
                    if (pController->wiiCon[i].kpad->wpad_err == WPAD_ERR_OK) {
                        bool pointerEnableFlag;

                        if (!IsValidDevType_(&pController->wiiCon[i])) {
                            if (pController->wiiCon[i].kpad->dpd_valid_fg > 0)
                                pointerEnableFlag = true;
                            else
                                pointerEnableFlag = false;
                        } else
                            pointerEnableFlag = true;

                        mpController[i]->setKpad(&pController->wiiCon[i],
                                                 pointerEnableFlag);

                        if (!mpHBInfo->cursor) {
                            mpCursorLayout[i]
                                ->GetRootPane()
                                ->FindPaneByName(scCursorPaneName, true)
                                ->SetVisible(true);
                        }
                    }
                } else {
                    mPadDrawTime[i]++;
                }

                if (!IsValidDevType_(&pController->wiiCon[i]) &&
                    pController->wiiCon[i].kpad->dpd_valid_fg <= 0) {
                    s32 result;
                    s32 type;

                    result = WPADProbe(i, &type);

                    if (pController->wiiCon[i].kpad->wpad_err !=
                            WPAD_ERR_COMMUNICATION_ERROR &&
                        result != WPAD_ERR_COMMUNICATION_ERROR) {
                        mpController[i]->setInValidPos();
                    }
                }
            } else {
                mpController[i]->setInValidPos();

                if (!mpHBInfo->cursor) {
                    mpCursorLayout[i]
                        ->GetRootPane()
                        ->FindPaneByName(scCursorPaneName, true)
                        ->SetVisible(false);
                }
            }

            if (!mControllerFlag[i]) {
                // mConnectNum = i;
                mControllerFlag[i] = true;

                getController(i)->getInfoAsync(&mWpadInfo[i]);

                anm_no = findGroupAnimator(i + 31, 17);
                mpGroupAnmController[anm_no]->start();

                anm_no = findGroupAnimator(i + 31, 18);
                mpGroupAnmController[anm_no]->stop();

                anm_no = findGroupAnimator(i + 31, 15);
                mpGroupAnmController[anm_no]->start();

                play_sound(i + 17);
                getController(i)->connect();
                getController(i)->startMotor();

                OSSetAlarmUserData(&mAlarm[i],
                                   reinterpret_cast<void*>(getController(i)));
                OSCancelAlarm(&mAlarm[i]);
                OSSetAlarm(&mAlarm[i], OS_MSEC_TO_TICKS(300), &MotorCallback);

                setSpeakerAlarm(i, 400);
            }

            if (pController->wiiCon[i].kpad->wpad_err == WPAD_ERR_OK) {
                nw4r::math::VEC3 vec;

                if (pController->wiiCon[i].use_devtype == WPAD_DEV_CLASSIC &&
                    pController->wiiCon[i].kpad->dev_type == WPAD_DEV_CLASSIC) {
                    vec = nw4r::math::VEC3(0.0f, 0.0f, 15.0f);
                } else {
                    Vec2 v = pController->wiiCon[i].kpad->horizon;
                    f32 mRad = nw4r::math::Atan2Deg(-v.y, v.x);

                    vec = nw4r::math::VEC3(0.0f, 0.0f, mRad);
                }

                if (!mpHBInfo->cursor) {
                    mpCursorLayout[i]
                        ->GetRootPane()
                        ->FindPaneByName(scCursorRotPaneName, true)
                        ->SetRotate(vec);

                    mpCursorLayout[i]
                        ->GetRootPane()
                        ->FindPaneByName(scCursorSRotPaneName, true)
                        ->SetRotate(vec);
                }

                if (mGetPadInfoTime > 100)
                    getController(i)->getInfoAsync(&mWpadInfo[i]);

                update_controller(i);

                if (!mpHBInfo->cursor)
                    update_posController(i);
            }

            if (getController(i)->getBatteryFlag())
                calc_battery(i);
        } else {
            if (mControllerFlag[i]) {
                anm_no = findGroupAnimator(i + 31, 17);
                mpGroupAnmController[anm_no]->start();

                anm_no = findGroupAnimator(i + 31, 18);
                mpGroupAnmController[anm_no]->start();

                for (int j = 0; j < (int)ARRAY_SIZE(scBatteryPaneName[i]);
                     j++) {
                    mpLayout->GetRootPane()
                        ->FindPaneByName(scBatteryPaneName[i][j], true)
                        ->SetVisible(false);
                }

                if (!mpHBInfo->cursor) {
                    mpCursorLayout[i]
                        ->GetRootPane()
                        ->FindPaneByName(scCursorPaneName, true)
                        ->SetVisible(false);
                }

                mPadDrawTime[i] = 0;
                mControllerFlag[i] = false;

                mpController[i]->setInValidPos();
                mpController[i]->clrKpadButton();
                mpController[i]->disconnect();
            }

            reset_guiManager(i);
        }
    }

    if (mGetPadInfoTime > 100)
        mGetPadInfoTime = 0;
    else
        mGetPadInfoTime++;
#undef IsValidDevType_
}

void HomeButton::update_controller(int id) {
    int anm_no;

    if (isActive()) {
        HBController* pCon = mpController[id]->getController();

        f32 x = pCon->x * 608.0f / 2.0f;
        f32 y = pCon->y * 456.0f / 2.0f;

        if (mAdjustFlag) {
            x *= mpHBInfo->adjust.x;
            y *= mpHBInfo->adjust.y;
        }

        mpPaneManager->update(id, x, -y, pCon->trig, pCon->hold, pCon->release,
                              pCon);

        if (((pCon->trig & 1 << 28) | (pCon->trig & WPAD_BUTTON_HOME)) &&
            isActive()) {

            if (mSequence == eSeq_Control) {
                mpPaneManager->update(id, 0.0f, -180.0f, 0, 0, 0, 0);
                mpPairGroupAnmController[4]->start();

                mSelectAnmNum = 2;
                mpPairGroupAnmController[mSelectAnmNum]->start();

                int anm_no = 11; // ?
                mpPairGroupAnmController[anm_no]->start();

                mState = 10;
                mSequence = eSeq_Normal;
                play_sound(8);
            } else if (mSequence == eSeq_Normal) {
                if (mpPairGroupAnmController[3]->isPlaying())
                    mpPairGroupAnmController[3]->stop();

                if (mpPairGroupAnmController[12]->isPlaying())
                    mpPairGroupAnmController[12]->stop();

                mSelectBtnNum = HBM_SELECT_HOMEBTN;

                mSelectAnmNum = 4;
                mpPairGroupAnmController[mSelectAnmNum]->start();

                mState = 14;
                play_sound(1);
            }
        } else if (mSequence == eSeq_Control && isActive()) {
            if ((pCon->trig & WPAD_BUTTON_MINUS) || (pCon->trig & (1 << 16))) {
                if (mVolumeNum > 0) {
                    mVolumeNum--;

                    anm_no = findGroupAnimator(mVolumeNum + 21, 10);
                    mpGroupAnmController[anm_no]->stop();

                    anm_no = findGroupAnimator(mVolumeNum + 21, 9);
                    mpGroupAnmController[anm_no]->start();

                    anm_no = findGroupAnimator(11, 5);
                    mpGroupAnmController[anm_no]->start();

                    if (mVolumeNum == 0) {
                        play_sound(12);

                        for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
                            getController(i)->setSpeakerVol(mVolumeNum / 10.0f);
                            getController(i)->playSound(mpSoundArchivePlayer,
                                                        1);
                        }
                    } else {
                        play_sound(10);

                        for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
                            getController(i)->setSpeakerVol(mVolumeNum / 10.0f);
                            getController(i)->playSound(mpSoundArchivePlayer,
                                                        1);
                        }
                    }
                } else {
                    play_sound(13);
                }
            } else if ((pCon->trig & WPAD_BUTTON_PLUS) ||
                       (pCon->trig & (1 << 17))) {
                if (mVolumeNum < 10) {
                    anm_no = findGroupAnimator(mVolumeNum + 21, 9);
                    mpGroupAnmController[anm_no]->stop();

                    anm_no = findGroupAnimator(mVolumeNum + 21, 10);
                    mpGroupAnmController[anm_no]->start();

                    mVolumeNum++;

                    anm_no = findGroupAnimator(12, 5);
                    mpGroupAnmController[anm_no]->start();

                    if (mVolumeNum == 10) {
                        play_sound(11);

                        for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
                            getController(i)->setSpeakerVol(mVolumeNum / 10.0f);
                            getController(i)->playSound(mpSoundArchivePlayer,
                                                        1);
                        }
                    } else {
                        play_sound(9);

                        for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
                            getController(i)->setSpeakerVol(mVolumeNum / 10.0f);
                            getController(i)->playSound(mpSoundArchivePlayer,
                                                        1);
                        }
                    }
                } else {
                    play_sound(13);
                }
            }
        }
    } else if (mSequence == eSeq_Control && mState == 5 &&
               !mpPairGroupAnmController[mSelectAnmNum]->isPlaying()) {
        HBController* pCon = mpController[id]->getController();
        if (pCon->trig)
            mMsgCount = iReConnectTime;
    }
}

void HomeButton::update_posController(int id) {
    HBController* pCon = mpController[id]->getController();
    nw4r::ut::Rect layoutRect = mpLayout->GetLayoutRect();

    f32 x = pCon->x * layoutRect.right;
    f32 y = pCon->y * layoutRect.bottom;
    nw4r::math::VEC2 pos(x, y);

    mpCursorLayout[id]
        ->GetRootPane()
        ->FindPaneByName(scCursorPaneName, true)
        ->SetTranslate(pos);
}

void HomeButton::updateTrigPane() {
    int i;

    switch (mSequence) {
    case eSeq_Normal:
        for (i = 0; i < (int)ARRAY_SIZE(scFuncTouchPaneName); i++) {
            if (i < 2 || i == 9) {
                nw4r::lyt::Pane* pTouchPane =
                    mpLayout->GetRootPane()->FindPaneByName(
                        scFuncTouchPaneName[i], true);

                mpPaneManager->getPaneComponentByPane(pTouchPane)
                    ->setTriggerTarget(true);
            } else {
                nw4r::lyt::Pane* pTouchPane =
                    mpLayout->GetRootPane()->FindPaneByName(
                        scFuncTouchPaneName[i], true);

                mpPaneManager->getPaneComponentByPane(pTouchPane)
                    ->setTriggerTarget(false);
            }
        }

        break;

    case eSeq_Control:
        for (i = 0; i < (int)ARRAY_SIZE(scFuncTouchPaneName); i++) {
            if ((i > 0 && i < 7) || i == 9) {
                nw4r::lyt::Pane* pTouchPane =
                    mpLayout->GetRootPane()->FindPaneByName(
                        scFuncTouchPaneName[i], true);

                mpPaneManager->getPaneComponentByPane(pTouchPane)
                    ->setTriggerTarget(true);
            } else {
                nw4r::lyt::Pane* pTouchPane =
                    mpLayout->GetRootPane()->FindPaneByName(
                        scFuncTouchPaneName[i], true);

                mpPaneManager->getPaneComponentByPane(pTouchPane)
                    ->setTriggerTarget(false);
            }
        }

        break;

    case eSeq_Cmn:
        for (i = 0; i < (int)ARRAY_SIZE(scFuncTouchPaneName); i++) {
            if (i < 7 || i == 9) {
                nw4r::lyt::Pane* pTouchPane =
                    mpLayout->GetRootPane()->FindPaneByName(
                        scFuncTouchPaneName[i], true);

                mpPaneManager->getPaneComponentByPane(pTouchPane)
                    ->setTriggerTarget(false);
            } else {
                nw4r::lyt::Pane* pTouchPane =
                    mpLayout->GetRootPane()->FindPaneByName(
                        scFuncTouchPaneName[i], true);

                mpPaneManager->getPaneComponentByPane(pTouchPane)
                    ->setTriggerTarget(true);
            }
        }

        break;
    }
}

void HomeButton::startPointEvent(const char* pName, void* pData) {
    int anm_no;
    int btn_no = getPaneNo(pName);
    HBController* pCon = static_cast<HBController*>(pData);
    bool onFlag = false;

    if (isActive() && btn_no != -1 && !mPaneCounter[btn_no]) {
        if (mSequence != eSeq_Cmn && btn_no < mButtonNum) {
            anm_no = findAnimator(btn_no, 0);
            mpAnmController[anm_no]->start();

            if (mSequence == eSeq_Normal) {
                setForcusSE();
                onFlag = true;
            }
        } else {
            switch (btn_no - mButtonNum) {
            case 0:
                if (mSequence == eSeq_Normal) {
                    if (isUpBarActive()) {
                        mpPairGroupAnmController[3]->start();
                        mBar0AnmRevHold = 3;
                        mBar0AnmRev = 0;
                        setForcusSE();
                        onFlag = true;
                    } else {
                        mBar0AnmRev = 3;
                    }
                }

                break;

            case 1:
            case 9:
                if (mSequence == eSeq_Normal) {
                    anm_no = findGroupAnimator(4, 2);

                    if (homebutton::HomeButton::isDownBarActive()) {
                        mpGroupAnmController[anm_no]->start();
                        mBar1AnmRevHold = anm_no;
                        mBar1AnmRev = 0;
                        setForcusSE();
                        onFlag = true;
                    } else {
                        mBar1AnmRev = anm_no;
                    }
                } else if (mSequence == eSeq_Control) {
                    anm_no = findGroupAnimator(4, 19);

                    if (isDownBarActive()) {
                        mpGroupAnmController[anm_no]->start();
                        mBar1AnmRevHold = anm_no;
                        mBar1AnmRev = 0;
                        setForcusSE();
                        onFlag = true;
                    } else {
                        mBar1AnmRev = anm_no;
                    }
                }

                break;

            case 2:
                if (mSequence == eSeq_Control) {
                    anm_no = findGroupAnimator(6, 4);
                    mpGroupAnmController[anm_no]->start();

                    setForcusSE();
                    onFlag = true;
                }

                break;

            case 3:
                if (mSequence == eSeq_Control) {
                    anm_no = findGroupAnimator(7, 4);
                    mpGroupAnmController[anm_no]->start();

                    setForcusSE();
                    onFlag = true;
                }

                break;

            case 4:
                if (mSequence == eSeq_Control) {
                    anm_no = findGroupAnimator(8, 4);
                    mpGroupAnmController[anm_no]->start();

                    setForcusSE();
                    onFlag = true;
                }

                break;

            case 5:
                if (mSequence == eSeq_Control) {
                    anm_no = findGroupAnimator(9, 4);
                    mpGroupAnmController[anm_no]->start();

                    setForcusSE();
                    onFlag = true;
                }

                break;

            case 6:
                if (mSequence == eSeq_Control) {
                    anm_no = findGroupAnimator(10, 4);
                    mpGroupAnmController[anm_no]->start();

                    setForcusSE();
                    onFlag = true;
                }

                break;

            case 7:
                if (mSequence == eSeq_Cmn) {
                    anm_no = findGroupAnimator(17, 11);
                    mpGroupAnmController[anm_no]->start();

                    setForcusSE();
                    onFlag = true;
                }

                break;

            case 8:
                if (mSequence == eSeq_Cmn) {
                    anm_no = findGroupAnimator(18, 11);
                    mpGroupAnmController[anm_no]->start();

                    setForcusSE();
                    onFlag = true;
                }

                break;
            }
        }
    }

    if (btn_no == mButtonNum + 1 || btn_no == mButtonNum + 9) {
        mPaneCounter[mButtonNum + 1]++;
        mPaneCounter[mButtonNum + 9]++;
    } else {
        mPaneCounter[btn_no]++;
    }

    if (onFlag && pCon) {
        if (!getController(pCon->chan)->isRumbling() &&
            mOnPaneVibWaitFrame[pCon->chan] <= 0.0f) {
            mOnPaneVibFrame[pCon->chan] = 3.0f;
            getController(pCon->chan)->startMotor();
        }
    }
}

void HomeButton::startLeftEvent(const char* pName) {
    int anm_no;
    int btn_no = getPaneNo(pName);

    if (0 < mPaneCounter[btn_no]) {
        if (btn_no == mButtonNum + 1 || btn_no == mButtonNum + 9) {
            mPaneCounter[mButtonNum + 1]--;
            mPaneCounter[mButtonNum + 9]--;
        } else {
            mPaneCounter[btn_no]--;
        }
    }

    if (isActive() && btn_no != -1 && !mPaneCounter[btn_no]) {
        if (mSequence != eSeq_Cmn && btn_no < mButtonNum) {
            anm_no = findAnimator(btn_no, 2);
            mpAnmController[anm_no]->start();
        } else {
            switch (btn_no - mButtonNum) {
            case 0:
                if (mSequence == eSeq_Normal) {
                    if (isUpBarActive()) {
                        mpPairGroupAnmController[12]->start();
                        mBar0AnmRevHold = 12;
                        mBar0AnmRev = 0;
                    } else {
                        mBar0AnmRev = 12;
                    }
                }

                break;

            case 1:
            case 9:
                if (mSequence == eSeq_Normal) {
                    anm_no = findGroupAnimator(5, 3);

                    if (isDownBarActive()) {
                        mpGroupAnmController[anm_no]->start();
                        mBar1AnmRevHold = anm_no;
                        mBar1AnmRev = 0;
                    } else {
                        mBar1AnmRev = anm_no;
                    }
                } else if (mSequence == eSeq_Control) {
                    anm_no = findGroupAnimator(5, 20);

                    if (isDownBarActive()) {
                        mpGroupAnmController[anm_no]->start();
                        mBar1AnmRevHold = anm_no;
                        mBar1AnmRev = 0;
                    } else {
                        mBar1AnmRev = anm_no;
                    }
                }

                break;

            case 2:
                if (mSequence == eSeq_Control) {
                    anm_no = findGroupAnimator(6, 7);
                    mpGroupAnmController[anm_no]->start();
                }

                break;

            case 3:
                if (mSequence == eSeq_Control) {
                    anm_no = findGroupAnimator(7, 7);
                    mpGroupAnmController[anm_no]->start();
                }

                break;

            case 4:
                if (mSequence == eSeq_Control) {
                    anm_no = findGroupAnimator(8, 7);
                    mpGroupAnmController[anm_no]->start();
                }

                break;

            case 5:
                if (mSequence == eSeq_Control) {
                    anm_no = findGroupAnimator(9, 7);
                    mpGroupAnmController[anm_no]->start();
                }

                break;

            case 6:
                if (mSequence == eSeq_Control) {
                    anm_no = findGroupAnimator(10, 7);
                    mpGroupAnmController[anm_no]->start();
                }

                break;

            case 7:
                if (mSequence == eSeq_Cmn) {
                    anm_no = findGroupAnimator(17, 12);
                    mpGroupAnmController[anm_no]->start();
                }

                break;

            case 8:
                if (mSequence == eSeq_Cmn) {
                    anm_no = findGroupAnimator(18, 12);
                    mpGroupAnmController[anm_no]->start();
                }

                break;
            }
        }
    }
}

void HomeButton::startTrigEvent(const char* pName) {
    int anm_no;
    int btn_no;

    btn_no = getPaneNo(pName);

    if (isActive() && btn_no != -1) {
        if (mSequence == eSeq_Normal && btn_no < mButtonNum) {
            mSelectBtnNum = static_cast<HBMSelectBtnNum>(btn_no + 1);

            mSelectAnmNum = findAnimator(btn_no + 4, 1);
            mpAnmController[mSelectAnmNum]->start();
            play_sound(5);

            if (mDialogFlag[btn_no]) {
                mState = 11;
                mSequence = eSeq_Cmn;

                nw4r::lyt::Pane* p_pane =
                    mpLayout->GetRootPane()->FindPaneByName(
                        scFuncTextPaneName[2], true);

                nw4r::lyt::TextBox* p_text =
                    nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(p_pane);

                u16 len;
                if (mpHBInfo->messageFlag & btn_no + 1) {
                    for (len = 0; true; len++) {
                        // U+FF1F FULLWIDTH QUESTION MARK
                        if (mpText[mpHBInfo->region][btn_no + 2][len] == L'？')
                            break;

                        // U+003F QUESTION MARK
                        if (mpText[mpHBInfo->region][btn_no + 2][len] == L'\?')
                            break;
                    }
                } else {
                    for (len = 0; true; len++) {
                        // U+0022 QUOTATION MARK
                        if (mpText[mpHBInfo->region][btn_no + 2][len + 1] ==
                            L'\"')
                            break;
                    }
                }

                p_text->SetString(mpText[mpHBInfo->region][btn_no + 2], 0,
                                  ++len);

                mpLayout->GetRootPane()
                    ->FindPaneByName(scFuncTextPaneName[2], true)
                    ->SetVisible(true);
            } else {
                mState = 15;
            }
        } else
            switch (btn_no - mButtonNum) {
            case 0:
                if (mpPairGroupAnmController[12]->isPlaying())
                    mpPairGroupAnmController[12]->stop();

                if (mpPairGroupAnmController[3]->isPlaying())
                    mpPairGroupAnmController[3]->stop();

                mSelectBtnNum = HBM_SELECT_HOMEBTN;
                mSelectAnmNum = 4;
                mpPairGroupAnmController[mSelectAnmNum]->start();

                mState = 14;
                play_sound(1);

                break;

            case 1:
            case 9:
                if (mSequence == eSeq_Control) {
                    mpPairGroupAnmController[4]->start();
                    mpPairGroupAnmController[11]->start();

                    mSelectAnmNum = 2;
                    mpPairGroupAnmController[mSelectAnmNum]->start();

                    mState = 10;
                    mSequence = eSeq_Normal;
                    play_sound(8);
                } else if (mSequence == eSeq_Normal) {
                    mpPairGroupAnmController[1]->start();
                    mSelectAnmNum = 9;
                    mpPairGroupAnmController[mSelectAnmNum]->start();
                    mState = 10;

                    for (int i = 2; i < 7; i++) {
                        mpLayout->GetRootPane()
                            ->FindPaneByName(scFuncTouchPaneName[i], true)
                            ->SetVisible(true);
                    }

                    mSequence = eSeq_Control;
                    play_sound(5);
                }

                break;

            case 2:
                if (mVolumeNum > 0) {
                    mVolumeNum--;

                    anm_no = findGroupAnimator(mVolumeNum + 21, 10);
                    mpGroupAnmController[anm_no]->stop();

                    anm_no = findGroupAnimator(mVolumeNum + 21, 9);
                    mpGroupAnmController[anm_no]->start();

                    if (mVolumeNum == 0) {
                        play_sound(12);

                        for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
                            getController(i)->setSpeakerVol(mVolumeNum / 10.0f);
                            getController(i)->playSound(mpSoundArchivePlayer,
                                                        1);
                        }
                    } else {
                        play_sound(10);

                        for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
                            getController(i)->setSpeakerVol(mVolumeNum / 10.0f);
                            getController(i)->playSound(mpSoundArchivePlayer,
                                                        1);
                        }
                    }

                    anm_no = findGroupAnimator(11, 5);
                    mpGroupAnmController[anm_no]->start();
                } else {
                    play_sound(13);
                }

                break;

            case 3:
                if (mVolumeNum < 10) {
                    anm_no = findGroupAnimator(mVolumeNum + 21, 9);
                    mpGroupAnmController[anm_no]->stop();

                    anm_no = findGroupAnimator(mVolumeNum + 21, 10);
                    mpGroupAnmController[anm_no]->start();

                    mVolumeNum++;

                    if (mVolumeNum == 10) {
                        play_sound(11);

                        for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
                            getController(i)->setSpeakerVol(mVolumeNum / 10.0f);
                            getController(i)->playSound(mpSoundArchivePlayer,
                                                        1);
                        }
                    } else {
                        play_sound(9);

                        for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
                            getController(i)->setSpeakerVol(mVolumeNum / 10.0f);
                            getController(i)->playSound(mpSoundArchivePlayer,
                                                        1);
                        }
                    }

                    anm_no = findGroupAnimator(12, 5);
                    mpGroupAnmController[anm_no]->start();
                } else {
                    play_sound(13);
                }

                break;

            case 4:
                if (!mVibFlag) {
                    mVibFlag = true;

                    setVibFlag(mVibFlag);

                    anm_no = findGroupAnimator(14, 8);
                    mpGroupAnmController[anm_no]->start();

                    mSelectAnmNum = findGroupAnimator(16, 6);
                    mpGroupAnmController[mSelectAnmNum]->start();

                    play_sound(14);
                } else {
                    mSelectAnmNum = findGroupAnimator(16, 14);
                    mpGroupAnmController[mSelectAnmNum]->start();

                    play_sound(13);
                }

                for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
                    getController(i)->startMotor();
                    mOnPaneVibFrame[i] = 0.0f;
                    mOnPaneVibWaitFrame[i] = 0.0f;
                }

                mState = 9;

                break;

            case 5:
                if (mVibFlag) {
                    mVibFlag = false;
                    setVibFlag(mVibFlag);

                    anm_no = findGroupAnimator(14, 6);
                    mpGroupAnmController[anm_no]->start();

                    mSelectAnmNum = findGroupAnimator(13, 8);
                    mpGroupAnmController[mSelectAnmNum]->start();

                    play_sound(15);
                } else {
                    play_sound(13);
                }

                mState = 9;

                break;

            case 6:
                mSelectAnmNum = findGroupAnimator(15, 5);
                mpGroupAnmController[mSelectAnmNum]->start();

                mState = 3;
                setReassignedFlag(true);

                for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
                    mOnPaneVibFrame[i] = 0.0f;
                    mOnPaneVibWaitFrame[i] = 0.0f;
                    getController(i)->stopMotor();
                    getController(i)->setEnableRumble(false);
                }

                mWaitStopMotorCount =
                    30.0f / getInstance()->getHBMDataInfo()->frameDelta;

                mpLayout->GetRootPane()
                    ->FindPaneByName(scFuncTextPaneName[0], true)
                    ->SetVisible(true);

                mpLayout->GetRootPane()
                    ->FindPaneByName(scFuncTextPaneName[1], true)
                    ->SetVisible(true);

                play_sound(5);
                play_sound(16);

                break;

            case 7:
                mSelectAnmNum = findGroupAnimator(19, 13);
                mpGroupAnmController[mSelectAnmNum]->start();

                mState = 13;
                mSequence = eSeq_Normal;

                if (mSelectBtnNum == HBM_SELECT_BTN1) {
                    play_sound(2);
                } else if (mSelectBtnNum == HBM_SELECT_BTN2) {
                    play_sound(3);
                }

                break;

            case 8:
                mSelectAnmNum = findGroupAnimator(20, 13);
                mpGroupAnmController[mSelectAnmNum]->start();

                mState = 13;
                mSelectBtnNum = HBM_SELECT_NULL;

                mSequence = eSeq_Normal;
                play_sound(6);
                break;
            }
    }
}

void HomeButton::reset_btn() {
    int anm_no;

    for (int i = 0; i < mButtonNum; i++) {
        if (!mPaneCounter[i])
            continue;

        anm_no = findAnimator(i, 2);
        mpAnmController[anm_no]->start();
        mPaneCounter[i] = 0;
    }

    if (mPaneCounter[mButtonNum]) {
        mpPairGroupAnmController[12]->start();
        mPaneCounter[mButtonNum + 1] = 0;
    }

    if (mPaneCounter[mButtonNum + 1]) {
        if (mSequence == eSeq_Control) {
            if (!mMsgCount) {
                anm_no = findGroupAnimator(5, 20);
                mpGroupAnmController[anm_no]->start();
                mPaneCounter[mButtonNum] = 0;
            }
        } else {
            anm_no = findGroupAnimator(5, 3);
            mpGroupAnmController[anm_no]->start();
            mPaneCounter[mButtonNum] = 0;
        }
    }
}

void HomeButton::reset_control() {
    int anm_no;

    for (int i = 0; i < 5; i++) {
        anm_no = findGroupAnimator(i + 6, 7);
        mpGroupAnmController[anm_no]->start();
    }
}

void HomeButton::reset_window() {
    int anm_no;

    anm_no = findGroupAnimator(17, 12);
    mpGroupAnmController[anm_no]->start();

    anm_no = findGroupAnimator(18, 12);
    mpGroupAnmController[anm_no]->start();
}

void HomeButton::reset_battery() {
    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        for (int j = 0; j < 4; j++) {
            mpLayout->GetRootPane()
                ->FindPaneByName(scBatteryPaneName[i][j], true)
                ->SetVisible(false);
        }
    }
}

void HomeButton::reset_guiManager(int num) {
    if (num < 0) // presumably a -1 = all case
    {
        for (int i = 0; i < 8; i++)
            mpPaneManager->update(i, -10000.0f, -10000.0f, 0, 0, 0, NULL);
    } else {
        mpPaneManager->update(num, -10000.0f, -10000.0f, 0, 0, 0, NULL);
    }
}

bool HomeButton::isActive() const {
    return mState == 2;
}

bool HomeButton::isUpBarActive() const {
    bool flag = true;

    if (!isActive() || mpPairGroupAnmController[12]->isPlaying() ||
        mpPairGroupAnmController[3]->isPlaying()) {
        flag = false;
    }

    return flag;
}

bool HomeButton::isDownBarActive() {
    bool flag = true;

    int anm_no[4];
    anm_no[0] = findGroupAnimator(4, 2);
    anm_no[1] = findGroupAnimator(5, 3);
    anm_no[2] = findGroupAnimator(4, 19);
    anm_no[3] = findGroupAnimator(5, 20);

    if (!isActive() || mpGroupAnmController[anm_no[0]]->isPlaying() ||
        mpGroupAnmController[anm_no[1]]->isPlaying() ||
        mpGroupAnmController[anm_no[2]]->isPlaying() ||
        mpGroupAnmController[anm_no[3]]->isPlaying()) {
        flag = false;
    }

    return flag;
}

int HomeButton::getPaneNo(const char* pName) {
    int ret = -1;

    for (int i = 0; i < mButtonNum; i++) {
        if (!std::strcmp(pName, getPaneName(i))) {
            ret = i;
            break;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (!std::strcmp(pName, getFuncPaneName(i))) {
            ret = i + mButtonNum;
            break;
        }
    }

    return ret;
}

int HomeButton::findAnimator(int pane, int anm) {
    for (int i = 0; i < mAnmNum; i++) {
        if (scAnmTable[i].pane == pane && scAnmTable[i].anm == anm)
            return i;
    }

    return -1;
}

int HomeButton::findGroupAnimator(int pane, int anm) {
    for (int i = 0; i < (int)ARRAY_SIZE(scGroupAnmTable); i++) {
        if (scGroupAnmTable[i].pane == pane && scGroupAnmTable[i].anm == anm)
            return i;
    }

    return -1;
}

HBMSelectBtnNum HomeButton::getSelectBtnNum() {
    // Interesting
    if (mState != 18)
        return HBM_SELECT_NULL;
    else
        return mSelectBtnNum;
}

void HomeButton::setForcusSE() {
    if (mForcusSEWaitTime <= 2)
        return;

    play_sound(4);
    mForcusSEWaitTime = 0;
}

void HomeButton::setAdjustFlag(int flag) {
    nw4r::math::VEC2 sc_v;

    mAdjustFlag = static_cast<bool>(flag);
    mDrawInfo.SetLocationAdjust(mAdjustFlag);

    if (mAdjustFlag) {
        sc_v = nw4r::math::VEC2(mpHBInfo->adjust.x, mpHBInfo->adjust.y);
        mpLayout->GetRootPane()->SetScale(sc_v);

        if (!mpHBInfo->cursor) {
            for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++)
                mpCursorLayout[i]->GetRootPane()->SetScale(sc_v);
        }
    } else {
        sc_v = nw4r::math::VEC2(1.0f, 1.0f);
        mpLayout->GetRootPane()->SetScale(sc_v);

        if (!mpHBInfo->cursor) {
            for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++)
                mpCursorLayout[i]->GetRootPane()->SetScale(sc_v);
        }
    }

    GXSetCullMode(GX_CULL_NONE);
}

void HomeButton::setVolume(int vol) {
    WPADSetSpeakerVolume(vol * 12.7f);
}

int HomeButton::getVolume() {
    return WPADGetSpeakerVolume() * (1.0f / 12.7f) + 0.9f;
}

void HomeButton::setVibFlag(bool flag) {
    WPADEnableMotor(flag);
}

bool HomeButton::getVibFlag() {
    return WPADIsMotorEnabled();
}

void HomeButtonEventHandler::onEvent(u32 uID, u32 uEvent, void* pData) {
    gui::PaneComponent* p_panecpt = // force downcast
        static_cast<gui::PaneComponent*>(mpManager->getComponent(uID));

    const nw4r::lyt::Pane* pPane = p_panecpt->getPane();
    const char* pPaneName = pPane->GetName();

    HomeButton* p_hbtn = getHomeButton();
    HBController* pCon = static_cast<HBController*>(pData);

    switch (uEvent) {
    case 1:
        p_hbtn->startPointEvent(pPaneName, pData);
        break;

    case 2:
        p_hbtn->startLeftEvent(pPaneName);
        break;

    case 0:
        if ((pCon->trig & WPAD_BUTTON_A) || (pCon->trig & (1 << 24))) {
            p_hbtn->startTrigEvent(pPaneName);
        }

        break;
    }
}

void HomeButton::startBlackOut() {
    if (!mStartBlackOutFlag) {
        mStartBlackOutFlag = true;

        for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++)
            mpController[i]->stopMotor();

        mForceSttInitProcFlag = false;
        mForceSttFadeInProcFlag = false;
        mForceStopSyncFlag = false;
        mForceEndMsgAnmFlag = false;

        switch (mState) {
        case 0:
            mForceSttInitProcFlag = true;
            // FALLTHROUGH

        case 1:
            mForceSttFadeInProcFlag = true;
            break;

        case 3:
        case 5:
        case 6:
        case 7:
            if ((mState == 3 && mSelectAnmNum == 5) ||
                (mState == 5 && !mSimpleSyncFlag)) {
                OSCancelAlarm(&mSimpleSyncAlarm);
                WPADSetSimpleSyncCallback(mSimpleSyncCallback);
            } else if (!mEndSimpleSyncFlag && mState > 3) {
                mForceStopSyncFlag = true;

                if (!WPADStopSimpleSync()) {
                    OSCancelAlarm(&mSimpleSyncAlarm);

                    OSSetAlarmUserData(&mSimpleSyncAlarm,
                                       reinterpret_cast<void*>(1));
                    OSSetAlarm(&mSimpleSyncAlarm, OS_MSEC_TO_TICKS(100),
                               &RetrySimpleSyncCallback);
                }
            } else {
                WPADSetSimpleSyncCallback(mSimpleSyncCallback);
            }

            mForceEndMsgAnmFlag = true;
            break;
        }

        mState = 19;
        mFader.start();

        mSelectBtnNum = HBM_SELECT_BTN2;

        f32 maxFrame = mFader.getMaxFrame();
        mFadeOutSeTime = maxFrame;

        if (mpHBInfo->sound_callback)
            mpHBInfo->sound_callback(3, maxFrame);
    }
}

void HomeButton::BlackFader::init(int maxFrame) {
    frame_ = 0;
    maxFrame_ = maxFrame;
    state_ = 0;
}

void HomeButton::BlackFader::calc() {
    if (state_ == 1)
        frame_++;
    else if (state_ == 2)
        frame_--;

    if (frame_ < 0)
        frame_ = 0;
    else if (frame_ > maxFrame_)
        frame_ = maxFrame_;
}

bool HomeButton::BlackFader::isDone() {
    if (state_ == 1) {
        if (frame_ == maxFrame_)
            return true;
    }

    if (state_ == 2) {
        if (frame_ == 0)
            return true;
    }

    return false;
}

static void initgx() {
    Mtx view_mtx;

    PSMTXIdentity(view_mtx);
    GXLoadPosMtxImm(view_mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGB, GX_F32, 0);

    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL,
                  GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL,
                  GX_DF_NONE, GX_AF_NONE);

    GXSetNumTexGens(0);

    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                  GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                    GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                    GX_TRUE, GX_TEVPREV);

    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetDispCopyGamma(0);

    GXSetNumIndStages(0);
    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE,
                          GX_CH_ALPHA);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);

    GXSetCullMode(GX_CULL_NONE);
}

static void drawBlackPlate(f32 left, f32 top, f32 right, f32 bottom,
                           GXColor clr) {
    GXSetTevColor(GX_TEVREG0, clr);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    {
        GXPosition2f32(left, top);
        GXPosition2f32(left, bottom);
        GXPosition2f32(right, bottom);
        GXPosition2f32(right, top);
    }
    GXEnd();
}

void HomeButton::BlackFader::draw() {
    u8 alpha = frame_ * 255 / maxFrame_;

    initgx();
    GXColor clr = {red_, green_, blue_, alpha};
    drawBlackPlate(-1000.0f, -1000.0f, 1000.0f, 1000.0f, clr);
}

const int HomeButton::scSoundHeapSize_but2 = 0x60000;
const int HomeButton::scSoundHeapSize_but3 = 0x6f800;
const int HomeButton::scSoundThreadPrio = 4;
const int HomeButton::scDvdThreadPrio = 3;

void HomeButton::update_sound() {
    if (mpSoundArchivePlayer != NULL) {
        nw4r::ut::detail::AutoLock<OSMutex> lock(sMutex);
        mpSoundArchivePlayer->Update();
    }

    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++)
        mpController[i]->updateSound();
}

void HomeButton::play_sound(int id) {
    int ret = 0;

    if (mpHBInfo->sound_callback != NULL) {
        ret = mpHBInfo->sound_callback(5, id);
    }

    if (ret != 0 || mpSoundArchivePlayer == NULL || mpSoundHandle == NULL) {
        return;
    }

    nw4r::ut::detail::AutoLock<OSMutex> lock(sMutex);
    mpSoundHandle->DetachSound();
    mpSoundArchivePlayer->StartSound(mpSoundHandle, id);
}

void HomeButton::fadeout_sound(f32 gain) {
    if (mSelectBtnNum == HBM_SELECT_BTN3)
        return;

    if (mEndInitSoundFlag)
        AXSetAuxAReturnVolume(gain * 32768.0f);

    if (mpSoundArchivePlayer != NULL) {
        nw4r::ut::detail::AutoLock<OSMutex> lock(sMutex);

        for (int i = 0; i < mpSoundArchivePlayer->GetSoundPlayerCount(); i++) {
            mpSoundArchivePlayer->GetSoundPlayer(i).SetVolume(gain);
        }
    }
}

} // namespace homebutton
