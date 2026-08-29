#ifndef RP_KERNEL_HOME_MENU_MANAGER_H
#define RP_KERNEL_HOME_MENU_MANAGER_H
#include <Pack/types_pack.h>
#include <Pack/RPSystem/RPSysProjectLocal.h>

#include <Pack/RPSingleton.h>
#include <homebuttonMiniLib.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief HBM library manager
 */
class RPSysHomeMenuMgr {
    RP_SINGLETON_DECL_EX(RPSysHomeMenuMgr);

public:
    void update();

    /**
     * @brief Check if program is exiting/resetting and black out if true
     * 
     * @return BOOL 
     */
    BOOL startBlackOut();

private:
    struct unknownArcStruct {
        void *mArcFile;
        u32 UNK_0x04; // set to 1 if DVD error occurs in function 801A4E8C
        u16 UNK_0x08;
        u16 UNK_0x0A;
    };

    u8 mUNK_0x08; // set to 1 at the end of LoadResource. bool?
    bool mUNK_0x09; // checked in 801A4E8C to make sure error has not occurred
    bool mUNK_0x0A; // set to true if no DVD error and scene change disabled
    bool mBlackOutOk;
    u8 mUNK_0x0C;
    u8 mUNK_0x0D;
    u32 mUNK_0x10;
    u16 mUNK_0x14;
    RPSysProjectLocal* mProjectLocal;
    unknownArcStruct* mARC_0x1C;
    HBMDataInfo *mMenuDataInfo;
    u32 mUNK_0x24;
    u32 mUNK_0x28;
    u32 mUNK_0x2C;
    void* mUNK_0x30;
    void* mSoundCallback;
    u32 mUNK_0x38;
    u32 mUNK_0x3C;
    u32 mUNK_0x40;
    u32 mUNK_0x44; // Seemingly skipped in constructor?
    u32 mUNK_0x48;
    u32 mUNK_0x4C;
    f32 mUNK_0x50; // Set to 1.2 if the console is in PAL 50 Hz mode, otherwise 1.0
    f32 mUNK_0x54;
    f32 mUNK_0x58;
    u32 mUNK_0x5C;
    const HBMControllerData *mHbmControllerData;
    u8 mUNK_0x64[60];
    KPADStatus mKpadStatus;
};

//! @}

#endif
