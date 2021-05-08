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
        // Unused slots
        tbl[0][3] = 0.0f;
        tbl[1][3] = 0.0f;
        tbl[2][3] = 0.0f;

        f32 y2 = (2.0f * rQuat.y);
        f32 x2 = (2.0f * rQuat.x);
        f32 z2 = (2.0f * rQuat.z);
        f32 w2 = (2.0f * rQuat.w);

        f32 yy2 = y2 * rQuat.y;
        f32 xx2 = x2 * rQuat.x;
        f32 zz2 = z2 * rQuat.z;

        f32 xy2 = x2 * rQuat.y;
        f32 zw2 = w2 * rQuat.z;
        f32 xz2 = x2 * rQuat.z;
        f32 yw2 = w2 * rQuat.y;
        f32 yz2 = y2 * rQuat.z;
        f32 xw2 = w2 * rQuat.x;

        tbl[0][0] = 1.0f - yy2 - zz2;
        tbl[0][1] = xy2 - zw2;

        tbl[1][0] = xy2 + zw2;
        tbl[1][1] = 1.0f - xx2 - zz2;
        tbl[2][2] = 1.0f - xx2 - yy2;
        
        tbl[0][2] = xz2 - yw2;
        tbl[1][2] = yz2 - xw2;
        tbl[2][0] = xz2 - yw2;
        tbl[2][1] = yz2 + xw2;
    }
    #else
    #error This file has yet to be decompiled accurately. Use "eggMatrix.s" instead.
    #endif

    void Matrix34f::makeS(const Vector3f& rVec)
    {
        tbl[0][0] = rVec.x, tbl[0][1] = 0.0f, tbl[0][2] = 0.0f, tbl[0][3] = 0.0f;
        tbl[1][0] = rVec.y, tbl[1][1] = 0.0f, tbl[1][2] = 0.0f, tbl[1][3] = 0.0f;
        tbl[2][0] = rVec.z, tbl[2][1] = 0.0f, tbl[2][2] = 0.0f, tbl[2][3] = 0.0f;
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