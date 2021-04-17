#ifndef NW4R_SND_STRMSOUND_H
#define NW4R_SND_STRMSOUND_H
#include "types_nw4r.h"
#include "snd_BasicSound.h"

namespace nw4r
{
    namespace snd
    {
        namespace detail
        {
            struct StrmSound : BasicSound
            {
                char UNK_0xD8[0x848];
                StrmSoundHandle *mTempSpecialHandle; // at 0x920
            };
        }
    }
}

#endif