#ifdef __DECOMP_NON_MATCHING
#include "ut_algorithm.h"
#include "math_arithmetic.h"
#include "g3d_anmtexpat.h"
#include "g3d_resanmtexpat.h"
#include "g3d_resfile.h"

namespace nw4r
{
	using namespace math;
	using namespace ut;
	
	namespace g3d
	{
		namespace
		{
			const ResAnmTexPatAnmFramesData * SearchFrame(const ResAnmTexPatAnmData * pData, float time)
			{
				const ResAnmTexPatAnmFramesData * pFirst = pData->mFrames;
				const ResAnmTexPatAnmFramesData * pLast = pData->mFrames + (pData->mCount - 1);
				
				if (time <= pFirst->mTime) return pFirst;
				
				if (pLast->mTime <= time) return pLast;
				
				float t = time - pFirst->mTime;
				
				const ResAnmTexPatAnmFramesData * pCur = pData->mFrames + F32ToU16(pData->FLOAT_0x4 * (t * U16ToF32(pData->mCount)));
				
				if (time < pCur->mTime)
				{
					do
					{
						pCur--;
					} while (time < pCur->mTime);
				}
				else
				{
					do
					{
						pCur++;
					} while (pCur->mTime <= time);
					
					pCur--;
				}
				
				return pCur;
			}
			
			ResName GetResNameFromOffsetArray(s32 * pOffsetArray, int i)
			{
				return reinterpret_cast<u8 *>(pOffsetArray) + pOffsetArray[i] - 4;
			}
		}
		
		void ResAnmTexPat::GetAnmResult(TexPatAnmResult * pResult, u32 i, float time) const
		{
			const ResTex * pTexArray;
			const ResPltt * pPlttArray;
			
			const ResAnmTexPatMatData * pMatAnm = GetMatAnm(i); // at r31
			const ResAnmTexPatMatData::AnmData * pAnm = pMatAnm->mAnms; // at r27
			u32 flags = pMatAnm->mFlags; // at r26
			//80057490
			pTexArray = mAnmTexPat.ofs_to_ptr<ResTex>(ref().mTexArrayOffset); // at r30
			pPlttArray = mAnmTexPat.ofs_to_ptr<ResPltt>(ref().mPlttArrayOffset); // at r29
			
			pResult->mTexFlags = 0;
			pResult->mPlttFlags = 0;
			
			//r23 <- 1 (CONSTANT)
			for (int i = 0; i < TexPatAnmResult::ANM_COUNT; i++, flags >>= 4)
			{
				//800574E4
				if (flags & 1)
				{
					u16 texIndex;
					u16 plttIndex;
					
					if (flags & 2)
					{
						texIndex = pAnm->mTexIndex;
						plttIndex = pAnm->mPlttIndex;
					}
					else
					{
						const ResAnmTexPatAnmData * pData = static_cast<const ResAnmTexPatAnmData *>(AddOffsetToPtr<s32>(pMatAnm, pAnm->mOffset));
						const ResAnmTexPatAnmFramesData * pFrame = SearchFrame(pData, time);
						
						texIndex = pFrame->mTexIndex;
						plttIndex = pFrame->mPlttIndex;
					}
					
					//80057518
					u32 flag = 1 << i; // at r5
					
					if (flags & 4)
					{
						ResTex tex = pTexArray[texIndex];
						
						if (tex.mTex.IsValid())
						{
							pResult->mTexs[i] = tex.mTex.ptr();
							pResult->mTexFlags |= flag;
						}
					}
					
					if (flags & 8)
					{
						ResPltt pltt = pPlttArray[plttIndex];
						
						if (pltt.mPltt.IsValid())
						{
							pResult->mPltts[i] = pltt.mPltt.ptr();
							pResult->mPlttFlags |= flag;
						}
					}
					
					pAnm++;
				}
				//CONTINUE
			}
		}
		
		bool ResAnmTexPat::Bind(ResFile file)
		{
			// r28 <- file
			
			int texCount = ref().mTexCount; // at r31
			int plttCount = ref().mPlttCount; // at r30
			
			s32 * pTexNameOffsetArray = mAnmTexPat.ofs_to_ptr<s32>(ref().mTexNameArrayOffset); // at r27
			s32 * pPlttNameOffsetArray = mAnmTexPat.ofs_to_ptr<s32>(ref().mPlttNameArrayOffset); // at r26
			ResTex * pTexArray = mAnmTexPat.ofs_to_ptr<ResTex>(ref().mTexArrayOffset); // at r24
			ResPltt * pPlttArray = mAnmTexPat.ofs_to_ptr<ResPltt>(ref().mPlttArrayOffset); // at r25
			
			int count = 0; // at r29
			
			for (int i = 0; i < texCount; i++)
			{
				//80057634
				if (pTexArray[i].mTex.IsValid())
				{
					count++;
				}
				else
				{
					ResTex tex = file.GetResTex(GetResNameFromOffsetArray(pTexNameOffsetArray, i));
					
					if (tex.mTex.IsValid())
					{
						pTexArray[i] = tex;
						count++;
					}
				}
			}
			
			for (int i = 0; i < plttCount; i++)
			{
				//80057694
				if (pPlttArray[i].mPltt.IsValid())
				{
					count++;
				}
				else
				{
					ResPltt pltt = file.GetResPltt(GetResNameFromOffsetArray(pPlttNameOffsetArray, i));
					
					if (pltt.mPltt.IsValid())
					{
						pPlttArray[i] = pltt;
						count++;
					}
				}
			}
			
			return texCount + plttCount == count;
		}
		
		void ResAnmTexPat::Release()
		{
			int texCount = ref().mTexCount;
			int plttCount = ref().mPlttCount;
			
			ResTex * pTexArray = mAnmTexPat.ofs_to_ptr<ResTex>(ref().mTexArrayOffset);
			ResPltt * pPlttArray = mAnmTexPat.ofs_to_ptr<ResPltt>(ref().mPlttArrayOffset);
			
			if (texCount > 0)
			{
				for (int i = 0; i < texCount; i++)
				{
					pTexArray[i] = ResTex(NULL);
				}
			}
			
			if (plttCount > 0)
			{
				for (int i = 0; i < plttCount; i++)
				{
					pPlttArray[i] = ResPltt(NULL);
				}
			}
		}
	}
}
#else
#error This file has yet to be decompiled accurately. Use "g3d_resanmtexpat.s" instead.
#endif