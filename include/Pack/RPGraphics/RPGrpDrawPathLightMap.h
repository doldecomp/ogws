#ifndef RP_GRAPHICS_DRAW_PATH_LIGHT_MAP_H
#define RP_GRAPHICS_DRAW_PATH_LIGHT_MAP_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpDrawPath.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpModel;

/**
 * @brief Light map draw path
 */
class RPGrpDrawPathLightMap : public RPGrpDrawPath {
public:
    void ReplaceModelTexture(u16 index, RPGrpModel* pModel);

    EGG::LightTextureManager* GetLightTextureManager() const {
        return mpLightTextureManager;
    }

private:
    EGG::LightTextureManager* mpLightTextureManager;
};

//! @}

#endif
