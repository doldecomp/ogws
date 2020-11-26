#ifndef NW4R_SND_SOUND_HEAP_H
#define NW4R_SND_SOUND_HEAP_H
#include "types_nw4r.h"

namespace nw4r
{
	namespace snd
	{
		struct SoundHeap
		{
			virtual ~SoundHeap(); // at 0x8
			virtual UNKTYPE * Alloc(u32); // at 0xc
		};
	}
}

#endif