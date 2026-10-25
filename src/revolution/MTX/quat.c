#include <revolution/MTX.h>
#include <revolution/MTX/internal/mtxAssert.h>
#include <revolution/OS.h>

#include <math.h>

#define EPSILON 0.00001f

void C_QUATAdd(CQuaternionPtr p, CQuaternionPtr q, QuaternionPtr r) {
    OS_DEBUG_ASSERT(p, "QUATAdd():  NULL QuaternionPtr 'p' ");
    OS_DEBUG_ASSERT(q, "QUATAdd():  NULL QuaternionPtr 'q' ");
    OS_DEBUG_ASSERT(r, "QUATAdd():  NULL QuaternionPtr 'r' ");

    r->x = p->x + q->x;
    r->y = p->y + q->y;
    r->z = p->z + q->z;
    r->w = p->w + q->w;
}

void PSQUATAdd(register CQuaternionPtr p, register CQuaternionPtr q,
               register QuaternionPtr r) {
    register f32 tmp0;
    register f32 tmp1;
    register f32 tmp2;
    register f32 tmp3;
    register f32 tmp4;
    register f32 tmp5;

    ASM (
        psq_l tmp0, Quaternion.x(p), 0, qr0;
        psq_l tmp1, Quaternion.x(q), 0, qr0;
        ps_add tmp2, tmp0, tmp1;
        psq_st tmp2, Quaternion.x(r), 0, qr0;
        psq_l tmp3, Quaternion.z(p), 0, qr0;
        psq_l tmp4, Quaternion.z(q), 0, qr0;
        ps_add tmp5, tmp3, tmp4;
        psq_st tmp5, Quaternion.z(r), 0, qr0;
   )
}

void C_QUATSubtract(CQuaternionPtr p, CQuaternionPtr q, QuaternionPtr r) {
    OS_DEBUG_ASSERT(p, "QUATSubtract():  NULL QuaternionPtr 'p' ");
    OS_DEBUG_ASSERT(q, "QUATSubtract():  NULL QuaternionPtr 'q' ");
    OS_DEBUG_ASSERT(r, "QUATSubtract():  NULL QuaternionPtr 'r' ");

    r->x = p->x - q->x;
    r->y = p->y - q->y;
    r->z = p->z - q->z;
    r->w = p->w - q->w;
}

void PSQUATSubtract(register CQuaternionPtr p, register CQuaternionPtr q,
                    register QuaternionPtr r) {
    register f32 tmp0;
    register f32 tmp1;
    register f32 tmp2;
    register f32 tmp3;
    register f32 tmp4;
    register f32 tmp5;

    ASM (
        psq_l tmp0, Quaternion.x(p), 0, qr0;
        psq_l tmp1, Quaternion.x(q), 0, qr0;
        ps_sub tmp2, tmp0, tmp1;
        psq_st tmp2, Quaternion.x(r), 0, qr0;
        psq_l tmp3, Quaternion.z(p), 0, qr0;
        psq_l tmp4, Quaternion.z(q), 0, qr0;
        ps_sub tmp5, tmp3, tmp4;
        psq_st tmp5, Quaternion.z(r), 0, qr0;
   )
}

void C_QUATMultiply(CQuaternionPtr p, CQuaternionPtr q, QuaternionPtr pq) {
    QuaternionPtr r;
    Quaternion rTmp;

    OS_DEBUG_ASSERT(p, "QUATMultiply():  NULL QuaternionPtr 'p' ");
    OS_DEBUG_ASSERT(q, "QUATMultiply():  NULL QuaternionPtr 'q' ");
    OS_DEBUG_ASSERT(pq, "QUATMultiply():  NULL QuaternionPtr 'pq' ");

    if (p == pq || q == pq) {
        r = &rTmp;
    } else {
        r = pq;
    }

    r->w = p->w * q->w - p->x * q->x - p->y * q->y - p->z * q->z;
    r->x = p->w * q->x + p->x * q->w + p->y * q->z - p->z * q->y;
    r->y = p->w * q->y + p->y * q->w + p->z * q->x - p->x * q->z;
    r->z = p->w * q->z + p->z * q->w + p->x * q->y - p->y * q->x;

    if (r == &rTmp) {
        *pq = rTmp;
    }
}

