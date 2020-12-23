#ifndef NW4R_SND_SOUND_ACTOR_H
#define NW4R_SND_SOUND_ACTOR_H
#include "snd_SoundStartable.h"
#include "snd_ExternalSoundPlayer.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			enum
			{
				SOUND_PLAYERS_PER_ACTOR = 8
			};
			
			struct SoundActor : SoundStartable
			{
				SoundStartable & mStartable; // at 0x4
				ExternalSoundPlayer mPlayers[SOUND_PLAYERS_PER_ACTOR]; // at 0x8
				
				inline SoundActor(SoundStartable & startable) : mStartable(startable)
				{
					mPlayers[0].SetPlayableSoundCount(0x7FFFFFFF);
				}
				
				inline UNKWORD detail_ConvertLabelStringToSoundId(const char * labelString)
				{
					return mStartable.detail_ConvertLabelStringToSoundId(labelString);
				}
			};
		}
	}
}

#endif