#ifndef RVL_SDK_NWC24_INTERNAL_CONFIG_H
#define RVL_SDK_NWC24_INTERNAL_CONFIG_H
#include <types.h>

#include <revolution/NWC24/NWC24Types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct NWC24iConfig {
    u32 magic;               // at 0x0
    u32 version;             // at 0x4
    u64 userId;              // at 0x8
    u32 createCount;         // at 0x10
    u32 createStage;         // at 0x14
    char acctDomain[64];     // at 0x18
    char password[32];       // at 0x58
    char mailchkId[36];      // at 0x78
    char acctUrl[128];       // at 0x9C
    char mailchkUrl[128];    // at 0x11C
    char mailrecvUrl[128];   // at 0x19C
    char maildeleteUrl[128]; // at 0x21C
    char mailsendUrl[128];   // at 0x29C
    char UNK_0x31C[0x3F8 - 0x31C];
    BOOL allowTitleBoot; // at 0x3F8
    u32 checksum;        // at 0x3FC
} NWC24iConfig;

NWC24Err NWC24iConfigOpen(void);
NWC24Err NWC24iConfigReload(void);
NWC24Err NWC24iConfigFlush(void);

#ifdef __cplusplus
}
#endif
#endif
