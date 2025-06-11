// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>
#include <egg/math.h>
#include <egg/prim.h>

#include <revolution/KPAD.h>
#include <revolution/VI.h>
#include <revolution/WPAD.h>
#include <revolution/WUD.h>

namespace EGG {

NullController sNullGCCont;

/******************************************************************************
 *
 * CoreStatus
 *
 ******************************************************************************/
u32 CoreStatus::getFSStickButton() {
    u32 buttons = 0;

#line 53
    EGG_ASSERT_MSG(isFreestyle(), "This Status is not for Free Style");

    f32 sx = getFSStickX();
    if (!(-0.25f < sx && sx < 0.25f)) {
        if (sx <= -0.5f) {
            buttons = 0;
            buttons |= cCORE_FSSTICK_LEFT;
        } else if (sx >= 0.5f) {
            buttons = 0;
            buttons |= cCORE_FSSTICK_RIGHT;
        }
    }

    f32 sy = getFSStickY();
    if (!(-0.25f < sy && sy < 0.25f)) {
        if (sy <= -0.5f) {
            buttons &= ~cCORE_FSSTICK_UP;
            buttons |= cCORE_FSSTICK_DOWN;
        } else if (sy >= 0.5f) {
            buttons &= ~cCORE_FSSTICK_DOWN;
            buttons |= cCORE_FSSTICK_UP;
        }
    }

    return buttons;
}

/******************************************************************************
 *
 * CoreController
 *
 ******************************************************************************/
CoreController::CoreController() : mRumbleMgr(NULL) {
    mFSStickHold = 0;
    mFSStickTrig = 0;
    mFSStickRelease = 0;

    sceneReset();
}

void CoreController::sceneReset() {
    mAccelPrev.set(0.0f, 0.0f, 0.0f);

    mPostureMtxPrev.makeIdentity();
    mPostureMtx.makeIdentity();

    setStableFrame(10);
    setStableMag(0.13f);

    mStableAccel.set(0.0, 0.0, 0.0);
    mStableFlags = 0;
    mStableTimer[0] = mStableTimer[1] = mStableTimer[2] = 0;

    mSimpleRumblePattern = 0;
    mSimpleRumbleFrame = 0;
    mEnableSimpleRumble = false;
    mSimpleRumbleSize = 32;
    mSimpleRumbleIndex = mSimpleRumbleSize - 1;

    stopRumbleMgr();
}

void CoreController::startMotor() {
    WPADControlMotor(mChannelID, WPAD_MOTOR_ON);
}

void CoreController::stopMotor() {
    WPADControlMotor(mChannelID, WPAD_MOTOR_OFF);
}

DECOMP_FORCEACTIVE(eggController_cpp,
                  "bit_num > 0 && bit_num <= 32");

void CoreController::createRumbleMgr(u8 overlap_num) {
#line 261
    EGG_ASSERT(mRumbleMgr == NULL);
    mRumbleMgr = new ControllerRumbleMgr();

#line 263
    EGG_ASSERT(overlap_num > 0);
    mRumbleMgr->createUnit(overlap_num, this);
}

void CoreController::startPatternRumble(const char* pPattern, int frame,
                                        bool force) {

    if (mRumbleMgr != NULL) {
        mRumbleMgr->startPattern(pPattern, frame, force);
    }
}

void CoreController::startPowerFrameRumble(f32 power, int frame, bool force) {
    if (mRumbleMgr != NULL) {
        mRumbleMgr->startPowerFrame(power, frame, force);
    }
}

void CoreController::stopRumbleMgr() {
    if (mRumbleMgr != NULL) {
        mRumbleMgr->stop();
    }
}

CoreStatus* CoreController::getCoreStatus(int index) {
#line 312
    EGG_ASSERT(index >= 0 && index < mKPADReadLength);
    return &mCoreStatus[index];
}

void CoreController::calc_posture_matrix(Matrix34f& rPostureMtx,
                                         bool checkStable) {

    if (checkStable && !isStable(STABLE_FLAG_XYZ)) {
        return;
    }

    Vector3f acc = -getAccel();

    Vector3f vy = acc;
    vy.normalise();

    Vector3f vz(0.0f, 0.0f, 1.0f);
    Vector3f vx(1.0f, 0.0f, 0.0f);

    Vector3f bx, by, bz;
    mPostureMtxPrev.getBase(0, bx);
    mPostureMtxPrev.getBase(1, by);
    mPostureMtxPrev.getBase(2, bz);

    Vector3f vz_n(0.0f, 0.0f, -1.0f);
    Vector3f vx_n(-1.0f, 0.0f, 0.0f);

    if (vz.dot(bz) < vz_n.dot(bz)) {
        vz = vz_n;
    }

    if (vx.dot(bx) < vx_n.dot(bx)) {
        vx = vx_n;
    }

    if (Math<f32>::abs(vy.dot(vz)) < Math<f32>::abs(vy.dot(vx))) {
        vx = vy.cross(vz);
        vx.normalise();
        vz = vx.cross(vy);
        vz.normalise();
    } else {
        vz = vx.cross(vy);
        vz.normalise();
        vx = vy.cross(vz);
        vx.normalise();
    }

    rPostureMtx.setBase(0, vx);
    rPostureMtx.setBase(1, vy);
    rPostureMtx.setBase(2, vz);
}

void CoreController::beginFrame(PADStatus* pStatus) {
#pragma unused(pStatus)

    mKPADReadLength =
        KPADRead(mChannelID, mCoreStatus, ARRAY_SIZE(mCoreStatus));

    if (mKPADReadLength > 0) {
        CoreStatus* coreStatus = &mCoreStatus[0];
        u32 stickHoldPrev = mFSStickHold;

        if (isFreestyle()) {
            mFSStickHold = coreStatus->getFSStickButton();
        } else {
            mFSStickHold = 0;
        }

        mFSStickTrig = mFSStickHold & ~stickHoldPrev;
        mFSStickRelease = stickHoldPrev & ~mFSStickHold;

#line 539
        EGG_ASSERT((coreStatus->hold & cCORE_FSSTICK_BUTTONS) == 0);
        EGG_ASSERT((coreStatus->trig & cCORE_FSSTICK_BUTTONS) == 0);
        EGG_ASSERT((coreStatus->release & cCORE_FSSTICK_BUTTONS) == 0);

        coreStatus->hold |= (mFSStickHold & cCORE_FSSTICK_BUTTONS);
        coreStatus->trig |= (mFSStickTrig & cCORE_FSSTICK_BUTTONS);
        coreStatus->release |= (mFSStickRelease & cCORE_FSSTICK_BUTTONS);
    }

    mPostureMtxPrev = mPostureMtx;
    mStableFlags = 0;

    Vector3f accel = getAccel();

    for (int i = 0; i < STABLE_AXIS_MAX; i++) {
        if (accel(i) - mAccelPrev(i) < mStableMag) {
            if (mStableFrame <= ++mStableTimer[i]) {
                mStableTimer[i] = mStableFrame;
                mStableFlags |= 1 << i;
                mStableAccel(i) = accel(i);
            }
        } else {
            mStableFlags &= ~(1 << i);
            mStableTimer[i] = 0;
        }
    }

    calc_posture_matrix(mPostureMtx, true);

    if (mEnableSimpleRumble) {
        if (mSimpleRumblePattern & (1 << mSimpleRumbleIndex)) {
            startMotor();
        } else {
            stopMotor();
        }

        if (mSimpleRumbleIndex <= 0) {
            mSimpleRumbleIndex = mSimpleRumbleSize - 1;
        } else {
            mSimpleRumbleIndex--;
        }

        if (--mSimpleRumbleFrame == 0) {
            stopMotor();
            mEnableSimpleRumble = false;
        }
    }

    if (mRumbleMgr != NULL) {
        mRumbleMgr->calc();
    }
}

void CoreController::endFrame() {
    mAccelPrev = getAccel();
}

/******************************************************************************
 *
 * CoreControllerMgr
 *
 ******************************************************************************/
EGG_SINGLETON_IMPL(CoreControllerMgr);

CoreControllerFactory CoreControllerMgr::sCoreControllerFactory = NULL;
CoreControllerConnectCallback CoreControllerMgr::sConnectCallback = NULL;
u32 CoreControllerMgr::sWPADWorkSize = 0x32000;

CoreController* CoreControllerMgr::getNthController(int index) {
    return mControllers(index);
}

namespace {

Allocator* sAllocator = NULL;

void* alloc(u32 size) {
    return sAllocator->alloc(size);
}

BOOL free(void* pBlock) {
    sAllocator->free(pBlock);
    return TRUE;
}

} // namespace

void CoreControllerMgr::connectCallback(s32 chan, s32 result) {
    CoreControllerConnectArg arg;
    arg.chan = chan;
    arg.result = result;

    if (sConnectCallback != NULL) {
        sConnectCallback(arg);
    }
}

CoreControllerMgr::CoreControllerMgr() {
    s32 channels[WPAD_MAX_CONTROLLERS] = {
        WPAD_CHAN0,
        WPAD_CHAN1,
        WPAD_CHAN2,
        WPAD_CHAN3,
    };

    ExpHeap* pHeap =
        ExpHeap::create(sWPADWorkSize, BaseSystem::getRootHeapMem2());

    sAllocator = new Allocator(pHeap);
    WPADRegisterAllocator(alloc, free);

    KPADInit();

    beginFrame();
    endFrame();

    VIWaitForRetrace();

    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        WPADSetConnectCallback(channels[i], connectCallback);
    }

