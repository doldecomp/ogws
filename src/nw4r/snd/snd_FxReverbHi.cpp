#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace snd {

FxReverbHi::FxReverbHi() {
    ReverbHiParam param = {0.02f, 3.0f, 0.6f, 0.4f, 0.1f, 1.0f};
    SetParam(param);
}

u32 FxReverbHi::GetRequiredMemSize() {
    u32 memSize = AXFXReverbHiGetMemSize(&mAxfxParam);
    return ut::RoundUp(memSize + detail::AxfxImpl::HEAP_SIZE_MIN, 32);
}

bool FxReverbHi::AssignWorkBuffer(void* pBuffer, u32 size) {
    return mImpl.CreateHeap(pBuffer, size);
}

void FxReverbHi::ReleaseWorkBuffer() {
    mImpl.DestroyHeap();
}

bool FxReverbHi::StartUp() {
    u32 memSize = GetRequiredMemSize();
    if (memSize > mImpl.GetHeapTotalSize()) {
        return false;
    }

    AXFXAllocHook allocHook;
    AXFXFreeHook freeHook;
    mImpl.HookAlloc(&allocHook, &freeHook);

    mImpl.mAllocatedSize = 0;
    BOOL success = AXFXReverbHiInit(&mAxfxParam);

    mImpl.RestoreAlloc(allocHook, freeHook);

    (void)AXFXReverbHiGetMemSize(&mAxfxParam); // debug leftover
    mImpl.mIsActive = true;

    return success;
}

void FxReverbHi::Shutdown() {
    if (!mImpl.mIsActive) {
        return;
    }

    mImpl.mIsActive = false;

    AXFXAllocHook allocHook;
    AXFXFreeHook freeHook;
    mImpl.HookAlloc(&allocHook, &freeHook);

    AXFXReverbHiShutdown(&mAxfxParam);

    mImpl.RestoreAlloc(allocHook, freeHook);
}

bool FxReverbHi::SetParam(const ReverbHiParam& rParam) {
    mParam = rParam;

    mAxfxParam.preDelay = ut::Clamp(rParam.preDelayTime, 0.0f, 0.1f);
    mAxfxParam.time = ut::Clamp(rParam.fusedTime, 0.0f, 10.0f);
    mAxfxParam.coloration = ut::Clamp(rParam.coloration, 0.0f, 1.0f);
    mAxfxParam.damping = ut::Clamp(rParam.damping, 0.0f, 1.0f);
    mAxfxParam.crosstalk = ut::Clamp(rParam.crossTalk, 0.0f, 1.0f);
    mAxfxParam.mix = ut::Clamp(rParam.outGain, 0.0f, 1.0f);

    if (!mImpl.mIsActive) {
        return true;
    }

    u32 memSize = GetRequiredMemSize();
    if (memSize > mImpl.GetHeapTotalSize()) {
        return false;
    }

    AXFXAllocHook allocHook;
    AXFXFreeHook freeHook;
    mImpl.HookAlloc(&allocHook, &freeHook);

    BOOL success = AXFXReverbHiSettings(&mAxfxParam);

    mImpl.RestoreAlloc(allocHook, freeHook);

    return success;
}

void FxReverbHi::UpdateBuffer(int channels, void** ppBuffer, u32 size,
                              SampleFormat format, f32 sampleRate,
                              OutputMode mode) {
#pragma unused(channels)
#pragma unused(size)
#pragma unused(format)
#pragma unused(sampleRate)
#pragma unused(mode)

    void* chans[AX_STEREO_MAX];
    chans[AX_STEREO_L] = ppBuffer[AX_STEREO_L];
    chans[AX_STEREO_R] = ppBuffer[AX_STEREO_R];
    chans[AX_STEREO_S] = ppBuffer[AX_STEREO_S];

    AXFXReverbHiCallback(chans, &mAxfxParam);
}

} // namespace snd
} // namespace nw4r
