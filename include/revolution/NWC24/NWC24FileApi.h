#ifndef RVL_SDK_NWC24_FILE_API_H
#define RVL_SDK_NWC24_FILE_API_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    NWC24_OPEN_WRITE = (1 << 0),
    NWC24_OPEN_READ = (1 << 1),
    NWC24_OPEN_RW = (1 << 2),
} NWC24OpenMode;

typedef enum {
    NWC24_SEEK_BEG,
    NWC24_SEEK_CUR,
    NWC24_SEEK_END,
} NWC24SeekMode;

typedef struct NWC24File {
    u8 dummy[0x94];
} NWC24File;

s32 NWC24FOpen(NWC24File* file, const char* path, u32 mode);
s32 NWC24FClose(NWC24File* file);
s32 NWC24FSeek(NWC24File* file, s32 offset, NWC24SeekMode mode);
s32 NWC24FRead(void* dst, u32 size, NWC24File* file);

#ifdef __cplusplus
}
#endif
#endif
