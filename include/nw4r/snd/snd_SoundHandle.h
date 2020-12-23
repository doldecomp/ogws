#ifndef NW4R_SND_SOUND_HANDLE_H
#define NW4R_SND_SOUND_HANDLE_H
#include "types_nw4r.h"

namespace nw4r
{
	namespace snd
	{
		struct SoundHandle
		{
			detail::BasicSound * mSound;
			
			UNKTYPE DetachSound();
			UNKTYPE detail_AttachSoundAsTempHandle(detail::BasicSound *);
			
			inline SoundHandle() : mSound(NULL) {}
			
			inline ~SoundHandle()
			{
				DetachSound();
			}
		};
	}
}

#endif