#include <revolution/MTX.h>

asm void PSVECAdd(register const Vec* a, register const Vec* b,
                  register Vec* sum) {
    // clang-format off
    nofralloc

    // Sum X,Y components
    psq_l  f2, Vec.x(a), 0, 0
    psq_l  f4, Vec.x(b), 0, 0
    ps_add f6, f2, f4

    // Store result
    psq_st f6, Vec.x(sum), 0, 0

    // Sum Z component
    psq_l  f3, Vec.z(a), 1, 0
    psq_l  f5, Vec.z(b), 1, 0
    ps_add f7, f3, f5

    // Store result
    psq_st f7, Vec.z(sum), 1, 0

    blr
    // clang-format on
}

void PSVECScale(register const Vec* in, register Vec* out, register f32 scale) {
    register f32 xy, z;
    register f32 sxy, sz;

    // clang-format off
    asm {
        // Load components
        psq_l xy, Vec.x(in), 0, 0
        psq_l z,  Vec.z(in), 1, 0

        // Scale components
        ps_muls0 sxy, xy, scale
        ps_muls0 sz,  z,  scale

        // Store result
        psq_st sxy, Vec.x(out), 0, 0
        psq_st sz,  Vec.z(out), 1, 0
    }
    // clang-format on
}

void PSVECNormalize(register const Vec* in, register Vec* out) {
    register f32 c_half, c_three;
    register f32 xy, z;
    register f32 z2;
    register f32 dot;
    register f32 work0, work1, work2;

    c_half = 0.5f;
    c_three = 3.0f;

    // clang-format off
    asm {
        // Load vector components
        psq_l xy, Vec.x(in), 0, 0
        psq_l z,  Vec.z(in), 1, 0

        // Compute dot product with self
        ps_mul  work0, xy, xy       // X^2,         Y^2
        ps_madd z2,    z,  z, work0 // Z^2+X^2,     junk
        ps_sum0 dot,   z2, z, work0 // Z^2+X^2+Y^2, junk

        // Reciprocal square root
        frsqrte work0, dot
        
        // Refine estimate using Newton-Raphson method
        // y = 1 / sqrt(x)
        fmuls   work1, work0, work0        // rsqrt^2
        fmuls   work2, work0, c_half       // rsqrt * 0.5
        fnmsubs work1, work1, dot, c_three // (3 - x * rsqrt^2)
        fmuls   work0, work1, work2        // (3 - x * rsqrt^2) * (rsqrt * 0.5)

        // Scale components to normalize
        ps_muls0 xy, xy, work0
        ps_muls0 z,  z,  work0

        // Store result
        psq_st xy, Vec.x(out), 0, 0
        psq_st z,  Vec.z(out), 1, 0
    }
    // clang-format on
}

f32 PSVECMag(register const Vec* v) {
    register f32 xy, xy2;
    register f32 z, z2;
    register f32 dot;
    register f64 rsqrt;
    register f32 work0, work1;
    register f32 c_three, c_half, c_zero;

    c_half = 0.5f;
    // clang-format off
    asm {
        // Load vector components
        psq_l xy, Vec.x(v), 0, 0
        lfs   z,  Vec.z(v)

        // Compute dot product with self
        ps_mul  xy2, xy, xy       // X^2,         Y^2
        ps_madd z2,  z,  z,   xy2 // Z^2+X^2,     junk
        ps_sum0 dot, z2, xy2, xy2 // Z^2+X^2+Y^2, junk

        // Get zero
        fsubs c_zero, c_half, c_half
    }
    // clang-format on

    // Avoid problematic square root where dot is zero
    if (dot == c_zero) {
        return dot;
    }

    // Estimate reciprocal square root
    rsqrt = __frsqrte(dot);

    c_three = 3.0f;
    // clang-format off
    asm {
        // Refine estimate using Newton-Raphson method
        // y = 1 / sqrt(x)
        fmuls   work0, rsqrt, rsqrt        // rsqrt^2
        fmuls   work1, rsqrt, c_half       // rsqrt * 0.5
        fnmsubs work0, work0, dot, c_three // (3 - x * rsqrt^2)
        fmuls   work1, work0, work1        // (3 - x * rsqrt^2) * (rsqrt * 0.5)

        // Convert rsqrt -> sqrt
        // x * rsqrt(x) == sqrt(x)
        fmuls dot, dot, work1
    }
    // clang-format on

    return dot;
}

