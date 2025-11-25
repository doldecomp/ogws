#ifndef RP_GRAPHICS_MODEL_RES_MANAGER_H
#define RP_GRAPHICS_MODEL_RES_MANAGER_H
#include <Pack/types_pack.h>

//! @addtogroup rp_graphics
//! @{

/**
 * @brief Model resource manager
 */
class RPGrpModelResManager {
public:
    /**
     * @brief Gets the currently active manager instance
     */
    static RPGrpModelResManager* GetCurrent() {
        return spCurrent;
    }

    /**
     * @brief Releases the specified resource file
     *
     * @param rd Resource file descriptor
     */
    void Terminate(u16 rd);

private:
    //! Allocator used for model-related allocations
    static RPGrpModelResManager* spCurrent;
};

//! @}

#endif
