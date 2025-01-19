#include <nw4r/ef.h>

namespace nw4r {
namespace ef {

CreationQueue::CreationQueue() : mNumItem(0) {}

void CreationQueue::AddParticleCreation(const EmitterInheritSetting* pSetting,
                                        Particle* pParticle,
                                        EmitterResource* pResource,
                                        u16 calcRemain) {

    if (mNumItem >= QUEUE_SIZE) {
        return;
    }

    // @bug Flags field not initialized
    mQueueData[mNumItem].mType = CreationQueueData::TYPE_PARTICLE;
    mQueueData[mNumItem].mCalcRemain = calcRemain;
    mQueueData[mNumItem].mInheritSetting = *pSetting;
    mQueueData[mNumItem].mReferenceParticle = pParticle;

    pParticle->Ref();

    mQueueData[mNumItem].mEmitterResource = pResource;

    mNumItem++;
}

void CreationQueue::AddEmitterCreation(const EmitterInheritSetting* pSetting,
                                       Particle* pParticle,
                                       EmitterResource* pResource,
                                       u16 calcRemain) {

    if (mNumItem >= QUEUE_SIZE) {
        return;
    }

    // @bug Flags field not initialized
    mQueueData[mNumItem].mType = CreationQueueData::TYPE_EMITTER;
    mQueueData[mNumItem].mCalcRemain = calcRemain;
    mQueueData[mNumItem].mInheritSetting = *pSetting;
    mQueueData[mNumItem].mReferenceParticle = pParticle;

    pParticle->Ref();

    mQueueData[mNumItem].mEmitterResource = pResource;

    mNumItem++;
}

void CreationQueue::Execute() {
    for (int i = 0; i < mNumItem; i++) {
        CreationQueueData& rData = mQueueData[i];

        switch (rData.mType) {
        case CreationQueueData::TYPE_PARTICLE: {
            rData.mReferenceParticle->mParticleManager->mManagerEM
                ->CreateEmitterTmp(rData.mEmitterResource,
                                   &rData.mInheritSetting,
                                   rData.mReferenceParticle, rData.mCalcRemain);

            rData.mReferenceParticle->UnRef();
            break;
        }

        case CreationQueueData::TYPE_EMITTER: {
            rData.mReferenceParticle->mParticleManager->mManagerEM
                ->CreateEmitter(rData.mEmitterResource, &rData.mInheritSetting,
                                rData.mReferenceParticle, rData.mCalcRemain);

            rData.mReferenceParticle->UnRef();
            break;
        }
        }
    }

    mNumItem = 0;
}

} // namespace ef
} // namespace nw4r
