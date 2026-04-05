#ifndef RVL_SDK_NWC24_MANAGE_H
#define RVL_SDK_NWC24_MANAGE_H
#include <types.h>

#include <revolution/NWC24/NWC24Types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NWC24i_IO_BUFFER_SIZE 512
#define NWC24i_STRING_WORK_SIZE 1024
#define NWC24i_PATH_WORK_SIZE 256

#define NWC24_WORK_PUBLIC_SIZE 0x4000
typedef struct NWC24Work {
    u8 data[NWC24_WORK_PUBLIC_SIZE];
} NWC24Work;

NWC24Err NWC24OpenLib(NWC24Work* pWork);
NWC24Err NWC24CloseLib(void);
BOOL NWC24IsMsgLibOpened(void);
BOOL NWC24IsMsgLibOpenedByTool(void);
BOOL NWC24IsMsgLibOpenBlocking(void);
NWC24Err NWC24BlockOpenMsgLib(BOOL block);

#ifdef __cplusplus
}
#endif
#endif
