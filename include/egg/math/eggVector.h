#ifndef EGG_MATH_VECTOR_H
#define EGG_MATH_VECTOR_H
#include "types_egg.h"
#include "eggMath.h"

namespace EGG
{
    struct Vector2f
    {
        Vector2f() {}
        Vector2f(f32 _x, f32 _y) : x(_x), y(_y) {}
        ~Vector2f();

        f32 x, y;

        static const Vector2f zero;
        static const Vector2f ex;
        static const Vector2f ey;
    };

    struct Vector3f
    {
        Vector3f() {}
        Vector3f(f32 _x, f32 _y, f32 _z) : x(_x), y(_y), z(_z) {}
        ~Vector3f();

        f32 normalise();

        f32 length() const
        {
            return Math<f32>::sqrt(squaredLength());
        }

        f32 squaredLength() const
        {
            return x * x + y * y + z * z;
        }

        f32 x, y, z;

        static const Vector3f zero;
        static const Vector3f ex;
        static const Vector3f ey;
        static const Vector3f ez;
    };
}

#endif