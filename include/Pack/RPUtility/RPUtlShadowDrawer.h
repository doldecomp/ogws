#ifndef RP_UTILITY_SHADOW_DRAWER_H
#define RP_UTILITY_SHADOW_DRAWER_H
#include <Pack/RPUtility/RPUtlSimpleShadow.h>

class RPUtlShadowDrawer {
    friend class RPUtlSimpleShadow;

public:
    void drawShadow(RPUtlSimpleShadow* simpShad);

private:
    static nw4r::math::MTX34 mMtx;
};

#endif