    mControllers.allocate(WPAD_MAX_CONTROLLERS);

    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        if (sCoreControllerFactory != NULL) {
            mControllers(i) = sCoreControllerFactory();
        } else {
            mControllers(i) = new CoreController();
        }
    }

    mDevTypes.allocate(WPAD_MAX_CONTROLLERS);

    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        mControllers(i)->mChannelID = channels[i];
        mDevTypes(i) = cDEV_NOT_FOUND;
    }

    mExtensionCallback = NULL;
}

void CoreControllerMgr::beginFrame() {
    for (int i = 0; i < mControllers.getSize(); i++) {
        mControllers(i)->beginFrame();
    }
}

void CoreControllerMgr::endFrame() {
    for (int i = 0; i < mControllers.getSize(); i++) {
        mControllers(i)->endFrame();

        s32 devType;
        s32 result = WPADProbe(i, &devType);

        eCoreDevType coreType;
        if (result == WPAD_ERR_OK) {
            coreType = static_cast<eCoreDevType>(devType);
        } else if (result == WPAD_ERR_NO_CONTROLLER) {
            coreType = cDEV_NOT_FOUND;
        } else {
            continue;
        }

        if (mExtensionCallback != NULL && coreType != mDevTypes(i)) {
            CoreControllerExtensionArg arg;
            arg.newDevType = coreType;
            arg.oldDevType = mDevTypes(i);
            arg.chan = i;

            mExtensionCallback->onConnect(arg);
        }

        mDevTypes(i) = coreType;
    }
}

