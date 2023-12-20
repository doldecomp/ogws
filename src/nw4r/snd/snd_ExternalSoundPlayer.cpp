#pragma ipa file // TODO: REMOVE AFTER REFACTOR

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
			ExternalSoundPlayer::ExternalSoundPlayer() : mPlayableSoundCount(1), mVolume(1.0f) {}
			
			ExternalSoundPlayer::~ExternalSoundPlayer()
			{
				BasicSoundExtPlayList::Iterator iter = mSoundList.GetBeginIter();
				while (iter != mSoundList.GetEndIter())
				{
					iter++->SetExternalSoundPlayer(NULL);
				}
			}
			
			void ExternalSoundPlayer::SetPlayableSoundCount(int playableSoundCount)
			{
				mPlayableSoundCount = playableSoundCount;
						
				while (GetPlayingSoundCount() > GetPlayableSoundCount())
				{
					GetLowestPrioritySound()->Shutdown();
				}
			}
			
			UNKTYPE ExternalSoundPlayer::InsertSoundList(BasicSound * pSound)
			{
				mSoundList.PushBack(pSound);
				pSound->SetExternalSoundPlayer(this);
			}
			
			UNKTYPE ExternalSoundPlayer::RemoveSoundList(BasicSound * pSound)
			{
				mSoundList.Erase(pSound);
				pSound->SetExternalSoundPlayer(NULL);
			}
			
			BasicSound * ExternalSoundPlayer::GetLowestPrioritySound()
			{
				BasicSoundExtPlayList::Iterator iter = mSoundList.GetBeginIter();
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