void PSQUATMultiply(register CQuaternionPtr p, register CQuaternionPtr q,
                    register QuaternionPtr pq) {
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
    register f32 tmp10;

    ASM (
        psq_l tmp0, Quaternion.x(p), 0, qr0;
        psq_l tmp1, Quaternion.z(p), 0, qr0;
        psq_l tmp2, Quaternion.x(q), 0, qr0;
        ps_neg tmp5, tmp0;
        psq_l tmp3, Quaternion.z(q), 0, qr0;
        ps_neg tmp6, tmp1;
        ps_merge01 tmp4, tmp5, tmp0;
        ps_muls0 tmp7, tmp1, tmp2;
        ps_muls0 tmp5, tmp5, tmp2;
        ps_merge01 tmp8, tmp6, tmp1;
        ps_muls1 tmp9, tmp4, tmp2;
        ps_madds0 tmp7, tmp4, tmp3, tmp7;
        ps_muls1 tmp10, tmp8, tmp2;
        ps_madds0 tmp5, tmp8, tmp3, tmp5;
        ps_madds1 tmp9, tmp6, tmp3, tmp9;
        ps_merge10 tmp7, tmp7, tmp7;
        ps_madds1 tmp10, tmp0, tmp3, tmp10;
        ps_merge10 tmp5, tmp5, tmp5;
        ps_add tmp7, tmp7, tmp10;
        psq_st tmp7, Quaternion.x(pq), 0, qr0;
        ps_sub tmp5, tmp5, tmp9;
        psq_st tmp5, Quaternion.z(pq), 0, qr0;
    )
}

void C_QUATScale(CQuaternionPtr q, QuaternionPtr r, f32 scale) {
    OS_DEBUG_ASSERT(q, "QUATScale():  NULL QuaternionPtr 'q' ");
    OS_DEBUG_ASSERT(r, "QUATScale():  NULL QuaternionPtr 'r' ");

    r->x = q->x * scale;
    r->y = q->y * scale;
    r->z = q->z * scale;
    r->w = q->w * scale;
}

void PSQUATScale(register CQuaternionPtr q, register QuaternionPtr r,
                 register f32 mult) {
    register f32 tmp0;
    register f32 tmp1;

    ASM (
        psq_l tmp0, Quaternion.x(q), 0, qr0;
        psq_l tmp1, Quaternion.z(q), 0, qr0;
        ps_muls0 tmp0, tmp0, mult;
        psq_st tmp0, Quaternion.x(r), 0, qr0;
        ps_muls0 tmp1, tmp1, mult;
        psq_st tmp1, Quaternion.z(r), 0, qr0;
    )
}

f32 C_QUATDotProduct(CQuaternionPtr p, CQuaternionPtr q) {
    OS_DEBUG_ASSERT(p, "QUATDotProduct():  NULL QuaternionPtr 'p' ");
    OS_DEBUG_ASSERT(q, "QUATDotProduct():  NULL QuaternionPtr 'q' ");
    return q->x * p->x + q->y * p->y + q->z * p->z + q->w * p->w;
}

f32 PSQUATDotProduct(register CQuaternionPtr p, register CQuaternionPtr q) {
    register f32 tmp0;
    register f32 tmp1;
    register f32 tmp2;
    register f32 tmp3;
    register f32 tmp4;

    ASM (
        psq_l tmp0, Quaternion.x(p), 0, qr0;
        psq_l tmp2, Quaternion.x(q), 0, qr0;
        ps_mul tmp4, tmp0, tmp2;
        psq_l tmp1, Quaternion.z(p), 0, qr0;
        psq_l tmp3, Quaternion.z(q), 0, qr0;
        ps_madd tmp4, tmp1, tmp3, tmp4;
        ps_sum0 tmp4, tmp4, tmp4, tmp4;
    )

    return tmp4;
}

