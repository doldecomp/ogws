#ifndef EGG_GFX_RES_TIMG_H
#define EGG_GFX_RES_TIMG_H
#include <egg/types_egg.h>

namespace EGG {

enum JUTTransparency {
    JUT_TRANSPARENCY_DISABLE,
    JUT_TRANSPARENCY_ENABLE,
};

struct ResTIMG {
    u8 format;           // at 0x0
    u8 transparency;     // at 0x1
    u16 width;           // at 0x2
    u16 height;          // at 0x4
    u8 wrapS;            // at 0x6
    u8 wrapT;            // at 0x7
    u8 tlutName;         // at 0x8
    u8 tlutFormat;       // at 0x9
    u16 paletteEntryNum; // at 0xA
    s32 paletteOffset;   // at 0xC
    u8 mipMap;           // at 0x10
    u8 edgeLODEnable;    // at 0x11
    u8 biasClampEnable;  // at 0x12
    u8 anisotropy;       // at 0x13
    u8 minFilter;        // at 0x14
    u8 magFilter;        // at 0x15
    s8 minLOD;           // at 0x16
    s8 maxLOD;           // at 0x17
    u8 mipMapLevel;      // at 0x18
    u8 BYTE_0x19;
    s16 LODBias;     // at 0x1A
    s32 imageOffset; // at 0x1C
};

} // namespace EGG

#endif
