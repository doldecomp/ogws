#include <revolution/MTX.h>
#include <revolution/MTX/internal/mtxAssert.h>

#include <math.h>

static f32 Unit01[] = {0.0f, 1.0f};

// Keep for float ordering
void C_MTXIdentity(MtxPtr m) {
    m[0][0] = 1.0f;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = 1.0f;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = 1.0f;
    m[2][3] = 0.0f;
}

void PSMTXIdentity(register MtxPtr m) {
    register f32 c_zero = 0.0f;
    register f32 c_one = 1.0f;
    register f32 c_01;
    register f32 c_10;

    // clang-format off
    asm {
        psq_st c_zero, Mtx_02(m), 0, qr0
        ps_merge01 c_01, c_zero, c_one
        psq_st c_zero, Mtx_12(m), 0, qr0
        ps_merge10 c_10, c_one, c_zero
        psq_st c_zero, Mtx_20(m), 0, qr0

        psq_st c_01, Mtx_10(m), 0, qr0
        psq_st c_10, Mtx_00(m), 0, qr0
        psq_st c_10, Mtx_22(m), 0, qr0
    } // clang-format on
}

// clang-format off
asm void PSMTXCopy(register CMtxPtr src, register MtxPtr dst) {
    psq_l f0, Mtx_00(src), 0, qr0
    psq_st f0, Mtx_00(dst), 0, qr0
    psq_l f1, Mtx_02(src), 0, qr0
    psq_st f1, Mtx_02(dst), 0, qr0
    psq_l f2, Mtx_10(src), 0, qr0
    psq_st f2, Mtx_10(dst), 0, qr0
    psq_l f3, Mtx_12(src), 0, qr0
    psq_st f3, Mtx_12(dst), 0, qr0
    psq_l f4, Mtx_20(src), 0, qr0
    psq_st f4, Mtx_20(dst), 0, qr0
    psq_l f5, Mtx_22(src), 0, qr0
    psq_st f5, Mtx_22(dst), 0, qr0
} // clang-format on

// clang-format off
asm void PSMTXConcat(register CMtxPtr mA, register CMtxPtr mB,
                     register MtxPtr mAB) {
    nofralloc

    stwu sp, -0x40(sp)
    psq_l f0, Mtx_00(mA), 0, qr0
    stfd f14, 0x8(sp)
    psq_l f6, Mtx_00(mB), 0, qr0
    lis r6, Unit01@ha
    psq_l f7, Mtx_02(mB), 0, qr0
    stfd f15, 0x10(sp)
    addi r6, r6, Unit01@l
    stfd f31, 0x28(sp)
    psq_l f8, Mtx_10(mB), 0, qr0
    ps_muls0 f12, f6, f0
    psq_l f2, Mtx_10(mA), 0, qr0
    ps_muls0 f13, f7, f0
    psq_l f31, 0x0(r6), 0, qr0
    ps_muls0 f14, f6, f2
    psq_l f9, Mtx_12(mB), 0, qr0
    ps_muls0 f15, f7, f2
    psq_l f1, Mtx_02(mA), 0, qr0
    ps_madds1 f12, f8, f0, f12
    psq_l f3, Mtx_12(mA), 0, qr0
    ps_madds1 f14, f8, f2, f14
    psq_l f10, Mtx_20(mB), 0, qr0
    ps_madds1 f13, f9, f0, f13
    psq_l f11, Mtx_22(mB), 0, qr0
    ps_madds1 f15, f9, f2, f15
    psq_l f4, Mtx_20(mA), 0, qr0
    psq_l f5, Mtx_22(mA), 0, qr0
    ps_madds0 f12, f10, f1, f12
    ps_madds0 f13, f11, f1, f13
    ps_madds0 f14, f10, f3, f14
    ps_madds0 f15, f11, f3, f15
    psq_st f12, Mtx_00(mAB), 0, qr0
    ps_muls0 f2, f6, f4
    ps_madds1 f13, f31, f1, f13
    ps_muls0 f0, f7, f4
    psq_st f14, Mtx_10(mAB), 0, qr0
    ps_madds1 f15, f31, f3, f15
    psq_st f13, Mtx_02(mAB), 0, qr0
    ps_madds1 f2, f8, f4, f2
    ps_madds1 f0, f9, f4, f0
    ps_madds0 f2, f10, f5, f2
    lfd f14, 0x8(sp)
    psq_st f15, Mtx_12(mAB), 0, qr0
    ps_madds0 f0, f11, f5, f0
    psq_st f2, Mtx_20(mAB), 0, qr0
    ps_madds1 f0, f31, f5, f0
    lfd f15, 0x10(sp)
    psq_st f0, Mtx_22(mAB), 0, qr0
    lfd f31, 0x28(sp)
    addi sp, sp, 0x40

    blr
} // clang-format on

