#ifndef EGG_MATH_MATRIX_H
#define EGG_MATH_MATRIX_H
#include <egg/types_egg.h>

#include <egg/math/eggVector.h>

#include <nw4r/math.h>

namespace EGG {

class Matrix34f : public nw4r::math::MTX34 {
public:
    static Matrix34f ident;

public:
    Matrix34f() {}

    // clang-format off
    Matrix34f(f32 m00, f32 m01, f32 m02, f32 m03,
              f32 m10, f32 m11, f32 m12, f32 m13,
              f32 m20, f32 m21, f32 m22, f32 m23);
    // clang-format on

    void makeZero() {
        _03 = _02 = _01 = _00 = 0.0f;
        _13 = _12 = _11 = _10 = 0.0f;
        _23 = _22 = _21 = _20 = 0.0f;
    }

    Matrix34f& operator=(const Matrix34f& rOther) {
        copyFrom(rOther);
        return *this;
    }

    f32& operator()(int i) {
        return a[i];
    }
    const f32 operator()(int i) const {
        return a[i];
    }

    f32& operator()(int i, int j) {
        return m[i][j];
    }
    const f32 operator()(int i, int j) const {
        return m[i][j];
    }

    void copyFrom(const Matrix34f& rOther) {
        for (int i = 0; i < 3 * 4; i++) {
            (*this)(i) = rOther(i);
        }
    }

    void getBase(int index, Vector3f& rBase) const {
        rBase.x = (*this)(0, index);
        rBase.y = (*this)(1, index);
        rBase.z = (*this)(2, index);
    }
    void setBase(int index, const Vector3f& rBase) {
        (*this)(0, index) = rBase.x;
        (*this)(1, index) = rBase.y;
        (*this)(2, index) = rBase.z;
    }

    void getTranslation(Vector3f& rTrans) const {
        getBase(3, rTrans);
    }
    void setTranslation(const Vector3f& rTrans) {
        setBase(3, rTrans);
    }

    Vector3f rotate(const Vector3f& rVec) const {
        f32 x = _00 * rVec.x + _01 * rVec.y + _02 * rVec.z;
        f32 y = _10 * rVec.x + _11 * rVec.y + _12 * rVec.z;
        f32 z = _20 * rVec.x + _21 * rVec.y + _22 * rVec.z;
        return Vector3f(x, y, z);
    }

    void makeIdentity();

    void makeQ(const Quatf& rQuat);
    void makeS(const Vector3f& rScale);

    void setAxisRotation(const Vector3f& rAxis, f32 angle);
    void loadPosMtx(u32 id);
};

} // namespace EGG

#endif
