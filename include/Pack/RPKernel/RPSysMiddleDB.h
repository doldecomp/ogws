#ifndef RP_KERNEL_MIDDLE_DB_H
#define RP_KERNEL_MIDDLE_DB_H
#include <Pack/types_pack.h>

#include <egg/core.h>

#include <RVLFaceLib.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief In-memory Mii database
 */
class RPSysMiddleDB {
public:
    u16 GetStoredNum() const {
        return mStoredNum;
    }

private:
    char unk0[0xA];
    u16 mStoredNum; // at 0xA
};

//! @}

#endif
