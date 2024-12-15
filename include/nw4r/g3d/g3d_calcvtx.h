#ifndef NW4R_G3D_CALCVIEW_H
#define NW4R_G3D_CALCVIEW_H
#include <nw4r/types_nw4r.h>

namespace nw4r {
namespace g3d {

void CalcView(math::MTX34*, math::MTX33*, const math::MTX34*, const u32*, u32,
              const math::MTX34*, ResMdl, math::MTX34*);

void CalcView_LC(math::MTX34*, math::MTX33*, const math::MTX34*, const u32*,
                 u32, const math::MTX34*, ResMdl, math::MTX34*);

void CalcView_LC_DMA_ModelMtx(math::MTX34*, math::MTX33*, const math::MTX34*,
                              const u32*, u32, const math::MTX34*, ResMdl,
                              math::MTX34*);

} // namespace g3d
} // namespace nw4r

#endif