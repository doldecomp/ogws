#include <Pack/RPGraphics.h>

#include <egg/gfxe.h>

#include <nw4r/g3d.h>

/**
 * @brief Constructor
 *
 * @param pCpuTexture CPU texture
 */
RPGrpTexture::RPGrpTexture(const EGG::CpuTexture* pCpuTexture) {
    pCpuTexture->getTexObj(&mTexObj);
}

/**
 * @brief Constructor
 *
 * @param pResTIMG Texture image resource
 */
RPGrpTexture::RPGrpTexture(const EGG::ResTIMG* pResTIMG) {
    EGG::GXUtility::getTexObj(&mTexObj, *pResTIMG);
}

/**
 * @brief Constructor
 *
 * @param pCapTexture Capture texture
 */
RPGrpTexture::RPGrpTexture(const RPGrpCaptureTexture* pCapTexture) {
    pCapTexture->GetCapTexture()->getTexObj(&mTexObj);
}

/**
 * @brief Constructor
 *
 * @param handle Resource file handle
 * @param pName Texture name
 */
RPGrpTexture::RPGrpTexture(RPGrpHandle handle, const char* pName) {
    const nw4r::g3d::ResTex tex =
        RPGrpModelResManager::GetCurrent()
            ->GetData<RPGrpModelResManager::Type_ResTex>(handle, pName);

    EGG::GXUtility::getTexObj(&mTexObj, tex, GX_CLAMP, GX_CLAMP, GX_LINEAR,
                              GX_LINEAR);
}
