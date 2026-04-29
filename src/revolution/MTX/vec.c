#include <revolution/MTX.h>
#include <revolution/MTX/internal/mtxAssert.h>

// clang-format off
asm void PSVECAdd(register CVecPtr vec1, register CVecPtr vec2,
                  register VecPtr dst) {
    psq_l f2, Vec.x(vec1), 0, qr0
    psq_l f4, Vec.x(vec2), 0, qr0
    ps_add f6, f2, f4
    psq_st f6, Vec.x(dst), 0, qr0
    psq_l f3, Vec.z(vec1), 1, qr0
    psq_l f5, Vec.z(vec2), 1, qr0
    ps_add f7, f3, f5
    psq_st f7, Vec.z(dst), 1, qr0
} // clang-format on

void PSVECScale(register CVecPtr src, register VecPtr dst, register f32 mult) {
    register f32 vxy;
    register f32 vz;
    register f32 rxy;
    register f32 rz;

    // clang-format off
    asm {
        psq_l vxy, Vec.x(src), 0, qr0
        psq_l vz, Vec.z(src), 1, qr0
        ps_muls0 rxy, vxy, mult
        psq_st rxy, Vec.x(dst), 0, qr0
        ps_muls0 rz, vz, mult
        psq_st rz, Vec.z(dst), 1, qr0
    } // clang-format on
}

void PSVECNormalize(register CVecPtr src, register VecPtr unit) {
    register f32 c_half = 0.5f;
    register f32 c_three = 3.0f;
    register f32 v1_xy;
    register f32 v1_z;
    register f32 xx_zz;
    register f32 xx_yy;
    register f32 sqsum;
    register f32 rsqrt;
    register f32 nwork0;
    register f32 nwork1;

    // clang-format off
    asm {
        psq_l v1_xy, Vec.x(src), 0, qr0
        ps_mul xx_yy, v1_xy, v1_xy
        psq_l v1_z, Vec.z(src), 1, qr0
        ps_madd xx_zz, v1_z, v1_z, xx_yy
        ps_sum0 sqsum, xx_zz, v1_z, xx_yy
        frsqrte rsqrt, sqsum
        fmuls nwork0, rsqrt, rsqrt
        fmuls nwork1, rsqrt, c_half
        fnmsubs nwork0, nwork0, sqsum, c_three
        fmuls rsqrt, nwork0, nwork1
        ps_muls0 v1_xy, v1_xy, rsqrt
        psq_st v1_xy, Vec.x(unit), 0, qr0
        ps_muls0 v1_z, v1_z, rsqrt
        psq_st v1_z, Vec.z(unit), 1, qr0
    } // clang-format on
}

f32 PSVECMag(register CVecPtr v) {
    register f32 vxy;
    register f32 vzz;
    register f32 sqmag;
    register f32 rmag;
    register f32 nwork0;
    register f32 nwork1;
    register f32 c_three;
    register f32 c_half = 0.5f;
    register f32 c_zero;

    // clang-format off
    asm {
        psq_l vxy, Vec.x(v), 0, qr0
        ps_mul vxy, vxy, vxy
        lfs vzz, Vec.z(v)
        fsubs c_zero, c_half, c_half
        ps_madd sqmag, vzz, vzz, vxy
        ps_sum0 sqmag, sqmag, vxy, vxy
        fcmpu cr0, sqmag, c_zero
        beq ret
        frsqrte rmag, sqmag
    } // clang-format on
    c_three = 3.0f;
    // clang-format off
    asm {
        fmuls nwork0, rmag, rmag
        fmuls nwork1, rmag, c_half
        fnmsubs nwork0, nwork0, sqmag, c_three
        fmuls rmag, nwork0, nwork1
        fmuls sqmag, sqmag, rmag
    ret:
    } // clang-format on

    return sqmag;
}

// clang-format off
asm f32 PSVECDotProduct(register CVecPtr vec1, register CVecPtr vec2) {
    psq_l f2, Vec.y(vec1), 0, qr0
    psq_l f3, Vec.y(vec2), 0, qr0
    ps_mul f2, f2, f3
    psq_l f5, Vec.x(vec1), 0, qr0
    psq_l f4, Vec.x(vec2), 0, qr0
    ps_madd f3, f5, f4, f2
    ps_sum0 f1, f3, f2, f2
} // clang-format on

// clang-format off
asm void PSVECCrossProduct(register CVecPtr vec1, register CVecPtr vec2,
                           register VecPtr dst) {
    psq_l f1, Vec.x(vec2), 0, qr0
    lfs f2, Vec.z(vec1)
    psq_l f0, Vec.x(vec1), 0, qr0
    ps_merge10 f6, f1, f1
    lfs f3, Vec.z(vec2)
    ps_mul f4, f1, f2
    ps_muls0 f7, f1, f0
    ps_msub f5, f0, f3, f4
    ps_msub f8, f0, f6, f7
    ps_merge11 f9, f5, f5
    ps_merge01 f10, f5, f8
    psq_st f9, Vec.x(dst), 1, qr0
    ps_neg f10, f10
    psq_st f10, Vec.y(dst), 0, qr0
} // clang-format on

void C_VECHalfAngle(CVecPtr a, CVecPtr b, VecPtr half) {
    Vec aTmp;
    Vec bTmp;
    Vec hTmp;

    aTmp.x = -a->x;
    aTmp.y = -a->y;
    aTmp.z = -a->z;
    bTmp.x = -b->x;
    bTmp.y = -b->y;
    bTmp.z = -b->z;

    VECNormalize(&aTmp, &aTmp);
    VECNormalize(&bTmp, &bTmp);
    VECAdd(&aTmp, &bTmp, &hTmp);
    if (VECDotProduct(&hTmp, &hTmp) > 0.0f) {
        VECNormalize(&hTmp, half);
    } else {
        *half = hTmp;
    }
}

f32 PSVECSquareDistance(register CVecPtr a, register CVecPtr b) {
    register f32 v0yz;
    register f32 v1yz;
    register f32 v0xy;
    register f32 v1xy;
    register f32 dyz;
    register f32 dxy;
    register f32 sqdist;

    // clang-format off
    asm {
        psq_l v0yz, Vec.y(a), 0, qr0
        psq_l v1yz, Vec.y(b), 0, qr0
        ps_sub dyz, v0yz, v1yz
        psq_l v0xy, Vec.x(a), 0, qr0
        psq_l v1xy, Vec.x(b), 0, qr0
        ps_mul dyz, dyz, dyz
        ps_sub dxy, v0xy, v1xy
        ps_madd sqdist, dxy, dxy, dyz
        ps_sum0 sqdist, sqdist, dyz, dyz
    } // clang-format on

    return sqdist;
}
