#ifndef NW4R_G3D_RESANMSCN_H
#define NW4R_G3D_RESANMSCN_H
#include "types_nw4r.h"
#include "g3d_rescommon.h"

namespace nw4r
{
	namespace g3d
	{
		struct ResAnmScnData
		{
			char UNK_0x0[0x8];
			u32 mRevision; // at 0x8
		};

		struct ResAnmScn
		{
			enum
			{
				REVISION = 4
			};
			
			ResCommon<ResAnmScnData> mAnmScn;
			
			inline ResAnmScn(void * vptr) : mAnmScn(vptr) {}
			
			inline bool CheckRevision() const
			{
				return mAnmScn.ref().mRevision == REVISION;
			}
		};
	}
}

#endif