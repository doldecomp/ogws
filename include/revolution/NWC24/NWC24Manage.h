#ifndef RVL_SDK_NWC24_MANAGE_H
#define RVL_SDK_NWC24_MANAGE_H
#include <revolution/NWC24/NWC24FriendList.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    NWC24_NEW_MSG = (1 << 0),
    // TODO: Find NWC24IsNewMsgForMenuArrived and verify
    NWC24_NEW_MSG_MENU = (1 << 1),
} NWC24NewMsgArrived;

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
    u8 flHeaderWork[ROUND_UP(sizeof(NWC24FLHeader), 0x100)]; // at 0x2800
    char sflHeaderWork[0x800];                               // at 0x2800
    char dlHeaderWork[0x800];                                // at 0x3000
    char WORK_0x3800[0x200];
} NWC24Work;

extern NWC24Work* NWC24WorkP;

void NWC24iRegister(void);
s32 NWC24OpenLib(NWC24Work* work);
s32 NWC24CloseLib(void);
BOOL NWC24IsMsgLibOpened(void);
BOOL NWC24IsMsgLibOpenedByTool(void);
BOOL NWC24IsMsgLibOpenBlocking(void);
s32 NWC24BlockOpenMsgLib(BOOL block);
s32 NWC24iSetNewMsgArrived(u32 flags);
void NWC24iSetErrorCode(u32 code);

#ifdef __cplusplus
}
#endif
#endif
