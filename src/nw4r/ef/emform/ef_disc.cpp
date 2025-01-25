#include <nw4r/ef.h>

#include <cmath>

namespace nw4r {
namespace ef {

void EmitterFormDisc::Emission(Emitter* pEmitter, ParticleManager* pManager,
                               int count, u32 flags, f32* pParams, u16 life,
                               f32 lifeRnd, const math::MTX34* pSpace) {

    if (count < 1) {
        return;
    }

    f32 sizeX, sizeZ;

    sizeX = std::fabs(pParams[0]) > NW4R_MATH_FLT_EPSILON
                ? pParams[0]
                : NW4R_MATH_FLT_EPSILON;

    if (flags & EmitterDesc::EMIT_FLAG_XYZ_SAME_SIZE) {
        sizeZ = sizeX;
    } else {
        sizeZ = std::fabs(pParams[4]) > NW4R_MATH_FLT_EPSILON
                    ? pParams[4]
                    : NW4R_MATH_FLT_EPSILON;
    }

    f32 angle = 0.0f;
    f32 dangle = 0.0f;

    f32 angleOffset;
    if (flags & EmitterDesc::EMIT_FLAG_18) {
        angleOffset = pParams[2];
    } else {
        angleOffset = pEmitter->mRandom.RandFloat() * NW4R_MATH_PI * 2;
    }

    if (flags & EmitterDesc::EMIT_FLAG_17) {
        f32 f = std::fmodf(pParams[3] - pParams[2], NW4R_MATH_PI * 2);

        if (f < NW4R_EF_EMIT_ANGLE_MIN || f > NW4R_EF_EMIT_ANGLE_MAX) {
            dangle =
                (pParams[3] - pParams[2]) / pEmitter->mParameter.mEmitEmitDiv;
        } else {
            // @bug EmitDiv value of 1 will cause division by zero
            dangle = (pParams[3] - pParams[2]) /
                     (pEmitter->mParameter.mEmitEmitDiv - 1);
        }
    }

    for (int i = 0; i < count; i++) {
        math::VEC3 pos;
        math::VEC3 vel;

        f32 dist = pEmitter->mRandom.RandFloat();
        f32 inner = pParams[1] / 100.0f;

        if (flags & EmitterDesc::EMIT_FLAG_24) {
            dist = std::sqrtf(dist + inner * inner * (1.0f - dist));
        } else {
            dist = dist + (inner * (1.0f - dist));
        }

        if (!(flags & EmitterDesc::EMIT_FLAG_17)) {
            angle = (pParams[3] - pParams[2]) * pEmitter->mRandom.RandFloat();
        }

        f32 sa = std::sinf(angleOffset + angle);
        f32 ca = std::cosf(angleOffset + angle);

        math::VEC3 fromYAxis(sa, 0.0f, -ca);

        pos.x = fromYAxis.x * dist * sizeX;
        pos.y = 0.0f;
        pos.z = fromYAxis.z * dist * sizeZ;

        math::VEC3 fromOrigin = fromYAxis;

        math::VEC3 normal;
        if (pEmitter->mParameter.mVelDiffusionEmitterNormal == 0.0f) {
            normal.x = 0.0f;
            normal.y = 1.0f;
            normal.z = 0.0f;
        } else {
            f32 cone = dist * pEmitter->mParameter.mVelDiffusionEmitterNormal;

            normal.x = std::sinf(cone) * sa;
            normal.y = std::cosf(cone);
            normal.z = std::sinf(cone) * -ca;
        }

        CalcVelocity(&vel, pEmitter, pos, normal, fromOrigin, fromYAxis);

        // clang-format off
        pManager->CreateParticle(
            CalcLife(life, lifeRnd, pEmitter),
            pos,
            vel,
            pSpace,
            1.0f + pEmitter->mParameter.mVelMomentumRandom *
                (1.0f / 100.0f) * pEmitter->mRandom.RandFloat(),
            &pEmitter->mInheritSetting,
            pEmitter->mpReferenceParticle,
            pEmitter->mCalcRemain);
        // clang-format on

        if (flags & EmitterDesc::EMIT_FLAG_17) {
            angle += dangle;
        }
    }
}

} // namespace ef
} // namespace nw4r
