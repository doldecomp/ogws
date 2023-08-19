#pragma ipa file
#include <string.h>
#include <OSCache.h>
#include <GXDisplayList.h>
#include "g3d_resshp.h"

namespace nw4r
{
	namespace g3d
	{
		using namespace detail;
		
		bool ResShp::GXGetVtxDescv(GXVtxDescList* list) const
		{
			ResShpPrePrim prePrim = GetResShpPrePrim();
			
			if (!prePrim.ref().CP_CMD_0xA[0]) return false;
			
			u32 r0;
			u32 r3;
			
			ResReadCPCmd(prePrim.ref().CP_CMD_0xA, &r0);
			ResReadCPCmd(prePrim.ref().CP_CMD_0x10, &r3);
			
			for (int i = 0; i < GX_POS_MTX_ARRAY; i++)
			{
				list[i].attr = (GXAttr)i;
			}
			
			list[GX_POS_MTX_ARRAY].attr = GX_VA_NULL;
			
			list[GX_VA_PNMTXIDX].type = (GXAttrType)(r0 & 0x1);
			list[GX_VA_TEX0MTXIDX].type = (GXAttrType)(r0 >> 1 & 0x1);
			list[GX_VA_TEX1MTXIDX].type = (GXAttrType)(r0 >> 2 & 0x1);
			list[GX_VA_TEX2MTXIDX].type = (GXAttrType)(r0 >> 3 & 0x1);
			list[GX_VA_TEX3MTXIDX].type = (GXAttrType)(r0 >> 4 & 0x1);
			list[GX_VA_TEX4MTXIDX].type = (GXAttrType)(r0 >> 5 & 0x1);
			list[GX_VA_TEX5MTXIDX].type = (GXAttrType)(r0 >> 6 & 0x1);
			list[GX_VA_TEX6MTXIDX].type = (GXAttrType)(r0 >> 7 & 0x1);
			list[GX_VA_TEX7MTXIDX].type = (GXAttrType)(r0 >> 8 & 0x1);
			list[GX_VA_POS].type = (GXAttrType)(r0 >> 9 & 0x3);
			list[GX_VA_NRM].type = (GXAttrType)(r0 >> 11 & 0x3);
			list[GX_VA_CLR0 + 0].type = (GXAttrType)(r0 >> 13 & 0x3);
			list[GX_VA_CLR0 + 1].type = (GXAttrType)(r0 >> 15 & 0x3);
			list[GX_VA_TEX0 + 0].type = (GXAttrType)(r3 & 0x3);
			list[GX_VA_TEX0 + 1].type = (GXAttrType)(r3 >> 2 & 0x3);
			list[GX_VA_TEX0 + 2].type = (GXAttrType)(r3 >> 4 & 0x3);
			list[GX_VA_TEX0 + 3].type = (GXAttrType)(r3 >> 6 & 0x3);
			list[GX_VA_TEX0 + 4].type = (GXAttrType)(r3 >> 8 & 0x3);
			list[GX_VA_TEX0 + 5].type = (GXAttrType)(r3 >> 10 & 0x3);
			list[GX_VA_TEX0 + 6].type = (GXAttrType)(r3 >> 12 & 0x3);
			list[GX_VA_TEX0 + 7].type = (GXAttrType)(r3 >> 14 & 0x3);
			
			return true;
		}
		
