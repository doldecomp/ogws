#ifdef __DECOMP_NON_MATCHING
#include <stdio.h>
#include "ut_TextWriterBase.h"
#include "ut_algorithm.h"
#include "ut_TagProcessorBase.h"

#pragma inline_depth(6)
#pragma inline_bottom_up off

namespace nw4r
{
	namespace ut
	{
		template <typename T>
		float TextWriterBase<T>::CalcLineWidth(const T * str, int len)
		{
			Rect rect;
			TextWriterBase<T> clone(*this);
			clone.SetCursor(0.0f, 0.0f);
			clone.CalcLineRectImpl(&rect, &str, len);
			return rect.GetWidth();
		}
		
		template <typename T>
		void TextWriterBase<T>::CalcStringRect(Rect * pRect, const T * str, int len) const
		{
			TextWriterBase<T>(*this).CalcStringRectImpl(pRect, str, len);
		}
		
		template <typename T>
		float TextWriterBase<T>::CalcStringWidth(const T * str, int len) const
		{
			Rect rect;
			TextWriterBase<T>(*this).CalcStringRectImpl(&rect, str, len);
			return rect.GetWidth();
		}
		
		template <>
		int TextWriterBase<char>::VSNPrintf(char * dest, u32 count, const char * format, va_list vlst)
		{
			return vsnprintf(dest, count, format, vlst);
		}
		
		template <typename T>
		TextWriterBase<T>::TextWriterBase()
		{
			FLOAT_0x50 = 0.0f;
			FLOAT_0x4C = F32_MAX;
			FLOAT_0x54 = 0.0f;
			mTabWidth = 4;
			WORD_0x5C = 0;
			mTagProcessor = &mDefaultTagProcessor;
		}
		template <typename T> TextWriterBase<T>::~TextWriterBase() {}
		
		template <typename T>
		float TextWriterBase<T>::GetLineHeight() const
		{
			int lf = (mFont ? mFont->GetLineFeed() : 0);
			return FLOAT_0x54 + mScale.y * lf;//(mFont ? mFont->GetLineFeed() : 0);
		}
		
		template <typename T>
		float TextWriterBase<T>::VPrintf(const T * str, va_list vlst)
		{
			T * pBuffer;
			
			if (mFormatBuffer)
			{
				pBuffer = mFormatBuffer;
			}
			else
			{
				T buffer[mFormatBufferSize];
				
				pBuffer = buffer;
			}
			
			int count = VSNPrintf(pBuffer, mFormatBufferSize, str, vlst);
			
			TextWriterBase<T> clone = *this;
			float ret = clone.PrintImpl(pBuffer, count);
			SetCursorX(clone.GetCursorX());
			SetCursorY(clone.GetCursorY());
			
			return ret;
		}
		
		template <typename T>
		float TextWriterBase<T>::Print(const T * str, int num)
		{
			TextWriterBase<T> clone = *this;
			float ret = clone.PrintImpl(str, num);
			SetCursorX(clone.GetCursorX());
			SetCursorY(clone.GetCursorY());
			return ret;
		}
		
