#ifndef RP_KERNEL_CONTROLLER_H
#define RP_KERNEL_CONTROLLER_H
#include <Pack/types_pack.h>

#include <egg/core.h>

#include <revolution/WPAD.h>

//! @addtogroup rp_kernel
//! @{

/******************************************************************************
 *
 * RPSysCoreAddress
 *
 ******************************************************************************/
class RPSysCoreAddress {
public:
    RPSysCoreAddress();

    void reset();
    bool get(s32 chan);
    void set(const u8* pData);

    bool isValid() const;

    u8 operator[](int i) const;
    bool operator==(const RPSysCoreAddress& rOther) const;

private:
    //! Remote address
    u8 mData[WPAD_ADDR_LEN]; // at 0x0
};

/******************************************************************************
 *
 * RPSysCoreController
 *
 ******************************************************************************/
class RPSysCoreController : public EGG::CoreController {
public:
    bool isPrevDpdCtrlEnable();

    const RPSysCoreAddress& getAddress() const {
        return mAddress;
    }

private:
    char unk8FC[0x2BA8 - 0x8FC];
    RPSysCoreAddress mAddress; // at 0x2BA8
};

/******************************************************************************
 *
 * RPSysCoreControllerMgr
 *
 ******************************************************************************/
class RPSysCoreControllerMgr {
public:
    static u32 isDpdCtrlEnable(s32 chan) {
        return sDpdCtrlEnableFlag & (1 << chan);
    }

    static RPSysCoreController* getNthController(int index) {
        EGG::CoreController* pController =
            EGG_GET_INSTANCE(EGG::CoreControllerMgr)->getNthController(index);

        return static_cast<RPSysCoreController*>(pController);
    }

private:
    static u32 sDpdCtrlEnableFlag;
};

//! @}

#endif
