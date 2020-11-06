#ifndef NW4R_SND_FX_REVERB_HI_H
#define NW4R_SND_FX_REVERB_HI_H
#include <AXFXReverbHi.h>
#include "snd_FxBase.h"
#include "snd_AxfxImpl.h"
#include "types_nw4r.h"

namespace nw4r
{
	namespace snd
	{
		struct FxReverbHi : FxBase
		{
			//sizeof(ReverbHiParam) = 0xc
			struct ReverbHiParam
			{
				float FLOAT_0x0;
				float FLOAT_0x4;
				float FLOAT_0x8;
			};
			
			FxReverbHi();
			
			inline ~FxReverbHi()
			{
				Shutdown();
				ReleaseWorkBuffer();
			}
			
			u32 GetRequiredMemSize();
			virtual UNKTYPE AssignWorkBuffer(void *, u32); // at 0x18
			virtual UNKTYPE ReleaseWorkBuffer(); // at 0x1c
			
			bool StartUp(); // at 0xc
			UNKTYPE Shutdown(); // at 0x10
			bool SetParam(const ReverbHiParam &);
			UNKTYPE UpdateBuffer(int, void **, u32, SampleFormat, float, OutputMode); // at 0x14
			
			detail::AxfxImpl mAxfxImpl; // at 0xc
			ReverbHiParam mParam; // at 0x18
			
			AXFXReverbHi mAXFXReverbHi; // at 0x24
			
			u32 INT_0x64;
			u32 INT_0x68;
			u32 INT_0x6C;
			
			u32 INT_0x70;
			u32 INT_0x74;
			u32 INT_0x78;
			
			u32 INT_0x7C;
			u32 INT_0x80;
			u32 INT_0x84;
		};
	}
}

#endif