#ifndef NW4R_EF_EMITTERRESOURCE
#define NW4R_EF_EMITTERRESOURCE
#include "types_nw4r.h"

namespace nw4r
{
	namespace ef
	{
		struct EmitterResource
		{
			
		};
		
		struct ResEmitter
		{
			EmitterResource * mPtr;
			
			inline EmitterResource * ptr() { return mPtr; }
		};
	}
}

#endif