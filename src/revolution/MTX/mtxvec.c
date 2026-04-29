#include <revolution/MTX.h>
#include <revolution/MTX/internal/mtxAssert.h>
#include <revolution/OS.h>

void C_MTXMultVec(CMtxPtr m, CVecPtr src, VecPtr dst) {
    Vec vTmp;

    OS_DEBUG_ASSERT(m, "MTXMultVec():  NULL MtxPtr 'm' ");
    OS_DEBUG_ASSERT(src, "MTXMultVec():  NULL VecPtr 'src' ");
    OS_DEBUG_ASSERT(dst, "MTXMultVec():  NULL VecPtr 'dst' ");

    vTmp.x = m[0][0] * src->x + m[0][1] * src->y + m[0][2] * src->z + m[0][3];
    vTmp.y = m[1][0] * src->x + m[1][1] * src->y + m[1][2] * src->z + m[1][3];
    vTmp.z = m[2][0] * src->x + m[2][1] * src->y + m[2][2] * src->z + m[2][3];

    dst->x = vTmp.x;
    dst->y = vTmp.y;
    dst->z = vTmp.z;
}

asm void PSMTXMultVec(register CMtxPtr m, register CVecPtr src,
                      register VecPtr dst) {
    nofralloc;

    psq_l f0, Vec.x(src), 0, qr0;
    psq_l f2, Mtx_00(m), 0, qr0;
    psq_l f1, Vec.z(src), 1, qr0;
    ps_mul f4, f2, f0;
    psq_l f3, Mtx_02(m), 0, qr0;
    ps_madd f5, f3, f1, f4;
    psq_l f8, Mtx_10(m), 0, qr0;
    ps_sum0 f6, f5, f6, f5;
    psq_l f9, Mtx_12(m), 0, qr0;
    ps_mul f10, f8, f0;
    psq_st f6, Vec.x(dst), 1, qr0;
    ps_madd f11, f9, f1, f10;
    psq_l f2, Mtx_20(m), 0, qr0;
    ps_sum0 f12, f11, f12, f11;
    psq_l f3, Mtx_22(m), 0, qr0;
    ps_mul f4, f2, f0;
    psq_st f12, Vec.y(dst), 1, qr0;
    ps_madd f5, f3, f1, f4;
    ps_sum0 f6, f5, f6, f5;
    psq_st f6, Vec.z(dst), 1, qr0;

    blr;
}

void C_MTXMultVecArray(CMtxPtr m, CVecPtr srcBase, VecPtr dstBase, u32 count) {
    u32 i;
    Vec vTmp;

    OS_DEBUG_ASSERT(m, "MTXMultVecArray():  NULL MtxPtr 'm' ");
    OS_DEBUG_ASSERT(srcBase, "MTXMultVecArray():  NULL VecPtr 'srcBase' ");
    OS_DEBUG_ASSERT(dstBase, "MTXMultVecArray():  NULL VecPtr 'dstBase' ");
    OS_DEBUG_ASSERT(count > 1, "MTXMultVecArray():  count must be greater than 1.");

    for (i = 0; i < count; ++i) {
        vTmp.x = m[0][0] * srcBase->x + m[0][1] * srcBase->y +
                 m[0][2] * srcBase->z + m[0][3];
        vTmp.y = m[1][0] * srcBase->x + m[1][1] * srcBase->y +
                 m[1][2] * srcBase->z + m[1][3];
        vTmp.z = m[2][0] * srcBase->x + m[2][1] * srcBase->y +
                 m[2][2] * srcBase->z + m[2][3];

        dstBase->x = vTmp.x;
        dstBase->y = vTmp.y;
        dstBase->z = vTmp.z;

        ++srcBase;
        ++dstBase;
    }
}

asm void PSMTXMultVecArray(register CMtxPtr m, register CVecPtr srcBase,
                           register VecPtr dstBase, register u32 count) {
    nofralloc;

    psq_l f13, Mtx_00(m), 0, qr0;
    psq_l f12, Mtx_10(m), 0, qr0;
    subi count, count, 0x1;
    psq_l f11, Mtx_02(m), 0, qr0;
    ps_merge00 f0, f13, f12;
    subi dstBase, dstBase, 0x4;
    psq_l f10, Mtx_12(m), 0, qr0;
    ps_merge11 f1, f13, f12;
    mtctr count;
    psq_l f4, Mtx_20(m), 0, qr0;
    ps_merge00 f2, f11, f10;
    psq_l f5, Mtx_22(m), 0, qr0;
    ps_merge11 f3, f11, f10;
    psq_l f6, Vec.x(srcBase), 0, qr0;
    psq_lu f7, Vec.z(srcBase), 1, qr0;
    ps_madds0 f8, f0, f6, f3;
    ps_mul f9, f4, f6;
    ps_madds1 f8, f1, f6, f8;
    ps_madd f10, f5, f7, f9;

// Don't use Vec offsets here, they're not accurate
loop:
    psq_lu f6, 0x4(srcBase), 0, qr0;
    ps_madds0 f12, f2, f7, f8;
    psq_lu f7, 0x8(srcBase), 1, qr0;
    ps_sum0 f13, f10, f9, f10;
    ps_madds0 f8, f0, f6, f3;
    ps_mul f9, f4, f6;
    psq_stu f12, 0x4(dstBase), 0, qr0;
    ps_madds1 f8, f1, f6, f8;
    psq_stu f13, 0x8(dstBase), 1, qr0;
    ps_madd f10, f5, f7, f9;
    bdnz loop;

    ps_madds0 f12, f2, f7, f8;
    ps_sum0 f13, f10, f9, f10;
    psq_stu f12, 0x4(dstBase), 0, qr0;
    psq_stu f13, 0x8(dstBase), 1, qr0;

    blr;
}

