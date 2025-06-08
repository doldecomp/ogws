#ifndef RVL_SDK_WPAD_H
#define RVL_SDK_WPAD_H
#include <types.h>

#include <revolution/SC.h>
#include <revolution/WUD.h>
#ifdef __cplusplus
extern "C" {
#endif

#define WPAD_MAX_DPD_OBJECTS 4

#define WPAD_MIN_DPD_SENS 1
#define WPAD_MAX_DPD_SENS 5

#define WPAD_MAX_DPD_X 1023
#define WPAD_MAX_DPD_Y 767

#define WPAD_MAX_SPEAKER_VOLUME 127

extern u8 _scFlush;

typedef WUDAllocFunc WPADAllocFunc;
typedef WUDFreeFunc WPADFreeFunc;

typedef void (*WPADCallback)(s32 chan, s32 result);
typedef void (*WPADSamplingCallback)(s32 chan);
typedef void (*WPADConnectCallback)(s32 chan, s32 result);
typedef void (*WPADExtensionCallback)(s32 chan, s32 dev);

typedef WUDSyncDeviceCallback WPADSyncDeviceCallback;
typedef WUDClearDeviceCallback WPADClearDeviceCallback;
typedef SCFlushCallback WPADSaveCallback;

typedef enum {
    WPAD_LIB_STATUS_0 = WUD_LIB_STATUS_0,
    WPAD_LIB_STATUS_1 = WUD_LIB_STATUS_1,
    WPAD_LIB_STATUS_2 = WUD_LIB_STATUS_2,
    WPAD_LIB_STATUS_3 = WUD_LIB_STATUS_3,
    WPAD_LIB_STATUS_4 = WUD_LIB_STATUS_4,
} WPADLibStatus;

typedef enum {
    WPAD_ERR_OK = 0,
    WPAD_ERR_NO_CONTROLLER = -1,
    WPAD_ERR_COMMUNICATION_ERROR = -2,
    WPAD_ERR_TRANSFER = -3,
    WPAD_ERR_INVALID = -4,
    WPAD_ERR_CORRUPTED = -7,

    WPAD_ERR_BUSY = WPAD_ERR_COMMUNICATION_ERROR,
} WPADResult;

typedef enum {
    WPAD_CHAN0,
    WPAD_CHAN1,
    WPAD_CHAN2,
    WPAD_CHAN3,

    WPAD_MAX_CONTROLLERS,
    WPAD_CHAN_INVALID = -1
} WPADChannel;

typedef enum {
    // Wii Remote (Core)
    WPAD_BUTTON_LEFT = (1 << 0),
    WPAD_BUTTON_RIGHT = (1 << 1),
    WPAD_BUTTON_DOWN = (1 << 2),
    WPAD_BUTTON_UP = (1 << 3),

    WPAD_BUTTON_A = (1 << 11),
    WPAD_BUTTON_B = (1 << 10),
    WPAD_BUTTON_1 = (1 << 9),
    WPAD_BUTTON_2 = (1 << 8),

    WPAD_BUTTON_PLUS = (1 << 4),
    WPAD_BUTTON_MINUS = (1 << 12),
    WPAD_BUTTON_HOME = (1 << 15),

    // Nunchuk (Free Style)
    WPAD_BUTTON_FS_Z = (1 << 13),
    WPAD_BUTTON_FS_C = (1 << 14),

    // Classic Controller
    WPAD_BUTTON_CL_LEFT = (1 << 1),
    WPAD_BUTTON_CL_RIGHT = (1 << 15),
    WPAD_BUTTON_CL_DOWN = (1 << 14),
    WPAD_BUTTON_CL_UP = (1 << 0),

    WPAD_BUTTON_CL_A = (1 << 4),
    WPAD_BUTTON_CL_B = (1 << 6),
    WPAD_BUTTON_CL_X = (1 << 3),
    WPAD_BUTTON_CL_Y = (1 << 5),
    WPAD_BUTTON_CL_ZL = (1 << 7),
    WPAD_BUTTON_CL_ZR = (1 << 2),

    WPAD_BUTTON_CL_L = (1 << 13),
    WPAD_BUTTON_CL_R = (1 << 9),

    WPAD_BUTTON_CL_PLUS = (1 << 10),
    WPAD_BUTTON_CL_MINUS = (1 << 12),
    WPAD_BUTTON_CL_HOME = (1 << 11),
} WPADButton;

typedef enum {
    WPAD_DEV_CORE,
    WPAD_DEV_FREESTYLE,
    WPAD_DEV_CLASSIC,

    WPAD_DEV_FUTURE = 251,
    WPAD_DEV_NOT_SUPPORTED = 252,
    WPAD_DEV_NOT_FOUND = 253,
    WPAD_DEV_NULL = 254,
    WPAD_DEV_UNKNOWN = 255,
} WPADDeviceType;

typedef enum {
    WPAD_FMT_CORE_BTN,
    WPAD_FMT_CORE_BTN_ACC,
    WPAD_FMT_CORE_BTN_ACC_DPD,

    WPAD_FMT_FS_BTN,
    WPAD_FMT_FS_BTN_ACC,
    WPAD_FMT_FS_BTN_ACC_DPD,

    WPAD_FMT_CLASSIC_BTN,
    WPAD_FMT_CLASSIC_BTN_ACC,
    WPAD_FMT_CLASSIC_BTN_ACC_DPD,

    WPAD_FMT_BTN_ACC_DPD_EXTENDED,
} WPADDataFormat;

typedef enum {
    WPAD_DEV_MODE_NORMAL,
    WPAD_DEV_MODE_CLASSIC_REDUCED,
    WPAD_DEV_MODE_CLASSIC_EXTENDED,
    WPAD_DEV_MODE_CLASSIC_STANDARD,
} WPADDeviceMode;

typedef enum {
    WPAD_MOTOR_STOP,
    WPAD_MOTOR_RUMBLE,
} WPADMotorCommand;

typedef enum {
    WPAD_SPEAKER_OFF,
    WPAD_SPEAKER_ON,
    WPAD_SPEAKER_MUTE,
    WPAD_SPEAKER_UNMUTE,
    WPAD_SPEAKER_PLAY,
    WPAD_SPEAKER_5
} WPADSpeakerCommand;

typedef enum {
    WPAD_DPD_DISABLE = 0x00,
    WPAD_DPD_BASIC = 0x01,
    WPAD_DPD_STANDARD = 0x03,
    WPAD_DPD_EXTENDED = 0x05,
} WPADDpdCommand;

typedef enum {
    WPAD_SENSOR_BAR_BOTTOM = SC_SENSOR_BAR_BOTTOM,
    WPAD_SENSOR_BAR_TOP = SC_SENSOR_BAR_TOP
} WPADSensorBarPos;

typedef enum {
    WPAD_MOTOR_OFF = SC_MOTOR_OFF,
    WPAD_MOTOR_ON = SC_MOTOR_ON
} WPADMotorMode;

typedef enum {
    WPAD_ACC_GRAVITY_UNIT_CORE,
    WPAD_ACC_GRAVITY_UNIT_FS,
} WPADAccGravityUnitType;

typedef struct DPDObject {
    s16 x;      // at 0x0
    s16 y;      // at 0x2
    u16 size;   // at 0x4
    u8 traceId; // at 0x6
} DPDObject;

typedef struct DPDObjEx {
    s16 range_x1; // at 0x0
    s16 range_y1; // at 0x2
    s16 range_x2; // at 0x4
    s16 range_y2; // at 0x6
    u16 pixel;    // at 0x8
    s8 radius;    // at 0xA
} DPDObjEx;

typedef struct WPADInfo {
    BOOL dpd;       // at 0x0
    BOOL speaker;   // at 0x4
    BOOL attach;    // at 0x8
    BOOL lowBat;    // at 0xC
    BOOL nearempty; // at 0x10
    u8 battery;     // at 0x14
    u8 led;         // at 0x15
    u8 protocol;    // at 0x16
    u8 firmware;    // at 0x17
} WPADInfo;

typedef struct WPADStatus {
    u16 button;                          // at 0x0
    s16 accX;                            // at 0x2
    s16 accY;                            // at 0x4
    s16 accZ;                            // at 0x6
    DPDObject obj[WPAD_MAX_DPD_OBJECTS]; // at 0x8
    u8 dev;                              // at 0x28
    s8 err;                              // at 0x29
} WPADStatus;

typedef struct WPADStatusEx {
    u16 button;                          // at 0x0
    s16 accX;                            // at 0x2
    s16 accY;                            // at 0x4
    s16 accZ;                            // at 0x6
    DPDObject obj[WPAD_MAX_DPD_OBJECTS]; // at 0x8
    u8 dev;                              // at 0x28
    s8 err;                              // at 0x29

    DPDObjEx exp[WPAD_MAX_DPD_OBJECTS]; // at 0x2A
} WPADStatusEx;

typedef struct WPADFSStatus {
    u16 button;                          // at 0x0
    s16 accX;                            // at 0x2
    s16 accY;                            // at 0x4
    s16 accZ;                            // at 0x6
    DPDObject obj[WPAD_MAX_DPD_OBJECTS]; // at 0x8
    u8 dev;                              // at 0x28
    s8 err;                              // at 0x29

    s16 fsAccX;  // at 0x2A
    s16 fsAccY;  // at 0x2C
    s16 fsAccZ;  // at 0x2E
    s8 fsStickX; // at 0x30
    s8 fsStickY; // at 0x31
} WPADFSStatus;

typedef struct WPADCLStatus {
    u16 button;                          // at 0x0
    s16 accX;                            // at 0x2
    s16 accY;                            // at 0x4
    s16 accZ;                            // at 0x6
    DPDObject obj[WPAD_MAX_DPD_OBJECTS]; // at 0x8
    u8 dev;                              // at 0x28
    s8 err;                              // at 0x29

    u16 clButton;  // at 0x2A
    s16 clLStickX; // at 0x2C
    s16 clLStickY; // at 0x2E
    s16 clRStickX; // at 0x30
    s16 clRStickY; // at 0x32
    u8 clTriggerL; // at 0x34
    u8 clTriggerR; // at 0x35
} WPADCLStatus;

typedef struct WPADAccGravityUnit {
    s16 x; // at 0x0
    s16 y; // at 0x2
    s16 z; // at 0x4
} WPADAccGravityUnit;

void WPADInit(void);
void WPADShutdown(void);

BOOL WPADStartSimpleSync(void);
BOOL WPADStartFastSimpleSync(void);
BOOL WPADStopSimpleSync(void);
BOOL WPADStartClearDevice(void);

WPADSyncDeviceCallback
WPADSetSimpleSyncCallback(WPADSyncDeviceCallback pCallback);

WPADClearDeviceCallback
WPADSetClearDeviceCallback(WPADClearDeviceCallback pCallback);

void WPADRegisterAllocator(WPADAllocFunc pAllocFunc, WPADFreeFunc pFreeFunc);
u32 WPADGetWorkMemorySize(void);

WPADLibStatus WPADGetStatus(void);
void WPADGetAddress(s32 chan, BD_ADDR_PTR pAddr);
u8 WPADGetSensorBarPosition(void);

void WPADGetAccGravityUnit(s32 chan, u32 type, WPADAccGravityUnit* pAcc);

void WPADDisconnect(s32 chan);
s32 WPADProbe(s32 chan, s32* pDevType);

WPADSamplingCallback WPADSetSamplingCallback(s32 chan,
                                             WPADSamplingCallback pCallback);
WPADConnectCallback WPADSetConnectCallback(s32 chan,
                                           WPADConnectCallback pCallback);
WPADExtensionCallback WPADSetExtensionCallback(s32 chan,
                                               WPADExtensionCallback pCallback);

u32 WPADGetDataFormat(s32 chan);
s32 WPADSetDataFormat(s32 chan, u32 format);

s32 WPADGetInfoAsync(s32 chan, WPADInfo* pInfo, WPADCallback pCallback);

void WPADControlMotor(s32 chan, u32 command);
void WPADEnableMotor(BOOL enable);
BOOL WPADIsMotorEnabled(void);

s32 WPADControlLed(s32 chan, u8 flags, WPADCallback pCallback);

BOOL WPADSaveConfig(WPADSaveCallback pCallback);

void WPADRead(s32 chan, WPADStatus* pStatus);
void WPADSetAutoSamplingBuf(s32 chan, void* pBuffer, u32 len);

BOOL WPADIsSpeakerEnabled(s32 chan);
s32 WPADControlSpeaker(s32 chan, u32 command, WPADCallback pCallback);
u8 WPADGetSpeakerVolume(void);
void WPADSetSpeakerVolume(u8 volume);

BOOL WPADCanSendStreamData(s32 chan);
s32 WPADSendStreamData(s32 chan, void* pData, u16 len);

u8 WPADGetDpdSensitivity(void);
BOOL WPADSetSensorBarPower(BOOL enable);
BOOL WPADIsDpdEnabled(s32 chan);
s32 WPADControlDpd(s32 chan, u32 command, WPADCallback pCallback);

void WPADRecalibrate(s32 chan);

//! /////////////////////////////////

s32 WPADReadFaceData(s32 chan, void* dst, u32 size, u32 src, WPADCallback cb);

//! /////////////////////////////////

#ifdef __cplusplus
}
#endif
#endif
