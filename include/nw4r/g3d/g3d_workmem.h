#ifndef NW4R_G3D_WORKMEM_H
#define NW4R_G3D_WORKMEM_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_anmshp.h>

#include <nw4r/math.h>

namespace nw4r {
namespace g3d {
namespace detail {
namespace workmem {

struct MdlZ {
    f32 Z;        // at 0x0
    u16 priority; // at 0x4
    u16 nodeID;   // at 0x6
    u16 matID;    // at 0x8
    u16 shpID;    // at 0xA
};

struct ShpAnmResultBuf {
    ShpAnmResult resultBuf;      // at 0x0
    const ShpAnmResult* pResult; // at 0x218
    f32 weight;                  // at 0x21C
};

math::VEC3* GetScaleTemporary();
u32* GetMtxIDTemporary();
MdlZ* GetMdlZTemporary();
math::MTX34* GetSkinningMtxTemporary();
math::MTX34* GetBillboardMtxTemporary();
ShpAnmResultBuf* GetShpAnmResultBufTemporary();

} // namespace workmem
} // namespace detail
} // namespace g3d
} // namespace nw4r

#endif
