#include <nw4r/ut.h>

namespace nw4r {
namespace ut {

u16 RomFont::mFontEncode = 0xFFFF;

namespace {

inline bool IsCP1252Char(u16 ch) {
    return ch >= 0x20 && ch <= 0xFF;
}

inline bool IsSJISHalfWidthChar(u16 ch) {
    if (ch > 0xFF) {
        return false;
    }

    return (ch >= 0x20 && ch <= 0x7E) || (ch >= 0xA1 && ch <= 0xDF);
}

inline bool IsSJISFullWidthChar(u16 ch) {
    u8 hi = BitExtract<u16>(ch, 8, 8);
    u8 lo = BitExtract<u16>(ch, 0, 8);

    return hi >= 0x81 && hi <= 0x98 && lo >= 0x40 && lo <= 0xFC;
}

} // namespace

RomFont::RomFont() : mFontHeader(NULL), mAlternateChar('?') {
    mDefaultWidths.left = 0;
    mDefaultWidths.glyphWidth = 0;
    mDefaultWidths.charWidth = 0;
}

RomFont::~RomFont() {}

bool RomFont::Load(void* pBuffer) {
    if (mFontHeader != NULL) {
        return false;
    }

    BOOL success = OSInitFont(static_cast<OSFontHeader*>(pBuffer));

    if (success) {
        mFontEncode = OSGetFontEncode();
        mFontHeader = static_cast<OSFontHeader*>(pBuffer);

        mDefaultWidths.left = 0;
        mDefaultWidths.glyphWidth = GetCellWidth();
        mDefaultWidths.charWidth = GetMaxCharWidth();

        InitReaderFunc(GetEncoding());
    }

    return success;
}

u32 RomFont::GetRequireBufferSize() {
    // TODO: How are these calculated?
    switch (OSGetFontEncode()) {
    case OS_FONT_ENCODE_ANSI: {
        return 0x00020120;
    }

    case OS_FONT_ENCODE_SJIS: {
        return 0x00120F00;
    }
    }

    return 0;
}

int RomFont::GetWidth() const {
    return mFontHeader->width;
}

int RomFont::GetHeight() const {
    return GetAscent() + GetDescent();
}

int RomFont::GetAscent() const {
    return mFontHeader->ascent;
}

int RomFont::GetDescent() const {
    return mFontHeader->descent;
}

int RomFont::GetBaselinePos() const {
    return mFontHeader->ascent;
}

int RomFont::GetCellHeight() const {
    return mFontHeader->cellHeight;
}

int RomFont::GetCellWidth() const {
    return mFontHeader->cellWidth;
}

int RomFont::GetMaxCharWidth() const {
    return mFontHeader->width;
}

Font::Type RomFont::GetType() const {
    return TYPE_ROM;
}

GXTexFmt RomFont::GetTextureFormat() const {
    return GX_TF_I4;
}

int RomFont::GetLineFeed() const {
    return mFontHeader->leading;
}

CharWidths RomFont::GetDefaultCharWidths() const {
    return mDefaultWidths;
}

void RomFont::SetDefaultCharWidths(const CharWidths& rWidths) {
    mDefaultWidths = rWidths;
}

bool RomFont::SetAlternateChar(u16 ch) {
    const u16 prev = mAlternateChar;
    mAlternateChar = 0xFFFF;

    u16 undef = HandleUndefinedChar(ch);
    if (undef != 0xFFFF) {
        mAlternateChar = ch;
        return true;
    } else {
        mAlternateChar = prev;
        return false;
    }
}

void RomFont::SetLineFeed(int lf) {
    mFontHeader->leading = lf;
}

int RomFont::GetCharWidth(u16 ch) const {
    u32 width;
    char buffer[CHAR_PTR_BUFFER_SIZE];

    MakeCharPtr(buffer, ch);
    OSGetFontWidth(buffer, &width);

    return width;
}

CharWidths RomFont::GetCharWidths(u16 ch) const {
    int width = GetCharWidth(ch);

    CharWidths widths;
    widths.left = 0;
    widths.glyphWidth = width;
    widths.charWidth = width;

    return widths;
}

void RomFont::GetGlyph(Glyph* pGlyph, u16 ch) const {
    void* pTexture;
    u32 x, y, width;
    char buffer[CHAR_PTR_BUFFER_SIZE];

    MakeCharPtr(buffer, ch);
    OSGetFontTexture(buffer, &pTexture, &x, &y, &width);

    pGlyph->pTexture = pTexture;

    pGlyph->widths.left = 0;
    pGlyph->widths.glyphWidth = width;
    pGlyph->widths.charWidth = width;

    pGlyph->height = mFontHeader->cellHeight;
    pGlyph->texFormat = GX_TF_I4;

    pGlyph->texWidth = mFontHeader->sheetWidth;
    pGlyph->texHeight = mFontHeader->sheetHeight;

    pGlyph->cellX = x;
    pGlyph->cellY = y;
}

FontEncoding RomFont::GetEncoding() const {
    switch (mFontEncode) {
    case OS_FONT_ENCODE_ANSI: {
        return FONT_ENCODING_CP1252;
    }

    case OS_FONT_ENCODE_SJIS: {
        return FONT_ENCODING_SJIS;
    }
    }

    return FONT_ENCODING_CP1252;
}

void RomFont::MakeCharPtr(char* pBuffer, u16 ch) const {
    ch = HandleUndefinedChar(ch);

    if (BitExtract<u16>(ch, 8, 8) == 0) {
        pBuffer[0] = ch & 0x00FF;
        pBuffer[1] = '\0';
    } else {
        pBuffer[0] = BitExtract<u16>(ch, 8, 8);
        pBuffer[1] = ch & 0x00FF;
        pBuffer[2] = '\0';
    }
}

u16 RomFont::HandleUndefinedChar(u16 ch) const {
    bool valid;

    switch (mFontEncode) {
    case OS_FONT_ENCODE_ANSI: {
        valid = IsCP1252Char(ch);
        break;
    }

    case OS_FONT_ENCODE_SJIS: {
        valid = IsSJISHalfWidthChar(ch) || IsSJISFullWidthChar(ch);
        break;
    }
    }

    return valid ? ch : mAlternateChar;
}

} // namespace ut
} // namespace nw4r
