#include <Pack/RPKernel.h>

#include <egg/core.h>

#include <revolution/KPAD.h>
#include <revolution/WPAD.h>

#include <cmath>
#include <cstring>

//! Sensor height when the bar is above the TV
#define SENSOR_HEIGHT_TOP 0.15f
//! Sensor height when the bar is below the TV
#define SENSOR_HEIGHT_BOTTOM -0.35f

//! KPAD button repeat delay frequency
#define KPAD_DELAY_FREQ 1.5f
//! KPAD button repeat pulse frequency
#define KPAD_PULSE_FREQ 12.0f

/**
 * @brief Default threshold parameters for each extended status
 */
const f32 RPSysCoreController::DEFAULT_EX_THRESHOLD[EExStatus_Max] = {
    0.01f, // EExStatus_0
    0.1f,  // EExStatus_1
    0.1f,  // EExStatus_2
    0.1f,  // EExStatus_3
};

/**
 * @brief Default rate parameters for each extended status
 */
const f32 RPSysCoreController::DEFAULT_EX_RATE[EExStatus_Max] = {
    0.1f,   // EExStatus_0
    0.015f, // EExStatus_1
    0.05f,  // EExStatus_2
    0.02f,  // EExStatus_3
};

/**
 * @brief Next player index
 */
s16 RPSysCoreController::sNextPlayerNo = 0;

/**
 * @brief Player 1's controller
 */
RPSysCoreController* RPSysCoreController::spMainController = NULL;

/**
 * @brief Player 1's controller address
 */
RPSysCoreAddress RPSysCoreController::sMainAddress;

/**
 * @brief Whether a controller has disconnected in this scene
 */
bool RPSysCoreController::sDisconnectOccurred = false;

/**
 * @brief Sensor bar height level
 */
f32 RPSysCoreController::sSensorHeight = SENSOR_HEIGHT_TOP;

/******************************************************************************
 *
 * ParamStack
 *
 ******************************************************************************/

/**
 * @brief Constructor
 */
RPSysCoreController::ParamStack::ParamStack()
    : mSize(0), mInitialPlayRadius(0.0f), mInitialSensitivity(0.0f) {

    for (int i = 0; i < CAPACITY; i++) {
        mPlayRadiusStack[i] = 0.0f;
        mSensitivityStack[i] = 0.0f;
    }
}

/**
 * @brief Clears the parameter stack
 */
void RPSysCoreController::ParamStack::reset() {
    mSize = 0;

    for (int i = 0; i < CAPACITY; i++) {
        mPlayRadiusStack[i] = 0.0f;
        mSensitivityStack[i] = 0.0f;
    }

    mPlayRadiusStack[0] = mInitialPlayRadius;
    mSensitivityStack[0] = mInitialSensitivity;
}

/**
 * @brief Sets the initial parameters
 *
 * @param playRadius DPD play radius
 * @param sensitivity DPD sensitivity
 */
void RPSysCoreController::ParamStack::configure(f32 playRadius,
                                                f32 sensitivity) {
    mInitialPlayRadius = playRadius;
    mInitialSensitivity = sensitivity;
}

/**
 * @brief Sets the current parameters
 *
 * @param playRadius DPD play radius
 * @param sensitivity DPD sensitivity
 */
void RPSysCoreController::ParamStack::set(f32 playRadius, f32 sensitivity) {
    mPlayRadiusStack[mSize] = playRadius;
    mSensitivityStack[mSize] = sensitivity;
}

/**
 * @brief Pushes the current parameter set onto the stack
 */
void RPSysCoreController::ParamStack::push() {
    ++mSize;

    if (mSize >= 0 && mSize < CAPACITY) {
        mPlayRadiusStack[mSize] = mInitialPlayRadius;
        mSensitivityStack[mSize] = mInitialSensitivity;
    }
}

/**
 * @brief Pops the top parameter set from the stack
 */
