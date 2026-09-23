#ifndef RP_SYSTEM_SCENE_H
#define RP_SYSTEM_SCENE_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>

#include <egg/core.h>

//! @addtogroup rp_system
//! @{

// Forward declarations
class RPSysCommonObject;

/**
 * @brief Pack Project scene
 */
class RPSysScene : public EGG::Scene, public IRPGrpDrawObject {
    friend class RPSysSceneCreator;

public:
    struct UnkStruct {
        u32 unk0;
        UnkStruct() : unk0(0) {}
    };

public:
    /**
     * @brief Constructor
     */
    RPSysScene();

    /**
     * @name Internal events
     * @brief These functions are internal, and should not be overriden.
     */
    /**@{*/
    /**
     * @brief Updates the scene state
     */
    virtual void calc() override; // at 0xC

    /**
     * @brief Renders the scene state
     */
    virtual void draw() override; // at 0x10

    /**
     * @brief Enters the scene
     */
    virtual void enter() override; // at 0x14

    /**
     * @brief Exits the scene
     */
    virtual void exit() override; // at 0x18

    /**
     * @brief Re-initializes the scene
     */
    virtual void reinit() override; // at 0x1C

    /**
     * @brief Prepares for destruction of (and transition from) a child scene
     */
    virtual void incoming_childDestroy() override; // at 0x20

    /**
     * @brief Prepares for creation of (and transition to) a child scene
     */
    virtual void outgoing_childCreate() override; // at 0x24
    /**@}*/

    /**
     * @name Lifecycle hooks
     * @brief These functions are mostly empty stubs, and should be overridden
     * to provide scene functionality.
     */
    /**@{*/
    virtual UnkStruct& VF_0x3C() {
        return sUnkStruct;
    } // at 0x3C

    /**
     * @brief Pause callback
     *
     * @param enter Whether the pause menu is being entered
     */
    virtual void pauseCallBack(bool /* enter */) {} // at 0x40

    /**
     * @brief Initializes the scene's state for the first time
     */
    virtual void Configure() {} // at 0x44

    /**
     * @brief Loads the scene's required assets
     */
    virtual void LoadResource() {} // at 0x48

    /**
     * @brief Re-initializes the scene's state
     */
    virtual void Reset() {} // at 0x4C

    /**
     * @brief Updates the scene's state
     */
    virtual void Calculate() {} // at 0x50

    /**
     * @brief Exits the scene
     */
    virtual void Exit() {} // at 0x54

    /**
     * @brief Runs an asynchronous task on the DVD thread
     */
    virtual void taskAsync() {} // at 0x58
    /**@}*/

    /**
     * @brief Tests whether the scene is fully visible
     */
    bool isSceneDisplay() const;

    /**
     * @brief Tests whether the scene is visibly obscured
     */
    bool isSceneBlank() const;

    /**
     * @brief Tests whether a scene change would be allowed
     */
    bool isSceneChangeEnable() const;

    /**
     * @brief Tests whether NAND access would be safe
     */
    bool isNandAccessEnable() const;

    /**
     * @brief Sets the duration of all faders
     *
     * @param frame Fade duration, in frames
     */
    void setFadeFrame(u16 frame);

    /**
     * @brief Gets the color of the manager fader
     */
    nw4r::ut::Color getFadeColor() const;

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
     * @brief Begins fading in the scene fader
     *
     * @return Success
     */
    bool startFadeIn();

    /**
     * @brief Begins fading out the scene fader
     *
     * @return Success
     */
    bool startFadeOut();

    /**
     * @brief Toggles screen dimming
     * @note If "Screen Saver Mode" is disabled, dimming is always OFF.
     *
     * @param enable Whether to dim the screen
     */
    void setDimming(bool enable);

    /**
     * @brief Sets this scene's parent/creator ID
     *
     * @param id ID of this scene's parent/creator
     */
    void setCreatorSceneID(s32 id);

    /**
     * @brief Gets this scene's parent/creator ID
     */
    s32 getCreatorSceneID() const;

    /**
     * @brief Marks this scene as a child of the previous scene
     */
    void setChildScene();

    /**
     * @brief Displays the game's build date timestamp
     *
     * @param color Text color
     */
    void drawTimeStamp(nw4r::ut::Color color);

    /**
     * @brief Marks that this scene requires an asynchronous task
     */
    void setTaskAsync();

    /**
     * @brief Tests whether this scene's asynchronous task has finished
     */
    bool isTaskAsyncFinish() const;

private:
    /**
     * @brief Prepares this scene to be entered
     */
    DECOMP_INLINE void incomingScene();

    /**
     * @brief Prepares this scene to be exited
     */
    void outgoingScene();

    /**
     * @brief Finalizes this scene after being exited
     */
    void exitScenePost();

    /**
     * @brief Initializes this scene's members
     */
    void init();

    void loadUpdate();

    /**
     * @brief Creates the asynchronous task thread if requested by the scene
     */
    void initTaskAsync();

    /**
     * @brief Enables the "Now Loading" message display
     */
    void enableLoadMessage();

    /**
     * @brief Loads this scene's resources asynchronously
     */
    void load();

    /**
     * @brief Loads this scene's resources asynchronously, displaying a "Now
     * Loading" message if the feature is enabled
     */
    void loadMessage();

    /**
     * @brief Polls the status of the DVD task thread
     */
    void updateDvdEndMessage();

    /**
     * @brief Polls the status of the NAND task thread
     */
    void updateNandEndMessage();

    /**
     * @brief Thread function for the LoadResource phase
     *
     * @param pArg Thread function argument
     */
    static void loadResourceFunc(void* pArg);

    /**
     * @brief Thread function for the scene's task
     *
     * @param pArg Thread function argument
     */
    static void taskAsyncFunc(void* pArg);

private:
    /**
     * @brief Scene flags
     */
    enum {
        EFlag_LoadMessage,      //!< Display "Now Loading" message
        EFlag_TaskAsyncSet,     //!< The scene requested an asynchronous task
        EFlag_TaskAsyncRunning, //!< The asynchronous task is running
        EFlag_IsChild,          //!< This scene was created as a child
    };

private:
    static UnkStruct sUnkStruct;

    //! Scene renderer
    RPGrpRenderer* mpRenderer; // at 0x2C
    //! Common draw functionality
    RPSysCommonObject* mpCommonObject; // at 0x30
    //! Scene effect creator
    RPSysEffectCreator* mpEffectCreator; // at 0x34
    //! Scene heap
    EGG::Heap* mpSceneHeap; // at 0x38
    //! Scene flags
    EGG::TBitFlag<u32> mFlags; // at 0x3C
    //! ID of the previous scene
    s32 mCreatorSceneID; // at 0x40
};

//! @}

#endif
