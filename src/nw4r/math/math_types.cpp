#include "math_types.h"
#include "math_equation.h"
#include "math_triangular.h"

namespace nw4r
{
    namespace math
    {
        void VEC3Maximize(VEC3 *out, const VEC3 *in1, const VEC3 *in2)
        {
            register f32 a, b, c, d;
            
            a = in1->mCoords.x;
            b = in2->mCoords.x;
            c = a - b;
            asm 
            {
                fsel d, c, a, b
            }
            out->mCoords.x = d;

            a = in1->mCoords.y;
            b = in2->mCoords.y;
            c = a - b;
            asm 
            {
                fsel d, c, a, b
            }
            out->mCoords.y = d;

            a = in1->mCoords.z;
            b = in2->mCoords.z;
            c = a - b;
            asm 
            {
                fsel d, c, a, b
            }
            out->mCoords.z = d;
        }

        void VEC3Minimize(VEC3 *out, const VEC3 *in1, const VEC3 *in2)
        {
            register f32 a, b, c, d;
            
            a = in1->mCoords.x;
            b = in2->mCoords.x;
            c = b - a;
            asm 
            {
                fsel d, c, a, b
            }
            out->mCoords.x = d;

            a = in1->mCoords.y;
            b = in2->mCoords.y;
            c = b - a;
            asm 
            {
                fsel d, c, a, b
            }
            out->mCoords.y = d;

            a = in1->mCoords.z;
            b = in2->mCoords.z;
            c = b - a;
            asm 
            {
                fsel d, c, a, b
            }
            out->mCoords.z = d;
        }

        void MTX33Identity(register MTX33 *in)
        {
            register f32 a, b, c;
            a = 0.0f;
            b = 1.0f;
            
            asm
            {
                psq_st a, 8(in), 0, 0
                ps_merge00 c, b, a
                psq_st a, 24(in), 0, 0
                psq_st c, 0(in), 0, 0
                psq_st c, 16(in), 0, 0
            }

            in->mEntries.tbl[2][2] = b;
        }

        void MTX34ToMTX33(register MTX33 *pOut, register const MTX34 *pIn)
        {
            register f32 a, b, c, d, e, f;
            asm
            {
                psq_l a, 0(pIn), 0, 0
                psq_l b, 8(pIn), 0, 0
                psq_l c, 16(pIn), 0, 0
                psq_l d, 24(pIn), 0, 0
                psq_l e, 32(pIn), 0, 0
                psq_l f, 40(pIn), 0, 0
                psq_st a, 0(pOut), 0, 0
                psq_st b, 8(pOut), 1, 0
                psq_st c, 12(pOut), 0, 0
                psq_st d, 20(pOut), 1, 0
                psq_st e, 24(pOut), 0, 0
                psq_st f, 32(pOut), 1, 0
            }
        }

        asm int MTX34InvTranspose(register MTX33 *mtx33, register const MTX34 *mtx34)
        {
            nofralloc

            psq_l f0, 0(mtx34), 1, 0
            psq_l f1, 4(mtx34), 0, 0
            psq_l f2, 16(mtx34), 1, 0
            ps_merge10 f6, f1, f0
            psq_l f3, 20(mtx34), 0, 0
            psq_l f4, 32(mtx34), 1, 0
            ps_merge10 f7, f3, f2
            psq_l f5, 36(mtx34), 0, 0
            ps_mul f11, f3, f6
            ps_merge10 f8, f5, f4
            ps_mul f13, f5, f7
            ps_msub f11, f1, f7, f11
            ps_mul f12, f1, f8
            ps_msub f13, f3, f8, f13
            ps_msub f12, f5, f6, f12
            ps_mul f10, f3, f4
            ps_mul f9, f0, f5
            ps_mul f8, f1, f2
            ps_msub f10, f2, f5, f10
            ps_msub f9, f1, f4, f9
            ps_msub f8, f0, f3, f8
            ps_mul f7, f0, f13
            ps_sub f1, f1, f1
            ps_madd f7, f2, f12, f7
            ps_madd f7, f4, f11, f7
            ps_cmpo0 cr0, f7, f1
            bne label
            li r3, 0
            blr 

            label:
            fres f0, f7
            ps_add f6, f0, f0
            ps_mul f5, f0, f0
            ps_nmsub f0, f7, f5, f6
            ps_add f6, f0, f0
            ps_mul f5, f0, f0
            ps_nmsub f0, f7, f5, f6
            ps_muls0 f13, f13, f0
            ps_muls0 f12, f12, f0
            psq_st f13, 0(mtx33), 0, 0
            ps_muls0 f11, f11, f0
            psq_st f12, 12(mtx33), 0, 0
            ps_muls0 f10, f10, f0
            psq_st f11, 24(mtx33), 0, 0
            ps_muls0 f9, f9, f0
            psq_st f10, 8(mtx33), 1, 0
            ps_muls0 f8, f8, f0
            psq_st f9, 20(mtx33), 1, 0
            psq_st f8, 32(mtx33), 1, 0
            li r3, 1
            blr
        }

