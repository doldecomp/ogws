#ifndef NW4R_UT_TAG_PROCESSOR_BASE
#define NW4R_UT_TAG_PROCESSOR_BASE
#include "types_nw4r.h"
#include "ut_TextWriterBase.h"
#include "ut_Rect.h"

namespace nw4r
{
	namespace ut
	{		
		template<typename T>
		struct PrintContext
		{
			TextWriterBase<T> * mTextWriter;
			float FLOAT_0x4;
			float FLOAT_0x8;
			
		};
		
		template<typename T>
		struct TagProcessorBase
		{
			TagProcessorBase();
			
			virtual ~TagProcessorBase();
			virtual int Process(u16, PrintContext<T> *);
			virtual int CalcRect(register Rect *, u16, PrintContext<T> *);
			
			inline void ProcessTab(PrintContext<T> * pContext)
			{
				s32 r30;
				TextWriterBase<T> * r31;
				
				float f0;
				float f1;
				float f4;
				float f3;
				
				r31 = pContext->mTextWriter;
				r30 = r31->GetTabWidth();
				
				if (r30 <= 0) return;
				
				f1 = r31->IsWidthFixed() ? r31->GetFixedWidth() : r31->GetFontWidth();
				f4 = r31->GetCursorX();
				f3 = pContext->FLOAT_0x8;
				f1 = r30 * f1;
				f4 -= f3;
				f0 = (s32)(f4 / f1) + 1;
				r31->SetCursorX(f3 + (f1 * f0));
			}
			
			inline void ProcessLinefeed(PrintContext<T> * pContext)
			{
				TextWriterBase<T> * r31;
				
				float f0;
				float f31;
				float f30;
				
				r31 = pContext->mTextWriter;
				f31 = pContext->FLOAT_0x8;
				f30 = r31->GetCursorY();
				
				f0 = f30 + r31->GetLineHeight();
				
				r31->SetCursorX(f31);
				r31->SetCursorY(f0);
			}
		};
		
		template struct TagProcessorBase<char>;
		template struct TagProcessorBase<wchar_t>;
	}
}

#endif