#ifndef NW4R_G3D_ANMCLR_H
#define NW4R_G3D_ANMCLR_H
#include "types_nw4r.h"

namespace nw4r
{
	namespace g3d
	{
		struct ClrAnmResult
		{
			u32 mFlags; // at 0x0
			u32 COLORS_0x4[11];
			UNKWORD WORDS_0x30[11];
		};
	}
}

#endif