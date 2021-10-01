#ifndef EGG_GFX_G3D_UTILITY_H
#define EGG_GFX_G3D_UTILITY_H
#include "types_egg.h"
#include "types_nw4r.h"

namespace EGG
{
    struct G3DUtility
    {
        static u8 sManualProjectionMapMode;
        static MEMAllocator *sAllocator;
        static char *sTempMem;
        static u32 sTempMemIndex;
        static u32 sTempMemSize;
    };
}

#endif