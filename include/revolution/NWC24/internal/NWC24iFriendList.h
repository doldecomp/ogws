#ifndef RVL_SDK_NWC24_INTERNAL_FRIEND_LIST_H
#define RVL_SDK_NWC24_INTERNAL_FRIEND_LIST_H
#include <types.h>

#include <revolution/NWC24/NWC24Types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct NWC24iFLHeader {
    u32 magic;    // at 0x0
    u32 version;  // at 0x4
    u32 capacity; // at 0x8
    u32 size;     // at 0xC
    char unk10[0x40 - 0x10];
    u64 friendCodes[NWC24_FRIEND_LIST_CAPACITY]; // at 0x40
} NWC24iFLHeader;

NWC24Err NWC24iOpenFriendList(void);

#ifdef __cplusplus
}
#endif
#endif
