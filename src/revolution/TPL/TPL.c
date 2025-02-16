#include <revolution/OS.h>
#include <revolution/TPL.h>

#define TPL_VERSION 2142000

void TPLBind(TPLPalette* pal) {
    u16 i;

    // clang-format off
#line 25
    OS_ASSERT(pal->versionNumber == TPL_VERSION, "invalid version number for texture palette");
    // clang-format on

    pal->descriptorArray =
        (TPLDescriptor*)((char*)pal->descriptorArray + (u32)pal);

    for (i = 0; i < pal->numDescriptors; i++) {
        if (pal->descriptorArray[i].textureHeader != NULL) {
            // Convert header offset into pointer
            pal->descriptorArray[i].textureHeader =
                (TPLHeader*)((char*)pal +
                             (u32)pal->descriptorArray[i].textureHeader);

            if (!pal->descriptorArray[i].textureHeader->unpacked) {
                // Convert data offset into pointer
                pal->descriptorArray[i].textureHeader->data =
                    (char*)pal +
                    (u32)pal->descriptorArray[i].textureHeader->data;

                pal->descriptorArray[i].textureHeader->unpacked = TRUE;
            }
        }

        if (pal->descriptorArray[i].CLUTHeader != NULL) {
            // Convert header offset into pointer
            pal->descriptorArray[i].CLUTHeader =
                (TPLClutHeader*)((char*)pal +
                                 (u32)pal->descriptorArray[i].CLUTHeader);

            if (!pal->descriptorArray[i].CLUTHeader->unpacked) {
                // Convert data offset into pointer
                pal->descriptorArray[i].CLUTHeader->data =
                    (char*)pal + (u32)pal->descriptorArray[i].CLUTHeader->data;

                pal->descriptorArray[i].CLUTHeader->unpacked = TRUE;
            }
        }
    }
}

TPLDescriptor* TPLGet(TPLPalette* pal, u32 id) {
    return &pal->descriptorArray[id % pal->numDescriptors];
}
