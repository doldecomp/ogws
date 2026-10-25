#ifndef RVL_SDK_OS_LINK_H
#define RVL_SDK_OS_LINK_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSModuleLink {
    struct OSModuleInfo* next; // at 0x0
    struct OSModuleInfo* prev; // at 0x4
} OSModuleLink;

typedef struct OSModuleInfo {
    u32 id;                // at 0x0
    OSModuleLink link;     // at 0x4
    u32 numSections;       // at 0xC
    u32 sectionInfoOffset; // at 0x10
    u32 nameOffset;        // at 0x14
    u32 nameSize;          // at 0x18
    u32 version;           // at 0x1C
} OSModuleInfo;

typedef struct OSSectionInfo {
    u32 offset; // at 0x0
    u32 size;   // at 0x0
} OSSectionInfo;

void __OSModuleInit(void);

#ifdef __cplusplus
}
#endif
#endif
