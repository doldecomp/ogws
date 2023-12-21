#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>

namespace nw4r {
namespace snd {
namespace detail {

ExternalSoundPlayer::ExternalSoundPlayer()
    : mPlayableSoundCount(1), mVolume(1.0f) {}

ExternalSoundPlayer::~ExternalSoundPlayer() {
    BasicSoundExtPlayList::Iterator iter = mSoundList.GetBeginIter();
    while (iter != mSoundList.GetEndIter()) {
        iter++->SetExternalSoundPlayer(NULL);
    }
}

void ExternalSoundPlayer::SetPlayableSoundCount(int count) {
    mPlayableSoundCount = count;

    while (GetPlayingSoundCount() > GetPlayableSoundCount()) {
        GetLowestPrioritySound()->Shutdown();
    }
}

void ExternalSoundPlayer::InsertSoundList(BasicSound* sound) {
    mSoundList.PushBack(sound);
    sound->SetExternalSoundPlayer(this);
}

void ExternalSoundPlayer::RemoveSoundList(BasicSound* sound) {
    mSoundList.Erase(sound);
    sound->SetExternalSoundPlayer(NULL);
}

BasicSound* ExternalSoundPlayer::GetLowestPrioritySound() {
    int lowestPrio = BasicSound::PRIORITY_MAX + 1;
    BasicSound* lowestPrioSound = NULL;

    for (BasicSoundExtPlayList::Iterator iter = mSoundList.GetBeginIter();
         iter != mSoundList.GetEndIter(); ++iter) {
        int prio = iter->CalcCurrentPlayerPriority();

        if (lowestPrio > prio) {
            lowestPrioSound = &*iter;
            lowestPrio = prio;
        }
    }

    return lowestPrioSound;
}

} // namespace detail
} // namespace snd
} // namespace nw4r
