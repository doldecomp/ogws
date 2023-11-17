#ifndef RVL_SDK_NWC24_FRIEND_LIST_H
#define RVL_SDK_NWC24_FRIEND_LIST_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

#define NWC24_FL_CAPACITY 100

typedef struct NWC24FLHeader {
    u32 magic;    // at 0x0
    u32 version;  // at 0x4
    u32 capacity; // at 0x8
    u32 size;     // at 0xC
    u8 padding[64 - 0x10];
    u64 friendCodes[NWC24_FL_CAPACITY]; // at 0x40
} NWC24FLHeader;

s32 NWC24iOpenFriendList(void);

#ifdef __cplusplus
}
#endif
#endif
