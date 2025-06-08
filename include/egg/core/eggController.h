#ifndef EGG_CORE_CONTROLLER_H
#define EGG_CORE_CONTROLLER_H
#include <egg/types_egg.h>

#include <egg/core/eggSingleton.h>

#include <egg/math.h>
#include <egg/prim.h>

#include <nw4r/ut.h>

#include <revolution/KPAD.h>
#include <revolution/PAD.h>
#include <revolution/WPAD.h>

namespace EGG {

// Forward declarations
class CoreController;
class ControllerRumbleMgr;

enum eCoreDevType {
    cDEV_CORE = WPAD_DEV_CORE,
    cDEV_FREESTYLE = WPAD_DEV_FREESTYLE,
    cDEV_CLASSIC = WPAD_DEV_CLASSIC,

    cDEV_FUTURE = WPAD_DEV_FUTURE,
    cDEV_NOT_SUPPORTED = WPAD_DEV_NOT_SUPPORTED,
    cDEV_NOT_FOUND = WPAD_DEV_NOT_FOUND,
    cDEV_NULL = WPAD_DEV_NULL,
    cDEV_UNKNOWN = WPAD_DEV_UNKNOWN,
};

enum eCoreButton {
    cCORE_BUTTON_UP = 1 << 3,
    cCORE_BUTTON_DOWN = 1 << 2,
    cCORE_BUTTON_LEFT = 1 << 0,
    cCORE_BUTTON_RIGHT = 1 << 1,

    cCORE_BUTTON_PLUS = 1 << 4,
    cCORE_BUTTON_MINUS = 1 << 12,

    cCORE_BUTTON_1 = 1 << 9,
    cCORE_BUTTON_2 = 1 << 8,

    cCORE_BUTTON_A = 1 << 11,
    cCORE_BUTTON_B = 1 << 10,

    cCORE_BUTTON_HOME = 1 << 15,

    cCORE_FSSTICK_UP = 1 << 16,
    cCORE_FSSTICK_DOWN = 1 << 17,
    cCORE_FSSTICK_LEFT = 1 << 18,
    cCORE_FSSTICK_RIGHT = 1 << 19,

    cCORE_FSSTICK_BUTTONS = cCORE_FSSTICK_UP | cCORE_FSSTICK_DOWN |
                            cCORE_FSSTICK_LEFT | cCORE_FSSTICK_RIGHT
};

typedef CoreController* (*CoreControllerFactory)();

struct CoreControllerConnectArg {
    s32 chan;   // at 0x0
    s32 result; // at 0x4
};

typedef void (*CoreControllerConnectCallback)(
    const CoreControllerConnectArg& rArg);

struct CoreControllerExtensionArg {
    eCoreDevType newDevType; // at 0x0
    eCoreDevType oldDevType; // at 0x4
    s32 chan;                // at 0x8
};

class CoreControllerExtensionCallback {
public:
    virtual void onConnect(const CoreControllerExtensionArg& rArg); // at 0x8
};

/******************************************************************************
 *
 * CoreStatus
 *
 ******************************************************************************/
class CoreStatus : public KPADStatus {
    friend class CoreController;

public:
    CoreStatus() {}

    u32 getHold() const {
        return hold;
    }
    u32 getRelease() const {
        return release;
    }
    u32 getTrigger() const {
        return trig;
    }

    bool down(u32 buttons) const {
        return hold & buttons;
    }
    bool up(u32 buttons) const {
        return (hold & buttons) != buttons;
    }

    bool downTrigger(u32 buttons) const {
        return trig & buttons;
    }
    bool upTrigger(u32 buttons) const {
        return release & buttons;
    }

    Vector3f getAccel() const {
        return Vector3f(acc.x, acc.y, acc.z);
    }

    eCoreDevType getDevType() const {
        return static_cast<eCoreDevType>(dev_type);
    }

    bool isCore() const {
        return getDevType() == WPAD_DEV_CORE || isFreestyle();
    }
    bool isFreestyle() const {
        return getDevType() == WPAD_DEV_FREESTYLE;
    }

