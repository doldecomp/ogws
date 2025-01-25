#include <nw4r/ef.h>

#include <cmath>

namespace nw4r {
namespace ef {

void EmitterFormSphere::Emission(Emitter* pEmitter, ParticleManager* pManager,
                                 int count, u32 flags, f32* pParams, u16 life,
                                 f32 lifeRnd, const math::MTX34* pSpace) {

    if (count < 1) {
        return;
    }

    f32 inner = pParams[1] / 100.0f;

    f32 sizeX, sizeY, sizeZ;

    sizeX = std::fabs(pParams[0]) > NW4R_MATH_FLT_EPSILON
                ? pParams[0]
                : NW4R_MATH_FLT_EPSILON;

    if (flags & EmitterDesc::EMIT_FLAG_XYZ_SAME_SIZE) {
        sizeY = sizeX;
        sizeZ = sizeX;
    } else {
        sizeY = std::fabs(pParams[4]) > NW4R_MATH_FLT_EPSILON
                    ? pParams[4]
                    : NW4R_MATH_FLT_EPSILON;

        sizeZ = std::fabs(pParams[5]) > NW4R_MATH_FLT_EPSILON
                    ? pParams[5]
                    : NW4R_MATH_FLT_EPSILON;
    }

    f32 startAngle = pParams[2];
    if (!(flags & EmitterDesc::EMIT_FLAG_18)) {
        startAngle += pEmitter->mRandom.RandFloat() * NW4R_MATH_PI * 2;
    }

    if (flags & EmitterDesc::EMIT_FLAG_17) {
        int maxX = count * 2 + 1;
        int countX = 0;

        int maxAngle = 1;
        int countAngle = 0;

        f32 sweepRange = pParams[3] - pParams[2];
        bool isSweepCircle = false;

        f32 f = std::fmodf(pParams[3] - pParams[2], NW4R_MATH_PI * 2);

        if (f < NW4R_EF_EMIT_ANGLE_MIN || f > NW4R_EF_EMIT_ANGLE_MAX) {
            isSweepCircle = true;
        }

        for (int i = 0; i < count * (count * 4) + 2; i++) {
            f32 x = static_cast<f32>(countX) / static_cast<f32>(maxX - 1) *
                        NW4R_MATH_PI +
                    (NW4R_MATH_PI / 2);

            f32 angle;
            if (maxAngle == 1) {
                angle = startAngle;
            } else if (isSweepCircle) {
                angle = startAngle + static_cast<f32>(countAngle) /
                                         static_cast<f32>(maxAngle) *
                                         sweepRange;
            } else {
                angle = startAngle + static_cast<f32>(countAngle) /
                                         static_cast<f32>(maxAngle - 1) *
                                         sweepRange;
            }

            countAngle++;

            if (countAngle == maxAngle) {
                countAngle = 0;
                countX++;

                if (countX * 2 < maxX) {
                    maxAngle = maxAngle != 1 ? maxAngle + 4 : maxAngle + 3;
                } else {
                    maxAngle = maxAngle != 4 ? maxAngle - 4 : 1;
                }
            }

            f32 radius = pEmitter->mRandom.RandFloat();

            if (flags & EmitterDesc::EMIT_FLAG_24) {
                radius = 1.0f - radius * radius * radius;
            }

            radius = radius * (1.0f - inner) + inner;

            math::VEC3 pos;
            math::VEC3 vel;
            math::VEC3 normal;
            math::VEC3 fromYAxis;

            fromYAxis.x = -std::sinf(angle);
            fromYAxis.y = 0.0f;
            fromYAxis.z = std::cosf(angle);

            pos.x = sizeX * radius * std::cosf(x) * fromYAxis.x;
            pos.y = sizeY * radius * -std::sinf(x);
            pos.z = sizeZ * radius * std::cosf(x) * fromYAxis.z;

            if (pos.x != 0.0f || pos.y != 0.0f || pos.z != 0.0f) {
                math::VEC3Normalize(&normal, &pos);
            } else {
                normal.x = normal.y = normal.z = 0.0f;
            }

            if (std::cosf(x) < 0.0f) {
                fromYAxis.x = -fromYAxis.x;
                fromYAxis.z = -fromYAxis.z;
            }

            CalcVelocity(&vel, pEmitter, pos, normal, normal, fromYAxis);

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
        }
    } else {
        f32 angle = 0.0f;
        f32 dangle = 0.0f;

        for (int i = 0; i < count; i++) {
            math::VEC3 pos;
            math::VEC3 vel;

            f32 dist = pEmitter->mRandom.RandFloat();
            f32 inner = pParams[1] / 100.0f;

            if (flags & EmitterDesc::EMIT_FLAG_24) {
                dist = 1.0f - dist * dist * dist;
                dist = dist + (inner * (1.0f - dist));
            } else {
                dist += inner * (1.0f - dist);
            }

            angle = (pParams[3] - pParams[2]) * pEmitter->mRandom.RandFloat() +
                    startAngle;

            f32 x = pEmitter->mRandom.RandFloat() * NW4R_MATH_PI +
                    (NW4R_MATH_PI / 2);

            pos.x = sizeX * dist * -std::cosf(x) * std::sinf(angle);
            pos.y = sizeY * dist * -std::sinf(x);
            pos.z = sizeZ * dist * std::cosf(x) * std::cosf(angle);

            math::VEC3 normal;
            if (pos.x != 0.0f || pos.y != 0.0f || pos.z != 0.0f) {
                math::VEC3Normalize(&normal, &pos);
            } else {
                normal.x = normal.y = normal.z = 0.0f;
            }

            math::VEC3 fromYAxis(pos);
            fromYAxis.y = 0.0f;

            if (fromYAxis.x != 0.0f || fromYAxis.z != 0.0f) {
                math::VEC3Normalize(&fromYAxis, &fromYAxis);
            }

            CalcVelocity(&vel, pEmitter, pos, normal, normal, fromYAxis);

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
        }
    }
}

} // namespace ef
} // namespace nw4r
