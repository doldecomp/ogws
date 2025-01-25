#include <nw4r/ef.h>

#include <cmath>

namespace nw4r {
namespace ef {

void EmitterForm::CalcVelocity(math::VEC3* pVel, Emitter* pEmitter,
                               const math::VEC3& rPos,
                               const math::VEC3& rNormal,
                               const math::VEC3& rFromOrigin,
                               const math::VEC3& rFromYAxis) const {

#pragma unused(rPos)

    math::VEC3 vecWork;
    f32 fltWork;

    if (pEmitter->mParameter.mVelPowerRadiationDir != 0.0f) {
        math::VEC3Scale(pVel, &rFromOrigin,
                        pEmitter->mParameter.mVelPowerRadiationDir);
    } else {
        pVel->x = 0.0f;
        pVel->y = 0.0f;
        pVel->z = 0.0f;
    }

    if (pEmitter->mParameter.mVelPowerYAxis != 0.0f) {
        math::VEC3Scale(&vecWork, &rFromYAxis,
                        pEmitter->mParameter.mVelPowerYAxis);

        math::VEC3Add(pVel, pVel, &vecWork);
    }

    if (pEmitter->mParameter.mVelPowerRandomDir != 0.0f) {
        f32 rx = pEmitter->mRandom.RandFloat() * NW4R_MATH_PI * 2;
        f32 ry = pEmitter->mRandom.RandFloat() * NW4R_MATH_PI * 2;
        f32 rz = pEmitter->mRandom.RandFloat() * NW4R_MATH_PI * 2;

        f32 sr = std::sinf(rx);
        f32 cr = std::cosf(rx);

        f32 sp = std::sinf(ry);
        f32 cp = std::cosf(ry);

        f32 sh = std::sinf(rz);
        f32 ch = std::cosf(rz);

        pVel->x +=
            (cr * sp * ch + sr * sh) * pEmitter->mParameter.mVelPowerRandomDir;
        pVel->y +=
            (cr * sp * sh - sr * ch) * pEmitter->mParameter.mVelPowerRandomDir;

        pVel->z += pEmitter->mParameter.mVelPowerRandomDir * cr * cp;
    }

    if (pEmitter->mParameter.mVelPowerNormalDir != 0.0f) {
        pVel->x += rNormal.x * pEmitter->mParameter.mVelPowerNormalDir;
        pVel->y += rNormal.y * pEmitter->mParameter.mVelPowerNormalDir;
        pVel->z += rNormal.z * pEmitter->mParameter.mVelPowerNormalDir;
    }

    if (pEmitter->mParameter.mVelPowerSpecDir != 0.0f) {
        if (pEmitter->mParameter.mVelDiffusionSpecDir == 0.0f) {
            math::MTX34 mtx;
            math::MTX34RotXYZRad(&mtx, pEmitter->mParameter.mVelSpecDir.x,
                                 pEmitter->mParameter.mVelSpecDir.y,
                                 pEmitter->mParameter.mVelSpecDir.z);

            math::VEC3 vec(0.0f, 1.0f, 0.0f);
            math::VEC3Transform(&vec, &mtx, &vec);

            pVel->x += pEmitter->mParameter.mVelPowerSpecDir * vec.x;
            pVel->y += pEmitter->mParameter.mVelPowerSpecDir * vec.y;
            pVel->z += pEmitter->mParameter.mVelPowerSpecDir * vec.z;
        } else {
            math::MTX34 mtx;

            // clang-format off
            math::MTX34RotXYZRad(&mtx,
                pEmitter->mRandom.RandFloat() * pEmitter->mParameter.mVelDiffusionSpecDir,
                pEmitter->mRandom.RandFloat() * NW4R_MATH_PI * 2,
                0.0f);
            // clang-format on

            math::MTX34 rotFromZ;
            math::MTX34RotXYZRad(&rotFromZ, pEmitter->mParameter.mVelSpecDir.x,
                                 pEmitter->mParameter.mVelSpecDir.y,
                                 pEmitter->mParameter.mVelSpecDir.z);

            math::MTX34Mult(&mtx, &rotFromZ, &mtx);

            pVel->x += mtx._01 * pEmitter->mParameter.mVelPowerSpecDir;
            pVel->y += mtx._11 * pEmitter->mParameter.mVelPowerSpecDir;
            pVel->z += mtx._21 * pEmitter->mParameter.mVelPowerSpecDir;
        }
    }

    if (pEmitter->mParameter.mVelInitVelocityRandom != 0) {
        fltWork = 1.0f - pEmitter->mParameter.mVelInitVelocityRandom *
                             (1.0f / 100.0f) *
                             (pEmitter->mRandom.RandFloat() * 2.0f - 1.0f);

        pVel->x *= fltWork;
        pVel->y *= fltWork;
        pVel->z *= fltWork;
    }
}

u16 EmitterForm::CalcLife(u16 life, f32 lifeRnd, Emitter* pEmitter) {
    u16 newLife = life;

    if (lifeRnd != 0.0f) {
        f32 rnd = life * pEmitter->mRandom.RandFloat() * lifeRnd;

        if (static_cast<f32>(newLife) - rnd < 1.0f) {
            newLife = 1;
        } else if (static_cast<f32>(newLife) - rnd > 65535.0f) {
            newLife = 65535;
        } else {
            newLife -= static_cast<u16>(rnd);
        }
    }

    return newLife;
}

} // namespace ef
} // namespace nw4r
