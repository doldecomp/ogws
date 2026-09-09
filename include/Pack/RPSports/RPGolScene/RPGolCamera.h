#ifndef RP_SPORTS_GOL_CAMERA_H
#define RP_SPORTS_GOL_CAMERA_H

#include <Pack/RPGraphics.h>
#include <Pack/RPSingleton.h>

#include <nw4r/math.h>


class RPGolCamera {
public:
    RP_SINGLETON_DECL(RPGolCamera);

private:
    u32 unk4;
    nw4r::math::MTX34 mMtx; // at 0x8
    nw4r::math::VEC3 mVec;  // at 0x38; tentative
    RPGrpCamera* mpCamera;  // at 0x44
};

#endif
