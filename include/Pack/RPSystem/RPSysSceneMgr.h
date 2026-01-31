#ifndef RP_SYSTEM_SCENE_MGR_H
#define RP_SYSTEM_SCENE_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>
#include <Pack/RPSystem/RPSysScene.h>

#include <egg/core.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Scene manager
 */
class RPSysSceneMgr : public EGG::SceneManager {
    RP_SINGLETON_DECL(RPSysSceneMgr);

public:
    bool isShutDownReserved() const;

    RPSysScene* getCurrentSceneRP() const;

    void returnToMenu(bool);
};

//! @}

#endif
