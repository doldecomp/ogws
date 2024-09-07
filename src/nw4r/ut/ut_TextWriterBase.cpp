#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/ut.h>

namespace nw4r {
namespace ut {

template <typename T> T* TextWriterBase<T>::mFormatBuffer;
template <typename T> u32 TextWriterBase<T>::mFormatBufferSize = 0x100;

template <typename T>
TagProcessorBase<T> TextWriterBase<T>::mDefaultTagProcessor;

template <typename T>
TextWriterBase<T>::TextWriterBase()
    : mCharSpace(0.0f),
      mWidthLimit(NW4R_MATH_FLT_MAX),
      mLineSpace(0.0f),
      mTabWidth(4),
      mDrawFlag(0),
      mTagProcessor(&mDefaultTagProcessor) {}

template <typename T> TextWriterBase<T>::~TextWriterBase() {}

template <typename T> f32 TextWriterBase<T>::GetLineHeight() const {
    const Font* pFont = GetFont();
    int lf = pFont != NULL ? pFont->GetLineFeed() : 0;
    return mLineSpace + GetScaleV() * lf;
}

template <typename T>
f32 TextWriterBase<T>::VPrintf(const T* pStr, std::va_list args) {
    T* pBuffer;

    if (mFormatBuffer != NULL) {
        pBuffer = mFormatBuffer;
    } else {
        pBuffer = static_cast<T*>(__alloca(mFormatBufferSize));
    }

    int len = VSNPrintf(pBuffer, mFormatBufferSize, pStr, args);
    return Print(pBuffer, len);
}

template <typename T> f32 TextWriterBase<T>::Print(const T* pStr, int len) {
    TextWriterBase<T> clone(*this);

    f32 width = clone.PrintImpl(pStr, len);
    SetCursor(clone.GetCursorX(), clone.GetCursorY());

    return width;
}

template <typename T>
f32 TextWriterBase<T>::CalcLineWidth(const T* pStr, int len) {
    Rect rect;
    TextWriterBase<T> clone(*this);

    clone.SetCursor(0.0f, 0.0f);
    clone.CalcLineRectImpl(&rect, &pStr, len);

    return rect.GetWidth();
}

template <typename T>
bool TextWriterBase<T>::CalcLineRectImpl(Rect* pRect, const T** ppStr,
                                         int len) {
    const T* pStrBegin = *ppStr;
    const T* pStrEnd = pStrBegin + len;
    bool useLimit = mWidthLimit < NW4R_MATH_FLT_MAX;

    PrintContext<T> context = {this, pStrBegin};

    f32 x = 0.0f;
    bool charSpace = false;
    bool overLimit = false;

    const T* pPrevStream = NULL;
    Rect prevRect;

    CharStrmReader reader = GetFont()->GetCharStrmReader();

    pRect->left = 0.0f;
    pRect->right = 0.0f;
    pRect->top = Min(0.0f, GetLineHeight());
    pRect->bottom = Max(0.0f, GetLineHeight());
    prevRect = *pRect;

    reader.Set(pStrBegin);
    pPrevStream = NULL;

    u16 ch = reader.Next();

    while (static_cast<const T*>(reader.GetCurrentPos()) <= pStrEnd) {
        if (ch < ' ') {
            Rect r(x, 0.0f, 0.0f, 0.0f);
            context.str = static_cast<const T*>(reader.GetCurrentPos());
            context.flags = charSpace ? 0 : PRINTFLAGS_CHARSPACE;
            SetCursorX(x);

            if (useLimit && ch != '\n' && pPrevStream != NULL) {
                PrintContext<T> context2 = context;
                TextWriterBase<T> clone(*this);

                Rect r;
                context2.writer = &clone;
                mTagProcessor->CalcRect(&r, ch, &context2);

                if (r.GetWidth() > 0.0f &&
                    clone.GetCursorX() - context.x > mWidthLimit) {
                    overLimit = true;
                    ch = '\n';
                    reader.Set(pPrevStream);
                    continue;
                }
            }

            Operation oper = mTagProcessor->CalcRect(&r, ch, &context);
            reader.Set(context.str);

            pRect->left = Min(pRect->left, r.left);
            pRect->top = Min(pRect->top, r.top);
            pRect->right = Max(pRect->right, r.right);
            pRect->bottom = Max(pRect->bottom, r.bottom);

            x = GetCursorX();

            if (oper == OPERATION_END_DRAW) {
                *ppStr += len;
                return false;
            }

            if (oper == OPERATION_NO_CHAR_SPACE) {
                charSpace = false;
            } else if (oper == OPERATION_CHAR_SPACE) {
                charSpace = true;
            } else if (oper == OPERATION_NEXT_LINE) {
                break;
            }
        } else {
            f32 dx = 0.0f;

            if (charSpace) {
                dx += GetCharSpace();
            }

            if (IsWidthFixed()) {
                dx += GetFixedWidth();
            } else {
                dx += GetFont()->GetCharWidth(ch) * GetScaleH();
            }

            if (useLimit && pPrevStream != NULL && x + dx > mWidthLimit) {
                overLimit = true;
                ch = '\n';
                reader.Set(pPrevStream);
                continue;
            }

            x += dx;
            pRect->left = Min(pRect->left, x);
            pRect->right = Max(pRect->right, x);

            charSpace = true;
        }

        if (useLimit) {
            pPrevStream = static_cast<const T*>(reader.GetCurrentPos());
        }

        ch = reader.Next();
    }

    *ppStr = static_cast<const T*>(reader.GetCurrentPos());
    return overLimit;
}

template <typename T>
void TextWriterBase<T>::CalcStringRectImpl(Rect* pRect, const T* pStr,
                                           int len) {
    const T* pEnd = pStr + len;
    int remain = len;

    pRect->left = 0.0f;
    pRect->right = 0.0f;
    pRect->top = 0.0f;
    pRect->bottom = 0.0f;

    SetCursor(0.0f, 0.0f);

    do {
        Rect r;
        CalcLineRectImpl(&r, &pStr, remain);
        remain = pEnd - pStr;

        pRect->left = Min(pRect->left, r.left);
        pRect->top = Min(pRect->top, r.top);
        pRect->right = Max(pRect->right, r.right);
        pRect->bottom = Max(pRect->bottom, r.bottom);
    } while (remain > 0);
}

template <typename T> f32 TextWriterBase<T>::PrintImpl(const T* pStr, int len) {
    f32 cursorX = GetCursorX();
    f32 cursorY = GetCursorY();

    bool useLimit = mWidthLimit < NW4R_MATH_FLT_MAX;

    f32 orgCursorX = cursorX;
    f32 orgCursorY = cursorY;

    f32 cursorXAdj = 0.0f;
    f32 cursorYAdj = 0.0f;

    bool charSpace = false;

    const T* pPrevStream = pStr;
    const T* pPrevNewLine = pStr;

    f32 textWidth = AdjustCursor(&cursorX, &cursorY, pStr, len);

    cursorXAdj = orgCursorX - GetCursorX();
    cursorYAdj = orgCursorY - GetCursorY();

    PrintContext<T> context = {this, pStr, cursorX, cursorY};

    CharStrmReader reader = GetFont()->GetCharStrmReader();
    reader.Set(pStr);

    Operation oper;
    u16 ch = reader.Next();

    while (static_cast<const T*>(reader.GetCurrentPos()) - pStr <= len) {
        if (ch < ' ') {
            context.str = static_cast<const T*>(reader.GetCurrentPos());
            context.flags = charSpace ? 0 : PRINTFLAGS_CHARSPACE;

            if (useLimit && ch != '\n' && pPrevStream != pPrevNewLine) {
                PrintContext<T> context2 = context;
                TextWriterBase<T> clone(*this);
                Rect rect;

                context2.writer = &clone;
                oper = mTagProcessor->CalcRect(&rect, ch, &context2);

                if (rect.GetWidth() > 0.0f &&
                    clone.GetCursorX() - context.x > mWidthLimit) {
                    ch = '\n';
                    reader.Set(pPrevStream);
                    continue;
                }
            }

            oper = mTagProcessor->Process(ch, &context);
            if (oper == OPERATION_NEXT_LINE) {
                if (IsDrawFlagSet(0x3, 0x1)) {
                    int remain = len - (context.str - pStr);
                    f32 width = CalcLineWidth(context.str, remain);
                    f32 offset = (textWidth - width) / 2.0f;
                    SetCursorX(context.x + offset);
                } else if (IsDrawFlagSet(0x3, 0x2)) {
                    int remain = len - (context.str - pStr);
                    f32 width = CalcLineWidth(context.str, remain);
                    f32 offset = textWidth - width;
                    SetCursorX(context.x + offset);
                } else {
                    f32 width = GetCursorX() - context.x;
                    textWidth = Max(textWidth, width);
                    SetCursorX(context.x);
                }

                if (useLimit) {
                    pPrevNewLine =
                        static_cast<const T*>(reader.GetCurrentPos());
                }

                charSpace = false;
            } else if (oper == OPERATION_NO_CHAR_SPACE) {
                charSpace = false;
            } else if (oper == OPERATION_CHAR_SPACE) {
                charSpace = true;
            } else if (oper == OPERATION_END_DRAW) {
                break;
            }

            reader.Set(context.str);
        } else {
            f32 baseY = GetCursorY();
            if (useLimit && pPrevStream != pPrevNewLine) {
                f32 baseX = GetCursorX();
                f32 space = charSpace ? GetCharSpace() : 0.0f;

                f32 width = IsWidthFixed()
                                ? GetFixedWidth()
                                : GetFont()->GetCharWidth(ch) * GetScaleH();

                if (baseX - cursorX + space + width > mWidthLimit) {
                    ch = '\n';
                    reader.Set(pPrevStream);
                    continue;
                }
            }

            if (charSpace) {
                MoveCursorX(GetCharSpace());
            }

            charSpace = true;

            f32 adj = -GetFont()->GetBaselinePos() * GetScaleV();
            MoveCursorY(adj);
            CharWriter::Print(ch);
            SetCursorY(baseY);
        }

        if (useLimit) {
            pPrevStream = static_cast<const T*>(reader.GetCurrentPos());
        }

        ch = reader.Next();
    }

    f32 width = GetCursorX() - context.x;
    textWidth = Max(textWidth, width);

    if (IsDrawFlagSet(0x300, 0x100) || IsDrawFlagSet(0x300, 0x200)) {
        SetCursorY(orgCursorY);
    } else {
        MoveCursorY(cursorYAdj);
    }

    return textWidth;
}

template <typename T>
f32 TextWriterBase<T>::AdjustCursor(f32* pX, f32* pY, const T* pStr, int len) {
    f32 textWidth = 0.0f;
    f32 textHeight = 0.0f;

    if (!IsDrawFlagSet(0x333, 0x300) && !IsDrawFlagSet(0x333, 0)) {
        Rect rect;
        CalcStringRect(&rect, pStr, len);

        textWidth = rect.left + rect.right;
        textHeight = rect.top + rect.bottom;

        if (textWidth > mWidthLimit) {
            textWidth = mWidthLimit;
        }
    }

    if (IsDrawFlagSet(0x30, 0x10)) {
        *pX -= textWidth / 2;
    } else if (IsDrawFlagSet(0x30, 0x20)) {
        *pX -= textWidth;
    }

    if (IsDrawFlagSet(0x300, 0x100)) {
        *pY -= textHeight / 2;
    } else if (IsDrawFlagSet(0x300, 0x200)) {
        *pY -= textHeight;
    }

    if (IsDrawFlagSet(0x3, 0x1)) {
        SetCursorX(*pX + (textWidth - CalcLineWidth(pStr, len)) / 2);
    } else if (IsDrawFlagSet(0x3, 0x2)) {
        SetCursorX(*pX + (textWidth - CalcLineWidth(pStr, len)));
    } else {
        SetCursorX(*pX);
    }

    if (IsDrawFlagSet(0x300, 0x300)) {
        SetCursorY(*pY);
    } else {
        SetCursorY(*pY + GetFontAscent());
    }

    return textWidth;
}

template <typename T>
f32 TextWriterBase<T>::CalcStringWidth(const T* pStr, int len) const {
    Rect rect;
    CalcStringRect(&rect, pStr, len);
    return rect.GetWidth();
}

template <typename T>
void TextWriterBase<T>::CalcStringRect(Rect* pRect, const T* pStr,
                                       int len) const {
    TextWriterBase<T> clone(*this);
    clone.CalcStringRectImpl(pRect, pStr, len);
}

template struct TextWriterBase<char>;
template struct TextWriterBase<wchar_t>;

} // namespace ut
} // namespace nw4r
