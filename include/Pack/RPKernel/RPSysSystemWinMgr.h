#ifndef RP_KERNEL_SYSTEM_WINDOW_MGR_H
#define RP_KERNEL_SYSTEM_WINDOW_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class RPSysMessage;

/**
 * @brief System window manager
 */
class RPSysSystemWinMgr {
    RP_SINGLETON_DECL_EX(RPSysSystemWinMgr);

public:
    enum E_ALIGN {};

    enum E_BUTTON {
        E_BUTTON_YES,
        E_BUTTON_NO,
    };

    enum E_WINDOW_TYPE {
        E_WINDOW_TYPE_TEXT,
        E_WINDOW_TYPE_ERROR,
    };

    enum E_RESULT {
        RESULT_NONE,
        RESULT_WAIT,
        RESULT_YES,
        RESULT_NO,
        RESULT_4,
        RESULT_5,
        RESULT_CONTINUE,
    };

    enum ESound {};

public:
    void setSystemWindow(E_WINDOW_TYPE type, u32 group, RPSysMessage* pMessage,
                         int argc, ...);

    void setCursors();

    void setDefaultCursor(E_BUTTON button) {
        unkAF = 0;
        unkB0 = button;
        unkAB = 0;
        unkAC = 0;
        unkAD = 0;
        unkAE = 0;
    }

    E_RESULT getResult() {
        return mResult;
    }

private:
    char unk8[0x90 - 0x8];
    E_RESULT mResult; // at 0x90
    char unk94[0xAB - 0x94];
    u8 unkAB;
    u8 unkAC;
    u8 unkAD;
    u8 unkAE;
    u8 unkAF;
    u8 unkB0;
};

//! @}

#endif
