#include <revolution/ESP.h>

static s32 __esFd = -1;

s32 ESP_ReadContentFile(s32 fd, void* dst, u32 len) {
    u8 WORK[256] ALIGN(32);

    IPCIOVector* vecWork = (IPCIOVector*)(WORK + 0xE8);
    s32* fdWork = (s32*)(WORK + 0x00);

    // Cast is necessary
    if (__esFd < 0 || fd < 0 || dst == (void*)NULL || len <= 0) {
        return -0x3F9;
    }

    if ((u32)dst % 32 != 0) {
        return -0x3F9;
    }

    *fdWork = fd;

    vecWork[1].base = dst;
    vecWork[1].length = len;
    vecWork[0].base = fdWork;
    vecWork[0].length = sizeof(s32);

    return IOS_Ioctlv(__esFd, ES_IOCTLV_READ_CONTENT_FILE, 1, 1, vecWork);
}

s32 ESP_SeekContentFile(s32 fd, s32 offset, s32 origin) {
    u8 WORK[256] ALIGN(32);

    IPCIOVector* vecWork = (IPCIOVector*)(WORK + 0xE8);
    s32* fdWork = (s32*)(WORK + 0x00);
    s32* offsetWork = (s32*)(WORK + 0x20);
    s32* originWork = (s32*)(WORK + 0x40);

    if (__esFd < 0) {
        return -0x3F9;
    }

    *fdWork = fd;
    *offsetWork = offset;
    *originWork = origin;

    vecWork[0].base = fdWork;
    vecWork[0].length = sizeof(s32);
    vecWork[1].base = offsetWork;
    vecWork[1].length = sizeof(s32);
    vecWork[2].base = originWork;
    vecWork[2].length = sizeof(s32);

    return IOS_Ioctlv(__esFd, ES_IOCTLV_SEEK_CONTENT_FILE, 3, 0, vecWork);
}