void C_QUATNormalize(CQuaternionPtr src, QuaternionPtr unit) {
    f32 norm;

    OS_DEBUG_ASSERT(src, "QUATNormalize():  NULL QuaternionPtr 'src' ");
    OS_DEBUG_ASSERT(unit, "QUATNormalize():  NULL QuaternionPtr 'unit' ");

    norm =
        src->x * src->x + src->y * src->y + src->z * src->z + src->w * src->w;
    if (norm >= EPSILON) {
        norm = 1.0f / sqrtf(norm);
        unit->x = src->x * norm;
        unit->y = src->y * norm;
        unit->z = src->z * norm;
        unit->w = src->w * norm;
    } else {
        unit->x = unit->y = unit->z = unit->w = 0.0f;
    }
}

void PSQUATNormalize(register CQuaternionPtr src, register QuaternionPtr unit) {
    register f32 tmp0;
    register f32 tmp1;
    register f32 tmp2;
    register f32 tmp3;
    register f32 tmp4 = EPSILON;
    register f32 tmp5;
    register f32 tmp6;
    register f32 tmp7;
    register f32 tmp8;
    register f32 c_half = 0.5f;
    register f32 c_three = 3.0f;

    ASM (
        psq_l tmp0, Quaternion.x(src), 0, qr0;
        ps_mul tmp2, tmp0, tmp0;
        psq_l tmp1, Quaternion.z(src), 0, qr0;
        ps_sub tmp5, tmp4, tmp4;
        ps_madd tmp2, tmp1, tmp1, tmp2;
        ps_sum0 tmp2, tmp2, tmp2, tmp2;
        frsqrte tmp3, tmp2;
        ps_sub tmp4, tmp2, tmp4;
        fmul tmp6, tmp3, tmp3;
        fmul tmp3, tmp3, c_half;
        fnmsub tmp6, tmp6, tmp2, c_three;
        fmul tmp3, tmp6, tmp3;
        ps_sel tmp3, tmp4, tmp3, tmp5;
        ps_muls0 tmp7, tmp0, tmp3;
        ps_muls0 tmp8, tmp1, tmp3;
        psq_st tmp7, Quaternion.x(unit), 0, qr0;
        psq_st tmp8, Quaternion.z(unit), 0, qr0;
    )
}

void C_QUATInverse(CQuaternionPtr src, QuaternionPtr inv) {
    f32 norm;
    f32 mult;

    OS_DEBUG_ASSERT(src, "QUATInverse():  NULL QuaternionPtr 'src' ");
    OS_DEBUG_ASSERT(inv, "QUATInverse():  NULL QuaternionPtr 'inv' ");

    norm =
        src->x * src->x + src->y * src->y + src->z * src->z + src->w * src->w;
    if (norm == 0.0f) {
        norm = 1.0f;
    }
    mult = 1.0f / norm;

    inv->x = -src->x * mult;
    inv->y = -src->y * mult;
    inv->z = -src->z * mult;
    inv->w = src->w * mult;
}

void PSQUATInverse(register CQuaternionPtr src, register QuaternionPtr inv) {
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
    register f32 tmp10 = 1.0f;

    ASM (
        psq_l tmp0, Quaternion.x(src), 0, qr0;
        ps_mul tmp5, tmp0, tmp0;
        ps_sub tmp9, tmp10, tmp10;
        psq_l tmp1, Quaternion.z(src), 0, qr0;
        ps_madd tmp5, tmp1, tmp1, tmp5;
        ps_add tmp8, tmp10, tmp10;
        ps_sum0 tmp5, tmp5, tmp5, tmp5;
        fcmpu cr0, tmp5, tmp9;
        beq branch;
        fres tmp10, tmp5;
        ps_neg tmp6, tmp5;
        ps_nmsub tmp5, tmp5, tmp10, tmp8;
        ps_mul tmp10, tmp10, tmp5;
        b branch;
    branch:
        ps_neg tmp7, tmp10;
        ps_muls1 tmp2, tmp10, tmp1;
        ps_muls0 tmp3, tmp0, tmp7;
        psq_st tmp2, Quaternion.w(inv), 1, qr0;
        ps_muls0 tmp4, tmp1, tmp7;
        psq_st tmp3, Quaternion.x(inv), 0, qr0;
        psq_st tmp4, Quaternion.z(inv), 1, qr0;
    )
}

