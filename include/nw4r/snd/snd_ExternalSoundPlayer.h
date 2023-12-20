#ifndef NW4R_SND_EXTERNAL_SOUND_PLAYER_H
#define NW4R_SND_EXTERNAL_SOUND_PLAYER_H
#include "snd_BasicSound.h"
#include "types_nw4r.h"
#include "ut_LinkList.h"

namespace nw4r {
namespace snd {
namespace detail {

class ExternalSoundPlayer {
public:
    ExternalSoundPlayer();
    ~ExternalSoundPlayer();

    f32 detail_GetVolume() const { return mVolume; }

    int GetPlayableSoundCount() const { return mPlayableSoundCount; }
    int GetPlayingSoundCount() const { return mSoundList.GetSize(); }

    template <typename TForEachFunc>
    TForEachFunc ForEachSound(TForEachFunc func, bool reverse) {
        if (reverse) {
            BasicSoundExtPlayList::RevIterator it =
                mSoundList.GetBeginReverseIter();

            while (it != mSoundList.GetEndReverseIter()) {
                BasicSoundExtPlayList::RevIterator curr = it;

                SoundHandle handle;
                handle.detail_AttachSoundAsTempHandle(&*curr);
                func(handle);

                if (handle.IsAttachedSound()) {
                    ++it;
                }
            }
        } else {
            BasicSoundExtPlayList::Iterator it = mSoundList.GetBeginIter();

            while (it != mSoundList.GetEndIter()) {
                BasicSoundExtPlayList::Iterator curr = it++;

                SoundHandle handle;
                handle.detail_AttachSoundAsTempHandle(&*curr);
                func(handle);
            }
        }

        return func;
    }

    void SetPlayableSoundCount(int);
    UNKTYPE InsertSoundList(BasicSound*);
    UNKTYPE RemoveSoundList(BasicSound*);
    BasicSound* GetLowestPrioritySound();

private:
    BasicSoundExtPlayList mSoundList; // at 0x0
    u16 mPlayableSoundCount;          // at 0xc
    f32 mVolume;                      // at 0x10
};

} // namespace detail
} // namespace snd
} // namespace nw4r

#endif