		template <typename T>
		bool TextWriterBase<T>::CalcLineRectImpl(Rect * pRect, const T ** pStr, int len)
		{
			
			const T * strBegin = *pStr;
			const T * strEnd = strBegin + len;//r31
			bool r30 = FLOAT_0x4C < F32_MAX;
			
			float f31 = 0.0f;
			PrintContext<T> stack_0x5c = { this };
			stack_0x5c.PTR_0x4 = strBegin;
			Rect stack_0x38(0.0f, 0.0f, 0.0f, 0.0f), *pstack_0x38 = &stack_0x38;
			bool r29 = false;
			bool r28 = false;
			CharStrmReader stack_0x28 = mFont->GetCharStrmReader();
			pRect->FLOAT_0x0 = 0.0f;
			pRect->FLOAT_0x8 = 0.0f;
			pRect->FLOAT_0x4 = Min<float>(GetLineHeight(), 0);
			pRect->FLOAT_0xC = Max<float>(GetLineHeight(), 0);
			const T * r27 = NULL;
			
			*pstack_0x38 = *pRect;
			
			stack_0x28.Set(strBegin);
			u16 r26 = stack_0x28.Next();
			
			while ((const T *)stack_0x28.mStrm <= strEnd)
			{
				if (r26 < ' ')
				{
					Rect stack_0x18(f31, 0.0f, 0.0f, 0.0f); // from 0x18 to 0x27
					stack_0x5c.PTR_0x4 = (const T *)stack_0x28.mStrm;
					stack_0x5c.WORD_0x10 = !r29;
					SetCursorX(f31);
					
					if (r30 && r26 != '\n' && r27)
					{
						PrintContext<T> stack_0x48(stack_0x5c);
						TextWriterBase<T> clone(*this); // at 0x70
						Rect stack_0x8;
						stack_0x48.mTextWriter = &clone;
						this->mTagProcessor->CalcRect(&stack_0x8, r26, &stack_0x48);
						if (stack_0x8.GetWidth() > 0.0f &&
						clone.GetCursorX() - stack_0x5c.FLOAT_0x8 > FLOAT_0x4C)
						{
							stack_0x28.Set(r27);
							r26 = '\n';
							r28 = true;
							continue;
						}
					}
					//lbl_8000CFD8
					int calcRectRet = mTagProcessor->CalcRect(&stack_0x18, r26, &stack_0x5c);
					
					stack_0x28.Set(stack_0x5c.PTR_0x4);
					
					pRect->FLOAT_0x0 = Min<float>(pRect->FLOAT_0x0, stack_0x18.FLOAT_0x0);
					pRect->FLOAT_0x4 = Min<float>(pRect->FLOAT_0x4, stack_0x18.FLOAT_0x4);
					pRect->FLOAT_0x8 = Max<float>(pRect->FLOAT_0x8, stack_0x18.FLOAT_0x8);
					pRect->FLOAT_0xC = Max<float>(pRect->FLOAT_0xC, stack_0x18.FLOAT_0xC);
					
					f31 = GetCursorX();
					
					if (calcRectRet == 4)
					{
						*pStr += len;
						return false;
					}
					if (calcRectRet == 1)
					{
						r29 = false;
					}
					else if (calcRectRet == 2)
					{
						r29 = true;
					}
					else if (calcRectRet == 3) break;
					
				}
				else
				{
					//lbl_8000D0BC
					float f28;
					float f27 = 0.0f;
					if (!r29) f27 += FLOAT_0x50;
					
					//f27 += (IsWidthFixed() ? GetFixedWidth() : (mFont->GetCharWidth(r26) * mScale.x));
					if (IsWidthFixed())
					{
						f27 += GetFixedWidth();
					}
					else
					{
						f28 = mScale.x;
						float f0 = mFont->GetCharWidth(r26);
						f27 += f0 * f28;
					}
					
					if (r30 && r27 && f31 + f27 > FLOAT_0x4C)
					{
						stack_0x28.Set(r27);
						r28 = true;
						r26 = '\n';
						continue;
					}
					
					f31 += f27;
					
					pRect->FLOAT_0x0 = Min<float>(pRect->FLOAT_0x0, f31);
					pRect->FLOAT_0x8 = Max<float>(pRect->FLOAT_0x8, f31);
					r29 = true;
				}
				
				if (r30) r27 = (const T *)stack_0x28.mStrm;
				r26 = stack_0x28.Next();
			}
			//lbl_8000D1AC: BREAK
			*pStr = (const T *)stack_0x28.mStrm;
			return r28;
			//lbl_8000D1B8: RETURN
		}
		
