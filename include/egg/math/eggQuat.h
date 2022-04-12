#ifndef EGG_MATH_QUAT_H
#define EGG_MATH_QUAT_H
#include "types_egg.h"
#include "eggVector.h"

namespace EGG
{
    struct Quatf
    {
        Quatf() {}
        Quatf(f32 _w, Vector3f vec) :
            x(vec.x),
            y(vec.y),
            z(vec.z),
            w(_w)
            {}

        ~Quatf() {}

        void setAxisRotation(const Vector3f &, f32);

        f32 x, y, z, w;
    };
}

#endif