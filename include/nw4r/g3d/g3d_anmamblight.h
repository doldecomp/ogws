#ifndef NW4R_G3D_ANMAMBLIGHT_H
#define NW4R_G3D_ANMAMBLIGHT_H
#include <nw4r/types_nw4r.h>

namespace nw4r {
namespace g3d {

struct AmbLightAnmResult {
    u32 flags; // at 0x0
    u32 color; // at 0x4
};

} // namespace g3d
} // namespace nw4r

#endif
