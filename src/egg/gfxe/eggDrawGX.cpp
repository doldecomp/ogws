#include <egg/core.h>
#include <egg/gfxe.h>

#include <revolution/GX.h>

// Vertex data uses fixed-point decimal values (2.14)
#define FX2_14(X) static_cast<s16>((X) * 0x4000)

namespace EGG {

const GXColor DrawGX::BLACK = {0, 0, 0, 255};
const GXColor DrawGX::WHITE = {255, 255, 255, 255};
const GXColor DrawGX::RED = {255, 0, 0, 255};
const GXColor DrawGX::GREEN = {0, 255, 0, 255};
const GXColor DrawGX::BLUE = {0, 0, 255, 255};
const GXColor DrawGX::ORANGE = {255, 162, 0, 255};

DrawGX::DLEntry DrawGX::s_DL[DL_MAX];
const DrawGX::DL DrawGX::s_circleDLTbl[CIRCLE_MAX] = {DL_CIRCLE_16,
                                                      DL_CIRCLE_32};

nw4r::math::MTX34 DrawGX::s_cameraMtx;
u32 DrawGX::s_flag = 0;

namespace {

GXLightID LIGHTMASK_DEFAULT = GX_LIGHT0;
GXTexMapID TEXMAP_DEFAULT = GX_TEXMAP0;

f32 QUAD_SCALE = 1.0f;

GXTexObj CLEAR_Z_TEX_OBJ;
u32 CLEAR_Z_TX[4 * 4] ALIGN(32) = {
    // clang-format off
    0x00FF00FF, 0x00FF00FF, 0x00FF00FF, 0x00FF00FF,
    0x00FF00FF, 0x00FF00FF, 0x00FF00FF, 0x00FF00FF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
    // clang-format on
};

} // namespace

namespace {

void DrawQuadNormal(u8 x1, u8 x2, u8 x3, u8 x4, u8 y) {
    GXPosition2u8(x1, y);
    GXPosition2u8(x2, y);
    GXPosition2u8(x3, y);
    GXPosition2u8(x4, y);
}

void DrawQuadLineStripNormal(u8 x1, u8 x2, u8 x3, u8 x4, u8 y) {
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);
    {
        GXPosition2u8(x1, y);
        GXPosition2u8(x2, y);
        GXPosition2u8(x3, y);
        GXPosition2u8(x4, y);
        GXPosition2u8(x1, y);
    }
    GXEnd();
}

void DrawCircleYPolygonFan(const nw4r::math::MTX34& rMtx, f32 radius,
                           u16 divide) {
#line 104
    EGG_ASSERT(divide > 0);

    f32 step = 2 * NW4R_MATH_PI / divide;

    nw4r::math::VEC3 v1(0.0f, 1.0f, 0.0f);
    nw4r::math::VEC3 v2(0.0f, radius, 0.0f);

    s32 segmentNum = divide + 1;

    nw4r::math::VEC3Transform(&v1, &rMtx, &v1);
    nw4r::math::VEC3Transform(&v2, &rMtx, &v2);

    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, segmentNum + 1);
    {
        GXPosition3f32(v2.x, v2.y, v2.z);
        GXPosition3f32(v1.x, v1.y, v1.z);

        for (int i = 0; i < segmentNum; i++) {
            nw4r::math::VEC3 vtx(0.5f * nw4r::math::SinRad(-step * i), 0.0f,
                                 0.5f * nw4r::math::CosRad(-step * i));

            nw4r::math::VEC3Transform(&vtx, &rMtx, &vtx);
            GXPosition3f32(vtx.x, vtx.y, vtx.z);

            nw4r::math::VEC3 prev(0.5f * nw4r::math::SinRad(-step * (i - 1)),
                                  0.0f,
                                  0.5f * nw4r::math::CosRad(-step * (i - 1)));

            nw4r::math::VEC3 next(0.5f * nw4r::math::SinRad(-step * (i + 1)),
                                  0.0f,
                                  0.5f * nw4r::math::CosRad(-step * (i + 1)));

            nw4r::math::VEC3Transform(&prev, &rMtx, &prev);
            nw4r::math::VEC3Transform(&next, &rMtx, &next);

            nw4r::math::VEC3Sub(&prev, &prev, &v2);
            nw4r::math::VEC3Sub(&next, &next, &v2);

            nw4r::math::VEC3 nrm;
            nw4r::math::VEC3Cross(&nrm, &next, &prev);
            nw4r::math::VEC3Normalize(&nrm, &nrm);
            GXPosition3f32(nrm.x, nrm.y, nrm.z);
        }
    }
    GXEnd();
}

} // namespace

void DrawGX::Initialize(Heap* pHeap) {
    pHeap = pHeap == NULL ? Heap::getCurrentHeap() : pHeap;

    InitClearTexObj();
    nw4r::math::MTX34Identity(&s_cameraMtx);
    CreateDisplayList(pHeap);
}

