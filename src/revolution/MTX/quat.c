#include <math.h>
#include <revolution/MTX.h>

DECOMP_FORCELITERAL(quat_c, FLT_EPSILON, 1.0f, 0.0f);

void PSQUATMultiply(register const Quaternion* a, register const Quaternion* b,
                    register Quaternion* prod) {
    register f32 axy, azw;
    register f32 bxy, bzw;
    register f32 naxay, naxy, nazw;
    register f32 work1, work2, work3, work4, work5;

    // clang-format off
    asm {
        // Load qA components
        psq_l axy, Quaternion.x(a), 0, 0 // AX, AY
        psq_l azw, Quaternion.z(a), 0, 0 // AZ, AW
        // Load qB components
        psq_l bxy, Quaternion.x(b), 0, 0 // BX, BY
        psq_l bzw, Quaternion.z(b), 0, 0 // BZ, BW

        // Negate copy of qA components
        ps_neg naxy, axy // -AX, -AY
        ps_neg nazw, azw // -AZ, -AW

        // Compute parts of product
        ps_muls0   work1, azw,   bxy        //  AZ*BX,        AW*BX
        ps_merge01 naxay, naxy,  axy        // -AX,           AY
        ps_merge01 work2, nazw,  azw        // -AZ,           AW
        ps_muls0   work3, naxy,  bxy        // -AX*BX,       -AY*BX
        ps_muls1   work4, naxay, bxy        // -AX*BY,        AY*BY
        ps_madds0  work1, naxay, bzw, work1 // -AX*BZ+AZ*BX,  AY*BZ+AW*BX
        ps_muls1   work5, work2, bxy        // -AZ*BY,        AW*BY
        ps_madds0  work3, work2, bzw, work3 // -AZ*BZ-AX*BX,  AW*BZ-AY*BX
        ps_merge10 work1, work1, work1      //  AY*BZ+AW*BX, -AX*BZ+AZ*BX
        ps_madds1  work5, axy,   bzw, work5 // -AX*BW-AZ*BY, -AY*BW+AW*BY
        ps_merge10 work3, work3, work3      //  AW*BZ-AY*BX, -AZ*BZ-AX*BX
        ps_madds1  work4, nazw,  bzw, work4 // -AZ*BW-AX*BY, -AW*BW+AY*BY

        // Put everything together
        ps_add work1, work1, work5 // AY*BZ+AW*BX-AX*BW-AZ*BY, -AX*BZ+AZ*BX-AY*BW+AW*BY
        ps_sub work3, work3, work4 // AW*BZ-AY*BX+AZ*BW-AX*BY, -AZ*BZ-AX*BX+AW*BW+AY*BY

        // Store result
        psq_st work1, Quaternion.x(prod), 0, 0
        psq_st work3, Quaternion.z(prod), 0, 0
    }
    // clang-format on
}

void PSQUATNormalize(register const Quaternion* in, register Quaternion* out) {
    register f32 xy, zw;
    register f32 xy2, dot;
    register f32 work0, work1, work2, work3;
    register f32 c_epsilon, c_half, c_three;

    c_epsilon = FLT_EPSILON;
    c_half = 0.5f;
    c_three = 3.0f;

    // clang-format off
    asm {
        // Load quaternion components
        psq_l xy, Quaternion.x(in), 0, 0
        psq_l zw, Quaternion.z(in), 0, 0

        // Compute dot product with self
        ps_mul  xy2, xy,  xy       // X^2,             Y^2
        ps_madd dot, zw,  zw,  xy2 // Z^2+X^2,         W^2+Y^2
        ps_sum0 dot, dot, dot, dot // Z^2+X^2+W^2+Y^2, junk

        // Reciprocal square root
        frsqrte work0, dot

        // Refine estimate using Newton-Raphson method
        // y = 1 / sqrt(x)
        fmul   work3, work0, work0        // rsqrt^2
        fmul   work0, work0, c_half       // rsqrt * 0.5
        fnmsub work3, work3, dot, c_three // (3 - x * rsqrt^2)
        fmul   work0, work3, work0        // (3 - x * rsqrt^2) * (rsqrt * 0.5)

        // Set magnitude to zero if too small
        // (dot - epsilon > zero) ? rsqrt : zero
        ps_sub work1, dot,       c_epsilon
        ps_sub work2, c_epsilon, c_epsilon
        ps_sel work0, work1,     work0, work2

        // Scale components to normalize
        ps_muls0 xy, xy, work0
        ps_muls0 zw, zw, work0

        // Store result
        psq_st xy, Quaternion.x(out), 0, 0
        psq_st zw, Quaternion.z(out), 0, 0
    }
    // clang-format on
}

void C_QUATMtx(Quaternion* quat, const Mtx mtx) {
    f32 root, trace;
    u32 dmax, dnext, dlast;
    u32 next[3] = {1, 2, 0};
    f32 temp[3];

    trace = mtx[0][0] + mtx[1][1] + mtx[2][2];

    if (trace > 0.0f) {
        root = sqrtf(1.0f + trace);
        quat->w = root * 0.5f;

        root = 0.5f / root;
        quat->x = root * (mtx[2][1] - mtx[1][2]);
        quat->y = root * (mtx[0][2] - mtx[2][0]);
        quat->z = root * (mtx[1][0] - mtx[0][1]);
    } else {
        dmax = 0;

        if (mtx[1][1] > mtx[dmax][dmax]) {
            dmax = 1;
        }

        if (mtx[2][2] > mtx[dmax][dmax]) {
            dmax = 2;
        }

        dnext = next[dmax];
        dlast = next[dnext];

        root = sqrtf(mtx[dmax][dmax] - (mtx[dnext][dnext] + mtx[dlast][dlast]) +
                     1.0f);
        temp[dmax] = 0.5f * root;

        if (0.0f != root) {
            root = 0.5f / root;
        }

        quat->w = root * (mtx[dlast][dnext] - mtx[dnext][dlast]);
        temp[dnext] = root * (mtx[dmax][dnext] + mtx[dnext][dmax]);
        temp[dlast] = root * (mtx[dmax][dlast] + mtx[dlast][dmax]);

        quat->x = temp[0];
        quat->y = temp[1];
        quat->z = temp[2];
    }
}

void C_QUATSlerp(const Quaternion* a, const Quaternion* b, Quaternion* out,
                 f32 t) {
    f32 dot;
    f32 coeffa, coeffb;
    f32 theta, sintheta;

    dot = a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
    coeffb = 1.0f;

    if (dot < 0) {
        dot = -dot;
        coeffb = -coeffb;
    }

    if (dot <= 1.0f - FLT_EPSILON) {
        theta = acosf(dot);
        sintheta = sinf(theta);

        coeffa = sinf((1.0f - t) * theta) / sintheta;
        coeffb *= sinf(t * theta) / sintheta;
    } else {
        coeffa = 1.0f - t;
        coeffb *= t;
    }

    out->x = coeffa * a->x + coeffb * b->x;
    out->y = coeffa * a->y + coeffb * b->y;
    out->z = coeffa * a->z + coeffb * b->z;
    out->w = coeffa * a->w + coeffb * b->w;
}
