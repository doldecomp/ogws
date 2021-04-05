#include "g3d_resanmvis.h"
#include "math_arithmetic.h"

namespace nw4r
{
	using namespace math;
	
	namespace g3d
	{
		using namespace detail;
		
		bool ResAnmVis::GetAnmResult(u32 i, float time) const
		{
			const ResAnmVisNodeData * pNodeAnm = GetNodeAnm(i);
			
			const ResAnmVisData & anmVis = ref();
			
			if (pNodeAnm->mFlags & 0x2) return pNodeAnm->mFlags & 0x1;
			
			float t = ClipFrame<const ResAnmVisInfoData>(anmVis.mInfo, time);
			
			return GetResBoolAnmFramesResult(pNodeAnm->mBoolFrames, FFloor(t));
		}
	}
}