void DrawGX::InitClearTexObj() {
    GXInitTexObj(&CLEAR_Z_TEX_OBJ, &CLEAR_Z_TX, 4, 4, GX_TF_Z24X8, GX_REPEAT,
                 GX_REPEAT, GX_FALSE);

    GXInitTexObjLOD(&CLEAR_Z_TEX_OBJ, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f,
                    GX_FALSE, GX_FALSE, GX_ANISO_1);
}

GXLightID DrawGX::GetLightMaskDefault() {
    return LIGHTMASK_DEFAULT;
}

GXTexMapID DrawGX::GetTexMapDefault() {
    return TEXMAP_DEFAULT;
}

void DrawGX::BeginDrawCube() {
    ResetMaterial(COLORCHAN_LIGHT);
    SetVtxState(VTXTYPE_CUBE);
}

void DrawGX::BeginDrawSphere() {
    ResetMaterial(COLORCHAN_LIGHT);
    SetVtxState(VTXTYPE_SPHERE);
}

void DrawGX::BeginDrawLine(ColorChannel chan, ZMode zMode) {
    SetMat_ColorChannel(chan);
    SetMat_TexGen(TEXGEN_DISABLE);
    SetMat_Ind();

    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE,
                          GX_CH_ALPHA);
    GXSetNumTevStages(1);
    SetMat_Tev(GX_TEVSTAGE0, TEVSETTING_COLOR);

    SetMat_PE(zMode, BLEND_NORMAL);
    SetVtxState(VTXTYPE_LINE);
}

void DrawGX::BeginDrawCornY() {
    ResetMaterial(COLORCHAN_LIGHT);
    SetVtxState(VTXTYPE_CONE);
}

void DrawGX::BeginDrawCircleZ(ColorChannel chan, ZMode zMode) {
    SetMat_ColorChannel(chan);
    SetMat_TexGen(TEXGEN_DISABLE);
    SetMat_Ind();

    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE,
                          GX_CH_ALPHA);
    GXSetNumTevStages(1);
    SetMat_Tev(GX_TEVSTAGE0, TEVSETTING_COLOR);

    SetMat_PE(zMode, BLEND_NORMAL);
    SetVtxState(VTXTYPE_CIRCLE);
}

void DrawGX::BeginDrawPolygon(ColorChannel chan) {
    ResetMaterial(chan);

    switch (chan) {
    case COLORCHAN_LIGHT: {
        GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT0,
                      GX_DF_CLAMP, GX_AF_NONE);
        break;
    }

    case COLORCHAN_COLOR: {
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT0,
                      GX_DF_CLAMP, GX_AF_NONE);
        break;
    }

    default: {
        break;
    }
    }

    SetVtxState(VTXTYPE_POLYGON);

    nw4r::math::MTX34 dummy;
    nw4r::math::MTX34Identity(&dummy);

    GXLoadPosMtxImm(s_cameraMtx, GX_PNMTX0);
    GXLoadNrmMtxImm(s_cameraMtx, GX_PNMTX0);

    GXSetChanMatColor(GX_COLOR0A0, WHITE);
}

void DrawGX::BeginDrawQuad(ColorChannel chan, ZMode zMode, Blend blend,
                           bool texture, bool alpha) {

    SetMat_ColorChannel(chan);
    SetMat_TexGen(texture ? TEXGEN_ENABLE : TEXGEN_DISABLE);
    SetMat_Ind();

    GXSetNumTevStages(1);
    SetMat_Tev(GX_TEVSTAGE0, texture ? TEVSETTING_TEXTURE : TEVSETTING_COLOR);

    if (alpha) {
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                        GX_CA_RASA);
    }

    SetMat_PE(zMode, blend);
    SetVtxState(texture ? VTXTYPE_QUAD_TEXTURE : VTXTYPE_QUAD);
}

void DrawGX::BeginDrawScreen(bool lu, bool texture, bool alpha) {
    SetMat_ColorChannel(COLORCHAN_COLOR);
    SetMat_TexGen(texture ? TEXGEN_ENABLE : TEXGEN_DISABLE);
    SetMat_Ind();

    GXSetNumTevStages(1);
    SetMat_Tev(GX_TEVSTAGE0, texture ? TEVSETTING_TEXTURE : TEVSETTING_COLOR);

    if (alpha) {
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                        GX_CA_RASA);
    }

    SetMat_PE(ZMODE_ALWAYS, BLEND_NORMAL);

    static const VtxType tbl[true + 1][true + 1] = {
        {VTX_TYPE_SCREEN_TEXTURE, VTX_TYPE_SCREEN},       // CC
        {VTX_TYPE_SCREEN_TEXTURE_LU, VTX_TYPE_SCREEN_LU}, // LU
    };

    SetVtxState(tbl[lu ? 1 : 0][texture ? 0 : 1]);
}

