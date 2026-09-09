#ifndef RP_SYSTEM_QUEUED_SCENE_H
#define RP_SYSTEM_QUEUED_SCENE_H

#include <RPSingleton.h>

class RPSysQueuedScene {
    RP_SINGLETON_DECL_EX(RPSysQueuedScene);

public:
    void reset();

private:
    s32 mSceneToLoad; // at 0x8
};

#endif