void PSMTXConcatArray(register CMtxPtr a, register CMtxPtr srcBase,
                      register MtxPtr dstBase, register u32 count) {
    register f32 a00;
    register f32 a02;
    register f32 a10;
    register f32 a12;
    register f32 a20;
    register f32 a22;
    register f32 s00;
    register f32 s02;
    register f32 s10;
    register f32 s12;
    register f32 s20;
    register f32 s22;
    register f32 d00;
    register f32 d02;
    register f32 d10;
    register f32 d12;
    register f32 d20;
    register f32 d22;
    register f32 unit;
    register f32* pUnit = Unit01;

    // clang-format off
    asm {
        psq_l a00, Mtx_00(a), 0, qr0
        psq_l a02, Mtx_02(a), 0, qr0
        psq_l a10, Mtx_10(a), 0, qr0
        psq_l a12, Mtx_12(a), 0, qr0
        subi count, count, 1
        psq_l a20, Mtx_20(a), 0, qr0
        psq_l a22, Mtx_22(a), 0, qr0
        mtctr count
        psq_l unit, 0x0(pUnit), 0, qr0
        psq_l s00, Mtx_00(srcBase), 0, qr0
        psq_l s10, Mtx_10(srcBase), 0, qr0
        ps_muls0 d00, s00, a00
        ps_muls0 d10, s00, a10
        ps_muls0 d20, s00, a20
        psq_l s20, Mtx_20(srcBase), 0, qr0
        ps_madds1 d00, s10, a00, d00
        ps_madds1 d10, s10, a10, d10
        ps_madds1 d20, s10, a20, d20
        psq_l s02, Mtx_02(srcBase), 0, qr0
        ps_madds0 d00, s20, a02, d00
        ps_madds0 d10, s20, a12, d10
        ps_madds0 d20, s20, a22, d20
        psq_l s12, Mtx_12(srcBase), 0, qr0
        psq_st d00, Mtx_00(dstBase), 0, qr0
        ps_muls0 d02, s02, a00
        ps_muls0 d12, s02, a10
        ps_muls0 d22, s02, a20
        psq_l s22, Mtx_22(srcBase), 0, qr0
        psq_st d10, Mtx_10(dstBase), 0, qr0
        ps_madds1 d02, s12, a00, d02
        ps_madds1 d12, s12, a10, d12
        ps_madds1 d22, s12, a20, d22
    loop:
        addi srcBase, srcBase, sizeof(Mtx)
        ps_madds0 d02, s22, a02, d02
        ps_madds0 d12, s22, a12, d12
        ps_madds0 d22, s22, a22, d22
        psq_l s00, Mtx_00(srcBase), 0, qr0
        psq_st d20, Mtx_20(dstBase), 0, qr0
        ps_madd d02, unit, a02, d02
        ps_madd d12, unit, a12, d12
        ps_madd d22, unit, a22, d22
        psq_l s10, Mtx_10(srcBase), 0, qr0
        psq_st d02, Mtx_02(dstBase), 0, qr0
        ps_muls0 d00, s00, a00
        ps_muls0 d10, s00, a10
        ps_muls0 d20, s00, a20
        psq_l s20, Mtx_20(srcBase), 0, qr0
        psq_st d12, Mtx_12(dstBase), 0, qr0
        ps_madds1 d00, s10, a00, d00
        ps_madds1 d10, s10, a10, d10
        ps_madds1 d20, s10, a20, d20
        psq_l s02, Mtx_02(srcBase), 0, qr0
        psq_st d22, Mtx_22(dstBase), 0, qr0
        addi dstBase, dstBase, sizeof(Mtx)
        ps_madds0 d00, s20, a02, d00
        ps_madds0 d10, s20, a12, d10
        ps_madds0 d20, s20, a22, d20
        psq_l s12, Mtx_12(srcBase), 0, qr0
        psq_st d00, Mtx_00(dstBase), 0, qr0
        ps_muls0 d02, s02, a00
        ps_muls0 d12, s02, a10
        ps_muls0 d22, s02, a20
        psq_l s22, Mtx_22(srcBase), 0, qr0
        psq_st d10, Mtx_10(dstBase), 0, qr0
        ps_madds1 d02, s12, a00, d02
        ps_madds1 d12, s12, a10, d12
        ps_madds1 d22, s12, a20, d22
        bdnz loop
        psq_st d20, Mtx_20(dstBase), 0, qr0
        ps_madds0 d02, s22, a02, d02
        ps_madds0 d12, s22, a12, d12
        ps_madds0 d22, s22, a22, d22
        ps_madd d02, unit, a02, d02
        ps_madd d12, unit, a12, d12
        ps_madd d22, unit, a22, d22
        psq_st d02, Mtx_02(dstBase), 0, qr0
        psq_st d12, Mtx_12(dstBase), 0, qr0
        psq_st d22, Mtx_22(dstBase), 0, qr0
    } // clang-format on
}

