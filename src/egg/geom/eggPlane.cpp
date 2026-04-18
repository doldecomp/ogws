#include <egg/geom.h>

namespace EGG {

DECOMP_FORCEACTIVE(eggPlane_cpp, Vector3f::multScalar);

Vector3f Plane3f::project(const Vector3f& rVec) {
    f32 s = normal.dot(rVec) - depth;
    Vector3f work(rVec);

    // TODO(kiwi) how is multScalar being called?
    Vector3f n(normal * s);
    work -= n;

    return work;
}

} // namespace EGG
