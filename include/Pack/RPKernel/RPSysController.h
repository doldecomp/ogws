#ifndef RP_KERNEL_CONTROLLER_H
#define RP_KERNEL_CONTROLLER_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel/IRPSysHostIOSocket.h>

#include <egg/core.h>

#include <revolution/KPAD.h>
#include <revolution/WPAD.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Helper macro to access core controllers
 */
#define RP_GET_CORE_CTRL(N)                                                    \
    static_cast<RPSysCoreController*>(                                         \
        EGG_GET_INSTANCE(EGG::CoreControllerMgr)->getNthController(N))

/******************************************************************************
 *
 * RPSysCoreAddress
 *
 ******************************************************************************/

/**
 * @brief Wii Remote controller MAC address
 */
class RPSysCoreAddress {
public:
    /**
     * @brief Constructor
     */
    RPSysCoreAddress();

    /**
     * @brief Clears the controller address
     */
    void reset();

    /**
     * @brief Attempts to read the address of the specified controller
     *
     * @param chan Controller remote channel
     * @return Success
     */
    bool read(s32 chan);

    /**
     * @brief Sets the value of this controller address
     *
     * @param pData New controller address
     */
    void set(const u8* pData);

    /**
     * @brief Gets the specified digit of this address
     *
     * @param idx Digit index
     */
    u8 get(int idx) const;

    /**
     * @brief Tests whether this controller address is valid
     */
    bool isValid() const;

    /**
     * @brief Tests whether two controller addresses are equivalent
     *
     * @param rOther Other controller address
     */
    bool isEqual(const RPSysCoreAddress& rOther) const;

private:
    //! Number of read attempts before giving up
    static const int RETRY_NUM = 1000;

private:
    //! Controller address work buffer
    static u8 sAddrWork[WPAD_ADDR_LEN];

    //! Remote address
    u8 mData[WPAD_ADDR_LEN]; // at 0x0
};

/******************************************************************************
 *
 * RPSysCoreInfo
 *
 ******************************************************************************/

/**
 * @brief Wii Remote controller information
 */
class RPSysCoreInfo : public WPADInfo {
    // Controller manages the flags
    friend class RPSysCoreController;

public:
    /**
     * @brief Constructor
     */
    RPSysCoreInfo();

    /**
     * @brief Clears the controller information
     */
    void reset();

    /**
     * @brief Tests whether the controller battery level is low
     */
    bool isLowBattery() const;

private:
    /**
     * @brief Information flags
     */
    enum {
        EFlag_GetInfoSuccess = 1 << 0, //!< WPADGetInfoAsync succeeded
        EFlag_GetInfoFail = 1 << 1,    //!< WPADGetInfoAsync failed
    };

private:
    //! Information flags
    u16 mFlags; // at 0x18
};

/******************************************************************************
 *
 * RPSysCoreController
 *
 ******************************************************************************/

/**
 * @brief Wii Remote controller state
 */