void PSMTXTranspose(register CMtxPtr src, register MtxPtr xPose) {
    register f32 c_zero = 0.0f;
    register f32 row0a;
    register f32 row1a;
    register f32 row0b;
    register f32 row1b;
    register f32 trns0;
    register f32 trns1;
    register f32 trns2;

    // clang-format off
    asm {
        psq_l row0a, Mtx_00(src), 0, qr0
        stfs c_zero, Mtx_23(xPose)
        psq_l row1a, Mtx_10(src), 0, qr0
        ps_merge00 trns0, row0a, row1a
        psq_l row0b, Mtx_02(src), 1, qr0
        ps_merge11 trns1, row0a, row1a
        psq_l row1b, Mtx_12(src), 1, qr0
        psq_st trns0, Mtx_00(xPose), 0, qr0
        psq_l row0a, Mtx_20(src), 0, qr0
        ps_merge00 trns2, row0b, row1b
        psq_st trns1, Mtx_10(xPose), 0, qr0
        ps_merge00 trns0, row0a, c_zero
        psq_st trns2, Mtx_20(xPose), 0, qr0
        ps_merge10 trns1, row0a, c_zero
        psq_st trns0, Mtx_02(xPose), 0, qr0
        lfs row0b, Mtx_22(src)
        psq_st trns1, Mtx_12(xPose), 0, qr0
        stfs row0b, Mtx_22(xPose)
    } // clang-format on
}

