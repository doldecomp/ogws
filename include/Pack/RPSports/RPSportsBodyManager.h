#ifndef RP_SPORTS_BODY_MANAGER_H
#define RP_SPORTS_BODY_MANAGER_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel.h>

//! @addtogroup rp_sports
//! @{

/**
 * @brief Sports Pack Mii body manager
 */
class RPSportsBodyManager : public IRPSysKokeshiBodyManager {
public:
    /**
     * @brief Constructor
     */
    RPSportsBodyManager();

    /**
     * @brief Destructor
     */
    virtual ~RPSportsBodyManager(); // at 0x2C

    virtual u16 GetFriendClothesStartIndex(); // at 0x8
    virtual u16 GetFriendClothesIndexRange(); // at 0xC

    virtual const char* GetBodyFileName(u16 bodyType,
                                        RFLSex sex); // at 0x10

    virtual u16 GetBodyModelIndex(u16 bodyType, RFLSex sex, u32 height,
                                  u32 build); // at 0x14

    virtual const char* GetClothesFileName(); // at 0x18

    virtual void GetClothesName(u16 clothesType, RFLSex sex,
                                const char** ppNameA,
                                const char** ppNameB); // at 0x1C

    virtual void GetHeadJointMtx(u16 bodyType, RPGrpModel* pBodyModel,
                                 EGG::Matrix34f* pMtx); // at 0x20

    virtual void GetLeftHandJointMtx(u16 bodyType, RPGrpModel* pBodyModel,
                                     EGG::Matrix34f* pMtx); // at 0x24
    virtual void GetRightHandJointMtx(u16 bodyType, RPGrpModel* pBodyModel,
                                      EGG::Matrix34f* pMtx); // at 0x28

private:
    // . . .
};

//! @}

#endif
