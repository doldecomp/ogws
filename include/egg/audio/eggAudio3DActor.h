#ifndef EGG_AUDIO_3D_ACTOR_H
#define EGG_AUDIO_3D_ACTOR_H
#include <egg/types_egg.h>

#include <nw4r/snd.h>

namespace EGG {

class AudioSound3DActor {
public:
    static void setCommonPlayer(nw4r::snd::SoundArchivePlayer* pPlayer) {
        smCommonPlayer = pPlayer;
    }
    static void setCommonManager(nw4r::snd::Sound3DManager* pManager) {
        smCommon3DManager = pManager;
    }

protected:
    static nw4r::snd::SoundArchivePlayer* smCommonPlayer;
    static nw4r::snd::Sound3DManager* smCommon3DManager;
};

} // namespace EGG

#endif
