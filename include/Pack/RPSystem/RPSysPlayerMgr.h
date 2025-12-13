#ifndef RP_SYSTEM_PLAYER_MGR_H
#define RP_SYSTEM_PLAYER_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>
#include <Pack/RPSystem/RPSysPlayer.h>

#include <egg/core.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Player manager
 */
class RPSysPlayerMgr {
    RP_SINGLETON_DECL_EX(RPSysPlayerMgr);

public:
    s32 getPlayerNum() const {
        return mPlayerNum;
    }

    const RPSysPlayer& getPlayer(s32 idx) const;

private:
    s32 mPlayerNum; // at 0x0
    s32 mRemoteNum; // at 0x4
};

//! @}

#endif
