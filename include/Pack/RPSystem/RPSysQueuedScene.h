#ifndef RP_SYSTEM_QUEUED_SCENE_H
#define RP_SYSTEM_QUEUED_SCENE_H

#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>


class RPSysQueuedScene {
    RP_SINGLETON_DECL_EX(RPSysQueuedScene);

public:
    void reset();

    s32 getNextSceneID() const {
        return mNextSceneID;
    }
    void setNextSceneID(s32 id) {
        mNextSceneID = id;
    }

private:
    s32 mNextSceneID; // at 0x8
};

#endif
