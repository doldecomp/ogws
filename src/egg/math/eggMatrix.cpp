#include "eggMatrix.h"
#include "eggVector.h"
#include "eggQuat.h"
#include <RevoSDK/GX/GXTransform.h>

namespace EGG
{
    Matrix34f::~Matrix34f()
    {

    }

    void Matrix34f::makeIdentity()
    {
        makeZero();
        tbl[2][2] = 1.0f;
        tbl[1][1] = 1.0f;
        tbl[0][0] = 1.0f;
    }

    #ifdef __DECOMP_NON_MATCHING
    /*
        Converts a quaternion to a rotation matrix (3x4)

        [1 - 2Y^2 - 2Z^2] [   2XY - 2ZW   ] [   2XZ + 2YW   ] [   UNUSED   ]
        [   2XY + 2ZW   ] [1 - 2X^2 - 2Z^2] [   2YZ - 2XW   ] [   UNUSED   ]
        [   2XZ - 2YW   ] [   2YZ + 2XW   ] [1 - 2X^2 - 2Y^2] [   UNUSED   ]
    */
    void Matrix34f::makeQ(const Quatf& rQuat)
    {
        // 800A2270
        f32 x2 = 2.0f * rQuat.x; // f9
        f32 w2 = 2.0f * rQuat.w; // f6
        f32 y2 = 2.0f * rQuat.y; // f3
        f32 z2 = 2.0f * rQuat.z; // f5

        // 800A2290
        f32 xx2 = x2 * rQuat.x; // f11
        f32 ww2 = w2 * rQuat.w; // f4
        tbl[0][3] = 0.0f;
        f32 yy2 = y2 * rQuat.y; // f3
        f32 xx2_m1 = 1.0f - xx2; // f1
        tbl[1][3] = 0.0f;
        f32 wx2 = w2 * rQuat.x; // f12
        tbl[2][3] = 0.0f;

        // 800A22B0
        f32 zy2 = z2 * rQuat.y; // f13
        f32 ww2_m1 = 1.0f - ww2; // f2
        f32 xx2_m1_myy2 = xx2_m1 - yy2; // f0
        f32 wx2_mzy2 = wx2 - zy2; // f4
        f32 ww2_m1_myy2 = ww2_m1 - yy2; // f1

        // 800A22C4
        f32 wx2_pzy2 = wx2 + zy2; // f3
        tbl[0][0] = xx2_m1_myy2;
        f32 ww2_m1_mxx2 = ww2_m1 - xx2; // f0
        f32 wy2 = w2 * rQuat.y; // f2
        tbl[0][1] = wx2_mzy2;
        f32 zx2 = z2 * rQuat.x; // f6
        tbl[1][0] = wx2_pzy2;

        // 800A22E0
        f32 xy2 = x2 * rQuat.y; // f4
        f32 zw2 = z2 * rQuat.w; // f5
        f32 wy2_pzx2 = wy2 + zx2; // f6
        tbl[1][1] = ww2_m1_myy2;
        f32 wy2_mzx2 = wy2 - zx2; // f1
        f32 xy2_mzw2 = xy2 - zw2; // f2
        tbl[2][2] = ww2_m1_mxx2;

        // 800A22FC
        f32 xy2_pzw2 = xy2 + zw2; // f0
        tbl[1][2] = wx2_pzy2;
        tbl[2][0] = wy2_mzx2;
        tbl[2][1] = xy2_pzw2;
    }
    #else
    #error This file has yet to be decompiled accurately. Use "eggMatrix.s" instead.
    #endif

    void Matrix34f::makeS(const Vector3f& rVec)
    {
        tbl[0][0] = rVec.x;
        tbl[0][1] = 0.0f;
        tbl[0][2] = 0.0f;
        tbl[0][3] = 0.0f;

        tbl[1][0] = rVec.y;
        tbl[1][1] = 0.0f;
        tbl[1][2] = 0.0f;
        tbl[1][3] = 0.0f;

        tbl[2][0] = rVec.z;
        tbl[2][1] = 0.0f;
        tbl[2][2] = 0.0f;
        tbl[2][3] = 0.0f;
    }

    void Matrix34f::setAxisRotation(const Vector3f & rVec, f32 f1)
    {
        Quatf q;
        q.setAxisRotation(rVec, f1);
        makeQ(q);
    }

    void Matrix34f::loadPosMtx(u32 i)
    {
        GXLoadPosMtxImm(tbl, i);
    }

    // TO-DO: Static members initialized here
}