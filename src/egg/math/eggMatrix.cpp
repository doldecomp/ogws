#include "eggMatrix.h"
#include "eggVector.h"
#include "eggQuat.h"
#include <RevoSDK/GX/GXTransform.h>

namespace EGG
{
    Matrix34f::Matrix34f(f32 _00, f32 _01, f32 _02, f32 _03,
        f32 _10, f32 _11, f32 _12, f32 _13,
        f32 _20, f32 _21, f32 _22, f32 _23)
    {
        tbl[0][0] = _00; tbl[0][1] = _01; tbl[0][2] = _02; tbl[0][3] = _03;
        tbl[1][0] = _00; tbl[1][1] = _01; tbl[1][2] = _02; tbl[1][3] = _03;
        tbl[2][0] = _00; tbl[2][1] = _01; tbl[2][2] = _02; tbl[2][3] = _03;
    }

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
        f32 x2, y2, z2, w2;
        f32 xx2, xy2, xz2, xw2, yy2, yz2, yw2, zz2, zw2, ww2;
        f32 _00, _01, _02;
        f32 _10, _11, _12;
        f32 _20, _21, _22;

        x2 = rQuat.x * 2.0f;
        y2 = rQuat.y * 2.0f;
        z2 = rQuat.z * 2.0f;
        w2 = rQuat.w * 2.0f;

        xx2 = x2 * rQuat.x;
        yy2 = y2 * rQuat.y;
        zz2 = z2 * rQuat.z;
        ww2 = w2 * rQuat.w;

        xy2 = x2 * rQuat.y;
        xz2 = x2 * rQuat.z;
        xw2 = x2 * rQuat.w;

        yz2 = y2 * rQuat.z;
        yw2 = y2 * rQuat.w;

        zw2 = z2 * rQuat.w;

        _00 = 1.0f - yy2 - zz2;
        _01 = xy2 - zw2;
        _02 = xz2 + yw2;
        tbl[0][3] = 0.0f;

        _10 = xy2 + zw2;
        _11 = 1.0f - xx2 - zz2;
        _12 = yz2 - xw2;
        tbl[1][3] = 0.0f;

        _20 = xz2 - yw2;
        _21 = yz2 + xw2;
        _22 = 1.0f - xx2 - yy2;
        tbl[2][3] = 0.0f;

        tbl[0][0] = _00;
        tbl[0][1] = _01;
        tbl[0][2] = _02;

        tbl[1][0] = _10;
        tbl[1][1] = _11;
        tbl[1][2] = _12;

        tbl[2][0] = _20;
        tbl[2][1] = _21;
        tbl[2][2] = _22;
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

    Matrix34f Matrix34f::ident = Matrix34f(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f
    );
}