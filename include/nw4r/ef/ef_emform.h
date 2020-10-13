#ifndef NW4R_EF_EMFORM_H
#define NW4R_EF_EMFORM_H
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
			virtual EmitterForm * Create(EmitFormType);
		};
	}
}

#endif