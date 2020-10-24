#ifndef NW4R_SND_CHANNEL_H
#define NW4R_SND_CHANNEL_H
#include "types_nw4r.h"
#include "snd_WaveFile.h"
#include "snd_EnvGenerator.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			struct Channel
			{
				enum ChannelCallbackStatus
				{
					PLACEHOLDER // Empty enums are ill-formed
				};
				
				typedef void (* ChannelCallback)(Channel *, ChannelCallbackStatus, u32);
				
				static Channel * AllocChannel(int, int, int, ChannelCallback, u32);
				
				UNKTYPE Start(const WaveData &, int, u32);
				
				EnvGenerator mEnvGenerator; // at 0x0
				char UNK_0x4[0xA4];
				float FLOAT_0xA8;
				float FLOAT_0xAC;
				float FLOAT_0xB0;
				float FLOAT_0xB4;
				char UNK_0xB8[0x8];
				UNKWORD WORD_0xC0;
				UNKWORD WORD_0xC4;
			};
		}
	}
}

#endif