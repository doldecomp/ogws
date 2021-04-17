#include "snd_SoundHandle.h"
#include "snd_BasicSound.h"

namespace nw4r
{
	namespace snd
	{
        void SoundHandle::detail_AttachSoundAsTempHandle(detail::BasicSound *pBasicSound)
        {
            mSound = pBasicSound;

            if (pBasicSound->IsAttachedTempGeneralHandle())
                mSound->DetachTempGeneralHandle();

            if (mSound->IsAttachedTempSpecialHandle())
                mSound->DetachTempSpecialHandle();

            mSound->mTempGeneralHandle = this;
        }

        void SoundHandle::detail_AttachSound(detail::BasicSound *pBasicSound)
        {
            mSound = pBasicSound;

            if (pBasicSound->IsAttachedGeneralHandle())
                mSound->DetachGeneralHandle();

            mSound->mGeneralHandle = this;
        }

        void SoundHandle::DetachSound()
        {
            if (mSound)
            {
                if (mSound->mGeneralHandle == this)
                    mSound->mGeneralHandle = NULL;

                if (mSound->mTempGeneralHandle == this)
                    mSound->mTempGeneralHandle = NULL;
            }

            if (mSound)
            {
                mSound = NULL;
            }
        }
	}
}