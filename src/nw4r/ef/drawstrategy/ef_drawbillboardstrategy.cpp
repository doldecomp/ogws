#include <nw4r/ef.h>

namespace nw4r {
namespace ef {

static u8 billboard_tex0_u8[] = {0x00, 0x01, 0x00, 0x00,
                                 0x01, 0x00, 0x01, 0x01};

DrawBillboardStrategy::DrawBillboardStrategy() {}

void DrawBillboardStrategy::Draw(const DrawInfo& rInfo,
                                 ParticleManager* pManager) {

    const EmitterDrawSetting& rSetting =
        *pManager->mResource->GetEmitterDrawSetting();

    switch (rSetting.typeOption) {
        case EmitterDrawSetting::ASSIST_BB_NORMAL: {
            DrawNormalBillboard(rInfo, pManager);
            break;
        }

        case EmitterDrawSetting::ASSIST_BB_Y: {
            DrawYBillboard(rInfo, pManager);
            break;
        }

        case EmitterDrawSetting::ASSIST_BB_DIRECTIONAL: {
            DrawDirectionalBillboard(rInfo, pManager);
            break;
        }
    }
}

void DrawBillboardStrategy::DrawNormalBillboard(const DrawInfo& rInfo,
                                                ParticleManager* pManager) {

    InitGraphics(rInfo, pManager);

    const EmitterDrawSetting& rSetting =
        *pManager->mResource->GetEmitterDrawSetting();

    int flags = mNumTexmap > 0 ? 1 : 0;
    const math::MTX34& rInfoMtx = *rInfo.GetViewMtx();

    math::VEC2 pivot;
    pivot.x = rSetting.pivotX / 100.0f;
    pivot.y = rSetting.pivotY / 100.0f;

    math::MTX34 viewMtx;
    pManager->CalcGlobalMtx(&viewMtx);
    math::MTX34Mult(&viewMtx, &rInfoMtx, &viewMtx);

    if (rSetting.zOffset != 0.0f) {
        CalcZOffset(&viewMtx, pManager, rInfo, rSetting.zOffset);
    }

    f32 vx = math::FSqrt(viewMtx._00 * viewMtx._00 + viewMtx._10 * viewMtx._10 +
                         viewMtx._20 * viewMtx._20);

    f32 vy = math::FSqrt(viewMtx._01 * viewMtx._01 + viewMtx._11 * viewMtx._11 +
                         viewMtx._21 * viewMtx._21);

    f32 vz = 0.0f;

    f32 rc, rs;
    f32 mag;

    mag =
        math::FSqrt(rInfoMtx._01 * rInfoMtx._01 + rInfoMtx._11 * rInfoMtx._11);
    if (mag == 0.0f) {
        rs = 0.0f;
        rc = 1.0f;
    } else {
        f32 denom = 1.0f / mag;
        rs = -rInfoMtx._01 * denom;
        rc = rInfoMtx._11 * denom;
    }

    GetFirstDrawParticleFunc pGetFirstFunc = GetGetFirstDrawParticleFunc(
        rSetting.mFlags & EmitterDrawSetting::FLAG_DRAW_ORDER);

    GetNextDrawParticleFunc pGetNextFunc = GetGetNextDrawParticleFunc(
        rSetting.mFlags & EmitterDrawSetting::FLAG_DRAW_ORDER);

    bool first = true;

    for (Particle* pIt = pGetFirstFunc(pManager); pIt != NULL;
     pIt = pGetNextFunc(pManager, pIt)) {

        f32 sx = pIt->Draw_GetSizeX();
        if (sx < std::numeric_limits<f32>::epsilon()) {
            continue;
        }

        f32 sy = pIt->Draw_GetSizeY();
        if (sy < std::numeric_limits<f32>::epsilon()) {
            continue;
        }

        SetupGP(pIt, rSetting, rInfo, first, false);
        first = false;

        DispParticle_Normal(pIt, viewMtx, vx, vy, vz, rc, rs, sx, sy, pivot,
                            flags);
    }
}

inline void DrawBillboardStrategy::DispParticle_Normal(
    Particle* pParticle, const math::MTX34& rViewMtx, f32 vx, f32 vy, f32 vz,
    f32 rc, f32 rs, f32 sx, f32 sy, const math::VEC2& rPivot, int flags) {

#pragma unused(vz)

    math::VEC3 rot;
    pParticle->Draw_GetRotate(&rot);

    math::VEC3 p0;  // sp+24
    math::VEC3 d0;  // sp+30
    math::VEC3 d1;  // sp+3c
    math::VEC3 pos; // sp+48

    math::VEC3Transform(&pos, &rViewMtx, &pParticle->mParameter.mPosition);

    f32 px = rPivot.x;
    f32 py = rPivot.y;

    f32 vx_rc = vx * rc;
    f32 vx_rs = vx * rs;
    f32 vy_rc = vy * rc;
    f32 vy_rs = vy * rs;

    if (rot.z != 0.0f) {
        f32 cr, sr;
        //math::SinCosRad(&sr, &cr, -rot.z);
        math::SinCosFIdx(&sr, &cr, -rot.z);

        f32 cr_sx = cr * sx;
        f32 sr_sx = sr * sx;
        f32 cr_sy = cr * sy;
        f32 sr_sy = sr * sy;
        f32 rc_sx = rc * sx;
        f32 rs_sy = rs * sy;
        f32 rs_sx = rs * sx;
        f32 rc_sy = rc * sy;

        f32 exp0 = (px - cr_sx * px) - sr_sy * py;
        f32 exp1 = (py + sr_sx * px) - cr_sy * py;

        p0.x = vx_rc * exp0 + vy_rs * exp1 + pos.x;
        p0.y = vx_rs * exp0 - vy_rc * exp1 + pos.y;
        p0.z = pos.z;

        f32 vx_rc_cr_sx = vx_rc * cr_sx;
        f32 vx_rc_sr_sy = vx_rc * sr_sy;
        f32 vy_rs_sr_sx = vy_rs * sr_sx;
        f32 vy_rs_cr_sy = vy_rs * cr_sy;
        f32 vx_rs_cr_sx = vx_rs * cr_sx;
        f32 vx_rs_sr_sy = vx_rs * sr_sy;
        f32 vy_rc_sr_sx = vy_rc * sr_sx;
        f32 vy_rc_cr_sy = vy_rc * cr_sy;

        d0.x = vx_rc_cr_sx - vx_rc_sr_sy - vy_rs_sr_sx - vy_rs_cr_sy;
        d0.y = vx_rs_cr_sx - vx_rs_sr_sy + vy_rc_sr_sx + vy_rc_cr_sy;
        d0.z = 0.0f;

        d1.x = vx_rc_cr_sx + vx_rc_sr_sy - vy_rs_sr_sx + vy_rs_cr_sy;
        d1.y = vx_rs_cr_sx + vx_rs_sr_sy + vy_rc_sr_sx - vy_rc_cr_sy;
        d1.z = 0.0f;
    } else {
        f32 dx0 = sx * px;
        f32 dy0 = sy * py;

        float exp0 = px - dx0;
        float exp1 = py - dy0;

        p0.x = vy_rc * exp0 + vy_rs * exp1 + pos.x;
        p0.y = vy * exp1 + pos.y;
        p0.z = (-vy * rs) * exp0 + (vy * rc) * exp1 + pos.z;

        d0.x = vy_rc * sx;
        d0.y = 0.0f;
        d0.z = (-vy * rs) * sx;

        d1.x = vy_rs * sy;
        d1.y = vy * sy;
        d1.z = (vy * rc) * sy;
    }

    DispPolygon(p0, d0, d1, flags);
}

void DrawBillboardStrategy::DrawYBillboard(const DrawInfo& rInfo,
                                           ParticleManager* pManager)
{
    InitGraphics(rInfo, pManager);

    const EmitterDrawSetting& rSetting =
        *pManager->mResource->GetEmitterDrawSetting();

    int flags = mNumTexmap != 0;

    math::VEC2 pivot;
    pivot.x = rSetting.pivotY / 100.0f;
    pivot.y = rSetting.pivotX / 100.0f;

    math::MTX34 viewMtx;
    pManager->CalcGlobalMtx(&viewMtx);
    math::MTX34Mult(&viewMtx, rInfo.GetViewMtx(), &viewMtx);

    if (rSetting.zOffset != 0.0f) {
        CalcZOffset(&viewMtx, pManager, rInfo, rSetting.zOffset);
    }

    f32 vx = math::FSqrt(viewMtx._00 * viewMtx._00 +
                         viewMtx._10 * viewMtx._10 +
                         viewMtx._20 * viewMtx._20);

    f32 vy = math::FSqrt(viewMtx._01 * viewMtx._01 +
                         viewMtx._11 * viewMtx._11 +
                         viewMtx._21 * viewMtx._21);

    f32 rc, rs;
    {
        const math::MTX34* pView = rInfo.GetViewMtx();
        f32 mag = math::FSqrt(pView->_01 * pView->_01 +
                              pView->_21 * pView->_21);
        if (mag == 0.0f) {
            rc = 1.0f;
            rs = 0.0f;
        } else {
            f32 invMag = math::FInv(mag);
            rc = pView->_21 * invMag;
            rs = pView->_01 * invMag;
        }
    }

    GetFirstDrawParticleFunc pGetFirstFunc =
        GetGetFirstDrawParticleFunc(
            rSetting.mFlags & EmitterDrawSetting::FLAG_DRAW_ORDER);
    GetNextDrawParticleFunc pGetNextFunc =
        GetGetNextDrawParticleFunc(
            rSetting.mFlags & EmitterDrawSetting::FLAG_DRAW_ORDER);

    bool first = true;

    for (Particle* pIt = pGetFirstFunc(pManager); pIt != NULL;
         pIt = pGetNextFunc(pManager, pIt)) {

        if (pIt->GetLifeStatus() != 1)  continue;

        f32 sx = pIt->Draw_GetSizeX();
        if (sx < std::numeric_limits<f32>::epsilon()) continue;

        f32 sy = pIt->Draw_GetSizeY();
        if (sy < std::numeric_limits<f32>::epsilon()) continue;

        SetupGP(pIt, rSetting, rInfo, first, false);
        first = false;

        DispParticle_YBillboard(
            pIt, viewMtx, vx, vy, 0.0f, rc, rs, sx, sy, pivot, flags);
    }
}

inline void DrawBillboardStrategy::DispParticle_YBillboard(
    Particle* pParticle, const math::MTX34& rViewMtx, f32 vx, f32 vy, f32 vz,
    f32 rs, f32 rc, f32 sx, f32 sy, const math::VEC2& rPivot, int flags) {

#pragma unused(vz)

    math::VEC3 rot;
    pParticle->Draw_GetRotate(&rot);

    math::VEC3 p0;
    math::VEC3 d0;
    math::VEC3 d1;
    math::VEC3 pos;

    math::VEC3Transform(&pos, &rViewMtx, &pParticle->mParameter.mPosition);

    f32 px = rPivot.x;
    f32 py = rPivot.y;

    f32 vx_rc =  vx * rc;
    f32 vx_invrs =  vx * -rs;
    f32 upY    =  vy;
    f32 vx_rs = vx * rs;

    f32 cr = 1.0f;
    f32 sr = 0.0f;
    if (rot.z != 0.0f) {
        math::SinCosRad(&sr, &cr, -rot.z);

        f32 cr_sx = cr * sx;
        f32 sr_sx = sr * sx;
        f32 cr_sy = cr * sy;
        f32 sr_sy = sr * sy;

        f32 exp0 = (px - cr_sx * px) - sr_sy * py;
        f32 exp1 = (py + sr_sx * px) - cr_sy * py;

        p0.x = vx_rc * exp0 + vx_rs * exp1 + pos.x;
        p0.y = upY * exp1 + pos.y;
        p0.z = vx_invrs * exp0 + vx_rc * exp1 + pos.z;

        f32 dxLocalX =  cr_sx;
        f32 dyLocalX =  sr_sx;
        f32 dxLocalY = -sr_sy;
        f32 dyLocalY =  cr_sy;

        d0.x = vx_rc * dxLocalX + vx_rs * dyLocalX;
        d0.y = upY    * dyLocalX;
        d0.z = vx_invrs * dxLocalX + vx_rc * dyLocalX;

        d1.x = vx_rc * dxLocalY + vx_rs * dyLocalY;
        d1.y = upY    * dyLocalY;
        d1.z = vx_invrs * dxLocalY + vx_rc * dyLocalY;
    } else {
        // todo
    }

    DispPolygon(p0, d0, d1, flags);
}

void DrawBillboardStrategy::DrawDirectionalBillboard(const DrawInfo& rInfo,
                                                     ParticleManager* pManager) {
    InitGraphics(rInfo, pManager);

    const EmitterDrawSetting& rSetting =
        *pManager->mResource->GetEmitterDrawSetting();

    int flags = mNumTexmap > 0 ? 1 : 0;
    const math::MTX34& rInfoMtx = *rInfo.GetViewMtx();

    math::VEC2 pivot;
    pivot.x = rSetting.pivotX / 100.0f;
    pivot.y = rSetting.pivotY / 100.0f;

    math::MTX34 viewMtx;
    pManager->CalcGlobalMtx(&viewMtx);
    math::MTX34Mult(&viewMtx, &rInfoMtx, &viewMtx);

    if (rSetting.zOffset != 0.0f) {
        CalcZOffset(&viewMtx, pManager, rInfo, rSetting.zOffset);
    }

    f32 vx = math::FSqrt(viewMtx._00 * viewMtx._00 + viewMtx._10 * viewMtx._10 +
                         viewMtx._20 * viewMtx._20);

    f32 vy = math::FSqrt(viewMtx._01 * viewMtx._01 + viewMtx._11 * viewMtx._11 +
                         viewMtx._21 * viewMtx._21);

    f32 vz = 0.0f;

    DrawStrategyImpl::AheadContext ahead(viewMtx, pManager);
    CalcAheadFunc pCalcAheadFunc = GetCalcAheadFunc(pManager);

    GetFirstDrawParticleFunc pGetFirstFunc = GetGetFirstDrawParticleFunc(
        rSetting.mFlags & EmitterDrawSetting::FLAG_DRAW_ORDER);

    GetNextDrawParticleFunc pGetNextFunc = GetGetNextDrawParticleFunc(
        rSetting.mFlags & EmitterDrawSetting::FLAG_DRAW_ORDER);

    bool first = true;

    for (Particle* pIt = pGetFirstFunc(pManager); pIt != NULL;
         pIt = pGetNextFunc(pManager, pIt)) {
        f32 sx = pIt->Draw_GetSizeX();
        if (sx < std::numeric_limits<f32>::epsilon()) {
            continue;
        }

        f32 sy = pIt->Draw_GetSizeY();
        if (sy < std::numeric_limits<f32>::epsilon()) {
            continue;
        }

        SetupGP(pIt, rSetting, rInfo, first, false);
        first = false;

        math::VEC3 aheadVec;
        pCalcAheadFunc(&aheadVec, &ahead, pIt);
        math::VEC3TransformNormal(&aheadVec, &viewMtx, &aheadVec);

        f32 mag = math::FSqrt(aheadVec.x * aheadVec.x + aheadVec.y * aheadVec.y);

        f32 rc, rs;
        if (mag == 0.0f) {
            rs = 0.0f;
            rc = 1.0f;
        } else {
            f32 denom = 1.0f / mag;
            rs = -aheadVec.x * denom;
            rc = aheadVec.y * denom;
        }

        DispParticle_Directional(pIt, viewMtx, vx, vy, vz, rc, rs, sx, sy, pivot,
                                 flags);
    }
}

inline void DrawBillboardStrategy::DispParticle_Directional(
    Particle* pParticle, const math::MTX34& rViewMtx, f32 vx, f32 vy, f32 vz,
    f32 rc, f32 rs, f32 sx, f32 sy, const math::VEC2& rPivot, int flags) {
#pragma unused(vz)

    math::VEC3 p0;
    math::VEC3 d0;
    math::VEC3 d1;
    math::VEC3 pos;

    math::VEC3Transform(&pos, &rViewMtx, &pParticle->mParameter.mPosition);

    f32 px = rPivot.x;
    f32 py = rPivot.y;

    f32 vx_rc = vx * rc;
    f32 vx_rs = vx * rs;
    f32 vy_rc = vy * rc;
    f32 vy_rs = vy * rs;

    f32 dx0 = sx * px;
    f32 dy0 = sy * py;

    f32 exp0 = px - dx0;
    f32 exp1 = py - dy0;

    p0.x = vx_rc * exp0 + vy_rs * exp1 + pos.x;
    p0.y = vx_rs * exp0 - vy_rc * exp1 + pos.y;
    p0.z = pos.z;

    d0.x = vx_rc * sx;
    d0.y = vx_rs * sx;
    d0.z = 0.0f;

    d1.x = vy_rs * sy;
    d1.y = -vy_rc * sy;
    d1.z = 0.0f;

    DispPolygon(p0, d0, d1, flags);
}

void DrawBillboardStrategy::DispPolygon(const math::VEC3& rP,
                                        const math::VEC3& rD1,
                                        const math::VEC3& rD2, int flags) {

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    {
        GXPosition(rP - rD1);
        if (flags != 0) {
            GXTexCoord1x8(0);
        }

        GXPosition(rP - rD2);
        if (flags != 0) {
            GXTexCoord1x8(1);
        }

        GXPosition(rP + rD1);
        if (flags != 0) {
            GXTexCoord1x8(2);
        }

        GXPosition(rP + rD2);
        if (flags != 0) {
            GXTexCoord1x8(3);
        }
    }
    GXEnd();
}

void DrawBillboardStrategy::CalcZOffset(math::MTX34* pMtx,
                                        const ParticleManager* pManager,
                                        const DrawInfo& rInfo, f32 offsetZ) {

    f32 proj[GX_PROJECTION_SZ];
    GXGetProjectionv(proj);

    switch (static_cast<GXProjectionType>(proj[0])) {
        case GX_PERSPECTIVE: {
            math::MTX34 glbMtx;
            pManager->mManagerEM->CalcGlobalMtx(&glbMtx);

            math::VEC3 pos(glbMtx._03, glbMtx._13, glbMtx._23);
            math::VEC3TransformCoord(&pos, rInfo.GetViewMtx(), &pos);

            if (Normalize(&pos)) {
                if (pos.z >= 0.0f) {
                    pMtx->_03 += pos.x * offsetZ;
                    pMtx->_13 += pos.y * offsetZ;
                    pMtx->_23 += pos.z * offsetZ;
                } else {
                    pMtx->_03 -= pos.x * offsetZ;
                    pMtx->_13 -= pos.y * offsetZ;
                    pMtx->_23 -= pos.z * offsetZ;
                }
            }
            break;
        }

        case GX_ORTHOGRAPHIC: {
            pMtx->_23 += offsetZ;
            break;
        }

        default: {
            break;
        }
    }
}

void DrawBillboardStrategy::InitGraphics(const DrawInfo& rInfo,
                                         ParticleManager* pManager) {

    const EmitterDrawSetting& rSetting =
        *pManager->mResource->GetEmitterDrawSetting();

    InitTexture(rSetting);
    InitTev(rSetting, rInfo);
    InitColor(pManager, rSetting, rInfo);

    GXEnableTexOffsets(GX_TEXCOORD0, TRUE, TRUE);

    GXSetArray(GX_VA_TEX0, billboard_tex0_u8, 2);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);

    if (mNumTexmap > 0) {
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
    }

    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);

    math::MTX34 ident;
    math::MTX34Identity(&ident);
    GXLoadPosMtxImm(ident, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
}

DrawStrategyImpl::CalcAheadFunc
DrawBillboardStrategy::GetCalcAheadFunc(ParticleManager* pManager) {

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

    case EmitterDrawSetting::AHEAD_BB_PARTICLE_BOTH: {
        return CalcAhead_ParticleBoth;
    }

    default: {
        return CalcAhead_Speed;
    }
    }
}

} // namespace ef
} // namespace nw4r