void DrawGX::BeginDrawShadowVolume(u8 alpha) {
    StateGX::GXSetColorUpdate_(false);
    StateGX::GXSetAlphaUpdate_(true);

    SetMat_ColorChannel(COLORCHAN_COLOR);
    SetMat_TexGen(TEXGEN_DISABLE);
    SetMat_Ind();

    GXSetChanAmbColor(GX_COLOR0A0, WHITE);
    GXSetChanMatColor(GX_COLOR0A0, WHITE);

    GXSetNumTevStages(1);
    GXSetTevDirect(GX_TEVSTAGE0);

    if (alpha == 0) {
        if (StateGX::getDefaultPixelFormat() == GX_PF_RGBA6_Z24) {
            GXColor tevColor = {0, 0, 0, 4};
            GXSetTevColor(GX_TEVREG0, tevColor);
        } else {
            GXColor tevColor = {4, 0, 0, 0};
            GXSetTevColor(GX_TEVREG0, tevColor);
        }

        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                      GX_COLOR_NULL);

        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO,
                        GX_CC_C0);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                        GX_CA_A0);

        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_TRUE, GX_TEVPREV);

        SetZMode(ZMODE_XLU);
    } else {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                      GX_COLOR0A0);

        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO,
                        GX_CC_RASC);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                        GX_CA_A0);

        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_TRUE, GX_TEVPREV);

        SetZMode(ZMODE_OPA);
    }

    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
}

DECOMP_FORCEACTIVE(eggDrawGX_cpp,
                  "pTexObj");

void DrawGX::DrawLine(const nw4r::math::VEC3* pPoints, u16 num, GXColor color,
                      u8 width) {

#line 506
    EGG_ASSERT(num % 2 == 0);

    GXLoadPosMtxImm(s_cameraMtx, GX_PNMTX0);
    GXSetChanMatColor(GX_COLOR0A0, color);
    GXSetLineWidth(width, 0);

    GXBegin(GX_LINES, GX_VTXFMT0, num);
    {
        for (int i = 0; i < num; i++) {
            GXPosition3f32(pPoints[i].x, pPoints[i].y, pPoints[i].z);
        }
    }
    GXEnd();
}

void DrawGX::DrawLineStrip(const nw4r::math::VEC3* pPoints, u16 num,
                           GXColor color, u8 width) {

    GXLoadPosMtxImm(s_cameraMtx, GX_PNMTX0);
    GXSetChanMatColor(GX_COLOR0A0, color);
    GXSetLineWidth(width, 0);

    GXBegin(GX_LINESTRIP, GX_VTXFMT0, num);
    {
        for (int i = 0; i < num; i++) {
            GXPosition3f32(pPoints[i].x, pPoints[i].y, pPoints[i].z);
        }
    }
    GXEnd();
}

void DrawGX::DrawCircle2D(Circle circle, f32 x, f32 y, f32 radius,
                          GXColor color) {

    nw4r::math::MTX34 mtx;
    PSMTXScale(mtx, radius * 2, radius * 2, 1.0f);
    PSMTXTransApply(mtx, mtx, x, y, 0.0f);

    GXSetCullMode(GX_CULL_NONE);
    DrawDL(s_circleDLTbl[circle], mtx, color);
}

void DrawGX::DrawCornY(Circle circle, const nw4r::math::MTX34& rMtx,
                       GXColor color) {

    switch (circle) {
    case CIRCLE_16: {
        DrawDLWorld(DL_CONE_16, rMtx, color);
        break;
    }

    case CIRCLE_32: {
        DrawDLWorld(DL_CONE_32, rMtx, color);
        break;
    }

    default: {
        break;
    }
    }
}

void DrawGX::DrawPolygon(const nw4r::math::VEC3& rP0,
                         const nw4r::math::VEC3& rP1,
                         const nw4r::math::VEC3& rP2, GXColor color) {

    nw4r::math::VEC3 v1 = rP1 - rP0;
    nw4r::math::VEC3 v0 = rP2 - rP0;

    nw4r::math::VEC3 v2;
    nw4r::math::VEC3Cross(&v2, &v0, &v1);
    nw4r::math::VEC3Normalize(&v2, &v2);

    GXBegin(GX_TRIANGLES, GX_VTXFMT0, 3);
    {
        GXPosition3f32(rP0.x, rP0.y, rP0.z);
        GXPosition3f32(v2.x, v2.y, v2.z);
        GXColor4u8(color.r, color.g, color.b, color.a);

        GXPosition3f32(rP1.x, rP1.y, rP1.z);
        GXPosition3f32(v2.x, v2.y, v2.z);
        GXColor4u8(color.r, color.g, color.b, color.a);

        GXPosition3f32(rP2.x, rP2.y, rP2.z);
        GXPosition3f32(v2.x, v2.y, v2.z);
        GXColor4u8(color.r, color.g, color.b, color.a);
    }
    GXEnd();
}

