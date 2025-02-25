#ifndef NW4R_SND_PLAYER_HEAP_H
#define NW4R_SND_PLAYER_HEAP_H
#include <nw4r/types_nw4r.h>

#include <nw4r/snd/snd_SoundHeap.h>

namespace nw4r {
namespace snd {

// Forward declarations
class SoundPlayer;

namespace detail {
class BasicSound;
} // namespace detail

namespace detail {

class PlayerHeap : public SoundHeap {
public:
    PlayerHeap() : mSound(NULL), mPlayer(NULL) {}
    virtual ~PlayerHeap() {} // at 0x8

    void SetSound(BasicSound* pSound) {
        mSound = pSound;
    }

    void SetSoundPlayer(SoundPlayer* pPlayer) {
        mPlayer = pPlayer;
    }

public:
    NW4R_UT_LINKLIST_NODE_DECL(); // at 0x2C

private:
    BasicSound* mSound;   // at 0x34
    SoundPlayer* mPlayer; // at 0x38
};

NW4R_UT_LINKLIST_TYPEDEF_DECL(PlayerHeap);

} // namespace detail
} // namespace snd
} // namespace nw4r

#endif
