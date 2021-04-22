#ifdef __DECOMP_NON_MATCHING
#include "ut_algorithm.h"
#include "math_arithmetic.h"
#include "g3d_anmtexsrt.h"
#include "g3d_resanmtexsrt.h"
#include "g3d_restex.h"

namespace nw4r
{
	using namespace ut;
	using namespace math;
	
	namespace g3d
	{
		using namespace detail;
		
		namespace
		{
			inline u32 MakeResult(TexSrt * pSrt, const ResAnmTexSrtTexData * pData, float time)
			{
				// register/address information is for the first loop in GetAnmResult
				u32 flags = pData->mFlags; // for the first loop: r31
				u32 i = 0; // for the first loop: r29
				
				if (!(flags & 0x2))
				{
					//80057990
					pSrt->mScaleX = GetResAnmResult(pData->mAnms + i++, time, flags & 0x20);
					
					if (flags & 0x10)
					{
						pSrt->mScaleY = pSrt->mScaleX;
					}
					else
					{
						pSrt->mScaleY = GetResAnmResult(pData->mAnms + i++, time, flags & 0x40);
					}
				}
				else
				{
					//80057A00
					pSrt->mScaleX = 1.0f;
					pSrt->mScaleY = 1.0f;
				}
				//80057A08
				if (!(flags & 0x4))
				{
					//80057A10
					pSrt->mRotation = GetResAnmResult(pData->mAnms + i++, time, flags & 0x80);
				}
				else
				{
					//80057A48
					pSrt->mRotation = 0.0f;
				}
				//80057A4C
				if (!(flags & 0x8))
				{
					//80057A54
					bool r0 = flags & 0x100;
					bool r21 = flags & 0x200;
					
					pSrt->mTranslationX = GetResAnmResult(pData->mAnms + i++, time, r0);
					pSrt->mTranslationY = GetResAnmResult(pData->mAnms + i++, time, r21);
				}
				else
				{
					//80057AC0
					pSrt->mTranslationX = 0.0f;
					pSrt->mTranslationY = 0.0f;
				}
				
				return flags & 0xF;
			}
		}
		
		void ResAnmTexSrt::GetAnmResult(TexSrtAnmResult * pResult, u32 i, float time) const
		{
			const ResAnmTexSrtMatData * pMatAnm = GetMatAnm(i); // at r30
			//80057934
			u32 r26 = pMatAnm->FLAGS_0x4;
			u32 r24 = pMatAnm->FLAGS_0x8;
			
			const s32 * pOffset = pMatAnm->mTexOffsets; // at r25
			
			for (int i = 0; r26; i++, r26 >>= 1)
			{
				if (r26 & 1)
				{
					const ResAnmTexSrtTexData * pData = static_cast<const ResAnmTexSrtTexData *>(AddOffsetToPtr<s32>(pMatAnm, *pOffset++));
					
					pResult->FLAGS_0x0 |= MakeResult(pResult->mSrts + i, pData, time) << (i * 4);
				}
			}
			//80057AF0
			for (int i = 0; r24; i++, r24 >>= 1)
			{
				if (r24 & 1)
				{
					const ResAnmTexSrtTexData * pData = static_cast<const ResAnmTexSrtTexData *>(AddOffsetToPtr<s32>(pMatAnm, *pOffset++));
					
					pResult->FLAGS_0x4 |= MakeResult(pResult->mSrts + (i + 8), pData, time) << (i * 4);
				}
			}
			//80057C90
		}
	}
}
#else
#error This file has yet to be decompiled accurately. Use "g3d_resanmtexsrt.s" instead.
#endif