void RPSysCoreController::ParamStack::pop() {
    if (mSize > 0) {
        mSize--;
    }
}

/******************************************************************************
 *
 * ExStatus
 *
 ******************************************************************************/

/**
 * @brief Performs smoothing on an acceleration component
 *
 * @param pValue Value to modify
 * @param target Smoothing target
 * @param threshold Smoothing threshold
 * @param rate Smoothing rate
 */
static void CalcAcc(f32* pValue, f32 target, f32 threshold, f32 rate) {
    f32 t;
    f32 delta = target - *pValue;

    if (delta < 0.0f) {
        t = -delta;
    } else {
        t = delta;
    }

    if (t >= threshold) {
        t = 1.0f;
    } else {
        t /= threshold;
        t *= t;
        t *= t;
    }

    t *= rate;
    *pValue += t * delta;
}

/**
 * @brief Constructor
 */
RPSysCoreController::ExStatus::ExStatus()
    : mPassThreshold(0.0f), mPassRate(1.0f) {

    std::memset(status, 0, sizeof(status));
}

/**
 * @brief Sets the current parameters
 *
 * @param threshold Acceleration smoothing threshold
 * @param rate Acceleration smoothing rate
 */
void RPSysCoreController::ExStatus::set(f32 threshold, f32 rate) {
    mPassThreshold = threshold;
    mPassRate = rate;
}

/**
 * @brief Updates the controller input state
 *
 * @param pStatusArray Controller sample set
 * @param count Number of controler samples
 */
void RPSysCoreController::ExStatus::calc(EGG::CoreStatus* pStatusArray,
                                         s32 count) {
    Vec prev = status[0].acc;

    for (s32 i = count - 1; i >= 0; i--) {
        EGG::CoreStatus* pOut = &status[i];
        Vec acc = prev;

        CalcAcc(&acc.x, pStatusArray[i].acc.x, mPassThreshold, mPassRate);
        CalcAcc(&acc.y, pStatusArray[i].acc.y, mPassThreshold, mPassRate);
        CalcAcc(&acc.z, pStatusArray[i].acc.z, mPassThreshold, mPassRate);
        pOut->acc = acc;

        pOut->acc_value =
            std::sqrtf(acc.x * acc.x + acc.y * acc.y + acc.z * acc.z);

        prev.x -= acc.x;
        prev.y -= acc.y;
        prev.z -= acc.z;

        pOut->acc_speed =
            std::sqrtf(prev.x * prev.x + prev.y * prev.y + prev.z * prev.z);

        prev = acc;
    }
}

/******************************************************************************
 *
 * RPSysCoreAddress
 *
 ******************************************************************************/

/**
 * @brief Controller address work buffer
 */
u8 RPSysCoreAddress::sAddrWork[WPAD_ADDR_LEN] = {};

/**
 * @brief Constructor
 */
RPSysCoreAddress::RPSysCoreAddress() {
    reset();
}

/**
 * @brief Clears the controller address
 */
void RPSysCoreAddress::reset() {
    for (int i = 0; i < WPAD_ADDR_LEN; i++) {
        mData[i] = 0;
    }
}

/**
 * @brief Attempts to read the address of the specified controller
 *
 * @param chan Controller remote channel
 * @return Success
 */
bool RPSysCoreAddress::read(s32 chan) {
    int attempts = 0;
    bool success = false;

    do {
        WPADGetAddress(chan, sAddrWork);
        attempts++;
        success = false;

        for (int j = 0; j < WPAD_ADDR_LEN; j++) {
            mData[j] = sAddrWork[j];
        }

        for (int j = 0; j < WPAD_ADDR_LEN; j++) {
            if (mData[j] != 0) {
                success = true;
                break;
            }
        }
    } while (!success && attempts < RETRY_NUM);

    return success;
}

/**
 * @brief Sets the value of this controller address
 *
 * @param pData New controller address
 */
