#include <Pack/RPKernel.h>

void RPSysPauseMenu::draw() {
    if (!mUNK_0x78) {
        mLayout->draw();
        //! todo(texline): define RPUtlLytFrameCursor
        // mUtlCursor->draw();
    }
}

RPSysPauseMenu::~RPSysPauseMenu() {}
