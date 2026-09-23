#include <Pack/RPSystem.h>

RP_SINGLETON_IMPL_EX(RPSysQueuedScene);

RPSysQueuedScene::RPSysQueuedScene(EGG::Heap* pHeap) : mpParentHeap(pHeap) {
    mNextSceneID = -1;
}

void RPSysQueuedScene::reset() {
    mNextSceneID = -1;
}

RPSysQueuedScene::~RPSysQueuedScene() {}
