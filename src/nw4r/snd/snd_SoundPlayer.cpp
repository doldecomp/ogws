#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>
#include <nw4r/ut.h>

#include <cstring>

namespace nw4r {
namespace snd {

SoundPlayer::SoundPlayer()
    : mPlayableCount(1), mPlayableLimit(1), mUsePlayerHeap(false) {
    InitParam();
}

SoundPlayer::~SoundPlayer() {
    StopAllSound(0);
}

void SoundPlayer::InitParam() {
    OSInitMutex(&mMutex);

    mOutputLineFlag = OUTPUT_LINE_MAIN;
    mVolume = 1.0f;
    mOutputLineFlagEnable = false;

    mMainOutVolume = 1.0f;
    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        mRemoteOutVolume[i] = 1.0f;
    }
}

void SoundPlayer::Update() {
    ut::detail::AutoLock<OSMutex> lock(mMutex);

    NW4R_UT_LIST_SAFE_FOREACH(mSoundList,
        it->Update();
    )

    detail_SortPriorityList();
}

void SoundPlayer::StopAllSound(int frames) {
    ut::detail::AutoLock<OSMutex> lock(mMutex);

    NW4R_UT_LIST_SAFE_FOREACH(mSoundList,
        it->Stop(frames);
    )
}

void SoundPlayer::PauseAllSound(bool flag, int frames) {
    ut::detail::AutoLock<OSMutex> lock(mMutex);

    NW4R_UT_LIST_SAFE_FOREACH(mSoundList,
        it->Pause(flag, frames);
    )
}

void SoundPlayer::SetVolume(f32 volume) {
    mVolume = ut::Clamp(volume, 0.0f, 1.0f);
}

int SoundPlayer::detail_GetOutputLine() const {
    return mOutputLineFlag;
}

bool SoundPlayer::detail_IsEnabledOutputLine() const {
    return mOutputLineFlagEnable;
}

f32 SoundPlayer::detail_GetRemoteOutVolume(int i) const {
    return mRemoteOutVolume[i];
}

void SoundPlayer::detail_InsertSoundList(detail::BasicSound* pSound) {
    mSoundList.PushBack(pSound);
    pSound->SetSoundPlayer(this);
}

void SoundPlayer::detail_RemoveSoundList(detail::BasicSound* pSound) {
    ut::detail::AutoLock<OSMutex> lock(mMutex);

    mSoundList.Erase(pSound);
    pSound->SetSoundPlayer(NULL);
}

void SoundPlayer::detail_InsertPriorityList(detail::BasicSound* pSound) {
    ut::detail::AutoLock<OSMutex> lock(mMutex);

    detail::BasicSoundPlayerPrioList::Iterator it =
        mPriorityList.GetBeginIter();

    for (; it != mPriorityList.GetEndIter(); ++it) {
        if (pSound->CalcCurrentPlayerPriority() <
            it->CalcCurrentPlayerPriority()) {
            break;
        }
    }

    mPriorityList.Insert(it, pSound);
}

void SoundPlayer::detail_RemovePriorityList(detail::BasicSound* pSound) {
    ut::detail::AutoLock<OSMutex> lock(mMutex);
    mPriorityList.Erase(pSound);
}

void SoundPlayer::detail_SortPriorityList() {
    ut::detail::AutoLock<OSMutex> lock(mMutex);

    detail::BasicSoundPlayerPrioList
        listsByPrio[detail::BasicSound::PRIORITY_MAX + 1];

    while (!mPriorityList.IsEmpty()) {
        detail::BasicSound& rSound = mPriorityList.GetFront();
        mPriorityList.PopFront();
        listsByPrio[rSound.CalcCurrentPlayerPriority()].PushBack(&rSound);
    }

    for (int i = 0; i < detail::BasicSound::PRIORITY_MAX + 1; i++) {
        while (!listsByPrio[i].IsEmpty()) {
            detail::BasicSound& rSound = listsByPrio[i].GetFront();
            listsByPrio[i].PopFront();
            mPriorityList.PushBack(&rSound);
        }
    }
}

detail::SeqSound* SoundPlayer::detail_AllocSeqSound(
    int priority, int startPriority,
    detail::BasicSound::AmbientArgInfo* pArgInfo,
    detail::ExternalSoundPlayer* pExtPlayer, u32 id,
    detail::SoundInstanceManager<detail::SeqSound>* pManager) {

    ut::detail::AutoLock<OSMutex> lock(mMutex);

    if (pManager == NULL) {
        return NULL;
    }

    int priorityReduction = CalcPriorityReduction(pArgInfo, id);

    startPriority = ut::Clamp(startPriority + priorityReduction, 0,
                              detail::BasicSound::PRIORITY_MAX);

    if (!CheckPlayableSoundCount(startPriority, pExtPlayer)) {
        return NULL;
    }

    detail::SeqSound* pSound = pManager->Alloc(startPriority);
    if (pSound == NULL) {
        return NULL;
    }

    detail_AllocPlayerHeap(pSound);

    if (pArgInfo != NULL) {
        InitAmbientArg(pSound, pArgInfo);
    }

    pSound->SetPriority(priority);
    pSound->GetAmbientParam().priority = priorityReduction;

    detail_InsertSoundList(pSound);

    if (pExtPlayer != NULL) {
        pExtPlayer->InsertSoundList(pSound);
    }

    detail_InsertPriorityList(pSound);

    return pSound;
}

detail::StrmSound* SoundPlayer::detail_AllocStrmSound(
    int priority, int startPriority,
    detail::BasicSound::AmbientArgInfo* pArgInfo,
    detail::ExternalSoundPlayer* pExtPlayer, u32 id,
    detail::SoundInstanceManager<detail::StrmSound>* pManager) {

    ut::detail::AutoLock<OSMutex> lock(mMutex);

    if (pManager == NULL) {
        return NULL;
    }

    int priorityReduction = CalcPriorityReduction(pArgInfo, id);

    startPriority = ut::Clamp(startPriority + priorityReduction, 0,
                              detail::BasicSound::PRIORITY_MAX);

    if (!CheckPlayableSoundCount(startPriority, pExtPlayer)) {
        return NULL;
    }

    detail::StrmSound* pSound = pManager->Alloc(startPriority);
    if (pSound == NULL) {
        return NULL;
    }

    detail_AllocPlayerHeap(pSound);

    if (pArgInfo != NULL) {
        InitAmbientArg(pSound, pArgInfo);
    }

    pSound->SetPriority(priority);
    pSound->GetAmbientParam().priority = priorityReduction;

    detail_InsertSoundList(pSound);

    if (pExtPlayer != NULL) {
        pExtPlayer->InsertSoundList(pSound);
    }

    detail_InsertPriorityList(pSound);

    return pSound;
}

detail::WaveSound* SoundPlayer::detail_AllocWaveSound(
    int priority, int startPriority,
    detail::BasicSound::AmbientArgInfo* pArgInfo,
    detail::ExternalSoundPlayer* pExtPlayer, u32 id,
    detail::SoundInstanceManager<detail::WaveSound>* pManager) {

    ut::detail::AutoLock<OSMutex> lock(mMutex);

    if (pManager == NULL) {
        return NULL;
    }

    int priorityReduction = CalcPriorityReduction(pArgInfo, id);

    startPriority = ut::Clamp(startPriority + priorityReduction, 0,
                              detail::BasicSound::PRIORITY_MAX);

    if (!CheckPlayableSoundCount(startPriority, pExtPlayer)) {
        return NULL;
    }

    detail::WaveSound* pSound = pManager->Alloc(startPriority);
    if (pSound == NULL) {
        return NULL;
    }

    detail_AllocPlayerHeap(pSound);

    if (pArgInfo != NULL) {
        InitAmbientArg(pSound, pArgInfo);
    }

    pSound->SetPriority(priority);
    pSound->GetAmbientParam().priority = priorityReduction;

    detail_InsertSoundList(pSound);

    if (pExtPlayer != NULL) {
        pExtPlayer->InsertSoundList(pSound);
    }

    detail_InsertPriorityList(pSound);

    return pSound;
}

int SoundPlayer::CalcPriorityReduction(
    detail::BasicSound::AmbientArgInfo* pArgInfo, u32 id) {

    int priority = 0;

    if (pArgInfo != NULL) {
        SoundParam param;

        pArgInfo->paramUpdateCallback->detail_Update(
            &param, id, NULL, pArgInfo->arg,
            detail::BasicSound::AmbientParamUpdateCallback::
                PARAM_UPDATE_PRIORITY);

        priority = param.priority;
    }

    return priority;
}

void SoundPlayer::InitAmbientArg(detail::BasicSound* pSound,
                                 detail::BasicSound::AmbientArgInfo* pArgInfo) {

    if (pArgInfo == NULL) {
        return;
    }

    void* pExtArg = pArgInfo->argAllocaterCallback->detail_AllocAmbientArg(
        pArgInfo->argSize);

    if (pExtArg == NULL) {
        return;
    }

    std::memcpy(pExtArg, pArgInfo->arg, pArgInfo->argSize);

    pSound->SetAmbientParamCallback(pArgInfo->paramUpdateCallback,
                                    pArgInfo->argUpdateCallback,
                                    pArgInfo->argAllocaterCallback, pExtArg);
}

void SoundPlayer::SetPlayableSoundCount(int count) {
    ut::detail::AutoLock<OSMutex> lock(mMutex);

    mPlayableCount = count;

    if (mUsePlayerHeap) {
        count = ut::Clamp<u16>(count, 0, mPlayableLimit);
        mPlayableCount = count;
    }

    while (GetPlayingSoundCount() > GetPlayableSoundCount()) {
        detail::BasicSound* pDropSound = detail_GetLowestPrioritySound();
        pDropSound->Shutdown();
    }
}

void SoundPlayer::detail_SetPlayableSoundLimit(int limit) {
    mPlayableLimit = limit;
}

bool SoundPlayer::CheckPlayableSoundCount(
    int startPriority, detail::ExternalSoundPlayer* pExtPlayer) {

    ut::detail::AutoLock<OSMutex> lock(mMutex);

    if (GetPlayableSoundCount() == 0) {
        return false;
    }

    while (GetPlayingSoundCount() >= GetPlayableSoundCount()) {
        detail::BasicSound* pDropSound = detail_GetLowestPrioritySound();

        if (pDropSound == NULL) {
            return false;
        }

        if (startPriority < pDropSound->CalcCurrentPlayerPriority()) {
            return false;
        }

        pDropSound->Shutdown();
    }

    if (pExtPlayer != NULL) {
        if (pExtPlayer->GetPlayableSoundCount() == 0) {
            return false;
        }

        while (pExtPlayer->GetPlayingSoundCount() >=
               pExtPlayer->GetPlayableSoundCount()) {

            detail::BasicSound* pDropSound =
                pExtPlayer->GetLowestPrioritySound();

            if (pDropSound == NULL) {
                return false;
            }

            if (startPriority < pDropSound->CalcCurrentPlayerPriority()) {
                return false;
            }

            pDropSound->Shutdown();
        }
    }

    return true;
}

void SoundPlayer::detail_AppendPlayerHeap(detail::PlayerHeap* pHeap) {
    ut::detail::AutoLock<OSMutex> lock(mMutex);

    pHeap->SetSoundPlayer(this);
    mHeapList.PushBack(pHeap);

    mUsePlayerHeap = true;
}

detail::PlayerHeap*
SoundPlayer::detail_AllocPlayerHeap(detail::BasicSound* pSound) {
    ut::detail::AutoLock<OSMutex> lock(mMutex);

    if (mHeapList.IsEmpty()) {
        return NULL;
    }

    detail::PlayerHeap& rHeap = mHeapList.GetFront();
    mHeapList.PopFront();

    rHeap.SetSound(pSound);
    pSound->SetPlayerHeap(&rHeap);
    rHeap.Clear();

    return &rHeap;
}

void SoundPlayer::detail_FreePlayerHeap(detail::BasicSound* pSound) {
    ut::detail::AutoLock<OSMutex> lock(mMutex);

    detail::PlayerHeap* pHeap = pSound->GetPlayerHeap();

    if (pHeap != NULL) {
        mHeapList.PushBack(pHeap);
    }

    if (pHeap != NULL) {
        pHeap->SetSound(NULL);
    }

    pSound->SetPlayerHeap(NULL);
}

} // namespace snd
} // namespace nw4r
