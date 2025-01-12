#ifndef NW4R_EF_MEMORY_MANAGER_H
#define NW4R_EF_MEMORY_MANAGER_H
#include <nw4r/types_nw4r.h>

namespace nw4r {
namespace ef {

class MemoryManagerBase {
public:
    MemoryManagerBase() {}
    virtual ~MemoryManagerBase() {} // at 0x8

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
