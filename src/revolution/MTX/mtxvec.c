#include <revolution/MTX.h>
#include <revolution/MTX/internal/mtxAssert.h>

// clang-format off
asm void PSMTXMultVec(register CMtxPtr m, register CVecPtr src,
                      register VecPtr dst) {
    psq_l f0, Vec.x(src), 0, qr0
    psq_l f2, Mtx_00(m), 0, qr0
    psq_l f1, Vec.z(src), 1, qr0
    ps_mul f4, f2, f0
    psq_l f3, Mtx_02(m), 0, qr0
    ps_madd f5, f3, f1, f4
    psq_l f8, Mtx_10(m), 0, qr0
    ps_sum0 f6, f5, f6, f5
    psq_l f9, Mtx_12(m), 0, qr0
    ps_mul f10, f8, f0
    psq_st f6, Vec.x(dst), 1, qr0
    ps_madd f11, f9, f1, f10
    psq_l f2, Mtx_20(m), 0, qr0
    ps_sum0 f12, f11, f12, f11
    psq_l f3, Mtx_22(m), 0, qr0
    ps_mul f4, f2, f0
    psq_st f12, Vec.y(dst), 1, qr0
    ps_madd f5, f3, f1, f4
    ps_sum0 f6, f5, f6, f5
    psq_st f6, Vec.z(dst), 1, qr0
} // clang-format on
