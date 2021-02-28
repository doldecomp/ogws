#ifndef NW4R_G3D_RESANMVIS_H
#define NW4R_G3D_RESANMVIS_H
#include "types_nw4r.h"
#include "g3d_rescommon.h"

namespace nw4r
{
	namespace g3d
	{
		struct ResAnmVisData
		{
			char UNK_0x0[0x8];
			u32 mRevision; // at 0x8
		};

		struct ResAnmVis
		{
			enum
			{
				REVISION = 3
			};
			
			ResCommon<ResAnmVisData> mAnmVis;
			
			inline ResAnmVis(void * vptr) : mAnmVis(vptr) {}
			
			inline bool CheckRevision() const
			{
				return mAnmVis.ref().mRevision == REVISION;
			}
		};
	}
}

#endif