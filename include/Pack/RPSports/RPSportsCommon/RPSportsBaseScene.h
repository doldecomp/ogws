#ifndef RP_SPORTS_COMMON_BASE_SCENE_H
#define RP_SPORTS_COMMON_BASE_SCENE_H
#include <Pack/types_pack.h>

#include <Pack/RPSystem.h>

//! @addtogroup rp_sports
//! @{

/**
 * @brief Base class for Sports Pack scenes
 */
class RPSportsBaseScene : public RPSysScene {
public:
    virtual void Configure() override;
    virtual void LoadResource() override;
    virtual void Reset() override;
    virtual void Calculate() override;
    virtual void Exit() override;

    virtual void OnConfigure();
    virtual void OnLoadResource();
    virtual void OnReset();
    virtual void OnCalculate();
    virtual void OnUserDraw();
    virtual void OnDebugDraw();
    virtual void OnExit();

    virtual void UserDraw() override;
    virtual void DebugDraw() override;

private:
    char unk44[0x9C - 0x44];
};

//! @}

#endif