        void MTX34Zero(register MTX34 *in)
        {
            register f32 a = 0.0f;
            asm
            {
                psq_st a, 0(in), 0, 0
                psq_st a, 8(in), 0, 0
                psq_st a, 16(in), 0, 0
                psq_st a, 24(in), 0, 0
                psq_st a, 32(in), 0, 0
                psq_st a, 40(in), 0, 0
            }
        }

        void MTX34Scale(register MTX34 *out, register const MTX34 *inMtx, register const VEC3 *inVec)
        {
            register f32 a, b, c, d, e, f, g;
            asm
            {
                psq_l a, 0(inVec), 0, 0
                psq_l c, 0(inMtx), 0, 0
                psq_l e, 16(inMtx), 0, 0
                psq_l f, 32(inMtx), 0, 0
                ps_mul c, c, a
                ps_mul e, e, a
                psq_l b, 8(inVec), 1, 0
                ps_mul f, f, a
                psq_l d, 8(inMtx), 0, 0
                psq_l a, 24(inMtx), 0, 0
                psq_l g, 40(inMtx), 0, 0
                ps_mul d, d, b
                psq_st c, 0(out), 0, 0
                ps_mul a, a, b
                ps_mul g, g, b
                psq_st e, 16(out), 0, 0
                psq_st d, 8(out), 0, 0
                psq_st a, 24(out), 0, 0
                psq_st f, 32(out), 0, 0
                psq_st g, 40(out), 0, 0
            }
        }

        void MTX34Trans(register MTX34 *out, register const MTX34 *inMtx, register const VEC3 *inVec)
        {
            register f32 a, b, c, d, e, f, g, h, i, j, k;
            asm
            {
                psq_l c, 0(inMtx), 0, 0
                psq_l a, 0(inVec), 0, 0
                psq_l d, 8(inMtx), 0, 0
                psq_l e, 16(inMtx), 0, 0
                ps_mul i, c, a
                psq_l b, 8(inVec), 1, 0
                psq_l f, 24(inMtx), 0, 0
                ps_madd j, d, b, i
                psq_l g, 32(inMtx), 0, 0
                ps_mul i, e, a
                psq_l h, 40(inMtx), 0, 0
                psq_st d, 8(out), 0, 0
                ps_sum0 k, j, k, j
                ps_madd j, f, b, i
                psq_st f, 24(out), 0, 0
                ps_mul i, g, a
                psq_st k, 12(out), 1, 0
                ps_sum0 k, j, k, j
                ps_madd j, h, b, i
                psq_st h, 40(out), 0, 0
                psq_st k, 28(out), 1, 0
                ps_sum0 k, j, k, j
                psq_st c, 0(out), 0, 0
                psq_st e, 16(out), 0, 0
                psq_st g, 32(out), 0, 0
                psq_st k, 44(out), 1, 0  
            }
        }

        MTX34 * MTX34RotAxisFIdx(MTX34 *pMtx, const VEC3 *pVec, f32 angle)
        {
            PSMTXRotAxisRad(*pMtx, *pVec, NW4R_BRAD_TO_RAD * angle);
            return pMtx;
        }

