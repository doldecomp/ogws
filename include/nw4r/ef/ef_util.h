#ifndef NW4R_EF_UTIL
#define NW4R_EF_UTIL
#include "types_nw4r.h"
#include "ut_list.h"

namespace nw4r
{
	namespace ef
	{
		typedef void (* Action)(void *, u32);
		
		u16 UtlistToArray(const ut::List *, void **, int);
	}
}

#endif