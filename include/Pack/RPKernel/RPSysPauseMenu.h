#ifndef RP_KERNEL_PAUSE_MENU_H
#define RP_KERNEL_PAUSE_MENU_H

#include <nw4r/lyt.h>
#include <Pack/types_pack.h>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class RPSysLayout;
class RPSysLytBounding;
class RPSysLytAnmObj;
class RPSysLytTextBox;

/**
 * @brief Library that handles pause menu layout.
 */

class RPSysPauseMenu {
    virtual ~RPSysPauseMenu();

public:
    void draw();

private:
    RPSysLayout* mLayout; // at 0x4
    RPSysLytAnmObj* mAnmObj_0x04;
    RPSysLytAnmObj* mAnmObj_0x08;
    void* mUNK_0x10;
    nw4r::lyt::Pane* mPane_0x14;
    nw4r::lyt::Pane* mPane_0x18;
    bool mUNK_0x1C;
    bool mUNK_0x1D;
    u8 mPAD_0x1E[2];
    nw4r::lyt::Pane* mPane_0x20;
    RPSysLytBounding* mBounding; // at 0x24
    RPSysLytTextBox* mTextBox; // at 0x28
    bool mUNK_0x2C;
    bool mUNK_0x2D;
    u8 mPAD_0x2E[10];
    bool mUNK_0x38;
    bool mUNK_0x39;
    u8 mPAD_0x3A[26];
    bool mUNK_0x54;
    bool mUNK_0x55;
    u8 mPAD_0x56[26];
    void* mUtlCursor; //! At 0x70. RPUtlLytFrameCursor is not defined yet.
    u8 mPAD_0x74[4];
    bool mUNK_0x78;
    u8 mPAD_0x79[4];
    bool mUNK_0x7D;
    bool mUNK_0x7E;
    bool mUNK_0x7F;
    u8 mPAD_0x80[8];
};

//! @}

#endif
