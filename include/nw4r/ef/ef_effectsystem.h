#ifndef NW4R_EF_EFFECT_SYSTEM_H
#define NW4R_EF_EFFECT_SYSTEM_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/ef_creationqueue.h>
#include <nw4r/ef/ef_random.h>

#include <nw4r/math.h>

namespace nw4r {
namespace ef {

// Forward declarations
class MemoryManagerBase;
class DrawOrderBase;
class DrawStrategyBuilder;
class EmitFormBuilder;
class ActivityList;

class EffectSystem {
private:
    MemoryManagerBase* mMemoryManager; // at 0x0

public:
    DrawOrderBase* mDrawOrderFunc;             // at 0x4
    DrawStrategyBuilder* mDrawStrategyBuilder; // at 0x8
    EmitFormBuilder* mEmitFormBuilder;         // at 0xC
    CreationQueue mCreationQueue;              // at 0x10
    u32 mMaxGroupID;                           // at 0xC014
    ActivityList* mActivityList;               // at 0xC018
    Random mRandom;                            // at 0xC01C
    math::VEC3 mProcessCameraPos;              // at 0xC020
    math::MTX34 mProcessCameraMtx;             // at 0xC02C
    f32 mProcessCameraFar;                     // at 0xC05C
    f32 mProcessCameraNear;                    // at 0xC060
    bool mXFFlushSafe;                         // at 0xC064

    static BOOL mDisplayVersion;
    static EffectSystem instance;

public:
    static EffectSystem* GetInstance();

    MemoryManagerBase* GetMemoryManager() const {
        return mMemoryManager;
    }
    void SetMemoryManager(MemoryManagerBase* pManager, u32 maxGroupID) {
        mMemoryManager = pManager;

        if (mMemoryManager != NULL) {
            Initialize(maxGroupID);
        } else {
            maxGroupID = 0;
            mActivityList = NULL;
        }
    }

    void SetXFFlushSafe(bool safe) {
        mXFFlushSafe = safe;
    }

    //////////////////////////////////////////////!

    bool Initialize(u32);
    bool Closing(Effect*);
    Effect* CreateEffect(const char*, u32, u16);
    bool RetireEffect(Effect*);
    u16 RetireEffectAll(u32);
    u16 RetireEmitterAll(u32);
    u16 RetireParticleAll(u32);

    void Calc(u32, bool);
    void Draw(const DrawInfo&, u32);

private:
    EffectSystem();
    ~EffectSystem();
};

} // namespace ef
} // namespace nw4r

#endif
