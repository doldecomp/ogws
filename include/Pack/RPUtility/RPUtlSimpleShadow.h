#ifndef RP_UTILITY_SIMPLE_SHADOW_H
#define RP_UTILITY_SIMPLE_SHADOW_H
#include <nw4r/math.h>

class RPUtlSimpleShadow {
    friend class RPUtlShadowDrawer;

private:
    const nw4r::math::MTX34 mMtx;
    char unk30[4];
    GXColor mColor;
};

#endif
