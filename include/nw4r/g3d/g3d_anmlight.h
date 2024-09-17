#ifndef NW4R_G3D_ANMLIGHT_H
#define NW4R_G3D_ANMLIGHT_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_resanmlight.h>

#include <nw4r/math.h>
#include <nw4r/ut.h>

#include <revolution/GX.h>

namespace nw4r {
namespace g3d {

struct LightAnmResult : ResAnmLightDataTypedef {
    u32 specIdx;           // at 0x0
    u32 flags;             // at 0x4
    math::VEC3 pos;        // at 0x8
    math::VEC3 aim;        // at 0x14
    ut::Color color;       // at 0x20
    GXDistAttnFn distFunc; // at 0x24
    f32 refDistance;       // at 0x28
    f32 refBrightness;     // at 0x2C
    GXSpotFn spotFunc;     // at 0x30
    f32 cutoff;            // at 0x34
    ut::Color specColor;   // at 0x38
    f32 shininess;         // at 0x3C
};

} // namespace g3d
} // namespace nw4r

#endif
