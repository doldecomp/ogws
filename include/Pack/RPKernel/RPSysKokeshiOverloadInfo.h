#ifndef RP_KERNEL_KOKESHI_OVERLOAD_INFO_H
#define RP_KERNEL_KOKESHI_OVERLOAD_INFO_H
#include <Pack/types_pack.h>

#include <RVLFaceLib.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Mii generation overload parameters
 */
class RPSysKokeshiOverloadInfo {
private:
    //! The type of clothes to wear
    u16 mClothesType; // at 0x0

public:
    /**
     * @brief Constructor
     */
    RPSysKokeshiOverloadInfo();

    /**
     * @brief Destructor
     */
    virtual ~RPSysKokeshiOverloadInfo(); // at 0x8

    /**
     * @brief Gets the type of clothes to wear
     */
    u16 GetClothesType() const {
        return mClothesType;
    }

    /**
     * @brief Sets the type of clothes to wear
     *
     * @param type Clothes type
     */
    void SetClothesType(u16 clothesType) {
        mClothesType = clothesType;
    }
};

//! @}

#endif
