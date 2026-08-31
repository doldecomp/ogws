#ifndef RP_KERNEL_SYS_CURSOR_DRAW_MGR_H
#define RP_KERNEL_SYS_CURSOR_DRAW_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Pack Project Cursor Draw Manager
 */
class RPSysCursorDrawMgr {
public:
    RP_SINGLETON_DECL_EX(RPSysCursorDrawMgr);
public:
    /**
     * @brief Initiates the manager.
     */
    void init();

    void preUpdate();

    void postUpdate();
};

//! @}

#endif
