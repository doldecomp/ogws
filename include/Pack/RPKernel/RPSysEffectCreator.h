#ifndef RP_KERNEL_EFFECT_CREATOR_H
#define RP_KERNEL_EFFECT_CREATOR_H
#include <Pack/types_pack.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Effect creator
 */
class RPSysEffectCreator {
public:
    /**
     * @brief Constructor
     *
     * @param effectScene Effect scene index
     */
    RPSysEffectCreator(u32 effectScene);

    /**
     * @brief Destructor
     */
    virtual ~RPSysEffectCreator(); // at 0x8

private:
    char unk4[0x44 - 0x4];
};

//! @}

#endif
