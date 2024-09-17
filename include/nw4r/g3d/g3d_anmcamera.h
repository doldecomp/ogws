#ifndef NW4R_G3D_ANMCAMERA_H
#define NW4R_G3D_ANMCAMERA_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_resanmcamera.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

namespace nw4r {
namespace g3d {

struct CameraAnmResult : ResAnmCameraDataTypedef {
    u32 flags;                 // at 0x0
    GXProjectionType projType; // at 0x4
    math::VEC3 pos;            // at 0x8
    f32 aspect;                // at 0x14
    f32 near;                  // at 0x18
    f32 far;                   // at 0x1C

    union {
        struct {
            math::_VEC3 rot; // at 0x20
        } rotate;

        struct {
            math::_VEC3 aim; // at 0x20
            f32 twist;       // at 0x2C
        } aim;
    };

    union {
        f32 perspFovy;   // at 0x30
        f32 orthoHeight; // at 0x30
    };
};

} // namespace g3d
} // namespace nw4r

#endif
