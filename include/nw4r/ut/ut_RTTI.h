#ifndef NW4R_UT_RTTI
#define NW4R_UT_RTTI
#include "types_nw4r.h"

namespace nw4r
{
	namespace ut
	{
		namespace detail
		{
			struct RuntimeTypeInfo
			{
				const RuntimeTypeInfo * mBase;

				inline RuntimeTypeInfo(const RuntimeTypeInfo * pBase) : mBase(pBase) {}
				
			};
		}
		
		struct Polymorphic
		{
			virtual const detail::RuntimeTypeInfo * GetRuntimeTypeInfo() const = 0;
		};
	}
}

#endif