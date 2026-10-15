#include <revolution/MTX.h>
#include <revolution/MTX/internal/mtx44extAssert.h>
#include <revolution/OS.h>

#include <math.h>

static f32 mtxUnit[] = {0.0f, 1.0f, 0.5f, 3.0f};

void C_MTXFrustum(Mtx44Ptr m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f) {
    f32 tmp;

    OS_DEBUG_ASSERT(m, "MTXFrustum():  NULL Mtx44Ptr 'm' ");
    OS_DEBUG_ASSERT(t != b, "MTXFrustum():  't' and 'b' clipping planes are equal ");
    OS_DEBUG_ASSERT(l != r, "MTXFrustum():  'l' and 'r' clipping planes are equal ");
    OS_DEBUG_ASSERT(n != f, "MTXFrustum():  'n' and 'f' clipping planes are equal ");

    tmp = 1.0f / (r - l);
    m[0][0] = 2.0f * n * tmp;
    m[0][1] = 0.0f;
    m[0][2] = (r + l) * tmp;
    m[0][3] = 0.0f;
    tmp = 1.0f / (t - b);
    m[1][0] = 0.0f;
    m[1][1] = 2.0f * n * tmp;
    m[1][2] = (t + b) * tmp;
    m[1][3] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    tmp = 1.0f / (f - n);
    m[2][2] = -n * tmp;
    m[2][3] = -(f * n) * tmp;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = -1.0f;
    m[3][3] = 0.0f;
}

void C_MTXPerspective(Mtx44Ptr m, f32 fovY, f32 aspect, f32 n, f32 f) {
    f32 angle;
    f32 cot;
    f32 tmp;

    OS_DEBUG_ASSERT(m, "MTXPerspective():  NULL Mtx44Ptr 'm' ");
    OS_DEBUG_ASSERT(fovY > 0.0 && fovY < 180.0, "MTXPerspective():  'fovY' out of range ");
    OS_DEBUG_ASSERT(aspect != 0.0f, "MTXPerspective():  'aspect' is 0 ");

    // Float ordering, debug compliance
    angle = fovY * 0.5f;
    angle = angle * DEG2RAD;
    cot = 1.0f / tanf(angle);

    m[0][0] = cot / aspect;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = cot;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    tmp = 1.0f / (f - n);
    m[2][2] = -n * tmp;
    m[2][3] = -(f * n) * tmp;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = -1.0f;
    m[3][3] = 0.0f;
}