void C_QUATDivide(CQuaternionPtr p, CQuaternionPtr q, QuaternionPtr r) {
    Quaternion tmp;

    OS_DEBUG_ASSERT(p, "QUATDivide():  NULL QuaternionPtr 'p' ");
    OS_DEBUG_ASSERT(q, "QUATDivide():  NULL QuaternionPtr 'q' ");
    OS_DEBUG_ASSERT(r, "QUATDivide():  NULL QuaternionPtr 'r' ");

    C_QUATInverse(q, &tmp);
    C_QUATMultiply(&tmp, p, r);
}

void PSQUATDivide(CQuaternionPtr p, CQuaternionPtr q, QuaternionPtr r) {
    Quaternion tmp;
    PSQUATInverse(q, &tmp);
    PSQUATMultiply(&tmp, p, r);
}

void C_QUATExp(CQuaternionPtr q, QuaternionPtr r) {
    f32 mag;
    f32 sinmag;

    OS_DEBUG_ASSERT(q, "QUATExp():  NULL QuaternionPtr 'q' ");
    OS_DEBUG_ASSERT(r, "QUATExp():  NULL QuaternionPtr 'r' ");
    OS_DEBUG_ASSERT(q->w == 0.0f, "QUATExp():  'q' is not a pure quaternion. ");

    mag = sqrtf(q->x * q->x + q->y * q->y + q->z * q->z);
    sinmag = 1.0f;
    if (mag > EPSILON) {
        sinmag = sinf(mag) / mag;
    }

    // \frac{\vec{v}}{\|\vec{v}\|} \sin\|\vec{v}\|
    // \implies \vec{v} \frac{\sin\|\vec{v}\|}{\|\vec{v}\|}
    // Instead of normalizing and then scaling, we only need one scalar
    r->x = sinmag * q->x;
    r->y = sinmag * q->y;
    r->z = sinmag * q->z;
    r->w = cosf(mag);
}

void C_QUATLogN(CQuaternionPtr q, QuaternionPtr r) {
    f32 mag;
    f32 tmp;

    OS_DEBUG_ASSERT(q, "QUATLogN():  NULL QuaternionPtr 'q' ");
    OS_DEBUG_ASSERT(r, "QUATLogN():  NULL QuaternionPtr 'r' ");

    mag = q->x * q->x + q->y * q->y + q->z * q->z;

    // Release doesn't quite optimize this out
#ifndef NDEBUG
    // We also need this local variable scoped in its own block for debug
    {
        // Broken, should be w^2, not z^2
        f32 magCheck = mag + q->z * q->z;
        if (magCheck < 1.0f - EPSILON || magCheck > 1.0f + EPSILON) {
            // #if 0 doesn't have same codegen
            (void)0;
        }
    }
#endif

    mag = sqrtf(mag);
    tmp = atan2f(mag, q->w);
    if (mag > 0.0f) {
        mag = tmp / mag;
    }

    r->x = mag * q->x;
    r->y = mag * q->y;
    r->z = mag * q->z;
    r->w = 0.0f;
}