void DrawGX::BeginDrawShadowVolumeTexture(bool lu, GXColor color,
                                          Blend blendMode) {

    SetMat_ColorChannel(COLORCHAN_COLOR);
    SetMat_TexGen(TEXGEN_ENABLE);
    SetMat_Ind();

    if (blendMode == BLEND_MUL_INV) {
        GXColor colorInv = {255 - color.r, 255 - color.g, 255 - color.b,
                            255 - color.a};

        GXSetTevColor(GX_TEVREG0, colorInv);
    } else {
        GXSetTevColor(GX_TEVREG0, color);
    }

    GXSetNumTevStages(1);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE,
                          GX_CH_ALPHA);

    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GetTexMapDefault(),
                  GX_COLOR_NULL);

    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_C0, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_COMP_RGB8_GT, GX_TB_ZERO,
                    GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_COMP_A8_GT, GX_TB_ZERO, GX_CS_SCALE_1,
                    GX_TRUE, GX_TEVPREV);

    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);

    SetZMode(ZMODE_ALWAYS);
    SetBlendMode(blendMode);
    SetVtxState(lu ? VTX_TYPE_SCREEN_TEXTURE_LU : VTX_TYPE_SCREEN_TEXTURE);
}

void DrawGX::ClearEfb(const nw4r::math::MTX34& rMtx, bool colorUpdate,
                      bool alphaUpdate, bool texture, GXColor color, bool lu) {

    StateGX::ScopedColorUpdate colorLock(colorUpdate);
    StateGX::ScopedAlphaUpdate alphaLock(alphaUpdate);

    SetMat_ColorChannel(COLORCHAN_COLOR);
    GXSetCullMode(GX_CULL_NONE);

    if (texture) {
        SetMat_TexGen(TEXGEN_ENABLE);
        GXLoadTexObj(&CLEAR_Z_TEX_OBJ, GetTexMapDefault());
    } else {
        SetMat_TexGen(TEXGEN_DISABLE);
    }

    SetMat_Ind();

    GXSetNumTevStages(1);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevColor(GX_TEVREG0, color);

    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE,
                          GX_CH_ALPHA);

    if (texture) {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GetTexMapDefault(),
                      GX_COLOR_NULL);
    } else {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                      GX_COLOR_NULL);
    }

    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                    GX_TRUE, GX_TEVPREV);

    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                    GX_TRUE, GX_TEVPREV);

    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);

    if (texture) {
        GXSetZTexture(GX_ZT_REPLACE, GX_TF_Z24X8, 0);
        GXSetZCompLoc(GX_FALSE);
        SetZMode(ZMODE_CLEAR);
    } else {
        SetZMode(ZMODE_ALWAYS);
    }

    SetBlendMode(BLEND_NONE);
    SetVtxState(lu ? VTX_TYPE_SCREEN_TEXTURE_LU : VTX_TYPE_SCREEN_TEXTURE);
    DrawScreenTexture(rMtx);

    if (texture) {
        GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z24X8, 0);
        GXSetZCompLoc(GX_TRUE);
    }
}

void DrawGX::ResetMaterial(ColorChannel chan) {
    SetMat_ColorChannel(chan);
    SetMat_TexGen(TEXGEN_DISABLE);
    SetMat_Ind();

    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE,
                          GX_CH_ALPHA);
    GXSetNumTevStages(1);
    SetMat_Tev(GX_TEVSTAGE0, TEVSETTING_COLOR);

    SetMat_PE(ZMODE_OPA, BLEND_NORMAL);
}

void DrawGX::SetMat_ColorChannel(ColorChannel chan) {
    switch (chan) {
    case COLORCHAN_LIGHT: {
        GXSetNumChans(1);
        GXSetCullMode(GX_CULL_BACK);

        GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_REG,
                      GetLightMaskDefault(), GX_DF_CLAMP, GX_AF_SPOT);
        GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX,
                      GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        break;
    }

    case COLORCHAN_COLOR: {
        GXSetNumChans(1);
        GXSetCullMode(GX_CULL_BACK);

        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG,
                      GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
        GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX,
                      GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        break;
    }
    }
}

void DrawGX::SetMat_TexGen(TexGen texGen) {
    switch (texGen) {
    case TEXGEN_DISABLE: {
        GXSetNumTexGens(0);
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
        break;
    }

    case TEXGEN_ENABLE: {
        GXSetNumTexGens(1);
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
        break;
    }
    }
}

void DrawGX::SetMat_Ind() {
    GXSetNumIndStages(0);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
}

void DrawGX::SetMat_Tev(GXTevStageID stage, TevSetting setting) {
    switch (setting) {
    case TEVSETTING_COLOR: {
        GXSetTevDirect(stage);
        GXSetTevOrder(stage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevSwapMode(stage, GX_TEV_SWAP0, GX_TEV_SWAP0);

        GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
        GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE,
                        GX_TEVPREV);

        GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
        GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE,
                        GX_TEVPREV);
        break;
    }

    case TEVSETTING_TEXTURE: {
        GXSetTevDirect(stage);
        GXSetTevOrder(stage, GX_TEXCOORD0, GetTexMapDefault(), GX_COLOR0A0);
        GXSetTevSwapMode(stage, GX_TEV_SWAP0, GX_TEV_SWAP0);

        GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
        GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE,
                        GX_TEVPREV);

        GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
        GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE,
                        GX_TEVPREV);
        break;
    }
    }
}

