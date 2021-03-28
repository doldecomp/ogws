#include <PPCArch.h>
#include <OSCache.h>
#include <GXDisplayList.h>
#include "g3d_restev.h"

namespace nw4r
{
	namespace g3d
	{
		using namespace detail;
		
		bool ResTev::GXGetTevSwapModeTable(_GXTevSwapSel sel, _GXTevColorChan * r_5, _GXTevColorChan * r_6, _GXTevColorChan * r_7, _GXTevColorChan * r_8) const
		{
			BPCmd * pSwapSelCmd = ref().mSwapSelCmds[sel];
			
			if (!pSwapSelCmd[0][0]) return false;
			
			u32 r10;
			
			ResReadBPCmd(pSwapSelCmd[1], &r10);
			
			if (r_5) *r_5 = (_GXTevColorChan)(r10 & 0x3);
			if (r_6) *r_6 = (_GXTevColorChan)(r10 >> 2 & 0x3);
			
			u32 r5;
			
			ResReadBPCmd(pSwapSelCmd[3], &r5);
			
			if (r_7) *r_7 = (_GXTevColorChan)(r5 & 0x3);
			if (r_8) *r_8 = (_GXTevColorChan)(r5 >> 2 & 0x3);
			
			return true;
		}
		
		void ResTev::GXSetTevSwapModeTable(_GXTevSwapSel sel, _GXTevColorChan r26_5, _GXTevColorChan r31_6, _GXTevColorChan r27_7, _GXTevColorChan r28_8)
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
		
		bool ResTev::GXGetTevOrder(_GXTevStageID stageID, _GXTexCoordID * pCoordID, _GXTexMapID * pMapID, _GXChannelID * pChannelID) const
		{
			u8 * pCmds = ref().mStageCmds[stageID / 2].BP_CMD_0xA;
			
			if (!pCmds[0]) return false;
			
			u32 r9;
			u32 r0;
			_GXTexCoordID r4;
			_GXTexMapID r3;
			_GXChannelID r8;
			
			ResReadBPCmd(pCmds, &r9);
			
			static const _GXChannelID r2c[] = {
				GX_CHANNEL_ID_4,
				GX_CHANNEL_ID_5,
				GX_CHANNEL_ID_INVALID,
				GX_CHANNEL_ID_INVALID,
				GX_CHANNEL_ID_INVALID,
				GX_CHANNEL_ID_7,
				GX_CHANNEL_ID_8,
				GX_CHANNEL_ID_6
			};
			
			if (stageID & 1)
			{
				r8 = r2c[r9 >> 19 & 0x7];
				r4 = (_GXTexCoordID)(r9 >> 15 & 0x7);
				r0 = r9 >> 18 & 0x1;
				r3 = (_GXTexMapID)(r9 >> 12 & 0x7);
			}
			else
			{
				r8 = r2c[r9 >> 7 & 0x7];
				r4 = (_GXTexCoordID)(r9 >> 3 & 0x7);
				r0 = r9 >> 6 & 0x1;
				r3 = (_GXTexMapID)(r9 & 0x7);
			}
			
			if (pCoordID) *pCoordID = r4;
			if (pChannelID) *pChannelID = r8;
			
			//if (pMapID) *pMapID = !r0 ? GX_TEX_MAP_ID_INVALID : r3;
			if (!r0) r3 = GX_TEX_MAP_ID_INVALID;
			if (pMapID) *pMapID = r3;
			
			return true;
		}
		
		void ResTev::GXSetTevColorIn(_GXTevStageID stageID, _GXTevColorArg r_5, _GXTevColorArg r_6, _GXTevColorArg r_7, _GXTevColorArg r_8)
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