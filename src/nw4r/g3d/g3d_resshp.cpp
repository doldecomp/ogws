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
		
		bool ResShp::GXGetVtxDescv(GXVtxDescList list) const
		{
			ResShpPrePrim prePrim = GetResShpPrePrim();
			
			if (!prePrim.ref().CP_CMD_0xA[0]) return false;
			
			u32 r0;
			u32 r3;
			
			ResReadCPCmd(prePrim.ref().CP_CMD_0xA, &r0);
			ResReadCPCmd(prePrim.ref().CP_CMD_0x10, &r3);
			
			for (int i = 0; i < GX_ATTR_COUNT; i++)
			{
				list[i].mAttr = (GXAttr)i;
			}
			
			list[GX_ATTR_COUNT].mAttr = GX_ATTR_INVALID;
			
			list[GX_ATTR_0].WORD_0x4 = r0 & 0x1;
			list[GX_ATTR_1].WORD_0x4 = r0 >> 1 & 0x1;
			list[GX_ATTR_2].WORD_0x4 = r0 >> 2 & 0x1;
			list[GX_ATTR_3].WORD_0x4 = r0 >> 3 & 0x1;
			list[GX_ATTR_4].WORD_0x4 = r0 >> 4 & 0x1;
			list[GX_ATTR_5].WORD_0x4 = r0 >> 5 & 0x1;
			list[GX_ATTR_6].WORD_0x4 = r0 >> 6 & 0x1;
			list[GX_ATTR_7].WORD_0x4 = r0 >> 7 & 0x1;
			list[GX_ATTR_8].WORD_0x4 = r0 >> 8 & 0x1;
			list[GX_ATTR_VTX_POS].WORD_0x4 = r0 >> 9 & 0x3;
			list[GX_ATTR_VTX_NRM].WORD_0x4 = r0 >> 11 & 0x3;
			list[GX_ATTR_VTX_CLR + 0].WORD_0x4 = r0 >> 13 & 0x3;
			list[GX_ATTR_VTX_CLR + 1].WORD_0x4 = r0 >> 15 & 0x3;
			list[GX_ATTR_VTX_TEX_COORD + 0].WORD_0x4 = r3 & 0x3;
			list[GX_ATTR_VTX_TEX_COORD + 1].WORD_0x4 = r3 >> 2 & 0x3;
			list[GX_ATTR_VTX_TEX_COORD + 2].WORD_0x4 = r3 >> 4 & 0x3;
			list[GX_ATTR_VTX_TEX_COORD + 3].WORD_0x4 = r3 >> 6 & 0x3;
			list[GX_ATTR_VTX_TEX_COORD + 4].WORD_0x4 = r3 >> 8 & 0x3;
			list[GX_ATTR_VTX_TEX_COORD + 5].WORD_0x4 = r3 >> 10 & 0x3;
			list[GX_ATTR_VTX_TEX_COORD + 6].WORD_0x4 = r3 >> 12 & 0x3;
			list[GX_ATTR_VTX_TEX_COORD + 7].WORD_0x4 = r3 >> 14 & 0x3;
			
			return true;
		}
		
		bool ResShp::GXGetVtxAttrFmtv(GXVtxAttrFmtList list) const
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
			
			for (i = 0; i < GX_ATTR_VTX_COUNT; i++)
			{
				list[i].mAttr = (GXAttr)(i + GX_ATTR_VTX);
			}
			
			list[GX_ATTR_VTX_POS - GX_ATTR_VTX].WORD_0x8 = r0 >> 1 & 0x7;
			list[GX_ATTR_VTX_POS - GX_ATTR_VTX].WORD_0x4 = r0 & 0x1;
			list[GX_ATTR_VTX_POS - GX_ATTR_VTX].BYTE_0xC = r0 >> 4 & 0x1f;
			
			list[GX_ATTR_VTX_NRM - GX_ATTR_VTX].WORD_0x8 = r0 >> 10 & 0x7;
			list[GX_ATTR_VTX_NRM - GX_ATTR_VTX].WORD_0x4 = r0 >> 31 ? i - 10 : r0 >> 9 & 1;
			list[GX_ATTR_VTX_NRM - GX_ATTR_VTX].BYTE_0xC = list[GX_ATTR_VTX_NRM - GX_ATTR_VTX].WORD_0x8 == 1 ? 6 : 14;
			
			list[GX_ATTR_VTX_CLR - GX_ATTR_VTX + 0].WORD_0x8 = r0 >> 14 & 0x7;
			list[GX_ATTR_VTX_CLR - GX_ATTR_VTX + 0].WORD_0x4 = r0 >> 13 & 0x1;
			
			list[GX_ATTR_VTX_CLR - GX_ATTR_VTX + 1].WORD_0x8 = r0 >> 18 & 0x7;
			list[GX_ATTR_VTX_CLR - GX_ATTR_VTX + 1].WORD_0x4 = r0 >> 17 & 0x1;
			
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 0].WORD_0x8 = r0 >> 22 & 0x7;
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 0].WORD_0x4 = r0 >> 21 & 0x1;
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 0].BYTE_0xC = r0 >> 25 & 0x1f;
			
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 1].WORD_0x8 = r5 >> 1 & 0x7;
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 1].WORD_0x4 = r5 & 1;
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 1].BYTE_0xC = r5 >> 4 & 0x1f;
			
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 2].WORD_0x8 = r5 >> 10 & 0x7;
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 2].WORD_0x4 = r5 >> 9 & 0x1;
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 2].BYTE_0xC = r5 >> 13 & 0x1f;
			
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 3].WORD_0x8 = r5 >> 19 & 0x7;
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 3].WORD_0x4 = r5 >> 18 & 0x1;
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 3].BYTE_0xC = r5 >> 22 & 0x1f;
			
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 4].WORD_0x8 = r5 >> 28 & 0x7;
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 4].WORD_0x4 = r5 >> 27 & 0x1;
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 4].BYTE_0xC = r16 & 0x1f;
			
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 5].WORD_0x8 = r16 >> 6 & 0x7;
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 5].WORD_0x4 = r16 >> 5 & 0x1;
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 5].BYTE_0xC = r16 >> 9 & 0x1f;
			
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 6].WORD_0x8 = r16 >> 15 & 0x7;
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 6].WORD_0x4 = r16 >> 14 & 0x1;
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 6].BYTE_0xC = r16 >> 18 & 0x1f;
			
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 7].WORD_0x8 = r16 >> 24 & 0x7;
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 7].WORD_0x4 = r16 >> 23 & 0x1;
			list[GX_ATTR_VTX_TEX_COORD - GX_ATTR_VTX + 7].BYTE_0xC = r16 >> 27;
			
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
			u32 i = attr - GX_ATTR_VTX;
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
			GXSetArray(GX_ATTR_VTX_POS, ptr_0x2c, byte_0x8);
			
			//80053D98
			ResVtxNrm vtxNrm = GetResVtxNrm();
			
			if (vtxNrm.mNrm.IsValid())
			{
				vtxNrm.GetArray(&ptr_0x2c, &byte_0x8);
				GXSetArray(GX_ATTR_VTX_NRM, ptr_0x2c, byte_0x8);
			}
			
			//80053E40
			for (u32 i = 0; i < GX_ATTR_VTX_CLR_COUNT; i++)
			{
				ResVtxClr vtxClr = GetResVtxClr(i);
				
				if (vtxClr.mClr.IsValid())
				{
					vtxClr.GetArray(&ptr_0x2c, &byte_0x8);
					GXSetArray((GXAttr)(GX_ATTR_VTX_CLR + i), ptr_0x2c, byte_0x8);
				}
			}
			
			//80053F2C
			for (u32 i = 0; i < GX_ATTR_VTX_TEX_COORD_COUNT; i++)
			{
				ResVtxTexCoord vtxTexCoord = GetResVtxTexCoord(i);
				
				if (vtxTexCoord.mTexCoord.IsValid())
				{
					vtxTexCoord.GetArray(&ptr_0x2c, &byte_0x8);
					GXSetArray((GXAttr)(GX_ATTR_VTX_TEX_COORD + i), ptr_0x2c, byte_0x8);
				}
			}
			
			//80054018
			DCStoreRangeNoSync(&GetResShpPrePrim().ref(), sizeof(ResPrePrimDL));
			
			ResShpData & data = ref();
			
			DCStoreRangeNoSync(ResTagDL(&data.mPrimDLTag).GetDL(), data.mPrimDLTag.mBufSize);
		}
		
		void ResShp::DisableSetArray(GXAttr attr)
		{
			memset(GetResShpPrePrim().ref().CP_CMD_PAIRS_0x32[attr - GX_ATTR_VTX], 0, sizeof(CPCmd) * 2);
		}
		
		void ResShp::Terminate()
		{
			DisableSetArray(GX_ATTR_VTX_POS);
			DisableSetArray(GX_ATTR_VTX_NRM);
			DisableSetArray((GXAttr)(GX_ATTR_VTX_CLR + 0));
			DisableSetArray((GXAttr)(GX_ATTR_VTX_CLR + 1));
			DisableSetArray((GXAttr)(GX_ATTR_VTX_TEX_COORD + 0));
			DisableSetArray((GXAttr)(GX_ATTR_VTX_TEX_COORD + 1));
			DisableSetArray((GXAttr)(GX_ATTR_VTX_TEX_COORD + 2));
			DisableSetArray((GXAttr)(GX_ATTR_VTX_TEX_COORD + 3));
			DisableSetArray((GXAttr)(GX_ATTR_VTX_TEX_COORD + 4));
			DisableSetArray((GXAttr)(GX_ATTR_VTX_TEX_COORD + 5));
			DisableSetArray((GXAttr)(GX_ATTR_VTX_TEX_COORD + 6));
			DisableSetArray((GXAttr)(GX_ATTR_VTX_TEX_COORD + 7));
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