#ifndef NW4R_EF_EMFORM_CYLINDER_H
#define NW4R_EF_EMFORM_CYLINDER_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/ef_emitterform.h>

namespace nw4r {
namespace ef {

class EmitterFormCylinder : public EmitterForm {
public:
    EmitterFormCylinder() {}

    virtual void Emission(Emitter* pEmitter, ParticleManager* pManager,
                          int count, u32 flags, f32* pParams, u16 life,
                          f32 lifeRnd, const math::MTX34* pSpace); // at 0x8

private:
    void EmissionSub(Emitter* pEmitter, ParticleManager* pManager, int count,
                     u32 flags, f32* pParams, u16 life, f32 lifeRnd,
                     const math::MTX34* pSpace, f32 sizeX, f32 sizeY, f32 sizeZ,
                     f32 angle, f32 dangle, f32 angleOffset, f32 height);
};

} // namespace ef
} // namespace nw4r

#endif
