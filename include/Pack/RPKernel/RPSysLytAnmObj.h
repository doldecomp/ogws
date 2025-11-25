#ifndef RP_KERNEL_LYT_ANM_OBJ_H
#define RP_KERNEL_LYT_ANM_OBJ_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel/RPSysFrameCtrl.h>

#include <nw4r/lyt.h>

//! @addtogroup rp_kernel
//! @{

// TODO(kiwi) Fill out this structure
struct RPSysLytAnmContent {};

/**
 * @brief Layout animation object
 */
class RPSysLytAnmObj {
public:
    /**
     * @brief Constructor
     */
    RPSysLytAnmObj();

    /**
     * @brief Updates the layout animation
     */
    void calc();

    /**
     * @brief Resets the layout animation
     */
    void reset();

    /**
     * @brief Starts playing the animation from the specified frame
     *
     * @param frame Starting frame (-1 to play from the current frame)
     */
    void play(s16 frame);

    /**
     * @brief Initializes the layout animation
     *
     * @param frame Starting frame
     * @param frameNum Number of frames to animate
     * @param playMode Animation policy
     */
    void init(s16 frame, u16 frameNum, RPSysFrameCtrl::EPlayMode playMode);

    /**
     * @brief Stops playing the animation
     */
    void stop() {
        mFrameCtrl.stop();
    }

    /**
     * @brief Gets the number of frames in this animation
     */
    f32 getFrameMax();

    /**
     * @brief Tests whether this animation has finished
     */
    bool isFinished() const {
        return mFrameCtrl.isFinished();
    }

    /**
     * @brief Tests whether this animation has looped at least once
     */
    bool isLooped() const {
        return mFrameCtrl.isLooped();
    }

    /**
     * @brief Sets the animation play policy
     *
     * @param playMode New play policy
     */
    void setPlayMode(RPSysFrameCtrl::EPlayMode playMode) {
        mFrameCtrl.setPlayMode(playMode);
    }

    /**
     * @brief Sets the current animation position
     *
     * @param frame New frame
     */
    void setFrame(f32 frame) {
        mFrameCtrl.setFrame(frame);
    }

    /**
     * @brief Sets the animation update rate
     *
     * @param rate New update rate
     */
    void setRate(f32 rate) {
        mFrameCtrl.setRate(rate);
    }

private:
    /**
     * @brief Animation result flags
     */
    enum EFlag {
        EFlag_Finished = 1 << 0, //!< Non-looping animation has finished
        EFlag_Looped = 1 << 1,   //!< Animation has looped at least once
    };

private:
    //! Animation transform
    nw4r::lyt::AnimTransform* mpAnimTrans; // at 0x0
    //! Animation controller
    RPSysFrameCtrl mFrameCtrl; // at 0x4

    //! Number of animation contents
    u16 mNumAnimContent; // at 0x18
    //! Animation contents
    RPSysLytAnmContent* mpAnimContent; // at 0x1C

    char unk20[0x28 - 0x20];
};

//! @}

#endif
