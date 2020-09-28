#ifndef NW4R_UT_CHAR_WRITER_BASE
#define NW4R_UT_CHAR_WRITER_BASE
#include "types_nw4r.h"
#include "math_types.h"
#include "ut_Color.h"
#include "ut_Font.h"

namespace nw4r
{
	namespace ut
	{
		// TODO: Implement the object accurately
		struct CharWriter
		{
			struct ColorMapping
			{
				Color COLOR_0x0;
				Color COLOR_0x4;
			};
			
			struct VertexColor
			{
				Color mTopLeft;
				Color mTopRight;
				Color mBottomLeft;
				Color mBottomRight;
			};
			
			struct TextureFilter
			{
				int WORD_0x0;
				int WORD_0x4;
				
				inline bool operator!=(const TextureFilter & other) const
				{
					return WORD_0x0 != other.WORD_0x0 || WORD_0x4 != other.WORD_0x4;
				}
			};
			
			//sizeof(LoadingTexture) = 0x10
			struct LoadingTexture
			{
				s32 s32_0x0;
				u8 * PTR_0x4;
				TextureFilter mFilter;
				
				inline bool operator!=(const LoadingTexture & other) const
				{
					return s32_0x0 != other.s32_0x0 || PTR_0x4 != other.PTR_0x4 || mFilter != other.mFilter;
				}
				
				inline void Reset()
				{
					s32_0x0 = 0xFF;
					PTR_0x4 = 0;
				}
			};
			
			struct TextColor
			{
				Color mStart;
				Color mEnd;
			};
			
			enum GradationMode
			{
				GradMode_None,
				GradMode_Horizontal,
				GradMode_Vertical
			};
			
			static LoadingTexture mLoadingTexture;
			
			ColorMapping mColorMapping; // at 0x0
			
			VertexColor mVertexColor; // at 0x8
			TextColor mTextColor; // at 0x18
			GradationMode mGradationMode; // at 0x20
			math::VEC2 mScale; // at 0x24
			math::VEC3 mCursor; // at 0x2c
			TextureFilter mFilter; // at 0x38
			u8 BYTE_0x40;
			u8 BYTE_0x41;
			u8 BYTE_0x42;
			bool mWidthFixedFlag;
			float mFixedWidth;
			Font * mFont; // at 0x48
			
			CharWriter();
			~CharWriter();
			
			void SetColorMapping(Color, Color);
			void SetTextColor(Color);
			
			void UpdateVertexColor();
			
			float GetFontWidth() const;
			float GetFontHeight() const;
			
			float GetFontAscent() const;
			float GetFontDescent() const;
			
			void EnableLinearFilter(bool, bool);
			
			float Print(u16);
			
			void LoadTexture(const Glyph &);//inlined
			
			void PrintGlyph(float, float, float, const Glyph &);
			
			inline float GetFixedWidth() const { return mFixedWidth; }
			inline bool IsWidthFixed() const { return mWidthFixedFlag; }
			inline void SetCursorX(float x) { mCursor.x = x; }
			inline void SetCursorY(float y) { mCursor.y = y; }
			inline float GetCursorX() const { return mCursor.x; }
			inline float GetCursorY() const { return mCursor.y; }
			
			void SetupGX();
			static void SetupGXWithColorMapping(Color, Color);
			void SetupGXDefault(); //inlined
			
			void SetFontSize(float, float);
			
			inline void SetScale(float x, float y)
			{
				mScale.x = x;
				mScale.y = y;
			}
			
			inline void SetCursor(float x, float y, float z)
			{
				SetCursorX(x);
				SetCursorY(y);
				mCursor.z = z;
			}
			
			inline void ResetColorMapping()
			{
				SetColorMapping(Color(0), Color());
			}
			
			inline void SetGradationMode(GradationMode gradationMode)
			{
				mGradationMode = gradationMode;
				
				mVertexColor.mTopLeft = mTextColor.mStart;
				mVertexColor.mTopRight = (mGradationMode != GradMode_Horizontal) ? mTextColor.mStart : mTextColor.mEnd;
				mVertexColor.mBottomLeft = (mGradationMode != GradMode_Vertical) ? mTextColor.mStart : mTextColor.mEnd;
				mVertexColor.mBottomRight = (mGradationMode == GradMode_None) ? mTextColor.mStart : mTextColor.mEnd;
				
				mVertexColor.mTopLeft.mChannels.a = (mVertexColor.mTopLeft.mChannels.a * BYTE_0x42) / 0xFF,
				mVertexColor.mTopRight.mChannels.a = (mVertexColor.mTopRight.mChannels.a * BYTE_0x42) / 0xFF;
				mVertexColor.mBottomLeft.mChannels.a = (mVertexColor.mBottomLeft.mChannels.a * BYTE_0x42) / 0xFF;
				mVertexColor.mBottomRight.mChannels.a = (mVertexColor.mBottomRight.mChannels.a * BYTE_0x42) / 0xFF;
			}
		};
	}
}

#endif