#include <revolution/MTX.h>
#include <revolution/MTX/internal/mtxAssert.h>

asm void PSMTXReorder(register CMtxPtr src, register ROMtxPtr dst) {
    nofralloc;

    psq_l f0, Mtx_00(src), 0, qr0;
    psq_l f2, Mtx_10(src), 0, qr0;
    psq_l f4, Mtx_20(src), 0, qr0;
    psq_l f1, Mtx_02(src), 0, qr0;
    ps_merge00 f6, f0, f2;
    psq_l f3, Mtx_12(src), 0, qr0;
    ps_merge01 f12, f4, f0;
    psq_l f5, Mtx_22(src), 0, qr0;
    ps_merge11 f7, f2, f4;
    psq_st f6, ROMtx_00(dst), 0, qr0;
    ps_merge00 f8, f1, f3;
    psq_st f12, ROMtx_02(dst), 0, qr0;
    ps_merge01 f9, f5, f1;
    psq_st f7, ROMtx_11(dst), 0, qr0;
    ps_merge11 f10, f3, f5;
    psq_st f8, ROMtx_20(dst), 0, qr0;
    psq_st f9, ROMtx_22(dst), 0, qr0;
    psq_st f10, ROMtx_31(dst), 0, qr0;

    blr;
}

asm void PSMTXROMultVecArray(register CROMtxPtr m, register CVecPtr srcBase,
                             register VecPtr dstBase, register u32 count) {
    // Don't use Vec for offsets, they're always updated on load/store
    nofralloc;

    stwu sp, -0x60(sp);
    stfd f14, 0x8(sp);
    psq_st f14, 0x10(sp), 0, qr0;
    subi r7, count, 0x1;
    stfd f15, 0x18(sp);
    psq_st f15, 0x20(sp), 0, qr0;
    srwi r7, r7, 0x1;
    stfd f16, 0x28(sp);
    psq_st f16, 0x30(sp), 0, qr0;
    stfd f17, 0x38(sp);
    psq_st f17, 0x40(sp), 0, qr0;
    stfd f18, 0x48(sp);
    psq_st f18, 0x50(sp), 0, qr0;
    mtctr r7;
    psq_l f0, ROMtx_00(m), 0, qr0;
    subi srcBase, srcBase, 0x8;
    psq_l f1, ROMtx_02(m), 1, qr0;
    subi dstBase, dstBase, 0x4;
    psq_l f6, ROMtx_30(m), 0, qr0;
    psq_lu f8, 0x8(srcBase), 0, qr0;
    psq_l f7, ROMtx_32(m), 1, qr0;
    psq_lu f9, 0x8(srcBase), 0, qr0;
    ps_madds0 f11, f0, f8, f6;
    psq_l f2, ROMtx_10(m), 0, qr0;
    ps_madds0 f12, f1, f8, f7;
    psq_l f3, ROMtx_12(m), 1, qr0;
    ps_madds1 f13, f0, f9, f6;
    psq_lu f10, 0x8(srcBase), 0, qr0;
    ps_madds1 f14, f1, f9, f7;
    psq_l f5, ROMtx_22(m), 1, qr0;
    ps_madds1 f11, f2, f8, f11;
    ps_madds1 f12, f3, f8, f12;
    psq_l f4, ROMtx_20(m), 0, qr0;
    ps_madds0 f13, f2, f10, f13;
    psq_lu f8, 0x8(srcBase), 0, qr0;
    ps_madds0 f14, f3, f10, f14;
    ps_madds0 f15, f4, f9, f11;
    ps_madds0 f16, f5, f9, f12;
    psq_lu f9, 0x8(srcBase), 0, qr0;
    ps_madds1 f17, f4, f10, f13;
    ps_madds1 f18, f5, f10, f14;
    psq_lu f10, 0x8(srcBase), 0, qr0;
loop:
    ps_madds0 f11, f0, f8, f6;
    psq_stu f15, 0x4(dstBase), 0, qr0;
    ps_madds0 f12, f1, f8, f7;
    psq_stu f16, 0x8(dstBase), 1, qr0;
    ps_madds1 f13, f0, f9, f6;
    psq_stu f17, 0x4(dstBase), 0, qr0;
    ps_madds1 f14, f1, f9, f7;
    psq_stu f18, 0x8(dstBase), 1, qr0;
    ps_madds1 f11, f2, f8, f11;
    ps_madds1 f12, f3, f8, f12;
    psq_lu f8, 0x8(srcBase), 0, qr0;
    ps_madds0 f13, f2, f10, f13;
    ps_madds0 f14, f3, f10, f14;
    ps_madds0 f15, f4, f9, f11;
    ps_madds0 f16, f5, f9, f12;
    psq_lu f9, 0x8(srcBase), 0, qr0;
    ps_madds1 f17, f4, f10, f13;
    ps_madds1 f18, f5, f10, f14;
    psq_lu f10, 0x8(srcBase), 0, qr0;
    bdnz loop;

    psq_stu f15, 0x4(dstBase), 0, qr0;

    // It wants to format "clrlwi. r7" with no whitespace
    // clang-format off
    clrlwi. r7, count, 0x1f;
    // clang-format on

    psq_stu f16, 0x8(dstBase), 1, qr0;
    bne epilogue;
    psq_stu f17, 0x4(dstBase), 0, qr0;
    psq_stu f18, 0x8(dstBase), 1, qr0;
epilogue:
    psq_l f14, 0x10(sp), 0, qr0;
    lfd f14, 0x8(sp);
    psq_l f15, 0x20(sp), 0, qr0;
    lfd f15, 0x18(sp);
    psq_l f16, 0x30(sp), 0, qr0;
    lfd f16, 0x28(sp);
    psq_l f17, 0x40(sp), 0, qr0;
    lfd f17, 0x38(sp);
    psq_l f18, 0x50(sp), 0, qr0;
    lfd f18, 0x48(sp);
    addi sp, sp, 0x60;
    blr;
}