void C_MTXMultVecSR(CMtxPtr m, CVecPtr src, VecPtr dst) {
    Vec vTmp;

    OS_DEBUG_ASSERT(m, "MTXMultVecSR():  NULL MtxPtr 'm' ");
    OS_DEBUG_ASSERT(src, "MTXMultVecSR():  NULL VecPtr 'src' ");
    OS_DEBUG_ASSERT(dst, "MTXMultVecSR():  NULL VecPtr 'dst' ");

    vTmp.x = m[0][0] * src->x + m[0][1] * src->y + m[0][2] * src->z;
    vTmp.y = m[1][0] * src->x + m[1][1] * src->y + m[1][2] * src->z;
    vTmp.z = m[2][0] * src->x + m[2][1] * src->y + m[2][2] * src->z;

    dst->x = vTmp.x;
    dst->y = vTmp.y;
    dst->z = vTmp.z;
}

asm void PSMTXMultVecSR(register CMtxPtr m, register CVecPtr src,
                        register VecPtr dst) {
    nofralloc;

    psq_l f0, Mtx_00(m), 0, qr0;
    psq_l f6, Vec.x(src), 0, qr0;
    psq_l f2, Mtx_10(m), 0, qr0;
    ps_mul f8, f0, f6;
    psq_l f4, Mtx_20(m), 0, qr0;
    ps_mul f10, f2, f6;
    psq_l f7, Vec.z(src), 1, qr0;
    ps_mul f12, f4, f6;
    psq_l f3, Mtx_12(m), 0, qr0;
    ps_sum0 f8, f8, f8, f8;
    psq_l f5, Mtx_22(m), 0, qr0;
    ps_sum0 f10, f10, f10, f10;
    psq_l f1, Mtx_02(m), 0, qr0;
    ps_sum0 f12, f12, f12, f12;
    ps_madd f9, f1, f7, f8;
    psq_st f9, Vec.x(dst), 1, qr0;
    ps_madd f11, f3, f7, f10;
    psq_st f11, Vec.y(dst), 1, qr0;
    ps_madd f13, f5, f7, f12;
    psq_st f13, Vec.z(dst), 1, qr0;

    blr;
}

void C_MTXMultVecArraySR(CMtxPtr m, CVecPtr srcBase, VecPtr dstBase,
                         u32 count) {
    u32 i;
    Vec vTmp;

    OS_DEBUG_ASSERT(m, "MTXMultVecArraySR():  NULL MtxPtr 'm' ");
    OS_DEBUG_ASSERT(srcBase, "MTXMultVecArraySR():  NULL VecPtr 'srcBase' ");
    OS_DEBUG_ASSERT(dstBase, "MTXMultVecArraySR():  NULL VecPtr 'dstBase' ");
    OS_DEBUG_ASSERT(count > 1, "MTXMultVecArraySR():  count must be greater than 1.");

    for (i = 0; i < count; ++i) {
        vTmp.x =
            m[0][0] * srcBase->x + m[0][1] * srcBase->y + m[0][2] * srcBase->z;
        vTmp.y =
            m[1][0] * srcBase->x + m[1][1] * srcBase->y + m[1][2] * srcBase->z;
        vTmp.z =
            m[2][0] * srcBase->x + m[2][1] * srcBase->y + m[2][2] * srcBase->z;

        dstBase->x = vTmp.x;
        dstBase->y = vTmp.y;
        dstBase->z = vTmp.z;

        ++srcBase;
        ++dstBase;
    }
}

asm void PSMTXMultVecArraySR(register CMtxPtr m, register CVecPtr srcBase,
                             register VecPtr dstBase, register u32 count) {
    nofralloc;

    psq_l f13, Mtx_00(m), 0, qr0;
    psq_l f12, Mtx_10(m), 0, qr0;
    subi count, count, 0x1;
    psq_l f11, Mtx_02(m), 1, qr0;
    ps_merge00 f0, f13, f12;
    subi dstBase, dstBase, 0x4;
    psq_l f10, Mtx_12(m), 1, qr0;
    ps_merge11 f1, f13, f12;
    mtctr count;
    psq_l f3, Mtx_20(m), 0, qr0;
    ps_merge00 f2, f11, f10;
    psq_l f4, Mtx_22(m), 1, qr0;
    psq_l f6, Vec.x(srcBase), 0, qr0;
    psq_lu f7, Vec.z(srcBase), 1, qr0;
    ps_muls0 f8, f0, f6;
    ps_mul f9, f3, f6;
    ps_madds1 f8, f1, f6, f8;
    ps_madd f10, f4, f7, f9;

// Don't use Vec offsets here, they're not accurate
loop:
    psq_lu f6, 0x4(srcBase), 0, qr0;
    ps_madds0 f12, f2, f7, f8;
    psq_lu f7, 0x8(srcBase), 1, qr0;
    ps_sum0 f13, f10, f9, f9;
    ps_muls0 f8, f0, f6;
    ps_mul f9, f3, f6;
    psq_stu f12, 0x4(dstBase), 0, qr0;
    ps_madds1 f8, f1, f6, f8;
    psq_stu f13, 0x8(dstBase), 1, qr0;
    ps_madd f10, f4, f7, f9;
    bdnz loop;

    ps_madds0 f12, f2, f7, f8;
    ps_sum0 f13, f10, f9, f9;
    psq_stu f12, 0x4(dstBase), 0, qr0;
    psq_stu f13, 0x8(dstBase), 1, qr0;

    blr;
}
