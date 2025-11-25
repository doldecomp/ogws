#ifndef RP_KERNEL_KOKESHI_ITERATER_H
#define RP_KERNEL_KOKESHI_ITERATER_H
#include <Pack/types_pack.h>

#include <RVLFaceLib.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Mii data source iterator
 */
class RPSysKokeshiIterater { // @typo
private:
    //! Whether this iterator has been initialized
    BOOL mIsInitialized; // at 0x0
    //! Selected data source
    RFLDataSource mDataSource; // at 0x4
    //! Current database index
    u16 mIndex; // at 0x8

public:
    /**
     * @brief Constructor
     *
     * @param src Mii data source to view
     */
    RPSysKokeshiIterater(RFLDataSource src);

    /**
     * @brief Destructor
     */
    virtual ~RPSysKokeshiIterater(); // at 0x8

    /**
     * @brief Moves the iterator back to the start
     */
    void Reset();

    /**
     * @brief Advances the iterator to the next Mii
     *
     * @return Whether the iterator is valid
     */
    bool Update();

    /**
     * @brief Gets the current database index
     */
    u16 GetIndex() const {
        return mIndex;
    }

private:
    /**
     * @brief Advances the iterator one index
     *
     * @return Whether the iterator is valid
     */
    bool Increment();
};

//! @}

#endif
