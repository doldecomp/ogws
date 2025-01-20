#ifndef NW4R_EF_CREATION_QUEUE_H
#define NW4R_EF_CREATION_QUEUE_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/ef_emitter.h>
#include <nw4r/ef/ef_types.h>

namespace nw4r {
namespace ef {

struct CreationQueue {
private:
    struct CreationQueueData {
        enum Type { TYPE_PARTICLE, TYPE_EMITTER };

        u8 mType;                              // at 0x0
        u8 mFlags;                             // at 0x1
        u16 mCalcRemain;                       // at 0x2
        EmitterInheritSetting mInheritSetting; // at 0x4
        Particle* mReferenceParticle;          // at 0xC
        EmitterResource* mEmitterResource;     // at 0x10
    };

private:
    static const int QUEUE_SIZE =
        MAX(NW4R_EF_MAX_PARTICLE, NW4R_EF_MAX_EMITTER);

private:
    int mNumItem;                             // at 0x0
    CreationQueueData mQueueData[QUEUE_SIZE]; // at 0x4

public:
    CreationQueue();

    void AddParticleCreation(const EmitterInheritSetting* pSetting,
                             Particle* pParticle, EmitterResource* pResource,
                             u16 calcRemain);

    void AddEmitterCreation(const EmitterInheritSetting* pSetting,
                            Particle* pParticle, EmitterResource* pResource,
                            u16 calcRemain);

    void Execute();

    bool IsEmpty() {
        return mNumItem == 0;
    }
};

} // namespace ef
} // namespace nw4r

#endif
