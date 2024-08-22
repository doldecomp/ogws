#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace snd {

FxChorus::FxChorus() {
    ChorusParam param = {10.0f, 0.5f, 1.0f};
    SetParam(param);
}

u32 FxChorus::GetRequiredMemSize() {
    u32 memSize = AXFXChorusGetMemSize(&mAxfxParam);
    return ut::RoundUp(memSize + detail::AxfxImpl::HEAP_SIZE_MIN, 32);
}

bool FxChorus::AssignWorkBuffer(void* pBuffer, u32 size) {
    return mImpl.CreateHeap(pBuffer, size);
}

void FxChorus::ReleaseWorkBuffer() {
    mImpl.DestroyHeap();
}

bool FxChorus::StartUp() {
    u32 memSize = GetRequiredMemSize();
    if (memSize > mImpl.GetHeapTotalSize()) {
        return false;
    }

    AXFXAllocHook allocHook;
    AXFXFreeHook freeHook;
    mImpl.HookAlloc(&allocHook, &freeHook);

    mImpl.mAllocatedSize = 0;
    BOOL success = AXFXChorusInit(&mAxfxParam);

    mImpl.RestoreAlloc(allocHook, freeHook);

    (void)AXFXChorusGetMemSize(&mAxfxParam); // debug leftover
    mImpl.mIsActive = true;

    return success;
}

void FxChorus::Shutdown() {
    if (!mImpl.mIsActive) {
        return;
    }

    mImpl.mIsActive = false;

    AXFXAllocHook allocHook;
    AXFXFreeHook freeHook;
    mImpl.HookAlloc(&allocHook, &freeHook);

    AXFXChorusShutdown(&mAxfxParam);

    mImpl.RestoreAlloc(allocHook, freeHook);
}

bool FxChorus::SetParam(const ChorusParam& rParam) {
    mParam = rParam;

    u32 baseDelay = static_cast<u32>(rParam.delayTime);
    u32 variation = static_cast<u32>(rParam.delayTime * rParam.depth);
    u32 period = static_cast<u32>(1000.0f / rParam.rate);

    mAxfxParam.baseDelay = ut::Clamp<u32>(baseDelay, 1, 50);
    mAxfxParam.variation = ut::Clamp<u32>(variation, 0, 50);
    mAxfxParam.period = ut::Clamp<u32>(period, 500, 10000);

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

    BOOL success = AXFXChorusSettings(&mAxfxParam);

    mImpl.RestoreAlloc(allocHook, freeHook);

    return success;
}

void FxChorus::UpdateBuffer(int channels, void** ppBuffer, u32 size,
                            SampleFormat format, f32 sampleRate,
                            OutputMode mode) {
    void* chans[AX_STEREO_MAX];
    chans[AX_STEREO_L] = ppBuffer[AX_STEREO_L];
    chans[AX_STEREO_R] = ppBuffer[AX_STEREO_R];
    chans[AX_STEREO_S] = ppBuffer[AX_STEREO_S];

    AXFXChorusCallback(chans, &mAxfxParam);
}

} // namespace snd
} // namespace nw4r
