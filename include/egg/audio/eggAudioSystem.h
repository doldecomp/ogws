#ifndef EGG_AUDIO_AUDIOSYSTEM_H
#define EGG_AUDIO_AUDIOSYSTEM_H
#include "types_egg.h"

namespace EGG
{
    struct AudioSystem
    {
        AudioSystem();
        ~AudioSystem();
        void calc();

        f32 FLOAT_0x0;
        UNKWORD WORD_0x4;
        UNKWORD WORD_0x8;
        UNKWORD WORD_0xC;

        static AudioSystem *sInstance;
    };
}

#endif