#ifndef NW4R_UT_TEXT_WRITER_BASE_H
#define NW4R_UT_TEXT_WRITER_BASE_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ut/ut_CharWriter.h>
#include <nw4r/ut/ut_TagProcessorBase.h>

#include <nw4r/math.h>

#include <cstdio>
#include <cwchar>

namespace nw4r {
namespace ut {

template <typename T> class TextWriterBase : public CharWriter {
public:
    static T* GetBuffer() {
        return mFormatBuffer;
    }
    static T* SetBuffer(T* pBuffer, u32 size) {
        T* old = mFormatBuffer;
        mFormatBuffer = pBuffer;
        mFormatBufferSize = size;
        return old;
    }

    static u32 GetBufferSize() {
        return mFormatBufferSize;
    }

    TextWriterBase();
    ~TextWriterBase();

    f32 GetWidthLimit() const {
        return mWidthLimit;
    }
    void SetWidthLimit(f32 limit) {
        mWidthLimit = limit;
    }
    void ResetWidthLimit() {
        mWidthLimit = NW4R_MATH_FLT_MAX;
    }

    f32 GetCharSpace() const {
        return mCharSpace;
    }
    void SetCharSpace(f32 space) {
        mCharSpace = space;
    }

    f32 GetLineSpace() const {
        return mLineSpace;
    }
    void SetLineSpace(f32 space) {
        mLineSpace = space;
    }

    int GetTabWidth() const {
        return mTabWidth;
    }
    void SetTabWidth(int width) {
        mTabWidth = width;
    }

    void SetDrawFlag(u32 flag) {
        mDrawFlag = flag;
    }
    bool IsDrawFlagSet(u32 mask, u32 flag) const {
        return (mDrawFlag & mask) == flag;
    }

    TagProcessorBase<T>* GetTagProcessor() const {
        return mTagProcessor;
    }
    void SetTagProcessor(TagProcessorBase<T>* pProcessor) {
        mTagProcessor = pProcessor;
    }
    void ResetTagProcessor() {
        mTagProcessor = &mDefaultTagProcessor;
    }

    f32 GetLineHeight() const;

    f32 CalcLineWidth(const T* pStr, int len);
    f32 CalcStringWidth(const T* pStr, int len) const;
    void CalcStringRect(Rect* pRect, const T* pStr, int len) const;

    int VSNPrintf(T* buffer, u32 count, const T* fmt, std::va_list args);
    f32 VPrintf(const T* pStr, std::va_list args);
    f32 Print(const T* pStr, int len);

    bool CalcLineRectImpl(Rect* pRect, const T** ppStr, int len);
    void CalcStringRectImpl(Rect* pRect, const T* pStr, int len);

    f32 PrintImpl(const T* pStr, int len);
    f32 AdjustCursor(f32* pX, f32* pY, const T* pStr, int len);

private:
    f32 mWidthLimit;                    // at 0x4C
    f32 mCharSpace;                     // at 0x50
    f32 mLineSpace;                     // at 0x54
    int mTabWidth;                      // at 0x58
    u32 mDrawFlag;                      // at 0x5C
    TagProcessorBase<T>* mTagProcessor; // at 0x60

    static T* mFormatBuffer;
    static u32 mFormatBufferSize;
    static TagProcessorBase<T> mDefaultTagProcessor;
};

template <>
inline int TextWriterBase<char>::VSNPrintf(char* pBuffer, u32 count,
                                           const char* pFmt,
                                           std::va_list args) {
    return std::vsnprintf(pBuffer, count, pFmt, args);
}

template <>
inline int TextWriterBase<wchar_t>::VSNPrintf(wchar_t* pBuffer, u32 count,
                                              const wchar_t* pFmt,
                                              std::va_list args) {
    return std::vswprintf(pBuffer, count, pFmt, args);
}

} // namespace ut
} // namespace nw4r

#endif