asm f32 PSVECDotProduct(register const Vec* a, register const Vec* b) {
    // clang-format off
    nofralloc

    // Compute Y,Z products
    psq_l  f2, Vec.y(a), 0, 0
    psq_l  f3, Vec.y(b), 0, 0
    ps_mul f2, f2, f3 // ABY, ABZ

    // Compute X product
    psq_l   f5, Vec.x(a), 0, 0
    psq_l   f4, Vec.x(b), 0, 0
    ps_madd f3, f5, f4, f2 // ABX+ABY, junk

    // Compute dot product
    ps_sum0 f1, f3, f2, f2 // ABX+ABY+ABZ, junk

    blr
    // clang-format on
}

asm void PSVECCrossProduct(register const Vec* a, register const Vec* b,
                           register Vec* prod) {
    // clang-format off
    nofralloc

    // Load vector components
    psq_l      f1, Vec.x(b), 0, 0 // BX, BY
    lfs        f2, Vec.z(a)       // AZ, AZ
    psq_l      f0, Vec.x(a), 0, 0 // AX, AY
    ps_merge10 f6, f1, f1         // BY, BX
    lfs        f3, Vec.z(b)       // BZ, BZ

    // Compute cross product components
    ps_mul   f4, f1, f2     // BX*AZ,       BY*AZ
    ps_muls0 f7, f1, f0     // BX*AX,       BY*AX
    ps_msub  f5, f0, f3, f4 // AX*BZ-BX*AZ, AY*BZ-BY*AZ
    ps_msub  f8, f0, f6, f7 // AX*BY-BX*AX, AY*BX-BY*AX

    // Manipulate storage
    ps_merge11 f9,  f5, f5 // AY*BZ-BY*AZ, AY*BZ-BY*AZ
    ps_merge01 f10, f5, f8 // AX*BZ-BX*AZ, AY*BX-BY*AX

    // Store cross product X
    // cx = AY*BZ-BY*AZ
    psq_st f9, Vec.x(prod), 1, 0

    // Store cross product Y/Z
    // Negate to fix formula
    // cy = -(AX*BZ-BX*AZ) -> BX*AZ-AX*BZ
    // cz = -(AY*BX-BY*AX) -> BY*AX-AY*BX
    ps_neg f10, f10
    psq_st f10, Vec.y(prod), 0, 0

    blr
    // clang-format on
}

void C_VECHalfAngle(register const Vec* a, register const Vec* b,
                    register Vec* half) {
    Vec na, nb, ns;

    na.x = -a->x;
    na.y = -a->y;
    na.z = -a->z;

    nb.x = -b->x;
    nb.y = -b->y;
    nb.z = -b->z;

    PSVECNormalize(&na, &na);
    PSVECNormalize(&nb, &nb);
    PSVECAdd(&na, &nb, &ns);

    if (PSVECDotProduct(&ns, &ns) > 0.0f) {
        PSVECNormalize(&ns, half);
    } else {
        *half = ns;
    }
}

f32 PSVECSquareDistance(register const Vec* a, register const Vec* b) {
    register f32 ayz, byz;
    register f32 axy, bxy;
    register f32 dxy, dyz;
    register f32 dist;

    // clang-format off
    asm {
        // Load vector components
        psq_l axy, Vec.x(a), 0, 0
        psq_l ayz, Vec.y(a), 0, 0 
        psq_l bxy, Vec.x(b), 0, 0
        psq_l byz, Vec.y(b), 0, 0

        // Compute differences
        ps_sub dxy, axy, bxy
        ps_sub dyz, ayz, byz

        // Compute distance
        ps_mul  dyz,  dyz,  dyz
        ps_madd dist, dxy,  dxy, dyz
        ps_sum0 dist, dist, dyz, dyz
    }
    // clang-format on

    return dist;
}
