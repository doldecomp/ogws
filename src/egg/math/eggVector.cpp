// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/math.h>

namespace EGG {

const Vector2f Vector2f::zero(0.0f, 0.0f);
const Vector2f Vector2f::ex(1.0f, 0.0f);
const Vector2f Vector2f::ey(0.0f, 1.0f);

const Vector3f Vector3f::zero(0.0f, 0.0f, 0.0f);
const Vector3f Vector3f::ex(1.0f, 0.0f, 0.0f);
const Vector3f Vector3f::ey(0.0f, 1.0f, 0.0f);
const Vector3f Vector3f::ez(0.0f, 0.0f, 1.0f);

f32 Vector3f::normalise() {
    // Force sdata2 ordering (1.0f, 0.0f)
    1.0f;

    f32 mag = length();

    if (mag > 0.0f) {
        f32 inv_mag = 1.0f / mag;
        x *= inv_mag;
        y *= inv_mag;
        z *= inv_mag;
    }

    return mag;
}

} // namespace EGG
