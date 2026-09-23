#ifndef RP_SYSTEM_SCENE_MGR_H
#define RP_SYSTEM_SCENE_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>
#include <Pack/RPSystem/RPSysScene.h>

#include <egg/core.h>

#include <nw4r/ut.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Pack Project scene manager
 */
class RPSysSceneMgr : public EGG::SceneManager {
    RP_SINGLETON_DECL_EX(RPSysSceneMgr);

public:
    /**
     * @brief Updates the state of the current scene
     */
    virtual void calcCurrentScene() override; // at 0x10

    /**
     * @brief Gets the currently active scene as the Pack Project type
     */
    RPSysScene* getCurrentSceneRP() const;

    /**
     * @brief Performs a soft reset
     *
     * @param fromHBM Whether the request came from HBM
     * @return Success
     */
    bool softReset(bool fromHBM);

    /**
     * @brief Returns to the IPL
     *
     * @param fromHBM Whether the request came from HBM
     * @return Success
     */
    bool returnToMenu(bool fromHBM);

    /**
     * @brief Powers off the console
     *
     * @param fromHBM Whether the request came from HBM
     * @return Success
     */
    bool shutdownSystem(bool fromHBM);

    /**
     * @brief Tests whether this manager is operating normally
     */
    bool isNormalState() const;

    /**
     * @brief Tests whether this manager is currently shutting down the system
     */
    bool isShutDownReserved() const;

    /**
     * @brief Tests whether this manager is currently returning to the IPL
     */
    bool getReturnToMenu() const;

    /**
     * @brief Disables the guard state and returns to normal operation
     */
    void resetGuard();

    /**
     * @brief Tests whether this manager is currently exiting the program
     */
    bool isApplicationEndReserved();

    /**
     * @brief Tests whether a DVD error should exit the program
     */
    bool isDvdErrorApplicationEnd();

    /**
     * @brief Requests a scene change after fading out
     * @details A scene id of -1 will select the current scene.
     *
     * @param id New scene ID
     * @param reconfigure Whether to fully reconfigure the scene
     * @return Success
     */
    bool changeNextSceneAfterFade(s32 id, bool reconfigure = false);

    /**
     * @brief Resets the duration of all faders
     */
    void resetFadeFrame();

    /**
     * @brief Gets the duration of the scene fader
     */
    u16 getFadeFrame();

    /**
     * @brief Sets the duration of all faders
     *
     * @param frame Fade duration, in frames
     */
    void setFadeFrame(u16 frame);

    /**
     * @brief Resets the color of all faders
     * @details The default fader color is black.
     */
    void resetFadeColor();

    /**
     * @brief Gets the color of the manager fader
     */
    nw4r::ut::Color getFadeColor();

    /**
     * @brief Sets the color of all faders
     *
     * @param color Fade color
     */
    void setFadeColor(nw4r::ut::Color color);

    /**
     * @brief Sets the color of the scene fader
     *
     * @param color Fade color
     */
    void setSceneFadeColor(nw4r::ut::Color color);

    /**
     * @brief Gets the status of the scene fader
     */
    EGG::Fader::EStatus getSceneStatus();

    /**
     * @brief Sets the status of the scene fader
     *
     * @param status Fade status
     */
    void setSceneStatus(EGG::Fader::EStatus status);

    /**
     * @brief Begins fading in the manager fader
     *
     * @return Success
     */
    bool startMgrFadeIn();

    /**
     * @brief Begins fading in the scene fader
     *
     * @return Success
     */
    bool startSceneFadeIn();

    /**
     * @brief Begins fading out the scene fader
     *
     * @return Success
     */
    bool startSceneFadeOut();

    /**
     * @brief Tests whether the scene is fully visible
     */
    bool isDisplay();

    /**
     * @brief Tests whether the scene is visibly obscured
     */
    bool isBlank();

    /**
     * @brief Tests whether the scene is fading out
     */
    bool isFadeOut();

    /**
     * @brief Tests whether all asynchronous tasks have finished
     */
    bool isTaskFinished();

    /**
     * @brief Tests whether a scene change would be allowed
     */
    bool isSceneChangeEnable();

    /**
     * @brief Updates the state of the scene fader
     *
     * @return Whether the fade has finished
     */
    bool calcSceneFader();

    /**
     * @brief Displays the state of the scene fader
     */
    void drawSceneFader();

    /**
     * @brief Displays the state of the manager fader
     */
    void drawMgrFader();

    /**
     * @brief Updates the state of this manager
     */
    void updateState();

private:
    /**
     * @brief Scene manager state
     */
    enum EState {
        EState_Normal,       //!< Normal operation
        EState_Guard,        //!< Prevents operations during soft reset
        EState_SoftReset,    //!< Perform soft reset
        EState_ReturnToMenu, //!< Return to system menu
        EState_Shutdown      //!< Shutdown the system
    };

    //! The default fade duration, in frames
    static const int DEFAULT_FADE_FRAME = 20;

    //! The default fade color
    static const u32 DEFAULT_FADE_COLOR = nw4r::ut::Color::BLACK;

private:
    //! Manager state
    EState mState; // at 0x30
    //! Fader usable by the current scene
    EGG::ColorFader* mpSceneFader; // at 0x34
};

//! @}

#endif
