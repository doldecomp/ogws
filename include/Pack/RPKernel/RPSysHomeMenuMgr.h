#ifndef RP_KERNEL_HOME_MENU_MANAGER_H
#define RP_KERNEL_HOME_MENU_MANAGER_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief HBM library manager
 */
class RPSysHomeMenuMgr {
    RP_SINGLETON_DECL_EX(RPSysHomeMenuMgr);

public:
    void update();
};

//! @}

#endif
