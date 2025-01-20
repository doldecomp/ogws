#include <nw4r/ef.h>
#include <nw4r/math.h>
#include <nw4r/ut.h>

#include <cmath>

namespace nw4r {
namespace ef {

u16 UtlistToArray(const ut::List* pList, void** ppArray, int maxlen) {
    u16 num = 0;

    NW4R_UT_LIST_FOREACH (void, it, *pList, {
        ppArray[num++] = it;

        if (num >= maxlen) {
            break;
        }
    });

    return num;
}

math::VEC3& Rotation2VecY(const nw4r::math::VEC3& rRot,
                          nw4r::math::VEC3* pVec) {

    f32 sx = std::sinf(rRot.x);
    f32 cx = std::cosf(rRot.x);

    f32 sy = std::sinf(rRot.y);
    f32 cy = std::cosf(rRot.y);

    f32 sz = std::sinf(rRot.z);
    f32 cz = std::cosf(rRot.z);

    pVec->x = sx * sy * cz - cx * sz;
    pVec->y = sx * sy * sz + cx * cz;
    pVec->z = sx * cy;

    return *pVec;
}

void GetDirMtxY(math::MTX34* pMtx, const math::VEC3& rVec) {
    f32 sx, cx;
    f32 sz, cz;

    sx = rVec.z;
    cx = math::FSqrt(1.0f - sx * sx);

    if (cx > NW4R_MATH_FLT_EPSILON) {
        cz = rVec.y / cx;
        sz = rVec.x / -cx;
    } else {
        sz = 0.0f;
        cz = 1.0f;
    }

    pMtx->_00 = cz;
    pMtx->_01 = rVec.x;
    pMtx->_02 = sx * sz;
    pMtx->_03 = 0.0f;

    pMtx->_10 = sz;
    pMtx->_11 = rVec.y;
    pMtx->_12 = -cz * sx;
    pMtx->_13 = 0.0f;

    pMtx->_20 = 0.0f;
    pMtx->_21 = rVec.z;
    pMtx->_22 = cx;
    pMtx->_23 = 0.0f;
}

void MtxGetRotationMtx(const math::MTX34& rMtx, math::MTX34* pDst) {
    math::VEC3 x, y, z;

    MtxColVec(&rMtx, 0, &x);
    if (x.x != 0.0f || x.y != 0.0f || x.z != 0.0f) {
        math::VEC3Normalize(&x, &x);
    } else {
        x.x = 1.0f;
    }

    MtxColVec(&rMtx, 1, &y);
    if (y.x != 0.0f || y.y != 0.0f || y.z != 0.0f) {
        math::VEC3Normalize(&y, &y);
    } else {
        y.y = 1.0f;
    }

    math::VEC3Cross(&z, &x, &y);
    math::VEC3Cross(&y, &z, &x);

    MtxSetColVec(pDst, 0, &x);
    MtxSetColVec(pDst, 1, &y);
    MtxSetColVec(pDst, 2, &z);

    pDst->_03 = 0.0f;
    pDst->_13 = 0.0f;
    pDst->_23 = 0.0f;
}

void MtxSetColVec(math::MTX34* pMtx, int col, const math::VEC3* pVec) {
    pMtx->m[0][col] = pVec->x;
    pMtx->m[1][col] = pVec->y;
    pMtx->m[2][col] = pVec->z;
}

math::VEC3* MtxColVec(const math::MTX34* pMtx, int col, math::VEC3* pVec) {
    pVec->x = pMtx->m[0][col];
    pVec->y = pMtx->m[1][col];
    pVec->z = pMtx->m[2][col];

    return pVec;
}

void MtxGetRotation(const math::MTX34& rMtx, math::VEC3* pRot) {
    f32 C;
    f32 sx, sy, sz;
    f32 f;

    if (!((sx = std::sqrtf(rMtx._00 * rMtx._00 + rMtx._10 * rMtx._10 +
                           rMtx._20 * rMtx._20)) < NW4R_MATH_FLT_MIN) &&
        !((sy = std::sqrtf(rMtx._01 * rMtx._01 + rMtx._11 * rMtx._11 +
                           rMtx._21 * rMtx._21)) < NW4R_MATH_FLT_MIN) &&
        !((sz = std::sqrtf(rMtx._02 * rMtx._02 + rMtx._12 * rMtx._12 +
                           rMtx._22 * rMtx._22)) < NW4R_MATH_FLT_MIN)) {

        f = -rMtx._20 / sx;
        pRot->y = std::asinf(f);
        C = std::cosf(pRot->y);

        if (C >= NW4R_MATH_FLT_MIN) {
            pRot->x = std::atan2f(rMtx._21 / sy, rMtx._22 / sz);
            pRot->z = std::atan2f(rMtx._10, rMtx._00);
        } else {
            pRot->x = std::atan2f(rMtx._01, rMtx._11);
            pRot->z = 0.0f;
        }
    } else {
        pRot->x = 0.0f;
        pRot->y = 0.0f;
        pRot->z = 0.0f;
    }
}

void MtxGetTranslate(const math::MTX34& rMtx, math::VEC3* pTrans) {
    pTrans->x = rMtx._03;
    pTrans->y = rMtx._13;
    pTrans->z = rMtx._23;
}

void MtxGetScale(const math::MTX34& rMtx, math::VEC3* pScale) {
    f32 sh[3];
    math::VEC3 v0, v1, v2, v;
    f32 mag;

    MtxColVec(&rMtx, 0, &v0);
    mag = math::VEC3LenSq(&v0);

    if (mag > NW4R_MATH_FLT_EPSILON) {
        mag = math::FrSqrt(mag);
        pScale->x = 1.0f / mag;

        math::VEC3Scale(&v0, &v0, mag);
        MtxColVec(&rMtx, 1, &v1);

        sh[0] = math::VEC3Dot(&v0, &v1);
        math::VEC3Scale(&v, &v0, sh[0]);
        math::VEC3Sub(&v1, &v1, &v);

        mag = math::VEC3LenSq(&v1);

        if (mag > NW4R_MATH_FLT_EPSILON) {
            mag = math::FrSqrt(mag);
            pScale->y = 1.0f / mag;

            sh[0] *= mag;
            math::VEC3Scale(&v1, &v1, mag);
            MtxColVec(&rMtx, 2, &v2);

            sh[2] = math::VEC3Dot(&v1, &v2);
            math::VEC3Scale(&v, &v1, sh[2]);
            math::VEC3Sub(&v2, &v2, &v);

            sh[1] = math::VEC3Dot(&v0, &v2);
            math::VEC3Scale(&v, &v0, sh[1]);
            math::VEC3Sub(&v2, &v2, &v);

            mag = math::VEC3LenSq(&v2);

            if (mag > NW4R_MATH_FLT_EPSILON) {
                pScale->z = std::sqrtf(mag);
                math::VEC3Cross(&v, &v1, &v2);

                if (math::VEC3Dot(&v0, &v) < 0.0f) {
                    // Double precision
                    pScale->x *= -1.0;
                    pScale->y *= -1.0;
                    pScale->z *= -1.0;
                }
            } else {
                pScale->z = 0.0f;
            }
        } else {
            pScale->y = 0.0f;
            MtxColVec(&rMtx, 2, &v2);

            sh[1] = math::VEC3Dot(&v0, &v2);
            math::VEC3Scale(&v, &v0, sh[1]);
            math::VEC3Sub(&v2, &v2, &v);

            mag = math::VEC3LenSq(&v2);

            if (mag > NW4R_MATH_FLT_EPSILON) {
                pScale->z = std::sqrtf(mag);
            } else {
                pScale->z = 0.0f;
            }
        }

    } else {
        pScale->x = 0.0f;

        MtxColVec(&rMtx, 1, &v1);
        mag = math::VEC3LenSq(&v1);

        if (mag > NW4R_MATH_FLT_EPSILON) {
            mag = math::FrSqrt(mag);
            pScale->y = 1.0f / mag;

            math::VEC3Scale(&v1, &v1, mag);
            MtxColVec(&rMtx, 2, &v2);

            sh[2] = math::VEC3Dot(&v1, &v2);
            math::VEC3Scale(&v, &v1, sh[2]);
            math::VEC3Sub(&v2, &v2, &v);
            pScale->z = math::VEC3Len(&v2);
        } else {
            pScale->y = 0.0f;

            MtxColVec(&rMtx, 2, &v2);
            pScale->z = math::VEC3Len(&v2);
        }
    }
}

} // namespace ef
} // namespace nw4r