        MTX34 * MTX34RotXYZFIdx(MTX34 *pMtx, f32 x, f32 y, f32 z)
        {
            f32 sx, cx, sy, cy, sz, cz;
            SinCosFIdx(&sx, &cx, x);
            SinCosFIdx(&sy, &cy, y);
            SinCosFIdx(&sz, &cz, z);

            pMtx->mEntries.tbl[2][0] = -sy;
            pMtx->mEntries.tbl[0][0] = cz * cy;
            pMtx->mEntries.tbl[1][0] = sz * cy;
            pMtx->mEntries.tbl[2][1] = cy * sx;
            pMtx->mEntries.tbl[2][2] = cy * cx;

            f32 temp, temp2;
            temp = cx * sz;
            temp2 = sx * cz;
            pMtx->mEntries.tbl[0][1] = temp2 * sy - temp;
            pMtx->mEntries.tbl[1][2] = temp * sy - temp2;

            f32 temp3, temp4;
            temp3 = sx * sz;
            temp4 = cx * cz;
            pMtx->mEntries.tbl[0][2] = temp4 * sy + temp3;
            pMtx->mEntries.tbl[1][1] = temp3 * sy + temp4;
            pMtx->mEntries.tbl[0][3] = 0.0f;
            pMtx->mEntries.tbl[1][3] = 0.0f;
            pMtx->mEntries.tbl[2][3] = 0.0f;

            return pMtx;
        }

        VEC3 * VEC3TransformNormal(VEC3 *pOut, const MTX34 *pMtx, const VEC3 *pVec)
        {
            VEC3 stack_0x8;
            stack_0x8.mCoords.x = pMtx->mEntries.tbl[0][0] * pVec->mCoords.x
                + pMtx->mEntries.tbl[0][1] * pVec->mCoords.y
                + pMtx->mEntries.tbl[0][2] * pVec->mCoords.z;
                
            stack_0x8.mCoords.y = pMtx->mEntries.tbl[1][0] * pVec->mCoords.x
                + pMtx->mEntries.tbl[1][1] * pVec->mCoords.y
                + pMtx->mEntries.tbl[1][2] * pVec->mCoords.z;

            stack_0x8.mCoords.z = pMtx->mEntries.tbl[2][0] * pVec->mCoords.x
                + pMtx->mEntries.tbl[2][1] * pVec->mCoords.y
                + pMtx->mEntries.tbl[2][2] * pVec->mCoords.z;

            *pOut = stack_0x8;
            return pOut;
        }

        void MTX44Identity(register MTX44 *pMtx)
        {
            register f32 a, b, c;
            a = 0.0f;
            b = 1.0f;
            asm
            {
                psq_st a, 8(pMtx), 0, 0
                ps_merge01 c, a, b
                ps_merge10 b, b, a
                psq_st a, 24(pMtx), 0, 0
                psq_st a, 32(pMtx), 0, 0
                psq_st c, 16(pMtx), 0, 0
                psq_st b, 0(pMtx), 0, 0
                psq_st b, 40(pMtx), 0, 0
                psq_st a, 48(pMtx), 0, 0
                psq_st c, 56(pMtx), 0, 0
            }
        }

        void MTX44Copy(register MTX44 *pDest, register const MTX44 *pSrc)
        {
            register f32 a, b, c, d, e, f, g, i;
            asm
            {
                psq_l a, 0(pSrc), 0, 0
                psq_l b, 8(pSrc), 0, 0
                psq_l c, 16(pSrc), 0, 0
                psq_l d, 24(pSrc), 0, 0
                psq_l e, 32(pSrc), 0, 0
                psq_l f, 40(pSrc), 0, 0
                psq_l g, 48(pSrc), 0, 0
                psq_l i, 56(pSrc), 0, 0
                psq_st a, 0(pDest), 0, 0
                psq_st b, 8(pDest), 0, 0
                psq_st c, 16(pDest), 0, 0
                psq_st d, 24(pDest), 0, 0
                psq_st e, 32(pDest), 0, 0
                psq_st f, 40(pDest), 0, 0
                psq_st g, 48(pDest), 0, 0
                psq_st i, 56(pDest), 0, 0
            }
        }
    }
}