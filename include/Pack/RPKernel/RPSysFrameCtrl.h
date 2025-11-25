#ifndef RP_KERNEL_FRAME_CTRL_H
#define RP_KERNEL_FRAME_CTRL_H
#include <Pack/types_pack.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Frame animation controller
 */
class RPSysFrameCtrl {
public:
    /**
     * @brief Animation play policy
     */
    enum EPlayMode {
        EPlayMode_OneTime, //!< Animation plays once
        EPlayMode_Reset,   //!< Animation plays once, then resets to the start
        EPlayMode_Loop,    //!< Animation loops indefinitely
    };

    /**
     * @brief Initializes the animation state
     *
     * @param frameNum Number of frames to animate
     */
    void init(u16 frameNum);

    /**
     * @brief Updates the animation state
     */
    void update();

private:
    /**
     * @brief Animation result flags
     */
    enum EFlag {
        EFlag_Finished = 1 << 0, //!< Non-looping animation has finished
        EFlag_Looped = 1 << 1,   //!< Animation has looped at least once
    };

private:
    //! Animation play policy
    u8 mPlayMode; // at 0x0
    //! Animation result flags
    u8 mFlags; // at 0x1
    //! Whether animation is enabled
    s16 mIsEnabled; // at 0x2

    //! First frame of the animation
    s16 mStartFrame; // at 0x4
    //! Last frame of the animation
    s16 mEndFrame; // at 0x6
    //! Offset to apply when looping
    s16 mLoopFrame; // at 0x8

    //! Animation update speed
    f32 mUpdateRate; // at 0xC
    //! Current animation position
    f32 mFrame; // at 0x10
};

//! @}

#endif
