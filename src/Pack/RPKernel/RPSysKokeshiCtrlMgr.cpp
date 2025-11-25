#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>

#include <egg/core.h>

/**
 * @brief Constructor
 *
 * @param pCallback Controller data callback
 * @param pParentHeap Heap to use as the parent of the controller data heap
 * @param heapSize Size of the controller data heap
 */
RPSysKokeshiCtrlMgr::RPSysKokeshiCtrlMgr(
    IRPSysKokeshiCtrlDataCallback* pCallback, EGG::Heap* pParentHeap,
    u32 heapSize)
    : unk10(NULL) {

    for (u8 i = 0; i < ARRAY_SIZE(mpDataMgrs); i++) {
        mpDataMgrs[i] =
            new RPSysKokeshiCtrlDataMgr(pCallback, pParentHeap, heapSize, i);
    }

    unk10 = this;
    RP_GET_INSTANCE(RPSysKokeshiManager)->SetCtrlMgr(this);
}

/**
 * @brief Destructor
 */
RPSysKokeshiCtrlMgr::~RPSysKokeshiCtrlMgr() {}

/**
 * @brief Notifies the user that all resources will be destroyed
 *
 * @param chan WPAD channel of the data manager
 */
void RPSysKokeshiCtrlMgr::notifyReleaseResource(s32 chan) {
    mpDataMgrs[chan]->notifyReleaseResource();
}

/**
 * @brief Resets the internal state for creating resources
 *
 * @param chan WPAD channel of the data manager
 */
void RPSysKokeshiCtrlMgr::resetResource(s32 chan) {
    mpDataMgrs[chan]->resetResource();
}

/**
 * @brief Tests whether the specified data manager is in an idle state
 *
 * @param chan WPAD channel of the data manager
 */
BOOL RPSysKokeshiCtrlMgr::isIdle(s32 chan) const {
    return mpDataMgrs[chan]->isIdle();
}

/**
 * @brief Tests whether an error occured while loading data
 *
 * @param chan WPAD channel of the data manager
 */
BOOL RPSysKokeshiCtrlMgr::isLoadError(s32 chan) const {
    return mpDataMgrs[chan]->isLoadError();
}

/**
 * @brief Creates resources for the next Mii in each database
 */
void RPSysKokeshiCtrlMgr::createResource() {
    for (u8 i = 0; i < ARRAY_SIZE(mpDataMgrs); i++) {
        mpDataMgrs[i]->createResource();
    }
}

/**
 * @brief Gets the heap used for resource allocation by the specified data
 * manager
 *
 * @param chan WPAD channel of the data manager
 */
EGG::Heap* RPSysKokeshiCtrlMgr::getResourceHeap(s32 chan) {
    return mpDataMgrs[chan]->getHeap();
}

/**
 * @brief Appends a new file to the file resource list
 *
 * @param chan WPAD channel of the data manager
 * @param rd File resource descriptor
 */
void RPSysKokeshiCtrlMgr::appendFile(s32 chan, u16 rd) {
    mpDataMgrs[chan]->appendFile(rd);
}

/**
 * @brief Appends a new model to the model resource list
 *
 * @param chan WPAD channel of the data manager
 * @param pModel New model
 */
void RPSysKokeshiCtrlMgr::appendModel(s32 chan, RPGrpModel* pModel) {
    mpDataMgrs[chan]->appendModel(pModel);
}

/**
 * @brief Updates each data manager's state
 */
void RPSysKokeshiCtrlMgr::calc() {
    for (u8 i = 0; i < ARRAY_SIZE(mpDataMgrs); i++) {
        mpDataMgrs[i]->calc();
    }
}
