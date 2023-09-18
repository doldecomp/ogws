#ifndef RVL_SDK_AX_VPB_H
#define RVL_SDK_AX_VPB_H
#include <revolution/AX/AXPB.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef void (*AXVoiceCallback)(void* voice);

typedef struct _AXVPB {
    void* next;               // at 0x0
    void* prev;               // at 0x4
    void* next1;              // at 0x8
    u32 priority;             // at 0xC
    AXVoiceCallback callback; // at 0x10
    u32 userContext;          // at 0x14
    u32 index;                // at 0x18
    u32 sync;                 // at 0x1C
    u32 depop;                // at 0x20
    void* itdBuffer;          // at 0x24
    AXPB pb;                  // at 0x28
} AXVPB;

UNKTYPE AXSetMaxDspCycles(UNKWORD);
UNKWORD AXGetMaxVoices(void);

void __AXSetPBDefault(AXVPB* vpb);

#ifdef __cplusplus
}
#endif
#endif
