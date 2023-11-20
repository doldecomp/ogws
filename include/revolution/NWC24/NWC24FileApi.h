#ifndef RVL_SDK_NWC24_FILE_API_H
#define RVL_SDK_NWC24_FILE_API_H
#include <revolution/NAND.h>
#include <revolution/NWC24/NWC24Types.h>
#include <revolution/VF.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    NWC24_OPEN_WRITE = (1 << 0),
    NWC24_OPEN_READ = (1 << 1),
    NWC24_OPEN_RW = (1 << 2),
    NWC24_OPEN_NEED_LIB = (1 << 3),
} NWC24OpenMode;

typedef enum {
    NWC24_SEEK_BEG,
    NWC24_SEEK_CUR,
    NWC24_SEEK_END,
} NWC24SeekMode;

typedef struct NWC24File {
    u32 id;             // at 0x0
    u32 mode;           // at 0x4
    u32 position;       // at 0x8
    NANDFileInfo nandf; // at 0xC
    VFFile vff;         // at 0x98
} NWC24File;

NWC24Err NWC24FOpen(NWC24File* file, const char* path, u32 mode);
NWC24Err NWC24FClose(NWC24File* file);
NWC24Err NWC24FSeek(NWC24File* file, s32 offset, NWC24SeekMode mode);
NWC24Err NWC24FRead(void* dst, u32 size, NWC24File* file);
NWC24Err NWC24FWrite(const void* src, u32 size, NWC24File* file);
NWC24Err NWC24FGetLength(NWC24File* file, u32* lengthOut);

#ifdef __cplusplus
}
#endif
#endif
