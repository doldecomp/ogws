#include <revolution/MTX.h>
#include <revolution/MTX/internal/mtxAssert.h>
#include <revolution/OS.h>

void C_VECAdd(CVecPtr a, CVecPtr b, VecPtr ab) {
    OS_DEBUG_ASSERT(a, "VECAdd():  NULL VecPtr 'a' ");
    OS_DEBUG_ASSERT(b, "VECAdd():  NULL VecPtr 'b' ");
    OS_DEBUG_ASSERT(ab, "VECAdd():  NULL VecPtr 'ab' ");

    ab->x = a->x + b->x;
    ab->y = a->y + b->y;
    ab->z = a->z + b->z;
}

asm void PSVECAdd(register CVecPtr vec1, register CVecPtr vec2,
                  register VecPtr dst) {
    psq_l f2, Vec.x(vec1), 0, qr0;
    psq_l f4, Vec.x(vec2), 0, qr0;
    ps_add f6, f2, f4;
    psq_st f6, Vec.x(dst), 0, qr0;
    psq_l f3, Vec.z(vec1), 1, qr0;
    psq_l f5, Vec.z(vec2), 1, qr0;
    ps_add f7, f3, f5;
    psq_st f7, Vec.z(dst), 1, qr0;
}

void C_VECSubtract(CVecPtr a, CVecPtr b, VecPtr a_b) {
    OS_DEBUG_ASSERT(a, "VECSubtract():  NULL VecPtr 'a' ");
    OS_DEBUG_ASSERT(b, "VECSubtract():  NULL VecPtr 'b' ");
    OS_DEBUG_ASSERT(a_b, "VECSubtract():  NULL VecPtr 'a_b' ");

    a_b->x = a->x - b->x;
    a_b->y = a->y - b->y;
    a_b->z = a->z - b->z;
}

asm void PSVECSubtract(register CVecPtr vec1, register CVecPtr vec2,
                       register VecPtr dst) {
    psq_l f2, Vec.x(vec1), 0, qr0;
    psq_l f4, Vec.x(vec2), 0, qr0;
    ps_sub f6, f2, f4;
    psq_st f6, Vec.x(dst), 0, qr0;
    psq_l f3, Vec.z(vec1), 1, qr0;
    psq_l f5, Vec.z(vec2), 1, qr0;
    ps_sub f7, f3, f5;
    psq_st f7, Vec.z(dst), 1, qr0;
}

void C_VECScale(CVecPtr src, VecPtr dst, f32 scale) {
    OS_DEBUG_ASSERT(src, "VECScale():  NULL VecPtr 'src' ");
    OS_DEBUG_ASSERT(dst, "VECScale():  NULL VecPtr 'dst' ");

    dst->x = src->x * scale;
    dst->y = src->y * scale;
    dst->z = src->z * scale;
}

void PSVECScale(register CVecPtr src, register VecPtr dst, register f32 mult) {
    register f32 vxy;
    register f32 vz;
    register f32 rxy;
    register f32 rz;

    ASM (
        psq_l vxy, Vec.x(src), 0, qr0;
        psq_l vz, Vec.z(src), 1, qr0;
        ps_muls0 rxy, vxy, mult;
        psq_st rxy, Vec.x(dst), 0, qr0;
        ps_muls0 rz, vz, mult;
        psq_st rz, Vec.z(dst), 1, qr0;
    )
}

void C_VECNormalize(CVecPtr src, VecPtr unit) {
    f32 mag;

    OS_DEBUG_ASSERT(src, "VECNormalize():  NULL VecPtr 'src' ");
    OS_DEBUG_ASSERT(unit, "VECNormalize():  NULL VecPtr 'unit' ");

    mag = src->x * src->x + src->y * src->y + src->z * src->z;
    OS_DEBUG_ASSERT(mag != 0.0f, "VECNormalize():  zero magnitude vector ");

    mag = 1.0f / sqrtf(mag);
    unit->x = src->x * mag;
    unit->y = src->y * mag;
    unit->z = src->z * mag;
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

    ASM (
        psq_l v1_xy, Vec.x(src), 0, qr0;
        ps_mul xx_yy, v1_xy, v1_xy;
        psq_l v1_z, Vec.z(src), 1, qr0;
        ps_madd xx_zz, v1_z, v1_z, xx_yy;
        ps_sum0 sqsum, xx_zz, v1_z, xx_yy;
        frsqrte rsqrt, sqsum;
        fmuls nwork0, rsqrt, rsqrt;
        fmuls nwork1, rsqrt, c_half;
        fnmsubs nwork0, nwork0, sqsum, c_three;
        fmuls rsqrt, nwork0, nwork1;
        ps_muls0 v1_xy, v1_xy, rsqrt;
        psq_st v1_xy, Vec.x(unit), 0, qr0;
        ps_muls0 v1_z, v1_z, rsqrt;
        psq_st v1_z, Vec.z(unit), 1, qr0;
    )
}

