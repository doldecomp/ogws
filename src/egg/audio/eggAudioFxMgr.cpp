// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/audio.h>
#include <egg/core.h>
#include <egg/prim.h>

#include <nw4r/snd.h>

#include <cstring>

namespace EGG {

/******************************************************************************
 *
 * AudioFx
 *
 ******************************************************************************/
AudioFx::AudioFx() : mFxBase(NULL), mType(TYPE_AXFX_NONE), mHeap(NULL) {}

AudioFx::~AudioFx() {
    destroy();
    mHeap->destroy();
}

void AudioFx::init(nw4r::snd::AuxBus bus, void* pHeapBuffer, u32 heapSize) {
#line 61
    EGG_ASSERT(bus<nw4r::snd::AUX_BUS_NUM);

    if (heapSize > 0) {
        mHeap = ExpHeap::create(pHeapBuffer, heapSize);
    }

    mAuxBus = bus;
}

bool AudioFx::create(u32 fxType, const void* pParam) {
    switch (fxType) {
    case TYPE_AXFX_REVERBHI: {
        return createFxReverbHi(
            static_cast<const nw4r::snd::FxReverbHi::ReverbHiParam*>(pParam));
    }

    case TYPE_AXFX_REVERBHI_DPL2: {
        return createFxReverbHiDpl2(
            static_cast<const nw4r::snd::FxReverbHiDpl2::ReverbHiDpl2Param*>(
                pParam));
    }

    // Dead-stripped
    case TYPE_AXFX_REVERBSTD: {
        return NULL;
    }

    case TYPE_AXFX_CHORUS: {
        return createFxChorus(
            static_cast<const nw4r::snd::FxChorus::ChorusParam*>(pParam));
    }

    case TYPE_AXFX_DELAY: {
        return createFxDelay(
            static_cast<const nw4r::snd::FxDelay::DelayParam*>(pParam));
    }
    }
}

void AudioFx::destroy() {
    if (mFxBase != NULL) {
        nw4r::snd::detail::AxManager::GetInstance().ClearEffect(mAuxBus, 0);

        if (mHeap != NULL) {
            if (mWorkBuffer != NULL) {
                mHeap->free(mWorkBuffer);
            }

            mWorkBuffer = NULL;
            delete mFxBase;
        }

        mFxBase = NULL;
        mType = TYPE_AXFX_NONE;
    }
}

bool AudioFx::createFxReverbHi(
    const nw4r::snd::FxReverbHi::ReverbHiParam* pParam) {

    destroy();

    if (mHeap == NULL) {
        return false;
    }

    nw4r::snd::FxReverbHi* pReverbHi = new (mHeap) nw4r::snd::FxReverbHi();
    mFxBase = pReverbHi;

    if (!pReverbHi->SetParam(*pParam)) {
        EGG_PRINT("createFxReverbHi FAILED!!! irregal param.\n");
        return false;
    }

    mParam = pParam;

    u32 workBufferSize = pReverbHi->GetRequiredMemSize();
    mWorkBuffer = new (mHeap) u8[workBufferSize];

    if (mWorkBuffer != NULL) {
        for (int i = 0; i < workBufferSize; i++) {
            mWorkBuffer[i] = 0;
        }

        pReverbHi->AssignWorkBuffer(mWorkBuffer, workBufferSize);
        mType = TYPE_AXFX_REVERBHI;

        return nw4r::snd::detail::AxManager::GetInstance().AppendEffect(
            mAuxBus, pReverbHi);

    } else {
        delete mFxBase;
        mFxBase = NULL;

        // TODO: Where does the 0xA4 come from?
        EGG_PRINT("createFxReverbHi FAILED!!! need %d (alloc %d)\n",
                  workBufferSize + sizeof(nw4r::snd::FxReverbHi) + 0xA4,
                  mHeap->getTotalSize());

        return false;
    }
}

bool AudioFx::createFxReverbHiDpl2(
    const nw4r::snd::FxReverbHiDpl2::ReverbHiDpl2Param* pParam) {

    destroy();

    if (mHeap == NULL) {
        return false;
    }

    // Allocate a buffer just for fun :^)
    void* pReverbBuffer = new (mHeap) u8[sizeof(nw4r::snd::FxReverbHiDpl2)];
    std::memset(pReverbBuffer, 0, sizeof(nw4r::snd::FxReverbHiDpl2));
    delete pReverbBuffer;

    nw4r::snd::FxReverbHiDpl2* pReverbHiDpl2 =
        new (mHeap) nw4r::snd::FxReverbHiDpl2();
    mFxBase = pReverbHiDpl2;

    if (!pReverbHiDpl2->SetParam(*pParam)) {
        EGG_PRINT("createFxReverbHiDpl2 FAILED!!! irregal param.\n");
        return false;
    }

    mParam = pParam;

    u32 workBufferSize = pReverbHiDpl2->GetRequiredMemSize();
    mWorkBuffer = new (mHeap) u8[workBufferSize];

    if (mWorkBuffer != NULL) {
        for (int i = 0; i < workBufferSize; i++) {
            mWorkBuffer[i] = 0;
        }

        pReverbHiDpl2->AssignWorkBuffer(mWorkBuffer, workBufferSize);
        mType = TYPE_AXFX_REVERBHI_DPL2;

        return nw4r::snd::detail::AxManager::GetInstance().AppendEffect(
            mAuxBus, pReverbHiDpl2);

    } else {
        delete mFxBase;
        mFxBase = NULL;

        // TODO: Where does the 0xA4 come from?
        EGG_PRINT("createFxReverbHiDpl2 FAILED!!! need %d (alloc %d)\n",
                  workBufferSize + sizeof(nw4r::snd::FxReverbHiDpl2) + 0xA4,
                  mHeap->getTotalSize());

        return false;
    }
}

DECOMP_FORCEACTIVE(eggAudioFxMgr_cpp,
                  "createFxReverbStd FAILED!!! irregal param.\n",
                  "createFxReverbStd FAILED!!! need %d (alloc %d)\n");

bool AudioFx::createFxChorus(const nw4r::snd::FxChorus::ChorusParam* pParam) {
    destroy();

    if (mHeap == NULL) {
        return false;
    }

    nw4r::snd::FxChorus* pChorus = new (mHeap) nw4r::snd::FxChorus();
    mFxBase = pChorus;

    if (!pChorus->SetParam(*pParam)) {
        EGG_PRINT("createFxChorus FAILED!!! irregal param.\n");
        return false;
    }

    mParam = pParam;

    u32 workBufferSize = pChorus->GetRequiredMemSize();
    mWorkBuffer = new (mHeap) u8[workBufferSize];

    if (mWorkBuffer != NULL) {
        for (int i = 0; i < workBufferSize; i++) {
            mWorkBuffer[i] = 0;
        }

        pChorus->AssignWorkBuffer(mWorkBuffer, workBufferSize);
        mType = TYPE_AXFX_CHORUS;

        return nw4r::snd::detail::AxManager::GetInstance().AppendEffect(
            mAuxBus, pChorus);

    } else {
        delete mFxBase;
        mFxBase = NULL;

        // TODO: Where does the 0xA4 come from?
        EGG_PRINT("createFxChorus FAILED!!! need %d (alloc %d)\n",
                  workBufferSize + sizeof(nw4r::snd::FxChorus) + 0xA4,
                  mHeap->getTotalSize());

        return false;
    }
}

bool AudioFx::createFxDelay(const nw4r::snd::FxDelay::DelayParam* pParam) {
    destroy();

    if (mHeap == NULL) {
        return false;
    }

    nw4r::snd::FxDelay* pDelay = new (mHeap) nw4r::snd::FxDelay();
    mFxBase = pDelay;

    if (!pDelay->SetParam(*pParam)) {
        EGG_PRINT("createFxDelay FAILED!!! irregal param.\n");
        return false;
    }

    mParam = pParam;

    u32 workBufferSize = pDelay->GetRequiredMemSize();
    mWorkBuffer = new (mHeap) u8[workBufferSize];

    if (mWorkBuffer != NULL) {
        for (int i = 0; i < workBufferSize; i++) {
            mWorkBuffer[i] = 0;
        }

        pDelay->AssignWorkBuffer(mWorkBuffer, workBufferSize);
        mType = TYPE_AXFX_DELAY;

        return nw4r::snd::detail::AxManager::GetInstance().AppendEffect(mAuxBus,
                                                                        pDelay);

    } else {
        delete mFxBase;
        mFxBase = NULL;

        // TODO: Where does the 0xA4 come from?
        EGG_PRINT("createFxDelay FAILED!!! need %d (alloc %d)\n",
                  workBufferSize + sizeof(nw4r::snd::FxDelay) + 0xA4,
                  mHeap->getTotalSize());

        return false;
    }
}

/******************************************************************************
 *
 * AudioFxMgr
 *
 ******************************************************************************/
const nw4r::snd::FxReverbHi::ReverbHiParam AudioFxMgr::sDefaultFxReverbHi = {
    0.02f, // preDelayTime
    3.0f,  // fusedTime
    0.6f,  // coloration
    0.4f,  // damping
    0.1f,  // crossTalk
    1.0f   // outGain
};

// clang-format off
const nw4r::snd::FxReverbHiDpl2::ReverbHiDpl2Param AudioFxMgr::sDefaultFxReverbHiDpl2 = {
    0.02f, // preDelayTime
    3.0f,  // fusedTime
    0.6f,  // coloration
    0.4f,  // damping
    0.1f,  // crossTalk
    1.0f   // outGain
};
// clang-format on

const nw4r::snd::FxChorus::ChorusParam AudioFxMgr::sDefaultFxChorus = {
    10.0f, // delayTime
    0.5f,  // depth
    1.0f   // rate
};

const nw4r::snd::FxDelay::DelayParam AudioFxMgr::sDefaultFxDelay = {
    160.0f, // delay
    0.4f,   // feedback
    1.0f    // outGain
};

AudioFxMgr::AudioFxMgr() {}

AudioFxMgr::~AudioFxMgr() {}

bool AudioFxMgr::initializeFx(nw4r::snd::SoundHeap* pHeap,
                              AudioFxMgrArg* pArg) {

    for (int i = 0; i < nw4r::snd::AUX_BUS_NUM; i++) {
        if (pArg->heapSize[i] == 0) {
            continue;
        }

        void* pHeapBuffer = pHeap->Alloc(pArg->heapSize[i], NULL, NULL);
        if (pHeapBuffer == NULL) {
            return false;
        }

        mAudioFx[i].init(static_cast<nw4r::snd::AuxBus>(i), pHeapBuffer,
                         pArg->heapSize[i]);
    }

    return true;
}

bool AudioFxMgr::setFxReverbHi(
    nw4r::snd::AuxBus bus, const nw4r::snd::FxReverbHi::ReverbHiParam* pParam) {

#line 438
    EGG_ASSERT(bus<nw4r::snd::AUX_BUS_NUM);
    return mAudioFx[bus].create(AudioFx::TYPE_AXFX_REVERBHI, pParam);
}

bool AudioFxMgr::setFxReverbHiDpl2(
    nw4r::snd::AuxBus bus,
    const nw4r::snd::FxReverbHiDpl2::ReverbHiDpl2Param* pParam) {

#line 466
    EGG_ASSERT(bus<nw4r::snd::AUX_BUS_NUM);
    return mAudioFx[bus].create(AudioFx::TYPE_AXFX_REVERBHI_DPL2, pParam);
}

bool AudioFxMgr::setFxChorus(nw4r::snd::AuxBus bus,
                             const nw4r::snd::FxChorus::ChorusParam* pParam) {
#line 501
    EGG_ASSERT(bus<nw4r::snd::AUX_BUS_NUM);
    return mAudioFx[bus].create(AudioFx::TYPE_AXFX_CHORUS, pParam);
}

bool AudioFxMgr::setFxDelay(nw4r::snd::AuxBus bus,
                            const nw4r::snd::FxDelay::DelayParam* pParam) {
#line 526
    EGG_ASSERT(bus<nw4r::snd::AUX_BUS_NUM);
    return mAudioFx[bus].create(AudioFx::TYPE_AXFX_DELAY, pParam);
}

void AudioFxMgr::clearFx(nw4r::snd::AuxBus bus) {
#line 549
    EGG_ASSERT(bus<nw4r::snd::AUX_BUS_NUM);
    mAudioFx[bus].destroy();
}

const nw4r::snd::FxReverbHi::ReverbHiParam* AudioFxMgr::getDefaultFxReverbHi() {
    return &sDefaultFxReverbHi;
}

const nw4r::snd::FxReverbHiDpl2::ReverbHiDpl2Param*
AudioFxMgr::getDefaultFxReverbHiDpl2() {

    return &sDefaultFxReverbHiDpl2;
}

const nw4r::snd::FxChorus::ChorusParam* AudioFxMgr::getDefaultFxChorus() {
    return &sDefaultFxChorus;
}

const nw4r::snd::FxDelay::DelayParam* AudioFxMgr::getDefaultFxDelay() {
    return &sDefaultFxDelay;
}

DECOMP_FORCEACTIVE(eggAudioFxMgr_cpp,
                  "code>=AudioFx::TYPE_AXFX_MAX");

} // namespace EGG
