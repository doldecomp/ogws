#ifndef NW4R_G3D_RESMDL_H
#define NW4R_G3D_RESMDL_H
#include "types_nw4r.h"
#include "g3d_rescommon.h"

namespace nw4r
{
	namespace g3d
	{
		struct ResMdlData
		{
			char UNK_0x0[0x8];
			u32 mRevision; // at 0x8
		};

		struct ResMdl
		{
			enum
			{
				REVISION = 9
			};
			
			ResCommon<ResMdlData> mMdl;
			
			inline ResMdl(void * vptr) : mMdl(vptr) {}
			
			bool Bind(ResFile);
			
			UNKTYPE Release();
			
			UNKTYPE Init();
			UNKTYPE Terminate();
			
			inline bool CheckRevision() const
			{
				return mMdl.ref().mRevision == REVISION;
			}
		};
	}
}

#endif