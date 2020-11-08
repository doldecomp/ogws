#ifndef NW4R_SND_VOICE_MANAGER_H
#define NW4R_SND_VOICE_MANAGER_H
#include "types_nw4r.h"
#include "snd_Voice.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			struct VoiceManager
			{
				static VoiceManager * GetInstance();
				UNKTYPE UpdateAllVoicesSync(u32);
				Voice * AllocVoice(int, int, int, Voice::VoiceCallback, void *);
			};
		}
	}
}

#endif