#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <egg/core.h>
#include <egg/gfxe.h>

#include <revolution/OS.h>
#include <revolution/SC.h>
#include <revolution/VI.h>

void RPSysSystem::initialize() {
    EGG::BaseSystem::configure((EGG::ConfigurationData*)&sConfigData);
    DVDInit();

    //! The below is pretty much ripped from EGG::ConfigurationData::initMemory.
    //! The order of some items has changed, which is why it is not just
    //! inlined.

    void* pMem1Lo = OSGetMEM1ArenaLo();
    void* pMem1Hi = OSGetMEM1ArenaHi();
    void* pMem2Lo = OSGetMEM2ArenaLo();
    void* pMem2Hi = OSGetMEM2ArenaHi();

    void* pMem1Arena = OSInitAlloc(pMem1Lo, pMem1Hi, 2);
    void* pMem2Arena = OSInitAlloc(pMem2Lo, pMem2Hi, 2);

    sConfigData.mCodeEnd = ROUND_UP_PTR(pMem1Arena, 32);
    sConfigData.mCodeStart =
        static_cast<OSBootInfo*>(OSPhysicalToCached(OS_PHYS_BOOT_INFO));
    sConfigData.mMem1Start = ROUND_UP_PTR(pMem1Arena, 32);
    sConfigData.mMem1End = ROUND_DOWN_PTR(pMem1Hi, 32);
    sConfigData.mMem2Start = ROUND_UP_PTR(pMem2Arena, 32);
    sConfigData.mMem2End = ROUND_DOWN_PTR(pMem2Hi, 32);
    sConfigData.mMemSize = sConfigData.mCodeStart->physMemSize;

    OSSetMEM1ArenaLo(pMem1Arena);
    OSSetMEM1ArenaHi(pMem1Arena);
    OSSetMEM2ArenaLo(pMem2Arena);
    OSSetMEM2ArenaHi(pMem2Arena);

    EGG::Heap::initialize();
    u32 heapSizeMem1 = nw4r::ut::GetOffsetFromPtr(sConfigData.mMem1Start,
                                                  sConfigData.mMem1End);
    sConfigData.mRootHeapMem1 = EGG::ExpHeap::create(pMem1Lo, heapSizeMem1);
    u32 heapSizeMem2 = nw4r::ut::GetOffsetFromPtr(sConfigData.mMem2Start,
                                                  sConfigData.mMem2End);
    sConfigData.mRootHeapMem2 = EGG::ExpHeap::create(pMem2Lo, heapSizeMem2);
    sConfigData.mRootHeapDebug = NULL; // unlike initMemory, this is hardcoded
    sConfigData.mSystemHeap = EGG::ExpHeap::create(
        sConfigData.mSystemHeapSize, sConfigData.mRootHeapMem1, 0);
    sConfigData.mSystemHeap->becomeCurrentHeap();
    EGG::GraphicsFifo::create(0x80000u, NULL);
    setupTVMode();
    setupRenderMode();

    EGG::DvdFile::initialize();
    EGG::Exception::create(64, 32, 4, 0);
    // EGG::Exception::setPadInfo(pointer); pointer needs to be defined
    sConfigData.mRootHeapMem2->becomeCurrentHeap();
}

void RPSysSystem::create() {
    //! Requires different code for rev 0. Doesn't match there.
    spInstance = new (sConfigData.GetSystemHeap()) RPSysSystem;
}

void RPSysSystem::mainLoop() {
    while (TRUE) {
        sConfigData.mDisplay->beginFrame();
        sConfigData.mPerfView->measureBeginFrame();
        RP_GET_INSTANCE(RPSysDvdStatus)->update();
        RP_GET_INSTANCE(RPSysSceneMgr)->getCurrentSceneRP();
    }
}

void RPSysSystem::setupTVMode() {
    int i;

    VIInit();
    for (i = 0; i < 60; i++) {
        if (SCCheckStatus() == SC_STATUS_OK) {
            break;
        }
        VIWaitForRetrace();
    }
    if (SCGetAspectRatio() == SC_ASPECT_WIDE) {
        EGG::Screen::SetTVMode(EGG::Screen::TV_MODE_WIDE);
    } else {
        EGG::Screen::SetTVMode(EGG::Screen::TV_MODE_STD);
    }
}

