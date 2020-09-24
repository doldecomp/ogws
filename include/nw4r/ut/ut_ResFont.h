#ifndef NW4R_UT_RES_FONT
#define NW4R_UT_RES_FONT
#include "ut_ResFontBase.h"
#include "ut_binaryFileFormat.h"

namespace nw4r
{
	namespace ut
	{
		struct ResFont : detail::ResFontBase
		{
			ResFont();
			~ResFont();
			
			bool SetResource(void *);
			static FontInformation * Rebuild(BinaryFileHeader *);
		};
	}
}

#endif