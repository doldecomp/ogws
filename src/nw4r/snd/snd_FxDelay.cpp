#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace snd {

FxDelay::FxDelay() {
    DelayParam param = {160.0f, 0.4f, 1.0f};
    SetParam(param);
}

u32 FxDelay::GetRequiredMemSize() {
    u32 memSize = AXFXDelayGetMemSize(&mAxfxParam);
    return ut::RoundUp(memSize + detail::AxfxImpl::HEAP_SIZE_MIN, 32);
}

bool FxDelay::AssignWorkBuffer(void* pBuffer, u32 size) {
    return mImpl.CreateHeap(pBuffer, size);
}

void FxDelay::ReleaseWorkBuffer() {
    mImpl.DestroyHeap();
}

bool FxDelay::StartUp() {
    u32 memSize = GetRequiredMemSize();
    if (memSize > mImpl.GetHeapTotalSize()) {
        return false;
    }

    AXFXAllocHook allocHook;
    AXFXFreeHook freeHook;
    mImpl.HookAlloc(&allocHook, &freeHook);

    mImpl.mAllocatedSize = 0;
    BOOL success = AXFXDelayInit(&mAxfxParam);

    mImpl.RestoreAlloc(allocHook, freeHook);

    (void)AXFXDelayGetMemSize(&mAxfxParam); // debug leftover
    mImpl.mIsActive = true;

    return success;
}

void FxDelay::Shutdown() {
    if (!mImpl.mIsActive) {
        return;
    }

    mImpl.mIsActive = false;

    AXFXAllocHook allocHook;
    AXFXFreeHook freeHook;
    mImpl.HookAlloc(&allocHook, &freeHook);

    AXFXDelayShutdown(&mAxfxParam);

    mImpl.RestoreAlloc(allocHook, freeHook);
}

bool FxDelay::SetParam(const DelayParam& rParam) {
    mParam = rParam;

    mAxfxParam.delay[0] = mAxfxParam.delay[1] = mAxfxParam.delay[2] =
        ut::Clamp<u32>(rParam.delay, 1, 5000);

    mAxfxParam.feedback[0] = mAxfxParam.feedback[1] = mAxfxParam.feedback[2] =
        ut::Clamp<u32>(100.0f * rParam.feedback, 0, 99);

    mAxfxParam.output[0] = mAxfxParam.output[1] = mAxfxParam.output[2] =
        ut::Clamp<u32>(100.0f * rParam.outGain, 0, 100);

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

    BOOL success = AXFXDelaySettings(&mAxfxParam);

    mImpl.RestoreAlloc(allocHook, freeHook);

    return success;
}

void FxDelay::UpdateBuffer(int channels, void** ppBuffer, u32 size,
                           SampleFormat format, f32 sampleRate,
                           OutputMode mode) {
    void* chans[AX_STEREO_MAX];
    chans[AX_STEREO_L] = ppBuffer[AX_STEREO_L];
    chans[AX_STEREO_R] = ppBuffer[AX_STEREO_R];
    chans[AX_STEREO_S] = ppBuffer[AX_STEREO_S];

    AXFXDelayCallback(chans, &mAxfxParam);
}

} // namespace snd
} // namespace nw4r
