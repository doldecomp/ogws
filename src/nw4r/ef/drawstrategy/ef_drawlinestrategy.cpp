#include <nw4r/ef.h>
#include <nw4r/math.h>

#include <revolution/GX.h>

#include <algorithm>
#include <limits>

namespace nw4r {
namespace ef {

static void DrawPolygon(const nw4r::math::VEC3& rP0,
                        const nw4r::math::VEC3& rP1, bool texCoord);

static void GXPosition(const math::VEC3& rPos);

DrawLineStrategy::DrawLineStrategy() {}

void DrawLineStrategy::Draw(const DrawInfo& rInfo, ParticleManager* pManager) {
    InitGraphics(rInfo, pManager);

    const EmitterDrawSetting& rSetting =
        *pManager->mResource->GetEmitterDrawSetting();

    math::MTX34 glbMtx;
    math::MTX34 posMtx;

    pManager->CalcGlobalMtx(&glbMtx);
    math::MTX34Mult(&posMtx, rInfo.GetViewMtx(), &glbMtx);
    GXLoadPosMtxImm(posMtx, GX_PNMTX0);

    GetFirstDrawParticleFunc pGetFirstFunc = GetGetFirstDrawParticleFunc(
        rSetting.mFlags & EmitterDrawSetting::FLAG_DRAW_ORDER);

    GetNextDrawParticleFunc pGetNextFunc = GetGetNextDrawParticleFunc(
        rSetting.mFlags & EmitterDrawSetting::FLAG_DRAW_ORDER);

    u8 prevLineWidth = 0;
    bool first = true;

    for (Particle* pParticle = pGetFirstFunc(pManager); pParticle != NULL;
         pParticle = pGetNextFunc(pManager, pParticle)) {

        f32 sx = pParticle->Draw_GetSizeX();
        if (sx < std::numeric_limits<f32>::epsilon()) {
            continue;
        }

        f32 sy = pParticle->Draw_GetSizeY();
        if (sy < std::numeric_limits<f32>::epsilon()) {
            continue;
        }

        math::VEC3 p0 = pParticle->mParameter.mPosition;

        math::VEC3 p1;
        pParticle->GetMoveDir(&p1);

        if (!Normalize(&p1)) {
            continue;
        }

        p1 *= sy;
        math::VEC3Sub(&p1, &p0, &p1);

        u8 lineWidth = static_cast<u8>(6.0f * std::min(42.5f, sx));
        if (lineWidth == 0) {
            continue;
        }

        if (prevLineWidth != lineWidth) {
            prevLineWidth = lineWidth;
            GXSetLineWidth(lineWidth, 5);

            SetupGP(pParticle, rSetting, rInfo, first, true);
        } else {
            SetupGP(pParticle, rSetting, rInfo, first, false);
        }

        first = false;
        DrawPolygon(p0, p1, mNumTexmap > 0);
    }
}

void DrawLineStrategy::InitGraphics(const DrawInfo& rInfo,
                                    ParticleManager* pManager) {

    const EmitterDrawSetting& rSetting =
        *pManager->mResource->GetEmitterDrawSetting();

    InitTexture(rSetting);
    InitTev(rSetting, rInfo);
    InitColor(pManager, rSetting, rInfo);

    GXEnableTexOffsets(GX_TEXCOORD0, TRUE, TRUE);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);

    if (mNumTexmap > 0) {
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    }

    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    GXSetCurrentMtx(GX_PNMTX0);
}

static void DrawPolygon(const nw4r::math::VEC3& rP0,
                        const nw4r::math::VEC3& rP1, bool texCoord) {

    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    {
        GXPosition(rP0);
        if (texCoord) {
            GXTexCoord2f32(0.0f, 0.0f);
        }

        GXPosition(rP1);
        if (texCoord) {
            GXTexCoord2f32(0.0f, 1.0f);
        }
    }
    GXEnd();
}

static void GXPosition(const math::VEC3& rPos) {
    GXPosition3f32(rPos.x, rPos.y, rPos.z);
}

} // namespace ef
} // namespace nw4r
