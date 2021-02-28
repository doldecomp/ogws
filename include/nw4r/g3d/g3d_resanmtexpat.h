#ifndef NW4R_G3D_RESANMTEXPAT_H
#define NW4R_G3D_RESANMTEXPAT_H
#include "types_nw4r.h"
#include "g3d_rescommon.h"

namespace nw4r
{
	namespace g3d
	{
		struct ResAnmTexPatData
		{
			char UNK_0x0[0x8];
			u32 mRevision; // at 0x8
		};

		struct ResAnmTexPat
		{
			enum
			{
				REVISION = 3
			};
			
			ResCommon<ResAnmTexPatData> mAnmTexPat;
			
			inline ResAnmTexPat(void * vptr) : mAnmTexPat(vptr) {}
			
			bool Bind(ResFile);
			
			UNKTYPE Release();
			
			inline bool CheckRevision() const
			{
				return mAnmTexPat.ref().mRevision == REVISION;
			}
		};
	}
}

#endif