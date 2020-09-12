#include "ut_TagProcessorBase.h"
#include "ut_TextWriterBase.h"
#include "ut_CharWriter.h"

namespace nw4r
{
	namespace ut
	{
		template <typename T> TagProcessorBase<T>::TagProcessorBase() {}
		
		template <typename T> TagProcessorBase<T>::~TagProcessorBase() {}
		
		template <typename T>
		int TagProcessorBase<T>::Process(u16 procCh, PrintContext<T> * pContext)
		{
			switch(procCh)
			{
				case '\n':
					ProcessLinefeed(pContext);
					return 3;
				case '\t':
					ProcessTab(pContext);
					return 1;
			}
			return 0;
		}
		
		template <typename T>
		int TagProcessorBase<T>::CalcRect(register Rect * pRect, u16 procCh, PrintContext<T> * pContext)
		{
			switch(procCh)
			{
				case '\n':
				{
					TextWriterBase<T> * r30_newline;
					
					r30_newline = pContext->mTextWriter;
					
					pRect->FLOAT_0x8 = r30_newline->GetCursorX();
					pRect->FLOAT_0x4 = r30_newline->GetCursorY();
					
					ProcessLinefeed(pContext);
					
					pRect->FLOAT_0x0 = r30_newline->GetCursorX();
					
					pRect->FLOAT_0xC = r30_newline->GetCursorY() + pContext->mTextWriter->GetFontHeight();
					
					register float out_0x4;
					
					register float dif1;
					register float dif2;
					
					register float out_0x0;
					register float out_0x8;
					register float out_0xc;
					
					register float in_0xc;
					register float in_0x8;
					register float in_0x4;
					register float in_0x0;
					
					in_0x0 = pRect->FLOAT_0x0;
					in_0x4 = pRect->FLOAT_0x4;
					in_0x8 = pRect->FLOAT_0x8;
					in_0xc = pRect->FLOAT_0xC;
					
					dif1 = in_0xc - in_0x4;
					dif2 = in_0x8 - in_0x0;
					
					asm
					{
						fsel out_0x4, dif1, in_0x4, in_0xc
						fsel out_0x0, dif2, in_0x0, in_0x8
						fsel out_0x8, dif2, in_0x8, in_0x0
						fsel out_0xc, dif1, in_0xc, in_0x4
						stfs out_0x4, 0x4(pRect)
						stfs out_0x0, 0x0(pRect)
						stfs out_0x8, 0x8(pRect)
						stfs out_0xc, 0xc(pRect)
					}
					
					return 3;
				}
				case '\t':
				{
					TextWriterBase<T> * r29_tab;
					
					r29_tab = pContext->mTextWriter;
					
					pRect->FLOAT_0x0 = r29_tab->GetCursorX();
					
					ProcessTab(pContext);
					
					pRect->FLOAT_0x8 = r29_tab->GetCursorX();
					pRect->FLOAT_0x4 = r29_tab->GetCursorY();
					
					pRect->FLOAT_0xC = pRect->FLOAT_0x4 + r29_tab->GetFontHeight();
					
					register float out_0x4;
					
					register float dif1;
					register float dif2;
					
					register float in_0x8;
					
					register float out_0x0;
					register float out_0x8;
					register float out_0xc;
					
					register float in_0xc;
					register float in_0x4;
					register float in_0x0;
					
					in_0x0 = pRect->FLOAT_0x0;
					in_0x4 = pRect->FLOAT_0x4;
					in_0x8 = pRect->FLOAT_0x8;
					in_0xc = pRect->FLOAT_0xC;
					
					dif2 = in_0x8 - in_0x0;
					dif1 = in_0xc - in_0x4;
					
					asm
					{
						fsel out_0x0, dif2, in_0x0, in_0x8
						fsel out_0x8, dif2, in_0x8, in_0x0
						fsel out_0x4, dif1, in_0x4, in_0xc
						fsel out_0xc, dif1, in_0xc, in_0x4
						stfs out_0x0, 0x0(pRect)
						stfs out_0x8, 0x8(pRect)
						stfs out_0x4, 0x4(pRect)
						stfs out_0xc, 0xc(pRect)
					}
					return 1;
				}
			}
			
			return 0;
		}
		
		template struct TagProcessorBase<char>;
		template struct TagProcessorBase<wchar_t>;
	}
}