		bool ResShp::GXGetVtxAttrFmtv(GXVtxAttrFmtList* list) const
		{
			ResShpPrePrim prePrim = GetResShpPrePrim();
			
			if (!prePrim.ref().CP_CMD_0x20[0]) return false;
			
			u32 r0;
			u32 r5;
			u32 r16;
			
			ResReadCPCmd(prePrim.ref().CP_CMD_0x20, &r0);
			ResReadCPCmd(prePrim.ref().CP_CMD_0x26, &r5);
			ResReadCPCmd(prePrim.ref().CP_CMD_0x2C, &r16);
			
			int i;
			
			for (i = 0; i < GX_POS_MTX_ARRAY - GX_VA_POS; i++)
			{
				list[i].attr = (GXAttr)(i + GX_VA_POS);
			}
			
			list[GX_VA_POS - GX_VA_POS].compType = (GXCompType)(r0 >> 1 & 0x7);
			list[GX_VA_POS - GX_VA_POS].compCnt = (GXCompCnt)(r0 & 0x1);
			list[GX_VA_POS - GX_VA_POS].shift = r0 >> 4 & 0x1f;
			
			list[GX_VA_NRM - GX_VA_POS].compType = (GXCompType)(r0 >> 10 & 0x7);
			list[GX_VA_NRM - GX_VA_POS].compCnt = (GXCompCnt)(r0 >> 31 ? i - 10 : r0 >> 9 & 1);
			list[GX_VA_NRM - GX_VA_POS].shift = list[GX_VA_NRM - GX_VA_POS].compType == 1 ? 6 : 14;
			
			list[GX_VA_CLR0 - GX_VA_POS + 0].compType = (GXCompType)(r0 >> 14 & 0x7);
			list[GX_VA_CLR0 - GX_VA_POS + 0].compCnt = (GXCompCnt)(r0 >> 13 & 0x1);
			
			list[GX_VA_CLR0 - GX_VA_POS + 1].compType = (GXCompType)(r0 >> 18 & 0x7);
			list[GX_VA_CLR0 - GX_VA_POS + 1].compCnt = (GXCompCnt)(r0 >> 17 & 0x1);
			
			list[GX_VA_TEX0 - GX_VA_POS + 0].compType = (GXCompType)(r0 >> 22 & 0x7);
			list[GX_VA_TEX0 - GX_VA_POS + 0].compCnt = (GXCompCnt)(r0 >> 21 & 0x1);
			list[GX_VA_TEX0 - GX_VA_POS + 0].shift = r0 >> 25 & 0x1f;
			
			list[GX_VA_TEX0 - GX_VA_POS + 1].compType = (GXCompType)(r5 >> 1 & 0x7);
			list[GX_VA_TEX0 - GX_VA_POS + 1].compCnt = (GXCompCnt)(r5 & 1);
			list[GX_VA_TEX0 - GX_VA_POS + 1].shift = r5 >> 4 & 0x1f;
			
			list[GX_VA_TEX0 - GX_VA_POS + 2].compType = (GXCompType)(r5 >> 10 & 0x7);
			list[GX_VA_TEX0 - GX_VA_POS + 2].compCnt = (GXCompCnt)(r5 >> 9 & 0x1);
			list[GX_VA_TEX0 - GX_VA_POS + 2].shift = r5 >> 13 & 0x1f;
			
			list[GX_VA_TEX0 - GX_VA_POS + 3].compType = (GXCompType)(r5 >> 19 & 0x7);
			list[GX_VA_TEX0 - GX_VA_POS + 3].compCnt = (GXCompCnt)(r5 >> 18 & 0x1);
			list[GX_VA_TEX0 - GX_VA_POS + 3].shift = r5 >> 22 & 0x1f;
			
			list[GX_VA_TEX0 - GX_VA_POS + 4].compType = (GXCompType)(r5 >> 28 & 0x7);
			list[GX_VA_TEX0 - GX_VA_POS + 4].compCnt = (GXCompCnt)(r5 >> 27 & 0x1);
			list[GX_VA_TEX0 - GX_VA_POS + 4].shift = r16 & 0x1f;
			
			list[GX_VA_TEX0 - GX_VA_POS + 5].compType = (GXCompType)(r16 >> 6 & 0x7);
			list[GX_VA_TEX0 - GX_VA_POS + 5].compCnt = (GXCompCnt)(r16 >> 5 & 0x1);
			list[GX_VA_TEX0 - GX_VA_POS + 5].shift = r16 >> 9 & 0x1f;
			
			list[GX_VA_TEX0 - GX_VA_POS + 6].compType = (GXCompType)(r16 >> 15 & 0x7);
			list[GX_VA_TEX0 - GX_VA_POS + 6].compCnt = (GXCompCnt)(r16 >> 14 & 0x1);
			list[GX_VA_TEX0 - GX_VA_POS + 6].shift = r16 >> 18 & 0x1f;
			
			list[GX_VA_TEX0 - GX_VA_POS + 7].compType = (GXCompType)(r16 >> 24 & 0x7);
			list[GX_VA_TEX0 - GX_VA_POS + 7].compCnt = (GXCompCnt)(r16 >> 23 & 0x1);
			list[GX_VA_TEX0 - GX_VA_POS + 7].shift = r16 >> 27;
			
			return true;
		}
		
		ResMdl ResShp::GetParent() const
		{
			return mShp.ofs_to_obj<ResMdl>(ref().mParentOffset);
		}
		
		ResVtxPos ResShp::GetResVtxPos() const
		{
			return GetParent().GetResVtxPos(ref().mVtxPosIndex);
		}
		
		ResVtxNrm ResShp::GetResVtxNrm() const
		{
			if (ref().mVtxNrmIndex != -1) return GetParent().GetResVtxNrm(ref().mVtxNrmIndex);
			
			return NULL;
		}
		
		ResVtxClr ResShp::GetResVtxClr(u32 i) const
		{
			if (ref().mVtxClrIndices[i] != -1) return GetParent().GetResVtxClr(ref().mVtxClrIndices[i]);
			
			return NULL;
		}
		
		ResVtxTexCoord ResShp::GetResVtxTexCoord(u32 i) const
		{
			if (ref().mVtxTexCoordIndices[i] != -1) return GetParent().GetResVtxTexCoord(ref().mVtxTexCoordIndices[i]);
			
			return NULL;
		}
		
