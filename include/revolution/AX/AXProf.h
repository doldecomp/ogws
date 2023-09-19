#ifndef RVL_SDK_AX_PROF_H
#define RVL_SDK_AX_PROF_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct _AXPROFILE {
    s64 timeBegin;       // at 0x0
    s64 timeMailCmdList; // at 0x8
    s64 timeProcessAux;  // at 0x10
    s64 TIME_0x18;
    s64 timeUserFrameCallback; // at 0x20
    s64 timeAiDma;             // at 0x28
    u32 maxVoices;             // at 0x30
    UNKWORD WORD_0x34;
} AXPROFILE;

AXPROFILE* __AXGetCurrentProfile(void);

#ifdef __cplusplus
}
#endif
#endif
