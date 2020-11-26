#ifndef NW4R_SND_BASIC_PLAYER_H
#define NW4R_SND_BASIC_PLAYER_H
#include "snd_Pan.h"
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
				inline virtual ~BasicPlayer() {} // at 0x8
				virtual UNKWORD Start() = 0; // at 0xc
				virtual UNKTYPE Stop() = 0; // at 0x10
				virtual UNKTYPE Pause(bool) = 0; // at 0x14
				virtual bool IsActive() const = 0; // at 0x18
				virtual bool IsStarted() const = 0; // at 0x1c
				virtual bool IsPause() const = 0; // at 0x20
				
				BasicPlayer();
				void InitParam();
				
				void SetFxSend(AuxBus, float);
				float GetFxSend(AuxBus) const;
				void SetRemoteOutVolume(int, float);
				float GetRemoteOutVolume(int) const;
				float GetRemoteSend(int) const;
				float GetRemoteFxSend(int) const;
				
				u32 mId; // at 0x4
				float FLOAT_0x8;
				float FLOAT_0xC;
				float FLOAT_0x10;
				float FLOAT_0x14;
				float mLpfFreq; // at 0x18
				char UNK_0x1C[0x4];
				UNKWORD WORD_0x20;
				float FLOAT_0x24;
				float FLOAT_0x28;
				float ARR_0x2C[3];
				float mRemoteOutputVolumes[4]; // at 0x38
				float ARR_0x48[4];
				float ARR_0x58[4];
				char mRemoteFilter; // at 0x68
				PanMode mPanMode; // at 0x6c
				PanCurve mPanCurve; // at 0x70
			};
		}
	}
}

#endif