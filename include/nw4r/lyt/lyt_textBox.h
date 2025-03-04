#ifndef NW4R_LYT_TEXTBOX_H
#define NW4R_LYT_TEXTBOX_H
#include <nw4r/types_nw4r.h>

#include <nw4r/lyt/lyt_common.h>
#include <nw4r/lyt/lyt_pane.h>
#include <nw4r/lyt/lyt_types.h>

#include <nw4r/ut.h>

namespace nw4r {
namespace lyt {

// Forward declarations
struct ResBlockSet;

/******************************************************************************
 *
 * TextColor
 *
 ******************************************************************************/
enum TextColor {
    TEXTCOLOR_TOP,
    TEXTCOLOR_BOTTOM,

    TEXTCOLOR_MAX
};

namespace res {

/******************************************************************************
 *
 * TXT1 binary layout
 *
 ******************************************************************************/
struct TextBox : Pane {
    static const u32 SIGNATURE = 'txt1';

    u16 textBufBytes;             // at 0x4C
    u16 textStrBytes;             // at 0x4E
    u16 materialIdx;              // at 0x50
    u16 fontIdx;                  // at 0x52
    u8 textPosition;              // at 0x54
    u8 textAlignment;             // at 0x55
    u8 PADDING_0x56[0x58 - 0x56]; // at 0x56
    u32 textStrOffset;            // at 0x58
    u32 textCols[TEXTCOLOR_MAX];  // at 0x5C
    Size fontSize;                // at 0x64
    f32 charSpace;                // at 0x6C
    f32 lineSpace;                // at 0x70
};

} // namespace res

/******************************************************************************
 *
 * TextBox
 *
 ******************************************************************************/
class TextBox : public Pane {
public:
    NW4R_UT_RTTI_DECL(TextBox);

public:
    TextBox(const res::TextBox* pRes, const ResBlockSet& rBlockSet);
    virtual ~TextBox(); // at 0x8

    virtual void DrawSelf(const DrawInfo& rInfo); // at 0x18

    virtual ut::Color GetVtxColor(u32 idx) const;       // at 0x24
    virtual void SetVtxColor(u32 idx, ut::Color color); // at 0x28

    virtual u8 GetVtxColorElement(u32 idx) const;       // at 0x34
    virtual void SetVtxColorElement(u32 idx, u8 value); // at 0x38

    virtual void AllocStringBuffer(u16 len); // at 0x64
    virtual void FreeStringBuffer();         // at 0x68
    u16 GetStringBufferLength() const;

    virtual u16 SetString(const wchar_t* pStr, u16 pos);          // at 0x6C
    virtual u16 SetString(const wchar_t* pStr, u16 pos, u16 len); // at 0x70

    ut::Rect GetTextDrawRect(const DrawInfo& rInfo) const;
    ut::Rect GetTextDrawRect(ut::WideTextWriter* pWriter) const;

    const wchar_t* GetString() const {
        return mTextBuf;
    }
    const wchar_t* GetStringBuffer() const {
        return mTextBuf;
    }

    const ut::Font* GetFont() const;
    void SetFont(const ut::Font* pFont);

    ut::Color GetTextColor(u32 idx) const {
        return mTextColors[idx];
    }
    void SetTextColor(u32 idx, ut::Color color) {
        mTextColors[idx] = color;
    }

    const Size& GetFontSize() const {
        return mFontSize;
    }
    void SetFontSize(const Size& rFontSize) {
        mFontSize = rFontSize;
    }

    f32 GetLineSpace() const {
        return mLineSpace;
    }
    void SetLineSpace(f32 space) {
        mLineSpace = space;
    }

    f32 GetCharSpace() const {
        return mCharSpace;
    }
    void SetCharSpace(f32 space) {
        mCharSpace = space;
    }

    ut::WideTagProcessor* GetTagProcessor() const {
        return mpTagProcessor;
    }
    void SetTagProcessor(ut::WideTagProcessor* pProcessor) {
        mpTagProcessor = pProcessor;
    }

    u8 GetTextPositionH() const {
        return detail::GetHorizontalPosition(mTextPosition);
    }
    void SetTextPositionH(u8 value) {
        detail::SetHorizontalPosition(&mTextPosition, value);
    }

    u8 GetTextPositionV() const {
        return detail::GetVerticalPosition(mTextPosition);
    }
    void SetTextPositionV(u8 value) {
        detail::SetVerticalPosition(&mTextPosition, value);
    }

    f32 GetTextMagH() const;
    f32 GetTextMagV() const;

    u32 MakeDrawFlag() const;

protected:
    wchar_t* mTextBuf;                    // at 0xD4
    ut::Color mTextColors[TEXTCOLOR_MAX]; // at 0xD8

    const ut::Font* mpFont; // at 0xE0
    Size mFontSize;         // at 0xE4
    f32 mLineSpace;         // at 0xEC
    f32 mCharSpace;         // at 0xF0

    ut::WideTagProcessor* mpTagProcessor; // at 0xF4
    u16 mTextBufBytes;                    // at 0xF8
    u16 mTextLen;                         // at 0xFA
    u8 mTextPosition;                     // at 0xFC

    struct {
        u8 bAllocFont : 1;
    } mBits; // at 0xFD

private:
    void Init(u16 len);
};

} // namespace lyt
} // namespace nw4r

#endif
