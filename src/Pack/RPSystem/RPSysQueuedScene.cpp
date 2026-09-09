#include <RPSystem.h>

RP_SINGLETON_IMPL_EX(RPSysQueuedScene);

RPSysQueuedScene::RPSysQueuedScene(EGG::Heap* pHeap) : mpParentHeap(pHeap) {
    mSceneToLoad = -1;
}

void RPSysQueuedScene::reset() {
    mSceneToLoad = -1;
}

RPSysQueuedScene::~RPSysQueuedScene() {}