void DrawGX::SetMat_PE(ZMode zMode, Blend blendMode) {
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);

    SetZMode(zMode);
    SetBlendMode(blendMode);
}

void DrawGX::LoadTexture(const ResTIMG* pRes, GXTexMapID map) {
#line 982
    EGG_ASSERT(pRes != NULL);

    GXTexObj obj;
    GXUtility::getTexObj(&obj, *pRes);

    GXLoadTexObj(&obj, map);
}

DECOMP_FORCEACTIVE(eggDrawGX_cpp,
                  "tex.IsValid()");

void DrawGX::SetVtxState(VtxType vtxType) {
    GXClearVtxDesc();

    switch (vtxType) {
    case VTXTYPE_CUBE: {
        static const s16 CUBE_VTX[][3] ALIGN(32) = {
            // clang-format off
            {FX2_14(-0.5), FX2_14( 0.5), FX2_14(-0.5)},
            {FX2_14(-0.5), FX2_14( 0.5), FX2_14( 0.5)},
            {FX2_14( 0.5), FX2_14( 0.5), FX2_14( 0.5)},
            {FX2_14( 0.5), FX2_14( 0.5), FX2_14(-0.5)},
            {FX2_14(-0.5), FX2_14(-0.5), FX2_14(-0.5)},
            {FX2_14(-0.5), FX2_14(-0.5), FX2_14( 0.5)},
            {FX2_14( 0.5), FX2_14(-0.5), FX2_14( 0.5)}, // ?????
            {FX2_14( 0.5), FX2_14(-0.5), FX2_14(-0.5)}, // ?????
            // clang-format on
        };
        static const s16 CUBE_NRM[][3] ALIGN(32) = {
            // clang-format off
            {FX2_14(-1.0), FX2_14( 0.0), FX2_14( 0.0)},
            {FX2_14( 1.0), FX2_14( 0.0), FX2_14( 0.0)},
            {FX2_14( 0.0), FX2_14(-1.0), FX2_14( 0.0)},
            {FX2_14( 0.0), FX2_14( 1.0), FX2_14( 0.0)},
            {FX2_14( 0.0), FX2_14( 0.0), FX2_14(-1.0)},
            {FX2_14( 0.0), FX2_14( 0.0), FX2_14( 1.0)},
            // clang-format on
        };

        // Fixed-point decimal values (2.14)
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 14);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S16, 14);

        GXSetArray(GX_VA_POS, CUBE_VTX, sizeof(s16) * 3);
        GXSetArray(GX_VA_NRM, CUBE_NRM, sizeof(s16) * 3);

        GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
        GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
        break;
    }

    case VTXTYPE_SPHERE:
    case VTXTYPE_CYLINDER:
    case VTXTYPE_CIRCLE:
    case VTXTYPE_CONE: {
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);

        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
        break;
    }

    case VTXTYPE_POLYGON: {
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);

        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        break;
    }

    case VTXTYPE_LINE: {
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        break;
    }

    case VTXTYPE_QUAD_TEXTURE:
    case VTXTYPE_QUAD: {
        static const s16 QUAD_VTX[][3] ALIGN(32) = {
            // clang-format off
            {FX2_14(-0.5), FX2_14( 0.5), FX2_14(0.0)},
            {FX2_14( 0.5), FX2_14( 0.5), FX2_14(0.0)},
            {FX2_14( 0.5), FX2_14(-0.5), FX2_14(0.0)},
            {FX2_14(-0.5), FX2_14(-0.5), FX2_14(0.0)},
            // clang-format on
        };
        static const s16 QUAD_NRM[][3] ALIGN(32) = {
            // clang-format off
            {FX2_14(0.0), FX2_14(0.0), FX2_14(1.0)},
            // clang-format on
        };

        GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
        GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
        if (vtxType == VTXTYPE_QUAD_TEXTURE) {
            GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        }

        // Fixed-point decimal values (2.14)
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 14);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S16, 14);
        if (vtxType == VTXTYPE_QUAD_TEXTURE) {
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        }

        GXSetArray(GX_VA_POS, QUAD_VTX, sizeof(s16) * 3);
        GXSetArray(GX_VA_NRM, QUAD_NRM, sizeof(s16) * 3);
        break;
    }

    case VTXTYPE_QUAD_SHADOW: {
        static const s16 QUAD_VTX[][3] ALIGN(32) = {
            // clang-format off
            {FX2_14(-0.5), FX2_14(0.0), FX2_14(-0.5)},
            {FX2_14( 0.5), FX2_14(0.0), FX2_14(-0.5)},
            {FX2_14( 0.5), FX2_14(0.0), FX2_14( 0.5)},
            {FX2_14(-0.5), FX2_14(0.0), FX2_14( 0.5)},
            // clang-format on
        };
        static const s16 QUAD_NRM[][3] ALIGN(32) = {
            // clang-format off
            {FX2_14(0.0), FX2_14(1.0), FX2_14(0.0)},
            // clang-format on
        };

        GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
        GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);

        // Fixed-point decimal values (2.14)
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 14);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S16, 14);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

        GXSetArray(GX_VA_POS, QUAD_VTX, sizeof(s16) * 3);
        GXSetArray(GX_VA_NRM, QUAD_NRM, sizeof(s16) * 3);
        break;
    }

    case VTX_TYPE_SCREEN_TEXTURE:
    case VTX_TYPE_SCREEN_TEXTURE_LU:
    case VTX_TYPE_SCREEN:
    case VTX_TYPE_SCREEN_LU: {
        static const s16 SCREEN_VTX[][2] ALIGN(32) = {
            // clang-format off
            {0, 1},
            {0, 1},
            {1, 0},
            {1, 0},
            {0, 0}, // ?????
            {0, 0}, // ?????
            // clang-format on
        };
        static const s16 SCREEN_VTX_LU[][2] ALIGN(32) = {
            // clang-format off
            {0, 0},
            {0, 1},
            {0, 0},
            {1, 1},
            {0, 0}, // ?????
            {1, 0}, // ?????
            // clang-format on
        };
        static const s16 SCREEN_UV[][2] ALIGN(32) = {
            {0, 0},
            {1, 0},
            {1, 1},
            {0, 1},
        };

        bool lu = vtxType == VTX_TYPE_SCREEN_TEXTURE_LU ||
                  vtxType == VTX_TYPE_SCREEN_LU;

        bool texture = vtxType == VTX_TYPE_SCREEN_TEXTURE ||
                       vtxType == VTX_TYPE_SCREEN_TEXTURE_LU;

        GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
        if (texture) {
            GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
        }

        GXSetArray(GX_VA_POS, lu ? SCREEN_VTX_LU : SCREEN_VTX, sizeof(s16) * 3);
        if (texture) {
            GXSetArray(GX_VA_TEX0, SCREEN_UV, sizeof(s16) * 2);
        }

        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
        if (texture) {
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 0);
        }
        break;
    }
    }
}

