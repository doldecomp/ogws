#ifndef NW4R_G3D_RESANMCLR_H
#define NW4R_G3D_RESANMCLR_H
#include "types_nw4r.h"
#include "g3d_rescommon.h"

namespace nw4r
{
	namespace g3d
	{
		struct ResAnmClrData
		{
			char UNK_0x0[0x8];
			u32 mRevision; // at 0x8
		};

		struct ResAnmClr
		{
			enum
			{
				REVISION = 3
			};
			
			ResCommon<ResAnmClrData> mAnmClr;
			
			inline ResAnmClr(void * vptr) : mAnmClr(vptr) {}
			
			inline bool CheckRevision() const
			{
				return mAnmClr.ref().mRevision == REVISION;
			}
		};
	}
}

#endif