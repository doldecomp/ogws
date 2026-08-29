#ifndef RP_SYSTEM_PAUSE_MGR_H
#define RP_SYSTEM_PAUSE_MGR_H

#include <Pack/RPSingleton.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief 
 * Pause manager
 */

class RPSysPauseMgr {
    RP_SINGLETON_DECL_EX(RPSysPauseMgr);

public:
    /**
     * @brief 
     * Draws pause screen. Passes to RPSysPauseMenu
     */
    void draw(void);

private:
    u32 mUNK_0x08;
    u32 mUNK_0x0C;
    f32 mFloats_0x10[0x78]; // TODO(Texline666) What are all these floats for?
    void* mLytPause; // placeholder for RPSysLytPause
};

//! @}

#endif