/******************************************************************************
 *
 * ControllerRumbleUnit
 *
 ******************************************************************************/
void ControllerRumbleUnit::init() {
    mRumblePattern = NULL;
    mRumblePatternPtr = NULL;

    mRumbleFrame = 0;
    mRumblePower = mRumbleValue = 0.0f;

    mFlags = 0;
}

void ControllerRumbleUnit::startPattern(const char* pPattern, int frame) {
    mRumblePattern = pPattern;
    mRumblePatternPtr = pPattern;

    clrFlags(BIT_PATTERN_LOOP);
    clrFlags(BIT_PATTERN_TIMER);

    if (frame < 0) {
        setFlags(BIT_PATTERN_LOOP);
    } else if (frame > 0) {
        setFlags(BIT_PATTERN_LOOP);
        setFlags(BIT_PATTERN_TIMER);
    }

    setFlags(BIT_USE_PATTERN);
    clrFlags(BIT_USE_POWER);
    setFlags(BIT_ENABLED);

    mRumbleFrame = frame;
}

void ControllerRumbleUnit::startPowerFrame(f32 power, int frame) {
    mRumblePower = power;
    mRumbleFrame = frame;
    mRumbleValue = 0.0f;

    setFlags(BIT_USE_POWER);
    clrFlags(BIT_USE_PATTERN);
    setFlags(BIT_ENABLED);

    if (frame < 0) {
        setFlags(BIT_POWER_LOOP);
    }
}

f32 ControllerRumbleUnit::calc() {
    f32 result = 0.0f;

    if (tstFlags(BIT_ENABLED)) {
        // Pattern rumble type
        if (tstFlags(BIT_USE_PATTERN)) {
            // @bug First pattern character is skipped
            char ch = *++mRumblePatternPtr;

            if (ch == '\0') {
                if (tstFlags(BIT_PATTERN_LOOP)) {
                    mRumblePatternPtr = mRumblePattern;
                } else {
                    clrFlags(BIT_ENABLED);
                }
            } else {
                switch (ch) {
                case '*': {
                    result = 1.0f;
                }

                case '-':
                default: {
                    break;
                }
                }
            }

            if (tstFlags(BIT_PATTERN_TIMER) && --mRumbleFrame <= 0) {
                clrFlags(BIT_ENABLED);
            }

            return result;
        }
        // Power rumble type
        else {
            mRumbleValue += mRumblePower;

            if (mRumbleValue >= 1.0f) {
                result = 1.0f;
                mRumbleValue = 0.0f;
            }

            if (!tstFlags(BIT_POWER_LOOP) && --mRumbleFrame <= 0) {
                clrFlags(BIT_ENABLED);
            }

            return result;
        }
    }

    return -1.0f;
}

