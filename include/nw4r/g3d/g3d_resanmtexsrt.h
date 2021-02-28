#ifndef NW4R_G3D_RESANMTEXSRT_H
#define NW4R_G3D_RESANMTEXSRT_H
#include "types_nw4r.h"
#include "g3d_rescommon.h"

namespace nw4r
{
	namespace g3d
	{
		struct ResAnmTexSrtData
		{
			char UNK_0x0[0x8];
			u32 mRevision; // at 0x8
		};

		struct ResAnmTexSrt
		{
			enum
			{
				REVISION = 4
			};
			
			ResCommon<ResAnmTexSrtData> mAnmTexSrt;
			
			inline ResAnmTexSrt(void * vptr) : mAnmTexSrt(vptr) {}
			
			inline bool CheckRevision() const
			{
				return mAnmTexSrt.ref().mRevision == REVISION;
			}
		};
	}
}

#endif