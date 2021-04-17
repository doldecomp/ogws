#ifndef NW4R_SND_WAVESOUND_H
#define NW4R_SND_WAVESOUND_H
#include "snd_BasicSound.h"

namespace nw4r
{
    namespace snd
    {
        namespace detail
        {
            struct WaveSound : BasicSound
            {
                char UNK_0xD8[0xD8];
                WaveSoundHandle *mTempSpecialHandle; // at 0x1B0
            };
        }
    }
}

#endif