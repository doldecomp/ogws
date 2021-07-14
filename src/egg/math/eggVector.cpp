#pragma fp_contract on

#include "eggMath.h"
#include "eggVector.h"

namespace EGG
{
    f32 Vector3f::normalise()
    {
        // Force sdata2 ordering (1.0f, 0.0f)
        1.0f;

        f32 mag = length();

        if (mag > 0.0f)
        {
            f32 inv_mag = 1.0f / mag;
            x *= inv_mag;
            y *= inv_mag;
            z *= inv_mag;
        }

        return mag;
    }

    Vector2f Vector2f::zero = Vector2f(0.0f, 0.0f);
    Vector2f Vector2f::ex = Vector2f(1.0f, 0.0f);
    Vector2f Vector2f::ey = Vector2f(0.0f, 1.0f);

    Vector3f Vector3f::zero = Vector3f(0.0f, 0.0f, 0.0f);
    Vector3f Vector3f::ex = Vector3f(1.0f, 0.0f, 0.0f);
    Vector3f Vector3f::ey = Vector3f(0.0f, 1.0f, 0.0f);
    Vector3f Vector3f::ez = Vector3f(0.0f, 0.0f, 1.0f);
}