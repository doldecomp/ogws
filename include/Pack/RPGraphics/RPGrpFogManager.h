#ifndef RP_GRAPHICS_FOG_MANAGER_H
#define RP_GRAPHICS_FOG_MANAGER_H
#include <Pack/types_pack.h>

#include <RPGraphics/RPGrpModelResManager.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

/**
 * @brief Fog manager
 */
class RPGrpFogManager : public EGG::FogManager {
public:
    /**
     * @brief Applies fog settings from the specified scene resource
     *
     * @param handle File resource handle
     * @param pName Scene file name
     * @param frame Animation frame (defaults to the first frame)
     */
    void LoadScnFog(RPGrpHandle handle, const char* pName, f32 frame = 0.0f);
};

//! @}

#endif
