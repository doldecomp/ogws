#include <nw4r/ef.h>
#include <nw4r/math.h>

#include <revolution/GX.h>

namespace nw4r {
namespace ef {

static u8 directional_tex0_u8[] = {0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01};

DrawDirectionalStrategy::DrawDirectionalStrategy() {}

inline math::MTX34 CalcLocalTransform(u8 face, f32 px, f32 py, f32 sx, f32 sy,
                                      f32 vs, const nw4r::math::MTX34& rRot) {
    switch (face) {
    case 0 /* magic number */: {
        f32 sx_px = sx * px;
        f32 sy_vs = sy * vs;
        f32 exp0 = sy * (py + vs - 1.0f);
        // clang-format off
        return math::MTX34(
            rRot._00 * sx,  rRot._01 * sy_vs,  rRot._02 * sx,  -rRot._00 * sx_px - rRot._01 * exp0 + px,
            rRot._10 * sx,  rRot._11 * sy_vs,  rRot._12 * sx,  -rRot._10 * sx_px - rRot._11 * exp0 + py,
            rRot._20 * sx,  rRot._21 * sy_vs,  rRot._22 * sx,  -rRot._20 * sx_px - rRot._21 * exp0);
        // clang-format on
    }
    default:
    case 1 /* magic number */: {
        f32 sx_px = sx * px;
        f32 sy_py = sy * py;
        // clang-format off
        return math::MTX34(
            rRot._00 * sx,  rRot._02 * sy,  rRot._01 * sx,  -rRot._00 * sx_px - rRot._02 * sy_py + px,
            rRot._10 * sx,  rRot._12 * sy,  rRot._11 * sx,  -rRot._10 * sx_px - rRot._12 * sy_py,
            rRot._20 * sx,  rRot._22 * sy,  rRot._21 * sx,  -rRot._20 * sx_px - rRot._22 * sy_py - py);
        // clang-format on
    }
    }
}

inline math::MTX34 CalcRotate(Particle* pParticle, u8 axis) {
    math::VEC3 rot;
    pParticle->Draw_GetRotate(&rot);

    f32 sx = 0.0f, cx = 1.0f;
    f32 sy = 0.0f, cy = 1.0f;
    f32 sz = 0.0f, cz = 1.0f;

    f32 sx_sy;
    f32 cx_sy;
    switch (axis) {
    case 0 /* magic number (X axis) */: {
        if (rot.x != 0.0f) {
            math::SinCosRad(&sx, &cx, -rot.x);
        }
        // clang-format off
        return math::MTX34(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f,   cx,  -sx, 0.0f,
            0.0f,   sx,   cx, 0.0f);
        // clang-format on
    }
    case 1 /* magic number (Y axis) */: {
        if (rot.y != 0.0f) {
            math::SinCosRad(&sy, &cy, -rot.y);
        }
        // clang-format off
        return math::MTX34(
              cy, 0.0f,   sy, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
             -sy, 0.0f,   cy, 0.0f);
        // clang-format on
    }
    case 2 /* magic number (Z axis) */: {
        if (rot.z != 0.0f) {
            math::SinCosRad(&sz, &cz, -rot.z);
        }
        // clang-format off
        return math::MTX34(
              cz,  -sz, 0.0f, 0.0f,
              sz,   cz, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f);
        // clang-format on
    }
    default:
    case 3 /* magic number (general/Tait-Bryan) */: {
        if (rot.x) {
            math::SinCosRad(&sx, &cx, -rot.x);
        }
        if (rot.y) {
            math::SinCosRad(&sy, &cy, -rot.y);
        }
        if (rot.z) {
            math::SinCosRad(&sz, &cz, -rot.z);
        }

        sx_sy = sx * sy;
        cx_sy = cx * sy;

        // clang-format off
        return math::MTX34(
            cy * cz,  sx_sy * cz - cx * sz,  cx_sy * cz + sx * sz,  0.0f,
            cy * sz,  sx_sy * sz + cx * cz,  cx_sy * sz - sx * cz,  0.0f,
                -sy,               cy * sx,               cx * cy,  0.0f);
        // clang-format on
    }
    }
}

static void DrawQuad(const math::MTX34& rMtx, const math::_VEC3* pPosArray,
                     bool texCoord) {

    math::VEC3 p0, p1, p2, p3;

    math::VEC3Transform(&p0, &rMtx,
                        static_cast<const math::VEC3*>(&pPosArray[0]));
    math::VEC3Transform(&p1, &rMtx,
                        static_cast<const math::VEC3*>(&pPosArray[1]));
    math::VEC3Transform(&p2, &rMtx,
                        static_cast<const math::VEC3*>(&pPosArray[2]));
    math::VEC3Transform(&p3, &rMtx,
                        static_cast<const math::VEC3*>(&pPosArray[3]));

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    {
        GXPosition(p0);
        if (texCoord) {
            GXTexCoord1x8(0);
        }

        GXPosition(p1);
        if (texCoord) {
            GXTexCoord1x8(1);
        }

        GXPosition(p2);
        if (texCoord) {
            GXTexCoord1x8(2);
        }

        GXPosition(p3);
        if (texCoord) {
            GXTexCoord1x8(3);
        }
    }
    GXEnd();
}

static void DrawQuad(const math::VEC3& p, const math::VEC3& d0,
              const math::VEC3& d1, bool texCoord) {
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    {
        GXPosition(p - d0);
        if (texCoord) {
            GXTexCoord1x8(0);
        }

        GXPosition(p - d1);
        if (texCoord) {
            GXTexCoord1x8(1);
        }

        GXPosition(p + d0);
        if (texCoord) {
            GXTexCoord1x8(2);
        }

        GXPosition(p + d1);
        if (texCoord) {
            GXTexCoord1x8(3);
        }
    }
    GXEnd();
}

void DrawDirectionalStrategy::Draw(const DrawInfo& rInfo,
                                   ParticleManager* pManager) {
    InitGraphics(rInfo, pManager);

    const EmitterDrawSetting& rSetting =
        *pManager->mResource->GetEmitterDrawSetting();

    switch (GetDirectionalPivot(rSetting)) {
    default:
    case DIRECTIONAL_PIVOT_NOP: {
        DrawDirectional(rInfo, pManager);
        break;
    }
    case DIRECTIONAL_PIVOT_BILLBOARD: {
        DrawDirectionalBillboard(rInfo, pManager);
        break;
    }
    }
}

void DrawDirectionalStrategy::DrawDirectional(const DrawInfo& rInfo,
                                              ParticleManager* pManager) {
    InitGraphics(rInfo, pManager);

    const EmitterDrawSetting& rSetting =
        *pManager->mResource->GetEmitterDrawSetting();

    AheadContext aheadContext(*rInfo.GetViewMtx(), pManager);
    CalcAheadFunc pCalcAheadFunc = GetCalcAheadFunc(pManager);
    
    math::MTX34 glbMtx;
    math::MTX34 posMtx;
    
    math::VEC3 refYAxis;
    math::VEC3 refZAxis;
    
    pManager->CalcGlobalMtx(&glbMtx);
    math::MTX34Mult(&posMtx, rInfo.GetViewMtx(), &glbMtx);
    GXLoadPosMtxImm(posMtx, GX_PNMTX0);
    
    math::MTX34 emMtx;
    math::MTX34 locMtx;
    
    pManager->mManagerEM->CalcGlobalMtx(&emMtx);
    math::MTX34Inv(&locMtx, &glbMtx);
    math::MTX34Mult(&emMtx, &locMtx, &emMtx);

    refYAxis = math::VEC3(emMtx._01, emMtx._11, emMtx._21);
    refZAxis = math::VEC3(emMtx._02, emMtx._12, emMtx._22);
    Normalize(&refZAxis);

    for (Particle* pParticle = GetYoungestParticle(pManager);
         pParticle != NULL && pParticle->mPrevAxis.x > 1.0f;
         pParticle = GetElderParticle(pManager, pParticle)) {
        pParticle->mPrevAxis = refYAxis;
    }

    f32 px = rSetting.pivotX / 100.0f;
    f32 py = rSetting.pivotY / 100.0f;

    GetFirstDrawParticleFunc pGetFirstFunc = GetGetFirstDrawParticleFunc(
        rSetting.mFlags & EmitterDrawSetting::FLAG_DRAW_ORDER);

    GetNextDrawParticleFunc pGetNextFunc = GetGetNextDrawParticleFunc(
        rSetting.mFlags & EmitterDrawSetting::FLAG_DRAW_ORDER);

    bool first = true;

    for (Particle* pParticle = pGetFirstFunc(pManager); pParticle;
         pParticle = pGetNextFunc(pManager, pParticle)) {

        f32 sx = pParticle->Draw_GetSizeX();
        if (sx < std::numeric_limits<f32>::epsilon()) {
            continue;
        }

        f32 sy = pParticle->Draw_GetSizeY();
        if (sy < std::numeric_limits<f32>::epsilon()) {
            continue;
        }

        f32 vs = 1.0f;
        if (rSetting.typeOption0) {
            math::VEC3 v;
            pParticle->GetMoveDir(&v);

            vs += 0.5f * math::FSqrt(math::VEC3Dot(&v, &v)) / sy;
        }

        SetupGP(pParticle, rSetting, rInfo, first, false);
        first = false;

        math::MTX34 rotMtx = CalcRotate(pParticle, rSetting.typeAxis);
        math::MTX34 locMtx = CalcLocalTransform(rSetting.typeOption1, px, py,
                                                sx, sy, vs, rotMtx);
        math::VEC3 xAxis;
        math::VEC3 yAxis;
        math::VEC3 zAxis;
        pCalcAheadFunc(&yAxis, &aheadContext, pParticle);

        math::VEC3Cross(&zAxis, &pParticle->mPrevAxis, &yAxis);
        if (!Normalize(&zAxis)) {
            zAxis = refZAxis;
        }

        math::VEC3Cross(&xAxis, &yAxis, &zAxis);
        pParticle->mPrevAxis = xAxis;
        math::VEC3 pos(pParticle->mParameter.mPosition);
        // clang-format off
        math::MTX34 mtxParticle(
            xAxis.x, yAxis.x, zAxis.x, pos.x,
            xAxis.y, yAxis.y, zAxis.y, pos.y,
            xAxis.z, yAxis.z, zAxis.z, pos.z);
        // clang-format on
        math::MTX34 mtx;
        math::MTX34Mult(&mtx, &mtxParticle, &locMtx);

        // clang-format off
        static const math::_VEC3 p[4] = {
            -1.0f, -1.0f, 0.0f,
            -1.0f,  1.0f, 0.0f,
             1.0f,  1.0f, 0.0f,
             1.0f, -1.0f, 0.0f
        };
        // clang-format on

        DrawQuad(mtx, p, mNumTexmap > 0);

        if (rSetting.typeOption == EmitterDrawSetting::TYPE_CMN_CROSS) {
            // clang-format off
            static const math::_VEC3 px[4] = {
                0.0f, -1.0f,  1.0f,
                0.0f,  1.0f,  1.0f,
                0.0f,  1.0f, -1.0f,
                0.0f, -1.0f, -1.0f
            };
            // clang-format on

            DrawQuad(mtx, px, mNumTexmap > 0);
        }
    }
}

void DrawDirectionalStrategy::DrawDirectionalBillboard(
    const DrawInfo& rInfo, ParticleManager* pManager) {
    InitGraphics(rInfo, pManager);

    const EmitterDrawSetting& rSetting =
        *pManager->mResource->GetEmitterDrawSetting();
    AheadContext aheadContext(*rInfo.GetViewMtx(), pManager);
    CalcAheadFunc pCalcAheadFunc = GetCalcAheadFunc(pManager);
    
    math::MTX34 viewMtx;
    math::MTX34 glbMtx;
    pManager->CalcGlobalMtx(&glbMtx);
    math::MTX34Mult(&viewMtx, rInfo.GetViewMtx(), &glbMtx);
    GXLoadPosMtxImm(mIdentityMtx, GX_PNMTX0);

    f32 vx = math::FSqrt(viewMtx._00 * viewMtx._00 +
                         viewMtx._10 * viewMtx._10 +
                         viewMtx._20 * viewMtx._20);

    f32 vy = math::FSqrt(viewMtx._01 * viewMtx._01 +
                         viewMtx._11 * viewMtx._11 +
                         viewMtx._21 * viewMtx._21);

    f32 vz = math::FSqrt(viewMtx._02 * viewMtx._02 +
                         viewMtx._12 * viewMtx._12 +
                         viewMtx._22 * viewMtx._22);

    for (Particle* pParticle = GetYoungestParticle(pManager);
         pParticle != NULL && pParticle->mPrevAxis.x > 1.0f;
         pParticle = GetElderParticle(pManager, pParticle)) {
        pParticle->mPrevAxis = mZeroVec;
    }

    f32 px = rSetting.pivotX / 100.0f;
    f32 py = rSetting.pivotY / 100.0f;

    GetFirstDrawParticleFunc pGetFirstFunc = GetGetFirstDrawParticleFunc(
        rSetting.mFlags & EmitterDrawSetting::FLAG_DRAW_ORDER);

    GetNextDrawParticleFunc pGetNextFunc = GetGetNextDrawParticleFunc(
        rSetting.mFlags & EmitterDrawSetting::FLAG_DRAW_ORDER);

    bool first = true;

    for (Particle* pParticle = pGetFirstFunc(pManager); pParticle != NULL;
         pParticle = pGetNextFunc(pManager, pParticle)) {
        f32 sx = pParticle->Draw_GetSizeX();
        if (sx < NW4R_MATH_FLT_EPSILON) {
            continue;
        }

        f32 sy = pParticle->Draw_GetSizeY();
        if (sy < NW4R_MATH_FLT_EPSILON) {
            continue;
        }

        f32 vs = 1.0f;
        if (rSetting.typeOption0) {
            math::VEC3 v;
            pParticle->GetMoveDir(&v);

            vs += 0.5f * math::FSqrt(math::VEC3Dot(&v, &v)) / sy;
        }

        SetupGP(pParticle, rSetting, rInfo, first, false);
        first = false;

        math::MTX34 rotMtx = CalcRotate(pParticle, rSetting.typeAxis);
        math::MTX34 locMtx = CalcLocalTransform(rSetting.typeOption1, px, py,
                                                sx, sy, vs, rotMtx);

        math::VEC3 xAxis;
        math::VEC3 yAxis;
        math::VEC3 zAxis;

        math::VEC3 dir;
        pCalcAheadFunc(&dir, &aheadContext, pParticle);
        math::VEC3TransformNormal(&dir, &viewMtx, &dir);

        yAxis = dir;
        Normalize(&yAxis);

        xAxis = math::VEC3(dir.y, -dir.x, 0.0f);

        if (Normalize(&xAxis)) {
            zAxis = math::VEC3(
                -dir.x * dir.z, -dir.y * dir.z,
                dir.x * dir.x + dir.y * dir.y);
        } else {
            math::VEC3Cross(&xAxis, &dir, &pParticle->mPrevAxis);
            if (!Normalize(&xAxis)) {
                xAxis = mXUnitVec;
            }

            math::VEC3Cross(&zAxis, &xAxis, &dir);
        }
        Normalize(&zAxis);

        pParticle->mPrevAxis = zAxis;

        math::VEC3 pos;
        math::VEC3Transform(&pos, &viewMtx,
                            &pParticle->mParameter.mPosition);

        math::MTX34 mtxParticle(
            vx * xAxis.x, vy * yAxis.x, vz * zAxis.x, pos.x,
            vx * xAxis.y, vy * yAxis.y, vz * zAxis.y, pos.y,
            vx * xAxis.z, vy * yAxis.z, vz * zAxis.z, pos.z);

        math::MTX34 mtx;
        math::MTX34Mult(&mtx, &mtxParticle, &locMtx);

        math::VEC3 vp0(mtx._03, mtx._13, mtx._23);

        math::VEC3 vd0(mtx._00 + mtx._01,
                       mtx._10 + mtx._11,
                       mtx._20 + mtx._21);
        math::VEC3 vd1(mtx._00 - mtx._01,
                       mtx._10 - mtx._11,
                       mtx._20 - mtx._21);
        DrawQuad(vp0, vd0, vd1, mNumTexmap > 0);

        if (rSetting.typeOption == EmitterDrawSetting::TYPE_CMN_CROSS) {
            math::VEC3 vd2(mtx._01 + mtx._02,
                           mtx._11 + mtx._12,
                           mtx._21 + mtx._22);
            math::VEC3 vd3(mtx._01 - mtx._02,
                           mtx._11 - mtx._12,
                           mtx._21 - mtx._22);
            DrawQuad(vp0, vd2, vd3, mNumTexmap > 0);
        }

    }
}

void DrawDirectionalStrategy::InitGraphics(const DrawInfo& rInfo,
                                           ParticleManager* pManager) {

    const EmitterDrawSetting& rSetting =
        *pManager->mResource->GetEmitterDrawSetting();

    InitTexture(rSetting);
    InitTev(rSetting, rInfo);
    InitColor(pManager, rSetting, rInfo);

    GXEnableTexOffsets(GX_TEXCOORD0, TRUE, TRUE);

    GXSetArray(GX_VA_TEX0, directional_tex0_u8, 2);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);