/******************************************************************************
 *
 * ControllerRumbleMgr
 *
 ******************************************************************************/
ControllerRumbleMgr::ControllerRumbleMgr() : mController(NULL) {
    NW4R_UT_LIST_INIT(mActiveUnitList, ControllerRumbleUnit);
    NW4R_UT_LIST_INIT(mStoppedUnitList, ControllerRumbleUnit);
}

void ControllerRumbleMgr::createUnit(u8 overlap_num,
                                     CoreController* pController) {

    for (u8 i = 0; i < overlap_num; i++) {
        nw4r::ut::List_Append(&mStoppedUnitList, new ControllerRumbleUnit());
    }

    mController = pController;
}

void ControllerRumbleMgr::stop() {
    mController->stopMotor();

    while (nw4r::ut::List_GetSize(&mActiveUnitList) > 0) {
        ControllerRumbleUnit* pUnit = static_cast<ControllerRumbleUnit*>(
            nw4r::ut::List_GetFirst(&mActiveUnitList));

        nw4r::ut::List_Remove(&mActiveUnitList, pUnit);
        nw4r::ut::List_Append(&mStoppedUnitList, pUnit);
    }
}

void ControllerRumbleMgr::calc() {
    if (nw4r::ut::List_GetSize(&mActiveUnitList) == 0) {
        return;
    }

    ControllerRumbleUnit* pUnit = static_cast<ControllerRumbleUnit*>(
        nw4r::ut::List_GetFirst(&mActiveUnitList));

    f32 totalPower = 0.0f;

    while (pUnit != NULL) {
        f32 unitPower = pUnit->calc();

        ControllerRumbleUnit* pNext = static_cast<ControllerRumbleUnit*>(
            nw4r::ut::List_GetNext(&mActiveUnitList, pUnit));

        if (unitPower < 0.0f) {
            nw4r::ut::List_Remove(&mActiveUnitList, pUnit);
            nw4r::ut::List_Append(&mStoppedUnitList, pUnit);
        } else {
            totalPower += unitPower;
        }

        pUnit = pNext;
    }

    if (totalPower >= 1.0f) {
        mController->startMotor();
    } else {
        mController->stopMotor();
    }
}

void ControllerRumbleMgr::startPattern(const char* pPattern, int frame,
                                       bool force) {

    ControllerRumbleUnit* pUnit = getUnitFromList(force);
    if (pUnit == NULL) {
        return;
    }

    pUnit->startPattern(pPattern, frame);
}

void ControllerRumbleMgr::startPowerFrame(f32 power, int frame, bool force) {
    ControllerRumbleUnit* pUnit = getUnitFromList(force);
    if (pUnit == NULL) {
        return;
    }

    pUnit->startPowerFrame(power, frame);
}

ControllerRumbleUnit* ControllerRumbleMgr::getUnitFromList(bool force) {
    ControllerRumbleUnit* pUnit = static_cast<ControllerRumbleUnit*>(
        nw4r::ut::List_GetFirst(&mStoppedUnitList));

    if (pUnit != NULL) {
        nw4r::ut::List_Remove(&mStoppedUnitList, pUnit);
        nw4r::ut::List_Append(&mActiveUnitList, pUnit);
    } else if (force) {
        // Recycle the oldest active rumble unit
        pUnit = static_cast<ControllerRumbleUnit*>(
            nw4r::ut::List_GetFirst(&mActiveUnitList));

        if (pUnit != NULL) {
            nw4r::ut::List_Remove(&mActiveUnitList, pUnit);
            nw4r::ut::List_Append(&mActiveUnitList, pUnit);
        }
    }

    return pUnit;
}

DECOMP_FORCEACTIVE(eggController_cpp,
                  "getDevType() == cDEV_DOLPHIN",
                  "c",
                  "0 <= channel && channel < 4");

} // namespace EGG
