// TODO(kiwi) REMOVE AFTER REFACTOR
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

DECOMP_FORCELITERAL(eggVector_cpp, 1.0f);

f32 Vector3f::normalise() {
    f32 mag = length();
    if (mag > 0.0f) {
        f32 invMag = 1.0f / mag;
        x *= invMag;
        y *= invMag;
        z *= invMag;
    }

    return mag;
}

} // namespace EGG
