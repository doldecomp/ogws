#ifndef NW4R_G3D_ANMFOG_H
#define NW4R_G3D_ANMFOG_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ut.h>

#include <revolution/GX.h>

namespace nw4r {
namespace g3d {

struct FogAnmResult {
    GXFogType type;  // at 0x0
    f32 startz;      // at 0x4
    f32 endz;        // at 0x8
    ut::Color color; // at 0xC
};

} // namespace g3d
} // namespace nw4r

#endif
