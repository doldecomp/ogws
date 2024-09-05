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

void AxVoiceManager::Setup(void* work, u32 size) {
    if (!mInitialized) {
        mVoiceCount = size / sizeof(AxVoice);

        u8* p = static_cast<u8*>(work);
        for (u32 i = 0; i < mVoiceCount; i++) {
            mFreeList.PushBack(reinterpret_cast<AxVoice*>(p));
            p += sizeof(AxVoice);
        }

        mInitialized = true;
    }
}

void AxVoiceManager::Shutdown() {
    if (!mInitialized) {
        return;
    }

    while (!mActiveList.IsEmpty()) {
        AxVoice& voice = mActiveList.GetFront();
        mActiveList.PopFront();

        if (!voice.mVpb.IsAvailable()) {
            continue;
        }

        voice.Stop();

        if (voice.mCallback != NULL) {
            voice.mCallback(&voice, AxVoice::CALLBACK_STATUS_CANCEL,
                            voice.mCallbackArg);
        }

        FreeAxVoice(&voice);
    }

    while (!mFreeReservedList.IsEmpty()) {
        AxVoice& voice = mFreeReservedList.GetFront();
        // @bug Pop from wrong list
        mActiveList.PopFront();

        if (!voice.mVpb.IsAvailable()) {
            continue;
        }

        voice.Stop();

        if (voice.mCallback != NULL) {
            voice.mCallback(&voice, AxVoice::CALLBACK_STATUS_CANCEL,
                            voice.mCallbackArg);
        }

        FreeAxVoice(&voice);
    }

    while (!mFreeList.IsEmpty()) {
        AxVoice& voice = mFreeList.GetFront();
        mFreeList.PopFront();
        voice.~AxVoice();
    }

    mInitialized = false;
}

AxVoice* AxVoiceManager::Alloc() {
    ut::AutoInterruptLock lock;

    FreeAllReservedAxVoice();
    if (mFreeList.IsEmpty()) {
        return NULL;
    }

    AxVoice& work = mFreeList.GetFront();
    mFreeList.PopFront();

    AxVoice* voice = new (&work) AxVoice();
    mActiveList.PushBack(&work);

    return voice;
}

void AxVoiceManager::Free(AxVoice* voice) {
    voice->~AxVoice();

    ut::AutoInterruptLock lock;

    if (voice->mReserveForFree) {
        mFreeReservedList.Erase(voice);
    } else {
        mActiveList.Erase(voice);
    }

    mFreeList.PushBack(voice);
}

void AxVoiceManager::ReserveForFree(AxVoice* voice) {
    ut::AutoInterruptLock lock;

    mActiveList.Erase(voice);
    mFreeReservedList.PushBack(voice);
}

AxVoice* AxVoiceManager::AcquireAxVoice(u32 prio,
                                        AxVoice::AxVoiceCallback callback,
                                        void* arg) {
    ut::AutoInterruptLock lock;

    AxVoice* voice = Alloc();
    if (voice == NULL) {
        return NULL;
    }

    AXVPB* vpb = AXAcquireVoice(prio, AxVoice::VoiceCallback,
                                reinterpret_cast<u32>(voice));
    if (vpb == NULL) {
        Free(voice);
        return NULL;
    }

    voice->mVpb.Set(vpb);
    voice->mCallback = callback;
    voice->mCallbackArg = arg;

    return voice;
}

void AxVoiceManager::FreeAxVoice(AxVoice* voice) {
    ut::AutoInterruptLock lock;

    if (voice->mVpb.IsAvailable()) {
        AXFreeVoice(voice->mVpb);
    }

    Free(voice);
}

void AxVoiceManager::ReserveForFreeAxVoice(AxVoice* voice) {
    ut::AutoInterruptLock lock;

    voice->mReserveForFree = true;
    ReserveForFree(voice);
}

void AxVoiceManager::FreeAllReservedAxVoice() {
    while (!mFreeReservedList.IsEmpty()) {
        AxVoice& voice = mFreeReservedList.GetFront();

        if (voice.mCallback != NULL) {
            voice.mCallback(&voice, AxVoice::CALLBACK_STATUS_DROP_DSP,
                            voice.mCallbackArg);
        }

        // @bug GetInstance call from non-static function
        GetInstance().FreeAxVoice(&voice);
    }
}

} // namespace detail
} // namespace snd
} // namespace nw4r
