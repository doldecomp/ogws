#ifndef RP_SPORTS_BOW_SCENE_H
#define RP_SPORTS_BOW_SCENE_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel.h>
#include <Pack/RPSports/RPSportsCommon.h>

//! @addtogroup rp_bow
//! @{

/**
 * @brief Sports Pack Bowling scene
 */
class RPBowScene : public RPSportsBaseScene, public IRPSysHostIOSocket {
private:
    char unkA0[0x13C - 0xA0];
};

//! @}

#endif
