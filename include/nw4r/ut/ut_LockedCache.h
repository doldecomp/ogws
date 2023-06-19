#ifndef NW4R_UT_LOCKED_CACHE
#define NW4R_UT_LOCKED_CACHE
#include "types_nw4r.h"
#include <revolution/OS/OSMutex.h>
#include <revolution/OS/OSCache.h>
#include <revolution/OS/OSThread.h>

namespace nw4r
{
	namespace ut
	{
		namespace LC
		{
			UNKTYPE Enable();
			UNKTYPE Disable();
			bool Lock();
			UNKTYPE Unlock();
			UNKTYPE LoadBlocks(void *, void *, u32);
			UNKTYPE StoreBlocks(void *, void *, u32);
			UNKTYPE StoreData(void *, void *, u32);
			
			inline void QueueWaitEx(u32 num)
			{
				while (LCQueueLength() != num) OSYieldThread();
			}
		}
	}
}

#endif