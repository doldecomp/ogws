#ifndef NW4R_SND_FX_BASE_H
#define NW4R_SND_FX_BASE_H
#include "types_nw4r.h"
#include "ut_LinkList.h"
#include "snd_AxManager.h"

namespace nw4r
{
	namespace snd
	{
		enum SampleFormat
		{
			SAMPLE_FORMAT_0
		};
		
		struct FxBase
		{
			virtual ~FxBase(); // at 0x4
			virtual bool StartUp(); // at 0x8
			virtual UNKTYPE Shutdown(); // at 0xc
			virtual UNKTYPE UpdateBuffer(int, void **, u32, SampleFormat, float, OutputMode); // at 0x10
			
			ut::LinkListNode mNode; // at 0x4
		};
	}
}

#endif