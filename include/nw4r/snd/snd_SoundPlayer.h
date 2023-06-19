#ifndef NW4R_SND_SOUND_PLAYER_H
#define NW4R_SND_SOUND_PLAYER_H
#include "types_nw4r.h"

namespace nw4r
{
	namespace snd
	{
		struct SoundPlayer
		{
			float FLOAT_0x28;
			float FLOAT_0x34;
			
			void StopAllSound(int);

			bool detail_IsEnabledOutputLine() const;
			int detail_GetOutputLine() const;
			float detail_GetRemoteOutVolume(int) const;
			UNKTYPE detail_FreePlayerHeap(detail::BasicSound *);
			UNKTYPE detail_InsertPriorityList(detail::BasicSound *);
			UNKTYPE detail_RemoveSoundList(detail::BasicSound *);
			UNKTYPE detail_RemovePriorityList(detail::BasicSound *);
		};
	}
}

#endif