void RPSysCoreAddress::set(const u8* pData) {
    std::memcpy(mData, pData, sizeof(mData));
}

/**
 * @brief Gets the specified digit of this address
 *
 * @param idx Digit index
 */
u8 RPSysCoreAddress::get(int idx) const {
    return mData[idx];
}

/**
 * @brief Tests whether this controller address is valid
 */
bool RPSysCoreAddress::isValid() const {
    bool valid = false;

    for (int i = 0; i < WPAD_ADDR_LEN; i++) {
        if (mData[i] != 0) {
            valid = true;
            break;
        }
    }

    return valid;
}

/**
 * @brief Tests whether two controller addresses are equivalent
 *
 * @param rOther Other controller address
 */
bool RPSysCoreAddress::isEqual(const RPSysCoreAddress& rOther) const {
    bool same = true;

    for (int i = 0; i < WPAD_ADDR_LEN; i++) {
        if (mData[i] != rOther.mData[i]) {
            same = false;
            break;
        }
    }

    return same;
}

/******************************************************************************
 *
 * RPSysCoreInfo
 *
 ******************************************************************************/

/**
 * @brief Constructor
 */
RPSysCoreInfo::RPSysCoreInfo() {
    reset();
}

/**
 * @brief Clears the controller information
 */
void RPSysCoreInfo::reset() {
    std::memset(this, 0, sizeof(*this));
    mFlags = 0; // double clear :p
}

/**
 * @brief Tests whether the controller battery level is low
 */
bool RPSysCoreInfo::isLowBattery() const {
    bool isLow = false;

    if (mFlags & EFlag_GetInfoSuccess) {
        switch (battery) {
        case 0:
        case 1: {
            isLow = true;
            break;

        default: {
            break;
        }
        }
        }
    }

    return isLow;
}

/******************************************************************************
 *
 * RPSysCoreController
 *
 ******************************************************************************/

/**
 * @brief Creates a new controller object
 */
EGG::CoreController* RPSysCoreController::createCoreController() {
    RPSysCoreController* pController = new RPSysCoreController(sNextPlayerNo++);

    if (spMainController == NULL) {
        pController->becomeMainController();
    }

    return pController;
}

/**
 * @brief Initializes the controller system
 */
void RPSysCoreController::initialize() {
    RPSysCoreControllerMgr::setCoreControllerFactory(createCoreController);
    RPSysCoreControllerMgr::create();

    f32 delay = 1.0f / KPAD_DELAY_FREQ;
    f32 pulse = 1.0f / KPAD_PULSE_FREQ;

    for (int i = 0; i < RP_MAX_CONTROLLERS; i++) {
        KPADSetSensorHeight(i, sSensorHeight);
        KPADSetBtnRepeat(i, delay, pulse);
    }

    for (int i = 0; i < RP_MAX_CONTROLLERS; i++) {
        RP_GET_CORE_CTRL(i)->createRumbleMgr();
    }

    sDisconnectOccurred = false;
}

/**
 * @brief Tests whether the sensor bar is positioned above the TV
 */
bool RPSysCoreController::isSensorBarTop() {
    return WPADGetSensorBarPosition() == WPAD_SENSOR_BAR_TOP;
}

/**
 * @brief Applies global controller settings
 */
void RPSysCoreController::applySetting() {
    if (isSensorBarTop()) {
        sSensorHeight = SENSOR_HEIGHT_TOP;
    } else {
        sSensorHeight = SENSOR_HEIGHT_BOTTOM;
    }

    for (int i = 0; i < RP_MAX_CONTROLLERS; i++) {
        KPADSetSensorHeight(i, sSensorHeight);
    }
}

/**
 * @brief Prepares the controller system for a scene reset
 */
void RPSysCoreController::sceneReset() {
    RP_GET_INSTANCE(RPSysCoreControllerMgr)->sceneReset();
}

