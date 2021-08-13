#ifndef EGG_AUDIO_AUDIOMGR_H
#define EGG_AUDIO_AUDIOMGR_H
#include "types_egg.h"
#include "eggAudioHeapMgr.h"
#include "eggAudioArcPlayerMgr.h"

namespace EGG
{
    class IAudioMgr
    {
    public:
        class Arg
        {

        };

        virtual UNKTYPE initialize(Arg *) {}
        virtual UNKTYPE calc() = 0;
    };

    class SimpleAudioMgr : public IAudioMgr, public SoundHeapMgr, public ArcPlayer
    {
        virtual ~SimpleAudioMgr(); // at 0x80
    };
}

#endif