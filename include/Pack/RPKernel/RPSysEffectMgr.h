#ifndef RP_KERNEL_EFFECT_MGR_H
#define RP_KERNEL_EFFECT_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class RPSysEffectCreator;

/**
 * @brief Effect manager
 */
class RPSysEffectMgr {
    RP_SINGLETON_DECL_EX(RPSysEffectMgr);

public:
    /**
     * @brief Effect scene index
     */
    enum EEffectScene {
        EEffectScene_Scene,  //!< Scene effects
        EEffectScene_Cursor, //!< Cursor effects
        EEffectScene_Work,   //!< Miscellaneous effects

        EEffectScene_Max
    };

public:
    void stopAllEffect();

    void setCreator(RPSysEffectCreator* pCreator, u32 effectScene);
    void resetCreator(RPSysEffectCreator* pCreator);
};

//! @}

#endif
