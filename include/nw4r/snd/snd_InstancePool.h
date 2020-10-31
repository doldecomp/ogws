#ifndef NW4R_SND_INSTANCE_POOL_H
#define NW4R_SND_INSTANCE_POOL_H
#include "types_nw4r.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			struct PoolImpl
			{
				struct Member
				{
					Member * mNext; // at 0x0
				};
				
				u32 CreateImpl(void *, u32, u32);
				void DestroyImpl(void *, u32);
				u32 CountImpl() const;
				void * AllocImpl();
				void FreeImpl(void *);
				
				Member mHead; // at 0x0
			};
		}
	}
}

#endif