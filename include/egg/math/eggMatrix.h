#ifndef EGG_MATH_MATRIX_H
#define EGG_MATH_MATRIX_H
#include "types_egg.h"

namespace EGG
{
    struct Matrix33f
    {
        f32& operator()(int i, int j) { return tbl[i][j]; }

        f32 tbl[3][3];
    };

    struct Matrix34f
    {
        Matrix34f() {}
        Matrix34f(f32, f32, f32, f32,
            f32, f32, f32, f32,
            f32, f32, f32, f32);

        void makeZero()
        {
            tbl[0][3] = tbl[0][2] = tbl[0][1] = tbl[0][0] = 0.0f;
            tbl[1][3] = tbl[1][2] = tbl[1][1] = tbl[1][0] = 0.0f;
            tbl[2][3] = tbl[2][2] = tbl[2][1] = tbl[2][0] = 0.0f;
        }

        void makeIdentity();
        void makeQ(const Quatf&);
        void makeS(const Vector3f&);
        void setAxisRotation(const Vector3f &, f32);
        void loadPosMtx(u32);

        f32& operator()(int i, int j) { return tbl[i][j]; }

        f32 tbl[3][4];

        static Matrix34f ident;
    };
}

#endif