		void ResShp::GXSetArray(GXAttr attr, const void * ptr, u8 byte)
		{
			ResShpPrePrim prePrim = GetResShpPrePrim();
			u32 i = attr - GX_VA_POS;
			CPCmd * pCmdPair = prePrim.ref().CP_CMD_PAIRS_0x32[i];
			u32 r28 = (attr != 0x19) ? i : 1;
			
			ResWriteCPCmd(pCmdPair[0], r28 + 0xA0, (u32)ptr - 0x80000000);
			ResWriteCPCmd(pCmdPair[1], r28 + 0xB0, byte);
		}
		
		void ResShp::Init()
		{
			const void * ptr_0x2c;
			u8 byte_0x8;
			
			GetResVtxPos().GetArray(&ptr_0x2c, &byte_0x8);
			GXSetArray(GX_VA_POS, ptr_0x2c, byte_0x8);
			
			//80053D98
			ResVtxNrm vtxNrm = GetResVtxNrm();
			
			if (vtxNrm.mNrm.IsValid())
			{
				vtxNrm.GetArray(&ptr_0x2c, &byte_0x8);
				GXSetArray(GX_VA_NRM, ptr_0x2c, byte_0x8);
			}
			
			//80053E40
			for (u32 i = 0; i < GX_VA_TEX0 - GX_VA_CLR0; i++)
			{
				ResVtxClr vtxClr = GetResVtxClr(i);
				
				if (vtxClr.mClr.IsValid())
				{
					vtxClr.GetArray(&ptr_0x2c, &byte_0x8);
					GXSetArray((GXAttr)(GX_VA_CLR0 + i), ptr_0x2c, byte_0x8);
				}
			}
			
			//80053F2C
			for (u32 i = 0; i < GX_POS_MTX_ARRAY - GX_VA_TEX0; i++)
			{
				ResVtxTexCoord vtxTexCoord = GetResVtxTexCoord(i);
				
				if (vtxTexCoord.mTexCoord.IsValid())
				{
					vtxTexCoord.GetArray(&ptr_0x2c, &byte_0x8);
					GXSetArray((GXAttr)(GX_VA_TEX0 + i), ptr_0x2c, byte_0x8);
				}
			}
			
			//80054018
			DCStoreRangeNoSync(&GetResShpPrePrim().ref(), sizeof(ResPrePrimDL));
			
			ResShpData & data = ref();
			
			DCStoreRangeNoSync(ResTagDL(&data.mPrimDLTag).GetDL(), data.mPrimDLTag.mBufSize);
		}
		
		void ResShp::DisableSetArray(GXAttr attr)
		{
			memset(GetResShpPrePrim().ref().CP_CMD_PAIRS_0x32[attr - GX_VA_POS], 0, sizeof(CPCmd) * 2);
		}
		
		void ResShp::Terminate()
		{
			DisableSetArray(GX_VA_POS);
			DisableSetArray(GX_VA_NRM);
			DisableSetArray((GXAttr)(GX_VA_CLR0 + 0));
			DisableSetArray((GXAttr)(GX_VA_CLR0 + 1));
			DisableSetArray((GXAttr)(GX_VA_TEX0 + 0));
			DisableSetArray((GXAttr)(GX_VA_TEX0 + 1));
			DisableSetArray((GXAttr)(GX_VA_TEX0 + 2));
			DisableSetArray((GXAttr)(GX_VA_TEX0 + 3));
			DisableSetArray((GXAttr)(GX_VA_TEX0 + 4));
			DisableSetArray((GXAttr)(GX_VA_TEX0 + 5));
			DisableSetArray((GXAttr)(GX_VA_TEX0 + 6));
			DisableSetArray((GXAttr)(GX_VA_TEX0 + 7));
		}
		
		void ResShp::CallPrePrimitiveDisplayList(bool r4, bool r5) const
		{
			ResTagDL tag(&ref().mPrePrimDLTag); // at r5
			
			if (r5)
			{
				if (r4)
				{
					//80054300
					GXCallDisplayList(tag.GetDL() + 0x20, tag.GetCmdSize() - 0x20);
				}
				else
				{
					//80054328
					GXFastCallDisplayList(tag.GetDL() + 0x20, tag.GetCmdSize() - 0x20);
				}
			}
			else if (r4)
			{
				//8005436C
				GXCallDisplayList(tag.GetDL(), tag.GetCmdSize());
			}
			else
			{
				//8005438C
				GXFastCallDisplayList(tag.GetDL(), tag.GetCmdSize());
			}
		}
		
		void ResShp::CallPrimitiveDisplayList(bool r4) const
		{
			ResTagDL tag(&ref().mPrimDLTag);
			
			if (r4)
			{
				GXCallDisplayList(tag.GetDL(), (int)tag.GetCmdSize());
			}
			else
			{
				GXFastCallDisplayList(tag.GetDL(), (int)tag.GetCmdSize());
			}
		}
	}
}