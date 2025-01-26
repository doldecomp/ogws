#include <nw4r/ef.h>

#include <cmath>

namespace nw4r {
namespace ef {

void EmitterFormTorus::Emission(Emitter* pEmitter, ParticleManager* pManager,
                                int count, u32 flags, f32* pParams, u16 life,
                                f32 lifeRnd, const math::MTX34* pSpace) {

    if (count < 1) {
        return;
    }

    f32 sizeX, sizeY, sizeZ;

    sizeX = std::fabs(pParams[0]) > NW4R_MATH_FLT_EPSILON
                ? pParams[0]
                : NW4R_MATH_FLT_EPSILON;

    sizeY = std::fabs(pParams[4]) > NW4R_MATH_FLT_EPSILON
                ? pParams[4]
                : NW4R_MATH_FLT_EPSILON;

    if (flags & EmitterDesc::EMIT_FLAG_XYZ_SAME_SIZE) {
        sizeZ = sizeX;
    } else {
        sizeZ = std::fabs(pParams[5]) > NW4R_MATH_FLT_EPSILON
                    ? pParams[5]
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

    int loopCount;
    if (flags & EmitterDesc::EMIT_FLAG_17) {
        loopCount = count * count;
    } else {
        loopCount = count;
    }

    f32 ringAngle = 0.0f;

    for (int i = 0; i < loopCount; i++) {
        math::VEC3 pos;
        math::VEC3 vel;

        f32 inner = (100.0f - pParams[1]) / (100.0f + pParams[1]);

        if (!(flags & EmitterDesc::EMIT_FLAG_17)) {
            angle = (pParams[3] - pParams[2]) * pEmitter->mRandom.RandFloat();
            ringAngle = pEmitter->mRandom.RandFloat() * NW4R_MATH_PI * 2;
        }

        f32 sa = std::sinf(angleOffset + angle);
        f32 ca = std::cosf(angleOffset + angle);

        f32 sr = std::sinf(ringAngle);
        f32 cr = std::cosf(ringAngle);

        pos.x = (inner * cr * sa + sa) * sizeX / (1.0f + inner);
        pos.y = sizeY * sr;
        pos.z = (-inner * cr * ca - ca) * sizeZ / (1.0f + inner);

        math::VEC3 fromOrigin = pos;
        if (fromOrigin.x != 0.0f || fromOrigin.y != 0.0f ||
            fromOrigin.z != 0.0f) {
            math::VEC3Normalize(&fromOrigin, &fromOrigin);
        }

        math::VEC3 fromYAxis(pos.x, 0.0f, pos.z);
        if (fromYAxis.x != 0.0f || fromYAxis.z != 0.0f) {
            math::VEC3Normalize(&fromYAxis, &fromYAxis);
        }

        math::VEC3 normal;
        if (inner == 0.0f) {
            normal.x = sizeX * cr * sa;
            normal.y = sizeY * sr;
            normal.z = -sizeZ * cr * ca;
        } else {
            normal.x = (inner * cr * sa) * sizeX / (1.0f + inner);
            normal.y = sizeY * sr;
            normal.z = (-inner * cr * ca) * sizeZ / (1.0f + inner);
        }

        if (normal.x != 0.0f || normal.y != 0.0f || normal.z != 0.0f) {
            math::VEC3Normalize(&normal, &normal);
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
            if ((i + 1) % count == 0) {
                angle += dangle;
                ringAngle = 0.0f;
            } else {
                ringAngle += NW4R_MATH_PI * 2 / count;
            }
        }
    }
}

} // namespace ef
} // namespace nw4r
