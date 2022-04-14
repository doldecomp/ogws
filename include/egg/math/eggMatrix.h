#ifndef EGG_MATH_MATRIX_H
#define EGG_MATH_MATRIX_H
#include "types_egg.h"
#include "math_types.h"

namespace EGG
{
    struct Matrix33f
    {
        f32& operator()(int i, int j) { return tbl[i][j]; }
        f32 tbl[3][3];
    };

    struct Matrix34f : nw4r::math::MTX34
    {
        Matrix34f() {}
        Matrix34f(f32, f32, f32, f32,
            f32, f32, f32, f32,
            f32, f32, f32, f32);

        void makeZero()
        {
            mEntries.tbl[0][3] = mEntries.tbl[0][2] = mEntries.tbl[0][1] = mEntries.tbl[0][0] = 0.0f;
            mEntries.tbl[1][3] = mEntries.tbl[1][2] = mEntries.tbl[1][1] = mEntries.tbl[1][0] = 0.0f;
            mEntries.tbl[2][3] = mEntries.tbl[2][2] = mEntries.tbl[2][1] = mEntries.tbl[2][0] = 0.0f;
        }

        void makeIdentity();
        void makeQ(const Quatf&);
        void makeS(const Vector3f&);
        void setAxisRotation(const Vector3f &, f32);
        void loadPosMtx(u32);

        typedef float (* MtxRef)[4];
        typedef const float (* MtxRefConst)[4];
        operator MtxRef() { return mEntries.tbl; }
        operator MtxRefConst() const { return mEntries.tbl; }

        f32& operator()(int i, int j) { return mEntries.tbl[i][j]; }

        static Matrix34f ident;
    };
}

#endif