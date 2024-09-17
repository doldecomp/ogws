#ifndef NW4R_G3D_ANMSHP_H
#define NW4R_G3D_ANMSHP_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_resvtx.h>

namespace nw4r {
namespace g3d {

struct ShpAnmVtxSet {
    ResVtxPos resVtxPos; // at 0x0
    ResVtxNrm resVtxNrm; // at 0x4
    ResVtxClr resVtxClr; // at 0x8
};

struct BlendVtx {
    ShpAnmVtxSet vtxSet; // at 0x0
    f32 weight;          // at 0xC
};

struct ShpAnmResult {
    static const int MAX_KEY_SHAPE = 32;

    u32 flags;                        // at 0x0
    u32 numKeyShape;                  // at 0x4
    ShpAnmVtxSet baseShapeVtxSet;     // at 0x8
    f32 baseShapeWeight;              // at 0x14
    BlendVtx keyShape[MAX_KEY_SHAPE]; // at 0x18
};

} // namespace g3d
} // namespace nw4r

#endif