    s8 getDPDValidFlag() const {
        return dpd_valid_fg;
    }

    f32 getFSStickX() const {
        return ex_status.fs.stick.x;
    }
    f32 getFSStickY() const {
        return ex_status.fs.stick.y;
    }

    u32 getFSStickButton();
};

/******************************************************************************
 *
 * CoreController
 *
 ******************************************************************************/
class CoreController {
    friend class CoreControllerMgr;

public:
    CoreController();

    virtual void setPosParam(f32 playRadius, f32 sensitivity) {
        KPADSetPosParam(mChannelID, playRadius, sensitivity);
    } // at 0x8
    virtual void setHoriParam(f32 playRadius, f32 sensitivity) {
        KPADSetHoriParam(mChannelID, playRadius, sensitivity);
    } // at 0xC
    virtual void setDistParam(f32 playRadius, f32 sensitivity) {
        KPADSetDistParam(mChannelID, playRadius, sensitivity);
    } // at 0x10
    virtual void setAccParam(f32 playRadius, f32 sensitivity) {
        KPADSetAccParam(mChannelID, playRadius, sensitivity);
    } // at 0x14

    virtual void beginFrame(PADStatus* pStatus = NULL); // at 0x18
    virtual void endFrame();                            // at 0x1C

    s32 getChannelID() const {
        return mChannelID;
    }

    bool down(u32 buttons) const {
        return mCoreStatus[0].down(buttons);
    }
    bool up(u32 buttons) const {
        return mCoreStatus[0].up(buttons);
    }

    bool downTrigger(u32 buttons) const {
        return mCoreStatus[0].downTrigger(buttons);
    }
    bool upTrigger(u32 buttons) const {
        return mCoreStatus[0].upTrigger(buttons);
    }

    Vector3f getAccel() const {
        return mCoreStatus[0].getAccel();
    }

    eCoreDevType getDevType() const {
        return mCoreStatus[0].getDevType();
    }

    bool isCore() const {
        return mCoreStatus[0].isCore();
    }
    bool isFreestyle() const {
        return mCoreStatus[0].isFreestyle();
    }

    s32 getReadLength() const {
        return mKPADReadLength;
    }

    bool isStable(u8 bits) const {
        return (mStableFlags & bits) == bits;
    }

    void setStableFrame(int frame) {
        mStableFrame = frame;
    }
    void setStableMag(f32 mag) {
        mStableMag = mag;
    }

    void sceneReset();

    void startMotor();
    void stopMotor();

    void createRumbleMgr(u8 overlap_num);
    void startPatternRumble(const char* pPattern, int frame, bool force);
    void startPowerFrameRumble(f32 power, int frame, bool force);
    void stopRumbleMgr();

    CoreStatus* getCoreStatus(int index);
    CoreStatus* getCoreStatus() {
        return getCoreStatus(0);
    }

private:
    enum StableAxis {
        STABLE_AXIS_X,
        STABLE_AXIS_Y,
        STABLE_AXIS_Z,

        STABLE_AXIS_MAX
    };

    enum StableFlag {
        STABLE_FLAG_X = 1 << STABLE_AXIS_X,
        STABLE_FLAG_Y = 1 << STABLE_AXIS_Y,
        STABLE_FLAG_Z = 1 << STABLE_AXIS_Z,

        STABLE_FLAG_XYZ = STABLE_FLAG_X | STABLE_FLAG_Y | STABLE_FLAG_Z
    };

private:
    void calc_posture_matrix(Matrix34f& rPostureMtx, bool checkStable);

private:
    s32 mChannelID; // at 0x4

    u32 mFSStickHold;    // at 0x8
    u32 mFSStickTrig;    // at 0xC
    u32 mFSStickRelease; // at 0x10

    CoreStatus mCoreStatus[KPAD_MAX_SAMPLES]; // at 0x14
    s32 mKPADReadLength;                      // at 0x854
    Vector3f mAccelPrev;                      // at 0x858

