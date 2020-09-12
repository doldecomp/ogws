#ifndef NW4R_UT_CHAR_WRITER_BASE
#define NW4R_UT_CHAR_WRITER_BASE
#include "types_nw4r.h"
#include "math_types.h"
#include "ut_Color.h"

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
				Color COLOR_0x0;
				Color COLOR_0x4;
				Color COLOR_0x8;
				Color COLOR_0xC;
			};
			
			struct LoadingTexture
			{
				u32 u32_0x0;
				u32 u32_0x4;
			};
			
			struct TextColor
			{
				
			};
			
			static LoadingTexture mLoadingTexture;
			
			ColorMapping mColorMapping; // at 0x0
			
			VertexColor mVertexColor; // at 0x8
			Color COLOR_0x18;
			Color COLOR_0x1C;
			UNKWORD WORD_0x20;
			float FLOAT_0x24;
			float FLOAT_0x28;
			math::VEC2 mCursor;
			float FLOAT_0x34;
			UNKWORD WORD_0x38;
			UNKWORD WORD_0x3C;
			u8 BYTE_0x40;
			u8 BYTE_0x41;
			u8 BYTE_0x42;
			bool mWidthFixedFlag;
			float mFixedWidth;
			UNKWORD WORD_0x48;
			
			CharWriter();
			
			void SetColorMapping(Color, Color);
			void SetTextColor(Color);
			
			void UpdateVertexColor();
			
			UNKTYPE EnableLinearFilter(bool, bool);
			
			float GetFontWidth() const;
			float GetFontHeight() const;
			
			inline float GetFixedWidth() const
			{
				return mFixedWidth;
			}
			
			inline bool IsWidthFixed() const
			{
				return mWidthFixedFlag;
			}
			
			inline void SetCursorX(float x)
			{
				mCursor.x = x;
			}
			
			inline void SetCursorY(float y)
			{
				mCursor.y = y;
			}
			
			inline float GetCursorX() const
			{
				return mCursor.x;
			}
			
			inline float GetCursorY() const
			{
				return mCursor.y;
			}
		};
	}
}

#endif