/**
 * @brief Forcibly turns on the sensor bar
 */
void RPSysCoreController::forceSensorBarPowerOn() {
    WPADSetSensorBarPower(TRUE);
}

/**
 * @brief Prepares the controller system for a new scene
 */
void RPSysCoreController::initScene() {
    for (int i = 0; i < RP_MAX_CONTROLLERS; i++) {
        RP_GET_CORE_CTRL(i)->mPosParamStack.reset();
        RP_GET_CORE_CTRL(i)->mHoriParamStack.reset();
        RP_GET_CORE_CTRL(i)->mDistParamStack.reset();
        RP_GET_CORE_CTRL(i)->mAccParamStack.reset();
        RP_GET_CORE_CTRL(i)->resetDpdCtrlStack();
    }

    forceSensorBarPowerOn();
    sDisconnectOccurred = false;
}

/**
 * @brief Constructor
 *
 * @param playerNo Player ID
 */
RPSysCoreController::RPSysCoreController(u32 playerNo) {
    mWPADProbeResult = WPAD_ERR_NO_CONTROLLER;
    mEvent = EEvent_None;
    mPlayerNo = playerNo;

    mCursorHold = 0;
    mCursorHoldTime = 0;
    mPrevCursorHold = 0;
    mCursorButtons = CURSOR_BUTTONS;
    mCursorRepeatDelay = CURSOR_REPEAT_DELAY;
    mCursorRepeatRate = CURSOR_REPEAT_RATE;

    mAccVYType = EAccVYType_None;
    mAccVYMin = 0.0f;
    mAccVYMax = 0.0f;
    mAccVYSamples = 0;

    resetDpdCtrlStack();

    mPosParamStack.configure(0.06f, 1.0f);
    mHoriParamStack.configure(0.0f, 1.0f);
    mDistParamStack.configure(0.0f, 1.0f);
    mAccParamStack.configure(0.0f, 1.0f);

    for (int i = 0; i < EExStatus_Max; i++) {
        setExAccParam(i, DEFAULT_EX_THRESHOLD[i], DEFAULT_EX_RATE[i]);
    }
}

/**
 * @brief Destructor
 */
RPSysCoreController::~RPSysCoreController() {}

/**
 * @brief Sets the parameters for the specified extended status
 *
 * @param idx Extended status index
 * @param threshold Smoothing threshold
 * @param rate Smoothing rate
 */
void RPSysCoreController::setExAccParam(int idx, f32 threshold, f32 rate) {
    mExStatus[idx].set(threshold, rate);
}

/**
 * @brief Accesses the specified core status
 *
 * @param idx Extended status index
 * @param sample Core status sample index
 */
EGG::CoreStatus* RPSysCoreController::getExCoreStatus(int idx, int sample) {
    return mExStatus[idx].getCoreStatus(sample);
}

/**
 * @brief Performs processing at the beginning of the frame
 *
 * @param pStatus GameCube controller status (for debugging?)
 */
