#ifndef RP_SYSTEM_SCENE_H
#define RP_SYSTEM_SCENE_H
#include <Pack/types_pack.h>

#include <egg/core.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Pack Project scene
 */
class RPSysScene : public EGG::Scene {
public:
    bool isNandAccessEnable() const;
};

//! @}

#endif
