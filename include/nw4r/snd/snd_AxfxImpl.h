#ifndef NW4R_SND_AXFX_IMPL_H
#define NW4R_SND_AXFX_IMPL_H
#include "types_nw4r.h"
#include <AXFXHooks.h>

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			struct AxfxImpl
			{
				static AxfxImpl * mCurrentFx;
				static u32 mAllocatedSize;
				
				bool CreateHeap(void *, u32);
				UNKTYPE DestroyHeap();
				UNKTYPE HookAlloc(AXFXAllocHook *, AXFXFreeHook *);
				UNKTYPE RestoreAlloc(AXFXAllocHook, AXFXFreeHook);
				
				static void * Alloc(u32);
				static void Free(void *);
				
				char UNK_0x0[0x4];
				UNKTYPE * mHeap; // at 0x4
				u32 mAllocCount; // at 0x8
			};
		}
	}
}

#endif