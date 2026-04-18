#ifndef EGG_GEOM_PLANE_H
#define EGG_GEOM_PLANE_H
#include <egg/types_egg.h>

#include <egg/math.h>

namespace EGG {

class Plane3f {
public:
    Plane3f() {}
    Plane3f(const Vector3f& rNormal) : normal(rNormal), depth(0.0f) {}
    Plane3f(const Vector3f& rNormal, f32 depth)
        : normal(rNormal), depth(depth) {}
    ~Plane3f() {}

    Vector3f project(const Vector3f& rVec);

private:
    Vector3f normal; // at 0x0
    f32 depth;       // at 0x10
};

} // namespace EGG

#endif