void RPSysCoreController::beginFrame(PADStatus* pStatus) {
    s32 devType;
    mWPADProbeResult = WPADProbe(mChannelID, &devType);

    if (mDpdCtrlStack[mDpdCtrlStackSize]) {
        KPADEnableDPD(mChannelID);
    } else {
        KPADDisableDPD(mChannelID);
    }

    KPADSetPosParam(mChannelID, //
                    mPosParamStack.getPlayRadius(),
                    mPosParamStack.getSensitivity());

    KPADSetHoriParam(mChannelID, //
                     mHoriParamStack.getPlayRadius(),
                     mHoriParamStack.getSensitivity());

    KPADSetDistParam(mChannelID, //
                     mDistParamStack.getPlayRadius(),
                     mDistParamStack.getSensitivity());

    KPADSetAccParam(mChannelID, //
                    mAccParamStack.getPlayRadius(),
                    mAccParamStack.getSensitivity());

    EGG::CoreController::beginFrame(pStatus);

    if (mWPADProbeResult == WPAD_ERR_NO_CONTROLLER) {
        getCoreStatus()->hold = 0;
        getCoreStatus()->trig = 0;
        getCoreStatus()->release = 0;
    }

    mCursorHold = 0;
    u32 nowHold = mCursorButtons & getCoreStatus()->hold;

    if (nowHold == 0) {
        mPrevCursorHold = 0;
        mCursorHoldTime = 0;
    } else {
        u32 prevHold = mPrevCursorHold;

        if (prevHold == nowHold) {
            u32 time = ++mCursorHoldTime;

            if (time == mCursorRepeatDelay ||
                (time > mCursorRepeatDelay &&
                 (time - mCursorRepeatDelay) % mCursorRepeatRate == 0)) {

                mCursorHold = nowHold;
            }
        } else {
            mPrevCursorHold = nowHold;
            mCursorHoldTime = 0;

            mCursorHold = nowHold & (0xFFFFFFFF ^ prevHold);
        }
    }

    for (int i = 0; i < EExStatus_Max; i++) {
        mExStatus[i].calc(mCoreStatus, mKPADReadLength);
    }

    updateAccVYMinMax();
}

/**
 * @brief Becomes the main (Player 1) controller
 */
void RPSysCoreController::becomeMainController() {
    spMainController = this;
    sMainAddress = mAddress;
}

/**
 * @brief Shuts down the controller system
 *
 * @param forIpl Whether the program is exiting to the IPL
 */
void RPSysCoreController::shutdownSystem(bool /* forIpl */) {}

/**
 * @brief Turns off the rumble motor in all controllers
 */
void RPSysCoreController::stopMotorAll() {
    for (int i = 0; i < RP_MAX_CONTROLLERS; i++) {
        RP_GET_CORE_CTRL(i)->stopMotor();
    }
}

/**
 * @brief Starts the specified rumble pattern
 *
 * @param pattern Rumble pattern
 */
void RPSysCoreController::rumble(ERumblePattern pattern) {
    switch (pattern) {
    case ERumblePattern_Cursor: {
        startPatternRumble("****--------", sizeof("****--------") - 1);
        break;
    }

    case ERumblePattern_Connect:
    case ERumblePattern_2:
    case ERumblePattern_Change: {
        startPatternRumble("***-***---*", sizeof("***-***---*") - 1);
        break;
    }

    default: {
        break;
    }
    }
}

/**
 * @brief Tests whether this controller's base device (no extension) is a
 * Wii Remote controller
 */
bool RPSysCoreController::isCoreBaseDevice() const {
    bool isCore = false;

    if (mWPADProbeResult != WPAD_ERR_NO_CONTROLLER) {
        switch (getDevType()) {
        case EGG::cDEV_CORE:
        case EGG::cDEV_FREESTYLE:
        case EGG::cDEV_CLASSIC:
        case EGG::cDEV_FUTURE:
        case EGG::cDEV_NOT_SUPPORTED:
        case EGG::cDEV_UNKNOWN: {
            isCore = true;
            break;
        }

        case EGG::cDEV_NOT_FOUND:
        case EGG::cDEV_NULL:
        default: {
            break;
        }
        }
    }

    return isCore;
}

/**
 * @brief Enables pairing of controllers
 */
void RPSysCoreController::enableConnection() {
    RP_GET_INSTANCE(RPSysCoreControllerMgr)->enableConnection();
}

/**
 * @brief Disables pairing of controllers
 */
void RPSysCoreController::disableConnection() {
    RP_GET_INSTANCE(RPSysCoreControllerMgr)->disableConnection();
}

/**
 * @brief Assigns a new WPAD channel and address to this controller
 *
 * @param chan New WPAD channel
 * @param rAddress New controller address
 */
void RPSysCoreController::set(s32 chan, const RPSysCoreAddress& rAddress) {
    mChannelID = chan;
    mAddress = rAddress;
}

