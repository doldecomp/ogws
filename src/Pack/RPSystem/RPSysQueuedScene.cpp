#include <RPSystem.h>

RP_SINGLETON_IMPL_EX(RPSysQueuedScene)

/**
 * @brief Constructor
 *
 * @param pHeap Parent heap
 */
RPSysQueuedScene::RPSysQueuedScene(EGG::Heap* pHeap) : mpParentHeap(pHeap) {
    reset();
}

void RPSysQueuedScene::reset() {
    mSceneID = -1;
}

/**
 * @brief Destructor
 */
RPSysQueuedScene::~RPSysQueuedScene() { }
