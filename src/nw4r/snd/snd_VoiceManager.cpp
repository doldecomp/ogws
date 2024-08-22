#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>
#include <revolution/AX.h>

namespace nw4r {
namespace snd {
namespace detail {

VoiceManager& VoiceManager::GetInstance() {
    static VoiceManager instance;
    return instance;
}

VoiceManager::VoiceManager() : mInitialized(false) {}

u32 VoiceManager::GetRequiredMemSize() {
    return AXGetMaxVoices() * sizeof(Voice);
}

void VoiceManager::Setup(void* pWork, u32 workSize) {
    if (mInitialized) {
        return;
    }

    u32 voiceCount = workSize / sizeof(Voice);
    u8* p = static_cast<u8*>(pWork);

    for (u32 i = 0; i < voiceCount; i++) {
        Voice* pVoice = new (p) Voice();
        mFreeList.PushBack(pVoice);
        p += sizeof(Voice);
    }

    mInitialized = true;
}

void VoiceManager::Shutdown() {
    if (!mInitialized) {
        return;
    }

    StopAllVoices();

    while (!mFreeList.IsEmpty()) {
        Voice& rVoice = mFreeList.GetFront();
        mFreeList.PopFront();
        rVoice.~Voice();
    }

    mInitialized = false;
}

void VoiceManager::StopAllVoices() {
    ut::AutoInterruptLock lock;

    while (!mPriorityList.IsEmpty()) {
        Voice& rVoice = mPriorityList.GetFront();

        rVoice.Stop();

        if (rVoice.mCallback != NULL) {
            rVoice.mCallback(&rVoice, Voice::CALLBACK_STATUS_CANCEL,
                             rVoice.mCallbackArg);
        }

        rVoice.Free();
    }
}

Voice* VoiceManager::AllocVoice(int channels, int voices, int prio,
                                Voice::VoiceCallback pCallback,
                                void* pCallbackArg) {
    ut::AutoInterruptLock lock;

    if (mFreeList.IsEmpty() && DropLowestPriorityVoice(prio) == 0) {
        return NULL;
    }

    Voice& rVoice = mFreeList.GetFront();
    if (!rVoice.Acquire(channels, voices, prio, pCallback, pCallbackArg)) {
        return NULL;
    }

    rVoice.mPriority = prio & Voice::PRIORITY_MAX;
    AppendVoiceList(&rVoice);
    UpdateEachVoicePriority(mPriorityList.GetIteratorFromPointer(&rVoice),
                            mPriorityList.GetEndIter());
    DisposeCallbackManager::GetInstance().RegisterDisposeCallback(&rVoice);

    return &rVoice;
}

void VoiceManager::FreeVoice(Voice* pVoice) {
    ut::AutoInterruptLock lock;

    DisposeCallbackManager::GetInstance().UnregisterDisposeCallback(pVoice);
    RemoveVoiceList(pVoice);
}

void VoiceManager::UpdateAllVoices() {
    for (VoiceList::Iterator it = mPriorityList.GetBeginIter();
         it != mPriorityList.GetEndIter();) {
        VoiceList::Iterator curr = it++;
        curr->StopFinished();
    }

    for (VoiceList::Iterator it = mPriorityList.GetBeginIter();
         it != mPriorityList.GetEndIter();) {
        VoiceList::Iterator curr = it++;
        curr->Calc();
    }

    ut::AutoInterruptLock lock;

    for (VoiceList::Iterator it = mPriorityList.GetBeginIter();
         it != mPriorityList.GetEndIter();) {
        VoiceList::Iterator curr = it++;
        curr->Update();
    }
}

void VoiceManager::NotifyVoiceUpdate() {
    ut::AutoInterruptLock lock;

    for (VoiceList::Iterator it = mPriorityList.GetBeginIter();
         it != mPriorityList.GetEndIter();) {
        VoiceList::Iterator curr = it++;
        curr->ResetDelta();
    }
}

void VoiceManager::AppendVoiceList(Voice* pVoice) {
    ut::AutoInterruptLock lock;

    mFreeList.Erase(pVoice);

    VoiceList::RevIterator it = mPriorityList.GetEndReverseIter();
    for (; it != mPriorityList.GetBeginReverseIter(); ++it) {
        if (it->GetPriority() <= pVoice->GetPriority()) {
            break;
        }
    }

    mPriorityList.Insert(it.GetBase(), pVoice);
}

void VoiceManager::RemoveVoiceList(Voice* pVoice) {
    ut::AutoInterruptLock lock;

    mPriorityList.Erase(pVoice);
    mFreeList.PushBack(pVoice);
}

void VoiceManager::ChangeVoicePriority(Voice* pVoice) {
    ut::AutoInterruptLock lock;

    RemoveVoiceList(pVoice);
    AppendVoiceList(pVoice);

    UpdateEachVoicePriority(mPriorityList.GetIteratorFromPointer(pVoice),
                            mPriorityList.GetEndIter());
}

void VoiceManager::UpdateEachVoicePriority(const VoiceList::Iterator& rBegin,
                                           const VoiceList::Iterator& rEnd) {
    for (VoiceList::Iterator it = rBegin; it != rEnd; ++it) {
        if (it->GetPriority() <= 1) {
            return;
        }

        if (it->GetPriority() != Voice::PRIORITY_MAX) {
            it->UpdateVoicesPriority();
        }
    }
}

void VoiceManager::UpdateAllVoicesSync(u32 syncFlag) {
    ut::AutoInterruptLock lock;

    for (VoiceList::Iterator it = mPriorityList.GetBeginIter();
         it != mPriorityList.GetEndIter();) {
        VoiceList::Iterator curr = it++;

        if (curr->mIsActive) {
            curr->mSyncFlag |= syncFlag;
        }
    }
}

int VoiceManager::DropLowestPriorityVoice(int prio) {
    int dropNum = 0;

    if (mFreeList.IsEmpty()) {
        Voice& rVoice = mPriorityList.GetFront();

        if (rVoice.GetPriority() > prio) {
            return 0;
        }

        dropNum = rVoice.GetAxVoiceCount();

        rVoice.Stop();
        rVoice.Free();

        if (rVoice.mCallback != NULL) {
            rVoice.mCallback(&rVoice, Voice::CALLBACK_STATUS_DROP_VOICE,
                             rVoice.mCallbackArg);
        }
    }

    return dropNum;
}

} // namespace detail
} // namespace snd
} // namespace nw4r