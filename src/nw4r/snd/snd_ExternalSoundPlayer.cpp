#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace snd {
namespace detail {

ExternalSoundPlayer::ExternalSoundPlayer()
    : mPlayableSoundCount(1), mVolume(1.0f) {}

ExternalSoundPlayer::~ExternalSoundPlayer() {
    NW4R_UT_LIST_SAFE_FOREACH(mSoundList,
        it->SetExternalSoundPlayer(NULL);
    );
}

void ExternalSoundPlayer::SetPlayableSoundCount(int count) {
    mPlayableSoundCount = count;

    while (GetPlayingSoundCount() > GetPlayableSoundCount()) {
        GetLowestPrioritySound()->Shutdown();
    }
}

void ExternalSoundPlayer::InsertSoundList(BasicSound* pSound) {
    mSoundList.PushBack(pSound);
    pSound->SetExternalSoundPlayer(this);
}

void ExternalSoundPlayer::RemoveSoundList(BasicSound* pSound) {
    mSoundList.Erase(pSound);
    pSound->SetExternalSoundPlayer(NULL);
}

BasicSound* ExternalSoundPlayer::GetLowestPrioritySound() {
    int lowestPrio = BasicSound::PRIORITY_MAX + 1;
    BasicSound* pLowest = NULL;

    for (BasicSoundExtPlayList::Iterator it = mSoundList.GetBeginIter();
         it != mSoundList.GetEndIter(); ++it) {

        int prio = it->CalcCurrentPlayerPriority();

        if (lowestPrio > prio) {
            pLowest = &*it;
            lowestPrio = prio;
        }
    }

    return pLowest;
}

} // namespace detail
} // namespace snd
} // namespace nw4r
