#ifndef NW4R_EF_DRAW_STRATEGY_DRAW_SMOOTH_STRIPE_STRATEGY_H
#define NW4R_EF_DRAW_STRATEGY_DRAW_SMOOTH_STRIPE_STRATEGY_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/drawstrategy/ef_drawstrategyimpl.h>

#include <nw4r/math.h>

namespace nw4r {
namespace ef {

// Forward declarations
class Particle;

class DrawSmoothStripeStrategy : public DrawStrategyImpl {
public:
    struct Trigonometric {
        f32 mCos; // at 0x0
        f32 mSin; // at 0x4
    };

    struct Vertex {
        math::VEC3 mVertex0; // at 0x0
        math::VEC3 mVertex1; // at 0xC
        f32 mTexCoord;       // at 0x18
    };

    struct VertexTube {
        math::VEC3 mCenter; // at 0x0
        math::VEC3 mX;      // at 0xC
        math::VEC3 mZ;      // at 0x18
        f32 mTexCoord;      // at 0x24
    };

    struct AheadContextStripe : public AheadContext {
        math::VEC3 mEmitterAxisX;      // at 0xBC
        math::VEC3 mScreenAxisZ;       // at 0xC8
        Trigonometric* mTrigonometric; // at 0xD4
    };

public:
    DrawSmoothStripeStrategy();

    virtual void Draw(const DrawInfo& rInfo,
                      ParticleManager* pManager); // at 0xC

    virtual GetFirstDrawParticleFunc
    GetGetFirstDrawParticleFunc(int drawOrder); // at 0x10

    virtual GetNextDrawParticleFunc
    GetGetNextDrawParticleFunc(int drawOrder); // at 0x14

    virtual CalcAheadFunc
    GetCalcAheadFunc(ParticleManager* pManager); // at 0x18
};

} // namespace ef
} // namespace nw4r

#endif
