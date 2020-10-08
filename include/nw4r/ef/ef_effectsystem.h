#ifndef NW4R_EF_EFFECTSYSTEM
#define NW4R_EF_EFFECTSYSTEM
#include "types_nw4r.h"
#include "ef_creationqueue.h"

namespace nw4r
{
	namespace ef
	{
		struct EffectSystem
		{
			MemoryManager * mMemoryManager;
			DrawOrder * mDrawOrder;
			char UNK_0x8[0x8];
			CreationQueue mCreationQueue;
			
			inline MemoryManager * GetMemoryManager() const
			{
				return mMemoryManager;
			}
			
			UNKTYPE Closing(Effect *);
		};
	}
}

#endif