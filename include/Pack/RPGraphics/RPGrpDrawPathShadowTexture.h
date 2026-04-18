#ifndef RP_GRAPHICS_DRAW_PATH_SHADOW_TEXTURE_H
#define RP_GRAPHICS_DRAW_PATH_SHADOW_TEXTURE_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpDrawPath.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpShadowTexture;

/**
 * @brief Shadow texture draw path
 */
class RPGrpDrawPathShadowTexture : public RPGrpDrawPath {
public:
    /**
     * @brief Constructor
     *
     * @param pRenderer Scene renderer
     */
    RPGrpDrawPathShadowTexture(EGG::ScnRenderer* pRenderer);

    /**
     * @brief Inserts a new shadow texture
     *
     * @param idx Texture index
     * @param pTexture Shadow texture
     */
    void SetTexture(u16 idx, RPGrpShadowTexture* pTexture);

    /**
     * @brief Appends a new shadow texture
     *
     * @param pTexture Shadow texture
     */
    void SetTexture(RPGrpShadowTexture* pTexture);

    /**
     * @brief Enables this draw path
     */
    virtual void On() override { // at 0xC
        mpShadowTextureManager->SetEnable(true);
    }

    /**
     * @brief Disables this draw path
     */
    virtual void Off() override { // at 0x10
        mpShadowTextureManager->SetEnable(false);
    }

    /**
     * @brief Tests whether this draw path is enabled
     */
    virtual bool IsEnable() const override { // at 0x10
        return mpShadowTextureManager->IsEnable();
    }

private:
    //! Shadow texture manager
    EGG::ShadowTextureManager* mpShadowTextureManager; // at 0xC
};

//! @}

#endif
