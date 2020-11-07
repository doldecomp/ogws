#include "snd_Lfo.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			UNKTYPE LfoParam::Init()
			{
				FLOAT_0x0 = 0.0f;
				BYTE_0xC = 1;
				FLOAT_0x4 = 6.25f;
				WORD_0x8 = 0;
			}
			
			UNKTYPE Lfo::Reset()
			{
				WORD_0x10 = 0;
				FLOAT_0x14 = 0.0f;
			}
			
			UNKTYPE Lfo::Update(int r4)
			{
				if (WORD_0x10 < mParam.WORD_0x8)
				{
					//u32 r0 = WORD_0x10 + r4;
					if (WORD_0x10 + r4 <= mParam.WORD_0x8)
					{
						WORD_0x10 += r4;
						return;
					}
					//r0 = mParam.WORD_0x8 - WORD_0x10;
					r4 -= mParam.WORD_0x8 - WORD_0x10;
					WORD_0x10 = mParam.WORD_0x8;
				}
				//8003B2B4
				FLOAT_0x14 += mParam.FLOAT_0x4 * r4 / 1000.0f;
				FLOAT_0x14 -= (int)FLOAT_0x14;
			}
			
			int Lfo::GetSinIdx(int i)
			{
				static const u8 sinTable[0x21] = {
					0, 6, 12,
					19, 25, 31,
					37, 43, 49,
					54, 60, 65,
					71, 76, 81,
					85, 90, 94,
					98, 102, 106,
					109, 112, 115,
					117, 120, 122,
					123, 125, 126,
					126, 127, 127
				};
				
				if (i < 0x20) return (s8)sinTable[i];
				if (i < 0x40) return (s8)sinTable[0x20 - (int)(i - 0x20)];
				if (i < 0x60) return (s8)-sinTable[i - 0x40];
				return (s8)-sinTable[0x20 - (i - 0x60)];
			}
			
			float Lfo::GetValue() const
			{
				if (0.0f == mParam.FLOAT_0x0) return 0.0f;
				if (WORD_0x10 < mParam.WORD_0x8) return 0.0f;
				
				float fSin = GetSinIdx(4.0f * (32.0f * FLOAT_0x14)) / 127.0f;
				return (fSin *= mParam.FLOAT_0x0) *= mParam.BYTE_0xC;
			}
		}
	}
}