void DrawGX::CreateDisplayList(Heap* pHeap) {
    static const u8 detailLevels[] = {16, 32};

    static const u32 tmpSize = 0x4000;
    u8 tmpDisplayList[tmpSize] ALIGN(32);

#line 1168
    EGG_ASSERT(( s_flag & FLAG_INITIALIZE_DISPLAY_LIST ) == 0);

    OSInitFastCast();

    for (int i_dl = 0; i_dl < DL_MAX; i_dl++) {
        DCInvalidateRange(tmpDisplayList, tmpSize);
        GXBeginDisplayList(tmpDisplayList, tmpSize);

        switch (i_dl) {
        case DL_LINE_AXIS: {
            GXSetChanMatColor(GX_COLOR0A0, RED);
            GXBegin(GX_LINES, GX_VTXFMT0, 2);
            {
                GXPosition3f32(0.0f, 0.0f, 0.0f);
                GXPosition3f32(1.0f, 0.0f, 0.0f);
            }
            GXEnd();

            GXSetChanMatColor(GX_COLOR0A0, GREEN);
            GXBegin(GX_LINES, GX_VTXFMT0, 2);
            {
                GXPosition3f32(0.0f, 0.0f, 0.0f);
                GXPosition3f32(0.0f, 1.0f, 0.0f);
            }
            GXEnd();

            GXSetChanMatColor(GX_COLOR0A0, BLUE);
            GXBegin(GX_LINES, GX_VTXFMT0, 2);
            {
                GXPosition3f32(0.0f, 0.0f, 0.0f);
                GXPosition3f32(0.0f, 0.0f, 1.0f);
            }
            GXEnd();
            break;
        }

        case DL_CUBE: {
            GXBegin(GX_QUADS, GX_VTXFMT0, 6 * 4);
            {
                DrawQuadNormal(1, 5, 4, 0, 0);
                DrawQuadNormal(3, 7, 6, 2, 1);
                DrawQuadNormal(5, 6, 7, 4, 2);
                DrawQuadNormal(3, 2, 1, 0, 3);

                DrawQuadNormal(0, 4, 7, 3, 4);
                DrawQuadNormal(2, 6, 5, 1, 5);
            }
            GXEnd();
            break;
        }

        case DL_CUBE_WIRE: {
            DrawQuadLineStripNormal(1, 5, 4, 0, 0);
            DrawQuadLineStripNormal(3, 7, 6, 2, 1);
            DrawQuadLineStripNormal(5, 6, 7, 4, 2);
            DrawQuadLineStripNormal(3, 2, 1, 0, 3);
            break;
        }

        case DL_SPHERE_4X8: {
            GXDrawSphere(4, 8);
            break;
        }

        case DL_SPHERE_8X16: {
            GXDrawSphere(8, 16);
            break;
        }

        case DL_LINE_CIRCLE_16:
        case DL_LINE_CIRCLE_32: {
            u16 numSegments = detailLevels[i_dl - DL_LINE_CIRCLE_16] + 1;
            f32 radPerSegment = 2 * NW4R_MATH_PI / (numSegments - 1);

            GXBegin(GX_LINESTRIP, GX_VTXFMT0, numSegments);
            {
                for (int i = 0; i < numSegments; i++) {
                    GXPosition3f32(0.5f * nw4r::math::CosRad(radPerSegment * i),
                                   0.5f * nw4r::math::SinRad(radPerSegment * i),
                                   0.0f);
                }
            }
            GXEnd();
            break;
        }

        case DL_CYLINDER_16:
        case DL_CYLINDER_32: {
            u16 numSegments = detailLevels[i_dl - DL_CYLINDER_16] + 1;
            f32 radPerSegment = 2 * NW4R_MATH_PI / (numSegments - 1);

            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, numSegments * 2);
            {
                for (int i = 0; i < numSegments; i++) {
                    f32 x = 0.5f * nw4r::math::SinRad(radPerSegment * i);
                    f32 z = 0.5f * nw4r::math::CosRad(radPerSegment * i);

                    GXPosition3f32(x, -0.5f, z);
                    GXPosition3f32(2.0f * x, 0.0f, 2.0f * z);
                    GXPosition3f32(x, 0.5f, z);
                    GXPosition3f32(2.0f * x, 0.0f, 2.0f * z);
                }
            }
            GXEnd();

            nw4r::math::MTX34 mtx;
            PSMTXTrans(mtx, 0.0f, 0.5f, 0.0f);
            DrawCircleYPolygonFan(mtx, 0.0f,
                                  detailLevels[i_dl - DL_CYLINDER_16]);

            nw4r::math::MTX34Identity(&mtx);
            PSMTXRotRad(mtx, 'z', NW4R_MATH_PI);
            PSMTXTransApply(mtx, mtx, 0.0f, -0.5f, 0.0f);
            DrawCircleYPolygonFan(mtx, 0.0f,
                                  detailLevels[i_dl - DL_CYLINDER_16]);
            break;
        }

        case DL_CONE_16:
        case DL_CONE_32: {
            nw4r::math::MTX34 rot;
            nw4r::math::MTX34Identity(&rot);

            DrawCircleYPolygonFan(rot, 1.0f, detailLevels[i_dl - DL_CONE_16]);

            PSMTXRotRad(rot, 'z', NW4R_MATH_PI);
            DrawCircleYPolygonFan(rot, 0.0f, detailLevels[i_dl - DL_CONE_16]);
            break;
        }

        case DL_CIRCLE_16:
        case DL_CIRCLE_32: {
            nw4r::math::MTX34 rot;
            nw4r::math::MTX34Identity(&rot);

            PSMTXRotRad(rot, 'x', NW4R_MATH_PI / 2);
            DrawCircleYPolygonFan(rot, 0.0f, detailLevels[i_dl - DL_CIRCLE_16]);
            break;
        }

        case DL_QUAD_TEXTURE:
        case DL_QUAD: {
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            {
                GXPosition2u8(0, 0);
                if (i_dl == DL_QUAD_TEXTURE) {
                    GXPosition2f32(0.0f, 0.0f);
                }

                GXPosition2u8(1, 0);
                if (i_dl == DL_QUAD_TEXTURE) {
                    GXPosition2f32(QUAD_SCALE, 0.0f);
                }

                GXPosition2u8(2, 0);
                if (i_dl == DL_QUAD_TEXTURE) {
                    GXPosition2f32(QUAD_SCALE, QUAD_SCALE);
                }

                GXPosition2u8(3, 0);
                if (i_dl == DL_QUAD_TEXTURE) {
                    GXPosition2f32(0.0f, QUAD_SCALE);
                }
            }
            GXEnd();
            break;
        }

        case DL_BOUNDBOX: {
            GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);
            {
                GXPosition3f32(-0.5f, 0.5f, 0.0f);
                GXPosition3f32(0.5f, 0.5f, 0.0f);
                GXPosition3f32(0.5f, -0.5f, 0.0f);
                GXPosition3f32(-0.5f, -0.5f, 0.0f);
                GXPosition3f32(-0.5f, 0.5f, 0.0f);
            }
            GXEnd();
            break;
        }

        case DL_SCREEN_TEXTURE:
        case DL_SCREEN: {
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            {
                GXPosition1x8(0);
                if (i_dl == DL_SCREEN_TEXTURE) {
                    GXPosition1x8(0);
                }

                GXPosition1x8(1);
                if (i_dl == DL_SCREEN_TEXTURE) {
                    GXPosition1x8(1);
                }

                GXPosition1x8(2);
                if (i_dl == DL_SCREEN_TEXTURE) {
                    GXPosition1x8(2);
                }

                GXPosition1x8(3);
                if (i_dl == DL_SCREEN_TEXTURE) {
                    GXPosition1x8(3);
                }
            }
            GXEnd();
            break;
        }

        default: {
#line 1349
            EGG_ASSERT(0);
            break;
        }
        }

        s_DL[i_dl].m_size = GXEndDisplayList();