f32 C_VECSquareMag(CVecPtr v) {
    f32 sqmag; // The DWARF build we have is outdated, this name is added

    OS_DEBUG_ASSERT(v, "VECMag():  NULL VecPtr 'v' ");

    sqmag = v->x * v->x + v->y * v->y + v->z * v->z;
    return sqmag;
}

f32 PSVECSquareMag(register CVecPtr vec1) {
    register f32 vxy;
    register f32 vzz;
    register f32 sqmag;

    ASM (
        psq_l vxy, Vec.x(vec1), 0, qr0;
        ps_mul vxy, vxy, vxy;
        lfs vzz, Vec.z(vec1);
        ps_madd sqmag, vzz, vzz, vxy;
        ps_sum0 sqmag, sqmag, vxy, vxy;
    )

    return sqmag;
}

f32 C_VECMag(CVecPtr v) {
    return sqrtf(C_VECSquareMag(v));
}

f32 PSVECMag(register CVecPtr v) {
    register f32 vxy;
    register f32 vzz;
    register f32 sqmag;
    register f32 mag; // DWARF has this, but somehow this can't exist, unused?
    register f32 rmag;
    register f32 nwork0;
    register f32 nwork1;
    register f32 c_three;
    register f32 c_half = 0.5f;
    register f32 c_zero; // DWARF doesn't have this, added

    ASM (
        psq_l vxy, Vec.x(v), 0, qr0;
        ps_mul vxy, vxy, vxy;
        lfs vzz, Vec.z(v);
        fsubs c_zero, c_half, c_half;
        ps_madd sqmag, vzz, vzz, vxy;
        ps_sum0 sqmag, sqmag, vxy, vxy;
        fcmpu cr0, sqmag, c_zero;
        beq ret;
        frsqrte rmag, sqmag;
    )
    c_three = 3.0f;

    ASM (
        fmuls nwork0, rmag, rmag;
        fmuls nwork1, rmag, c_half;
        fnmsubs nwork0, nwork0, sqmag, c_three;
        fmuls rmag, nwork0, nwork1;
        fmuls sqmag, sqmag, rmag;
    ret:
    )

    return sqmag;
}

f32 C_VECDotProduct(CVecPtr a, CVecPtr b) {
    f32 dot;

    OS_DEBUG_ASSERT(a, "VECDotProduct():  NULL VecPtr 'a' ");
    OS_DEBUG_ASSERT(b, "VECDotProduct():  NULL VecPtr 'b' ");

    dot = a->x * b->x + a->y * b->y + a->z * b->z;
    return dot;
}

asm f32 PSVECDotProduct(register CVecPtr vec1, register CVecPtr vec2) {
    psq_l f2, Vec.y(vec1), 0, qr0;
    psq_l f3, Vec.y(vec2), 0, qr0;
    ps_mul f2, f2, f3;
    psq_l f5, Vec.x(vec1), 0, qr0;
    psq_l f4, Vec.x(vec2), 0, qr0;
    ps_madd f3, f5, f4, f2;
    ps_sum0 f1, f3, f2, f2;
}

void C_VECCrossProduct(CVecPtr a, CVecPtr b, VecPtr axb) {
    Vec v;

    OS_DEBUG_ASSERT(a, "VECCrossProduct():  NULL VecPtr 'a' ");
    OS_DEBUG_ASSERT(b, "VECCrossProduct():  NULL VecPtr 'b' ");
    OS_DEBUG_ASSERT(axb, "VECCrossProduct():  NULL VecPtr 'axb' ");

    v.x = a->y * b->z - a->z * b->y;
    v.y = a->z * b->x - a->x * b->z;
    v.z = a->x * b->y - a->y * b->x;

    axb->x = v.x;
    axb->y = v.y;
    axb->z = v.z;
}

asm void PSVECCrossProduct(register CVecPtr vec1, register CVecPtr vec2,
                           register VecPtr dst) {
    psq_l f1, Vec.x(vec2), 0, qr0;
    lfs f2, Vec.z(vec1);
    psq_l f0, Vec.x(vec1), 0, qr0;
    ps_merge10 f6, f1, f1;
    lfs f3, Vec.z(vec2);
    ps_mul f4, f1, f2;
    ps_muls0 f7, f1, f0;
    ps_msub f5, f0, f3, f4;
    ps_msub f8, f0, f6, f7;
    ps_merge11 f9, f5, f5;
    ps_merge01 f10, f5, f8;
    psq_st f9, Vec.x(dst), 1, qr0;
    ps_neg f10, f10;
    psq_st f10, Vec.y(dst), 0, qr0;
}

