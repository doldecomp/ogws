#include <Pack/RPGraphics.h>

#include <egg/gfxe.h>

RPGrpScreen RPGrpScreen::g_default_screen;

void RPGrpScreen::Initialize(const u16 maxX[TV_MODE_MAX],
                             const u16 maxY[TV_MODE_MAX]) {
    EGG::Screen::Initialize(maxX, maxY, &g_default_screen);
}

void RPGrpScreen::BeginDrawQuad() const {
    EGG::DrawGX::BeginDrawScreen(GetCanvasMode() == CANVASMODE_LU, false,
                                 false);
}

void RPGrpScreen::DrawQuad(f32 x, f32 y, f32 width, f32 height, GXColor color) {
    nw4r::math::MTX34 mtx;

    CalcMatrixForDrawQuad(&mtx, x, y, nw4r::math::FAbs(width - x),
                          nw4r::math::FAbs(height - y));
    EGG::DrawGX::DrawDL(EGG::DrawGX::DL_SCREEN, mtx, color);
}

void RPGrpScreen::BeginDrawQuadTexture(bool alpha) const {
    EGG::DrawGX::BeginDrawScreen(GetCanvasMode() == CANVASMODE_LU, true, alpha);
}

void RPGrpScreen::DrawQuadTexture(f32 x, f32 y, f32 width, f32 height,
                                  EGG::ResTIMG* pTextureRes, GXColor color) {
    RPGrpTexture tex = RPGrpTexture(pTextureRes);
    nw4r::math::MTX34 mtx;

    GXColor colorTemp = color;

    GXLoadTexObj(&tex.GetTexObj(), GX_TEXMAP0);
    CalcMatrixForDrawQuad(&mtx, x, y, nw4r::math::FAbs(width - x),
                          nw4r::math::FAbs(height - y));
    EGG::DrawGX::DrawDL(EGG::DrawGX::DL_SCREEN_TEXTURE, mtx, colorTemp);
}
