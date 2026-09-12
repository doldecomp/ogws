#ifndef RP_UTILITY_SHADOW_DRAWER_H
#define RP_UTILITY_SHADOW_DRAWER_H

#include <nw4r/math.h>
#include <nw4r/ut.h>

#include <revolution/GX.h>

class RPUtlShadowDrawer {

public:
    void initMtx() const;
    void drawShadow();

private:
    nw4r::math::MTX34 mLocalMtx; // at 0x0
    u32 unk30;
    nw4r::ut::Color mColor; // at 0x34

private:
    static nw4r::math::MTX34 sCameraMtx;
};

#endif
