// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>
#include <egg/prim.h>

#include <revolution/GX.h>

namespace EGG {

u16 SceneManager::sHeapOptionFlg = 0;

Heap* SceneManager::sHeapMem1_ForCreateScene = NULL;
Heap* SceneManager::sHeapMem2_ForCreateScene = NULL;
Heap* SceneManager::sHeapDebug_ForCreateScene = NULL;

SceneManager::SceneManager(SceneCreator* pSceneCreator) {
    mSceneCreator = pSceneCreator;
    mCurrentScene = NULL;
    mNextSceneID = mCurrentSceneID = mPreviousSceneID = -1;
    mAfterFadeType = AFTER_FADE_TYPE_NONE;
    mCurrentFader = NULL;
    mRootHeapType = ROOT_HEAP_TYPE_MEM2;

    createDefaultFader();
#line 60
    EGG_ASSERT(mCurrentFader);
}

SceneManager::~SceneManager() {}

bool SceneManager::fadeIn() {
#line 77
    EGG_ASSERT(mCurrentFader);

    return mCurrentFader->fadeIn();
}

bool SceneManager::fadeOut() {
#line 87
    EGG_ASSERT(mCurrentFader);

    return mCurrentFader->fadeOut();
}

void SceneManager::calc() {
    calcCurrentScene();
    calcCurrentFader();
}

void SceneManager::draw() {
    drawCurrentScene();
    drawCurrentFader();
}

void SceneManager::reinitCurrentScene() {
    if (mCurrentScene != NULL) {
        mCurrentScene->reinit();
    }
}

bool SceneManager::reinitCurrentSceneAfterFadeOut() {
    bool success = false;

    if (isStoppingAfterFade() && fadeOut()) {
        setAfterFadeType(AFTER_FADE_TYPE_REINIT);
        success = true;
    }

    return success;
}

void SceneManager::changeScene(s32 id) {
    while (mCurrentScene != NULL) {
        destroyCurrentSceneNoIncoming(true);
    }

    changeSiblingScene(id);
}

bool SceneManager::changeSceneAfterFadeOut(s32 id) {
    bool success = false;

    if (isStoppingAfterFade() && fadeOut()) {
        setNextSceneID(id);
        setAfterFadeType(AFTER_FADE_TYPE_CHANGE);
        success = true;
    }

    return success;
}

void SceneManager::changeSiblingScene(s32 id) {
    setNextSceneID(id);
    changeSiblingScene();
}

bool SceneManager::changeSiblingSceneAfterFadeOut(s32 id) {
    bool success = false;

    if (isStoppingAfterFade() && fadeOut()) {
        setNextSceneID(id);
        setAfterFadeType(AFTER_FADE_TYPE_CHANGE_SIBLING);
        success = true;
    }

    return success;
}

void SceneManager::changeSiblingScene() {
    Scene* pParent = NULL;
    if (mCurrentScene != NULL) {
        pParent = mCurrentScene->getParentScene();
    }

    if (mCurrentScene != NULL) {
        destroyScene(mCurrentScene);
        mCurrentScene = NULL;
    }

    s32 nextID = mNextSceneID;
    setupNextSceneID();
    createScene(nextID, pParent);
}

void SceneManager::createScene(s32 id, Scene* pParent) {
    BOOL locked;
    Heap* pParentHeap_Mem1;
    Heap* pParentHeap_Mem2;
    Heap* pParentHeap_Debug;

    if (pParent != NULL) {
        pParentHeap_Mem1 = pParent->getHeap_Mem1();
        pParentHeap_Mem2 = pParent->getHeap_Mem2();
        pParentHeap_Debug = pParent->getHeap_Debug();
    } else {
        pParentHeap_Mem1 = BaseSystem::getRootHeapMem1();
        pParentHeap_Mem2 = BaseSystem::getRootHeapMem2();
        pParentHeap_Debug = BaseSystem::getRootHeapDebug();
    }

    Heap* pParentHeap = mRootHeapType == ROOT_HEAP_TYPE_MEM1 ? pParentHeap_Mem1
                                                             : pParentHeap_Mem2;

#line 267
    EGG_ASSERT(pParentHeap_Mem1 && pParentHeap_Mem2);

    locked = pParentHeap->tstDisableAllocation() ? TRUE : FALSE;

    if (locked) {
        pParentHeap->enableAllocation();
    }

    ExpHeap* pNewHeap = ExpHeap::create(-1, pParentHeap, sHeapOptionFlg);

    ExpHeap* pNewHeap_Mem1;
    ExpHeap* pNewHeap_Mem2;
    ExpHeap* pNewHeap_Debug = NULL;

    if (pParentHeap == pParentHeap_Mem2) {
        pNewHeap_Mem1 = ExpHeap::create(-1, pParentHeap_Mem1, sHeapOptionFlg);
        pNewHeap_Mem2 = pNewHeap;
    } else {
        pNewHeap_Mem2 = ExpHeap::create(-1, pParentHeap_Mem2, sHeapOptionFlg);
        pNewHeap_Mem1 = pNewHeap;
    }

    if (pParentHeap_Debug != NULL) {
        pNewHeap_Debug = ExpHeap::create(-1, pParentHeap_Debug, sHeapOptionFlg);
    }

    sHeapMem1_ForCreateScene = pNewHeap_Mem1;
    sHeapMem2_ForCreateScene = pNewHeap_Mem2;
    sHeapDebug_ForCreateScene = pNewHeap_Debug;

#line 299
    EGG_ASSERT(pNewHeap && pNewHeap_Mem1 && pNewHeap_Mem2);

    if (locked) {
        pParentHeap->disableAllocation();
    }

    pNewHeap->becomeCurrentHeap();

#line 311
    EGG_ASSERT(mSceneCreator);
    Scene* pNewScene = mSceneCreator->create(id);
    EGG_ASSERT(pNewScene);

    if (pParent != NULL) {
        pParent->setChildScene(pNewScene);
    }

    mCurrentScene = pNewScene;

    pNewScene->setSceneID(id);
    pNewScene->setParentScene(pParent);
    pNewScene->setSceneMgr(this);
    pNewScene->enter();
}

void SceneManager::createChildScene(s32 id, Scene* pParent) {
    outgoingParentScene(pParent);

    setNextSceneID(id);
    setupNextSceneID();

    createScene(id, pParent);
}

bool SceneManager::createChildSceneAfterFadeOut(s32 id, Scene* pParent) {
    bool success = false;

    if (isStoppingAfterFade()) {
#line 360
        EGG_ASSERT(pParent);

        if (fadeOut()) {
            success = true;

            setNextSceneID(id);
            mParentScene = pParent;
            setAfterFadeType(AFTER_FADE_TYPE_CREATE_CHILD);
        }
    }

    return success;
}

bool SceneManager::destroyCurrentSceneNoIncoming(bool destroyRoot) {
    bool success = false;

    if (mCurrentScene != NULL) {
        Scene* pParent = mCurrentScene->getParentScene();

        if (pParent != NULL) {
            success = true;

            destroyScene(pParent->getChildScene());
            setNextSceneID(pParent->getSceneID());
            setupNextSceneID();
        } else if (destroyRoot) {
            destroyScene(mCurrentScene);
            setNextSceneID(-1);
            setupNextSceneID();
        }
    }

    return success;
}

bool SceneManager::destroyToSelectSceneID(s32 id) {
    bool success = false;
    Scene* pParent = findParentScene(id);

    if (pParent != NULL) {
        success = true;

        while (pParent->getSceneID() != getCurrentSceneID()) {
            destroyCurrentSceneNoIncoming(false);
        }

        incomingCurrentScene();
    }

    return success;
}

bool SceneManager::destroyToSelectSceneIDAfterFadeOut(s32 id) {
    bool success = false;

    if (isStoppingAfterFade() && fadeOut() && findParentScene(id) != NULL) {
        success = true;

        setNextSceneID(id);
        setAfterFadeType(AFTER_FADE_TYPE_DESTROY_TO_SELECT);
    }

    return success;
}

void SceneManager::destroyScene(Scene* pScene) {
#line 490
    EGG_ASSERT(pScene);

    pScene->exit();

    Scene* pChild = pScene->getChildScene();
    if (pChild != NULL) {
        destroyScene(pChild);
    }

    GXFlush();
    GXDrawDone();

    Scene* pParent = pScene->getParentScene();

#line 509
    EGG_ASSERT(mSceneCreator);
    mSceneCreator->destroy(pScene->getSceneID());
    mCurrentScene = NULL;

    if (pParent != NULL) {
        pParent->setChildScene(NULL);
        mCurrentScene = pParent;
    }

    if (pScene->getHeap_Debug() != NULL) {
#line 523
        EGG_ASSERT(pScene->getHeap() != pScene->getHeap_Debug());
        pScene->getHeap_Debug()->destroy();
    }

    if (pScene->getHeap_Mem1() == pScene->getHeap()) {
        pScene->getHeap_Mem2()->destroy();
        pScene->getHeap_Mem1()->destroy();
    } else if (pScene->getHeap_Mem2() == pScene->getHeap()) {
        pScene->getHeap_Mem1()->destroy();
        pScene->getHeap_Mem2()->destroy();
    } else {
#line 538
        EGG_ASSERT(0);
    }

    Heap* pParentHeap;
    if (pParent != NULL) {
        pParentHeap = pParent->getHeap();
    } else {
        pParentHeap = mRootHeapType == ROOT_HEAP_TYPE_MEM1
                          ? BaseSystem::getRootHeapMem1()
                          : BaseSystem::getRootHeapMem2();
    }

#line 551
    EGG_ASSERT(pParentHeap != NULL);
    pParentHeap->becomeCurrentHeap();
}

void SceneManager::incomingCurrentScene() {
    if (mCurrentScene != NULL) {
        mCurrentScene->incoming_childDestroy();
    }
}

void SceneManager::calcCurrentScene() {
    if (mCurrentScene != NULL) {
        mCurrentScene->calc();
    }
}

void SceneManager::calcCurrentFader() {
    if (mCurrentFader == NULL) {
        return;
    }

    if (!mCurrentFader->calc()) {
        return;
    }

    switch (mAfterFadeType) {
    case AFTER_FADE_TYPE_CHANGE: {
        changeScene(mNextSceneID);
        break;
    }

    case AFTER_FADE_TYPE_CHANGE_SIBLING: {
        changeSiblingScene(mNextSceneID);
        break;
    }

    case AFTER_FADE_TYPE_CREATE_CHILD: {
        outgoingParentScene(mParentScene);
        setupNextSceneID();
        createScene(mCurrentSceneID, mParentScene);
        break;
    }

    case AFTER_FADE_TYPE_DESTROY_TO_SELECT: {
        destroyToSelectSceneID(mNextSceneID);
        break;
    }

    case AFTER_FADE_TYPE_REINIT: {
        reinitCurrentScene();
        break;
    }

    default: {
        break;
    }
    }

    resetAfterFadeType();
}

void SceneManager::drawCurrentScene() {
    if (mCurrentScene == NULL) {
        return;
    }

    mCurrentScene->draw();
    BaseSystem::getDisplay()->setBlack(false);
}

void SceneManager::drawCurrentFader() {
    if (mCurrentFader != NULL) {
        mCurrentFader->draw();
    }
}

void SceneManager::createDefaultFader() {
    mCurrentFader = new ColorFader(0.0f, 0.0f, 640.0f, 480.0f);
}

void SceneManager::setupNextSceneID() {
    mPreviousSceneID = mCurrentSceneID;
    mCurrentSceneID = mNextSceneID;
    mNextSceneID = -1;
}

void SceneManager::outgoingParentScene(Scene* pParent) {
#line 701
    EGG_ASSERT(pParent);

#line 704
    EGG_ASSERT(pParent->getChildScene() == NULL);

    pParent->outgoing_childCreate();
}

Scene* SceneManager::findParentScene(s32 id) {
    bool found = false;
    Scene* pScene = getCurrentScene()->getParentScene();

    while (pScene != NULL) {
        if (id == pScene->getSceneID()) {
            found = true;
            break;
        }

        pScene = pScene->getParentScene();
    }

    return found ? pScene : NULL;
}

} // namespace EGG
