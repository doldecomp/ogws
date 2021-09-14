#ifndef EGG_GFX_SCREEN_H
#define EGG_GFX_SCREEN_H
#include "types_egg.h"

namespace EGG
{
    struct eggScreen // : public eggFrustum
    {
        char UNK_0x0[0x18];
        f32 mNearZ; // at 0x18
        f32 mFarZ; // at 0x1C
    };
}

#endif