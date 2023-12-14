#ifndef NW4R_UT_TEXT_WRITER_BASE_H
#define NW4R_UT_TEXT_WRITER_BASE_H
#include <nw4r/types_nw4r.h>
#include <nw4r/ut/ut_CharWriter.h>
#include <nw4r/ut/ut_TagProcessorBase.h>

namespace nw4r {
namespace ut {

template <typename T> class TextWriterBase : public CharWriter {
public:
    TextWriterBase();
    ~TextWriterBase();

    int GetTabWidth() const { return mTabWidth; }

    bool IsDrawFlagSet(u32 mask, u32 flag) const {
        return (mDrawFlag & mask) == flag;
    }

    f32 GetLineHeight() const;
    int VSNPrintf(T* buffer, u32 count, const T* fmt, va_list args);
    f32 VPrintf(const T* str, va_list args);
    f32 Print(const T* str, int len);
    f32 CalcLineWidth(const T* str, int len);
    bool CalcLineRectImpl(Rect* rect, const T** str,
                          int len) DECOMP_DONT_INLINE;
    void CalcStringRectImpl(Rect* rect, const T* str, int len);
    f32 PrintImpl(const T* str, int len) DECOMP_DONT_INLINE;
    f32 AdjustCursor(f32* x1, f32* y1, const T* str, int len);

    f32 CalcStringWidth(const T* str, int len) const;
    void CalcStringRect(Rect* rect, const T* str, int len) const;

private:
    f32 mWidthLimit;                    // at 0x4C
    f32 mCharSpace;                     // at 0x50
    f32 mLineSpace;                     // at 0x54
    int mTabWidth;                      // at 0x58
    u32 mDrawFlag;                      // at 0x5C
    TagProcessorBase<T>* mTagProcessor; // at 0x60

    static TagProcessorBase<T> mDefaultTagProcessor;
    static T* mFormatBuffer;
    static u32 mFormatBufferSize;
};

} // namespace ut
} // namespace nw4r

#endif