void C_QUATMakeClosest(CQuaternionPtr q, CQuaternionPtr qto, QuaternionPtr r) {
    f32 dot;

    OS_DEBUG_ASSERT(q, "QUATMakeClosest():  NULL QuaternionPtr 'q' ");
    OS_DEBUG_ASSERT(qto, "QUATMakeClosest():  NULL QuaternionPtr 'qto' ");
    OS_DEBUG_ASSERT(r, "QUATMakeClosest():  NULL QuaternionPtr 'r' ");

    dot = q->x * qto->x + q->y * qto->y + q->z * qto->z + q->w * qto->w;
    if (dot < 0.0f) {
        r->x = -q->x;
        r->y = -q->y;
        r->z = -q->z;
        r->w = -q->w;
    } else {
        *r = *q;
    }
}

void C_QUATRotAxisRad(QuaternionPtr r, CVecPtr axis, f32 rad) {
    Vec unit;
    f32 halfA;
    f32 sinA;
    f32 cosA;

    OS_DEBUG_ASSERT(r, "QUATRotAxisRad():  NULL QuaternionPtr 'r' ");
    OS_DEBUG_ASSERT(axis, "QUATRotAxisRad():  NULL VecPtr 'axis' ");

    VECNormalize(axis, &unit);
    halfA = rad * 0.5f;
    sinA = sinf(halfA);
    cosA = cosf(halfA);

    r->x = sinA * unit.x;
    r->y = sinA * unit.y;
    r->z = sinA * unit.z;
    r->w = cosA;
}

void C_QUATMtx(QuaternionPtr r, CMtxPtr m) {
    s32 tmp0[3] = {1, 2, 0};
    f32 tmp1;
    f32 tmp2;
    s32 tmp3;
    s32 tmp4;
    s32 tmp5;
    f32 tmp6[3];

    OS_DEBUG_ASSERT(r, "QUATMtx():  NULL QuaternionPtr 'r' ");
    OS_DEBUG_ASSERT(m, "QUATMtx():  NULL MtxPtr 'm' ");

    tmp1 = m[0][0] + m[1][1] + m[2][2];
    if (tmp1 > 0.0f) {
        tmp2 = sqrtf(tmp1 + 1.0f);
        r->w = tmp2 * 0.5f;
        tmp2 = 0.5f / tmp2;
        r->x = (m[2][1] - m[1][2]) * tmp2;
        r->y = (m[0][2] - m[2][0]) * tmp2;
        r->z = (m[1][0] - m[0][1]) * tmp2;
    } else {
        tmp3 = 0;
        if (m[1][1] > m[0][0]) {
            tmp3 = 1;
        }
        if (m[2][2] > m[tmp3][tmp3]) {
            tmp3 = 2;
        }
        tmp4 = tmp0[tmp3];
        tmp5 = tmp0[tmp4];
        tmp2 = sqrtf(m[tmp3][tmp3] - (m[tmp4][tmp4] + m[tmp5][tmp5]) + 1.0f);
        tmp6[tmp3] = tmp2 * 0.5f;

        if (tmp2 != 0.0f) {
            tmp2 = 0.5f / tmp2;
        }

        r->w = (m[tmp5][tmp4] - m[tmp4][tmp5]) * tmp2;
        tmp6[tmp4] = (m[tmp3][tmp4] + m[tmp4][tmp3]) * tmp2;
        tmp6[tmp5] = (m[tmp3][tmp5] + m[tmp5][tmp3]) * tmp2;
        r->x = tmp6[0];
        r->y = tmp6[1];
        r->z = tmp6[2];
    }
}

void C_QUATLerp(CQuaternionPtr p, CQuaternionPtr q, QuaternionPtr r, f32 t) {
    OS_DEBUG_ASSERT(p, "QUATLerp():  NULL QuaternionPtr 'p' ");
    OS_DEBUG_ASSERT(q, "QUATLerp():  NULL QuaternionPtr 'q' ");
    OS_DEBUG_ASSERT(r, "QUATLerp():  NULL QuaternionPtr 'r' ");

    r->x = p->x + (q->x - p->x) * t;
    r->y = p->y + (q->y - p->y) * t;
    r->z = p->z + (q->z - p->z) * t;
    r->w = p->w + (q->w - p->w) * t;
}

