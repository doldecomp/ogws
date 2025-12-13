#ifndef RP_GRAPHICS_MODEL_MANAGER_H
#define RP_GRAPHICS_MODEL_MANAGER_H
#include <Pack/types_pack.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpDrawPathManager;

/**
 * @brief Model manager
 */
class RPGrpModelManager {
public:
    /**
     * @brief Gets the currently active manager instance
     */
    static RPGrpModelManager* GetCurrent() {
        return spCurrent;
    }

    RPGrpDrawPathManager* GetDrawPathManager(u8 drawScene) const;

private:
    //! Allocator used for model-related allocations
    static RPGrpModelManager* spCurrent;
};

//! @}

#endif
