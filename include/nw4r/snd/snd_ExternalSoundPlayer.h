#ifndef NW4R_SND_EXTERNAL_SOUND_PLAYER_H
#define NW4R_SND_EXTERNAL_SOUND_PLAYER_H
#include "types_nw4r.h"
#include "ut_LinkList.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			struct ExternalSoundPlayer
			{
				ExternalSoundPlayer();
				~ExternalSoundPlayer();
				ut::LinkList<struct BasicSound, 0xD0> mSoundList; // at 0x0
				u16 mPlayableSoundCount; // at 0xc
				float FLOAT_0x10;
				
				UNKTYPE RemoveSoundList(BasicSound *);
			};
		}
	}
}

#endif