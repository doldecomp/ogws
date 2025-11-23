#ifndef RVL_SDK_NWC24_FRIEND_LIST_H
#define RVL_SDK_NWC24_FRIEND_LIST_H
#include <types.h>

#include <revolution/NWC24/NWC24Types.h>
#ifdef __cplusplus
extern "C" {
#endif

#define NWC24_FRIEND_LIST_CAPACITY 100

typedef struct NWC24FLHeader {
    u32 magic;    // at 0x0
    u32 version;  // at 0x4
    u32 capacity; // at 0x8
    u32 size;     // at 0xC
    char UNK_0x10[0x40 - 0x10];
    u64 friendCodes[NWC24_FRIEND_LIST_CAPACITY]; // at 0x40
} NWC24FLHeader;

NWC24Err NWC24iOpenFriendList(void);

#ifdef __cplusplus
}
#endif
#endif
