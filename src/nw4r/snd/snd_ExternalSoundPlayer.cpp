#pragma ipa file
#include "snd_ExternalSoundPlayer.h"
#include "snd_BasicSound.h"

namespace nw4r
{
	namespace snd
	{
		using namespace ut;
		
		namespace detail
		{
			ExternalSoundPlayer::ExternalSoundPlayer() : mPlayableSoundCount(1), FLOAT_0x10(1.0f) {}
			
			ExternalSoundPlayer::~ExternalSoundPlayer()
			{
				LinkList<BasicSound, 0xD0>::Iterator iter = mSoundList.GetBeginIter();
				while (iter != mSoundList.GetEndIter())
				{
					iter++->mExternalSoundPlayer = NULL;
				}
			}
			
			void ExternalSoundPlayer::SetPlayableSoundCount(int playableSoundCount)
			{
				mPlayableSoundCount = playableSoundCount;
						
				while ((int)mSoundList.mCount > mPlayableSoundCount)
				{
					GetLowestPrioritySound()->Shutdown();
				}
			}
			
			UNKTYPE ExternalSoundPlayer::InsertSoundList(BasicSound * pSound)
			{
				mSoundList.PushBack(pSound);
				pSound->mExternalSoundPlayer = this;
			}
			
			UNKTYPE ExternalSoundPlayer::RemoveSoundList(BasicSound * pSound)
			{
				mSoundList.Erase(pSound);
				pSound->mExternalSoundPlayer = NULL;
			}
			
			BasicSound * ExternalSoundPlayer::GetLowestPrioritySound()
			{
				LinkList<BasicSound, 0xD0>::Iterator iter = mSoundList.GetBeginIter();
				int currentPriority;
				int lowestPriority = 0x80;
				BasicSound * lowestPrioritySound = NULL;
				
				while (iter != mSoundList.GetEndIter())
				{
					currentPriority = iter->CalcCurrentPlayerPriority();
					if (lowestPriority > currentPriority)
					{
						lowestPrioritySound = &*iter;
						lowestPriority = currentPriority;
					}
					++iter;
				}
				
				return lowestPrioritySound;
			}
		}
	}
}