RPSysSceneCreator::ESceneID RPSysSystem::getBootScene() {
#if defined(PACK_SPORTS)
    return RPSysSceneCreator::ESceneID_RPSportsPackTitleScene;
#elif defined(PACK_PARTY)
    return RPSysSceneCreator::ESceneID_RPPartyPackTitleScene;
#endif
}

void RPSysSystem::startLoadCount() {
    mLoadCount = 0;
}

const char* RPSysSystem::getTimeStampString() {
    return mpTimeStampString;
}

/**
 * @brief Constructor
 */

RPSysSystem::RPSysSystem() : mEffectWorkSize(0) {
    mpResourceHeap = NULL;
    mpReserveHeap = NULL;
    mpAssertHeap = NULL;
    HEAP_0x14 = NULL;
    mpCurrentHeap = NULL;
    OSInitMutex(&mCurrentHeapMutex);
    mpNandThread = NULL;
    mpDvdThread = NULL;
    mpWc24Thread = NULL;
    mNandEndMessage = FOURCC('n', 'a', 'n', 'd');
    mDvdEndMessage = FOURCC('d', 'i', 's', 'k');  // "disk"
    mWc24EndMessage = FOURCC('w', 'c', '2', '4'); // "wc24"
    mFrameRate = 1;
    sConfigData.GetDisplay()->setFrameRate(mFrameRate);
    mLoadCount = 0;
    mpTimeStampString = NULL;
    mFrameTime = (f32)mFrameRate / 60.0f;
}

void RPSysSystem::setupLocalSettings() {
    u8 sysLanguage = SCGetLanguage();

    if (sysLanguage == SC_LANG_EN) {
        RP_GET_INSTANCE(RPSysProjectLocal)
            ->setLocale(RPSysProjectLocal::EArea_USA);
        RP_GET_INSTANCE(RPSysProjectLocal)
            ->setLanguage(RPSysProjectLocal::EArea_USA);
    } else if (sysLanguage == SC_LANG_FR) {
        RP_GET_INSTANCE(RPSysProjectLocal)
            ->setLocale(RPSysProjectLocal::EArea_USA);
        RP_GET_INSTANCE(RPSysProjectLocal)
            ->setLanguage(RPSysProjectLocal::EArea_France);
    } else if (sysLanguage == SC_LANG_SP) {
        RP_GET_INSTANCE(RPSysProjectLocal)
            ->setLocale(RPSysProjectLocal::EArea_USA);
        RP_GET_INSTANCE(RPSysProjectLocal)
            ->setLanguage(RPSysProjectLocal::EArea_Spain);
    }
    //! Requires ifdef for non Americas versions
    else {
        RP_GET_INSTANCE(RPSysProjectLocal)
            ->setLocale(RPSysProjectLocal::EArea_USA);
        RP_GET_INSTANCE(RPSysProjectLocal)
            ->setLanguage(RPSysProjectLocal::EArea_USA);
    }
}

/**
 * @brief Controls whether the game restarts or returns to the Wii Menu upon a
 * soft reset.
 */
void RPSysSystem::softResetCallBack() {
    if (RP_GET_INSTANCE(RPSysDvdStatus)->isErrorOccured()) {
        RP_GET_INSTANCE(RPSysSceneMgr)->returnToMenu(FALSE);

    } else {
        VIEnableDimming(FALSE);

        if (RP_GET_INSTANCE(RPSysSceneMgr)->isNormalState() &&
            !RP_GET_INSTANCE(RPSysHomeMenuMgr)->softReset()) {

            RP_GET_INSTANCE(RPSysSceneMgr)->softReset(FALSE);
        }
    }
}

void RPSysSystem::shutdownSystemCallBack() {
    RP_GET_INSTANCE(RPSysSceneMgr)->shutdownSystem(FALSE);
}
