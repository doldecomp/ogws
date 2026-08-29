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
     * @brief Destructor
     */
    virtual ~RPSysScene() override {} // at 0x8

    /**
     * @name Internal events
     * @brief These event functions are internal and should not be overriden.
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
     * @name User events
     * @brief These event functions are mostly empty stubs and should be
     * overriden to provide scene functionality.
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
    virtual void pauseCallBack(bool enter); // at 0x40

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
     * @brief Sets the current frame of both faders
     *
     * @param frame Frame count
     */
    void setFadeFrame(u16 frame);

    /**
     * @brief Gets the color of the manager fader
     */
    nw4r::ut::Color getFadeColor() const;

    /**
     * @brief Sets the color of both faders
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
     */
    void startFadeIn();

    /**
     * @brief Begins fading out the scene fader
     */
    void startFadeOut();

    /**
     * @brief Toggles screen dimming
     * @note If "Screen Saver Mode" is disabled, dimming is always OFF.
     *
     * @param enable Whether to dim the screen
     */
    void setDimming(bool enable);

protected:
    void outgoingScene();

    void exitScenePost();

    void init();

    void setCreatorSceneID(s32 id);

    s32 getCreatorSceneID() const;

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
