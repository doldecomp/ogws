#include "eggMatrix.h"
#include "eggVector.h"
#include "eggQuat.h"
#include <revolution/GX.h>

namespace EGG
{

    // This weak destructor likely belongs to Quatf due to the BBA map
    // and that this is referenced in the stack unwinding instructions of setAxisRotation.
    namespace
    {
        void INSTANTIATE_WEAK_EGGMATRIX()
        {
            Quatf q;
            q.~Quatf();
        }
    }

    Matrix34f::Matrix34f(f32 _00, f32 _01, f32 _02, f32 _03,
        f32 _10, f32 _11, f32 _12, f32 _13,
        f32 _20, f32 _21, f32 _22, f32 _23)
    {
        tbl[0][0] = _00; tbl[0][1] = _01; tbl[0][2] = _02; tbl[0][3] = _03;
        tbl[1][0] = _10; tbl[1][1] = _11; tbl[1][2] = _12; tbl[1][3] = _13;
        tbl[2][0] = _20; tbl[2][1] = _21; tbl[2][2] = _22; tbl[2][3] = _23;
    }

    void Matrix34f::makeIdentity()
    {
        // Force float order in sdata2
        1.0f;
        2.0f;
        0.0f;

        makeZero();
        tbl[2][2] = 1.0f;
        tbl[1][1] = 1.0f;
        tbl[0][0] = 1.0f;
    }

   /**
    * Converts a quaternion to a rotation matrix (3x4)
    * [1 - 2Y^2 - 2Z^2] [   2XY - 2ZW   ] [   2XZ + 2YW   ] [   UNUSED   ]
    * [   2XY + 2ZW   ] [1 - 2X^2 - 2Z^2] [   2YZ - 2XW   ] [   UNUSED   ]
    * [   2XZ - 2YW   ] [   2YZ + 2XW   ] [1 - 2X^2 - 2Y^2] [   UNUSED   ]
    * 
    * Implementation from SEAD decompilation: https://github.com/open-ead/sead/blob/master/include/math/seadMatrixCalcCommon.hpp#L1179
    */
    void Matrix34f::makeQ(const Quatf& quat)
    {
        f32 yy = 2.0f * quat.y * quat.y;
        f32 zz = 2.0f * quat.z * quat.z;
        f32 xx = 2.0f * quat.x * quat.x;
        f32 xy = 2.0f * quat.x * quat.y;
        f32 xz = 2.0f * quat.x * quat.z;
        f32 yz = 2.0f * quat.y * quat.z;
        f32 wz = 2.0f * quat.w * quat.z;
        f32 wx = 2.0f * quat.w * quat.x;
        f32 wy = 2.0f * quat.w * quat.y;

        tbl[0][0] = 1.0f - yy - zz;
        tbl[0][1] = xy - wz;
        tbl[0][2] = xz + wy;

        tbl[1][0] = xy + wz;
        tbl[1][1] = 1.0f - xx - zz;
        tbl[1][2] = yz - wx;

        tbl[2][0] = xz - wy;
        tbl[2][1] = yz + wx;
        tbl[2][2] = 1 - xx - yy;

        tbl[0][3] = 0.0f;
        tbl[1][3] = 0.0f;
        tbl[2][3] = 0.0f;
    }

    void Matrix34f::makeS(const Vector3f& vec)
    {
        tbl[0][0] = vec.x;
        tbl[0][1] = 0.0f;
        tbl[0][2] = 0.0f;

        tbl[1][0] = 0.0f;
        tbl[1][1] = vec.y;
        tbl[1][2] = 0.0f;

        tbl[2][0] = 0.0f;
        tbl[2][1] = 0.0f;
        tbl[2][2] = vec.z;

        tbl[0][3] = 0.0f;
        tbl[1][3] = 0.0f;
        tbl[2][3] = 0.0f;
    }

    void Matrix34f::setAxisRotation(const Vector3f & vec, f32 f1)
    {
        Quatf q;
        
        q.setAxisRotation(vec, f1);
        makeQ(q);
    }

    void Matrix34f::loadPosMtx(u32 i)
    {
        GXLoadPosMtxImm(tbl, i);
    }

    Matrix34f Matrix34f::ident(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f
    );
}