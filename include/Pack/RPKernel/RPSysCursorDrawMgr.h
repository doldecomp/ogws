#ifndef RP_KERNEL_CURSOR_DRAW_MGR_H
#define RP_KERNEL_CURSOR_DRAW_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics.h>
#include <Pack/RPKernel/IRPSysHostIOSocket.h>
#include <Pack/RPSingleton.h>

#include <egg/core.h>
#include <egg/math.h>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class RPSysEffect;

/**
 * @brief Cursor draw manager
 */
class RPSysCursorDrawMgr : public IRPSysHostIOSocket {
    RP_SINGLETON_DECL_EX(RPSysCursorDrawMgr);

public:
    /**
     * @brief Player slot index
     */
    enum EPlayer {
        EPlayer_P1, //!< Player 1
        EPlayer_P2, //!< Player 2
        EPlayer_P3, //!< Player 3
        EPlayer_P4, //!< Player 4

        EPlayer_Max
    };

    /**
     * @brief DPD cursor type
     */
    enum ECursorType {
        ECursorType_Invalid, //!< DPD flag is invalid
        ECursorType_1,
        ECursorType_2,
    };

public:
    /**
     * @brief Pushes a new DPD cursor configuration to the stack
     */
    void startDpdCheck();

    /**
     * @brief Pops the top DPD cursor configuration from the stack
     */
    void finishDpdCheck();

    /**
     * @brief Creates the active (main player) cursor
     */
    void createActiveCursor();

    /**
     * @brief Fades away the active (main player) cursor
     */
    void fadeActiveCursor();

    /**
     * @brief Gets the screen position of the active (main player) cursor
     */
    const EGG::Vector2f& getActiveCursorPos() const;

    /**
     * @brief Gets the DPD cursor type of the active (main player) cursor
     */
    ECursorType getActiveCursorType() const;

    /**
     * @brief Gets the player index of the active (main player) cursor
     *
     * @return Player slot index, or -1 if no such cursor exists
     */
    s32 getActiveCursorPlayer() const;

    /**
     * @brief Creates the cursor for the specified player
     *
     * @param player Player slot index
     */
    void createPlayerCursor(EPlayer player) DECOMP_DONT_INLINE;

    /**
     * @brief Moves the specified player cursor outside the screen
     *
     * @param player Player slot index
     */
    void setPlayerCursorOutOfScreen(EPlayer player);

    /**
     * @brief Gets the position of the specified player cursor
     *
     * @param player Player slot index
     */
    const EGG::Vector2f& getPlayerCursorPos(EPlayer player) const;

    /**
     * @brief Gets the controller channel used by the specified player cursor
     *
     * @param player Player slot index
     * @return Controller channel, or -1 if no such cursor exists
     */
    s32 getPlayerCursorChannel(EPlayer player) const;

    /**
     * @brief Forces a player cursor to the specified screen position
     *
     * @param rPos New cursor position
     * @param player Player slot index
     * @param clearHorizon Whether to reset the cursor horizon to zero
     */
    void setPlayerCursorPos(const EGG::Vector2f& rPos, EPlayer player,
                            bool clearHorizon);

    /**
     * @brief Clears this manager's state
     */
    void init();

    /**
     * @brief Performs logic that must occur before the scene is updated
     */
    void preUpdate();

    /**
     * @brief Performs logic that must occur after the scene is updated
     */
    void postUpdate();

private:
    /**
     * @brief Cursor flags
     */
    enum {
        EFlag_ActiveCursorEnable,
        EFlag_Player1CursorValid = 4,
        EFlag_Player2CursorValid,
        EFlag_Player3CursorValid,
        EFlag_Player4CursorValid,
        EFlag_ActiveCursorValid,
        EFlag_9,
        EFlag_10,
        EFlag_11,
    };

    //! Capacity of the cursor flag stack
    static const int FLAG_STACK_SIZE = 5;
    //! Default time before hidden cursors re-appear, in frames
    static const u32 HIDE_TIME_MAX = 90;
    //! Default alpha value for disabled cursors
    static const u8 DISABLED_ALPHA = 96;

private:
    /**
     * @brief Pushes the current controller parameter set to the stack
     */
    void stackControllerSetting();

    /**
     * @brief Pops the top controller parameter set from the stack
     */
    void popControllerSetting();

    /**
     * @brief Performs pre-update logic for the active (main player) cursor
     */
    void preUpdateActive();

    /**
     * @brief Performs pre-update logic for player cursors
     */
    void preUpdatePlayer();

    /**
     * @brief Performs post-update logic for the active (main player) cursor
     */
    void postUpdateActive();

    /**
     * @brief Performs post-update logic for player cursors
     */
    void postUpdatePlayer();

    /**
     * @brief Configures the effect draw settings of the specified cursor
     *
     * @param cursor Cursor index
     * @param visible Whether the cursor should be visible
     * @param enabled Whether the cursor should be enabled (not faded)
     */
    void drawCursor(s32 cursor, bool visible, bool enabled);

    /**
     * @brief Updates the specified cursor to match the latest DPD data
     *
     * @param cursor Cursor index
     * @param player Player index
     */
    void updateCursor(s32 cursor, s32 player);

    /**
     * @brief Tests whether the active cursor exists
     */
    bool checkActiveCursorEnable() const {
        return mCursorFlagStack[0].onBit(EFlag_ActiveCursorEnable);
    }

    /**
     * @brief Tests whether any player cursor exists
     */
    bool checkPlayerCursorEnable() {
        return mCursorFlagStack[0] &
               (1 << EFlag_Player1CursorValid | 1 << EFlag_Player2CursorValid |
                1 << EFlag_Player3CursorValid | 1 << EFlag_Player4CursorValid);
    }

    /**
     * @brief Tests whether the active cursor is in a valid state
     */
    bool getActiveCursorValid() const {
        return mCursorFlagStack[0] & 1 << EFlag_ActiveCursorValid;
    }

    /**
     * @brief Tests whether the specified player cursor is in a valid state
     *
     * @param player Player slot index
     */
    bool getPlayerCursorValid(EPlayer player) const {
        return mCursorFlagStack[0].onBit(EFlag_Player1CursorValid + player);
    }

private:
    //! Position way outside of the screen boundaries
    static const EGG::Vector2f OUT_OF_SCREEN_POS;

    //! Cursor flag stack
    EGG::TBitFlag<u32> mCursorFlagStack[FLAG_STACK_SIZE]; // at 0x8

    //! Index of the active (main player) cursor
    s32 mActiveCursorIndex; // at 0x1C
    //! Index of each player cursor
    s32 mCursorIndex[EPlayer_Max]; // at 0x20

    //! DPD cursor type
    ECursorType mCursorType[EPlayer_Max]; // at 0x30
    //! Cursor horizon
    f32 mCursorHorizon[EPlayer_Max]; // at 0x40

    //! Hidden cursor timer
    u32 mCursorHideTime[EPlayer_Max]; // at 0x50
    //! Time before hidden cursors re-appear, in frames
    u32 mCursorHideTimeMax; // at 0x60

    //! Alpha value for disabled cursors
    u8 mDisabledAlpha; // at 0x64

    //! Cursor screen position
    EGG::Vector2f mCursorPos[EPlayer_Max]; // at 0x68

    //! Normal cursor effect
    RPSysEffect* mpEffCursorNormal[EPlayer_Max]; // at 0x88
    //! Blur cursor effect
    RPSysEffect* mpEffCursorBlur[EPlayer_Max]; // at 0x98
    //! Shadow cursor effect
    RPSysEffect* mpEffCursorShadow[EPlayer_Max]; // at 0xA8
};

//! @}

#endif
