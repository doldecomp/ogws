#ifndef RVL_SDK_GX_MISC_H
#define RVL_SDK_GX_MISC_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef void (*GXDrawDoneCallback)(void);

void GXSetMisc(UNKWORD token, UNKWORD val);
void GXFlush(void);
void GXResetWriteGatherPipe(void);

void GXAbortFrame(void);

void GXDrawDone(void);
void GXPixModeSync(void);

GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback);

#ifdef __cplusplus
}
#endif
#endif
