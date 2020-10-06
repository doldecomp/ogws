#ifndef NW4R_EF_LIST
#define NW4R_EF_LIST
#include "types_nw4r.h"
#include "ut_list.h"

namespace nw4r
{
	namespace ef
	{
		struct ActivityList
		{
			ut::List UTLIST_0x0;
			ut::List UTLIST_0xC;
			u16 SHORT_0x18;
		};
	}
}

#endif
