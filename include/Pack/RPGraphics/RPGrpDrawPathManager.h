#ifndef RP_GRAPHICS_DRAW_PATH_MANAGER_H
#define RP_GRAPHICS_DRAW_PATH_MANAGER_H
#include <Pack/types_pack.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpDrawPathLightMap;

/**
 * @brief Draw path manager
 */
class RPGrpDrawPathManager : public EGG::IScnProc {
public:
    RPGrpDrawPathLightMap* GetDrawPathLightMap() const {
        return mpDrawPathLightMap;
    }

private:
    char unkC[0x18 - 0xC];
    RPGrpDrawPathLightMap* mpDrawPathLightMap; // at 0x18
};

//! @}

#endif
