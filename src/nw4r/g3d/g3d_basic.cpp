#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/g3d.h>

namespace nw4r {
namespace g3d {
namespace detail {
namespace dcc {

u32 CalcWorldMtx_Basic(math::MTX34* pW, math::VEC3* pS, const math::MTX34* pW1,
                       const math::VEC3* pS1, u32 attr,
                       const ChrAnmResult* pResult) {

    u32 flag = pResult->flags;
    u32 newAttr = attr;

    if (flag & ChrAnmResult::FLAG_S_ONE) {
        newAttr = WorldMtxAttr::AnmScaleOne(newAttr);
        pS->x = pS->y = pS->z = 1.0f;
    } else {
        newAttr = WorldMtxAttr::AnmNotScaleOne(newAttr);
        *pS = pResult->s;
    }

    if ((flag & ChrAnmResult::FLAG_MTX_IDENT) ||
        (flag & ChrAnmResult::FLAG_RT_ZERO)) {

        if (WorldMtxAttr::IsScaleOne(attr)) {
            math::MTX34Copy(pW, pW1);
        } else {
            math::MTX34Scale(pW, pW1, pS1);
        }
    } else if (flag & ChrAnmResult::FLAG_R_ZERO) {
        if (WorldMtxAttr::IsScaleOne(attr)) {
            math::VEC3 trans(pResult->rt.m[0][3], pResult->rt.m[1][3],
                             pResult->rt.m[2][3]);

            math::MTX34Trans(pW, pW1, &trans);
        } else {
            math::MTX34 temp;

            math::MTX34Scale(&temp, pS1, &pResult->rt);
            math::MTX34Mult(pW, pW1, &temp);
        }
    } else if (WorldMtxAttr::IsScaleOne(attr)) {
        math::MTX34Mult(pW, pW1, &pResult->rt);
    } else {
        math::MTX34Scale(pW, pW1, pS1);
        math::MTX34Mult(pW, pW, &pResult->rt);
    }

    if (flag & ChrAnmResult::FLAG_S_UNIFORM) {
        newAttr = WorldMtxAttr::AnmScaleUniform(newAttr);
    } else {
        newAttr = WorldMtxAttr::AnmNotScaleUniform(newAttr);
    }

    return newAttr;
}

} // namespace dcc
} // namespace detail
} // namespace g3d
} // namespace nw4r
