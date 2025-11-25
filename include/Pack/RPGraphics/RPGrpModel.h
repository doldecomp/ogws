#ifndef RP_GRAPHICS_MODEL_H
#define RP_GRAPHICS_MODEL_H
#include <Pack/types_pack.h>

#include <egg/core.h>

//! @addtogroup rp_graphics
//! @{

/**
 * @brief Base class for model implementations
 */
class RPGrpModel {
public:
    /**
     * @brief Gets the allocator used for model-related allocations
     */
    static EGG::Allocator* GetAllocator() {
        return spAllocator;
    }
    /**
     * @brief Sets the allocator used for model-related allocations
     *
     * @param pAllocator New allocator
     */
    static void SetAllocator(EGG::Allocator* pAllocator) {
        spAllocator = pAllocator;
    }

    /**
     * @brief Removes this model from the global list
     */
    void RemoveGenList();

private:
    //! Allocator used for model-related allocations
    static EGG::Allocator* spAllocator;
};

//! @}

#endif
