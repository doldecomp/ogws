#include <revolution/OS.h>
#include <revolution/TPL.h>

#define TPL_VERSION 0x0020AF30

void TPLBind(TPLPalette* pal) {
    u16 i;

    // clang-format off
#line 25
    OS_ASSERT(pal->version == TPL_VERSION, "invalid version number for texture palette");
    // clang-format on

    pal->descriptors = (TPLDescriptor*)((char*)pal->descriptors + (u32)pal);

    for (i = 0; i < pal->numImages; i++) {
        if (pal->descriptors[i].texHeader != NULL) {
            // Convert header offset into pointer
            pal->descriptors[i].texHeader =
                (TPLHeader*)((char*)pal + (u32)pal->descriptors[i].texHeader);

            if (!pal->descriptors[i].texHeader->unpacked) {
                // Convert data offset into pointer
                pal->descriptors[i].texHeader->data =
                    (char*)pal + (u32)pal->descriptors[i].texHeader->data;

                pal->descriptors[i].texHeader->unpacked = TRUE;
            }
        }

        if (pal->descriptors[i].clutHeader != NULL) {
            // Convert header offset into pointer
            pal->descriptors[i].clutHeader =
                (TPLClutHeader*)((char*)pal +
                                 (u32)pal->descriptors[i].clutHeader);

            if (!pal->descriptors[i].clutHeader->unpacked) {
                // Convert data offset into pointer
                pal->descriptors[i].clutHeader->data =
                    (char*)pal + (u32)pal->descriptors[i].clutHeader->data;

                pal->descriptors[i].clutHeader->unpacked = TRUE;
            }
        }
    }
}

TPLDescriptor* TPLGet(TPLPalette* pal, u32 id) {
    return &pal->descriptors[id % pal->numImages];
}