// clang-format off
asm u32 PSMTXInverse(register CMtxPtr src, register MtxPtr inv) {
    psq_l f0, Mtx_00(src), 1, qr0
    psq_l f1, Mtx_01(src), 0, qr0
    psq_l f2, Mtx_10(src), 1, qr0
    ps_merge10 f6, f1, f0
    psq_l f3, Mtx_11(src), 0, qr0
    psq_l f4, Mtx_20(src), 1, qr0
    ps_merge10 f7, f3, f2
    psq_l f5, Mtx_21(src), 0, qr0
    ps_mul f11, f3, f6
    ps_mul f13, f5, f7
    ps_merge10 f8, f5, f4
    ps_msub f11, f1, f7, f11
    ps_mul f12, f1, f8
    ps_msub f13, f3, f8, f13
    ps_mul f10, f3, f4
    ps_msub f12, f5, f6, f12
    ps_mul f9, f0, f5
    ps_mul f8, f1, f2
    ps_sub f6, f6, f6
    ps_msub f10, f2, f5, f10
    ps_mul f7, f0, f13
    ps_msub f9, f1, f4, f9
    ps_madd f7, f2, f12, f7
    ps_msub f8, f0, f3, f8
    ps_madd f7, f4, f11, f7
    ps_cmpo0 cr0, f7, f6
    bne nonsingular

    li r3, 0x0
    blr

nonsingular:
    fres f0, f7
    ps_add f6, f0, f0
    ps_mul f5, f0, f0
    ps_nmsub f0, f7, f5, f6
    lfs f1, Mtx_03(src)
    ps_muls0 f13, f13, f0
    lfs f2, Mtx_13(src)
    ps_muls0 f12, f12, f0
    lfs f3, Mtx_23(src)
    ps_muls0 f11, f11, f0
    ps_merge00 f5, f13, f12
    ps_muls0 f10, f10, f0
    ps_merge11 f4, f13, f12
    ps_muls0 f9, f9, f0
    psq_st f5, Mtx_00(inv), 0, qr0
    ps_mul f6, f13, f1
    psq_st f4, Mtx_10(inv), 0, qr0
    ps_muls0 f8, f8, f0
    ps_madd f6, f12, f2, f6
    psq_st f10, Mtx_20(inv), 1, qr0
    ps_nmadd f6, f11, f3, f6
    psq_st f9, Mtx_21(inv), 1, qr0
    ps_mul f7, f10, f1
    ps_merge00 f5, f11, f6
    psq_st f8, Mtx_22(inv), 1, qr0
    ps_merge11 f4, f11, f6
    psq_st f5, Mtx_02(inv), 0, qr0
    ps_madd f7, f9, f2, f7
    psq_st f4, Mtx_12(inv), 0, qr0
    ps_nmadd f7, f8, f3, f7
    li r3, 0x1
    psq_st f7, Mtx_23(inv), 1, qr0
    blr
} // clang-format on

// clang-format off
asm u32 PSMTXInvXpose(register CMtxPtr src, register MtxPtr invX) {
    psq_l f0, Mtx_00(src), 1, qr0
    psq_l f1, Mtx_01(src), 0, qr0
    psq_l f2, Mtx_10(src), 1, qr0
    ps_merge10 f6, f1, f0
    psq_l f3, Mtx_11(src), 0, qr0
    psq_l f4, Mtx_20(src), 1, qr0
    ps_merge10 f7, f3, f2
    psq_l f5, Mtx_21(src), 0, qr0
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
    bne nonsingular

    li r3, 0x0
    blr

nonsingular:
    fres f0, f7
    psq_st f1, Mtx_03(invX), 1, qr0
    ps_add f6, f0, f0
    ps_mul f5, f0, f0
    psq_st f1, Mtx_13(invX), 1, qr0
    ps_nmsub f0, f7, f5, f6
    psq_st f1, Mtx_23(invX), 1, qr0
    ps_muls0 f13, f13, f0
    ps_muls0 f12, f12, f0
    ps_muls0 f11, f11, f0
    psq_st f13, Mtx_00(invX), 0, qr0
    psq_st f12, Mtx_10(invX), 0, qr0
    ps_muls0 f10, f10, f0
    ps_muls0 f9, f9, f0
    psq_st f11, Mtx_20(invX), 0, qr0
    psq_st f10, Mtx_02(invX), 1, qr0
    ps_muls0 f8, f8, f0
    li r3, 0x1
    psq_st f9, Mtx_12(invX), 1, qr0
    psq_st f8, Mtx_22(invX), 1, qr0
    blr
} // clang-format on

void PSMTXRotRad(MtxPtr m, char axis, f32 rad) {
    f32 sinA, cosA;

    sinA = sinf(rad);
    cosA = cosf(rad);
    PSMTXRotTrig(m, axis, sinA, cosA);
}

