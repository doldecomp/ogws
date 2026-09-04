#ifndef RP_KERNEL_EFFECT_DEFINE_H
#define RP_KERNEL_EFFECT_DEFINE_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel/RPSysEffectCreator.h>
#include <Pack/RPKernel/RPSysEffectMgr.h>

//! @addtogroup rp_kernel
//! @{

namespace RPSysEffectDefine {

/**
 * @brief Effect userdata flags
 */
enum EUserFlag {
    EUserFlag_0 = 1 << 0,

    //! Effect supports slow motion
    EUserFlag_SlowSystem = 1 << 14,

    EUserFlag_15 = 1 << 15,
};

/**
 * @brief Number of effect systems (standard + slow)
 */
static const u32 MAX_SYSTEM = 2;

/**
 * @brief Maximum effect system group ID
 */
static const u32 MAX_GROUP_ID = RPSysEffectMgr::EDrawGroup_Max * MAX_SYSTEM *
                                RPSysEffectMgr::EDrawScene_Max;

} // namespace RPSysEffectDefine

//! @}

#endif
