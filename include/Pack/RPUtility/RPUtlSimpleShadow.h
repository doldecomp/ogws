#ifndef RP_UTILITY_SIMPLE_SHADOW_H
#define RP_UTILITY_SIMPLE_SHADOW_H
#include <egg/gfx.h>

class RPUtlSimpleShadow {

private:
    EGG::ResTIMG* mpTexture; // at 0x0
    f32 mWidth;              // at 0x4
    f32 mHeight;             // at 0x8
};

#endif
