#include "types_nw4r.h"
#include "ut_RTTI.h"
#include "snd_SeqSound.h"
#include "snd_SeqSoundHandle.h"

namespace nw4r
{
	using namespace ut;
	
	namespace snd
	{
		SeqSoundHandle::SeqSoundHandle(SoundHandle * pHandle) : mSound(NULL)
		{
			if (!pHandle) return;
			if (!pHandle->mSound) return;
			
			SeqSound * pSound = DynamicCast<SeqSound *, BasicSound>(pHandle->mSound);
			
			if (pSound)
			{	
				mSound = pSound;
				
				if (mSound->IsAttachedTempGeneralHandle()) mSound->DetachTempGeneralHandle();
				if (mSound->IsAttachedTempSpecialHandle()) mSound->DetachTempSpecialHandle();
				
				mSound->mTempSpecialHandle = this;
			}
		}
		
		void SeqSoundHandle::DetachSound()
		{
			if (mSound && mSound->mTempSpecialHandle == this) mSound->mTempSpecialHandle = NULL;
			if (mSound) mSound = NULL;
		}
	}
}