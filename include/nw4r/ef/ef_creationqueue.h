#ifndef NW4R_EF_CREATIONQUEUE
#define NW4R_EF_CREATIONQUEUE
#include "types_nw4r.h"

namespace nw4r
{
	namespace ef
	{
		struct CreationQueue
		{
			CreationQueue();
			
			UNKWORD WORD_0x0;
			
			inline bool IsEmpty()
			{
				return WORD_0x0 == 0;
			}
			
			UNKTYPE Execute();
		};
	}
}

#endif