void C_VECHalfAngle(CVecPtr a, CVecPtr b, VecPtr half) {
    Vec aTmp;
    Vec bTmp;
    Vec hTmp;

    OS_DEBUG_ASSERT(a, "VECHalfAngle():  NULL VecPtr 'a' ");
    OS_DEBUG_ASSERT(b, "VECHalfAngle():  NULL VecPtr 'b' ");
    OS_DEBUG_ASSERT(half, "VECHalfAngle():  NULL VecPtr 'half' ");

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

void C_VECReflect(CVecPtr src, CVecPtr normal, VecPtr dst) {
    f32 cosA;
    Vec uI;
    Vec uN;

    OS_DEBUG_ASSERT(src, "VECReflect():  NULL VecPtr 'src' ");
    OS_DEBUG_ASSERT(normal, "VECReflect():  NULL VecPtr 'normal' ");
    OS_DEBUG_ASSERT(dst, "VECReflect():  NULL VecPtr 'dst' ");

    uI.x = -src->x;
    uI.y = -src->y;
    uI.z = -src->z;

    VECNormalize(&uI, &uI);
    VECNormalize(normal, &uN);
    cosA = VECDotProduct(&uI, &uN);

    dst->x = (2.0f * uN.x * cosA) - uI.x;
    dst->y = (2.0f * uN.y * cosA) - uI.y;
    dst->z = (2.0f * uN.z * cosA) - uI.z;
    VECNormalize(dst, dst);
}

f32 C_VECSquareDistance(CVecPtr a, CVecPtr b) {
    Vec v;

    v.x = a->x - b->x;
    v.y = a->y - b->y;
    v.z = a->z - b->z;
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

f32 PSVECSquareDistance(register CVecPtr a, register CVecPtr b) {
    register f32 v0yz;
    register f32 v1yz;
    register f32 v0xy;
    register f32 v1xy;
    register f32 dyz;
    register f32 dxy;
    register f32 sqdist;

    ASM (
        psq_l v0yz, Vec.y(a), 0, qr0;
        psq_l v1yz, Vec.y(b), 0, qr0;
        ps_sub dyz, v0yz, v1yz;
        psq_l v0xy, Vec.x(a), 0, qr0;
        psq_l v1xy, Vec.x(b), 0, qr0;
        ps_mul dyz, dyz, dyz;
        ps_sub dxy, v0xy, v1xy;
        ps_madd sqdist, dxy, dxy, dyz;
        ps_sum0 sqdist, sqdist, dyz, dyz;
    )

    return sqdist;
}

f32 C_VECDistance(CVecPtr a, CVecPtr b) {
    return sqrtf(C_VECSquareDistance(a, b));
}

f32 PSVECDistance(register CVecPtr a, register CVecPtr b) {
    register f32 v0yz;
    register f32 v1yz;
    register f32 v0xy;
    register f32 v1xy;
    register f32 dyz;
    register f32 dxy;
    register f32 sqdist;
    register f32 rdist;
    register f32 dist; // DWARF has this, but somehow this can't exist, unused?
    register f32 nwork0;
    register f32 nwork1;
    register f32 c_half;
    register f32 c_three;
    register f32 c_zero; // DWARF doesn't have this, added

    ASM (
        psq_l v0yz, Vec.y(a), 0, qr0;
        psq_l v1yz, Vec.y(b), 0, qr0;
        ps_sub dyz, v0yz, v1yz;
        psq_l v0xy, Vec.x(a), 0, qr0;
        psq_l v1xy, Vec.x(b), 0, qr0;
        ps_mul dyz, dyz, dyz;
        ps_sub dxy, v0xy, v1xy;
    )
    c_half = 0.5f;

    ASM (
        ps_madd sqdist, dxy, dxy, dyz;
        fsubs c_zero, c_half, c_half;
        ps_sum0 sqdist, sqdist, dyz, dyz;
        fcmpu cr0, c_zero, sqdist;
        beq end;
    )
    c_three = 3.0f;

    ASM (
        frsqrte rdist, sqdist;
        fmuls nwork0, rdist, rdist;
        fmuls nwork1, rdist, c_half;
        fnmsubs nwork0, nwork0, sqdist, c_three;
        fmuls rdist, nwork0, nwork1;
        fmuls sqdist, sqdist, rdist;
    end:
    )

    return sqdist;
}
