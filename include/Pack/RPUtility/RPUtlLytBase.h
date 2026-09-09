#ifndef RP_UTILITY_LYT_BASE_H
#define RP_UTILITY_LYT_BASE_H

#include <nw4r/math.h>

#include <revolution/GX.h>

class RPUtlLytBase {
    static f32 one;
    static f32 zero;

public:
    void drawLine(GXColor pColor, u16 pVerts, u8 pWidth);
};

#endif
