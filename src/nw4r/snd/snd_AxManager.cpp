#include <nw4r/snd.h>

#include <revolution/AXFX.h>
#include <revolution/DVD.h>
#include <revolution/OS.h>

#include <cstring>

namespace nw4r {
namespace snd {
namespace detail {

NW4R_UT_LINKLIST_TYPEDEF_FORCE(FxBase);

u8 AxManager::sZeroBuffer[AxManager::ZERO_BUFFER_SIZE];

AxManager::AxManager()
    : mOutputMode(OUTPUT_MODE_STEREO),
      mZeroBufferAddress(NULL),
      mInitialized(false),
      mUpdateVoicePrioFlag(true),
      mOldAidCallback(NULL),
      mResetReadyCounter(-1),
      mDiskError(false) {

    mMainOutVolume.InitValue(1.0f);
    mMasterVolume.InitValue(1.0f);
    mVolumeForReset.InitValue(1.0f);

    for (int i = 0; i < AUX_BUS_NUM; i++) {
        mAuxFadeVolume[i].InitValue(1.0f);
        mAuxUserVolume[i].InitValue(1.0f);
        mAuxCallback[i] = NULL;
        mAuxCallbackContext[i] = 0;
    }
}

AxManager& AxManager::GetInstance() {
    static AxManager instance;
    return instance;
}

void AxManager::Init() {
    if (mInitialized) {
        return;
    }

    std::memset(sZeroBuffer, 0, sizeof(sZeroBuffer));
    DCFlushRange(sZeroBuffer, sizeof(sZeroBuffer));
    mZeroBufferAddress = sZeroBuffer;

    ut::AutoInterruptLock lock;

    AXGetAuxACallback(&mAuxCallback[AUX_A], &mAuxCallbackContext[AUX_A]);
    AXGetAuxBCallback(&mAuxCallback[AUX_B], &mAuxCallbackContext[AUX_B]);
    AXGetAuxCCallback(&mAuxCallback[AUX_C], &mAuxCallbackContext[AUX_C]);

    AXRegisterAuxACallback(NULL, NULL);
    AXRegisterAuxBCallback(NULL, NULL);
    AXRegisterAuxCCallback(NULL, NULL);

    mNextAxRegisterCallback = AXRegisterCallback(AxCallbackFunc);

    mInitialized = true;
}

void AxManager::Shutdown() {
    if (!mInitialized) {
        return;
    }

    AXRegisterCallback(mNextAxRegisterCallback);

    ShutdownEffect(AUX_A);
    ShutdownEffect(AUX_B);
    ShutdownEffect(AUX_C);

    AXRegisterAuxACallback(mAuxCallback[AUX_A], mAuxCallbackContext[AUX_A]);
    AXRegisterAuxBCallback(mAuxCallback[AUX_B], mAuxCallbackContext[AUX_B]);
    AXRegisterAuxCCallback(mAuxCallback[AUX_C], mAuxCallbackContext[AUX_C]);

    for (int i = 0; i < AUX_BUS_NUM; i++) {
        mAuxCallback[i] = NULL;
        mAuxCallbackContext[i] = NULL;
    }

    mZeroBufferAddress = NULL;

    mInitialized = false;
}

f32 AxManager::GetOutputVolume() const {
    return mMasterVolume.GetValue();
}

void AxManager::Update() {
    s32 status = DVDGetDriveStatus();

    if (status == DVD_STATE_IDLE || status == DVD_STATE_BUSY) {
        if (mDiskError) {
            mDiskError = false;
            VoiceManager::GetInstance().UpdateAllVoicesSync(
                Voice::SYNC_AX_VOICE);
        }
    } else {
        if (!mDiskError) {
            mDiskError = true;
            VoiceManager::GetInstance().UpdateAllVoicesSync(
                Voice::SYNC_AX_VOICE);
        }
    }

    for (int i = 0; i < AUX_BUS_NUM; i++) {
        bool update = false;

        if (!mAuxUserVolume[i].IsFinished()) {
            mAuxUserVolume[i].Update();
            update = true;
        }

        if (!mAuxFadeVolume[i].IsFinished()) {
            mAuxFadeVolume[i].Update();

            if (mAuxFadeVolume[i].IsFinished()) {
                ShutdownEffect(static_cast<AuxBus>(i));
            }

            update = true;
        }

        if (update) {
            f32 ratio = 1.0f;
            ratio *= ut::Clamp(mAuxUserVolume[i].GetValue(), 0.0f, 1.0f);
            ratio *= ut::Clamp(mAuxFadeVolume[i].GetValue(), 0.0f, 1.0f);
            u16 volume = static_cast<u16>(AX_MAX_VOLUME * ratio);

            switch (i) {
            case AUX_A: {
                AXSetAuxAReturnVolume(volume);
                break;
            }

            case AUX_B: {
                AXSetAuxBReturnVolume(volume);
                break;
            }

            case AUX_C: {
                AXSetAuxCReturnVolume(volume);
                break;
            }
            }
        }
    }

    if (!mMasterVolume.IsFinished()) {
        mMasterVolume.Update();
        VoiceManager::GetInstance().UpdateAllVoicesSync(Voice::SYNC_AX_VE);
    }

    if (!mVolumeForReset.IsFinished()) {
        mVolumeForReset.Update();
    }

    if (!mMainOutVolume.IsFinished()) {
        mMainOutVolume.Update();
    }

    f32 masterRatio = mMainOutVolume.GetValue();
    masterRatio *= mVolumeForReset.GetValue();
    masterRatio = ut::Clamp(masterRatio, 0.0f, 1.0f);
    AXSetMasterVolume(static_cast<u16>(AX_MAX_VOLUME * masterRatio));
}

void* AxManager::GetZeroBufferAddress() {
    return mZeroBufferAddress;
}

void AxManager::RegisterCallback(CallbackListNode* pNode,
                                 AXOutCallback pCallback) {
    ut::AutoInterruptLock lock;
    pNode->callback = pCallback;
    mCallbackList.PushBack(pNode);
}

void AxManager::UnregisterCallback(CallbackListNode* pNode) {
    ut::AutoInterruptLock lock;
    mCallbackList.Erase(pNode);
}

void AxManager::SetOutputMode(OutputMode mode) {
    mOutputMode = mode;

    switch (mode) {
    case OUTPUT_MODE_STEREO: {
        AXSetMode(AX_OUTPUT_STEREO);
        break;
    }

    case OUTPUT_MODE_SURROUND: {
        AXSetMode(AX_OUTPUT_SURROUND);
        break;
    }

    case OUTPUT_MODE_DPL2: {
        AXSetMode(AX_OUTPUT_DPL2);
        break;
    }

    case OUTPUT_MODE_MONO: {
        AXSetMode(AX_OUTPUT_STEREO);
        break;
    }
    }

    VoiceManager::GetInstance().UpdateAllVoicesSync(Voice::SYNC_AX_MIX);
}

OutputMode AxManager::GetOutputMode() {
    return mOutputMode;
}

void AxManager::SetMasterVolume(f32 volume, int frame) {
    mMasterVolume.SetTarget(ut::Clamp(volume, 0.0f, 1.0f), (frame + 2) / 3);

    if (frame == 0) {
        VoiceManager::GetInstance().UpdateAllVoicesSync(Voice::SYNC_AX_VE);
    }
}

void AxManager::AxCallbackFunc() {
    NW4R_UT_LINKLIST_FOREACH_SAFE(it, GetInstance().mCallbackList,
                                  { it->callback(); });

    if (GetInstance().mNextAxRegisterCallback != NULL) {
        GetInstance().mNextAxRegisterCallback();
    }
}

bool AxManager::AppendEffect(AuxBus bus, FxBase* pFx) {
    if (!mAuxFadeVolume[bus].IsFinished()) {
        ShutdownEffect(bus);
    }

    mAuxFadeVolume[bus].SetTarget(1.0f, 0);

    switch (bus) {
    case AUX_A: {
        AXSetAuxAReturnVolume(AX_MAX_VOLUME);
        break;
    }

    case AUX_B: {
        AXSetAuxBReturnVolume(AX_MAX_VOLUME);
        break;
    }

    case AUX_C: {
        AXSetAuxCReturnVolume(AX_MAX_VOLUME);
        break;
    }
    }

    if (!pFx->StartUp()) {
        return false;
    }

    ut::AutoInterruptLock lock;

    if (GetEffectList(bus).IsEmpty()) {
        switch (bus) {
        case AUX_A: {
            AXRegisterAuxACallback(AuxCallbackFunc,
                                   reinterpret_cast<void*>(bus));
            break;
        }

        case AUX_B: {
            AXRegisterAuxBCallback(AuxCallbackFunc,
                                   reinterpret_cast<void*>(bus));
            break;
        }

        case AUX_C: {
            AXRegisterAuxCCallback(AuxCallbackFunc,
                                   reinterpret_cast<void*>(bus));
            break;
        }
        }

        mAuxCallbackWaitCounter[bus] = 2;
    }

    GetEffectList(bus).PushBack(pFx);
    return true;
}

void AxManager::ClearEffect(AuxBus bus, int frame) {
    if (frame == 0) {
        ShutdownEffect(bus);
        return;
    }

    mAuxFadeVolume[bus].SetTarget(0.0f, (frame + 2) / 3);
}

void AxManager::ShutdownEffect(AuxBus bus) {
    ut::AutoInterruptLock lock;

    if (GetEffectList(bus).IsEmpty()) {
        return;
    }

    for (FxBaseList::Iterator it = GetEffectList(bus).GetBeginIter();
         it != GetEffectList(bus).GetEndIter(); ++it) {
        it->Shutdown();
    }

    GetEffectList(bus).Clear();

    switch (bus) {
    case AUX_A: {
        AXRegisterAuxACallback(NULL, NULL);
        break;
    }

    case AUX_B: {
        AXRegisterAuxBCallback(NULL, NULL);
        break;
    }

    case AUX_C: {
        AXRegisterAuxCCallback(NULL, NULL);
        break;
    }
    }
}

void AxManager::AuxCallbackFunc(void* pChans, void* pContext) {
    int num;
    void* buffer[AX_DPL2_MAX];

    void** ppChans = static_cast<void**>(pChans);
    AuxBus bus = static_cast<AuxBus>(reinterpret_cast<u32>(pContext));

    if (GetInstance().GetOutputMode() == OUTPUT_MODE_DPL2) {
        num = AX_DPL2_MAX;

        buffer[AX_DPL2_L] = ppChans[AX_DPL2_L];
        buffer[AX_DPL2_R] = ppChans[AX_DPL2_R];
        buffer[AX_DPL2_LS] = ppChans[AX_DPL2_LS];
        buffer[AX_DPL2_RS] = ppChans[AX_DPL2_RS];
    } else {
        num = AX_STEREO_MAX;

        buffer[AX_STEREO_L] = ppChans[AX_STEREO_L];
        buffer[AX_STEREO_R] = ppChans[AX_STEREO_R];
        buffer[AX_STEREO_S] = ppChans[AX_STEREO_S];
    }

    if (GetInstance().mAuxCallbackWaitCounter[bus] > 0) {
        GetInstance().mAuxCallbackWaitCounter[bus]--;

        for (int i = 0; i < num; i++) {
            std::memset(buffer[i], 0, FX_BUFFER_SIZE);
        }
    } else if (GetInstance().GetEffectList(bus).IsEmpty()) {
        for (int i = 0; i < num; i++) {
            std::memset(buffer[i], 0, FX_BUFFER_SIZE);
        }
    } else {
        for (FxBaseList::Iterator it =
                 GetInstance().GetEffectList(bus).GetBeginIter();
             it != GetInstance().GetEffectList(bus).GetEndIter(); ++it) {

            it->UpdateBuffer(num, buffer, FX_BUFFER_SIZE, FX_SAMPLE_FORMAT,
                             FX_SAMPLE_RATE, GetInstance().GetOutputMode());
        }
    }
}

void AxManager::PrepareReset() {
    if (mOldAidCallback != NULL) {
        return;
    }

    mVolumeForReset.SetTarget(0.0f, 3);
    mResetReadyCounter = -1;
    mOldAidCallback = AIRegisterDMACallback(AiDmaCallbackFunc);
}

void AxManager::AiDmaCallbackFunc() {
    static bool finishedFlag = false;

    AxManager& r = GetInstance();
    r.mOldAidCallback();

    if (finishedFlag) {
        if (r.mResetReadyCounter < 0) {
            AXSetMaxDspCycles(0);
            r.mResetReadyCounter = AUX_CALLBACK_WAIT_FRAME;
        }
    } else if (r.mVolumeForReset.GetValue() == 0.0f) {
        finishedFlag = true;
    }

    if (r.mResetReadyCounter > 0) {
        r.mResetReadyCounter--;
    }
}

} // namespace detail
} // namespace snd
} // namespace nw4r
