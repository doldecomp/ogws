#ifndef NW4R_EF_DRAW_BILLBOARD_STRATEGY_H
#define NW4R_EF_DRAW_BILLBOARD_STRATEGY_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/drawstrategy/ef_drawstrategyimpl.h>

namespace nw4r {
namespace ef {

class DrawBillboardStrategy : public DrawStrategyImpl {
public:
    DrawBillboardStrategy();

    virtual void Draw(const DrawInfo& rInfo,
                      ParticleManager* pManager); // at 0xC

    virtual CalcAheadFunc
    GetCalcAheadFunc(ParticleManager* pManager); // at 0x18

    void InitGraphics(const DrawInfo& rInfo, ParticleManager* pManager);

private:
    void DrawNormalBillboard(const DrawInfo& rInfo, ParticleManager* pManager);

    inline void DispParticle_Normal(Particle* pParticle,
                                    const math::MTX34& rViewMtx, f32 vx, f32 vy,
                                    f32 vz, f32 rc, f32 rs, f32 sx, f32 sy,
                                    const math::VEC2& rPivot, int flags);

    void DrawYBillboard(const DrawInfo& rInfo, ParticleManager* pManager);

    inline void DispParticle_YBillboard(Particle* pParticle,
                                        const math::MTX34& rViewMtx, f32 vx,
                                        f32 vy, f32 vz, f32 rc, f32 rs, f32 sx,
                                        f32 sy, const math::VEC2& rPivot,
                                        int flags);

    void DrawDirectionalBillboard(const DrawInfo& rInfo,
                                  ParticleManager* pManager);

    inline void DispParticle_Directional(Particle* pParticle,
                                         const math::MTX34& rViewMtx, f32 vx,
                                         f32 vy, f32 vz, f32 rc, f32 rs, f32 sx,
                                         f32 sy, const math::VEC2& rPivot,
                                         int flags);

    void DispPolygon(const math::VEC3& rP, const math::VEC3& rD1,
                     const math::VEC3& rD2, int flags);

    void CalcZOffset(math::MTX34* pMtx, const ParticleManager* pManager,
                     const DrawInfo& rInfo, f32 offsetZ);
};

} // namespace ef
} // namespace nw4r

#endif
