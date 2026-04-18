#include <Pack/RPGraphics.h>

#include <egg/gfxe.h>

/**
 * @brief Constructor
 *
 * @param pScreen Capture source
 * @param format Texture format
 * @param flags Creation flags
 */
RPGrpCaptureTexture::RPGrpCaptureTexture(RPGrpScreen* pScreen, GXTexFmt format,
                                         u32 flags)
    : mEfbFlags(0), mTexFlags(0), mpScreen(pScreen) {

    if (flags & EFlag_MipMap) {
        mTexFlags |= ETexFlag_MipMap;
    }

    bool mipmap = IsMipMapEnable();
    const RPGrpScreen::DataEfb& rEfb = pScreen->GetDataEfb();

    mpCapTexture = new EGG::CapTexture(
        mipmap ? rEfb.vp.width / 2 : rEfb.vp.width,
        mipmap ? rEfb.vp.height / 2 : rEfb.vp.height, format);

    mpCapTexture->configure();
    mpCapTexture->alloc();
}

/**
 * @brief Captures the EFB contents as a texture
 *
 * @param format Texture format override (optional)
 */
void RPGrpCaptureTexture::Capture(int format) {
    if (mEfbFlags & EEfbFlag_ColorUpdate) {
        mpCapTexture->enableColorUpdate();
    } else {
        mpCapTexture->disableColorUpdate();
    }

    if (mEfbFlags & EEfbFlag_AlphaUpdate) {
        mpCapTexture->enableAlphaUpdate();
    } else {
        mpCapTexture->disableAlphaUpdate();
    }

    if (mEfbFlags & EEfbFlag_ZBufferUpdate) {
        mpCapTexture->enableZBufferUpdate();
    } else {
        mpCapTexture->disableZBufferUpdate();
    }

    const RPGrpScreen::DataEfb& rEfb = mpScreen->GetDataEfb();
    mpCapTexture->capture(rEfb.vp.x, rEfb.vp.y, IsMipMapEnable(), format);

    GXInvalidateTexAll();
}
