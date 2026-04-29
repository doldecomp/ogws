#include <revolution/MTX.h>
#include <revolution/MTX/internal/mtxAssert.h>

#include <math.h>

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

    // clang-format off
    asm {
        psq_l tmp0, Quaternion.x(p), 0, qr0
        psq_l tmp1, Quaternion.z(p), 0, qr0
        psq_l tmp2, Quaternion.x(q), 0, qr0
        ps_neg tmp5, tmp0
        psq_l tmp3, Quaternion.z(q), 0, qr0
        ps_neg tmp6, tmp1
        ps_merge01 tmp4, tmp5, tmp0
        ps_muls0 tmp7, tmp1, tmp2
        ps_muls0 tmp5, tmp5, tmp2
        ps_merge01 tmp8, tmp6, tmp1
        ps_muls1 tmp9, tmp4, tmp2
        ps_madds0 tmp7, tmp4, tmp3, tmp7
        ps_muls1 tmp10, tmp8, tmp2
        ps_madds0 tmp5, tmp8, tmp3, tmp5
        ps_madds1 tmp9, tmp6, tmp3, tmp9
        ps_merge10 tmp7, tmp7, tmp7
        ps_madds1 tmp10, tmp0, tmp3, tmp10
        ps_merge10 tmp5, tmp5, tmp5
        ps_add tmp7, tmp7, tmp10
        psq_st tmp7, Quaternion.x(pq), 0, qr0
        ps_sub tmp5, tmp5, tmp9
        psq_st tmp5, Quaternion.z(pq), 0, qr0
    } // clang-format on
}

// Keep for float ordering
void C_QUATNormalize(CQuaternionPtr src, QuaternionPtr unit) {
    f32 norm =
        src->x * src->x + src->y * src->y + src->z * src->z + src->w * src->w;
    if (norm >= 0.00001f) {
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
    register f32 tmp4 = 0.00001f;
    register f32 tmp5;
    register f32 tmp6;
    register f32 tmp7;
    register f32 tmp8;
    register f32 c_half = 0.5f;
    register f32 c_three = 3.0f;

    // clang-format off
    asm {
        psq_l tmp0, Quaternion.x(src), 0, qr0
        ps_mul tmp2, tmp0, tmp0
        psq_l tmp1, Quaternion.z(src), 0, qr0
        ps_sub tmp5, tmp4, tmp4
        ps_madd tmp2, tmp1, tmp1, tmp2
        ps_sum0 tmp2, tmp2, tmp2, tmp2
        frsqrte tmp3, tmp2
        ps_sub tmp4, tmp2, tmp4
        fmul tmp6, tmp3, tmp3
        fmul tmp3, tmp3, c_half
        fnmsub tmp6, tmp6, tmp2, c_three
        fmul tmp3, tmp6, tmp3
        ps_sel tmp3, tmp4, tmp3, tmp5
        ps_muls0 tmp7, tmp0, tmp3
        ps_muls0 tmp8, tmp1, tmp3
        psq_st tmp7, Quaternion.x(unit), 0, qr0
        psq_st tmp8, Quaternion.z(unit), 0, qr0
    } // clang-format on
}

void C_QUATMtx(QuaternionPtr r, CMtxPtr m) {
    s32 tmp0[3] = {1, 2, 0};
    f32 tmp1;
    f32 tmp2;
    s32 tmp3;
    s32 tmp4;
    s32 tmp5;
    f32 tmp6[3];

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

void C_QUATSlerp(CQuaternionPtr p, CQuaternionPtr q, QuaternionPtr r, f32 t) {
    f32 dot;
    f32 pt;
    f32 qt;
    f32 tmp0;
    f32 tmp1;

    dot = p->x * q->x + p->y * q->y + p->z * q->z + p->w * q->w;
    qt = 1.0f;
    if (dot < 0.0f) {
        dot = -dot;
        qt = -qt;
    }

    if (dot <= 0.99999f) {
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
