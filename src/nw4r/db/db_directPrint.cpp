#include <nw4r/db.h>

#include <revolution/GX.h>
#include <revolution/OS.h>
#include <revolution/VI.h>

#include <cstdio>
#include <cstring>

#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480

#define TAB_SIZE 4

namespace nw4r {
namespace db {

// Forward declarations
static void DrawStringToXfb_(int x, int y, const char* pStr, bool turnOver,
                             bool backErase);
static const char* DrawStringLineToXfb_(int x, int y, const char* str,
                                        int width);
static void DrawCharToXfb_(int x, int y, int code);

struct FrameBufferInfo {
    u8* frameMemory; // at 0x0
    u32 frameSize;   // at 0x4
    u16 frameWidth;  // at 0x8
    u16 frameHeight; // at 0xA
    u16 frameRow;    // at 0xC
    u16 reserved;    // at 0xE
};

static FrameBufferInfo sFrameBufferInfo;

struct YUVColorInfo {
    GXColor colorRGBA; // at 0x0
    u16 colorY256;     // at 0x4
    u16 colorU;        // at 0x6
    u16 colorU2;       // at 0x8
    u16 colorU4;       // at 0xA
    u16 colorV;        // at 0xC
    u16 colorV2;       // at 0xE
    u16 colorV4;       // at 0x10
    u16 reserved;      // at 0x12
};

static YUVColorInfo sFrameBufferColor;

static BOOL sInitialized = FALSE;

static const u8 sAsciiTable[] = {
    // clang-format off
            /* 0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07  0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F */
    /* 0x00 */ 0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0xFD, 0xFE, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A,
    /* 0x10 */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    /* 0x20 */ 0xFF, 0x29, 0x64, 0x65, 0x66, 0x2B, 0x67, 0x68, 0x25, 0x26, 0x69, 0x2A, 0x6A, 0x27, 0x2C, 0x6B,
    /* 0x30 */ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x24, 0x6C, 0x6D, 0x6E, 0x6F, 0x28,
    /* 0x40 */ 0x70, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
    /* 0x50 */ 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x71, 0x72, 0x73, 0x74, 0x75,
    /* 0x60 */ 0xFF, 0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B,
    /* 0x70 */ 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x76, 0x77, 0x78, 0x79, 0x7A,
    // clang-format on
};

static const u32 sFontData[] = {
    0x70871C30, 0x8988A250, 0x88808290, 0x88830C90, 0x888402F8, 0x88882210,
    0x71CF9C10, 0xF9CF9C70, 0x8208A288, 0xF200A288, 0x0BC11C78, 0x0A222208,
    0x8A222208, 0x71C21C70, 0x23C738F8, 0x5228A480, 0x8A282280, 0x8BC822F0,
    0xFA282280, 0x8A28A480, 0x8BC738F8, 0xF9C89C08, 0x82288808, 0x82088808,
    0xF2EF8808, 0x82288888, 0x82288888, 0x81C89C70, 0x8A08A270, 0x920DA288,
    0xA20AB288, 0xC20AAA88, 0xA208A688, 0x9208A288, 0x8BE8A270, 0xF1CF1CF8,
    0x8A28A220, 0x8A28A020, 0xF22F1C20, 0x82AA0220, 0x82492220, 0x81A89C20,
    0x8A28A288, 0x8A28A288, 0x8A289488, 0x8A2A8850, 0x894A9420, 0x894AA220,
    0x70852220, 0xF8011000, 0x08020800, 0x10840400, 0x20040470, 0x40840400,
    0x80020800, 0xF8011000, 0x70800000, 0x88822200, 0x08820400, 0x108F8800,
    0x20821000, 0x00022200, 0x20800020, 0x00000000,
};

static const u32 sFontData2[] = {
    0x51421820, 0x53E7A420, 0x014A2C40, 0x01471000, 0x0142AA00, 0x03EAA400,
    0x01471A78, 0x00000000, 0x50008010, 0x20010820, 0xF8020040, 0x20420820,
    0x50441010, 0x00880000, 0x00070E00, 0x01088840, 0x78898820, 0x004A8810,
    0x788A8810, 0x01098808, 0x00040E04, 0x70800620, 0x11400820, 0x12200820,
    0x10001020, 0x10000820, 0x100F8820, 0x70000620, 0x60070000, 0x110F82A0,
    0x12AA8AE0, 0x084F92A0, 0x100FBE1C, 0x10089008, 0x60070808, 0x00000000,
    0x02000200, 0x7A078270, 0x8BC81E88, 0x8A2822F8, 0x9A282280, 0x6BC79E78,
    0x30000000, 0x48080810, 0x41E80000, 0x422F1830, 0xFBE88810, 0x40288890,
    0x43C89C60, 0x81000000, 0x81000000, 0x990F3C70, 0xA10AA288, 0xE10AA288,
    0xA10AA288, 0x98CAA270, 0x00000000, 0x00000020, 0xF1EF1E20, 0x8A28A0F8,
    0x8A281C20, 0xF1E80220, 0x80283C38, 0x00000000, 0x00000000, 0x8A28B688,
    0x8A2A8888, 0x8A2A8878, 0x894A8808, 0x788536F0, 0x00000000, 0x00000000,
    0xF8000000, 0x10000000, 0x20000000, 0x40000000, 0xF8000000,
};

static inline int GetDotWidth_() {
    return sFrameBufferInfo.frameWidth < 400 ? 1 : 2;
}

static inline int GetDotHeight_() {
    return sFrameBufferInfo.frameHeight < 300 ? 1 : 2;
}

static inline int StrLineWidth_(const char* pStr) {
    int len = 0;
    char c;

    NW4R_NULL_ASSERT(LINE(304), pStr);

    while (true) {
        c = *pStr++;

        if (c == '\0' || c == '\n') {
            return len;
        }

        if (c == '\t') {
            len = ROUND_DOWN(len + 4, 4);
        } else {
            len++;
        }
    }
}

void DirectPrint_Init() {
    if (sInitialized) {
        return;
    }

    DirectPrint_ChangeXfb(NULL, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    DirectPrint_SetColor(255, 255, 255);

    sInitialized = TRUE;
}

bool DirectPrint_IsActive() {
    return sInitialized && sFrameBufferInfo.frameMemory != NULL;
}

void DirectPrint_EraseXfb(int x, int y, int width, int height) {
    if (sFrameBufferInfo.frameMemory == NULL) {
        return;
    }

    if (GetDotWidth_() == 2) {
        x *= 2;
        width *= 2;
    }

    int x2 = x + width;

    x = x >= 0 ? x : 0;
    x2 = x2 <= sFrameBufferInfo.frameWidth ? x2 : sFrameBufferInfo.frameWidth;

    width = x2 - x;

    if (GetDotHeight_() == 2) {
        y *= 2;
        height *= 2;
    }

    int y2 = y + height;

    y = y >= 0 ? y : 0;
    y2 = y2 <= sFrameBufferInfo.frameHeight ? y2 : sFrameBufferInfo.frameHeight;

    height = y2 - y;

    // Character location in framebuffer
    u16* pPixel = reinterpret_cast<u16*>(sFrameBufferInfo.frameMemory) +
                  sFrameBufferInfo.frameRow * y + x;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            *pPixel++ = 0x1080;
        }

        pPixel += sFrameBufferInfo.frameRow - width;
    }
}

void DirectPrint_ChangeXfb(void* pXfb, u16 width, u16 height) {
    sFrameBufferInfo.frameMemory = static_cast<u8*>(pXfb);
    sFrameBufferInfo.frameWidth = width;
    sFrameBufferInfo.frameHeight = height;

    sFrameBufferInfo.frameRow = ROUND_UP(static_cast<u16>(width), 16);
    sFrameBufferInfo.frameSize =
        sFrameBufferInfo.frameRow * sFrameBufferInfo.frameHeight * sizeof(u16);
}

void DirectPrint_ChangeXfb(void* pXfb) {
    sFrameBufferInfo.frameMemory = static_cast<u8*>(pXfb);
}

void DirectPrint_StoreCache() {
    DCStoreRange(sFrameBufferInfo.frameMemory, sFrameBufferInfo.frameSize);
}

void DirectPrint_Printf(int x, int y, const char* pFmt, ...) {
    if (sFrameBufferInfo.frameMemory != NULL) {
        std::va_list list;
        va_start(list, pFmt);

        detail::DirectPrint_DrawStringToXfb(x, y, pFmt, list, true, true);

        va_end(list);
    }
}

void DirectPrint_Printf(int x, int y, bool turnOver, const char* pFmt, ...) {
    if (sFrameBufferInfo.frameMemory != NULL) {
        std::va_list list;
        va_start(list, pFmt);

        detail::DirectPrint_DrawStringToXfb(x, y, pFmt, list, turnOver, true);

        va_end(list);
    }
}

void DirectPrint_DrawString(int x, int y, const char* pFmt, ...) {
    if (sFrameBufferInfo.frameMemory != NULL) {
        std::va_list list;
        va_start(list, pFmt);

        detail::DirectPrint_DrawStringToXfb(x, y, pFmt, list, true, false);

        va_end(list);
    }
}

void DirectPrint_DrawString(int x, int y, bool turnOver, const char* pFmt,
                            ...) {
    if (sFrameBufferInfo.frameMemory != NULL) {
        std::va_list list;
        va_start(list, pFmt);

        detail::DirectPrint_DrawStringToXfb(x, y, pFmt, list, turnOver, false);

        va_end(list);
    }
}

void DirectPrint_SetColor(GXColor color) {
    DirectPrint_SetColor(color.r, color.g, color.b);
}

void DirectPrint_SetColor(u8 r, u8 g, u8 b) {
    int y = 0.257f * static_cast<int>(r) + //
            0.504f * static_cast<int>(g) + //
            0.098f * static_cast<int>(b) + //
            16.0f;

    int u = -0.148f * static_cast<int>(r) - //
            0.291f * static_cast<int>(g) +  //
            0.439f * static_cast<int>(b) +  //
            128.0f;

    int v = 0.439f * static_cast<int>(r) - //
            0.368f * static_cast<int>(g) - //
            0.071f * static_cast<int>(b) + //
            128.0f;

    sFrameBufferColor.colorRGBA.r = r;
    sFrameBufferColor.colorRGBA.g = g;
    sFrameBufferColor.colorRGBA.b = b;
    sFrameBufferColor.colorRGBA.a = 255;

    sFrameBufferColor.colorY256 = y * 256;

    sFrameBufferColor.colorU = u;
    sFrameBufferColor.colorU2 = u / 2;
    sFrameBufferColor.colorU4 = u / 4;

    sFrameBufferColor.colorV = v;
    sFrameBufferColor.colorV2 = v / 2;
    sFrameBufferColor.colorV4 = v / 4;
}

GXColor DirectPrint_GetColor() {
    return sFrameBufferColor.colorRGBA;
}

namespace detail {

void DirectPrint_DrawStringToXfb(int x, int y, const char* pFmt,
                                 std::va_list list, bool turnOver,
                                 bool backErase) {
    NW4R_NULL_ASSERT(LINE(645), sFrameBufferInfo.frameMemory);

    char buffer[256];
    int length = std::vsnprintf(buffer, sizeof(buffer), pFmt, list);

    int start = x; // unused
    if (length > 0) {
        DrawStringToXfb_(x, y, buffer, turnOver, backErase);
    }
}

} // namespace detail

static void DrawStringToXfb_(int x, int y, const char* pStr, bool turnOver,
                             bool backErase) {
    int x1;
    int width, fbWidth;

    x1 = x;
    fbWidth = sFrameBufferInfo.frameWidth / GetDotWidth_();

    while (*pStr != '\0') {
        if (backErase) {
            int len = StrLineWidth_(pStr);
            DirectPrint_EraseXfb(x - 6, y - 3,
                                 (len + 2) * NW4R_DB_FONT_CHAR_WIDTH, 13);
        }

        width = (fbWidth - x) / NW4R_DB_FONT_CHAR_WIDTH;
        pStr = DrawStringLineToXfb_(x, y, pStr, width);
        y += NW4R_DB_FONT_LEADING;

        if (*pStr == '\n') {
            pStr++;
            x = x1;
        } else if (*pStr != '\0') {
            pStr++;

            if (!turnOver) {
                pStr = std::strchr(pStr, '\n');
                if (pStr == NULL) {
                    break;
                }

                pStr++;
                x = x1;
            } else {
                x = 0;
            }
        }
    }
}

static const char* DrawStringLineToXfb_(int x, int y, const char* str,
                                        int width) {
    char ch;
    int code;
    int count = 0;

    NW4R_NULL_ASSERT(LINE(743), str);
    NW4R_ASSERT(LINE(744), width > 0);

    while ((ch = *str) != '\0') {
        // Line or string has ended, stop drawing
        if (ch == '\n' || ch == '\0') {
            return str;
        }

        // Convert to font code
        code = sAsciiTable[ch & 0x7F];

        // Tab character
        if (code == 0xFD) {
            int tabSize = TAB_SIZE - (count & (TAB_SIZE - 1));
            x += tabSize * NW4R_DB_FONT_CHAR_WIDTH;
            count += tabSize;
        } else {
            // Non-tab character
            if (code != 0xFF) {
                DrawCharToXfb_(x, y, code);
            }

            // 0xFF is treated as whitespace
            x += NW4R_DB_FONT_CHAR_WIDTH;
            count++;
        }

        // Stop at max line width
        if (count >= width) {
            // Skip over newline if it comes next.
            // It wouldn't take up view space anyways.
            if (str[1] == '\n') {
                str++;
            }

            return str;
        }

        str++;
    }

    return str;
}

static void DrawCharToXfb_(int x, int y, int code) {
    static u32 twiceBit[] = {0b0000, 0b0011, 0b1100, 0b1111};

    // Convert to font-relative code
    int ncode = code >= 100 ? code - 100 : code;

    int fontW = ncode % 5 * NW4R_DB_FONT_CHAR_WIDTH;
    int fontH = ncode / 5 * NW4R_DB_FONT_CHAR_HEIGHT;
    const u32* pFontLine = code < 100 ? &sFontData[fontH] : &sFontData2[fontH];

    int dotW = GetDotWidth_();
    int dotH = GetDotHeight_();

    // Character location in framebuffer
    u16* pPixel = reinterpret_cast<u16*>(sFrameBufferInfo.frameMemory) +
                  sFrameBufferInfo.frameRow * y * dotH + x * dotW;

    if (y < 0 || x < 0) {
        return;
    }

    if (sFrameBufferInfo.frameWidth <= dotW * (x + NW4R_DB_FONT_CHAR_WIDTH) ||
        sFrameBufferInfo.frameHeight <= dotH * (y + NW4R_DB_FONT_CHAR_HEIGHT)) {
        return;
    }

    for (int countY = 0; countY < NW4R_DB_FONT_CHAR_HEIGHT; countY++) {
        u32 fontBits = *pFontLine++ << fontW;

        if (dotW == 1) {
            fontBits = (fontBits & 0xFC000000) >> 1;
        } else {
            fontBits = ((twiceBit[(fontBits >> 26) & 3]) |
                        (twiceBit[(fontBits >> 28) & 3] << 4) |
                        (twiceBit[fontBits >> 30] << 8))
                       << 19;
        }

        for (int countX = 0; countX < dotW * NW4R_DB_FONT_CHAR_WIDTH;
             countX += 2) {
            u16 color;

            // clang-format off
            color = ((fontBits & 0x40000000) ? sFrameBufferColor.colorY256 : 0x00) |
                    ((fontBits & 0x80000000) ? sFrameBufferColor.colorU4   : 0x20) +
                    ((fontBits & 0x40000000) ? sFrameBufferColor.colorU2   : 0x40) +
                    ((fontBits & 0x20000000) ? sFrameBufferColor.colorU4   : 0x20);
            // clang-format on

            *pPixel = color;
            if (dotH > 1) {
                pPixel[sFrameBufferInfo.frameRow] = color;
            }

            pPixel++;

            // clang-format off
            color = ((fontBits & 0x20000000) ? sFrameBufferColor.colorY256 : 0x00) |
                    ((fontBits & 0x40000000) ? sFrameBufferColor.colorV4   : 0x20) +
                    ((fontBits & 0x20000000) ? sFrameBufferColor.colorV2   : 0x40) +
                    ((fontBits & 0x10000000) ? sFrameBufferColor.colorV4   : 0x20);
            // clang-format on

            *pPixel = color;
            if (dotH > 1) {
                pPixel[sFrameBufferInfo.frameRow] = color;
            }

            pPixel++;
            fontBits <<= 2;
        }

        pPixel += (sFrameBufferInfo.frameRow * dotH) -
                  (dotW * NW4R_DB_FONT_CHAR_WIDTH);
    }
}

namespace detail {

static void WaitVIRetrace_() {
    BOOL enabled = OSEnableInterrupts();
    u32 count = VIGetRetraceCount();

    while (count == VIGetRetraceCount()) {
        ;
    }

    OSRestoreInterrupts(enabled);
}

static void* CreateFB_(const GXRenderModeObj* pRenderMode) {
    u32 arenaHi = reinterpret_cast<u32>(OSGetArenaHi());

    u32 size = static_cast<u16>(ROUND_UP(pRenderMode->fbWidth & 0xFFFF, 16)) *
               pRenderMode->xfbHeight * sizeof(u16);

    u32 frameBuf = ROUND_DOWN(arenaHi - size, 32);

    VIConfigure(pRenderMode);
    VISetNextFrameBuffer(reinterpret_cast<void*>(frameBuf));
    return reinterpret_cast<void*>(frameBuf);
}

void* DirectPrint_SetupFB(const GXRenderModeObj* pRenderMode) {
    DirectPrint_Init();

    void* pXfb = VIGetCurrentFrameBuffer();
    if (pXfb == NULL) {
        if (pRenderMode == NULL) {
            switch (VIGetTvFormat()) {
            case VI_TVFORMAT_NTSC: {
                pRenderMode = &GXNtsc480IntDf;
                break;
            }

            case VI_TVFORMAT_PAL: {
                pRenderMode = &GXPal528IntDf;
                break;
            }

            case VI_TVFORMAT_EURGB60: {
                pRenderMode = &GXEurgb60Hz480IntDf;
                break;
            }

            case VI_TVFORMAT_MPAL: {
                pRenderMode = &GXMpal480IntDf;
                break;
            }

            default: {
                break;
            }
            }
        }

        pXfb = CreateFB_(pRenderMode);
    }

    VISetBlack(FALSE);
    VIFlush();
    WaitVIRetrace_();

    if (pRenderMode != NULL) {
        DirectPrint_ChangeXfb(pXfb, pRenderMode->fbWidth,
                              pRenderMode->xfbHeight);
    } else {
        DirectPrint_ChangeXfb(pXfb);
    }

    return pXfb;
}

} // namespace detail
} // namespace db
} // namespace nw4r
