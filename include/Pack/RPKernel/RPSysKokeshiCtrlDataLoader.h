#ifndef RP_KERNEL_KOKESHI_CTRL_DATA_LOADER_H
#define RP_KERNEL_KOKESHI_CTRL_DATA_LOADER_H
#include <Pack/types_pack.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Controller Mii data loader
 */
class RPSysKokeshiCtrlDataLoader {
private:
    /**
     * @brief Data loading state
     */
    enum ELoadState {
        ELoadState_Start,  //!< Begin request
        ELoadState_Wait,   //!< Wait for RFL
        ELoadState_Finish, //!< Request complete
    };

private:
    //! Selected WPAD channel
    s32 mChannel; // at 0x0
    //! Current load state
    ELoadState mLoadState; // at 0x4

public:
    /**
     * @brief Constructor
     *
     * @param chan WPAD channel to use
     */
    explicit RPSysKokeshiCtrlDataLoader(s32 chan);

    /**
     * @brief Destructor
     */
    virtual ~RPSysKokeshiCtrlDataLoader(); // at 0x8

    /**
     * @brief Tests whether an error occurred while loading data
     */
    BOOL isError() const;

    /**
     * @brief Begins loading Mii data from the controller
     */
    void load();

    /**
     * @brief Tests whether the loader is in an idle state
     */
    BOOL isIdle() const;

    /**
     * @brief Updates the loader state
     */
    void calc();

    /**
     * @brief Gets the WPAD channel this loader is using
     */
    s32 getChannel() const {
        return mChannel;
    }
};

//! @}

#endif
