#include <nw4r/snd.h>
#include <nw4r/ut.h>

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

void VoiceManager::Setup(void* pBuffer, u32 size) {
    if (mInitialized) {
        return;
    }

    u32 voices = size / sizeof(Voice);
    u8* pPtr = static_cast<u8*>(pBuffer);

    for (u32 i = 0; i < voices; i++) {
        Voice* pVoice = new (pPtr) Voice();
        mFreeVoiceList.PushBack(pVoice);
        pPtr += sizeof(Voice);
    }

    mInitialized = true;
}

void VoiceManager::Shutdown() {
    if (!mInitialized) {
        return;
    }

    StopAllVoices();

    while (!mFreeVoiceList.IsEmpty()) {
        Voice& rVoice = mFreeVoiceList.GetFront();
        mFreeVoiceList.PopFront();
        rVoice.~Voice();
    }

    mInitialized = false;
}

void VoiceManager::StopAllVoices() {
    ut::AutoInterruptLock lock;

    while (!mPrioVoiceList.IsEmpty()) {
        Voice& rVoice = mPrioVoiceList.GetFront();

        rVoice.Stop();

        if (rVoice.mCallback != NULL) {
            rVoice.mCallback(&rVoice, Voice::CALLBACK_STATUS_CANCEL,
                             rVoice.mCallbackArg);
        }

        rVoice.Free();
    }
}

Voice* VoiceManager::AllocVoice(int channels, int voices, int priority,
                                Voice::VoiceCallback pCallback,
                                void* pCallbackArg) {

    ut::AutoInterruptLock lock;

    if (mFreeVoiceList.IsEmpty() && DropLowestPriorityVoice(priority) == 0) {
        return NULL;
    }

    Voice& rVoice = mFreeVoiceList.GetFront();
    if (!rVoice.Acquire(channels, voices, priority, pCallback, pCallbackArg)) {
        return NULL;
    }

    rVoice.mPriority = priority & Voice::PRIORITY_MAX;
    AppendVoiceList(&rVoice);
    UpdateEachVoicePriority(mPrioVoiceList.GetIteratorFromPointer(&rVoice),
                            mPrioVoiceList.GetEndIter());
    DisposeCallbackManager::GetInstance().RegisterDisposeCallback(&rVoice);

    return &rVoice;
}

void VoiceManager::FreeVoice(Voice* pVoice) {
    ut::AutoInterruptLock lock;

    DisposeCallbackManager::GetInstance().UnregisterDisposeCallback(pVoice);
    RemoveVoiceList(pVoice);
}

void VoiceManager::UpdateAllVoices() {
    NW4R_UT_LINKLIST_FOREACH_SAFE(it, mPrioVoiceList, { it->StopFinished(); });
    NW4R_UT_LINKLIST_FOREACH_SAFE(it, mPrioVoiceList, { it->Calc(); });

    ut::AutoInterruptLock lock;

    NW4R_UT_LINKLIST_FOREACH_SAFE(it, mPrioVoiceList, { it->Update(); });
}

void VoiceManager::NotifyVoiceUpdate() {
    ut::AutoInterruptLock lock;

    NW4R_UT_LINKLIST_FOREACH_SAFE(it, mPrioVoiceList, { it->ResetDelta(); });
}

void VoiceManager::AppendVoiceList(Voice* pVoice) {
    ut::AutoInterruptLock lock;

    mFreeVoiceList.Erase(pVoice);

    VoiceList::RevIterator it = mPrioVoiceList.GetEndReverseIter();
    for (; it != mPrioVoiceList.GetBeginReverseIter(); ++it) {
        if (it->GetPriority() <= pVoice->GetPriority()) {
            break;
        }
    }

    mPrioVoiceList.Insert(it.GetBase(), pVoice);
}

void VoiceManager::RemoveVoiceList(Voice* pVoice) {
    ut::AutoInterruptLock lock;

    mPrioVoiceList.Erase(pVoice);
    mFreeVoiceList.PushBack(pVoice);
}

void VoiceManager::ChangeVoicePriority(Voice* pVoice) {
    ut::AutoInterruptLock lock;

    RemoveVoiceList(pVoice);
    AppendVoiceList(pVoice);

    UpdateEachVoicePriority(mPrioVoiceList.GetIteratorFromPointer(pVoice),
                            mPrioVoiceList.GetEndIter());
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

    NW4R_UT_LINKLIST_FOREACH_SAFE(it, mPrioVoiceList, {
        if (it->mIsActive) {
            it->mSyncFlag |= syncFlag;
        }
    });
}

int VoiceManager::DropLowestPriorityVoice(int priority) {
    int dropped = 0;

    if (mFreeVoiceList.IsEmpty()) {
        Voice& rVoice = mPrioVoiceList.GetFront();

        if (rVoice.GetPriority() > priority) {
            return 0;
        }

        dropped = rVoice.GetAxVoiceCount();

        rVoice.Stop();
        rVoice.Free();

        if (rVoice.mCallback != NULL) {
            rVoice.mCallback(&rVoice, Voice::CALLBACK_STATUS_DROP_VOICE,
                             rVoice.mCallbackArg);
        }
    }

    return dropped;
}

} // namespace detail
} // namespace snd
} // namespace nw4r
