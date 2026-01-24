#ifndef RP_AUDIO_SND_MOVE_PARAM_H
#define RP_AUDIO_SND_MOVE_PARAM_H
#include <Pack/types_pack.h>

#include <nw4r/snd.h>
#include <nw4r/ut.h>

//! @addtogroup rp_audio
//! @{

/******************************************************************************
 *
 * RPSndMoveValueF32
 *
 ******************************************************************************/

/**
 * @brief Configurable value interpolation
 */
class RPSndMoveValueF32 {
public:
    /**
     * @brief Move value callback
     *
     * @param value Current move value
     * @param pUserData Callback user argument
     */
    typedef void (*Callback)(f32 value, void* pUserData);

public:
    /**
     * @brief Constructor
     */
    RPSndMoveValueF32();

    /**
     * @brief Begins interpolation of this value
     *
     * @param target Interpolation target
     * @param frame Interpolation duration
     */
    void moveValue(f32 target, u32 frame);

    /**
     * @brief Updates the interpolation state
     *
     * @return Whether interpolation is ongoing
     */
    virtual bool update(); // at 0x8

protected:
    //! Interpolation callback
    Callback mpCallback; // at 0x4
    //! Callback user argument
    void* mpUserData; // at 0x8

    //! Remaining frame count
    u32 mFrame; // at 0xC
    //! Move target value
    f32 mTarget; // at 0x10
    //! Current move value
    f32 mValue; // at 0x14
    //! Frame delta value
    f32 mDelta; // at 0x18
};

/******************************************************************************
 *
 * RPSndMoveParamLink
 *
 ******************************************************************************/

/**
 * @brief Move parameter linked-list item
 */
class RPSndMoveParamLink {
public:
    //! Linked-list node
    NW4R_UT_LIST_LINK_DECL(); // at 0x0
};

/******************************************************************************
 *
 * RPSndMoveParam
 *
 ******************************************************************************/

/**
 * @brief Sound parameter interpolation
 */
class RPSndMoveParam : public RPSndMoveParamLink, public RPSndMoveValueF32 {
public:
    /**
     * @brief Move parameter type
     */
    enum ParamCategory {
        ParamCategory_SoundPitch,  //!< Controls pitch of the attached sound
        ParamCategory_SoundLpf,    //!< Controls LPF freq. of the attached sound
        ParamCategory_TrackVolume, //!< Controls volume of the selected track(s)
        ParamCategory_TrackPitch,  //!< Controls pitch of the selected track(s)
    };

public:
    /**
     * @brief Constructor
     *
     * @param category Sound parameter category
     * @param rHandle Sound handle
     */
    RPSndMoveParam(ParamCategory category, nw4r::snd::SoundHandle& rHandle);

    /**
     * @brief Updates the interpolation state
     *
     * @return Whether interpolation is ongoing
     */
    virtual bool update(); // at 0x8

private:
    //! Sound handle
    nw4r::snd::SoundHandle& mrHandle; // at 0x28
    //! Sound parameter category
    ParamCategory mCategory; // at 0x2C
    //! Sequence sound track flags
    u32 mTrackFlags; // at 0x30
};

/******************************************************************************
 *
 * RPSndMoveParamMgr
 *
 ******************************************************************************/

/**
 * @brief Move parameter manager
 */
class RPSndMoveParamMgr {
public:
    /**
     * @brief Updates the state of all move parameters
     */
    void update();

private:
    //! List of all active move parameters
    static nw4r::ut::List sMoveParamList;
};

//! @}

#endif