    if (mNumTexmap > 0) {
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
    }

    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);

    GXSetCurrentMtx(GX_PNMTX0);
}

DrawStrategyImpl::CalcAheadFunc
DrawDirectionalStrategy::GetCalcAheadFunc(ParticleManager* pManager) {

    const EmitterDrawSetting& rSetting =
        *pManager->mResource->GetEmitterDrawSetting();

    switch (rSetting.typeDir) {
    case EmitterDrawSetting::AHEAD_BB_SPEED: {
        return CalcAhead_Speed;
    }

    case EmitterDrawSetting::AHEAD_BB_EMITTER_CENTER: {
        return CalcAhead_EmitterCenter;
    }

    case EmitterDrawSetting::AHEAD_BB_EMITTER_DESIGN: {
        return CalcAhead_EmitterDesign;
    }

    case EmitterDrawSetting::AHEAD_BB_PARTICLE: {
        return CalcAhead_Particle;
    }

    case EmitterDrawSetting::AHEAD_CMN_NODESIGN: {
        return CalcAhead_NoDesign;
    }

    case EmitterDrawSetting::AHEAD_BB_PARTICLE_BOTH: {
        return CalcAhead_ParticleBoth;
    }

    case EmitterDrawSetting::AHEAD_CMN_NODESIGN + 1 /* magic number */:
    default: {
        return CalcAhead_Speed;
    }
    }
}

} // namespace ef
} // namespace nw4r
