#ifndef NW4R_EF_EFFECT
#define NW4R_EF_EFFECT
#include "types_nw4r.h"
#include "ef_ref.h"
#include "ut_list.h"
#include "ef_list.h"

namespace nw4r
{
	namespace ef
	{
		struct Effect : ReferencedObject
		{
			char UNK_0x20[0x4];
			ActivityList EFLIST_0x24;
			char UNK_0x3E[0x50];
			ut::List UTLIST_0x90;
		};
	}
}

#endif