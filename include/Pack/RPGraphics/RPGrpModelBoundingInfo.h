#ifndef RP_GRAPHICS_MODEL_BOUNDING_INFO_H
#define RP_GRAPHICS_MODEL_BOUNDING_INFO_H
#include <Pack/types_pack.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpModel;

/**
 * @brief AABB and spherical model bounds
 */
class RPGrpModelBoundingInfo : public EGG::ModelBoundingInfo {
public:
    /**
     * @brief Constructor
     *
     * @param flags Bound type flags
     * @param pModel Owner model
     */
    RPGrpModelBoundingInfo(u32 flags, RPGrpModel* pModel);

    /**
     * @brief Destructor
     */
    virtual ~RPGrpModelBoundingInfo() {} // at 0x8
};

//! @}

#endif
