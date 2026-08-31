#ifndef RP_SYSTEM_PAUSE_MGR_H
#define RP_SYSTEM_PAUSE_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Pause menu manager
 */
class RPSysPauseMgr {
    RP_SINGLETON_DECL_EX(RPSysPauseMgr);

public:
    /**
     * @brief Initiates the manager.
     */
    void init();

    void update();

    void draw();

    bool isPause() const {
        return unk8 & 1;
    }

private:
    u32 unk8;
};

//! @}

#endif