void PSMTXRotTrig(register MtxPtr m, register char axis, register f32 sinA,
                  register f32 cosA) {
    register f32 fc0;
    register f32 fc1;
    register f32 nsinA;
    register f32 fw0;
    register f32 fw1;
    register f32 fw2;
    register f32 fw3;

    // clang-format off
    asm {
        frsp sinA, sinA
        frsp cosA, cosA
    } // clang-format on

    fc0 = 0.0f;
    fc1 = 1.0f;

    // clang-format off
    asm {
        ori axis, axis, 0x20
        ps_neg nsinA, sinA
        cmplwi axis, 'x'
        beq axis_x
        cmplwi axis, 'y'
        beq axis_y
        cmplwi axis, 'z'
        beq axis_z
        b epilogue
    axis_x:
        psq_st fc1, Mtx_00(m), 1, qr0
        psq_st fc0, Mtx_01(m), 0, qr0
        ps_merge00 fw0, sinA, cosA
        psq_st fc0, Mtx_03(m), 0, qr0
        ps_merge00 fw1, cosA, nsinA
        psq_st fc0, Mtx_13(m), 0, qr0
        psq_st fc0, Mtx_23(m), 1, qr0
        psq_st fw0, Mtx_21(m), 0, qr0
        psq_st fw1, Mtx_11(m), 0, qr0
        b epilogue
    axis_y:
        ps_merge00 fw0, cosA, fc0
        ps_merge00 fw1, fc0, fc1
        psq_st fc0, Mtx_12(m), 0, qr0
        psq_st fw0, Mtx_00(m), 0, qr0
        ps_merge00 fw2, nsinA, fc0
        ps_merge00 fw3, sinA, fc0
        psq_st fw0, Mtx_22(m), 0, qr0
        psq_st fw1, Mtx_10(m), 0, qr0
        psq_st fw3, Mtx_02(m), 0, qr0
        psq_st fw2, Mtx_20(m), 0, qr0
        b epilogue
    axis_z:
        psq_st fc0, Mtx_02(m), 0, qr0
        ps_merge00 fw0, sinA, cosA
        ps_merge00 fw2, cosA, nsinA
        psq_st fc0, Mtx_12(m), 0, qr0
        psq_st fc0, Mtx_20(m), 0, qr0
        ps_merge00 fw1, fc1, fc0
        psq_st fw0, Mtx_10(m), 0, qr0
        psq_st fw2, Mtx_00(m), 0, qr0
        psq_st fw1, Mtx_22(m), 0, qr0
    epilogue:
    }
    // clang-format on
}

