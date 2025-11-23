// TODO(kiwi) REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>
#include <egg/prim.h>

namespace EGG {

Scene::Scene() {
    mHeap = Heap::getCurrentHeap();
#line 32
    EGG_ASSERT(mHeap != NULL);

    mHeap_Mem1 = SceneManager::getHeapForCreateScene_Mem1();
    mHeap_Mem2 = SceneManager::getHeapForCreateScene_Mem2();
    mHeap_Debug = SceneManager::getHeapForCreateScene_Debug();

    mParentScene = NULL;
    mChildScene = NULL;

    mSceneID = -1;
    mSceneMgr = NULL;
}

Scene::~Scene() {}

} // namespace EGG
