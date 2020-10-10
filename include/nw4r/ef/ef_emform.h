#ifndef NW4R_EF_EMFORM
#define NW4R_EF_EMFORM
#include "types_nw4r.h"

namespace nw4r
{
	namespace ef
	{
		enum EmitFormType
		{
			UNKVALS // Empty enums are ill-formed
		};
		
		struct EmitFormBuilder
		{
			virtual UNKTYPE Create(EmitFormType);
		};
	}
}

#endif