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
			enum GradationMode { GRADMODE_NONE, GRADMODE_H, GRADMODE_V };

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
			
			struct TextureFilter {
				GXTexFilter atSmall; // at 0x0
				GXTexFilter atLarge; // at 0x4

				bool operator!=(const TextureFilter& other) const {
					return atSmall != other.atSmall || atLarge != other.atLarge;
				}
			};
			
			struct LoadingTexture {
				GXTexMapID slot; // at 0x0
				void* texture;   // at 0x4
				TextureFilter filter;

				bool operator!=(const LoadingTexture& other) const {
					return slot != other.slot || texture != other.texture ||
						filter != other.filter;
				}

				void Reset() {
					slot = GX_TEXMAP_NULL;
					texture = NULL;
				}
			};
			
			struct TextColor {
				Color start;            // at 0x0
				Color end;              // at 0x4
				GradationMode gradMode; // at 0x8
			};
			
			static LoadingTexture mLoadingTexture;
			
			ColorMapping mColorMapping; // at 0x0		
			VertexColor mVertexColor; // at 0x8
			TextColor mTextColor; // at 0x18
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
			inline void SetCursorX(float x) { mCursor.mCoords.x = x; }
			inline void SetCursorY(float y) { mCursor.mCoords.y = y; }
			inline void MoveCursorX(float x) { mCursor.mCoords.x += x; }
			inline void MoveCursorY(float y) { mCursor.mCoords.y += y; }
			inline float GetCursorX() const { return mCursor.mCoords.x; }
			inline float GetCursorY() const { return mCursor.mCoords.y; }
			
			void SetupGX();
			static void SetupGXWithColorMapping(Color, Color);
			void SetupGXDefault(); //inlined
			
			void SetFontSize(float, float);
			
			inline void SetScale(float x, float y)
			{
				mScale.mCoords.x = x;
				mScale.mCoords.y = y;
			}
			
			inline void SetCursor(float x, float y)
			{
				mCursor.mCoords.x = x;
				mCursor.mCoords.y = y;
			}
			inline void SetCursor(float x, float y, float z)
			{
				mCursor.mCoords.x = x;
				mCursor.mCoords.y = y;
				mCursor.mCoords.z = z;
			}
			
			inline void ResetColorMapping()
			{
				SetColorMapping(Color(0), Color());
			}
			
			inline void SetGradationMode(GradationMode gradationMode)
			{
				mTextColor.gradMode = gradationMode;
				
				mVertexColor.mTopLeft = mTextColor.start;
				mVertexColor.mTopRight = (mTextColor.gradMode != GRADMODE_H) ? mTextColor.start : mTextColor.end;
				mVertexColor.mBottomLeft = (mTextColor.gradMode != GRADMODE_V) ? mTextColor.start : mTextColor.end;
				mVertexColor.mBottomRight = (mTextColor.gradMode == GRADMODE_NONE) ? mTextColor.start : mTextColor.end;
				
				mVertexColor.mTopLeft.a = (mVertexColor.mTopLeft.a * BYTE_0x42) / 0xFF,
				mVertexColor.mTopRight.a = (mVertexColor.mTopRight.a * BYTE_0x42) / 0xFF;
				mVertexColor.mBottomLeft.a = (mVertexColor.mBottomLeft.a * BYTE_0x42) / 0xFF;
				mVertexColor.mBottomRight.a = (mVertexColor.mBottomRight.a * BYTE_0x42) / 0xFF;
			}
		};
	}
}

#endif