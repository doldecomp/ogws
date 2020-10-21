#ifndef NW4R_SND_VOICE_MANAGER_H
#define NW4R_SND_VOICE_MANAGER_H
#include "types_nw4r.h"

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
			};
		}
	}
}

#endif