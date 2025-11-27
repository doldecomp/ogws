#ifndef RP_KERNEL_LYT_DYNAMIC_ANM_H
#define RP_KERNEL_LYT_DYNAMIC_ANM_H
#include <Pack/types_pack.h>

#include <egg/core.h>

#include <nw4r/lyt.h>
#include <nw4r/ut.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Layout "dynamic" in/out animation
 * @details Direction and length configurable by layout artists via user data
 */
class RPSysLytDynamicAnm {
public:
    /**
     * @brief Direction in which the pane will animate out
     */
    enum EDirection {
        EDirection_Up,
        EDirection_Down,
        EDirection_Left,
        EDirection_Right,
        EDirection_None,
    };

public:
    /**
     * @brief Constructor
     *
     * @param pParent Parent pane
     * @param direction Animation direction
     * @param frameNum Number of frames to animate
     */
    RPSysLytDynamicAnm(nw4r::lyt::Pane* pParent, EDirection direction,
                       s16 frameNum);

    /**
     * @brief Resets the dynamic animation
     */
    void reset();

    /**
     * @brief Flips the horizontal direction of the animation
     * @note If the animation has a vertical direction, this function will never
     * reverse it.
     *
     * @param reverse Whether to reverse the horizontal direction
     */
    void reverseAnmHDirection(bool reverse);

    /**
     * @brief Starts playing the animation inwards
     * @details The pane will move opposite the animation direction until it
     * is back at its original position.
     *
     * @param frame Starting frame (-1 to play from the ending frame)
     */
    void startAnmIn(s16 frame);

    /**
     * @brief Starts playing the animation outwards
     * @details The pane will move in the animation direction until it is no
     * longer visible.
     *
     * @param frame Starting frame (-1 to play from the ending frame)
     */
    void startAnmOut(s16 frame);

    /**
     * @brief Updates the dynamic animation
     */
    void calc();

    /**
     * @brief Tests whether the pane has finished animating in
     */
    bool isFinishedAnmIn() const {
        return mState == EState_FinishIn;
    }

    /**
     * @brief Tests whether the pane has finished animating out
     */
    bool isFinishedAnmOut() const {
        return mState == EState_FinishOut;
    }

private:
    /**
     * @brief Animation state
     */
    enum EState {
        EState_FinishOut, //!< The pane has finished animating out
        EState_StartIn,   //!< The pane is preparing to animate in
        EState_FinishIn,  //!< The pane has finished animating in
        EState_StartOut,  //!< The pane is preparing to animate out
        EState_None,      //!< The pane is not animating
    };

private:
    //! Current animation state
    s16 mState; // at 0x0
    //! Requested animation state
    s16 mNextState; // at 0x2

    //! Current frame of the animation
    s16 mFrame; // at 0x4
    //! Last frame of the animation
    s16 mEndFrame; // at 0x6
    //! First frame of the animation
    s16 mStartFrame; // at 0x8
    //! Animation direction
    EDirection mDirection; // at 0xC

    //! Parent pane
    nw4r::lyt::Pane* mpParent; // at 0x10
    //! Transparency
    u8 mAlpha; // at 0x14

    //! Initial pane position
    EGG::Vector3f mStartPos; // at 0x18
    //! Current pane position
    EGG::Vector3f mNowPos; // at 0x24

public:
    //! Linked-list node
    NW4R_UT_LIST_LINK_DECL(); // at 0x30

private:
    static const f32* lbl_804BF588;
    static const f32 lbl_804C1750[];
};

//! @}

#endif
