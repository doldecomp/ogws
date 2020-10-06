#ifndef NW4R_UT_TEXT_WRITER_BASE
#define NW4R_UT_TEXT_WRITER_BASE
#include <stdarg.h>
#include "ut_TagProcessorBase.h"
#include "ut_CharWriter.h"
#include "ut_Rect.h"

namespace nw4r
{
	namespace ut
	{
		template<typename T>
		struct TextWriterBase : CharWriter
		{
			static TagProcessorBase<T> mDefaultTagProcessor;
			static T * mFormatBuffer;
			static u32 mFormatBufferSize;
			float FLOAT_0x4C;
			float FLOAT_0x50;
			float FLOAT_0x54;
			u32 mTabWidth; // at 0x58
			UNKWORD WORD_0x5C;
			TagProcessorBase<T> * mTagProcessor; // at 0x60
			
			TextWriterBase();
			~TextWriterBase();
			
			inline u32 GetTabWidth() const
			{
				return mTabWidth;
			}
			
			float GetLineHeight() const;
			int VSNPrintf(T *, u32, const T *, va_list);
			
			float AdjustCursor(float *, float *, const T *, int);
			float PrintImpl(const T *, int);
			bool CalcStringRectImpl(Rect *, const T *, int) __attribute__((never_inline));
			bool CalcLineRectImpl(Rect *, const T **, int);
			float Print(const T *, int);
			float VPrintf(const T *, va_list);
			
			void CalcStringRect(Rect *, const T *, int) const;
			float CalcStringWidth(const T *, int) const;
			float CalcLineWidth(const T *, int);
			
			inline bool IsDrawFlagSet(u32 mask, u32 flags) const
			{
				return (WORD_0x5C & mask) == flags;
			}
		};
	}
}

#endif