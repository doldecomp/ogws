#ifndef RVL_SDK_TPL_H
#define RVL_SDK_TPL_H
#include <types.h>

#include <revolution/GX.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct TPLHeader {
    u16 height;            // at 0x0
    u16 width;             // at 0x2
    u32 format;            // at 0x4
    char* data;            // at 0x8
    GXTexWrapMode wrapS;   // at 0xC
    GXTexWrapMode wrapT;   // at 0x10
    GXTexFilter minFilter; // at 0x14
    GXTexFilter magFilter; // at 0x18
    f32 LODBias;           // at 0x1C
    u8 edgeLODEnable;      // at 0x20
    u8 minLOD;             // at 0x21
    u8 maxLOD;             // at 0x22
    u8 unpacked;           // at 0x23
} TPLHeader;

typedef struct TPLClutHeader {
    u16 numEntries;   // at 0x0
    u8 unpacked;      // at 0x1
    u8 pad8;          // at 0x2
    GXTlutFmt format; // at 0x4
    char* data;       // at 0x8
} TPLClutHeader;

typedef struct TPLDescriptor {
    TPLHeader* textureHeader;  // at 0x0
    TPLClutHeader* CLUTHeader; // at 0x4
} TPLDescriptor;

typedef struct TPLPalette {
    u32 versionNumber;              // at 0x0
    u32 numDescriptors;             // at 0x4
    TPLDescriptor* descriptorArray; // at 0x8
} TPLPalette;

void TPLBind(TPLPalette* pal);
TPLDescriptor* TPLGet(TPLPalette* pal, u32 id);

#ifdef __cplusplus
}
#endif
#endif