void C_QUATSlerp(CQuaternionPtr p, CQuaternionPtr q, QuaternionPtr r, f32 t) {
    f32 dot;
    f32 pt;
    f32 qt;
    f32 tmp0;
    f32 tmp1;

    OS_DEBUG_ASSERT(p, "QUATSlerp():  NULL QuaternionPtr 'p' ");
    OS_DEBUG_ASSERT(q, "QUATSlerp():  NULL QuaternionPtr 'q' ");
    OS_DEBUG_ASSERT(r, "QUATSlerp():  NULL QuaternionPtr 'r' ");

    dot = p->x * q->x + p->y * q->y + p->z * q->z + p->w * q->w;
    qt = 1.0f;
    if (dot < 0.0f) {
        dot = -dot;
        qt = -qt;
    }

    if (dot <= 1.0f - EPSILON) {
        tmp0 = acosf(dot);
        tmp1 = sinf(tmp0);
        pt = sinf((1.0f - t) * tmp0) / tmp1;
        qt *= sinf(t * tmp0) / tmp1;
    } else {
        pt = 1.0f - t;
        qt *= t;
    }

    r->x = pt * p->x + qt * q->x;
    r->y = pt * p->y + qt * q->y;
    r->z = pt * p->z + qt * q->z;
    r->w = pt * p->w + qt * q->w;
}

void C_QUATSquad(CQuaternionPtr p, CQuaternionPtr a, CQuaternionPtr b,
                 CQuaternionPtr q, QuaternionPtr r, f32 t) {
    f32 tmp0;
    Quaternion tmp1;
    Quaternion tmp2;

    OS_DEBUG_ASSERT(p, "QUATSquad():  NULL QuaternionPtr 'p' ");
    OS_DEBUG_ASSERT(a, "QUATSquad():  NULL QuaternionPtr 'a' ");
    OS_DEBUG_ASSERT(b, "QUATSquad():  NULL QuaternionPtr 'b' ");
    OS_DEBUG_ASSERT(q, "QUATSquad():  NULL QuaternionPtr 'q' ");
    OS_DEBUG_ASSERT(r, "QUATSquad():  NULL QuaternionPtr 'r' ");

    tmp0 = t * 2.0f * (1.0f - t);
    C_QUATSlerp(p, q, &tmp1, t);
    C_QUATSlerp(a, b, &tmp2, t);
    C_QUATSlerp(&tmp1, &tmp2, r, tmp0);
}

void C_QUATCompA(CQuaternionPtr qprev, CQuaternionPtr q, CQuaternionPtr qnext,
                 QuaternionPtr a) {
    Quaternion tmp0;
    Quaternion tmp1;
    Quaternion tmp2;
    Quaternion tmp3;
    Quaternion tmp4;
    Quaternion tmp5;

    OS_DEBUG_ASSERT(qprev, "QUATCompA():  NULL QuaternionPtr 'qprev' ");
    OS_DEBUG_ASSERT(q, "QUATCompA():  NULL QuaternionPtr 'q' ");
    OS_DEBUG_ASSERT(qnext, "QUATCompA():  NULL QuaternionPtr 'qnext' ");
    OS_DEBUG_ASSERT(a, "QUATCompA():  NULL QuaternionPtr 'a' ");

    C_QUATDivide(qprev, q, &tmp0);
    C_QUATLogN(&tmp0, &tmp2);
    C_QUATDivide(qnext, q, &tmp1);
    C_QUATLogN(&tmp1, &tmp3);
    C_QUATAdd(&tmp3, &tmp2, &tmp4);
    C_QUATScale(&tmp4, &tmp4, -0.25f);
    C_QUATExp(&tmp4, &tmp5);
    C_QUATMultiply(q, &tmp5, a);
}
