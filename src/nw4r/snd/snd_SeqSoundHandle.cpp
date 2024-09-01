#include "types_nw4r.h"
#include "ut_RuntimeTypeInfo.h"
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
			if (!pHandle->IsAttachedSound()) return;
			
			SeqSound * pSound = DynamicCast<SeqSound *, BasicSound>(pHandle->detail_GetAttachedSound());
			
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