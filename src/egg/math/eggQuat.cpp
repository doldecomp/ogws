#include "eggQuat.h"
#include "eggMath.h"
#include "eggVector.h"

namespace EGG
{
    UNKTYPE Quatf::setAxisRotation(const Vector3f &rVec, f32 f1)
    {
        f32 f1Half = f1 * 0.5f;
        f32 rotCos = Math<f32>::cos(f1Half);
        f32 rotSin = Math<f32>::sin(f1Half);

        w = rotCos;
        z = rotSin * rVec.z;
        f32 _y = rotSin * rVec.y;
        x = rotSin * rVec.x;
        y = _y;
    }
}