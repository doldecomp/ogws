#ifndef RVL_SDK_ESP_H
#define RVL_SDK_ESP_H
#include <types.h>

#include <revolution/ARC.h>
#include <revolution/IPC.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ES_IOCTLV_LAUNCH_TITLE = 8,
    ES_IOCTLV_READ_CONTENT_FILE = 10,
    ES_IOCTLV_GET_NUM_TICKET_VIEWS = 18,
    ES_IOCTLV_GET_TICKET_VIEWS = 19,
    ES_IOCTLV_GET_DATA_DIR = 29,
    ES_IOCTLV_GET_TITLE_ID = 32,
    ES_IOCTLV_SEEK_CONTENT_FILE = 35,
} ESIoctl;

typedef struct ESPTicket {
    u8 dummy[0x2A4];
} ESPTicket;

typedef struct ESPTmd {
    u8 dummy[0x49E4];
} ESPTmd;

s32 ESP_ReadContentFile(s32 fd, void* dst, u32 len);
s32 ESP_SeekContentFile(s32 fd, s32 offset, s32 origin);

#ifdef __cplusplus
}
#endif
#endif
