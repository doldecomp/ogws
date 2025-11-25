#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

#include <cstdarg>

RP_SINGLETON_IMPL(RPSysTextWriter);

/**
 * @brief Constructor
 */
RPSysTextWriter::RPSysTextWriter() {
    nw4r::ut::RomFont* pRomFont =
        RP_GET_INSTANCE(RPSysFontManager)->GetRomFont();

    SetFont(*pRomFont);

    mIsInBegin = false;
}

/**
 * @brief Destructor
 */
RPSysTextWriter::~RPSysTextWriter() {}

/**
 * @brief Resets all text settings
 */
void RPSysTextWriter::Reset() {
    SetAlpha(255);

    EnableFixedWidth(false);
    SetFixedWidth(0.0f);

    SetColorMapping(nw4r::ut::Color::ELEMENT_MIN, nw4r::ut::Color::ELEMENT_MAX);
    SetGradationMode(GRADMODE_NONE);
    SetTextColor(nw4r::ut::Color::ELEMENT_MAX);

    SetScale(1.0f, 1.0f);
    SetCursor(0.0f, 0.0f, 0.0f);

    EnableLinearFilter(true, true);
    SetTabWidth(4);
    SetCharSpace(0.0f);
    SetLineSpace(0.0f);
    SetDrawFlag(0);
}

/**
 * @brief Prints formatted text to the screen at the specified coordinates
 * @details Coordinates use a left-upper origin
 */
void RPSysTextWriter::Printf(f32 x, f32 y, const char* pMsg, ...) {
    std::va_list list;
    va_start(list, pMsg);

    RPGrpScreen* pScreen = RPGrpRenderer::GetCurrentScreen();
    if (pScreen->GetCanvasMode() == RPGrpScreen::CANVASMODE_CC) {
        y = -y;
    }

    SetCursor(x, y);
    VPrintf(pMsg, list);

    va_end(list);
}

/**
 * @brief Prints formatted text to the screen at the specified coordinates
 * @details Coordinates use a center-canvas origin
 */
void RPSysTextWriter::PrintfZeroCenter(f32 x, f32 y, const char* pMsg, ...) {
    std::va_list list;
    va_start(list, pMsg);

    RPGrpScreen* pScreen = RPGrpRenderer::GetCurrentScreen();

    if (pScreen->GetCanvasMode() == RPGrpScreen::CANVASMODE_CC) {
        y = -y;
    }

    switch (pScreen->GetCanvasMode()) {
    case RPGrpScreen::CANVASMODE_CC: {
        x = x * pScreen->GetWidth() / 2.0f;
        y = y * pScreen->GetHeight() / 2.0f;
        break;
    }

    case RPGrpScreen::CANVASMODE_LU: {
        x = (x + 1.0f) * (pScreen->GetWidth() / 2.0f);
        y = (-y + 1.0f) * (pScreen->GetHeight() / 2.0f);
        break;
    }
    }

    SetCursor(x, y);
    VPrintf(pMsg, list);

    va_end(list);
}

/**
 * @brief Sets up a GX context for rendering
 */
void RPSysTextWriter::Begin() {
    mIsInBegin = true;
    SetupGX();

    // Always pass the Z test (draw over everything)
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);

    nw4r::math::MTX34 posMtx;
    nw4r::math::MTX34Identity(&posMtx);

    // Correct for centered canvas mode
    // TODO(kiwi) How exactly does this work?
    if (RPGrpRenderer::GetCurrentScreen()->GetCanvasMode() ==
        RPGrpScreen::CANVASMODE_CC) {

        posMtx._01 = -posMtx._01;
        posMtx._11 = -posMtx._11;
        posMtx._21 = -posMtx._21;
    }

    GXLoadPosMtxImm(posMtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
}

/**
 * @brief Ends the rendering context
 */
void RPSysTextWriter::End() {
    mIsInBegin = false;
}
