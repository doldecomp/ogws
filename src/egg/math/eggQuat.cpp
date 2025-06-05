// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/math.h>

namespace EGG {

void Quatf::set(f32 fw, f32 fx, f32 fy, f32 fz) {
    w = fw;
    v.x = fx;
    v.y = fy;
    v.z = fz;
}

void Quatf::setAxisRotation(const Vector3f& rAxis, f32 angle) {
    f32 half = angle * 0.5f;
    f32 cosa = Math<f32>::cos(half);
    f32 sina = Math<f32>::sin(half);
    set(cosa, sina * rAxis.x, sina * rAxis.y, sina * rAxis.z);
}

} // namespace EGG
