#include <nw4r/ef.h>

#include <cmath>

namespace nw4r {
namespace ef {

void EmitterFormCube::EmissionSub(math::VEC3& rPos, math::VEC3& rNormal,
                                  Emitter* pEmitter, ParticleManager* pManager,
                                  u16 life, f32 lifeRnd,
                                  const math::MTX34* pSpace) {

    if (rNormal.x != 0.0f || rNormal.y != 0.0f || rNormal.z != 0.0f) {
        math::VEC3Normalize(&rNormal, &rNormal);
    }

    math::VEC3 fromOrigin = rPos;

    if (math::VEC3LenSq(&fromOrigin) <= NW4R_MATH_FLT_MIN) {
        fromOrigin.x = 2.0f * pEmitter->mRandom.RandFloat() - 1.0f;
        fromOrigin.y = 2.0f * pEmitter->mRandom.RandFloat() - 1.0f;
        fromOrigin.z = 2.0f * pEmitter->mRandom.RandFloat() - 1.0f;
    }

    if (fromOrigin.x != 0.0f || fromOrigin.y != 0.0f || fromOrigin.z != 0.0f) {
        math::VEC3Normalize(&fromOrigin, &fromOrigin);
    }

    math::VEC3 fromYAxis = rPos;
    fromYAxis.y = 0.0f;

    if (math::VEC3LenSq(&fromYAxis) <= NW4R_MATH_FLT_MIN) {
        fromYAxis.x = 2.0f * pEmitter->mRandom.RandFloat() - 1.0f;
        fromYAxis.z = 2.0f * pEmitter->mRandom.RandFloat() - 1.0f;
    }

    if (fromYAxis.x != 0.0f || fromYAxis.y != 0.0f || fromYAxis.z != 0.0f) {
        math::VEC3Normalize(&fromYAxis, &fromYAxis);
    }

    math::VEC3 vel;
    CalcVelocity(&vel, pEmitter, rPos, rNormal, fromOrigin, fromYAxis);

    // clang-format off
    pManager->CreateParticle(
        CalcLife(life, lifeRnd, pEmitter),
        rPos,
        vel,
        pSpace,
        1.0f + pEmitter->mParameter.mVelMomentumRandom *
            (1.0f / 100.0f) * pEmitter->mRandom.RandFloat(),
        &pEmitter->mInheritSetting,
        pEmitter->mpReferenceParticle,
        pEmitter->mCalcRemain);
    // clang-format on
}

void EmitterFormCube::Emission(Emitter* pEmitter, ParticleManager* pManager,
                               int count, u32 flags, f32* pParams, u16 life,
                               f32 lifeRnd, const math::MTX34* pSpace) {

    if (count < 1) {
        return;
    }

    f32 outerX, outerY, outerZ;

    outerX = pParams[0];
    outerY = pParams[1];
    outerZ = pParams[2];

    if (outerX < 1e-5f) {
        outerX = 1e-5f;
    }
    if (outerY < 1e-5f) {
        outerY = 1e-5f;
    }
    if (outerZ < 1e-5f) {
        outerZ = 1e-5f;
    }

    f32 inner;
    if (pParams[3] == 0.0f) {
        inner = 1e-5f;
    } else {
        inner = pParams[3] * (1.0f / 100.0f);
    }

    f32 innerRev = 1.0f - inner;

    f32 diffuseNrm = pEmitter->mParameter.mVelDiffusionEmitterNormal;
    if (std::fabs(diffuseNrm - NW4R_MATH_PI) <
        NW4R_MATH_PI * NW4R_MATH_FLT_EPSILON) {

        diffuseNrm -= NW4R_MATH_PI * NW4R_MATH_FLT_EPSILON;
    }

    if (flags & EmitterDesc::EMIT_FLAG_17) {
        f32 div = 2.0f / (count + 1);

        int i;
        int countX = (count / 2) + 1;
        int countY = ((count - 1) / 2) + 1;

        int dir = 0;
        if (count % 2 == 0) {
            dir = 2;
        }

        int dirCountLife = 1;
        int dirCountRemain = dirCountLife;

        for (i = 0; i < count * count; i++) {
            if (i != 0) {
                switch (dir) {
                case 0: {
                    countY--;
                    break;
                }

                case 1: {
                    countX++;
                    break;
                }

                case 2: {
                    countY++;
                    break;
                }

                case 3: {
                    countX--;
                    break;
                }
                }

                if (--dirCountRemain <= 0) {
                    dir++;

                    if (dir == 4) {
                        dir = 0;
                    }

                    if (dir % 2 == 0) {
                        dirCountLife++;
                    }

                    dirCountRemain = dirCountLife;
                }
            }

            f32 baseX = countX * div - 1.0f;
            f32 baseY = countY * div - 1.0f;

            f32 x = baseX * outerX;
            f32 y = baseY * outerZ;

            f32 maxDepth = 1.0f - MAX(std::fabs(baseX), std::fabs(baseY));
            f32 dist = MAX(std::fabs(baseX), std::fabs(baseY));

            math::VEC3 pos;
            math::VEC3 normal;

            pos.x = x;
            pos.y = -outerY;
            pos.z = y;

            if (innerRev != 0.0f) {
                f32 rnd;
                if (flags & EmitterDesc::EMIT_FLAG_24) {
                    rnd = pEmitter->mRandom.RandFloat();
                    rnd *= rnd;
                    rnd = 1.0f - rnd * innerRev * maxDepth;
                } else {
                    rnd = 1.0f -
                          (pEmitter->mRandom.RandFloat() * innerRev * maxDepth);
                }

                pos.y *= rnd;
            }

            if (diffuseNrm == 0.0f ||
                (std::fabs(pos.x) < 1e-5f && std::fabs(pos.z) < 1e-5f)) {

                normal.x = 0.0f;
                normal.y = -1.0f;
                normal.z = 0.0f;
            } else {
                f32 cone = dist * diffuseNrm;
                f32 ylen = 1.0f / std::tanf(cone);

                normal.x = pos.x;
                normal.y = ylen * -std::sqrtf(pos.x * pos.x + pos.z * pos.z);
                normal.z = pos.z;
            }

            EmissionSub(pos, normal, pEmitter, pManager, life, lifeRnd, pSpace);
        }

        for (countY = 1; countY <= count; countY++) {
            f32 baseY = countY * div - 1.0f;
            f32 y = baseY * outerY;

            for (countX = 1; countX <= count; countX++) {
                f32 baseX = countX * div - 1.0f;
                f32 x = baseX * outerX;

                f32 maxDepth = 1.0f - MAX(std::fabs(baseX), std::fabs(baseY));
                f32 dist = MAX(std::fabs(baseX), std::fabs(baseY));

                math::VEC3 pos;
                math::VEC3 normal;

                pos.x = x;
                pos.y = y;
                pos.z = -outerZ;

                if (innerRev != 0.0f) {
                    f32 rnd;
                    if (flags & EmitterDesc::EMIT_FLAG_24) {
                        rnd = pEmitter->mRandom.RandFloat();
                        rnd *= rnd;
                        rnd = 1.0f - rnd * innerRev * maxDepth;
                    } else {
                        rnd = 1.0f - (pEmitter->mRandom.RandFloat() * innerRev *
                                      maxDepth);
                    }

                    pos.z *= rnd;
                }

                if (diffuseNrm == 0.0f ||
                    (std::fabs(pos.x) < 1e-5f && std::fabs(pos.y) < 1e-5f)) {

                    normal.x = 0.0f;
                    normal.y = 0.0f;
                    normal.z = -1.0f;
                } else {
                    f32 cone = dist * diffuseNrm;
                    f32 ylen = 1.0f / std::tanf(cone);

                    normal.x = pos.x;
                    normal.y = pos.y;

                    normal.z =
                        ylen * -std::sqrtf(pos.x * pos.x + pos.y * pos.y);
                }

                EmissionSub(pos, normal, pEmitter, pManager, life, lifeRnd,
                            pSpace);
            }

            for (countX = 1; countX <= count; countX++) {
                f32 baseX = countX * div - 1.0f;
                f32 x = baseX * outerZ;

                f32 maxDepth = 1.0f - MAX(std::fabs(baseX), std::fabs(baseY));
                f32 dist = MAX(std::fabs(baseX), std::fabs(baseY));

                math::VEC3 pos;
                math::VEC3 normal;

                pos.x = outerX;
                pos.y = y;
                pos.z = x;

                if (innerRev != 0.0f) {
                    f32 rnd;
                    if (flags & EmitterDesc::EMIT_FLAG_24) {
                        rnd = pEmitter->mRandom.RandFloat();
                        rnd *= rnd;
                        rnd = 1.0f - rnd * innerRev * maxDepth;
                    } else {
                        rnd = 1.0f - (pEmitter->mRandom.RandFloat() * innerRev *
                                      maxDepth);
                    }

                    pos.x *= rnd;
                }

                if (diffuseNrm == 0.0f ||
                    (std::fabs(pos.y) < 1e-5f && std::fabs(pos.z) < 1e-5f)) {

                    normal.x = 1.0f;
                    normal.y = 0.0f;
                    normal.z = 0.0f;
                } else {
                    f32 cone = dist * diffuseNrm;
                    f32 ylen = 1.0f / std::tanf(cone);

                    normal.x = ylen * std::sqrtf(pos.y * pos.y + pos.z * pos.z);

                    normal.y = pos.y;
                    normal.z = pos.z;
                }

                EmissionSub(pos, normal, pEmitter, pManager, life, lifeRnd,
                            pSpace);
            }

            for (countX = count; countX >= 1; countX--) {
                f32 baseX = countX * div - 1.0f;
                f32 x = baseX * outerX;

                f32 maxDepth = 1.0f - MAX(std::fabs(baseX), std::fabs(baseY));
                f32 dist = MAX(std::fabs(baseX), std::fabs(baseY));

                math::VEC3 pos;
                math::VEC3 normal;

                pos.x = x;
                pos.y = y;
                pos.z = outerZ;

                if (innerRev != 0.0f) {
                    f32 rnd;
                    if (flags & EmitterDesc::EMIT_FLAG_24) {
                        rnd = pEmitter->mRandom.RandFloat();
                        rnd *= rnd;
                        rnd = 1.0f - rnd * innerRev * maxDepth;
                    } else {
                        rnd = 1.0f - (pEmitter->mRandom.RandFloat() * innerRev *
                                      maxDepth);
                    }

                    pos.z *= rnd;
                }

                if (diffuseNrm == 0.0f ||
                    (std::fabs(pos.x) < 1e-5f && std::fabs(pos.y) < 1e-5f)) {

                    normal.x = 0.0f;
                    normal.y = 0.0f;
                    normal.z = 1.0f;
                } else {
                    f32 cone = dist * diffuseNrm;
                    f32 ylen = 1.0f / std::tanf(cone);

                    normal.x = pos.x;
                    normal.y = pos.y;
                    normal.z = ylen * std::sqrtf(pos.x * pos.x + pos.y * pos.y);
                }

                EmissionSub(pos, normal, pEmitter, pManager, life, lifeRnd,
                            pSpace);
            }

            for (countX = count; countX >= 1; countX--) {
                f32 baseX = countX * div - 1.0f;
                f32 x = baseX * outerZ;

                f32 maxDepth = 1.0f - MAX(std::fabs(baseX), std::fabs(baseY));
                f32 dist = MAX(std::fabs(baseX), std::fabs(baseY));

                math::VEC3 pos;
                math::VEC3 normal;

                pos.x = -outerX;
                pos.y = y;
                pos.z = x;

                if (innerRev != 0.0f) {
                    f32 rnd;
                    if (flags & EmitterDesc::EMIT_FLAG_24) {
                        rnd = pEmitter->mRandom.RandFloat();
                        rnd *= rnd;
                        rnd = 1.0f - rnd * innerRev * maxDepth;
                    } else {
                        rnd = 1.0f - (pEmitter->mRandom.RandFloat() * innerRev *
                                      maxDepth);
                    }

                    pos.x *= rnd;
                }

                if (diffuseNrm == 0.0f ||
                    (std::fabs(pos.y) < 1e-5f && std::fabs(pos.z) < 1e-5f)) {

                    normal.x = -1.0f;
                    normal.y = 0.0f;
                    normal.z = 0.0f;
                } else {
                    f32 cone = dist * diffuseNrm;
                    f32 ylen = 1.0f / std::tanf(cone);

                    normal.x =
                        ylen * -std::sqrtf(pos.y * pos.y + pos.z * pos.z);
                    normal.y = pos.y;
                    normal.z = pos.z;
                }

                EmissionSub(pos, normal, pEmitter, pManager, life, lifeRnd,
                            pSpace);
            }
        }

        {
            int i;
            int countX = 1;
            int countY = 1;

            int dir = 2;
            int dirCountLife = count - 1;
            int dirCountRemain = dirCountLife;

            for (i = 0; i < count * count; i++) {
                if (i != 0) {
                    switch (dir) {
                    case 0: {
                        countX--;
                        break;
                    }

                    case 1: {
                        countY++;
                        break;
                    }

                    case 2: {
                        countX++;
                        break;
                    }

                    case 3: {
                        countY--;
                        break;
                    }
                    }

                    if (--dirCountRemain <= 0) {
                        if (dir == 0) {
                            dir = 3;
                        } else {
                            dir--;
                        }

                        if (dir % 2 == 1 &&
                            (dir != 1 || dirCountLife != count - 1)) {

                            dirCountLife--;
                        }

                        dirCountRemain = dirCountLife;
                    }
                }

                f32 baseX = countX * div - 1.0f;
                f32 baseY = countY * div - 1.0f;

                f32 x = baseX * outerX;
                f32 y = baseY * outerZ;

                f32 maxDepth = 1.0f - MAX(std::fabs(baseX), std::fabs(baseY));
                f32 dist = MAX(std::fabs(baseX), std::fabs(baseY));

                math::VEC3 pos;
                math::VEC3 normal;

                pos.x = x;
                pos.y = outerY;
                pos.z = y;

                if (innerRev != 0.0f) {
                    f32 rnd;
                    if (flags & EmitterDesc::EMIT_FLAG_24) {
                        rnd = pEmitter->mRandom.RandFloat();
                        rnd *= rnd;
                        rnd = 1.0f - rnd * innerRev * maxDepth;
                    } else {
                        rnd = 1.0f - (pEmitter->mRandom.RandFloat() * innerRev *
                                      maxDepth);
                    }

                    pos.y *= rnd;
                }

                if (diffuseNrm == 0.0f ||
                    (std::fabs(pos.x) < 1e-5f && std::fabs(pos.z) < 1e-5f)) {

                    normal.x = 0.0f;
                    normal.y = 1.0f;
                    normal.z = 0.0f;
                } else {
                    f32 cone = dist * diffuseNrm;
                    f32 ylen = 1.0f / std::tanf(cone);

                    normal.x = pos.x;
                    normal.y = ylen * std::sqrtf(pos.x * pos.x + pos.z * pos.z);
                    normal.z = pos.z;
                }

                EmissionSub(pos, normal, pEmitter, pManager, life, lifeRnd,
                            pSpace);
            }
        }
    } else {
        for (int i = 0; i < count; i++) {
            f32 x, y, z;

            if (inner == 0.0f) {
                x = pEmitter->mRandom.RandFloat() * 2.0f - 1.0f;
                y = pEmitter->mRandom.RandFloat() * 2.0f - 1.0f;
                z = pEmitter->mRandom.RandFloat() * 2.0f - 1.0f;
            } else if (inner == 1.0f) {
                switch (pEmitter->mRandom.Rand() % 6) {
                case 0: {
                    x = pEmitter->mRandom.RandFloat() * 2.0f - 1.0f;
                    y = pEmitter->mRandom.RandFloat() * 2.0f - 1.0f;
                    z = 1.0f;
                    break;
                }

                case 1: {
                    x = pEmitter->mRandom.RandFloat() * 2.0f - 1.0f;
                    y = pEmitter->mRandom.RandFloat() * 2.0f - 1.0f;
                    z = -1.0f;
                    break;
                }

                case 2: {
                    x = pEmitter->mRandom.RandFloat() * 2.0f - 1.0f;
                    y = 1.0f;
                    z = pEmitter->mRandom.RandFloat() * 2.0f - 1.0f;
                    break;
                }

                case 3: {
                    x = pEmitter->mRandom.RandFloat() * 2.0f - 1.0f;
                    y = -1.0f;
                    z = pEmitter->mRandom.RandFloat() * 2.0f - 1.0f;
                    break;
                }

                case 4: {
                    x = 1.0f;
                    y = pEmitter->mRandom.RandFloat() * 2.0f - 1.0f;
                    z = pEmitter->mRandom.RandFloat() * 2.0f - 1.0f;
                    break;
                }

                case 5: {
                    x = -1.0f;
                    y = pEmitter->mRandom.RandFloat() * 2.0f - 1.0f;
                    z = pEmitter->mRandom.RandFloat() * 2.0f - 1.0f;
                    break;
                }
                }
            } else {
                f32 topBottom = outerX * outerY * innerRev * outerZ;
                f32 frontBack = outerX * outerY * inner * outerZ * innerRev;
                f32 leftRight =
                    outerX * innerRev * outerY * inner * outerZ * inner;

                f32 f = pEmitter->mRandom.RandFloat() *
                        (topBottom + frontBack + leftRight);

                if (f < topBottom) {
                    x = pEmitter->mRandom.RandFloat() * 2.0f - 1.0f;

                    y = (pEmitter->mRandom.RandFloat() * 2.0f - 1.0f) *
                        innerRev;
                    y = y >= 0.0f ? 1.0f - y : -1.0f - y;

                    z = pEmitter->mRandom.RandFloat() * 2.0f - 1.0f;
                } else if (f < topBottom + frontBack) {
                    x = pEmitter->mRandom.RandFloat() * 2.0f - 1.0f;
                    y = (pEmitter->mRandom.RandFloat() * 2.0f - 1.0f) * inner;

                    z = (pEmitter->mRandom.RandFloat() * 2.0f - 1.0f) *
                        innerRev;
                    z = z >= 0.0f ? 1.0f - z : -1.0f - z;
                } else {
                    x = (pEmitter->mRandom.RandFloat() * 2.0f - 1.0f) *
                        innerRev;
                    x = x >= 0.0f ? 1.0f - x : -1.0f - x;

                    y = (pEmitter->mRandom.RandFloat() * 2.0f - 1.0f) * inner;
                    z = (pEmitter->mRandom.RandFloat() * 2.0f - 1.0f) * inner;
                }
            }

            math::VEC3 pos;
            math::VEC3 normal(0.0f, 0.0f, 0.0f);

            if (y >= 0.0f && y >= std::fabs(x) && y >= std::fabs(z)) {
                normal.y = 1.0f;
            } else if (y < 0.0f && -y >= std::fabs(x) && -y >= std::fabs(z)) {
                normal.y = -1.0f;
            } else if (x >= 0.0f && x >= std::fabs(y) && x >= std::fabs(z)) {
                normal.x = 1.0f;
            } else if (x < 0.0f && -x >= std::fabs(y) && -x >= std::fabs(z)) {
                normal.x = -1.0f;
            } else if (z >= 0.0f) {
                normal.z = 1.0f;
            } else {
                normal.z = -1.0f;
            }

            pos.x = x * outerX;
            pos.y = y * outerY;
            pos.z = z * outerZ;

            if (diffuseNrm != 0.0f) {
                f32 dist;

                if (normal.x != 0.0f) {
                    dist = MAX(std::fabs(pos.y), std::fabs(pos.z));

                    f32 cone = dist * diffuseNrm;
                    f32 ylen = 1.0f / std::tanf(cone);

                    normal.x *=
                        ylen * std::sqrtf(pos.y * pos.y + pos.z * pos.z);
                    normal.y = pos.y;
                    normal.z = pos.z;
                } else if (normal.y != 0.0f) {
                    dist = MAX(std::fabs(pos.x), std::fabs(pos.z));

                    f32 cone = dist * diffuseNrm;
                    f32 ylen = 1.0f / std::tanf(cone);

                    normal.x = pos.x;
                    normal.y *=
                        ylen * std::sqrtf(pos.x * pos.x + pos.z * pos.z);
                    normal.z = pos.z;
                } else {
                    dist = MAX(std::fabs(pos.x), std::fabs(pos.y));

                    f32 cone = dist * diffuseNrm;
                    f32 ylen = 1.0f / std::tanf(cone);

                    normal.x = pos.x;
                    normal.y = pos.y;
                    normal.z *=
                        ylen * std::sqrtf(pos.x * pos.x + pos.y * pos.y);
                }
            }

            EmissionSub(pos, normal, pEmitter, pManager, life, lifeRnd, pSpace);
        }
    }
}

} // namespace ef
} // namespace nw4r
