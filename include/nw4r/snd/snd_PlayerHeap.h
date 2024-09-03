#ifndef NW4R_SND_PLAYER_HEAP_H
#define NW4R_SND_PLAYER_HEAP_H
#include <nw4r/snd/snd_SoundHeap.h>
#include <nw4r/types_nw4r.h>

namespace nw4r {
namespace snd {
namespace detail {

class PlayerHeap : public SoundHeap {
    virtual ~PlayerHeap() {} // at 0x8
};

} // namespace detail
} // namespace snd
} // namespace nw4r

#endif
