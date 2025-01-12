#ifndef NW4R_EF_MEMORY_MANAGER_TMP_H
#define NW4R_EF_MEMORY_MANAGER_TMP_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/ef_effect.h>
#include <nw4r/ef/ef_emitter.h>
#include <nw4r/ef/ef_memorymanager.h>
#include <nw4r/ef/ef_particle.h>
#include <nw4r/ef/ef_particlemanager.h>

#include <nw4r/ut.h>

namespace nw4r {
namespace ef {

template <typename T> class MemoryManagerTmp {
private:
    T* mHead;             // at 0x0
    ut::List mFreeList;   // at 0x4
    ut::List mLeasedList; // at 0x10
    int mStructSize;      // at 0x1C

public:
    virtual void AssignObjectID(void* pObject);
};

class MemoryManager : public MemoryManagerBase {
private:
    struct MemInfo {
        MemInfo* prev;      // at 0x0
        MemInfo* next;      // at 0x4
        MemInfo* chainPrev; // at 0x8
        MemInfo* chainNext; // at 0xC
        u32 size;           // at 0x10
        bool active;        // at 0x14
        u8 PADDING_0x15[3]; // at 0x15
    };

private:
    int mMaxEffect;                      // at 0x4
    MemoryManagerTmp<Effect>* mEffectOM; // at 0x8

    int mMaxEmitter;                       // at 0xC
    MemoryManagerTmp<Emitter>* mEmitterOM; // at 0x10

    int mMaxParticleManager;                               // at 0x14
    MemoryManagerTmp<ParticleManager>* mParticleManagerOM; // at 0x18

    int mMaxParticle;                        // at 0x1C
    MemoryManagerTmp<Particle>* mParticleOM; // at 0x20

    void* mHeapStartAddr; // at 0x24
    void* mHeapEndAddr;   // at 0x28

    MemInfo* mActiveMem;   // at 0x2C
    MemInfo* mFreeMem;     // at 0x30
    MemInfo* mFreeMemTail; // at 0x34
    MemInfo* mAllChain;    // at 0x38

public:
    // TODO: Crazy big implementation...

    MemoryManager() {}
    virtual ~MemoryManager() {} // at 0x8

    virtual void GarbageCollection() = 0; // at 0xC

    virtual Effect* AllocEffect() = 0;          // at 0x10
    virtual void FreeEffect(void* pObject) = 0; // at 0x14
    virtual u32 GetNumAllocEffect() const = 0;  // at 0x18
    virtual u32 GetNumActiveEffect() const = 0; // at 0x1C
    virtual u32 GetNumFreeEffect() const = 0;   // at 0x20

    virtual Emitter* AllocEmitter() = 0;         // at 0x24
    virtual void FreeEmitter(void* pObject) = 0; // at 0x28
    virtual u32 GetNumAllocEmitter() const = 0;  // at 0x2C
    virtual u32 GetNumActiveEmitter() const = 0; // at 0x30
    virtual u32 GetNumFreeEmitter() const = 0;   // at 0x34

    virtual ParticleManager* AllocParticleManager() = 0; // at 0x38
    virtual void FreeParticleManager(void* pObject) = 0; // at 0x3C
    virtual u32 GetNumAllocParticleManager() const = 0;  // at 0x40
    virtual u32 GetNumActiveParticleManager() const = 0; // at 0x44
    virtual u32 GetNumFreeParticleManager() const = 0;   // at 0x48

    virtual Particle* AllocParticle() = 0;        // at 0x4C
    virtual void FreeParticle(void* pObject) = 0; // at 0x50
    virtual u32 GetNumAllocParticle() const = 0;  // at 0x54
    virtual u32 GetNumActiveParticle() const = 0; // at 0x58
    virtual u32 GetNumFreeParticle() const = 0;   // at 0x5C

    virtual void* AllocHeap(u32 size) = 0; // at 0x60
};

} // namespace ef
} // namespace nw4r

#endif
