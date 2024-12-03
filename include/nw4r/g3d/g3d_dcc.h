#ifndef NW4R_G3D_DCC_H
#define NW4R_G3D_DCC_H
#include "g3d_resanmtexsrt.h"
#include "types_nw4r.h"

namespace nw4r {
namespace g3d {

class WorldMtxAttr {
public:
    static bool IsScaleOne(u32 flags) {
        return (flags & 0x40000000);
    }

    static u32 AnmScaleOne(u32 flags) {
        return (flags | 0x40000000);
    }

    static u32 AnmNotScaleOne(u32 flags) {
        return (flags & 0x3fffffff);
    }

    static u32 AnmScaleUniform(u32 flags) {
        return (flags | 0x10000000);
    }

    static u32 AnmNotScaleUniform(u32 flags) {
        return (flags & 0x0fffffff);
    }
};

void CalcTexMtx(math::MTX34*, bool, const TexSrt&, TexSrt::Flag,
                TexSrtTypedef::TexMatrixMode);

} // namespace g3d

} // namespace nw4r

#endif