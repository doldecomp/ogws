#ifndef RP_GRAPHICS_RENDERER_H
#define RP_GRAPHICS_RENDERER_H
#include <Pack/types_pack.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpScreen;

/**
 * @brief Rendering engine
 */
class RPGrpRenderer {
public:
    /**
     * @brief Gets the currently active manager instance
     */
    static RPGrpRenderer* GetCurrent() {
        return spCurrent;
    }

    /**
     * @brief Gets the screen currently being rendered to
     */
    static RPGrpScreen* GetCurrentScreen() {
        return spCurrentScreen;
    }

private:
    //! Allocator used for model-related allocations
    static RPGrpRenderer* spCurrent;

    //! Screen currently being rendered to
    static RPGrpScreen* spCurrentScreen;
};

//! @}

#endif
