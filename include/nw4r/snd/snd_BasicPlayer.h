#ifndef NW4R_SND_BASIC_PLAYER_H
#define NW4R_SND_BASIC_PLAYER_H
#include "snd_AxManager.h"
#include "types_nw4r.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			struct BasicPlayer
			{
				inline virtual ~BasicPlayer() {}
				virtual UNKTYPE Start() = 0;
				virtual UNKTYPE Stop() = 0;
				virtual UNKTYPE Pause(bool) = 0;
				virtual bool IsActive() const = 0;
				virtual bool IsStarted() const = 0;
				virtual bool IsPause() const = 0;
				
				BasicPlayer();
				void InitParam();
				
				void SetFxSend(AuxBus, float);
				float GetFxSend(AuxBus) const;
				void SetRemoteOutVolume(int, float);
				float GetRemoteOutVolume(int) const;
				float GetRemoteSend(int) const;
				float GetRemoteFxSend(int) const;
				
				UNKWORD WORD_0x4;
				float FLOAT_0x8;
				float FLOAT_0xC;
				float FLOAT_0x10;
				float FLOAT_0x14;
				float FLOAT_0x18;
				char UNK_0x1C[0x4];
				UNKWORD WORD_0x20;
				float FLOAT_0x24;
				float FLOAT_0x28;
				float ARR_0x2C[3];
				float mRemoteOutputVolumes[4]; // at 0x38
				float ARR_0x48[4];
				float ARR_0x58[4];
				char BYTE_0x68;
				UNKWORD WORD_0x6C;
				UNKWORD WORD_0x70;
			};
		}
	}
}

#endif