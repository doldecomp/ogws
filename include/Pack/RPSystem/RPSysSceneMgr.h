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
 * @brief Scene manager
 */
class RPSysSceneMgr : public EGG::SceneManager {
    RP_SINGLETON_DECL_EX(RPSysSceneMgr);

public:
    /**
<<<<<<< HEAD
     * @brief 
     * Gives system status. Indicates if an error has occurred
     */
    enum ApplicationStatus {
        NORMAL_STATUS,
        RESET_STATUS,
        UNK2_STATUS,
        MENU_RETURN_STATUS,
        SHUTTING_DOWN_STATUS
    };
    bool isShutDownReserved() const;
    bool isDvdErrorApplicationEnd() const;
    bool isNormalState();

    RPSysScene* getCurrentSceneRP() const;

    void shutdownSystem(BOOL pBlack);
    BOOL returnToMenu(BOOL pBlack);
    void softReset(BOOL pFade);

private:
    char mPlaceholder[4];
    ApplicationStatus mApplicationStatus;
    EGG::ColorFader* mColorFader;
=======
     * @brief Performs a soft reset
     *
     * @param skipFade Whether to skip the fade to black (for HBM)
     * @return Success
     */
    bool softReset(bool skipFade);
    /**
     * @brief Returns to the system menu
     *
     * @param setBlack Whether to call VISetBlack before exiting
     * @return Success
     */
    bool returnToMenu(bool setBlack);
    /**
     * @brief Shuts down the console
     *
     * @param setBlack Whether to call VISetBlack before exiting
     * @return Success
     */
    bool shutdownSystem(bool setBlack);

    /**
     * @brief Tests whether the manager is operating normally
     */
    bool isNormalState() const;
    /**
     * @brief Tests whether the manager is currently shutting down the system
     */
    bool isShutDownReserved() const;

    /**
     * @brief Disables the guard state and returns to normal operation
     */
    void resetGuard();

    /**
     * @brief Tests whether the manager is currently returning to the menu or
     * shutting down the system
     */
    bool isApplicationEndReserved();
    /**
     * @brief Tests whether the application should end in its current state due
     * to a DVD error
     * @details Any state other than normal operation will result in the
     * application ending.
     */
    bool isDvdErrorApplicationEnd();

    /**
     * @brief Fades out the display and changes to the specified scene
     * @remark Supply -1 as the scene ID to use the current scene ID.
     * @note If you are changing to the current scene ID again, set @p
     * forceChange so the scene is completely teared down.
     *
     * @param id Scene ID
     * @param forceChange Force a full scene change when a re-init would
     * otherwise happen
     * @return Success
     */
    bool changeNextSceneAfterFade(s32 id, bool forceChange);

    /**
     * @name Faders
     * @note The scene manager owns two faders: the "manager" fader (inherited
     * from @ref EGG::SceneManager) and the "scene" fader (@ref mpSceneFader).
     * The manager fader is used for fading between scene transitions, while the
     * scene fader can be controlled at any time by the current scene.
     */
    /**@{*/
    /**
     * @brief Resets the fade duration of both the scene and manager faders
     * @remark The default duration is 20 frames.
     */
    void resetFadeFrame();
    /**
     * @brief Gets the fade duration of the scene fader
     */
    u16 getSceneFadeFrame();
    /**
     * @brief Sets the duration of both the scene and manager faders
     * @note The fade duration cannot be zero.
     *
     * @param frame Fade duration, in frames
     */
    void setFadeFrame(u16 frame);

    /**
     * @brief Resets the fade color of both the scene and manager faders
     * @remark The default color is white with full opacity.
     */
    void resetFadeColor();

    /**
     * @brief Gets the fade color of the manager fader
     */
    nw4r::ut::Color getMgrFadeColor();

    /**
     * @brief Sets the fade color of both faders
     *
     * @param color Fade color
     */
    void setFadeColor(nw4r::ut::Color color);

    /**
     * @brief Sets the fade color of the scene fader
     *
     * @param color Fade color
     */
    void setSceneFadeColor(nw4r::ut::Color color);

    /**
     * @brief Gets the fade status of the scene fader
     */
    EGG::Fader::EStatus getSceneStatus();
    /**
     * @brief Sets the fade status of the scene fader
     *
     * @param status Fade status
     */
    void setSceneStatus(EGG::Fader::EStatus status);

    /**
     * @brief Begins to fade in the manager fader
     */
    void startMgrFadeIn();

    /**
     * @brief Begins to fade in the scene fader
     */
    void startSceneFadeIn();
    /**
     * @brief Begins to fade out the scene fader
     */
    void startSceneFadeOut();

    /**
     * @brief Tests whether the scene is currently fully visible
     */
    bool isDisplay();
    /**
     * @brief Tests whether the scene is currently not visible
     */
    bool isBlank();
    /**
     * @brief Tests whether the scene is currently fading out
     */
    bool isFadeOut();
    /**@}*/

    /**
     * @brief Tests whether all asynchronous tasks have been completed
     * @details The system threads (DVD, NAND, WiiConnect24) must all be idle,
     * and the system must not currently be writing save data to the NAND.
     */
    bool isTaskFinished();
    /**
     * @brief Tests whether the scene is currently permitted to change
     * @details The scene can only change once all tasks have finished and the
     * manager fader is prepared to fade out.
     */
    bool isSceneChangeEnable();

    /**
     * @name Faders
     */
    /**@{*/
    /**
     * @brief Updates the scene fader's state
     */
    void calcSceneFader();
    /**
     * @brief Renders the scene fader's state
     */
    void drawSceneFader();
    /**
     * @brief Renders the manager fader's state
     */
    void drawMgrFader();
    /**@}*/

    /**
     * @brief Updates the scene manager's state
     */
    void updateState();

    RPSysScene* getCurrentSceneRP() const;
>>>>>>> 15d86d66 (type shit..)
};

//! @}

#endif
