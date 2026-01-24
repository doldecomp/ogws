#ifndef EGG_AUDIO_ACTOR_H
#define EGG_AUDIO_ACTOR_H
#include <egg/types_egg.h>

#include <nw4r/snd.h>

namespace EGG {

template <int N> class AudioSoundActorBaseWithCamera {
public:
    static void setCommonManager(nw4r::snd::Sound3DManager* pManager, int idx) {
        smCommon3DManager[idx] = pManager;
    }

protected:
    static nw4r::snd::Sound3DManager* smCommon3DManager[N];
};

} // namespace EGG

#endif
