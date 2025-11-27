#include <Pack/RPKernel.h>

#include <revolution/GX.h>

/**
 * @brief Applies the specified player material color to the window frame
 * @details The color is applied to TEV color register 1
 *
 * @param idx Player index
 * @param content Whether to also apply the color to the content
 */
void RPSysLytWindow::applyPlayerColor(u32 idx, bool content) {
    const GXColor& rColor = RPSysLayout::getPlayerColor(idx);
    GXColorS10 tevColor = {rColor.r, rColor.g, rColor.b, rColor.a};

    for (u32 i = 0; i < mFrameNum; i++) {
        GetFrameMaterial(i)->SetTevColor(nw4r::lyt::TEVCOLOR_REG1, tevColor);
    }

    if (content) {
        GetContentMaterial()->SetTevColor(nw4r::lyt::TEVCOLOR_REG1, tevColor);
    }
}

/**
 * @brief Applies the CPU player material color to the window frame
 * @details The color is applied to TEV color register 1
 *
 * @param content Whether to also apply the color to the content
 */
void RPSysLytWindow::applyCpuColor(bool content) {
    const GXColor& rColor = RPSysLayout::getCpuColor();
    GXColorS10 tevColor = {rColor.r, rColor.g, rColor.b, rColor.a};

    for (u32 i = 0; i < mFrameNum; i++) {
        GetFrameMaterial(i)->SetTevColor(nw4r::lyt::TEVCOLOR_REG1, tevColor);
    }

    if (content) {
        GetContentMaterial()->SetTevColor(nw4r::lyt::TEVCOLOR_REG1, tevColor);
    }
}
