// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/math.h>

#include <revolution/GX.h>

namespace EGG {

// clang-format off
Matrix34f Matrix34f::ident(1.0f, 0.0f, 0.0f, 0.0f,
                           0.0f, 1.0f, 0.0f, 0.0f,
                           0.0f, 0.0f, 1.0f, 0.0f);
// clang-format on

DECOMP_FORCEACTIVE_DTOR(eggMatrix_cpp,
                        Quatf);

DECOMP_FORCELITERAL(eggMatrix_cpp_1,
                    1.0f, 2.0f, 0.0f);

Matrix34f::Matrix34f(f32 m00, f32 m01, f32 m02, f32 m03, f32 m10, f32 m11,
                     f32 m12, f32 m13, f32 m20, f32 m21, f32 m22, f32 m23) {

    _00 = m00;
    _01 = m01;
    _02 = m02;
    _03 = m03;
    _10 = m10;
    _11 = m11;
    _12 = m12;
    _13 = m13;
    _20 = m20;
    _21 = m21;
    _22 = m22;
    _23 = m23;
}

void Matrix34f::makeIdentity() {
    makeZero();
    _00 = _11 = _22 = 1.0f;
}

void Matrix34f::makeQ(const Quatf& rQuat) {
    f32 yy = 2.0f * rQuat.v.y * rQuat.v.y;
    f32 zz = 2.0f * rQuat.v.z * rQuat.v.z;
    f32 xx = 2.0f * rQuat.v.x * rQuat.v.x;
    f32 xy = 2.0f * rQuat.v.x * rQuat.v.y;
    f32 xz = 2.0f * rQuat.v.x * rQuat.v.z;
    f32 yz = 2.0f * rQuat.v.y * rQuat.v.z;
    f32 wz = 2.0f * rQuat.w * rQuat.v.z;
    f32 wx = 2.0f * rQuat.w * rQuat.v.x;
    f32 wy = 2.0f * rQuat.w * rQuat.v.y;

    _00 = 1.0f - yy - zz;
    _01 = xy - wz;
    _02 = xz + wy;

    _10 = xy + wz;
    _11 = 1.0f - xx - zz;
    _12 = yz - wx;

    _20 = xz - wy;
    _21 = yz + wx;
    _22 = 1.0f - xx - yy;

    _03 = 0.0f;
    _13 = 0.0f;
    _23 = 0.0f;
}

void Matrix34f::makeS(const Vector3f& rScale) {
    _00 = rScale.x;
    _01 = 0.0f;
    _02 = 0.0f;

    _10 = 0.0f;
    _11 = rScale.y;
    _12 = 0.0f;

    _20 = 0.0f;
    _21 = 0.0f;
    _22 = rScale.z;

    _03 = 0.0f;
    _13 = 0.0f;
    _23 = 0.0f;
}

void Matrix34f::setAxisRotation(const Vector3f& rAxis, f32 angle) {
    Quatf q;
    q.setAxisRotation(rAxis, angle);
    makeQ(q);
}

void Matrix34f::loadPosMtx(u32 id) {
    GXLoadPosMtxImm(m, id);
}

} // namespace EGG
