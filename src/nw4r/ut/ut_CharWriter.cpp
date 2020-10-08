#include "ut_CharWriter.h"

namespace
{
	static void SetupGXCommon()
	{
		static const nw4r::ut::Color fog = 0;
		
		GXSetFog(0, fog, 0.0f, 0.0f, 0.0f, 0.0f);
		GXSetTevSwapModeTable(0, 0, 1, 2, 3);
		GXSetZTexture(0, 17, 0);
		GXSetNumChans(1);
		GXSetChanCtrl(4, 0, 0, 1, 0, 0, 2);
		GXSetChanCtrl(5, 0, 0, 0, 0, 0, 2);
		GXSetNumTexGens(1);
		GXSetTexCoordGen2(0, 1, 4, 60, 0, 125);
		GXSetNumIndStages(0);
		GXSetBlendMode(1, 4, 5, 15);
	}
}

namespace nw4r
{
	namespace ut
	{
		CharWriter::CharWriter() : BYTE_0x42(0xFF), mWidthFixedFlag(false), mFixedWidth(0.0f), mFont(NULL)
		{
			mLoadingTexture.Reset();
			ResetColorMapping();
			SetGradationMode(GradMode_None);
			SetTextColor(Color());
			SetScale(1.0f, 1.0f);
			SetCursor(0.0f, 0.0f, 0.0f);
			mFilter.WORD_0x0 = true;
			mFilter.WORD_0x4 = true;
		}
		
		void CharWriter::SetColorMapping(Color color1, Color color2)
		{
			mColorMapping.COLOR_0x0 = color1;
			mColorMapping.COLOR_0x4 = color2;
		}
		
		void CharWriter::SetTextColor(Color color)
		{
			mTextColor.mStart = color;
			mVertexColor.mTopLeft = mTextColor.mStart;
			mVertexColor.mTopRight = (mGradationMode != GradMode_Horizontal) ? mTextColor.mStart : mTextColor.mEnd;
			mVertexColor.mBottomLeft = (mGradationMode != GradMode_Vertical) ? mTextColor.mStart : mTextColor.mEnd;
			mVertexColor.mBottomRight = (mGradationMode == GradMode_None) ? mTextColor.mStart : mTextColor.mEnd;
			
			mVertexColor.mTopLeft.mChannels.a = (mVertexColor.mTopLeft.mChannels.a * BYTE_0x42) / 0xFF,
			mVertexColor.mTopRight.mChannels.a = (mVertexColor.mTopRight.mChannels.a * BYTE_0x42) / 0xFF;
			mVertexColor.mBottomLeft.mChannels.a = (mVertexColor.mBottomLeft.mChannels.a * BYTE_0x42) / 0xFF;
			mVertexColor.mBottomRight.mChannels.a = (mVertexColor.mBottomRight.mChannels.a * BYTE_0x42) / 0xFF;
		}
		CharWriter::~CharWriter() {}
		
		void CharWriter::SetupGXDefault()
		{
			SetupGXCommon();
			GXSetNumTevStages(1);
			GXSetTevDirect(0);
			GXSetTevSwapMode(0,0,0);
			GXSetTevOrder(0,0,0,4);
			GXSetTevOp(0,0);
			GXSetVtxAttrFmt(0,9,1,4,0);
			GXSetVtxAttrFmt(0,0xb,1,5,0);
			GXSetVtxAttrFmt(0,0xd,1,2,0xf);
			GXClearVtxDesc();
			GXSetVtxDesc(9,1);
			GXSetVtxDesc(0xb,1);
			GXSetVtxDesc(0xd,1);
		}
		
