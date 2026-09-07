#ifndef RP_SYSTEM_COMMON_OBJECT_H
#define RP_SYSTEM_COMMON_OBJECT_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Encapsulates common object behavior/rendering
 */
class RPSysCommonObject : public IRPGrpDrawObject {
public:
    enum EView {
        EView_2D_Cursor = 29,
        EView_2D_31 = 31,
    };

public:
    /**
     * @brief Constructor
     */
    RPSysCommonObject();

    /**
     * @brief Renders common objects' state
     */
    virtual void UserDraw() override; // at 0xC

    /**
     * @brief Initializes common objects' state
     */
    void init();

    /**
     * @brief Updates common objects' state before the scene gets to update
     */
    void preUpdate();

    /**
     * @brief Updates common objects' state after the scene gets to update
     */
    void postUpdate();
};

//! @}

#endif