		template <typename T>
		bool TextWriterBase<T>::CalcStringRectImpl(Rect * pRect, const T * str, int len)
		{
			bool ret;
			const T * strEnd = str + len;
			
			pRect->FLOAT_0x0 = 0.0f;
			pRect->FLOAT_0x4 = 0.0f;
			pRect->FLOAT_0x8 = 0.0f;
			pRect->FLOAT_0xC = 0.0f;
			
			int i = len;
			
			SetCursor(0.0f, 0.0f);
			
			do
			{
				Rect rect;
				
				ret = CalcLineRectImpl(&rect, &str, i);
				
				i = strEnd - str;
				
				pRect->FLOAT_0x0 = Min<float>(pRect->FLOAT_0x0, rect.FLOAT_0x0);
				pRect->FLOAT_0x4 = Min<float>(pRect->FLOAT_0x4, rect.FLOAT_0x4);
				pRect->FLOAT_0x8 = Max<float>(pRect->FLOAT_0x8, rect.FLOAT_0x8);
				pRect->FLOAT_0xC = Max<float>(pRect->FLOAT_0xC, rect.FLOAT_0xC);
			} while(i > 0);
			
			return ret;
		}
		
		template <typename T>
		float TextWriterBase<T>::PrintImpl(const T * str, int len)
		{
			//r24 <- str (r4)
			//r25 <- len (r5)
			//r23 <- this (r3)
			
			
			float cursorX = GetCursorX(); // at 0x14
			
			float f28 = GetCursorY();
			float cursorY = f28; // at 0x10
			
			bool r30 = FLOAT_0x4C < F32_MAX;
			
			const T * r28 = str;
			const T * r27 = str;
			
			bool r29 = false;
			
			float f25 = AdjustCursor(&cursorX, &cursorY, str, len);
			
			float f26 = f28 - GetCursorY();
			
			PrintContext<T> context = { 0 }; // at 0x6c
			
			context.mTextWriter = this;
			context.PTR_0x4 = str;
			context.FLOAT_0x8 = cursorX;
			context.FLOAT_0xC = cursorY;
			
			CharStrmReader strmReader = mFont->GetCharStrmReader(); // at 0x48
			
			strmReader.Set(str);
			u16 r26 = strmReader.Next(); // r26
			//f29 = 0.0f
			//f30 = 0.5f
			//f31, r22: int2float conv constant
			while ((const T *)strmReader.mStrm - str <= len) //8000DCB8
			{
				//8000D464
				if (r26 < ' ')
				{
					//8000D470
					context.PTR_0x4 = (const T *)strmReader.mStrm;
					context.WORD_0x10 = !r29;
					if (r30 && r26 != '\n' && r28 != r27)
					{
						//8000D498
						PrintContext<T> stack_0x58 = context;
						
						TextWriterBase<T> clone = *this; // at 0x148
						
						Rect stack_0x38;
						
						context.mTextWriter = &clone;
						
						mTagProcessor->CalcRect(&stack_0x38, r26, &stack_0x58);
						
						if (stack_0x38.GetWidth() > 0.0f &&
						clone.GetCursorX() - context.FLOAT_0x8 > FLOAT_0x4C)
						{
							strmReader.Set(r28);
							r26 = '\n';
							continue;
						}
					}
					//8000D6D8
					int processRet = mTagProcessor->Process(r26, &context);
					
					if (processRet == 3)
					{
						//8000D700
						if (IsDrawFlagSet(0x3, 0x1))
						{
							SetCursorX(context.FLOAT_0x8 + (f25 - CalcLineWidth(context.PTR_0x4, str - context.PTR_0x4 - len)) / 2);
						}
						else if (IsDrawFlagSet(0x3, 0x2))
						{
							SetCursorX(context.FLOAT_0x8 + (f25 - CalcLineWidth(context.PTR_0x4, str - context.PTR_0x4 - len)));
						}
						else
						{
							f25 = Max<float>(f25, GetCursorX() - context.FLOAT_0x8);
							SetCursorX(context.FLOAT_0x8);
						}
						
						if (r30) r27 = (const T *)strmReader.mStrm;
						r29 = false;
					}
					//8000DB5C
					else if (processRet == 1)
					{
						r29 = false;
					}
					else if (processRet == 2)
					{
						r29 = true;
					}
					else if (processRet == 4)
					{
						break;
					}
					//8000DB84
					strmReader.Set(context.PTR_0x4);
				}
				else
				{
					//8000DB90
					float f27 = GetCursorY();
					if (r30 && r28 != r27)
					{
						float f24 = GetCursorX();
						float f23 = r29 ? FLOAT_0x50 : 0.0f;
						float f2;// = (IsWidthFixed() ? GetFixedWidth() : (mFont->GetCharWidth(r26) * mScale.x));
						
						if (IsWidthFixed())
						{
							f2 = GetFixedWidth();
						}
						else
						{
							float f22 = mScale.x;
							float f0 = mFont->GetCharWidth(r26);
							f2 = f0 * f22;
						}
						
						if (f2 + f23 + (f24 - cursorX) > FLOAT_0x4C)
						{
							strmReader.Set(r28);
							r26 = '\n';
							continue;
						}
					}
					//8000DC2C
					if (r29) MoveCursorX(FLOAT_0x50);
					r29 = true;
					float f22 = mScale.y;
					MoveCursorY(-mFont->GetBaselinePos() * f22);
					CharWriter::Print(r26);
					SetCursorY(f27);
				}
				//8000DC98
				
				if (r30) r28 = (const T *)strmReader.mStrm;
				
				r26 = strmReader.Next();
			}
			//8000DCC8
			float ret = Max<float>(f25, GetCursorX() - context.FLOAT_0x8);
			
			if (IsDrawFlagSet(0x300, 0x100) || IsDrawFlagSet(0x300, 0x200)) SetCursorY(f28);
			else MoveCursorY(f26);
			
			return ret;
		}
		
