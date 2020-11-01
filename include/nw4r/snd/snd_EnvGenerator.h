#ifndef NW4R_SND_ENV_GENERATOR_H
#define NW4R_SND_ENV_GENERATOR_H
#include "types_nw4r.h"
#include "snd_WaveFile.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			//sizeof(EnvGenerator) = 0x18
			struct EnvGenerator
			{
				static const volatile float VOLUME_INIT;
				static const s16 DecibelSquareTable[0x80];
				
				enum Status
				{
					Status_Attack,
					Status_Decay,
					Status_Sustain,
					Status_Release
				};
				
				float CalcRelease(int); //inlined
				
				EnvGenerator();
				
				UNKTYPE Init(float);
				UNKTYPE Reset(float);
				float GetValue() const;
				void Update(int);
				UNKTYPE SetAttack(int);
				UNKTYPE SetDecay(int);
				UNKTYPE SetSustain(int);
				UNKTYPE SetRelease(int);
				
				Status mStatus; // at 0x0
				float mValue; // at 0x4
				float mDecay; // at 0x8
				float mRelease; // at 0xc
				float mAttack; // at 0x10
				u8 mSustain; // at 0x14
				
				inline Status GetStatus() const { return mStatus; }
				inline void SetStatus(Status status) { mStatus = status; }
			};
		}
	}
}

#endif