void C_MTXOrtho(Mtx44Ptr m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f) {
    f32 tmp;

    OS_DEBUG_ASSERT(m, "MTXOrtho():  NULL Mtx44Ptr 'm' ");
    OS_DEBUG_ASSERT(t != b, "MTXOrtho():  't' and 'b' clipping planes are equal ");
    OS_DEBUG_ASSERT(l != r, "MTXOrtho():  'l' and 'r' clipping planes are equal ");
    OS_DEBUG_ASSERT(n != f, "MTXOrtho():  'n' and 'f' clipping planes are equal ");

    tmp = 1.0f / (r - l);
    m[0][0] = 2.0f * tmp;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = -(r + l) * tmp;
    tmp = 1.0f / (t - b);
    m[1][0] = 0.0f;
    m[1][1] = 2.0f * tmp;
    m[1][2] = 0.0f;
    m[1][3] = -(t + b) * tmp;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    tmp = 1.0f / (f - n);
    m[2][2] = -1.0f * tmp;
    m[2][3] = -f * tmp;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

void C_MTX44Identity(Mtx44Ptr m) {
    OS_DEBUG_ASSERT(m, "MTX44Identity():  NULL Mtx44 'm' ");

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
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

void PSMTX44Identity(register Mtx44Ptr m) {
    register f32 c1 = 1.0f;
    register f32 c0 = 0.0f;

    ASM (
        stfs c1, Mtx_00(m);
        psq_st c0, Mtx_01(m), 0, qr0;
        psq_st c0, Mtx_03(m), 0, qr0;
        stfs c1, Mtx_11(m);
        psq_st c0, Mtx_12(m), 0, qr0;
        psq_st c0, Mtx_20(m), 0, qr0;
        stfs c1, Mtx_22(m);
        psq_st c0, Mtx_23(m), 0, qr0;
        psq_st c0, Mtx_31(m), 0, qr0;
        stfs c1, Mtx_33(m);
   )
}

void C_MTX44Copy(CMtx44Ptr src, Mtx44Ptr dst) {
    OS_DEBUG_ASSERT(src, "MTX44Copy():  NULL Mtx44Ptr 'src' ");
    OS_DEBUG_ASSERT(dst, "MTX44Copy():  NULL Mtx44Ptr 'dst' ");

    if (src == dst) {
        return;
    }

    dst[0][0] = src[0][0];
    dst[0][1] = src[0][1];
    dst[0][2] = src[0][2];
    dst[0][3] = src[0][3];
    dst[1][0] = src[1][0];
    dst[1][1] = src[1][1];
    dst[1][2] = src[1][2];
    dst[1][3] = src[1][3];
    dst[2][0] = src[2][0];
    dst[2][1] = src[2][1];
    dst[2][2] = src[2][2];
    dst[2][3] = src[2][3];
    dst[3][0] = src[3][0];
    dst[3][1] = src[3][1];
    dst[3][2] = src[3][2];
    dst[3][3] = src[3][3];
}

asm void PSMTX44Copy(register CMtx44Ptr src, register Mtx44Ptr dst) {
    nofralloc;

    psq_l f1, Mtx_00(src), 0, qr0;
    psq_st f1, Mtx_00(dst), 0, qr0;
    psq_l f1, Mtx_02(src), 0, qr0;
    psq_st f1, Mtx_02(dst), 0, qr0;
    psq_l f1, Mtx_10(src), 0, qr0;
    psq_st f1, Mtx_10(dst), 0, qr0;
    psq_l f1, Mtx_12(src), 0, qr0;
    psq_st f1, Mtx_12(dst), 0, qr0;
    psq_l f1, Mtx_20(src), 0, qr0;
    psq_st f1, Mtx_20(dst), 0, qr0;
    psq_l f1, Mtx_22(src), 0, qr0;
    psq_st f1, Mtx_22(dst), 0, qr0;
    psq_l f1, Mtx_30(src), 0, qr0;
    psq_st f1, Mtx_30(dst), 0, qr0;
    psq_l f1, Mtx_32(src), 0, qr0;
    psq_st f1, Mtx_32(dst), 0, qr0;

    blr;
}

void C_MTX44Concat(CMtx44Ptr a, CMtx44Ptr b, Mtx44Ptr ab) {
    Mtx44 mTmp;
    Mtx44Ptr m;

    OS_DEBUG_ASSERT(a, "MTX44Concat():  NULL Mtx44Ptr 'a'  ");
    OS_DEBUG_ASSERT(b, "MTX44Concat():  NULL Mtx44Ptr 'b'  ");
    OS_DEBUG_ASSERT(ab, "MTX44Concat():  NULL Mtx44Ptr 'ab' ");

    if (ab == a || ab == b) {
        m = mTmp;
    } else {
        m = ab;
    }

    m[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0] +
              a[0][3] * b[3][0];
    m[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1] + a[0][2] * b[2][1] +
              a[0][3] * b[3][1];
    m[0][2] = a[0][0] * b[0][2] + a[0][1] * b[1][2] + a[0][2] * b[2][2] +
              a[0][3] * b[3][2];
    m[0][3] = a[0][0] * b[0][3] + a[0][1] * b[1][3] + a[0][2] * b[2][3] +
              a[0][3] * b[3][3];
    m[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0] + a[1][2] * b[2][0] +
              a[1][3] * b[3][0];
    m[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1] + a[1][2] * b[2][1] +
              a[1][3] * b[3][1];
    m[1][2] = a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2] +
              a[1][3] * b[3][2];
    m[1][3] = a[1][0] * b[0][3] + a[1][1] * b[1][3] + a[1][2] * b[2][3] +
              a[1][3] * b[3][3];
    m[2][0] = a[2][0] * b[0][0] + a[2][1] * b[1][0] + a[2][2] * b[2][0] +
              a[2][3] * b[3][0];
    m[2][1] = a[2][0] * b[0][1] + a[2][1] * b[1][1] + a[2][2] * b[2][1] +
              a[2][3] * b[3][1];
    m[2][2] = a[2][0] * b[0][2] + a[2][1] * b[1][2] + a[2][2] * b[2][2] +
              a[2][3] * b[3][2];
    m[2][3] = a[2][0] * b[0][3] + a[2][1] * b[1][3] + a[2][2] * b[2][3] +
              a[2][3] * b[3][3];
    m[3][0] = a[3][0] * b[0][0] + a[3][1] * b[1][0] + a[3][2] * b[2][0] +
              a[3][3] * b[3][0];
    m[3][1] = a[3][0] * b[0][1] + a[3][1] * b[1][1] + a[3][2] * b[2][1] +
              a[3][3] * b[3][1];
    m[3][2] = a[3][0] * b[0][2] + a[3][1] * b[1][2] + a[3][2] * b[2][2] +
              a[3][3] * b[3][2];
    m[3][3] = a[3][0] * b[0][3] + a[3][1] * b[1][3] + a[3][2] * b[2][3] +
              a[3][3] * b[3][3];

    if (m == mTmp) {
        C_MTX44Copy(mTmp, ab);
    }
}

asm void PSMTX44Concat(register CMtx44Ptr mA, register CMtx44Ptr mB,
                       register Mtx44Ptr mAB) {
    nofralloc;

    psq_l f0, Mtx_00(mA), 0, qr0;
    psq_l f2, Mtx_00(mB), 0, qr0;
    ps_muls0 f6, f2, f0;
    psq_l f3, Mtx_10(mB), 0, qr0;
    psq_l f4, Mtx_20(mB), 0, qr0;
    ps_madds1 f6, f3, f0, f6;
    psq_l f1, Mtx_02(mA), 0, qr0;
    psq_l f5, Mtx_30(mB), 0, qr0;
    ps_madds0 f6, f4, f1, f6;
    psq_l f0, Mtx_10(mA), 0, qr0;
    ps_madds1 f6, f5, f1, f6;
    psq_l f1, Mtx_12(mA), 0, qr0;
    ps_muls0 f8, f2, f0;
    ps_madds1 f8, f3, f0, f8;
    psq_l f0, Mtx_20(mA), 0, qr0;
    ps_madds0 f8, f4, f1, f8;
    ps_madds1 f8, f5, f1, f8;
    psq_l f1, Mtx_22(mA), 0, qr0;
    ps_muls0 f10, f2, f0;
    ps_madds1 f10, f3, f0, f10;
    psq_l f0, Mtx_30(mA), 0, qr0;
    ps_madds0 f10, f4, f1, f10;
    ps_madds1 f10, f5, f1, f10;
    psq_l f1, Mtx_32(mA), 0, qr0;
    ps_muls0 f12, f2, f0;
    psq_l f2, Mtx_02(mB), 0, qr0;
    ps_madds1 f12, f3, f0, f12;
    psq_l f0, Mtx_00(mA), 0, qr0;
    ps_madds0 f12, f4, f1, f12;
    psq_l f3, Mtx_12(mB), 0, qr0;
    ps_madds1 f12, f5, f1, f12;
    psq_l f1, Mtx_02(mA), 0, qr0;
    ps_muls0 f7, f2, f0;
    psq_l f4, Mtx_22(mB), 0, qr0;
    ps_madds1 f7, f3, f0, f7;
    psq_l f5, Mtx_32(mB), 0, qr0;
    ps_madds0 f7, f4, f1, f7;
    psq_l f0, Mtx_10(mA), 0, qr0;
    ps_madds1 f7, f5, f1, f7;
    psq_l f1, Mtx_12(mA), 0, qr0;
    ps_muls0 f9, f2, f0;
    psq_st f6, Mtx_00(mAB), 0, qr0;
    ps_madds1 f9, f3, f0, f9;
    psq_l f0, Mtx_20(mA), 0, qr0;
    ps_madds0 f9, f4, f1, f9;
    psq_st f8, Mtx_10(mAB), 0, qr0;
    ps_madds1 f9, f5, f1, f9;
    psq_l f1, Mtx_22(mA), 0, qr0;
    ps_muls0 f11, f2, f0;
    psq_st f10, Mtx_20(mAB), 0, qr0;
    ps_madds1 f11, f3, f0, f11;
    psq_l f0, Mtx_30(mA), 0, qr0;
    ps_madds0 f11, f4, f1, f11;
    psq_st f12, Mtx_30(mAB), 0, qr0;
    ps_madds1 f11, f5, f1, f11;
    psq_l f1, Mtx_32(mA), 0, qr0;
    ps_muls0 f13, f2, f0;
    psq_st f7, Mtx_02(mAB), 0, qr0;
    ps_madds1 f13, f3, f0, f13;
    psq_st f9, Mtx_12(mAB), 0, qr0;
    ps_madds0 f13, f4, f1, f13;
    psq_st f11, Mtx_22(mAB), 0, qr0;
    ps_madds1 f13, f5, f1, f13;
    psq_st f13, Mtx_32(mAB), 0, qr0;

    blr;
}

void C_MTX44Transpose(CMtx44Ptr src, Mtx44Ptr xPose) {
    Mtx44 mTmp;
    Mtx44Ptr m;

    OS_DEBUG_ASSERT(src, "MTX44Transpose():  NULL Mtx44Ptr 'src' ");
    OS_DEBUG_ASSERT(xPose, "MTX44Transpose():  NULL Mtx44Ptr 'xPose' ");

    if (src == xPose) {
        m = mTmp;
    } else {
        m = xPose;
    }

    m[0][0] = src[0][0];
    m[0][1] = src[1][0];
    m[0][2] = src[2][0];
    m[0][3] = src[3][0];
    m[1][0] = src[0][1];
    m[1][1] = src[1][1];
    m[1][2] = src[2][1];
    m[1][3] = src[3][1];
    m[2][0] = src[0][2];
    m[2][1] = src[1][2];
    m[2][2] = src[2][2];
    m[2][3] = src[3][2];
    m[3][0] = src[0][3];
    m[3][1] = src[1][3];
    m[3][2] = src[2][3];
    m[3][3] = src[3][3];

    if (m == mTmp) {
        MTX44Copy(mTmp, xPose);
    }
}

asm void PSMTX44Transpose(register CMtx44Ptr src, register Mtx44Ptr xPose) {
    nofralloc;

    psq_l f0, Mtx_00(src), 0, qr0;
    psq_l f1, Mtx_10(src), 0, qr0;
    ps_merge00 f4, f0, f1;
    psq_l f2, Mtx_02(src), 0, qr0;
    psq_st f4, Mtx_00(xPose), 0, qr0;
    ps_merge11 f5, f0, f1;
    psq_l f3, Mtx_12(src), 0, qr0;
    psq_st f5, Mtx_10(xPose), 0, qr0;
    ps_merge00 f4, f2, f3;
    psq_l f0, Mtx_20(src), 0, qr0;
    psq_st f4, Mtx_20(xPose), 0, qr0;
    ps_merge11 f5, f2, f3;
    psq_l f1, Mtx_30(src), 0, qr0;
    psq_st f5, Mtx_30(xPose), 0, qr0;
    ps_merge00 f4, f0, f1;
    psq_l f2, Mtx_22(src), 0, qr0;
    psq_st f4, Mtx_02(xPose), 0, qr0;
    ps_merge11 f5, f0, f1;
    psq_l f3, Mtx_32(src), 0, qr0;
    psq_st f5, Mtx_12(xPose), 0, qr0;
    ps_merge00 f4, f2, f3;
    psq_st f4, Mtx_22(xPose), 0, qr0;
    ps_merge11 f5, f2, f3;
    psq_st f5, Mtx_32(xPose), 0, qr0;

    blr;
}

u32 C_MTX44Inverse(CMtx44Ptr src, Mtx44Ptr inv) {
    Mtx44 gjm;
    s32 i;
    s32 j;
    s32 k;
    f32 w;
    f32 max;
    s32 swp;
    f32 ftmp;

    OS_DEBUG_ASSERT(src, "MTX44Inverse():  NULL Mtx44Ptr 'src' ");
    OS_DEBUG_ASSERT(inv, "MTX44Inverse():  NULL Mtx44Ptr 'inv' ");

    MTX44Copy(src, gjm);
    MTX44Identity(inv);

    for (i = 0; i < 4; ++i) {
        f32 max = 0.0f;
        s32 swp = i;

        for (j = i; j < 4; ++j) {
            ftmp = fabsf(gjm[j][i]);
            if (ftmp > max) {
                max = ftmp;
                swp = j;
            }
        }

        if (max == 0.0f) {
            // Missing pivot, matrix is singular
            return FALSE;
        }

        if (swp != i) {
            for (j = 0; j < 4; ++j) {
                // DWARF has two "tmp" variables
                // Placing one here and another in the bottom loop doesn't work
                {
                    f32 tmp = gjm[i][j];
                    gjm[i][j] = gjm[swp][j];
                    gjm[swp][j] = tmp;
                }
                {
                    f32 tmp = inv[i][j];
                    inv[i][j] = inv[swp][j];
                    inv[swp][j] = tmp;
                }
            }
        }

        w = 1.0f / gjm[i][i];

        for (k = 0; k < 4; ++k) {
            gjm[i][k] *= w;
            inv[i][k] *= w;
        }

        for (j = 0; j < 4; ++j) {
            if (j != i) {
                w = gjm[j][i];
                for (k = 0; k < 4; ++k) {
                    gjm[j][k] -= gjm[i][k] * w;
                    inv[j][k] -= inv[i][k] * w;
                }
            }
        }
    }

    return TRUE;
}

void C_MTX44Trans(Mtx44Ptr m, f32 xT, f32 yT, f32 zT) {
    OS_DEBUG_ASSERT(m, "MTX44Trans():  NULL Mtx44Ptr 'm' ");

    m[0][0] = 1.0f;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = xT;
    m[1][0] = 0.0f;
    m[1][1] = 1.0f;
    m[1][2] = 0.0f;
    m[1][3] = yT;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = 1.0f;
    m[2][3] = zT;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

void PSMTX44Trans(register Mtx44Ptr m, register f32 xT, register f32 yT,
                  register f32 zT) {
    register f32 c_zero = 0.0f;
    register f32 c_one = 1.0f;
    register f32 c_01;

    ASM (
        stfs xT, Mtx_03(m);
        stfs yT, Mtx_13(m);
        ps_merge00 c_01, c_zero, c_one;
        stfs zT, Mtx_23(m);
        psq_st c_one, Mtx_00(m), 1, qr0;
        psq_st c_zero, Mtx_01(m), 0, qr0;
        psq_st c_01, Mtx_10(m), 0, qr0;
        psq_st c_zero, Mtx_12(m), 1, qr0;
        psq_st c_zero, Mtx_20(m), 0, qr0;
        psq_st c_one, Mtx_22(m), 1, qr0;
        psq_st c_zero, Mtx_30(m), 0, qr0;
        psq_st c_01, Mtx_32(m), 0, qr0;
    )
}

void C_MTX44TransApply(CMtx44Ptr src, Mtx44Ptr dst, f32 xT, f32 yT, f32 zT) {
    OS_DEBUG_ASSERT(src, "MTX44TransApply(): NULL Mtx44Ptr 'src' ");
    OS_DEBUG_ASSERT(dst, "MTX44TransApply(): NULL Mtx44Ptr 'src' ");

    if (src != dst) {
        dst[0][0] = src[0][0];
        dst[0][1] = src[0][1];
        dst[0][2] = src[0][2];
        dst[1][0] = src[1][0];
        dst[1][1] = src[1][1];
        dst[1][2] = src[1][2];
        dst[2][0] = src[2][0];
        dst[2][1] = src[2][1];
        dst[2][2] = src[2][2];
        dst[3][0] = src[3][0];
        dst[3][1] = src[3][1];
        dst[3][2] = src[3][2];
        dst[3][3] = src[3][3];
    }

    dst[0][3] = src[0][3] + xT;
    dst[1][3] = src[1][3] + yT;
    dst[2][3] = src[2][3] + zT;
}

asm void PSMTX44TransApply(register CMtx44Ptr src, register Mtx44Ptr dst,
                           register f32 xT, register f32 yT, register f32 zT) {
    nofralloc;

    psq_l f4, Mtx_00(src), 0, qr0;
    frsp xT, xT;
    psq_l f5, Mtx_02(src), 0, qr0;
    frsp yT, yT;
    psq_l f6, Mtx_10(src), 0, qr0;
    frsp zT, zT;
    psq_l f7, Mtx_12(src), 0, qr0;
    psq_st f4, Mtx_00(dst), 0, qr0;
    ps_sum1 f5, f1, f5, f5;
    psq_l f4, Mtx_22(src), 0, qr0;
    psq_st f6, Mtx_10(dst), 0, qr0;
    ps_sum1 f7, f2, f7, f7;
    psq_l f8, Mtx_20(src), 0, qr0;
    psq_st f5, Mtx_02(dst), 0, qr0;
    ps_sum1 f4, f3, f4, f4;
    psq_st f7, Mtx_12(dst), 0, qr0;
    psq_st f8, Mtx_20(dst), 0, qr0;
    psq_l f5, Mtx_30(src), 0, qr0;
    psq_l f6, Mtx_32(src), 0, qr0;
    psq_st f4, Mtx_22(dst), 0, qr0;
    psq_st f5, Mtx_30(dst), 0, qr0;
    psq_st f6, Mtx_32(dst), 0, qr0;

    blr;
}

void C_MTX44Scale(Mtx44Ptr m, f32 xS, f32 yS, f32 zS) {
    OS_DEBUG_ASSERT(m, "MTX44Scale():  NULL Mtx44Ptr 'm' ");

    m[0][0] = xS;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = yS;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = zS;
    m[2][3] = 0.0f;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

void PSMTX44Scale(register Mtx44Ptr m, register f32 xS, register f32 yS,
                  register f32 zS) {
    register f32 c_zero = 0.0f;
    register f32 c_one = 1.0f;

    ASM (
        stfs xS, Mtx_00(m);
        psq_st c_zero, Mtx_01(m), 0, qr0;
        psq_st c_zero, Mtx_03(m), 0, qr0;
        stfs yS, Mtx_11(m);
        psq_st c_zero, Mtx_12(m), 0, qr0;
        psq_st c_zero, Mtx_20(m), 0, qr0;
        stfs zS, Mtx_22(m);
        psq_st c_zero, Mtx_23(m), 0, qr0;
        psq_st c_zero, Mtx_31(m), 0, qr0;
        stfs c_one, Mtx_33(m);
    )
}

void C_MTX44ScaleApply(CMtx44Ptr src, Mtx44Ptr dst, f32 xS, f32 yS, f32 zS) {
    OS_DEBUG_ASSERT(src, "MTX44ScaleApply(): NULL Mtx44Ptr 'src' ");
    OS_DEBUG_ASSERT(dst, "MTX44ScaleApply(): NULL Mtx44Ptr 'dst' ");

    dst[0][0] = src[0][0] * xS;
    dst[0][1] = src[0][1] * xS;
    dst[0][2] = src[0][2] * xS;
    dst[0][3] = src[0][3] * xS;
    dst[1][0] = src[1][0] * yS;
    dst[1][1] = src[1][1] * yS;
    dst[1][2] = src[1][2] * yS;
    dst[1][3] = src[1][3] * yS;
    dst[2][0] = src[2][0] * zS;
    dst[2][1] = src[2][1] * zS;
    dst[2][2] = src[2][2] * zS;
    dst[2][3] = src[2][3] * zS;
    dst[3][0] = src[3][0];
    dst[3][1] = src[3][1];
    dst[3][2] = src[3][2];
    dst[3][3] = src[3][3];
}

asm void PSMTX44ScaleApply(register CMtx44Ptr src, register Mtx44Ptr dst,
                           register f32 xS, register f32 yS, register f32 zS) {
    nofralloc;

    psq_l f4, Mtx_00(src), 0, qr0;
    frsp xS, xS;
    psq_l f5, Mtx_02(src), 0, qr0;
    frsp yS, yS;
    psq_l f6, Mtx_10(src), 0, qr0;
    ps_muls0 f4, f4, xS;
    psq_l f7, Mtx_12(src), 0, qr0;
    ps_muls0 f5, f5, xS;
    psq_l f8, Mtx_20(src), 0, qr0;
    frsp zS, zS;
    psq_st f4, Mtx_00(dst), 0, qr0;
    ps_muls0 f6, f6, yS;
    psq_l f9, Mtx_22(src), 0, qr0;
    psq_st f5, Mtx_02(dst), 0, qr0;
    ps_muls0 f7, f7, yS;
    psq_l f10, Mtx_30(src), 0, qr0;
    psq_st f6, Mtx_10(dst), 0, qr0;
    ps_muls0 f8, f8, zS;
    psq_l f11, Mtx_32(src), 0, qr0;
    psq_st f7, Mtx_12(dst), 0, qr0;
    ps_muls0 f9, f9, zS;
    psq_st f8, Mtx_20(dst), 0, qr0;
    psq_st f9, Mtx_22(dst), 0, qr0;
    psq_st f10, Mtx_30(dst), 0, qr0;
    psq_st f11, Mtx_32(dst), 0, qr0;

    blr;
}

void C_MTX44RotRad(Mtx44Ptr m, char axis, f32 rad) {
    f32 sinA, cosA;

    OS_DEBUG_ASSERT(m, "MTX44RotRad():  NULL Mtx44Ptr 'm' ");

    sinA = sinf(rad);
    cosA = cosf(rad);
    C_MTX44RotTrig(m, axis, sinA, cosA);
}

void PSMTX44RotRad(Mtx44Ptr m, char axis, f32 rad) {
    f32 sinA, cosA;

    sinA = sinf(rad);
    cosA = cosf(rad);
    PSMTX44RotTrig(m, axis, sinA, cosA);
}

void C_MTX44RotTrig(Mtx44Ptr m, char axis, f32 sinA, f32 cosA) {
    OS_DEBUG_ASSERT(m, "MTX44RotTrig():  NULL Mtx44Ptr 'm' ");

    axis |= 0x20;
    switch (axis) {
    case 'x':
        m[0][0] = 1.0f;
        m[0][1] = 0.0f;
        m[0][2] = 0.0f;
        m[0][3] = 0.0f;
        m[1][0] = 0.0f;
        m[1][1] = cosA;
        m[1][2] = -sinA;
        m[1][3] = 0.0f;
        m[2][0] = 0.0f;
        m[2][1] = sinA;
        m[2][2] = cosA;
        m[2][3] = 0.0f;
        m[3][0] = 0.0f;
        m[3][1] = 0.0f;
        m[3][2] = 0.0f;
        m[3][3] = 1.0f;
        break;
    case 'y':
        m[0][0] = cosA;
        m[0][1] = 0.0f;
        m[0][2] = sinA;
        m[0][3] = 0.0f;
        m[1][0] = 0.0f;
        m[1][1] = 1.0f;
        m[1][2] = 0.0f;
        m[1][3] = 0.0f;
        m[2][0] = -sinA;
        m[2][1] = 0.0f;
        m[2][2] = cosA;
        m[2][3] = 0.0f;
        m[3][0] = 0.0f;
        m[3][1] = 0.0f;
        m[3][2] = 0.0f;
        m[3][3] = 1.0f;
        break;
    case 'z':
        m[0][0] = cosA;
        m[0][1] = -sinA;
        m[0][2] = 0.0f;
        m[0][3] = 0.0f;
        m[1][0] = sinA;
        m[1][1] = cosA;
        m[1][2] = 0.0f;
        m[1][3] = 0.0f;
        m[2][0] = 0.0f;
        m[2][1] = 0.0f;
        m[2][2] = 1.0f;
        m[2][3] = 0.0f;
        m[3][0] = 0.0f;
        m[3][1] = 0.0f;
        m[3][2] = 0.0f;
        m[3][3] = 1.0f;
        break;
    default:
        OS_DEBUG_ASSERT(FALSE, "MTX44RotTrig():  invalid 'axis' value ");
        break;
    }
}

void PSMTX44RotTrig(register MtxPtr m, register char axis, register f32 sinA,
                    register f32 cosA) {
    register f32 ftmp0;
    register f32 ftmp1;
    register f32 ftmp2;
    register f32 ftmp3;
    register f32 ftmp4;
    register f32 c_zero = 0.0f;
    register f32 c_one = 1.0f;

    ASM (
        frsp sinA, sinA;
        ori axis, axis, 0x20;
        frsp cosA, cosA;
        cmplwi axis, 'x';
        beq axis_x;
        cmplwi axis, 'y';
        beq axis_y;
        cmplwi axis, 'z';
        beq axis_z;
        b epilogue;
    axis_x:
        psq_st c_one, Mtx_00(m), 1, qr0;
        psq_st c_zero, Mtx_01(m), 0, qr0;
        ps_neg ftmp0, sinA;
        psq_st c_zero, Mtx_03(m), 0, qr0;
        ps_merge00 ftmp1, sinA, cosA;
        psq_st c_zero, Mtx_13(m), 0, qr0;
        ps_merge00 ftmp0, cosA, ftmp0;
        psq_st c_zero, Mtx_23(m), 0, qr0;
        psq_st c_zero, Mtx_31(m), 0, qr0;
        psq_st ftmp1, Mtx_21(m), 0, qr0;
        psq_st ftmp0, Mtx_11(m), 0, qr0;
        psq_st c_one, Mtx_33(m), 1, qr0;
        b epilogue;
    axis_y:
        ps_merge00 ftmp1, cosA, c_zero;
        psq_st c_zero, Mtx_30(m), 0, qr0;
        ps_neg ftmp0, sinA;
        psq_st c_zero, Mtx_12(m), 0, qr0;
        ps_merge00 ftmp3, c_zero, c_one;
        psq_st ftmp1, Mtx_00(m), 0, qr0;
        ps_merge00 ftmp4, ftmp0, c_zero;
        ps_merge00 ftmp2, sinA, c_zero;
        psq_st ftmp3, Mtx_10(m), 0, qr0;
        psq_st ftmp2, Mtx_02(m), 0, qr0;
        psq_st ftmp4, Mtx_20(m), 0, qr0;
        psq_st ftmp1, Mtx_22(m), 0, qr0;
        psq_st ftmp3, Mtx_32(m), 0, qr0;
        b epilogue;
    axis_z:
        psq_st c_zero, Mtx_02(m), 0, qr0;
        ps_neg ftmp0, sinA;
        psq_st c_zero, Mtx_12(m), 0, qr0;
        ps_merge00 ftmp1, sinA, cosA;
        psq_st c_zero, Mtx_20(m), 0, qr0;
        ps_merge00 ftmp2, c_one, c_zero;
        psq_st c_zero, Mtx_30(m), 0, qr0;
        ps_merge00 ftmp3, c_zero, c_one;
        psq_st ftmp1, Mtx_10(m), 0, qr0;
        ps_merge00 ftmp4, cosA, ftmp0;
        psq_st ftmp2, Mtx_22(m), 0, qr0;
        psq_st ftmp3, Mtx_32(m), 0, qr0;
        psq_st ftmp4, Mtx_00(m), 0, qr0;
    epilogue:
    )
}

void C_MTX44RotAxisRad(MtxPtr m, CVecPtr axis, f32 rad) {
    Vec vN;
    f32 s;
    f32 c;
    f32 t;
    f32 x;
    f32 y;
    f32 z;
    // The DWARF build we have is outdated, these names are added
    f32 sqx;
    f32 sqy;
    f32 sqz;

    OS_DEBUG_ASSERT(m, "MTX44RotAxisRad():  NULL Mtx44Ptr 'm' ");
    OS_DEBUG_ASSERT(axis, "MTX44RotAxisRad():  NULL VecPtr 'axis' ");

    s = sinf(rad);
    c = cosf(rad);
    t = 1.0f - c;

    C_VECNormalize(axis, &vN);

    x = vN.x;
    y = vN.y;
    z = vN.z;
    sqx = x * x;
    sqy = y * y;
    sqz = z * z;

    m[0][0] = t * sqx + c;
    m[0][1] = t * x * y - s * z;
    m[0][2] = t * x * z + s * y;
    m[0][3] = 0.0f;
    m[1][0] = t * x * y + s * z;
    m[1][1] = t * sqy + c;
    m[1][2] = t * y * z - s * x;
    m[1][3] = 0.0f;
    m[2][0] = t * x * z - s * y;
    m[2][1] = t * y * z + s * x;
    m[2][2] = t * sqz + c;
    m[2][3] = 0.0f;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

// Subroutine for PSMTX44RotAxisRad
// Paired singles don't have good ways of doing trig so we rely on a C caller
// DWARF doesn't have this, so copied from __PSMTXRotAxisRadInternal
static void __PSMTX44RotAxisRadInternal(register MtxPtr m,
                                        register CVecPtr axis, register f32 sT,
                                        register f32 cT) {
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

    ASM (
        frsp cT, cT;
        psq_l tmp0, Vec.x(axis), 0, qr0;
        frsp sT, sT;
        lfs tmp1, Vec.z(axis);
        ps_mul tmp2, tmp0, tmp0;
        fadds tmp7, tmp9, tmp9;
        ps_madd tmp3, tmp1, tmp1, tmp2;
        fsubs fc0, tmp9, tmp9;
        ps_sum0 tmp4, tmp3, tmp1, tmp2;
        fsubs tT, tmp7, cT;
        frsqrte tmp5, tmp4;
        ps_merge00 tmp7, fc0, tmp7;
        fmuls tmp2, tmp5, tmp5;
        fmuls tmp3, tmp5, tmp9;
        psq_st fc0, Mtx_30(m), 0, qr0;
        fnmsubs tmp2, tmp2, tmp4, tmp8;
        fmuls tmp5, tmp2, tmp3;
        psq_st tmp7, Mtx_32(m), 0, qr0;
        ps_merge00 cT, cT, cT;
        ps_muls0 tmp0, tmp0, tmp5;
        ps_muls0 tmp1, tmp1, tmp5;
        ps_muls0 tmp4, tmp0, tT;
        ps_muls0 tmp9, tmp0, sT;
        ps_muls0 tmp5, tmp1, tT;
        ps_muls1 tmp3, tmp4, tmp0;
        ps_muls0 tmp2, tmp4, tmp0;
        ps_muls0 tmp4, tmp4, tmp1;
        fnmsubs tmp6, tmp1, sT, tmp3;
        fmadds tmp7, tmp1, sT, tmp3;
        ps_neg tmp0, tmp9;
        ps_sum0 tmp8, tmp4, fc0, tmp9;
        ps_sum0 tmp2, tmp2, tmp6, cT;
        ps_sum1 tmp3, cT, tmp7, tmp3;
        ps_sum0 tmp6, tmp0, fc0, tmp4;
        psq_st tmp8, Mtx_02(m), 0, qr0;
        ps_sum0 tmp0, tmp4, tmp4, tmp0;
        psq_st tmp2, Mtx_00(m), 0, qr0;
        ps_muls0 tmp5, tmp5, tmp1;
        psq_st tmp3, Mtx_10(m), 0, qr0;
        ps_sum1 tmp4, tmp9, tmp0, tmp4;
        psq_st tmp6, Mtx_12(m), 0, qr0;
        ps_sum0 tmp5, tmp5, fc0, cT;
        psq_st tmp4, Mtx_20(m), 0, qr0;
        psq_st tmp5, Mtx_22(m), 0, qr0;
    )
}

void PSMTX44RotAxisRad(MtxPtr m, CVecPtr axis, f32 rad) {
    f32 s;
    f32 c;

    s = sinf(rad);
    c = cosf(rad);
    __PSMTX44RotAxisRadInternal(m, axis, s, c);
}
