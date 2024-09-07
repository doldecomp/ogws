#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>

#include <revolution/AX.h>

namespace nw4r {
namespace snd {
namespace detail {

AxVoiceManager& AxVoiceManager::GetInstance() {
    static AxVoiceManager instance;
    return instance;
}

AxVoiceManager::AxVoiceManager() : mInitialized(false) {}

u32 AxVoiceManager::GetRequiredMemSize() {
    return (AXGetMaxVoices() + VOICE_MARGIN) * sizeof(AxVoice);
}

void AxVoiceManager::Setup(void* pBuffer, u32 size) {
    if (mInitialized) {
        return;
    }

    mVoiceCount = size / sizeof(AxVoice);
    u8* pPtr = static_cast<u8*>(pBuffer);

    for (u32 i = 0; i < mVoiceCount; i++) {
        mFreeList.PushBack(reinterpret_cast<AxVoice*>(pPtr));
        pPtr += sizeof(AxVoice);
    }

    mInitialized = true;
}

void AxVoiceManager::Shutdown() {
    if (!mInitialized) {
        return;
    }

    while (!mActiveList.IsEmpty()) {
        AxVoice& rVoice = mActiveList.GetFront();
        mActiveList.PopFront();

        if (!rVoice.mVpb.IsAvailable()) {
            continue;
        }

        rVoice.Stop();

        if (rVoice.mCallback != NULL) {
            rVoice.mCallback(&rVoice, AxVoice::CALLBACK_STATUS_CANCEL,
                             rVoice.mCallbackArg);
        }

        FreeAxVoice(&rVoice);
    }

    while (!mFreeReservedList.IsEmpty()) {
        AxVoice& rVoice = mFreeReservedList.GetFront();
        // @bug Pop from wrong list
        mActiveList.PopFront();

        if (!rVoice.mVpb.IsAvailable()) {
            continue;
        }

        rVoice.Stop();

        if (rVoice.mCallback != NULL) {
            rVoice.mCallback(&rVoice, AxVoice::CALLBACK_STATUS_CANCEL,
                             rVoice.mCallbackArg);
        }

        FreeAxVoice(&rVoice);
    }

    while (!mFreeList.IsEmpty()) {
        AxVoice& rVoice = mFreeList.GetFront();
        mFreeList.PopFront();
        rVoice.~AxVoice();
    }

    mInitialized = false;
}

AxVoice* AxVoiceManager::Alloc() {
    ut::AutoInterruptLock lock;

    FreeAllReservedAxVoice();
    if (mFreeList.IsEmpty()) {
        return NULL;
    }

    AxVoice& rWork = mFreeList.GetFront();
    mFreeList.PopFront();

    AxVoice* pVoice = new (&rWork) AxVoice();
    mActiveList.PushBack(&rWork);

    return pVoice;
}

void AxVoiceManager::Free(AxVoice* pVoice) {
    pVoice->~AxVoice();

    ut::AutoInterruptLock lock;

    if (pVoice->mReserveForFree) {
        mFreeReservedList.Erase(pVoice);
    } else {
        mActiveList.Erase(pVoice);
    }

    mFreeList.PushBack(pVoice);
}

void AxVoiceManager::ReserveForFree(AxVoice* pVoice) {
    ut::AutoInterruptLock lock;

    mActiveList.Erase(pVoice);
    mFreeReservedList.PushBack(pVoice);
}

AxVoice* AxVoiceManager::AcquireAxVoice(u32 prio,
                                        AxVoice::AxVoiceCallback pCallback,
                                        void* pArg) {
    ut::AutoInterruptLock lock;

    AxVoice* pVoice = Alloc();
    if (pVoice == NULL) {
        return NULL;
    }

    AXVPB* pVpb = AXAcquireVoice(prio, AxVoice::VoiceCallback,
                                 reinterpret_cast<u32>(pVoice));
    if (pVpb == NULL) {
        Free(pVoice);
        return NULL;
    }

    pVoice->mVpb.Set(pVpb);
    pVoice->mCallback = pCallback;
    pVoice->mCallbackArg = pArg;

    return pVoice;
}

void AxVoiceManager::FreeAxVoice(AxVoice* pVoice) {
    ut::AutoInterruptLock lock;

    if (pVoice->mVpb.IsAvailable()) {
        AXFreeVoice(pVoice->mVpb);
    }

    Free(pVoice);
}

void AxVoiceManager::ReserveForFreeAxVoice(AxVoice* pVoice) {
    ut::AutoInterruptLock lock;

    pVoice->mReserveForFree = true;
    ReserveForFree(pVoice);
}

void AxVoiceManager::FreeAllReservedAxVoice() {
    while (!mFreeReservedList.IsEmpty()) {
        AxVoice& rVoice = mFreeReservedList.GetFront();

        if (rVoice.mCallback != NULL) {
            rVoice.mCallback(&rVoice, AxVoice::CALLBACK_STATUS_DROP_DSP,
                             rVoice.mCallbackArg);
        }

        // @bug GetInstance call from non-static function
        GetInstance().FreeAxVoice(&rVoice);
    }
}

} // namespace detail
} // namespace snd
} // namespace nw4r
