#ifndef NW4R_G3D_ANMCLR_H
#define NW4R_G3D_ANMCLR_H
#include <nw4r/types_nw4r.h>

namespace nw4r {
namespace g3d {

struct ClrAnmResult {
    static const int NUM_OF_CLA_COLOR = 11;

    u32 bRgbaExist;                 // at 0x0
    u32 rgba[NUM_OF_CLA_COLOR];     // at 0x4
    u32 rgbaMask[NUM_OF_CLA_COLOR]; // at 0x30
};

} // namespace g3d
} // namespace nw4r

#endif