		void CharWriter::SetupGX()
		{
			mLoadingTexture.Reset();
			if ((u32)mColorMapping.COLOR_0x0 != 0 || (u32)mColorMapping.COLOR_0x4 != 0xFFFFFFFF)
			{
				SetupGXWithColorMapping(mColorMapping.COLOR_0x0, mColorMapping.COLOR_0x4);
			}
			else if (mFont)
			{
				switch (mFont->GetTextureFormat())
				{
					case 0:
					case 1:
						SetupGXCommon();
						GXSetNumTevStages(1);
						GXSetTevDirect(0);
						GXSetTevSwapMode(0,0,0);
						GXSetTevOrder(0,0,0,4);
						GXSetTevColorIn(0,0xf,0xf,0xf,10);
						GXSetTevAlphaIn(0,7,4,5,7);
						GXSetTevColorOp(0,0,0,0,1,0);
						GXSetTevAlphaOp(0,0,0,0,1,0);
						GXSetVtxAttrFmt(0,9,1,4,0);
						GXSetVtxAttrFmt(0,0xb,1,5,0);
						GXSetVtxAttrFmt(0,0xd,1,2,0xf);
						GXClearVtxDesc();
						GXSetVtxDesc(9,1);
						GXSetVtxDesc(0xb,1);
						GXSetVtxDesc(0xd,1);
						break;
					case 2:
					case 3:
						SetupGXDefault();
						break;
					case 4:
					case 5:
					case 6:
						SetupGXDefault();
						break;
					default:
						SetupGXDefault();
						break;
				}
			}
			else
			{
				SetupGXDefault();
			}
		}
		
		void CharWriter::SetFontSize(float width, float height)
		{
			SetScale(width / mFont->GetWidth(), height / mFont->GetHeight());
		}
		
		float CharWriter::GetFontWidth() const
		{
			return mScale.mCoords.x * mFont->GetWidth();
		}
		
		float CharWriter::GetFontHeight() const
		{
			return mScale.mCoords.y * mFont->GetHeight();
		}
		
		float CharWriter::GetFontAscent() const
		{
			return mScale.mCoords.y * mFont->GetAscent();
		}
		
		float CharWriter::GetFontDescent() const
		{
			return mScale.mCoords.y * mFont->GetDescent();
		}
		
		void CharWriter::EnableLinearFilter(bool b1, bool b2)
		{
			mFilter.WORD_0x0 = b1 != FALSE;
			mFilter.WORD_0x4 = b2 != FALSE;
		}
		
		float CharWriter::Print(u16 ch)
		{
			Glyph glyph; // at 0x8
			
			mFont->GetGlyph(&glyph, ch);
			
			float xOfs;
			float ret;
			
			if (mWidthFixedFlag)
			{
				ret = mFixedWidth;
				xOfs = (ret - glyph.BYTE_0x6 * mScale.mCoords.x) / 2 + (glyph.BYTE_0x4 * mScale.mCoords.x);
			}
			else
			{
				ret = glyph.BYTE_0x6 * mScale.mCoords.x;
				xOfs = glyph.BYTE_0x4 * mScale.mCoords.x;
			}
			
			PrintGlyph(mCursor.mCoords.x + xOfs, mCursor.mCoords.y, mCursor.mCoords.z, glyph);
			mCursor.mCoords.x += ret;
			
			return ret;
		}
		
		void CharWriter::LoadTexture(const Glyph & glyph)
		{
			_GXTexObj texObj;
			LoadingTexture loadingTexture;
			
			loadingTexture.s32_0x0 = 0;
			loadingTexture.PTR_0x4 = glyph.PTR_0x0;//r0
			loadingTexture.mFilter = mFilter;
			
			if (loadingTexture != mLoadingTexture)
			{
				GXInitTexObj(&texObj, glyph.PTR_0x0, glyph.SHORT_0xC, glyph.SHORT_0xE,
				glyph.WORD_0x8, 0, 0, 0);
				GXInitTexObjLOD(&texObj, mFilter.WORD_0x0, mFilter.WORD_0x4, 0, 0, 0,
				0.0f, 0.0f, 0.0f);
				GXLoadTexObj(&texObj, 0);
				mLoadingTexture = loadingTexture;
			}
		}
		
