#ifndef RP_SYSTEM_QUEUED_SCENE_H
#define RP_SYSTEM_QUEUED_SCENE_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Pack Project Queued Scene
 */
class RPSysQueuedScene {
    RP_SINGLETON_DECL_EX(RPSysQueuedScene);

    /**
     * @brief Resets the queued scene's ID
     */
    void reset();

    inline s32 getSceneID() {
        return mSceneID;
    }
private:
    //! Queued Scene ID
    s32 mSceneID; // at 0x8
};

//! @}

#endif