/**
 * @brief Toggles whether DPD control is enabled
 *
 * @param enable Whether to enable DPD control
 */
void RPSysCoreController::enableDpdCtrl(bool enable) {
    if (mDpdCtrlStackSize >= 0 && mDpdCtrlStackSize < DPD_STACK_CAPACITY) {
        mDpdCtrlStack[mDpdCtrlStackSize] = enable;
    }
}

/**
 * @brief Disables DPD control for all controllers
 */
void RPSysCoreController::disableDpdCtrlAll() {
    for (int i = 0; i < RP_MAX_CONTROLLERS; i++) {
        RP_GET_CORE_CTRL(i)->enableDpdCtrl(false);
    }
}

/**
 * @brief Resets the state of the DPD control stack
 */
void RPSysCoreController::resetDpdCtrlStack() {
    mDpdCtrlStackSize = 0;

    for (int i = 0; i < DPD_STACK_CAPACITY; i++) {
        mDpdCtrlStack[i] = true;
    }
}

/**
 * @brief Pushes a new value to the DPD control stack
 *
 * @param enable Whether to enable DPD control
 */
void RPSysCoreController::pushDpdCtrlStack(bool enable) {
    ++mDpdCtrlStackSize;

    if (mDpdCtrlStackSize >= 0 && mDpdCtrlStackSize < DPD_STACK_CAPACITY) {
        mDpdCtrlStack[mDpdCtrlStackSize] = enable;
    }
}

/**
 * @brief Pushes a new value to the DPD control stack for all controllers
 *
 * @param enable Whether to enable DPD control
 */
void RPSysCoreController::pushDpdCtrlStackAll(bool enable) {
    for (int i = 0; i < RP_MAX_CONTROLLERS; i++) {
        RP_GET_CORE_CTRL(i)->pushDpdCtrlStack(enable);
    }
}

/**
 * @brief Pops the top value from the DPD control stack
 */
void RPSysCoreController::popDpdCtrlStack() {
    if (mDpdCtrlStackSize > 0) {
        mDpdCtrlStackSize--;
    }
}

/**
 * @brief Pops the top value from the DPD control stack for all controllers
 */
void RPSysCoreController::popDpdCtrlStackAll() {
    for (int i = 0; i < RP_MAX_CONTROLLERS; i++) {
        RP_GET_CORE_CTRL(i)->popDpdCtrlStack();
    }
}

/**
 * @brief Tests whether DPD control was enabled at the previous stack level
 */
bool RPSysCoreController::isPrevDpdCtrlEnable() {
    s16 prev = mDpdCtrlStackSize - 1;

    if (prev < 0) {
        prev = 0;
    }

    return mDpdCtrlStack[prev];
}

/**
 * @brief Sets the KPAD position parameters
 *
 * @param playRadius Play radius parameter
 * @param sensitivity Sensitivity parameter
 */
void RPSysCoreController::setPosParam(f32 playRadius, f32 sensitivity) {
    mPosParamStack.set(playRadius, sensitivity);
}

/**
 * @brief Sets the KPAD horizon parameters
 *
 * @param playRadius Play radius parameter
 * @param sensitivity Sensitivity parameter
 */
void RPSysCoreController::setHoriParam(f32 playRadius, f32 sensitivity) {
    mHoriParamStack.set(playRadius, sensitivity);
}

/**
 * @brief Sets the KPAD distance parameters
 *
 * @param playRadius Play radius parameter
 * @param sensitivity Sensitivity parameter
 */
void RPSysCoreController::setDistParam(f32 playRadius, f32 sensitivity) {
    mDistParamStack.set(playRadius, sensitivity);
}

/**
 * @brief Sets the KPAD acceleration parameters
 *
 * @param playRadius Play radius parameter
 * @param sensitivity Sensitivity parameter
 */
