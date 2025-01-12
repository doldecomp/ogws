#ifndef NW4R_EF_CUBE_H
#define NW4R_EF_CUBE_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/ef_emitterform.h>

namespace nw4r {
namespace ef {

class EmitterFormCube : public EmitterForm {
public:
    virtual UNKTYPE Emission(Emitter*, ParticleManager*, int, u32, float*, u16,
                             float, const math::MTX34*);
};

} // namespace ef
} // namespace nw4r

#endif
