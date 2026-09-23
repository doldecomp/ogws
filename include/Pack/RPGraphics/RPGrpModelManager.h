#ifndef RP_GRAPHICS_MODEL_MANAGER_H
#define RP_GRAPHICS_MODEL_MANAGER_H
#include <Pack/types_pack.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpDrawPathManager;
class RPGrpModelScene;

/**
 * @brief Model manager
 */
class RPGrpModelManager {
public:
    //! Maximum number of model scenes
    static const int MAX_SCENE = 8;

public:
    /**
     * @brief Gets the currently active manager instance
     */
    static RPGrpModelManager* GetCurrent() {
        return spCurrent;
    }

    RPGrpDrawPathManager* GetDrawPathManager(u8 drawScene) const;

    RPGrpModelScene* GetModelScene(int i) {
        return mpModelScenes[i];
    }

private:
    //! Allocator used for model-related allocations
    static RPGrpModelManager* spCurrent;

    //! Model scenes
    RPGrpModelScene* mpModelScenes[MAX_SCENE]; // at 0x4
};

//! @}

#endif
