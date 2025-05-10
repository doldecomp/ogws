// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/audio.h>
#include <egg/core.h>
#include <egg/prim.h>

#include <nw4r/ut.h>

#include <revolution/OS.h>

namespace EGG {

ConfigurationData* BaseSystem::mConfigData = NULL;

void ConfigurationData::initMemory() {
    void* pMem1Lo = OSGetMEM1ArenaLo();
    void* pMem1Hi = OSGetMEM1ArenaHi();
    void* pMem2Lo = OSGetMEM2ArenaLo();
    void* pMem2Hi = OSGetMEM2ArenaHi();

    void* pMem1Arena = OSInitAlloc(pMem1Lo, pMem1Hi, 2);
    void* pMem2Arena = OSInitAlloc(pMem2Lo, pMem2Hi, 2);

    pMem1Lo = ROUND_UP_PTR(pMem1Arena, 32);
    pMem2Lo = ROUND_UP_PTR(pMem2Arena, 32);

    pMem1Arena = ROUND_DOWN_PTR(pMem1Hi, 32);
    pMem2Arena = ROUND_DOWN_PTR(pMem2Hi, 32);

    OSBootInfo* pBootInfo =
        static_cast<OSBootInfo*>(OSPhysicalToCached(OS_PHYS_BOOT_INFO));

    mCodeStart = pBootInfo;
    mCodeEnd = pMem1Lo;

    mMem1Start = pMem1Lo;
    mMem1End = pMem1Arena;

    mMem2Start = pMem2Lo;
    mMem2End = pMem2Arena;

    mMemorySize = pBootInfo->physMemSize;

    OSSetMEM1ArenaLo(pMem1Arena);
    OSSetMEM1ArenaHi(pMem1Arena);

    OSSetMEM2ArenaLo(pMem2Arena);
    OSSetMEM2ArenaHi(pMem2Arena);

    Heap::initialize();

    u32 heapSizeMem1 = nw4r::ut::GetOffsetFromPtr(mMem1Start, mMem1End);
    u32 heapSizeMem2 = nw4r::ut::GetOffsetFromPtr(mMem2Start, mMem2End);
    u32 heapSizeDebug;

    if (heapSizeMem2 >= OS_MEM_MB_TO_B(64)) {
        heapSizeDebug = OS_MEM_MB_TO_B(64);
        heapSizeMem2 = nw4r::ut::RoundDown(heapSizeMem2 - heapSizeDebug, 32);
    } else {
        heapSizeDebug = 0;
    }

    pMem1Lo = mMem1Start;
    pMem2Lo = mMem2Start;
    void* pMemDebugStart = static_cast<u8*>(pMem2Lo) + heapSizeMem2;

    EGG_PRINT("MEM1      : %p-> : (%.1fMBytes)\n", pMem1Lo,
              heapSizeMem1 / (1024.0f * 1024.0f));
    EGG_PRINT("MEM2(Rel) : %p-> : (%.1fMBytes)\n", pMem2Lo,
              heapSizeMem2 / (1024.0f * 1024.0f));
    EGG_PRINT("MEM2(Dbg) : %p-> : (%.1fMBytes)\n", pMemDebugStart,
              heapSizeDebug / (1024.0f * 1024.0f));

    mRootHeapMem1 = ExpHeap::create(pMem1Lo, heapSizeMem1);
    mRootHeapMem2 = ExpHeap::create(pMem2Lo, heapSizeMem2);

    if (heapSizeDebug > 0) {
        mRootHeapDebug = ExpHeap::create(pMemDebugStart, heapSizeDebug);
    } else {
        mRootHeapDebug = NULL;
    }

    mSystemHeap = ExpHeap::create(mSystemHeapSize, mRootHeapMem1);
    mSystemHeap->becomeCurrentHeap();
}

void ConfigurationData::run() {
    CoreControllerMgr* pControllerMgr = CoreControllerMgr::instance();

    while (true) {
        // Measure frame timing
        getDisplay()->beginFrame();
        onBeginFrame();
        getPerfView()->measureBeginFrame();
        {
            // Controller polling
            pControllerMgr->beginFrame();
            {
                // Render frame
                getDisplay()->beginRender();
                getPerfView()->measureBeginRender();
                {
                    getSceneMgr()->draw();
                    getPerfView()->draw();
                }
                getPerfView()->measureEndRender();
                getDisplay()->endRender();

                // Run scene logic
                getSceneMgr()->calc();
            }
            pControllerMgr->endFrame();

            // Run audio logic
            if (getAudioMgr() != NULL) {
                getAudioMgr()->calc();
            }
        }
        getDisplay()->endFrame();
        onEndFrame();
        getPerfView()->measureEndFrame();
    }
}

// clang-format off
DECOMP_FORCEACTIVE(eggSystem_cpp,
                  "mem == 0 || mem == 1");
// clang-format on

} // namespace EGG
