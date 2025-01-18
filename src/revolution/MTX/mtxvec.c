#include <revolution/MTX.h>

asm void PSMTXMultVec(register const Mtx mtx, register const Vec* vec,
                      register Vec* out) {
    // clang-format off
    nofralloc

    // Calculate X transformation (dot(mtx[0], vec))
    psq_l   f0, Vec.x(vec), 0, 0 // VX,                       VY
    psq_l   f2, 0(mtx),     0, 0 // M0X,                      M0Y
    psq_l   f1, Vec.z(vec), 1, 0 // VZ,                       1
    ps_mul  f4, f2, f0           // M0X*VX,                   M0Y*VY
    psq_l   f3, 8(mtx),     0, 0 // M0Z,                      M0W
    ps_madd f5, f3, f1, f4       // M0Z*VZ+M0X*VX,            M0W+M0Y*VY
    psq_l   f8, 16(mtx),    0, 0 // M1X,                      M1Y
    ps_sum0 f6, f5, f6, f5       // M0Z*VZ+M0X*VX+M0W+M0Y*VY, junk

    // Head start on Y transformation
    psq_l  f9,  24(mtx), 0, 0    // M1Z,    M1W
    ps_mul f10, f8, f0           // M1X*VX, M1Y*VY

    // tx = M0X*VX + M0Y*VY + M0Z*VZ + M0W
    psq_st f6, Vec.x(out), 1, 0

    // Calculate Y transformation (dot(mtx[1], vec))
    ps_madd f11, f9,  f1,  f10 // M1Z*VZ+M1X*VX,            M1W+M1Y*VY
    psq_l   f2,  32(mtx), 0, 0 // M2X,                      M2Y
    ps_sum0 f12, f11, f12, f11 // M1Z*VZ+M1X*VX+M1W+M1Y*VY, junk

    // Head start on Z transformation
    psq_l  f3, 40(mtx), 0, 0 // M2Z,    M2W
    ps_mul f4, f2, f0        // M2X*VX, M2Y*VY

    // ty = M1X*VX + M1Y*VY + M1Z*VZ + M1W
    psq_st f12, Vec.y(out), 1, 0

    // Calculate Z transformation (dot(mtx[2], vec))
    ps_madd f5, f3, f1, f4 // M2Z*VZ+M2X*VX,            M2W+M2Y*VY
    ps_sum0 f6, f5, f6, f5 // M2Z*VZ+M2X*VX+M2W+M2Y*VY, junk

    // tz = M2X*VX + M2Y*VY + M2Z*VZ + M2W
    psq_st f6, Vec.z(out), 1, 0
    
    blr
    // clang-format on
}