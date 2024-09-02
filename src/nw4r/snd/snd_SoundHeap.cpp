#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace snd {

SoundHeap::SoundHeap() {
    OSInitMutex(&mMutex);
}

SoundHeap::~SoundHeap() {
    mFrameHeap.Destroy();
}

bool SoundHeap::Create(void* pBase, u32 size) {
    return mFrameHeap.Create(pBase, size);
}

void SoundHeap::Destroy() {
    mFrameHeap.Destroy();
}

void* SoundHeap::Alloc(u32 size) {
    ut::detail::AutoLock<OSMutex> lock(mMutex);
    return mFrameHeap.Alloc(size, DisposeCallbackFunc, NULL);
}

void* SoundHeap::Alloc(u32 size, detail::FrameHeap::AllocCallback pCallback,
                       void* pCallbackArg) {
    ut::detail::AutoLock<OSMutex> lock(mMutex);
    return mFrameHeap.Alloc(size, pCallback, pCallbackArg);
}

void SoundHeap::Clear() {
    ut::detail::AutoLock<OSMutex> lockHeap(mMutex);
    detail::SoundThread::AutoLock lockThread;

    mFrameHeap.Clear();
}

int SoundHeap::SaveState() {
    ut::detail::AutoLock<OSMutex> lock(mMutex);
    return mFrameHeap.SaveState();
}

void SoundHeap::LoadState(int id) {
    ut::detail::AutoLock<OSMutex> lockHeap(mMutex);
    detail::SoundThread::AutoLock lockThread;

    mFrameHeap.LoadState(id);
}

void SoundHeap::DisposeCallbackFunc(void* pBuffer, u32 size,
                                    void* pCallbackArg) {
    detail::DisposeCallbackManager::GetInstance().Dispose(pBuffer, size,
                                                          pCallbackArg);

    detail::DisposeCallbackManager::GetInstance().DisposeWave(pBuffer, size,
                                                              pCallbackArg);
}

} // namespace snd
} // namespace nw4r
