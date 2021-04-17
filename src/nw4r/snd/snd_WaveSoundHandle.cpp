#include "snd_WaveSoundHandle.h"
#include "snd_WaveSound.h"

namespace nw4r
{
    namespace snd
    {
        void WaveSoundHandle::DetachSound()
        {
            if (IsAttachedSound() && mWaveSound->mTempSpecialHandle == this)
                mWaveSound->mTempSpecialHandle = NULL;

            if (mWaveSound) mWaveSound = NULL;
        }
    }
}