// Subroutine for PSMTXRotAxisRad
// Paired singles don't have good ways of doing trig so we rely on a C caller
// DWARF merges PSMTXRotAxisRad with this so it's not perfect
static void __PSMTXRotAxisRadInternal(register MtxPtr m, register CVecPtr axis,
                                      register f32 sT, register f32 cT) {
    register f32 tT;
    register f32 fc0;
    register f32 tmp0;
    register f32 tmp1;
    register f32 tmp2;
    register f32 tmp3;
    register f32 tmp4;
    register f32 tmp5;
    register f32 tmp6;
    register f32 tmp7;
    register f32 tmp8;
    register f32 tmp9;

    tmp9 = 0.5f;
    tmp8 = 3.0f;

    // clang-format off
    asm {
        frsp cT, cT
        psq_l tmp0, Vec.x(axis), 0, qr0
        frsp sT, sT
        lfs tmp1, Vec.z(axis)
        ps_mul tmp2, tmp0, tmp0
        fadds tmp7, tmp9, tmp9
        ps_madd tmp3, tmp1, tmp1, tmp2
        fsubs fc0, tmp9, tmp9
        ps_sum0 tmp4, tmp3, tmp1, tmp2
        fsubs tT, tmp7, cT
        frsqrte tmp5, tmp4
        fmuls tmp2, tmp5, tmp5
        fmuls tmp3, tmp5, tmp9
        fnmsubs tmp2, tmp2, tmp4, tmp8
        fmuls tmp5, tmp2, tmp3
        ps_merge00 cT, cT, cT
        ps_muls0 tmp0, tmp0, tmp5
        ps_muls0 tmp1, tmp1, tmp5
        ps_muls0 tmp4, tmp0, tT
        ps_muls0 tmp9, tmp0, sT
        ps_muls0 tmp5, tmp1, tT
        ps_muls1 tmp3, tmp4, tmp0
        ps_muls0 tmp2, tmp4, tmp0
        ps_muls0 tmp4, tmp4, tmp1
        fnmsubs tmp6, tmp1, sT, tmp3
        fmadds tmp7, tmp1, sT, tmp3
        ps_neg tmp0, tmp9
        ps_sum0 tmp8, tmp4, fc0, tmp9
        ps_sum0 tmp2, tmp2, tmp6, cT
        ps_sum1 tmp3, cT, tmp7, tmp3
        ps_sum0 tmp6, tmp0, fc0, tmp4
        psq_st tmp8, Mtx_02(m), 0, qr0
        ps_sum0 tmp0, tmp4, tmp4, tmp0
        psq_st tmp2, Mtx_00(m), 0, qr0
        ps_muls0 tmp5, tmp5, tmp1
        psq_st tmp3, Mtx_10(m), 0, qr0
        ps_sum1 tmp4, tmp9, tmp0, tmp4
        psq_st tmp6, Mtx_12(m), 0, qr0
        ps_sum0 tmp5, tmp5, fc0, cT
        psq_st tmp4, Mtx_20(m), 0, qr0
        psq_st tmp5, Mtx_22(m), 0, qr0
    } // clang-format on
}

void PSMTXRotAxisRad(MtxPtr m, CVecPtr axis, f32 rad) {
    f32 s;
    f32 c;

    s = sinf(rad);
    c = cosf(rad);
    __PSMTXRotAxisRadInternal(m, axis, s, c);
}

void PSMTXTrans(register MtxPtr m, register f32 xT, register f32 yT,
                register f32 zT) {
    register f32 c0 = 0.0f;
    register f32 c1 = 1.0f;

    // clang-format off
    asm {
        stfs xT, Mtx_03(m)
        stfs yT, Mtx_13(m)
        psq_st c0, Mtx_01(m), 0, qr0
        psq_st c0, Mtx_20(m), 0, qr0
        stfs c0, Mtx_10(m)
        stfs c1, Mtx_11(m)
        stfs c0, Mtx_12(m)
        stfs c1, Mtx_22(m)
        stfs zT, Mtx_23(m)
        stfs c1, Mtx_00(m)
    } // clang-format on
}

// clang-format off
asm void PSMTXTransApply(register CMtxPtr src, register MtxPtr dst,
                         register f32 xT, register f32 yT, register f32 zT) {
    psq_l f4, Mtx_00(src), 0, qr0
    frsp xT, xT
    psq_l f5, Mtx_02(src), 0, qr0
    frsp yT, yT
    psq_l f7, Mtx_12(src), 0, qr0
    frsp zT, zT
    psq_l f8, Mtx_22(src), 0, qr0
    psq_st f4, Mtx_00(dst), 0, qr0
    ps_sum1 f5, xT, f5, f5
    psq_l f6, Mtx_10(src), 0, qr0
    psq_st f5, Mtx_02(dst), 0, qr0
    ps_sum1 f7, yT, f7, f7
    psq_l f9, Mtx_20(src), 0, qr0
    psq_st f6, Mtx_10(dst), 0, qr0
    ps_sum1 f8, zT, f8, f8
    psq_st f7, Mtx_12(dst), 0, qr0
    psq_st f9, Mtx_20(dst), 0, qr0
    psq_st f8, Mtx_22(dst), 0, qr0
} // clang-format on

