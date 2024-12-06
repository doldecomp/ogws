#include <nw4r/ut.h>

namespace nw4r {
namespace ut {

template <typename T> TagProcessorBase<T>::TagProcessorBase() {}

template <typename T> TagProcessorBase<T>::~TagProcessorBase() {}

template <typename T>
Operation TagProcessorBase<T>::Process(u16 ch, PrintContext<T>* pCtx) {
    switch (ch) {
    case '\n': {
        ProcessLinefeed(pCtx);
        return OPERATION_NEXT_LINE;
    }

    case '\t': {
        ProcessTab(pCtx);
        return OPERATION_NO_CHAR_SPACE;
    }
    }

    return OPERATION_DEFAULT;
}

template <typename T>
Operation TagProcessorBase<T>::CalcRect(Rect* pRect, u16 ch,
                                        PrintContext<T>* pCtx) {

    switch (ch) {
    case '\n': {
        const TextWriterBase<T>& rWriter = *pCtx->writer;
        pRect->right = rWriter.GetCursorX();
        pRect->top = rWriter.GetCursorY();
        ProcessLinefeed(pCtx);
        pRect->left = rWriter.GetCursorX();
        pRect->bottom = rWriter.GetCursorY() + pCtx->writer->GetFontHeight();
        pRect->Normalize();
        return OPERATION_NEXT_LINE;
    }

    case '\t': {
        const TextWriterBase<T>& rWriter = *pCtx->writer;
        pRect->left = rWriter.GetCursorX();
        ProcessTab(pCtx);
        pRect->right = rWriter.GetCursorX();
        pRect->top = rWriter.GetCursorY();
        pRect->bottom = pRect->top + rWriter.GetFontHeight();
        pRect->Normalize();
        return OPERATION_NO_CHAR_SPACE;
    }
    }

    return OPERATION_DEFAULT;
}

template <typename T>
void TagProcessorBase<T>::ProcessTab(PrintContext<T>* pCtx) {
    TextWriterBase<T>& rWriter = *pCtx->writer;

    int tabWidth = rWriter.GetTabWidth();
    if (tabWidth <= 0) {
        return;
    }

    f32 charWidth = rWriter.IsWidthFixed() ? rWriter.GetFixedWidth()
                                           : rWriter.GetFontWidth();

    f32 dx = rWriter.GetCursorX() - pCtx->x;
    f32 tabPixel = tabWidth * charWidth;
    int numTab = static_cast<int>(dx / tabPixel) + 1;
    f32 x = pCtx->x + (tabPixel * numTab);

    rWriter.SetCursorX(x);
}

template <typename T>
void TagProcessorBase<T>::ProcessLinefeed(PrintContext<T>* pCtx) {
    TextWriterBase<T>& rWriter = *pCtx->writer;

    f32 x = pCtx->x;
    f32 y = rWriter.GetCursorY() + rWriter.GetLineHeight();

    rWriter.SetCursorX(x);
    rWriter.SetCursorY(y);
}

template class TagProcessorBase<char>;
template class TagProcessorBase<wchar_t>;

} // namespace ut
} // namespace nw4r
