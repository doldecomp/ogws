#include "g3d_resanmclr.h"
#include "g3d_anmclr.h"

namespace nw4r
{
	namespace g3d
	{
		using namespace detail;
		
		void ResAnmClr::GetAnmResult(ClrAnmResult * pResult, u32 i, float time) const
		{
			const ResAnmClrMatData * pMatAnm = GetMatAnm(i);
			
			const ResAnmClrMatData::AnmData * pAnm = pMatAnm->mAnms;
			u32 flags = pMatAnm->mFlags;
			ResAnmClrData & anmClr = ref();
			
			pResult->mFlags = 0;
			
			if (!flags) return;
			
			float t = ClipFrame<const ResAnmClrInfoData>(anmClr.mInfo, time);
			
			for (int i = 0; i < ClrAnmResult::ANM_COUNT; i++, flags >>= 2)
			{
				if (flags & 1)
				{
					pResult->mFlags |= 1 << i;
					pResult->WORDS_0x30[i] = pAnm->WORD_0x0;
					pResult->COLORS_0x4[i] = GetResColorAnmResult(&pAnm->mColor, t, flags & 2);
					
					pAnm++;
				}
			}
		}
	}
}