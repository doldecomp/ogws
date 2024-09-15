#ifndef NW4R_G3D_ANMTEXPAT_H
#define NW4R_G3D_ANMTEXPAT_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_respltt.h>
#include <nw4r/g3d/g3d_restex.h>

namespace nw4r {
namespace g3d {

struct TexPatAnmResult {
    static const int NUM_OF_ANMS = 8;

    u8 bTexExist;              // at 0x0
    u8 bPlttExist;             // at 0x1
    u8 padding_[2];            // at 0x2
    ResTex tex[NUM_OF_ANMS];   // at 0x4
    ResPltt pltt[NUM_OF_ANMS]; // at 0x24
};

} // namespace g3d
} // namespace nw4r

#endif