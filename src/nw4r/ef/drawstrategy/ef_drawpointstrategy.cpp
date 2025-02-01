#include <nw4r/ef.h>
#include <nw4r/math.h>

#include <revolution/GX.h>

#include <algorithm>
#include <limits>

namespace nw4r {
namespace ef {

static void DrawPoint(const math::VEC3& rPos, bool texCoord);
static void GXPosition(const math::VEC3& rPos);

DrawPointStrategy::DrawPointStrategy() {}

void DrawPointStrategy::Draw(const DrawInfo& rInfo, ParticleManager* pManager) {
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

    u8 prevPointSize = 0;
    bool first = true;

    for (Particle* pParticle = pGetFirstFunc(pManager); pParticle != NULL;
         pParticle = pGetNextFunc(pManager, pParticle)) {

        f32 sx = pParticle->Draw_GetSizeX();
        if (sx < std::numeric_limits<f32>::epsilon()) {
            continue;
        }

        u8 pointSize = static_cast<u8>(6.0f * std::min(42.5f, sx));
        if (pointSize == 0) {
            continue;
        }

        if (prevPointSize != pointSize) {
            prevPointSize = pointSize;
            GXSetPointSize(pointSize, 5);

            SetupGP(pParticle, rSetting, rInfo, first, true);
        } else {
            SetupGP(pParticle, rSetting, rInfo, first, false);
        }

        first = false;
        DrawPoint(pParticle->mParameter.mPosition, mNumTexmap > 0);
    }
}

static void DrawPoint(const math::VEC3& rPos, bool texCoord) {
    GXBegin(GX_POINTS, GX_VTXFMT0, 1);
    {
        GXPosition(rPos);

        if (texCoord) {
            GXTexCoord2f32(0.0f, 0.0f);
        }
    }
    GXEnd();
}

static void GXPosition(const math::VEC3& rPos) {
    GXPosition3f32(rPos.x, rPos.y, rPos.z);
}

void DrawPointStrategy::InitGraphics(const DrawInfo& rInfo,
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

} // namespace ef
} // namespace nw4r
