#include <Pack/RPGraphics.h>

#include <egg/gfxe.h>

/**
 * @brief Screen hierarchy root
 */
RPGrpScreen RPGrpScreen::sRootScreen;

/**
 * @brief Initializes the screen system
 *
 * @param maxX Screen width limits for all TV modes
 * @param maxY Screen height limits for all TV modes
 */
void RPGrpScreen::Initialize(const u16 maxX[TV_MODE_MAX],
                             const u16 maxY[TV_MODE_MAX]) {

    EGG::Screen::Initialize(maxX, maxY, &sRootScreen);
}

/**
 * @brief Configures the GX rendering state to draw a quad
 */
void RPGrpScreen::BeginDrawQuad() const {
    EGG::DrawGX::BeginDrawScreen(mCanvasMode == CANVASMODE_LU, false, false);
}

/**
 * @brief Draws a colored quad to this screen
 *
 * @param x1 Left point of the quad
 * @param y1 Top point of the quad
 * @param x2 Right point of the quad
 * @param y2 Bottom point of the quad
 * @param color Fill color
 */
void RPGrpScreen::DrawQuad(f32 x1, f32 y1, f32 x2, f32 y2,
                           GXColor color) const {
    nw4r::math::MTX34 mtx;
    CalcMatrixForDrawQuad(&mtx, x1, y1, nw4r::math::FAbs(x2 - x1),
                          nw4r::math::FAbs(y2 - y1));

    EGG::DrawGX::DrawScreen(mtx, color);
}

/**
 * @brief Configures the GX rendering state to draw a textured quad
 *
 * @param alpha Whether to enable the raster alpha channel
 */
void RPGrpScreen::BeginDrawQuadTexture(bool alpha) const {
    EGG::DrawGX::BeginDrawScreen(mCanvasMode == CANVASMODE_LU, true, alpha);
}

/**
 * @brief Draws a textured quad to this screen
 * @details It is assumed the texture has already been loaded to GX_TEXMAP0.
 *
 * @param x1 Left point of the quad
 * @param y1 Top point of the quad
 * @param x2 Right point of the quad
 * @param y2 Bottom point of the quad
 * @param color Material color
 */
void RPGrpScreen::DrawQuadTexture(f32 x1, f32 y1, f32 x2, f32 y2,
                                  GXColor color) const {
    nw4r::math::MTX34 mtx;
    CalcMatrixForDrawQuad(&mtx, x1, y1, nw4r::math::FAbs(x2 - x1),
                          nw4r::math::FAbs(y2 - y1));

    EGG::DrawGX::DrawScreenTexture(mtx, color);
}

/**
 * @brief Draws a textured quad to this screen
 *
 * @param x1 Left point of the quad
 * @param y1 Top point of the quad
 * @param x2 Right point of the quad
 * @param y2 Bottom point of the quad
 * @param rTexture Fill texture
 * @param color Material color
 */
void RPGrpScreen::DrawQuadTexture(f32 x1, f32 y1, f32 x2, f32 y2,
                                  const RPGrpTexture& rTexture,
                                  GXColor color) const {
    GXLoadTexObj(&rTexture.GetTexObj(), GX_TEXMAP0);
    DrawQuadTexture(x1, y1, x2, y2, color);
}

/**
 * @brief Draws a textured quad to this screen
 *
 * @param x1 Left point of the quad
 * @param y1 Top point of the quad
 * @param x2 Right point of the quad
 * @param y2 Bottom point of the quad
 * @param pResTIMG Fill texture
 * @param color Material color
 */
void RPGrpScreen::DrawQuadTexture(f32 x1, f32 y1, f32 x2, f32 y2,
                                  const EGG::ResTIMG* pResTIMG,
                                  GXColor color) const {
    RPGrpTexture texture(pResTIMG);
    DrawQuadTexture(x1, y1, x2, y2, texture, color);
}