    u32 mSimpleRumblePattern;        // at 0x864
    bool mEnableSimpleRumble;        // at 0x868
    int mSimpleRumbleFrame;          // at 0x86C
    u8 mSimpleRumbleSize;            // at 0x870
    u8 mSimpleRumbleIndex;           // at 0x871
    ControllerRumbleMgr* mRumbleMgr; // at 0x874

    Matrix34f mPostureMtx;     // at 0x878
    Matrix34f mPostureMtxPrev; // at 0x8A8

    u8 mStableFlags;                   // at 0x8D8
    int mStableFrame;                  // at 0x8DC
    int mStableTimer[STABLE_AXIS_MAX]; // at 0x8E0
    f32 mStableMag;                    // at 0x8EC
    Vector3f mStableAccel;             // at 0x8F0
};

/******************************************************************************
 *
 * NullController
 *
 ******************************************************************************/
class NullController : public CoreController {
public:
    NullController() : mDevType(cDEV_NULL) {}

private:
    char UNK_0x8FC[0x958 - 0x8FC];
    u8 mDevType; // at 0x958
    char UNK_0x95C[0x980 - 0x95C];
};

/******************************************************************************
 *
 * CoreControllerMgr
 *
 ******************************************************************************/
class CoreControllerMgr {
    EGG_SINGLETON_DECL(CoreControllerMgr);

public:
    virtual void beginFrame(); // at 0x8
    virtual void endFrame();   // at 0xC

    CoreController* getNthController(int index);

private:
    CoreControllerMgr();

    static void connectCallback(s32 chan, s32 result);

private:
    TBuffer<CoreController*> mControllers;               // at 0x14
    CoreControllerExtensionCallback* mExtensionCallback; // at 0x20
    TBuffer<eCoreDevType> mDevTypes;                     // at 0x24

    static CoreControllerFactory sCoreControllerFactory;
    static CoreControllerConnectCallback sConnectCallback;
    static u32 sWPADWorkSize;
};

/******************************************************************************
 *
 * ControllerRumbleUnit
 *
 ******************************************************************************/
class ControllerRumbleUnit {
    friend class ControllerRumbleMgr;

public:
    ControllerRumbleUnit() {
        init();
    }

    virtual ~ControllerRumbleUnit() {} // at 0x8

    void startPattern(const char* pPattern, int frame);
    void startPowerFrame(f32 power, int frame);

    f32 calc();

private:
    enum {
        BIT_USE_PATTERN,
        BIT_USE_POWER,

        BIT_POWER_LOOP,
        BIT_ENABLED,
        BIT_PATTERN_LOOP,
        BIT_PATTERN_TIMER,
    };

private:
    void init();

    void setFlags(u8 bit) {
        mFlags.setBit(bit);
    }
    void clrFlags(u8 bit) {
        mFlags.resetBit(bit);
    }
    bool tstFlags(u8 bit) {
        return mFlags.onBit(bit);
    }

private:
    const char* mRumblePattern;    // at 0x4
    const char* mRumblePatternPtr; // at 0x8
    int mRumbleFrame;              // at 0xC
    f32 mRumblePower;              // at 0x10
    f32 mRumbleValue;              // at 0x14
    TBitFlag<u8> mFlags;           // at 0x18
    NW4R_UT_LIST_LINK_DECL();      // at 0x1C
    char UNK_0x24[0x28 - 0x24];
};

/******************************************************************************
 *
 * ControllerRumbleMgr
 *
 ******************************************************************************/
class ControllerRumbleMgr {
public:
    ControllerRumbleMgr();
    virtual ~ControllerRumbleMgr() {} // at 0x8

    void createUnit(u8 overlap_num, CoreController* pController);

    void stop();
    void calc();

    void startPattern(const char* pPattern, int frame, bool force);
    void startPowerFrame(f32 power, int frame, bool force);

private:
    ControllerRumbleUnit* getUnitFromList(bool force);

private:
    nw4r::ut::List mActiveUnitList;  // at 0x0
    nw4r::ut::List mStoppedUnitList; // at 0x10
    CoreController* mController;     // at 0x14
};

} // namespace EGG

#endif
