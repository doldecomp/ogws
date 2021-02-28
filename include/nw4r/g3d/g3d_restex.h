#ifndef NW4R_G3D_RESTEX_H
#define NW4R_G3D_RESTEX_H
#include "types_nw4r.h"
#include "g3d_rescommon.h"

namespace nw4r
{
	namespace g3d
	{
		struct ResTexData
		{
			char UNK_0x0[0x8];
			u32 mRevision; // at 0x8
		};
		
		struct ResPlttData
		{
			char UNK_0x0[0x8];
			u32 mRevision; // at 0x8
		};
		
		struct ResTex
		{
			enum
			{
				REVISION = 1
			};
			
			ResCommon<ResTexData> mTex; // at 0x0
			
			inline ResTex(void * vptr) : mTex(vptr) {}
			
			UNKTYPE Init();
			
			inline bool CheckRevision() const
			{
				return mTex.ref().mRevision == REVISION;
			}
		};
		
		struct ResPltt
		{
			enum
			{
				REVISION = 1
			};
			
			ResCommon<ResPlttData> mPltt; // at 0x0
			
			inline ResPltt(void * vptr) : mPltt(vptr) {}
			
			UNKTYPE DCStore(bool);
			
			inline bool CheckRevision() const
			{
				return mPltt.ref().mRevision == REVISION;
			}
		};
	}
}

#endif