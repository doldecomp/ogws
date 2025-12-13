#ifndef RP_SYSTEM_PLAYER_H
#define RP_SYSTEM_PLAYER_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

#include <RVLFaceLib.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Player object
 */
class RPSysPlayer {
public:
    s8 getDataSource() const {
        return mDataSource;
    }

    u16 getIndex() const {
        return mIndex;
    }

private:
    u8 mChannel;           // at 0x0
    s8 mDataSource;        // at 0x1
    u16 mIndex;            // at 0x2
    RFLCreateID mCreateID; // at 0x4
    // . . .
};

//! @}

#endif
