#ifndef RVL_SDK_NWC24_MANAGE_H
#define RVL_SDK_NWC24_MANAGE_H
#include <revolution/NWC24/NWC24Download.h>
#include <revolution/NWC24/NWC24FriendList.h>
#include <revolution/NWC24/NWC24SecretFList.h>
#include <revolution/NWC24/NWC24Types.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    NWC24_NEW_MSG = (1 << 0),
    // TODO: Find NWC24IsNewMsgForMenuArrived and verify
    NWC24_NEW_MSG_MENU = (1 << 1),
} NWC24NewMsgArrived;

#define WORK_SIZE(x) (ROUND_UP(sizeof(x), 256))
typedef struct NWC24Work {
    char stringWork[1024]; // at 0x0
    char WORK_0x400[0x800 - 0x400];
    char pathWork[128]; // at 0x800
    char WORK_0x880[0x900 - 0x880];
    u8 readWork[512];   // at 0x900
    u8 writeWork[512];  // at 0xB00
    u8 configWork[512]; // at 0xD00
    char WORK_0xF00[0x1100 - 0xF00];
    char WORK_0x1100[128];
    char WORK_0x1180[128];
    char WORK_0x1200[128];
    char WORK_0x1280[128];
    u8 base64Work[256]; // at 0x1300
    char WORK_0x1400[0x2400 - 0x1400];

    u8 flHeader[WORK_SIZE(NWC24FLHeader)];             // at 0x2800
    u8 secretFlHeader[WORK_SIZE(NWC24SecretFLHeader)]; // at 0x2800
    u8 dlHeader[WORK_SIZE(NWC24DlHeader)];             // at 0x3000
    u8 dlTask[WORK_SIZE(NWC24DlTask)];                 // at 0x3800
} NWC24Work;
#undef WORK_SIZE

extern NWC24Work* NWC24WorkP;

void NWC24iRegister(void);
NWC24Err NWC24OpenLib(NWC24Work* work);
NWC24Err NWC24CloseLib(void);
BOOL NWC24IsMsgLibOpened(void);
BOOL NWC24IsMsgLibOpenedByTool(void);
BOOL NWC24IsMsgLibOpenBlocking(void);
NWC24Err NWC24BlockOpenMsgLib(BOOL block);
NWC24Err NWC24iSetNewMsgArrived(u32 flags);
void NWC24iSetErrorCode(u32 code);

#ifdef __cplusplus
}
#endif
#endif