#line 1354
        EGG_ASSERT(s_DL[i_dl].m_size < tmpSize);

        u8* pDisplayList = new (pHeap, 32) u8[s_DL[i_dl].m_size];
        s_DL[i_dl].m_list = pDisplayList;

        for (int i = 0; i < s_DL[i_dl].m_size; i++) {
            pDisplayList[i] = tmpDisplayList[i];
        }

        DCFlushRange(s_DL[i_dl].m_list, s_DL[i_dl].m_size);
    }

    s_flag |= FLAG_INITIALIZE_DISPLAY_LIST;
}

void DrawGX::DrawDL(DL dl, const nw4r::math::MTX34& rMtx) {
#line 1377
    EGG_ASSERT(s_flag & FLAG_INITIALIZE_DISPLAY_LIST);

    GXLoadPosMtxImm(rMtx, GX_PNMTX0);
    GXLoadNrmMtxImm(rMtx, GX_PNMTX0);

    GXCallDisplayList(s_DL[dl].m_list, s_DL[dl].m_size);
}

void DrawGX::DrawDL(DL dl, const nw4r::math::MTX34& rMtx, GXColor color) {
#line 1397
    EGG_ASSERT(s_flag & FLAG_INITIALIZE_DISPLAY_LIST);

    GXLoadPosMtxImm(rMtx, GX_PNMTX0);
    GXLoadNrmMtxImm(rMtx, GX_PNMTX0);
    GXSetChanMatColor(GX_COLOR0A0, color);

    GXCallDisplayList(s_DL[dl].m_list, s_DL[dl].m_size);
}

