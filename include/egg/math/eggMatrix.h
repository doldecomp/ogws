#ifndef EGG_MATH_MATRIX_H
#define EGG_MATH_MATRIX_H
#include <egg/types_egg.h>

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

    f32& operator()(int i) {
        return a[i];
    }
    const f32& operator()(int i) const {
        return a[i];
    }

    f32& operator()(int i, int j) {
        return m[i][j];
    }
    const f32& operator()(int i, int j) const {
        return m[i][j];
    }

    void copyFrom(const Matrix34f& rOther) {
        for (int i = 0; i < ARRAY_SIZE(a); i++) {
            (*this)(i) = rOther(i);
        }
    }

    /*
    getBase__Q23EGG9Matrix34fCFiRQ23EGG8Vector3f
    setBase__Q23EGG9Matrix34fFiRCQ23EGG8Vector3f

    getTranslation__Q23EGG9Matrix34fCFRQ23EGG8Vector3f
    setTranslation__Q23EGG9Matrix34fFRCQ23EGG8Vector3f

    multVectorTo__Q23EGG9Matrix34fCFRCQ23EGG8Vector3fRQ23EGG8Vector3f

    concat__Q23EGG9Matrix34fCFRCQ23EGG9Matrix34fRQ23EGG9Matrix34f
    rotate__Q23EGG9Matrix34fCFRCQ23EGG8Vector3f
    */

    void makeIdentity();

    void makeQ(const Quatf& rQuat);
    void makeS(const Vector3f& rScale);

    void setAxisRotation(const Vector3f& rAxis, f32 angle);
    void loadPosMtx(u32 id);
};

} // namespace EGG

#endif
