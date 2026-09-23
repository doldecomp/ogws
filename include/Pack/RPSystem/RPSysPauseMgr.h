#ifndef RP_SYSTEM_PAUSE_MGR_H
#define RP_SYSTEM_PAUSE_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel.h>
#include <Pack/RPSingleton.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Pause menu manager
 */
class RPSysPauseMgr {
    RP_SINGLETON_DECL_EX(RPSysPauseMgr);

public:
    void init();
    void draw();
    bool isPause() const {
        return mPause & 1;
    }

private:
    BOOL mPause;
    u32 mUNK_0x0C;
    f32 mFloats_0x10[120];
    RPSysPauseMenu *mPauseMenu;
};

//! @}

#endif