		void CharWriter::PrintGlyph(float x, float y, float z, const Glyph & glyph)
		{
			u32 left;
			u32 top;
			u32 right;
			u32 bottom;
			
			u16 normLeft;
			u16 normTop;
			u16 normRight;
			u16 normBottom;
			
			float x2;
			float y2;
			
			x2 = x + (glyph.cellWidth * mScale.mCoords.x);
			y2 = y + (glyph.cellHeight * mScale.mCoords.y);
			
			left = glyph.SHORT_0x10;
			normLeft = 0x8000 * left / glyph.SHORT_0xC;
			
			top = glyph.SHORT_0x12;
			normTop = 0x8000 * top / glyph.SHORT_0xE;
			
			right = left + glyph.cellWidth;
			normRight = 0x8000 * right / glyph.SHORT_0xC;
			
			bottom = top + glyph.cellHeight;
			normBottom = 0x8000 * bottom / glyph.SHORT_0xE;
			
			LoadTexture(glyph);
			
			GXBegin(0x80, 0, 4);
			
			WGPIPE.f = x;
			WGPIPE.f = y;
			WGPIPE.f = z;
			WGPIPE.i = mVertexColor.mTopLeft;
			WGPIPE.s = normLeft;
			WGPIPE.s = normTop;
			
			WGPIPE.f = x2;
			WGPIPE.f = y;
			WGPIPE.f = z;
			WGPIPE.i = mVertexColor.mTopRight;
			WGPIPE.s = normRight;
			WGPIPE.s = normTop;
			
			WGPIPE.f = x2;
			WGPIPE.f = y2;
			WGPIPE.f = z;
			WGPIPE.i = mVertexColor.mBottomRight;
			WGPIPE.s = normRight;
			WGPIPE.s = normBottom;
			
			WGPIPE.f = x;
			WGPIPE.f = y2;
			WGPIPE.f = z;
			WGPIPE.i = mVertexColor.mBottomLeft;
			WGPIPE.s = normLeft;
			WGPIPE.s = normBottom;
			
			GXEnd();
		}
		
		void CharWriter::UpdateVertexColor()
		{
			mVertexColor.mTopLeft = mTextColor.mStart;
			mVertexColor.mTopRight = (mGradationMode != GradMode_Horizontal) ? mTextColor.mStart : mTextColor.mEnd;
			mVertexColor.mBottomLeft = (mGradationMode != GradMode_Vertical) ? mTextColor.mStart : mTextColor.mEnd;
			mVertexColor.mBottomRight = (mGradationMode == GradMode_None) ? mTextColor.mStart : mTextColor.mEnd;
			
			mVertexColor.mTopLeft.mChannels.a = (mVertexColor.mTopLeft.mChannels.a * BYTE_0x42) / 0xFF,
			mVertexColor.mTopRight.mChannels.a = (mVertexColor.mTopRight.mChannels.a * BYTE_0x42) / 0xFF;
			mVertexColor.mBottomLeft.mChannels.a = (mVertexColor.mBottomLeft.mChannels.a * BYTE_0x42) / 0xFF;
			mVertexColor.mBottomRight.mChannels.a = (mVertexColor.mBottomRight.mChannels.a * BYTE_0x42) / 0xFF;
		}
		
		void CharWriter::SetupGXWithColorMapping(Color color1, Color color2)
		{
			SetupGXCommon();
			GXSetNumTevStages(2);
			GXSetTevDirect(0);
			GXSetTevDirect(1);
			GXSetTevSwapMode(0, 0, 0);
			GXSetTevSwapMode(1, 0, 0);
			GXSetTevOrder(0, 0, 0, 0xFF);
			GXSetTevColor(1, color1.mChannels);
			GXSetTevColor(2, color2.mChannels);
			GXSetTevColorIn(0,2,4,8,0xf);
			GXSetTevAlphaIn(0,1,2,4,7);
			GXSetTevColorOp(0,0,0,0,1,0);
			GXSetTevAlphaOp(0,0,0,0,1,0);
			GXSetTevOrder(1,0xff,0xff,4);
			GXSetTevColorIn(1,0xf,0,10,0xf);
			GXSetTevAlphaIn(1,7,0,5,7);
			GXSetTevColorOp(1,0,0,0,1,0);
			GXSetTevAlphaOp(1,0,0,0,1,0);
			GXSetVtxAttrFmt(0,9,1,4,0);
			GXSetVtxAttrFmt(0,0xb,1,5,0);
			GXSetVtxAttrFmt(0,0xd,1,2,0xf);
			GXClearVtxDesc();
			GXSetVtxDesc(9,1);
			GXSetVtxDesc(0xb,1);
			GXSetVtxDesc(0xd,1);
		}
		
		CharWriter::LoadingTexture CharWriter::mLoadingTexture;
	}
}