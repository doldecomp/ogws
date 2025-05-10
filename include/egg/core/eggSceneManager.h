#ifndef EGG_CORE_SCENE_MANAGER_H
#define EGG_CORE_SCENE_MANAGER_H
#include <egg/types_egg.h>

namespace EGG {

// Forward declarations
class Fader;
class Heap;
class SceneCreator;

class SceneManager {
public:
    SceneManager(SceneCreator* pSceneCreator);
    ~SceneManager();

    virtual void calc(); // at 0x8
    virtual void draw(); // at 0xC

    virtual void calcCurrentScene(); // at 0x10
    virtual void calcCurrentFader(); // at 0x14

    virtual void drawCurrentScene(); // at 0x18
    virtual void drawCurrentFader(); // at 0x1C

    virtual void createDefaultFader(); // at 0x20

    bool fadeIn();
    bool fadeOut();

    void reinitCurrentScene();
    bool reinitCurrentSceneAfterFadeOut();

    void changeScene(s32 id);
    bool changeSceneAfterFadeOut(s32 id);

    void changeSiblingScene(s32 id);
    bool changeSiblingSceneAfterFadeOut(s32 id);
    void changeSiblingScene();

    void createScene(s32 id, Scene* pParent);
    void createChildScene(s32 id, Scene* pParent);
    bool createChildSceneAfterFadeOut(s32 id, Scene* pParent);

    bool destroyCurrentSceneNoIncoming(bool destroyRoot);
    bool destroyToSelectSceneID(s32 id);
    bool destroyToSelectSceneIDAfterFadeOut(s32 id);
    void destroyScene(Scene* pScene);

    void createChildSceneCurrent(s32 id) {
        createChildScene(id, getCurrentScene());
    }

    void setCreator(SceneCreator* pSceneCreator) {
        mSceneCreator = pSceneCreator;
    }

    Scene* getCurrentScene() const {
        return mCurrentScene;
    }

    void setNextSceneID(s32 id) {
        mNextSceneID = id;
    }

    s32 getCurrentSceneID() const {
        return mCurrentSceneID;
    }

    bool isStoppingAfterFade() {
        return mAfterFadeType == AFTER_FADE_TYPE_NONE ? true : false;
    }

    static Heap* getHeapForCreateScene_Mem1() {
        return sHeapMem1_ForCreateScene;
    }
    static Heap* getHeapForCreateScene_Mem2() {
        return sHeapMem2_ForCreateScene;
    }
    static Heap* getHeapForCreateScene_Debug() {
        return sHeapDebug_ForCreateScene;
    }

protected:
    enum eAfterFadeType {
        AFTER_FADE_TYPE_CHANGE,
        AFTER_FADE_TYPE_CHANGE_SIBLING,
        AFTER_FADE_TYPE_CREATE_CHILD,
        AFTER_FADE_TYPE_REINIT,
        AFTER_FADE_TYPE_DESTROY_TO_SELECT,
        AFTER_FADE_TYPE_NONE = -1
    };

    enum eRootHeapType { ROOT_HEAP_TYPE_MEM1, ROOT_HEAP_TYPE_MEM2 };

protected:
    void incomingCurrentScene();
    void setupNextSceneID();
    void outgoingParentScene(Scene* pParent);
    Scene* findParentScene(s32 id);

    void setAfterFadeType(eAfterFadeType type) {
        mAfterFadeType = type;
    }
    void resetAfterFadeType() {
        mAfterFadeType = AFTER_FADE_TYPE_NONE;
    }

private:
    SceneCreator* mSceneCreator;   // at 0x4
    char UNK_0x8[0xC - 0x8];       // at 0x8
    Scene* mCurrentScene;          // at 0xC
    Scene* mParentScene;           // at 0x10
    s32 mNextSceneID;              // at 0x14
    s32 mCurrentSceneID;           // at 0x18
    s32 mPreviousSceneID;          // at 0x1C
    eAfterFadeType mAfterFadeType; // at 0x20
    Fader* mCurrentFader;          // at 0x24
    eRootHeapType mRootHeapType;   // at 0x28

    static u16 sHeapOptionFlg;

    static Heap* sHeapMem1_ForCreateScene;
    static Heap* sHeapMem2_ForCreateScene;
    static Heap* sHeapDebug_ForCreateScene;
};

} // namespace EGG

#endif
