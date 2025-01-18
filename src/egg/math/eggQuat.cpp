#include "eggQuat.h"
#include "eggMath.h"
#include "eggVector.h"

namespace EGG
{
    void Quatf::setAxisRotation(const Vector3f &axis, f32 angle)
    {
        f32 angleHalf = angle * 0.5f;
        f32 angleCos = Math<f32>::cos(angleHalf);
        f32 angleSin = Math<f32>::sin(angleHalf);

        w = angleCos;
        z = angleSin * axis.z;
        f32 _y = angleSin * axis.y;
        x = angleSin * axis.x;
        y = _y;
    }
}