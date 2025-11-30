#ifndef NW4R_EF_EMITTER_FORM_H
#define NW4R_EF_EMITTER_FORM_H
#include <nw4r/types_nw4r.h>

#include <nw4r/math.h>

namespace nw4r {
namespace ef {

// Forward declarations
class Emitter;
class ParticleManager;

class EmitterForm {
public:
    EmitterForm() {}

    virtual void Emission(Emitter* pEmitter, ParticleManager* pManager,
                          int count, u32 flags, f32* pParams, u16 life,
                          f32 lifeRnd, const math::MTX34* pSpace) = 0; // at 0x8

    void CalcVelocity(math::VEC3* pVel, Emitter* pEmitter,
                      const math::VEC3& rPos, const math::VEC3& rNormal,
                      const math::VEC3& rFromOrigin,
                      const math::VEC3& rFromYAxis) const;

    u16 CalcLife(u16 life, f32 lifeRnd, Emitter* pEmitter);
};

} // namespace ef
} // namespace nw4r

#endif
