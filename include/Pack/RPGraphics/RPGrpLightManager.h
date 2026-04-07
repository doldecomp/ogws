#ifndef RP_GRAPHICS_LIGHT_MANAGER_H
#define RP_GRAPHICS_LIGHT_MANAGER_H
#include <Pack/types_pack.h>

#include <RPGraphics/RPGrpModelResManager.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

/**
 * @brief Light manager
 */
class RPGrpLightManager : public EGG::LightManager {
public:
    /**
     * @brief Constructor
     *
     * @param viewNum Maximum number of renderer views
     */
    RPGrpLightManager(u8 viewNum)
        : EGG::LightManager(LIGHT_NUM, AMBIENT_NUM, viewNum) {}

    /**
     * @brief Applies light settings from the specified scene resource
     *
     * @param handle File resource handle
     * @param pName Scene file name
     * @param frame Animation frame (defaults to the first frame)
     * @param lightSetRef Light set reference number (defaults to index 0)
     */
    void LoadScnLight(RPGrpHandle handle, const char* pName, f32 frame = 0.0f,
                      u32 lightSetRef = -1);

private:
    //! Maximum number of light objects
    static const int LIGHT_NUM = 16;

    //! Maximum number of ambient light objects
    static const int AMBIENT_NUM = 8;
};

//! @}

#endif