void PSMTXScale(register MtxPtr m, register f32 xS, register f32 yS,
                register f32 zS) {
    register f32 c0 = 0.0f;

    // clang-format off
    asm {
        stfs xS, Mtx_00(m)
        psq_st c0, Mtx_01(m), 0, qr0
        psq_st c0, Mtx_03(m), 0, qr0
        stfs yS, Mtx_11(m)
        psq_st c0, Mtx_12(m), 0, qr0
        psq_st c0, Mtx_20(m), 0, qr0
        stfs zS, Mtx_22(m)
        stfs c0, Mtx_23(m)
    } // clang-format on
}

// clang-format off
asm void PSMTXScaleApply(register CMtxPtr src, register MtxPtr dst,
                         register f32 xS, register f32 yS, register f32 zS) {
    frsp xS, xS
    psq_l f4, Mtx_00(src), 0, qr0
    frsp yS, yS
    psq_l f5, Mtx_02(src), 0, qr0
    frsp zS, zS
    ps_muls0 f4, f4, xS
    psq_l f6, Mtx_10(src), 0, qr0
    ps_muls0 f5, f5, xS
    psq_l f7, Mtx_12(src), 0, qr0
    ps_muls0 f6, f6, yS
    psq_l f8, Mtx_20(src), 0, qr0
    psq_st f4, Mtx_00(dst), 0, qr0
    ps_muls0 f7, f7, yS
    psq_l f2, Mtx_22(src), 0, qr0
    psq_st f5, Mtx_02(dst), 0, qr0
    ps_muls0 f8, f8, zS
    psq_st f6, Mtx_10(dst), 0, qr0
    ps_muls0 f2, f2, zS
    psq_st f7, Mtx_12(dst), 0, qr0
    psq_st f8, Mtx_20(dst), 0, qr0
    psq_st f2, Mtx_22(dst), 0, qr0
} // clang-format on

void PSMTXQuat(register MtxPtr m, register CQuaternionPtr q) {
    register f32 c_zero;
    register f32 c_one = 1.0f;
    register f32 c_two;
    register f32 scale;
    register f32 tmp0;
    register f32 tmp1;
    register f32 tmp2;
    register f32 tmp3;
    register f32 tmp4;
    register f32 tmp5;
    register f32 tmp6;
    register f32 tmp7;
    register f32 tmp8;
    register f32 tmp9;

    // clang-format off
    asm {
        psq_l tmp0, Quaternion.x(q), 0, qr0
        psq_l tmp1, Quaternion.z(q), 0, qr0
        fsubs c_zero, c_one, c_one
        fadds c_two, c_one, c_one
        ps_mul tmp2, tmp0, tmp0
        ps_merge10 tmp5, tmp0, tmp0
        ps_madd tmp4, tmp1, tmp1, tmp2
        ps_mul tmp3, tmp1, tmp1
        ps_sum0 scale, tmp4, tmp4, tmp4
        ps_muls1 tmp7, tmp5, tmp1
        fres tmp9, scale
        ps_sum1 tmp4, tmp3, tmp4, tmp2
        ps_nmsub scale, scale, tmp9, c_two
        ps_muls1 tmp6, tmp1, tmp1
        ps_mul scale, tmp9, scale
        ps_sum0 tmp2, tmp2, tmp2, tmp2
        fmuls scale, scale, c_two
        ps_madd tmp8, tmp0, tmp5, tmp6
        ps_msub tmp6, tmp0, tmp5, tmp6
        psq_st c_zero, Mtx_03(m), 1, qr0
        ps_nmsub tmp2, tmp2, scale, c_one
        ps_nmsub tmp4, tmp4, scale, c_one
        psq_st c_zero, Mtx_23(m), 1, qr0
        ps_mul tmp8, tmp8, scale
        ps_mul tmp6, tmp6, scale
        psq_st tmp2, Mtx_22(m), 1, qr0
        ps_madds0 tmp5, tmp0, tmp1, tmp7
        ps_merge00 tmp1, tmp8, tmp4
        ps_nmsub tmp7, tmp7, c_two, tmp5
        ps_merge10 tmp0, tmp4, tmp6
        psq_st tmp1, Mtx_10(m), 0, qr0
        ps_mul tmp5, tmp5, scale
        ps_mul tmp7, tmp7, scale
        psq_st tmp0, Mtx_00(m), 0, qr0
        psq_st tmp5, Mtx_02(m), 1, qr0
        ps_merge10 tmp3, tmp7, c_zero
        ps_merge01 tmp9, tmp7, tmp5
        psq_st tmp3, Mtx_12(m), 0, qr0
        psq_st tmp9, Mtx_20(m), 0, qr0
    } // clang-format on
}

