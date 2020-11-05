#ifndef NW4R_SND_FX_DELAY_H
#define NW4R_SND_FX_DELAY_H
#include <AXFXDelay.h>
#include "types_nw4r.h"
#include "snd_FxBase.h"
#include "snd_AxfxImpl.h"

namespace nw4r
{
	namespace snd
	{
		struct FxDelay : FxBase
		{
			//sizeof(DelayParam) = 0xc
			struct DelayParam
			{
				float FLOAT_0x0;
				float FLOAT_0x4;
				float FLOAT_0x8;
			};
			
			FxDelay();
			
			inline ~FxDelay()
			{
				Shutdown();
				ReleaseWorkBuffer();
			}
			
			u32 GetRequiredMemSize();
			virtual UNKTYPE AssignWorkBuffer(void *, u32); // at 0x18
			virtual UNKTYPE ReleaseWorkBuffer(); // at 0x1c
			
			bool StartUp(); // at 0xc
			UNKTYPE Shutdown(); // at 0x10
			bool SetParam(const DelayParam &);
			UNKTYPE UpdateBuffer(int, void **, u32, SampleFormat, float, OutputMode); // at 0x14
			
			detail::AxfxImpl mAxfxImpl;
			
			DelayParam mParam; // at 0x18
			AXFXDelay mAXFXDelay; // 0x24
			
			u32 INT_0xC4;
			u32 INT_0xC8;
			u32 INT_0xCC;
		};
	}
}

#endif