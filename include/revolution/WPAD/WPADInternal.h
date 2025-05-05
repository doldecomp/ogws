#ifndef RVL_SDK_WPAD_INTERNAL_H
#define RVL_SDK_WPAD_INTERNAL_H
#include <types.h>

// Public API
#include <revolution/WPAD/WPAD.h>
#include <revolution/WPAD/WPADHIDParser.h>
#include <revolution/WPAD/WPADMem.h>
#ifdef __cplusplus
extern "C" {
#endif

#define RX_BUFFER_SIZE ROUND_UP(sizeof(WPADStatusEx), 32)

#define WPAD_CONFIG_BLOCK_CHECKSUM_BIAS 0x55
#define WPAD_MAX_CONFIG_BLOCKS 2

#define WPAD_DPD_CONFIG_BLOCK_CHECKSUM 10
#define WPAD_DPD_CONFIG_BLOCK_SIZE 11

#define WPAD_DEV_CONFIG_BLOCK_CHECKSUM 9
#define WPAD_DEV_CONFIG_BLOCK_SIZE 10

#define DPD_CFG_OBJ_BL 0
#define DPD_CFG_OBJ_BR 1
#define DPD_CFG_OBJ_TR 2
#define DPD_CFG_OBJ_TL 3

/*
 * Wiimote memory addresses
 */
// clang-format off
#define WM_ADDR_MEM_DEV_CONFIG_0 WM_MEM_ADDR(0x0000)
#define WM_ADDR_MEM_GAME_INFO_0  WM_MEM_ADDR(0x002A)
#define WM_ADDR_MEM_GAME_INFO_1  WM_MEM_ADDR(0x0062)
#define WM_ADDR_MEM_176C         WM_MEM_ADDR(0x176C)
#define WM_ADDR_MEM_1770         WM_MEM_ADDR(0x1770)
// clang-format on

/*
 * Wiimote extension register addresses
 */
// clang-format off
// Speaker register addresses
#define WM_REG_SPEAKER_01 WM_EXT_REG_ADDR(SPEAKER, 0x01)
#define WM_REG_SPEAKER_08 WM_EXT_REG_ADDR(SPEAKER, 0x08)
#define WM_REG_SPEAKER_09 WM_EXT_REG_ADDR(SPEAKER, 0x09)

// Extension register addresses
#define WM_REG_EXTENSION_CONFIG         WM_EXT_REG_ADDR(EXTENSION, 0x20)
#define WM_REG_EXTENSION_40             WM_EXT_REG_ADDR(EXTENSION, 0x40)
#define WM_REG_EXTENSION_CERT_PARAM     WM_EXT_REG_ADDR(EXTENSION, 0x50)
#define WM_REG_EXTENSION_F0             WM_EXT_REG_ADDR(EXTENSION, 0xF0)
#define WM_REG_EXTENSION_CERT_CHALLENGE WM_EXT_REG_ADDR(EXTENSION, 0xF1)
#define WM_REG_EXTENSION_F2             WM_EXT_REG_ADDR(EXTENSION, 0xF2)
#define WM_REG_EXTENSION_F3             WM_EXT_REG_ADDR(EXTENSION, 0xF3)
#define WM_REG_EXTENSION_EXT_TYPE_2     WM_EXT_REG_ADDR(EXTENSION, 0xF6)
#define WM_REG_EXTENSION_CERT_PROBE     WM_EXT_REG_ADDR(EXTENSION, 0xF7)
#define WM_REG_EXTENSION_FA             WM_EXT_REG_ADDR(EXTENSION, 0xFA)
#define WM_REG_EXTENSION_FB             WM_EXT_REG_ADDR(EXTENSION, 0xFB)
#define WM_REG_EXTENSION_DEV_MODE       WM_EXT_REG_ADDR(EXTENSION, 0xFE)
#define WM_REG_EXTENSION_ID_BYTE        WM_EXT_REG_ADDR(EXTENSION, 0xFF)

// IR camera register addresses
#define WM_REG_DPD_CONFIG_BLOCK_1 WM_EXT_REG_ADDR(DPD, 0x00)
#define WM_REG_DPD_CONFIG_BLOCK_2 WM_EXT_REG_ADDR(DPD, 0x1A)
#define WM_REG_DPD_30             WM_EXT_REG_ADDR(DPD, 0x30)
#define WM_REG_DPD_DATA_FORMAT    WM_EXT_REG_ADDR(DPD, 0x33)
// clang-format on

#define WM_EXTENSION_CONFIG_SIZE 0x20 // 0xA40020 - 0xA4003F

typedef enum {
    WPAD_STATE_EXT_UNINITIALIZED,
    WPAD_STATE_EXT_INITIALIZED,
    WPAD_STATE_EXT_ENCRYPTED,
    WPAD_STATE_EXT_ENCRYPTED_3RD,
} WPADExtensionState;

typedef enum {
    WPAD_RADIO_QUALITY_GOOD, // 80+
    WPAD_RADIO_QUALITY_BAD   // 80-
    // if radioQuality calculation == 80, state stays the same
} WPADRadioQuality;

typedef enum {
    WPAD_ILBUF_NONE = 0,

    WPAD_ILBUF_BUF3E = (1 << 0),
    WPAD_ILBUF_BUF3F = (1 << 1),

    WPAD_ILBUF_ALL = WPAD_ILBUF_BUF3E | WPAD_ILBUF_BUF3F,
} WPADInterleaveBufferFlags;

typedef struct WPADCommand {
    u32 reportID;              // at 0x0
    u8 dataBuf[RPT_MAX_SIZE];  // at 0x4
    u16 dataLength;            // at 0x1A
    void* dstBuf;              // at 0x1C
    u16 readLength;            // at 0x20
    u32 readAddress;           // at 0x24
    WPADInfo* statusReportOut; // at 0x28
    WPADCallback cmdCB;        // at 0x2C
} WPADCommand;

typedef struct WPADCommandQueue {
    s8 front;            // at 0x1
    s8 back;             // at 0x0
    WPADCommand* buffer; // at 0x4
    u32 capacity;        // at 0x8
} WPADCommandQueue;

typedef struct WPADDevConfig {
    DPDObject dpd[WPAD_MAX_DPD_OBJECTS]; // at 0x0

    s16 accX0g; // at 0x20
    s16 accY0g; // at 0x22
    s16 accZ0g; // at 0x24

    s16 accX1g; // at 0x26
    s16 accY1g; // at 0x28
    s16 accZ1g; // at 0x2A

    u8 motor;  // at 0x2C
    u8 volume; // at 0x2D
} WPADDevConfig;

typedef struct WPADExtConfig {
    union {
        struct WPADFSConfig {
            s16 stickXCenter; // at 0x0
            s16 at_0x02;      // at 0x2
            s16 at_0x04;      // at 0x4
            s16 stickYCenter; // at 0x6
            s16 at_0x08;      // at 0x8
            s16 at_0x0a;      // at 0xA

            s16 accX0g; // at 0xC
            s16 accY0g; // at 0xE
            s16 accZ0g; // at 0x10

            s16 accX1g; // at 0x12
            s16 accY1g; // at 0x14
            s16 accZ1g; // at 0x16
        } fs;

        struct WPADCLConfig {
            s16 lStickXCenter; // at 0x0
            s16 at_0x02;       // at 0x2
            s16 at_0x04;       // at 0x4
            s16 lStickYCenter; // at 0x6
            s16 at_0x08;       // at 0x8
            s16 at_0x0a;       // at 0xA

            s16 rStickXCenter; // at 0xC
            s16 at_0x0e;       // at 0xE
            s16 at_0x10;       // at 0x10
            s16 rStickYCenter; // at 0x12
            s16 at_0x14;       // at 0x14
            s16 at_0x16;       // at 0x16

            u8 triggerLZero; // at 0x18
            u8 triggerRZero; // at 0x19
        } cl;
    };
} WPADExtConfig;

typedef struct WPADCB {
    WPADGameInfo gameInfo; // at 0x0
    s32 UNK_0x38[2];
    u8 rxBufMain[RX_BUFFER_SIZE];      // at 0x40
    u8 rxBufs[2][RX_BUFFER_SIZE];      // at 0xA0
    WPADCommandQueue stdCmdQueue;      // at 0x160
    WPADCommand stdCmdQueueList[24];   // at 0x16C
    WPADCommandQueue extCmdQueue;      // at 0x5EC
    WPADCommand extCmdQueueList[12];   // at 0x5F8
    WPADInfo wpInfo;                   // at 0x838
    WPADInfo* wpInfoOut;               // at 0x850
    WPADDevConfig devConfig;           // at 0x854
    WPADExtConfig extConfig;           // at 0x882
    WPADCallback cmdBlkCB;             // at 0x89C
    WPADExtensionCallback extensionCB; // at 0x8A0
    WPADConnectCallback connectCB;     // at 0x8A4
    WPADSamplingCallback samplingCB;   // at 0x8A8
    union {
        WPADStatus* samplingBuf;
        WPADStatusEx* samplingBufEx;
        WPADFSStatus* samplingBufFS;
        WPADCLStatus* samplingBufCL;
    }; // at 0x8AC
    u32 samplingBufIndex; // at 0x8B0
    u32 samplingBufSize;  // at 0x8B4
    u32 dataFormat;       // at 0x8B8
    s32 status;           // at 0x8BC
    u8 statusReqBusy;     // at 0x8C0
    u8 devType;           // at 0x8C1
    u8 devMode;           // at 0x8C2
    s8 devHandle;         // at 0x8C3
    s32 UNK_0x8C4;
    u8 rxBufIndex; // at 0x8C8
    s8 UNK_0x8C9;
    u8 defaultDpdSize;            // at 0x8CA
    u8 currentDpdCommand;         // at 0x8CB
    u8 pendingDpdCommand;         // at 0x8CC
    u8 radioQuality;              // at 0x8CD
    u8 radioQualityOkMs;          // at 0x8CE
    u8 audioFrames;               // at 0x8CF
    u32 motorBusy;                // at 0x8D0
    BOOL motorRunning;            // at 0x8D4
    BOOL used;                    // at 0x8D8
    BOOL handshakeFinished;       // at 0x8DC
    s32 configIndex;              // at 0x8E0
    OSThreadQueue threadQueue;    // at 0x8E4
    s64 lastControllerDataUpdate; // at 0x8F0
    u16 filterDiffDpd;            // at 0x8F8
    u16 filterSameDpd;            // at 0x8FA
    u16 filterDiffAcc;            // at 0x8FC
    u16 filterSameAcc;            // at 0x8FE
    u16 filterDiffExt;            // at 0x900
    u16 filterSameExt;            // at 0x902
    s64 lastReportSendTime;       // at 0x908
    u8 UNK_0x910;
    u8 calibrated;         // at 0x911
    u16 comboHeld;         // at 0x912
    u8 encryptionKey[16];  // at 0x914
    u8 decryptAddTable[8]; // at 0x924
    u8 decryptXorTable[8]; // at 0x92C
    u8 wmReadDataBuf[64];  // at 0x934
    u8* wmReadDataPtr;     // at 0x974
    u32 wmReadAddress;     // at 0x978
    int wmReadHadError;    // at 0x97C
    u16 wmReadLength;      // at 0x980
    s8 UNK_0x982;
    u8 radioSensitivity;    // at 0x983
    u16 copyOutCount;       // at 0x984
    u8 sleeping;            // at 0x986
    u8 lastReportID;        // at 0x987
    WPADCallback getInfoCB; // at 0x988
    u8 getInfoBusy;         // at 0x98C
    u8 UNK_0x98F[0x9A0 - 0x990];
} WPADCB;

extern WPADCB _wpd[WPAD_MAX_CONTROLLERS];
extern WPADCB* _wpdcb[WPAD_MAX_CONTROLLERS];

void WPADiInitSub(void);

void WPADiExcludeButton(s32 chan);
void WPADiCopyOut(s32 chan);

BOOL WPADiSendSetPort(WPADCommandQueue* pQueue, u8 port,
                      WPADCallback pCallback);
BOOL WPADiSendSetReportType(WPADCommandQueue* pQueue, s32 format,
                            WPADCallback pCallback);
BOOL WPADiSendEnableDPD(WPADCommandQueue* pQueue, BOOL enable,
                        WPADCallback pCallback);
BOOL WPADiSendEnableSpeaker(WPADCommandQueue* pQueue, BOOL enable,
                            WPADCallback pCallback);
BOOL WPADiSendGetContStat(WPADCommandQueue* pQueue, WPADInfo* pInfo,
                          WPADCallback pCallback);
BOOL WPADiSendWriteDataCmd(WPADCommandQueue* pQueue, u8 cmd, u32 addr,
                           WPADCallback pCallback);
BOOL WPADiSendWriteData(WPADCommandQueue* pQueue, const void* pSrc, u16 len,
                        u32 addr, WPADCallback pCallback);
BOOL WPADiSendReadData(WPADCommandQueue* pQueue, void* pDst, u16 len, u32 addr,
                       WPADCallback pCallback);
BOOL WPADiSendStreamData(WPADCommandQueue* pQueue, const void* pData, u16 len);
BOOL WPADiSendMuteSpeaker(WPADCommandQueue* pQueue, BOOL mute,
                          WPADCallback pCallback);
BOOL WPADiSendDPDCSB(WPADCommandQueue* pQueue, BOOL enable,
                     WPADCallback pCallback);

void WPADiClearQueue(WPADCommandQueue* pQueue);
BOOL WPADiPushCommand(WPADCommandQueue* pQueue, WPADCommand command);
BOOL WPADiGetCommand(const WPADCommandQueue* pQueue, WPADCommand* pCommand);
BOOL WPADiPopCommand(WPADCommandQueue* pQueue);

u16 _WPADGetStackBufferStatus(s32 chan);
u16 _WPADGetModuleBufferStatus(s32 chan);

void __WPADShutdown(void);
void __WPADReconnect(void);

#ifdef __cplusplus
}
#endif
#endif
