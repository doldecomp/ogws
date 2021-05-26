#ifndef NW4R_SND_SOUND_SYSTEM_H
#define NW4R_SND_SOUND_SYSTEM_H
#include "types_nw4r.h"

namespace nw4r
{
	namespace snd
	{
        struct SoundSystem
        {
            struct SoundSystemParam
            {

            };

            void InitSoundSystem(s32, s32);
            void InitSoundSystem(const SoundSystemParam&, void *, u32);
            static void ShutdownSoundSystem();
            static void WaitForResetReady();
            UNKWORD GetRequiredMemSize(const SoundSystemParam &);
        };
	}
}

#endif