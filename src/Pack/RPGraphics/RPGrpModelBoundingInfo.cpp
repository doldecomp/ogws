#include <Pack/RPGraphics.h>

/**
 * @brief Constructor
 *
 * @param flags Bound type flags
 * @param pModel Owner model
 */
RPGrpModelBoundingInfo::RPGrpModelBoundingInfo(u32 flags, RPGrpModel* pModel)
    : EGG::ModelBoundingInfo(flags, pModel->GetModelEx()) {}
