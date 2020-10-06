#ifndef NW4R_EF_REF
#define NW4R_EF_REF
#include "types_nw4r.h"
#include "math_types.h"

namespace nw4r
{
	namespace ef
	{
		struct ReferencedObject
		{
			char UNK_0x0[0x1C];
			
			virtual UNKTYPE SendClosing();
			virtual UNKTYPE DestroyFunc();
		};
	}
}

#endif