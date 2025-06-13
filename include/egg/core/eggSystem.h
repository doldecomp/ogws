#ifndef EGG_CORE_SYSTEM_H
#define EGG_CORE_SYSTEM_H
#include <egg/types_egg.h>

namespace EGG {

// Forward declarations
class Display;
class Heap;
class IAudioMgr;
class PerformanceView;
class SceneManager;
class Video;
class XfbManager;

class ConfigurationData {
public:
    explicit ConfigurationData(u32 systemHeapSize)
        : mSystemHeapSize(systemHeapSize) {}

    virtual Video* getVideo() = 0;              // at 0x8
    virtual Heap* getSystemHeap() = 0;          // at 0xC
    virtual Display* getDisplay() = 0;          // at 0x10
    virtual XfbManager* getXfbMgr() = 0;        // at 0x14
    virtual PerformanceView* getPerfView() = 0; // at 0x18
    virtual SceneManager* getSceneMgr() = 0;    // at 0x1C
    virtual IAudioMgr* getAudioMgr() = 0;       // at 0x20

    virtual void onBeginFrame() {} // at 0x24
    virtual void onEndFrame() {}   // at 0x28
    virtual void initMemory();     // at 0x2C
    virtual void run();            // at 0x30

    Heap* getRootHeapMem1() {
        return mRootHeapMem1;
    }
    Heap* getRootHeapMem2() {
        return mRootHeapMem2;
    }
    Heap* getRootHeapDebug() {
        return mRootHeapDebug;
    }

private:
    void* mMem1Start;     // at 0x4
    void* mMem1End;       // at 0x8
    void* mMem2Start;     // at 0xC
    void* mMem2End;       // at 0x10
    u32 mMemorySize;      // at 0x14
    Heap* mRootHeapMem1;  // at 0x18
    Heap* mRootHeapMem2;  // at 0x1C
    Heap* mRootHeapDebug; // at 0x20

protected:
    Heap* mSystemHeap;     // at 0x24
    Thread* mParentThread; // at 0x28
    void* mCodeStart;      // at 0x2C
    void* mCodeEnd;        // at 0x30
    u32 mSystemHeapSize;   // at 0x34
};

class BaseSystem {
public:
    static void configure(ConfigurationData* pConfigData) {
        mConfigData = pConfigData;
    }

    static Video* getVideo() {
        return mConfigData->getVideo();
    }

    static Heap* getRootHeapMem1() {
        return mConfigData->getRootHeapMem1();
    }
    static Heap* getRootHeapMem2() {
        return mConfigData->getRootHeapMem2();
    }
    static Heap* getRootHeapDebug() {
        return mConfigData->getRootHeapDebug();
    }

    static Heap* getSystemHeap() {
        return mConfigData->getSystemHeap();
    }

    static Display* getDisplay() {
        return mConfigData->getDisplay();
    }

    static XfbManager* getXfbManager() {
        return mConfigData->getXfbMgr();
    }

    static PerformanceView* getPerfView() {
        return mConfigData->getPerfView();
    }

    static SceneManager* getSceneManager() {
        return mConfigData->getSceneMgr();
    }

    static IAudioMgr* getAudioManager() {
        return mConfigData->getAudioMgr();
    }

private:
    static ConfigurationData* mConfigData;
};

} // namespace EGG

#endif