		template <typename T>
		float TextWriterBase<T>::AdjustCursor(float * pX, float * pY, const T * str, int len)
		{
			float f31 = 0.0f;
			float f2 = 0.0f;
			
			if (!IsDrawFlagSet(0x333, 0x300) && !IsDrawFlagSet(0x333, 0))
			{
				Rect rect;
				
				TextWriterBase<T>(*this).CalcStringRectImpl(&rect, str, len);
				
				f31 = rect.FLOAT_0x0 + rect.FLOAT_0x8;
				f2 = rect.FLOAT_0x4 + rect.FLOAT_0xC;
				
				if (f31 > FLOAT_0x4C) f31 = FLOAT_0x4C;
			}
			
			if (IsDrawFlagSet(0x30, 0x10)) *pX -= f31 / 2;
			else if (IsDrawFlagSet(0x30, 0x20)) *pX -= f31;
			
			if (IsDrawFlagSet(0x300, 0x100)) *pY -= f2 / 2;
			else if (IsDrawFlagSet(0x300, 0x200)) *pY -= f2;
			
			
			if (IsDrawFlagSet(0x3, 0x1)) SetCursorX(*pX + (f31 - CalcLineWidth(str, len)) / 2);
			else if (IsDrawFlagSet(0x3, 0x2)) SetCursorX(*pX + (f31 - CalcLineWidth(str, len)));
			else SetCursorX(*pX);
			
			
			if (IsDrawFlagSet(0x300, 0x300)) SetCursorY(*pY);
			else SetCursorY(*pY + GetFontAscent());
			
			return f31;
		}
		
		template <typename T> T * TextWriterBase<T>::mFormatBuffer;
		template <typename T> TagProcessorBase<T> TextWriterBase<T>::mDefaultTagProcessor;
		template <typename T> u32 TextWriterBase<T>::mFormatBufferSize = 0x100;
		
		template struct TextWriterBase<char>;
		template struct TextWriterBase<wchar_t>;
	}
}
#else
#error This file has yet to be decompiled accurately. Use "ut_TextWriter.s" instead.
#endif