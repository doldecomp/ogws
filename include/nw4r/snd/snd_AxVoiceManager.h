#ifndef NW4R_SND_AX_VOICE_MANAGER
#define NW4R_SND_AX_VOICE_MANAGER
#include "types_nw4r.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			struct AxVoiceManager
			{
				static AxVoiceManager& GetInstance();

				AxVoiceManager();

				void FreeAllReservedAxVoice();
				
				void ReserveForFreeAxVoice(AxVoice*);
			};
		}
	}
}

#endif