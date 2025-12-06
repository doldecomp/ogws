#include <nw4r/ef.h>
#include <nw4r/math.h>

#include <revolution/GX.h>

namespace nw4r {
namespace ef {

static math::MTX34 CalcLocalTransform(f32 px, f32 py, f32 sx, f32 sy,
                                      const nw4r::math::MTX34& rRot);

static math::MTX34 CalcRotate(Particle* pParticle, u8 axis);

static u8 free_tex0_u8[] = {0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01};

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

DrawFreeStrategy::DrawFreeStrategy() {}

void DrawFreeStrategy::Draw(const DrawInfo& rInfo, ParticleManager* pManager) {
    InitGraphics(rInfo, pManager);

    const EmitterDrawSetting& rSetting =
        *pManager->mResource->GetEmitterDrawSetting();

    math::MTX34 glbMtx;
    math::MTX34 posMtx;

    pManager->CalcGlobalMtx(&glbMtx);
    math::MTX34Mult(&posMtx, rInfo.GetViewMtx(), &glbMtx);
    GXLoadPosMtxImm(posMtx, GX_PNMTX0);

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

        SetupGP(pParticle, rSetting, rInfo, first, false);
        first = false;

        math::MTX34 rotMtx = CalcRotate(pParticle, rSetting.typeAxis);
        math::MTX34 locMtx = CalcLocalTransform(px, py, sx, sy, rotMtx);

        locMtx._03 += pParticle->mParameter.mPosition.x;
        locMtx._13 += pParticle->mParameter.mPosition.y;
        locMtx._23 += pParticle->mParameter.mPosition.z;

        // clang-format off
        static const math::_VEC3 p[4] = {
            -1.0f, -1.0f, 0.0f,
            -1.0f,  1.0f, 0.0f,
             1.0f,  1.0f, 0.0f,
             1.0f, -1.0f, 0.0f
        };
        // clang-format on

        DrawQuad(locMtx, p, mNumTexmap > 0);

        if (rSetting.typeOption == EmitterDrawSetting::TYPE_CMN_CROSS) {
            // clang-format off
            static const math::_VEC3 px[4] = {
                0.0f, -1.0f,  1.0f,
                0.0f,  1.0f,  1.0f,
                0.0f,  1.0f, -1.0f,
                0.0f, -1.0f, -1.0f
            };
            // clang-format on

            DrawQuad(locMtx, px, mNumTexmap > 0);
        }
    }
}

void DrawFreeStrategy::InitGraphics(const DrawInfo& rInfo,
                                    ParticleManager* pManager) {

    const EmitterDrawSetting& rSetting =
        *pManager->mResource->GetEmitterDrawSetting();

    InitTexture(rSetting);
    InitTev(rSetting, rInfo);
    InitColor(pManager, rSetting, rInfo);

    GXEnableTexOffsets(GX_TEXCOORD0, TRUE, TRUE);

    GXSetArray(GX_VA_TEX0, free_tex0_u8, 2);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);

    if (mNumTexmap > 0) {
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
    }

    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);

    GXSetCurrentMtx(GX_PNMTX0);
}

static math::MTX34 CalcLocalTransform(f32 px, f32 py, f32 sx, f32 sy,
                                      const nw4r::math::MTX34& rRot) {

    f32 sx_px = sx * px;
    f32 sy_py = sy * py;

    // clang-format off
    return math::MTX34(
        rRot._00 * sx,  rRot._01 * sy,  rRot._02 * sx,  -rRot._00 * sx_px - rRot._01 * sy_py + px,
        rRot._10 * sx,  rRot._11 * sy,  rRot._12 * sx,  -rRot._10 * sx_px - rRot._11 * sy_py + py,
        rRot._20 * sx,  rRot._21 * sy,  rRot._22 * sx,  -rRot._20 * sx_px - rRot._21 * sy_py);
    // clang-format on
}

static math::MTX34 CalcRotate(Particle* pParticle, u8 axis) {
#pragma unused(axis)

    math::VEC3 rot;
    pParticle->Draw_GetRotate(&rot);

    f32 sx, cx;
    math::SinCosRad(&sx, &cx, rot.x);

    f32 sy, cy;
    math::SinCosRad(&sy, &cy, rot.y);

    f32 sz, cz;
    math::SinCosRad(&sz, &cz, rot.z);

    f32 sx_sy = sx * sy;
    f32 cx_sy = cx * sy;

    // clang-format off
    return math::MTX34(
        cy * cz,  sx_sy * cz - cx * sz,  cx_sy * cz + sx * sz,  0.0f,
        cy * sz,  sx_sy * sz + cx * cz,  cx_sy * sz - sx * cz,  0.0f,
            -sy,               cy * sx,               cx * cy,  0.0f);
    // clang-format on
}

} // namespace ef
} // namespace nw4r