class RPSysCoreController : public EGG::CoreController,
                            public IRPSysHostIOSocket {
    // Manager accesses internal state
    friend class RPSysCoreControllerMgr;

public:
    /**
     * @brief Rumble pattern
     */
    enum ERumblePattern {
        ERumblePattern_Cursor,  //!< Cursor action
        ERumblePattern_Connect, //!< Controller connected
        ERumblePattern_2,
        ERumblePattern_Change, //!< Active player change
    };

    /**
     * @brief KPAD parameter stack
     */
    class ParamStack {
    public:
        /**
         * @brief Constructor
         */
        ParamStack();

        /**
         * @brief Clears the parameter stack
         */
        void reset();

        /**
         * @brief Sets the initial parameters
         *
         * @param playRadius DPD play radius
         * @param sensitivity DPD sensitivity
         */
        void configure(f32 playRadius, f32 sensitivity);

        /**
         * @brief Sets the current parameters
         *
         * @param playRadius DPD play radius
         * @param sensitivity DPD sensitivity
         */
        void set(f32 playRadius, f32 sensitivity);

        /**
         * @brief Pushes the current parameter set onto the stack
         */
        void push();

        /**
         * @brief Pops the top parameter set from the stack
         */
        void pop();

        /**
         * @brief Gets the current play radius parameter
         */
        f32 getPlayRadius() const {
            return mPlayRadiusStack[mSize];
        }

        /**
         * @brief Gets the current sensitivity parameter
         */
        f32 getSensitivity() const {
            return mSensitivityStack[mSize];
        }

    private:
        //! Stack capacity
        static const int CAPACITY = 8;

    private:
        //! Stack size
        s16 mSize; // at 0x0

        //! Initial play radius parameter
        f32 mInitialPlayRadius; // at 0x4
        //! Initial sensitivity parameter
        f32 mInitialSensitivity; // at 0x8

        //! Play radius parameter stack
        f32 mPlayRadiusStack[CAPACITY]; // at 0xC
        //! Sensitivity parameter stack
        f32 mSensitivityStack[CAPACITY]; // at 0x2C
    };

    /**
     * @brief CoreStatus extension
     */
    class ExStatus {
    public:
        /**
         * @brief Constructor
         */
        ExStatus();

        /**
         * @brief Sets the current parameters
         *
         * @param threshold Acceleration smoothing threshold
         * @param rate Acceleration smoothing rate
         */
        void set(f32 threshold, f32 rate);

        /**
         * @brief Gets the specified core status
         *
         * @param idx Core status index
         */
        EGG::CoreStatus* getCoreStatus(int idx) {
            return &status[idx];
        }

        /**
         * @brief Updates the controller input state
         *
         * @param pStatusArray Controller sample set
         * @param count Number of controler samples
         */
        void calc(EGG::CoreStatus* pStatusArray, s32 count);

    private:
        //! Smoothing threshold
        f32 mPassThreshold; // at 0x0
        //! Smoothing rate
        f32 mPassRate; // at 0x4

        //! Input samples
        EGG::CoreStatus status[KPAD_MAX_SAMPLES]; // at 0x8
    };

public:
    /**
     * @brief Initializes the controller system
     */
    static void initialize();

    /**
     * @brief Tests whether the sensor bar is positioned above the TV
     */
    static bool isSensorBarTop();

    /**
     * @brief Applies global controller settings
     */
    static void applySetting();

    /**
     * @brief Prepares the controller system for a scene reset
     */
    static void sceneReset();

    /**
     * @brief Forcibly turns on the sensor bar
     */
    static void forceSensorBarPowerOn();

    /**
     * @brief Prepares the controller system for a new scene
     */
    static void initScene();

    /**
     * @brief Constructor
     *
     * @param playerNo Player ID
     */
    RPSysCoreController(u32 playerNo);

    /**
     * @brief Destructor
     */
    virtual ~RPSysCoreController() override; // at 0x14

    /**
     * @brief Sets the KPAD position parameters
     *
     * @param playRadius Play radius parameter
     * @param sensitivity Sensitivity parameter
     */
    virtual void setPosParam(f32 playRadius,
                             f32 sensitivity) override; // at 0x8

    /**
     * @brief Sets the KPAD horizon parameters
     *
     * @param playRadius Play radius parameter
     * @param sensitivity Sensitivity parameter
     */
    virtual void setHoriParam(f32 playRadius,
                              f32 sensitivity) override; // at 0xC

    /**
     * @brief Sets the KPAD distance parameters
     *
     * @param playRadius Play radius parameter
     * @param sensitivity Sensitivity parameter
     */
    virtual void setDistParam(f32 playRadius,
                              f32 sensitivity) override; // at 0x10

    /**
     * @brief Sets the KPAD acceleration parameters
     *
     * @param playRadius Play radius parameter
     * @param sensitivity Sensitivity parameter
     */
    virtual void setAccParam(f32 playRadius,
                             f32 sensitivity) override; // at 0x14

    /**
     * @brief Performs processing at the beginning of the frame
     *
     * @param pStatus GameCube controller status (for debugging?)
     */
    virtual void beginFrame(PADStatus* pStatus = NULL) override; // at 0x18

    /**
     * @brief Sets the parameters for the specified extended status
     *
     * @param idx Extended status index
     * @param threshold Smoothing threshold
     * @param rate Smoothing rate
     */
    void setExAccParam(int idx, f32 threshold, f32 rate);

    /**
     * @brief Accesses the specified core status
     *
     * @param idx Extended status index
     * @param sample Core status sample index
     */
    EGG::CoreStatus* getExCoreStatus(int idx, int sample);

    /**
     * @brief Shuts down the controller system
     *
     * @param forIpl Whether the program is exiting to the IPL
     */
    static void shutdownSystem(bool forIpl);

    /**
     * @brief Turns off the rumble motor in all controllers
     */
    static void stopMotorAll();

    /**
     * @brief Starts the specified rumble pattern
     *
     * @param pattern Rumble pattern
     */
    void rumble(ERumblePattern pattern);

    /**
     * @brief Tests whether this controller's base device (no extension) is a
     * Wii Remote controller
     */
    bool isCoreBaseDevice() const;

    /**
     * @brief Enables pairing of controllers
     */
    static void enableConnection();

    /**
     * @brief Disables pairing of controllers
     */
    static void disableConnection();

    /**
     * @brief Toggles whether DPD control is enabled
     *
     * @param enable Whether to enable DPD control
     */
    void enableDpdCtrl(bool enable);

    /**
     * @brief Disables DPD control for all controllers
     */
    static void disableDpdCtrlAll();

    /**
     * @brief Resets the state of the DPD control stack
     */
    void resetDpdCtrlStack();

    /**
     * @brief Pushes a new value to the DPD control stack
     *
     * @param enable Whether to enable DPD control
     */
    void pushDpdCtrlStack(bool enable);

    /**
     * @brief Pushes a new value to the DPD control stack for all controllers
     *
     * @param enable Whether to enable DPD control
     */
    static void pushDpdCtrlStackAll(bool enable);

    /**
     * @brief Pops the top value from the DPD control stack
     */
    void popDpdCtrlStack();

    /**
     * @brief Pops the top value from the DPD control stack for all controllers
     */
    static void popDpdCtrlStackAll();

    /**
     * @brief Tests whether DPD control was enabled at the previous stack level
     */
    bool isPrevDpdCtrlEnable();

    /**
     * @brief Pushes the current KPAD parameter set onto the stack for all
     * controllers
     */
    static void pushKPADParamStackAll();

    /**
     * @brief Pops the top KPAD parameter set from the stack for all controllers
     */
    static void popKPADParamStackAll();

    /**
     * @brief Attempts to read the controller information
     *
     * @return Success
     */
    bool requestCoreInfoAsync();

    /**
     * @brief Accesses this controller's MAC address
     */
    RPSysCoreAddress& getAddress() {
        return mAddress;
    }
    /**
     * @brief Accesses this controller's MAC address (const-view)
     */
    const RPSysCoreAddress& getAddress() const {
        return mAddress;
    }

private:
    /**
     * @brief Controller event
     */
    enum EEvent {
        EEvent_None,       //!< Nothing happened
        EEvent_Connect,    //!< Connected this frame
        EEvent_Disconnect, //!< Disconnected this frame
    };

    /**
     * @brief Extended status ID
     */
    enum EExStatus {
        EExStatus_0,
        EExStatus_1,
        EExStatus_2,
        EExStatus_3,

        EExStatus_Max,
    };

    /**
     * @brief Vertical Y acceleration type
     */
    enum EAccVYType {
        EAccVYType_None, //!< DPD is invalid
        EAccVYType_Low,  //!< Below average acceleration
        EAccVYType_High, //!< Above average acceleration
    };

    //! DPD control stack size
    static const int DPD_STACK_CAPACITY = 8;

    //! Number of samples to use for the vertical Y acceleration average
    static const u32 ACC_VY_AVG_SAMPLES = 100;

    //! Buttons considered for cursor auto-repeat
    static const u32 CURSOR_BUTTONS =
        EGG::cCORE_BUTTON_UP | EGG::cCORE_BUTTON_DOWN |    //
        EGG::cCORE_BUTTON_LEFT | EGG::cCORE_BUTTON_RIGHT | //
        EGG::cCORE_FSSTICK_UP | EGG::cCORE_FSSTICK_DOWN |  //
        EGG::cCORE_FSSTICK_LEFT | EGG::cCORE_FSSTICK_RIGHT;

    //! Cursor auto-repeat delay, in frames
    static const u32 CURSOR_REPEAT_DELAY = 40;
    //! Cursor auto-repeat rate, in frames
    static const u32 CURSOR_REPEAT_RATE = 5;

private:
    /**
     * @brief Creates a new controller object
     */
    static EGG::CoreController* createCoreController();

    /**
     * @brief Becomes the main (Player 1) controller
     */
    void becomeMainController();

    /**
     * @brief Assigns a new WPAD channel and address to this controller
     *
     * @param chan New WPAD channel
     * @param rAddress New controller address
     */
    void set(s32 chan, const RPSysCoreAddress& rAddress);

    /**
     * @brief Updates the vertical Y acceleration statistics
     */
    DECOMP_INLINE void updateAccVYMinMax();

    /**
     * @brief WPADGetInfoAsync callback
     *
     * @param chan Remote channel
     * @param result WPAD library result
     */
    static void getInfoCallback(s32 chan, s32 result);

private:
    //! Default threshold parameters for each extended status
    static const f32 DEFAULT_EX_THRESHOLD[EExStatus_Max];
    //! Default rate parameters for each extended status
    static const f32 DEFAULT_EX_RATE[EExStatus_Max];

    //! Next player index
    static s16 sNextPlayerNo;

    //! Player 1's controller
    static RPSysCoreController* spMainController;
    //! Player 1's controller address
    static RPSysCoreAddress sMainAddress;

    //! Whether a controller has disconnected in this scene
    static bool sDisconnectOccurred;

    //! Sensor bar height level
    static f32 sSensorHeight;

    //! Last result from WPADProbe
    s32 mWPADProbeResult; // at 0x900
    //! Controller event
    EEvent mEvent; // at 0x904
    //! Assigned player ID
    u32 mPlayerNo; // at 0x908

    //! Held cursor buttons
    u32 mCursorHold; // at 0x90C
    //! How long the cursor buttons have been held
    u32 mCursorHoldTime; // at 0x910
    //! Cursor buttons held during the previous frame
    u32 mPrevCursorHold; // at 0x914
    //! Controller buttons to consider for cursor auto-repeat
    u32 mCursorButtons; // at 0x918
    //! Delay for cursor auto-repeat
    u32 mCursorRepeatDelay; // at 0x91C
    //! Rate for cursor auto-repeat
    u32 mCursorRepeatRate; // at 0x920

    //! Vertical Y acceleration analysis result
    EAccVYType mAccVYType; // at 0x924
    //! Minimum vertical Y acceleration
    f32 mAccVYMin; // at 0x928
    //! Maximum vertical Y acceleration
    f32 mAccVYMax; // at 0x92C
    //! Number of vertical Y samples taken for averaging
    u16 mAccVYSamples; // at 0x930

    //! DPD control stack size
    s16 mDpdCtrlStackSize; // at 0x932
    //! DPD control stack space
    bool mDpdCtrlStack[DPD_STACK_CAPACITY]; // at 0x934

    //! KPAD position parameter stack
    ParamStack mPosParamStack; // at 0x93C
    //! KPAD horizon parameter stack
    ParamStack mHoriParamStack; // at 0x988
    //! KPAD distance parameter stack
    ParamStack mDistParamStack; // at 0x9D4
    //! KPAD acceleration parameter stack
    ParamStack mAccParamStack; // at 0xA20

    //! Controller information
    RPSysCoreInfo mCoreInfo; // at 0xA6C
    //! Extended controller status
    ExStatus mExStatus[EExStatus_Max]; // at 0xA88
    //! MAC address
    RPSysCoreAddress mAddress; // at 0x2BA8
};

//! @}

#endif
