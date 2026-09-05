#ifndef RP_KERNEL_HOME_MENU_MGR_H
#define RP_KERNEL_HOME_MENU_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPAudio.h>
#include <Pack/RPSingleton.h>
#include <Pack/RPSystem/RPSysProjectLocal.h>

#include <homebuttonMiniLib.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief HOME Menu manager
 */
class RPSysHomeMenuMgr {
    RP_SINGLETON_DECL_EX(RPSysHomeMenuMgr);

public:
    /**
     * @brief Icon when HOME Menu is disabled
     */
    class BanIcon {
    public:
        /**
         * @brief Constructor
         */
        BanIcon();

        /**
         * @brief Updates this icon's state
         */
        void calc();

        /**
         * @brief Renders this icon's state
         */
        void draw();

        /**
         * @brief Resets this icon's state
         */
        void clear() {
            mState = EState_Hide;
            mTimer = 0;
            mAlpha = 0;
        }

        /**
         * @brief Enables this icon
         */
        void switchOn() {
            mState = EState_FadeIn;
            mTimer = 0;
            mAlpha = 0;
        }

        /**
         * @brief Tests whether this icon is visible
         */
        bool isDisp() const {
            return mState != EState_Hide;
        }

        /**
         * @brief Attaches a texture to this icon
         *
         * @param pTexture Icon texture
         */
        void setTexture(const EGG::ResTIMG* pTexture) {
            mpTexture = pTexture;
        }

    private:
        /**
         * @brief State machine state
         */
        enum EState {
            EState_Hide,    //!< Icon is not displaying
            EState_FadeIn,  //!< Icon is appearing
            EState_Disp,    //!< Icon is fully visible
            EState_FadeOut, //!< Icon is disappearing
        };

        //! Time to fade in/out the icon, in frames
        static const int FADE_LENGTH = 15;
        //! Time to fully display the icon, in frames
        static const int DISP_LENGTH = 60;

    private:
        //! Ban icon texture
        const EGG::ResTIMG* mpTexture; // at 0x0

        //! State machine state
        EState mState; // at 0x4
        //! Duration of the current state
        s16 mTimer; // at 0x8

        //! Calculated icon transparency
        u16 mAlpha; // at 0xA
    };

    /**
     * @brief HOME Menu state
     */
    enum EMenuState {
        EMenuState_End,   //!< Menu is closing
        EMenuState_Start, //!< Menu is opening
        EMenuState_Open,  //!< Menu is interactable
        EMenuState_Reset, //!< Menu is performing a soft reset
    };

public:
    /**
     * @brief Initializes this manager's state
     */
    void init();

    /**
     * @brief Initializes the HBM library
     */
    void initHomeButtonInfo();

    /**
     * @brief Performs a soft reset
     *
     * @return Whether HBM will perform the reset
     */
    bool softReset();

    /**
     * @brief Updates this manager's state
     */
    void update();

    /**
     * @brief Renders the HOME Menu if it is visible
     */
    void draw();

    /**
     * @brief Renders the ban icon if it is visible
     */
    void drawBanIcon();

    /**
     * @brief Toggles whether the HOME Menu is disabled
     *
     * @param disable Whether to disable the menu
     */
    void disable(bool disable) {
        mIsDisabled = disable;
    }

    /**
     * @brief Tests whether the HOME Menu is currently active
     */
    bool isActive() const {
        return mIsActive;
    }

private:
    //! HBM work memory size
    static const u32 HBM_WORK_SIZE = OS_MEM_KB_TO_B(512);
    //! Size of the HBM config.txt file
    static const u32 HBM_CONFIG_SIZE = 0x23;

private:
    /**
     * @brief HBM library sound callback
     *
     * @param event HBM event
     * @param arg Event argument
     * @return Whether this callback handled the playback for HBM
     */
    static BOOL soundCallback(int event, int arg);

    /**
     * @brief Checks whether the HOME Menu should be opened
     */
    void checkMenuStart();

    /**
     * @brief Checks whether the HOME Menu should be closed
     */
    void checkMenuEnd();

private:
    //! HOME Menu sound archive manager
    static RPSndHomeMenuArcMgr* spHomeMenuArcMgr;
    //! Sound archive heap size
    static u32 sSoundHeapSize;

    //! Whether the HBM resources have been initialized
    bool mIsInitialized; // at 0x8

    //! Whether the menu is disabled
    bool mIsDisabled; // at 0x9
    //! Whether the menu is opening due to a button press
    bool mIsStarting; // at 0xA
    //! Whether the menu is interactable
    bool mIsActive; // at 0xB
    //! Whether the menu should be drawn
    bool mIsVisible; // at 0xC

    //! Whether a soft reset is in progress
    bool mIsSoftReset; // at 0xD

    //! Current state machine state
    EMenuState mMenuState; // at 0x10
    //! Current state duration
    s16 mStateTimer; // at 0x14

    //! Runtime project localization
    RPSysProjectLocal* mpProjectLocal; // at 0x18

    //! Menu ban icon
    BanIcon* mpBanIcon; // at 0x1C

    //! HBM library configuration
    HBMDataInfo mHBMDataInfo; // at 0x20

    //! HBM controller input state
    HBMControllerData mHBMControllerData; // at 0x60
    //! Local controller input state
    KPADStatus mKPADStatus[KPAD_MAX_CONTROLLERS]; // at 0xA0
};

//! @}

#endif
