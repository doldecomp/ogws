#include <revolution/BASE.h>
#include <OSCache.h>
#include <GXDisplayList.h>
#include "g3d_restev.h"

namespace nw4r
{
	namespace g3d
	{
		using namespace detail;
		
		bool ResTev::GXGetTevSwapModeTable(GXTevSwapSel sel, GXTevColorChan * r_5, GXTevColorChan * r_6, GXTevColorChan * r_7, GXTevColorChan * r_8) const
		{
			BPCmd * pSwapSelCmd = ref().mSwapSelCmds[sel];
			
			if (!pSwapSelCmd[0][0]) return false;
			
			u32 r10;
			
			ResReadBPCmd(pSwapSelCmd[1], &r10);
			
			if (r_5) *r_5 = (GXTevColorChan)(r10 & 0x3);
			if (r_6) *r_6 = (GXTevColorChan)(r10 >> 2 & 0x3);
			
			u32 r5;
			
			ResReadBPCmd(pSwapSelCmd[3], &r5);
			
			if (r_7) *r_7 = (GXTevColorChan)(r5 & 0x3);
			if (r_8) *r_8 = (GXTevColorChan)(r5 >> 2 & 0x3);
			
			return true;
		}
		
		void ResTev::GXSetTevSwapModeTable(GXTevSwapSel sel, GXTevColorChan r26_5, GXTevColorChan r31_6, GXTevColorChan r27_7, GXTevColorChan r28_8)
		{
			u32 r30 = sel;
			BPCmd * pSwapSelCmd = ref().mSwapSelCmds[sel];
			
			ResWriteSSMask(pSwapSelCmd[0], 0xf);
			
			r30 <<= 1;
			
			u32 r4 = r26_5;
			r4 |= (r31_6) << 0x2;
			r4 |= (r30 + 0xf6) << 0x18;
			
			ResWriteBPCmd(pSwapSelCmd[1], r4, 0xFF00000F);
			
			ResWriteSSMask(pSwapSelCmd[2], 0xf);
			
			u32 r4_ = r27_7;
			r4_ |= (r28_8) << 0x2;
			r4_ |= (r30 + 0xf7) << 0x18;
			
			ResWriteBPCmd(pSwapSelCmd[3], r4_, 0xFF00000F);
		}
		
		bool ResTev::GXGetTevOrder(GXTevStageID stageID, GXTexCoordID * pCoordID, GXTexMapID * pMapID, GXChannelID * pChannelID) const
		{
			u8 * pCmds = ref().mStageCmds[stageID / 2].BP_CMD_0xA;
			
			if (!pCmds[0]) return false;
			
			u32 r9;
			u32 r0;
			GXTexCoordID r4;
			GXTexMapID r3;
			GXChannelID r8;
			
			ResReadBPCmd(pCmds, &r9);
			
			static const GXChannelID r2c[] = {
				GX_COLOR0A0,
				GX_COLOR1A1,
				GX_COLOR_NULL,
				GX_COLOR_NULL,
				GX_COLOR_NULL,
				GX_ALPHA_BUMP,
				GX_ALPHA_BUMPN,
				GX_COLOR_ZERO
			};
			
			if (stageID & 1)
			{
				r8 = r2c[r9 >> 19 & 0x7];
				r4 = (GXTexCoordID)(r9 >> 15 & 0x7);
				r0 = r9 >> 18 & 0x1;
				r3 = (GXTexMapID)(r9 >> 12 & 0x7);
			}
			else
			{
				r8 = r2c[r9 >> 7 & 0x7];
				r4 = (GXTexCoordID)(r9 >> 3 & 0x7);
				r0 = r9 >> 6 & 0x1;
				r3 = (GXTexMapID)(r9 & 0x7);
			}
			
			if (pCoordID) *pCoordID = r4;
			if (pChannelID) *pChannelID = r8;
			
			//if (pMapID) *pMapID = !r0 ? GX_TEXMAP_NULL : r3;
			if (!r0) r3 = GX_TEXMAP_NULL;
			if (pMapID) *pMapID = r3;
			
			return true;
		}
		
		void ResTev::GXSetTevColorIn(GXTevStageID stageID, GXTevColorArg r_5, GXTevColorArg r_6, GXTevColorArg r_7, GXTevColorArg r_8)
		{
			u8 * pCmds = ref().mStageCmds[stageID / 2].BP_CMD_PAIR_0xF[stageID % 2];
			/*
			u32 r6 = r_6 << 8;
			r6 |= r_8;
			r6 |= r_7 << 4;
			r6 |= r_5 << 0xc;
			r6 |= (0xc0 + stageID * 2) << 0x18;
			
			ResWriteBPCmd(pCmds, r6, 0xFF00FFFF);
			*/
			ResWriteBPCmd(pCmds, r_8 | (r_7 << 4) | (r_6 << 8) | (r_5 << 0xc) | ((0xc0 + stageID * 2) << 0x18), 0xFF00FFFF);
		}
		
		void ResTev::CallDisplayList(bool sync) const
		{
			if (sync) PPCSync();
			
			static const u32 dlsize[] = {
				0xA0, 0xA0,
				0xC0, 0xC0,
				0x100, 0x100,
				0x120, 0x120,
				0x160, 0x160,
				0x180, 0x180,
				0x1C0, 0x1C0,
				0x1E0, 0x1E0
			};
			
			GXCallDisplayList(ref().mSwapSelCmds, dlsize[ref().BYTE_0xC - 1]);
		}
		
		void * ResTev::CopyTo(void * ptr)
		{
			volatile ResTevData * pDest = static_cast<volatile ResTevData *>(ptr);
			ResTevData * pSrc = &ref();
			
			Copy32ByteBlocks(ptr, pSrc, 0x200);
			
			pDest->INT_0x4 -= (u8 *)pDest - (u8 *)pSrc;
			
			DCStoreRangeNoSync(ptr, pDest->SIZE_0x0);
			
			return ptr;
		}
		
		UNKTYPE ResTev::DCStore(bool sync)
		{
			void * ptr = &ref();
			u32 size = ref().SIZE_0x0;
			
			if (sync) DCStoreRange(ptr, size);
			else DCStoreRangeNoSync(ptr, size);
		}
	}
}