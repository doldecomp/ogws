#include "g3d_basic.h"

namespace nw4r
{
    namespace g3d
    {
        namespace detail
        {
            namespace dcc
            {
                u32 CalcWorldMtx_Basic(math::MTX34 *pMtx, math::VEC3 *pVec, const math::MTX34 *pcMtx,
                const math::VEC3 *pcVec, u32 worldAttr, const ChrAnmResult *pcAnm)
                {
                    u32 anmFlags = pcAnm->mFlags;
                    u32 newAttr;
                    if (anmFlags & 0x8)
                    {
                        newAttr = WorldMtxAttr::AnmScaleOne(worldAttr);
                        pVec->z = 1.0f;
                        pVec->y = 1.0f;
                        pVec->x = 1.0f;
                    }
                    else
                    {
                        newAttr = WorldMtxAttr::AnmNotScaleOne(worldAttr);
                        *pVec = pcAnm->VEC3_0x4;
                    }

                    if ((anmFlags & 0x2) || (anmFlags & 0x4))
                    {
                        if (WorldMtxAttr::IsScaleOne(worldAttr))
                        {
                            math::MTX34Copy(pMtx, pcMtx);
                        }
                        else
                        {
                            math::MTX34Scale(pMtx, pcMtx, pcVec);
                        }
                    }
                    else if (anmFlags & 0x20)
                    {
                        if (WorldMtxAttr::IsScaleOne(worldAttr))
                        {
                            const math::VEC3 stack_0x8(pcAnm->mMtx[0][3], pcAnm->mMtx[1][3], pcAnm->mMtx[2][3]);
                            math::MTX34Trans(pMtx, pcMtx, &stack_0x8);
                        }
                        else
                        {
                            math::MTX34 stack_0x18;
                            math::MTX34Scale(&stack_0x18, pcVec, &pcAnm->mMtx);
                            math::MTX34Mult(pMtx, pcMtx, &stack_0x18);
                        }
                    }
                    else if (WorldMtxAttr::IsScaleOne(worldAttr))
                    {
                        math::MTX34Mult(pMtx, pcMtx, &pcAnm->mMtx);
                    }                        
                    else
                    {
                        math::MTX34Scale(pMtx, pcMtx, pcVec);
                        math::MTX34Mult(pMtx, pMtx, &pcAnm->mMtx);
                    }

                    u32 result = WorldMtxAttr::AnmNotScaleUniform(newAttr);
                    if (anmFlags & 0x10)
                    {
                        result = WorldMtxAttr::AnmScaleUniform(newAttr);
                    }

                    return result;
                }
            }
        }
    }
}