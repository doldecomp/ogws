#ifndef EGG_MATH_QUAT_H
#define EGG_MATH_QUAT_H
#include "types_egg.h"

namespace EGG
{
    struct Quat
    {
        UNKTYPE setAxisRotation(const Vector3f &, f32);

        f32 x, y, z, w;
    };
}

#endif