void RPSysCoreController::setAccParam(f32 playRadius, f32 sensitivity) {
    mAccParamStack.set(playRadius, sensitivity);
}

/**
 * @brief Pushes the current KPAD parameter set onto the stack for all
 * controllers
 */
void RPSysCoreController::pushKPADParamStackAll() {
    for (int i = 0; i < RP_MAX_CONTROLLERS; i++) {
        RP_GET_CORE_CTRL(i)->mPosParamStack.push();
        RP_GET_CORE_CTRL(i)->mHoriParamStack.push();
        RP_GET_CORE_CTRL(i)->mDistParamStack.push();
        RP_GET_CORE_CTRL(i)->mAccParamStack.push();
    }
}

/**
 * @brief Pops the top KPAD parameter set from the stack for all controllers
 */
void RPSysCoreController::popKPADParamStackAll() {
    for (int i = 0; i < RP_MAX_CONTROLLERS; i++) {
        RP_GET_CORE_CTRL(i)->mPosParamStack.pop();
        RP_GET_CORE_CTRL(i)->mHoriParamStack.pop();
        RP_GET_CORE_CTRL(i)->mDistParamStack.pop();
        RP_GET_CORE_CTRL(i)->mAccParamStack.pop();
    }
}

/**
 * @brief Updates the vertical Y acceleration statistics
 */
void RPSysCoreController::updateAccVYMinMax() {
    // TODO(kiwi) What is this flag value?
    if (getCoreStatus()->getDPDValidFlag() == 2) {
        if (mAccVYSamples < ACC_VY_AVG_SAMPLES) {
            mAccVYSamples++;
        }

        mAccVYMin += (getCoreStatus()->acc_vertical.y - mAccVYMin) * 0.05f;
        mAccVYMax += (getCoreStatus()->acc_vertical.y - mAccVYMax) * 0.05f;
    } else {
        mAccVYSamples = 0;
    }

    if (mAccVYSamples >= ACC_VY_AVG_SAMPLES) {
        if (getCoreStatus()->acc_vertical.y < mAccVYMin) {
            mAccVYMin = getCoreStatus()->acc_vertical.y;
        }

        if (getCoreStatus()->acc_vertical.y > mAccVYMax) {
            mAccVYMax = getCoreStatus()->acc_vertical.y;
        }
    }

    // TODO(kiwi) What is this flag value?
    if (getCoreStatus()->getDPDValidFlag() == 0) {
        if (getCoreStatus()->acc_vertical.y > (mAccVYMin + mAccVYMax) * 0.5f) {
            mAccVYType = EAccVYType_High;
        } else {
            mAccVYType = EAccVYType_Low;
        }
    } else {
        mAccVYType = EAccVYType_None;
    }
}

/**
 * @brief WPADGetInfoAsync callback
 *
 * @param chan Remote channel
 * @param result WPAD library result
 */
void RPSysCoreController::getInfoCallback(s32 chan, s32 result) {
    RPSysCoreController* p =
        RP_GET_INSTANCE(RPSysCoreControllerMgr)->findController(chan);

    if (p == NULL) {
        return;
    }

    if (result == WPAD_ERR_OK) {
        p->mCoreInfo.mFlags |= RPSysCoreInfo::EFlag_GetInfoSuccess;
    }

    p->mCoreInfo.mFlags |= RPSysCoreInfo::EFlag_GetInfoFail;
}

/**
 * @brief Attempts to read the controller information
 *
 * @return Success
 */
bool RPSysCoreController::requestCoreInfoAsync() {
    bool success = false;
    mCoreInfo.reset();

    s32 result = WPADGetInfoAsync(mChannelID, &mCoreInfo, getInfoCallback);
    if (result == WPAD_ERR_OK) {
        success = true;
    } else {
        mCoreInfo.mFlags |= RPSysCoreInfo::EFlag_GetInfoFail;
    }

    return success;
}