void C_MTXLookAt(MtxPtr m, CVecPtr camPos, CVecPtr camUp, CPoint3dPtr target) {
    Vec vLook;
    Vec vRight;
    Vec vUp;

    vLook.x = camPos->x - target->x;
    vLook.y = camPos->y - target->y;
    vLook.z = camPos->z - target->z;
    VECNormalize(&vLook, &vLook);
    VECCrossProduct(camUp, &vLook, &vRight);
    VECNormalize(&vRight, &vRight);
    VECCrossProduct(&vLook, &vRight, &vUp);

    m[0][0] = vRight.x;
    m[0][1] = vRight.y;
    m[0][2] = vRight.z;
    m[0][3] =
        -(camPos->x * vRight.x + camPos->y * vRight.y + camPos->z * vRight.z);
    m[1][0] = vUp.x;
    m[1][1] = vUp.y;
    m[1][2] = vUp.z;
    m[1][3] = -(camPos->x * vUp.x + camPos->y * vUp.y + camPos->z * vUp.z);
    m[2][0] = vLook.x;
    m[2][1] = vLook.y;
    m[2][2] = vLook.z;
    m[2][3] =
        -(camPos->x * vLook.x + camPos->y * vLook.y + camPos->z * vLook.z);
}

void C_MTXLightFrustum(MtxPtr m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 scaleS,
                       f32 scaleT, f32 transS, f32 transT) {
    f32 tmp = 1.0f / (r - l);
    m[0][0] = 2.0f * n * tmp * scaleS;
    m[0][1] = 0.0f;
    m[0][2] = (r + l) * tmp * scaleS - transS;
    m[0][3] = 0.0f;
    tmp = 1.0f / (t - b);
    m[1][0] = 0.0f;
    m[1][1] = 2.0f * n * tmp * scaleT;
    m[1][2] = (t + b) * tmp * scaleT - transT;
    m[1][3] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = -1.0f;
    m[2][3] = 0.0f;
}

void C_MTXLightPerspective(MtxPtr m, f32 fovY, f32 aspect, f32 scaleS,
                           f32 scaleT, f32 transS, f32 transT) {
    f32 angle;
    f32 cot;

    // Matching with C_MTXPerspective, debug compliance
    angle = fovY * 0.5f;
    angle = angle * DEG2RAD;
    cot = 1.0f / tanf(angle);

    m[0][0] = cot / aspect * scaleS;
    m[0][1] = 0.0f;
    m[0][2] = -transS;
    m[0][3] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = cot * scaleT;
    m[1][2] = -transT;
    m[1][3] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = -1.0f;
    m[2][3] = 0.0f;
}

void C_MTXLightOrtho(MtxPtr m, f32 t, f32 b, f32 l, f32 r, f32 scaleS,
                     f32 scaleT, f32 transS, f32 transT) {
    f32 tmp = 1.0f / (r - l);
    m[0][0] = 2.0f * tmp * scaleS;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = -(r + l) * tmp * scaleS + transS;
    tmp = 1.0f / (t - b);
    m[1][0] = 0.0f;
    m[1][1] = 2.0f * tmp * scaleT;
    m[1][2] = 0.0f;
    m[1][3] = -(t + b) * tmp * scaleT + transT;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = 0.0f;
    m[2][3] = 1.0f;
}
