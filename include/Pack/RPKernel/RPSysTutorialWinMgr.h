#ifndef RP_KERNEL_SYS_TUTORIAL_WIN_MGR_H
#define RP_KERNEL_SYS_TUTORIAL_WIN_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Pack Project Tutorial Win Manager
 */
class RPSysTutorialWinMgr {
public:
    RP_SINGLETON_DECL_EX(RPSysTutorialWinMgr);
public:
    /**
     * @brief Initiates the manager.
     */
    void init();

    void calc();

    void draw();
};

//! @}

#endif
