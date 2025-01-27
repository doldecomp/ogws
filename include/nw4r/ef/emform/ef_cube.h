#ifndef NW4R_EF_EMFORM_CUBE_H
#define NW4R_EF_EMFORM_CUBE_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/ef_emitterform.h>

namespace nw4r {
namespace ef {

class EmitterFormCube : public EmitterForm {
public:
    EmitterFormCube() {}

    virtual void Emission(Emitter* pEmitter, ParticleManager* pManager,
                          int count, u32 flags, f32* pParams, u16 life,
                          f32 lifeRnd, const math::MTX34* pSpace); // at 0x8

private:
    void EmissionSub(math::VEC3& rPos, math::VEC3& rNormal, Emitter* pEmitter,
                     ParticleManager* pManager, u16 life, f32 lifeRnd,
                     const math::MTX34* pSpace);
};

} // namespace ef
} // namespace nw4r

#endif
