#ifndef NW4R_SND_LFO_H
#define NW4R_SND_LFO_H
#include "types_nw4r.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			struct LfoParam
			{
				float FLOAT_0x0;
				float FLOAT_0x4;
				u32 WORD_0x8;
				u8 BYTE_0xC;
				
				UNKTYPE Init();
				
				inline LfoParam()
				{
					Init();
				}
			};
			
			struct Lfo
			{
				LfoParam mParam; // at 0x0
				u32 WORD_0x10;
				float FLOAT_0x14;
				
				UNKTYPE Reset();
				UNKTYPE Update(int);
				
				inline Lfo() : mParam(), WORD_0x10(0), FLOAT_0x14(0.0f) {}
				
				static int GetSinIdx(int); // inlined
				float GetValue() const;
			};
		}
	}
}

#endif