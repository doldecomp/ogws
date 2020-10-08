#ifndef NW4R_EF_MEMORYMANAGERBASE
#define NW4R_EF_MEMORYMANAGERBASE
#include "types_nw4r.h"

namespace nw4r
{
	namespace ef
	{
		struct MemoryManagerBase
		{
			virtual ~MemoryManagerBase(); // at 0x8
			virtual UNKTYPE GarbageCollection() = 0; // at 0xc
			
			virtual Effect * AllocEffect() = 0; // at 0x10
			virtual UNKTYPE FreeEffect(void *) = 0; // at 0x14
			virtual UNKWORD GetNumAllocEffect() const = 0; // at 0x18
			virtual UNKWORD GetNumActiveEffect() const = 0; // at 0x1c
			virtual UNKWORD GetNumFreeEffect() const = 0; // at 0x20
			
			virtual Emitter * AllocEmitter() = 0; // at 0x24
			virtual UNKTYPE FreeEmitter(void *) = 0;
			virtual UNKWORD GetNumAllocEmitter() const = 0;
			virtual UNKWORD GetNumActiveEmitter() const = 0;
			virtual UNKWORD GetNumFreeEmitter() const = 0;
		};
	}
}

#endif