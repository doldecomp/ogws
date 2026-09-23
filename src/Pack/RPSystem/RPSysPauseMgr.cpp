#include <Pack/RPKernel.h>
#include <Pack/RPSingleton.h>
#include <Pack/RPSystem.h>

RP_SINGLETON_IMPL_EX(RPSysPauseMgr);

void RPSysPauseMgr::draw() {
    if (isPause()) {
        mPauseMenu->draw();
    }
}

/**
 * @brief Destructor
 */
RPSysPauseMgr::~RPSysPauseMgr() {
    //TODO(texline): delete mPauseMenu (it does not have a singleton)
}