void DrawGX::SetZMode(ZMode zMode) {
#line 1417
    EGG_ASSERT(zMode < ZMODE_MAX);

    static const ZModeEntry Z_ARG[ZMODE_MAX] = {
        {GX_FALSE, GX_ALWAYS, GX_FALSE}, // ZMODE_ALWAYS
        {GX_TRUE, GX_LEQUAL, GX_TRUE},   // ZMODE_OPA
        {GX_TRUE, GX_LEQUAL, GX_FALSE},  // ZMODE_XLU
        {GX_TRUE, GX_ALWAYS, GX_TRUE},   // ZMODE_CLEAR
    };

    GXSetZMode(Z_ARG[zMode].m_enableTest, Z_ARG[zMode].m_func,
               Z_ARG[zMode].m_enableUpdate);
}

void DrawGX::SetBlendMode(Blend blendMode) {
#line 1438
    EGG_ASSERT(blendMode < BLEND_MAX);

    static const BlendEntry BLEND[BLEND_MAX] = {
        // clang-format off
        {GX_BM_BLEND,    GX_BL_SRCALPHA,    GX_BL_INVSRCALPHA, GX_LO_CLEAR}, // BLEND_NORMAL
        {GX_BM_BLEND,    GX_BL_INVSRCALPHA, GX_BL_SRCALPHA,    GX_LO_CLEAR}, // BLEND_INVERSE
        {GX_BM_BLEND,    GX_BL_ONE,         GX_BL_ONE,         GX_LO_CLEAR}, // BLEND_ADD
        {GX_BM_BLEND,    GX_BL_SRCALPHA,    GX_BL_ONE,         GX_LO_CLEAR}, // BLEND_ADD_ALPHA
        {GX_BM_BLEND,    GX_BL_DSTCLR,      GX_BL_ONE,         GX_LO_CLEAR}, // BLEND_MUL_ADD
        {GX_BM_SUBTRACT, GX_BL_ONE,         GX_BL_ONE,         GX_LO_CLEAR}, // BLEND_SUB
        {GX_BM_BLEND,    GX_BL_ZERO,        GX_BL_SRCCLR,      GX_LO_CLEAR}, // BLEND_MUL
        {GX_BM_BLEND,    GX_BL_ZERO,        GX_BL_INVSRCCLR,   GX_LO_CLEAR}, // BLEND_MUL_INV
        {GX_BM_BLEND,    GX_BL_ONE,         GX_BL_ZERO,        GX_LO_CLEAR}, // BLEND_REPLACE
        {GX_BM_NONE,     GX_BL_ONE,         GX_BL_ONE,         GX_LO_CLEAR}, // BLEND_NONE
        // clang-format on
    };

    GXSetBlendMode(BLEND[blendMode].m_blendMode, BLEND[blendMode].m_srcFactor,
                   BLEND[blendMode].m_dstFactor, BLEND[blendMode].m_op);
}

} // namespace EGG
