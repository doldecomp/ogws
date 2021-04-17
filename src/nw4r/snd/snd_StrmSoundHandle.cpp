#include "snd_StrmSoundHandle.h"
#include "snd_StrmSound.h"

namespace nw4r
{
    namespace snd
    {
        void StrmSoundHandle::DetachSound()
        {
            if (IsAttachedSound() && mStrmSound->mTempSpecialHandle == this)
                mStrmSound->mTempSpecialHandle = NULL;

            if (mStrmSound) mStrmSound = NULL;
        }
    }
}