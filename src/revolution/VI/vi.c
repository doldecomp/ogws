#include <revolution/VI.h>

static VIRetraceCallback PreCB;
static void* CurrBufAddr;

VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback callback) {
    VIRetraceCallback currCB = PreCB;
    BOOL enabled = OSDisableInterrupts();
    PreCB = callback;
    OSRestoreInterrupts(enabled);
    return currCB;
}

void* VIGetCurrentFrameBuffer(void) {
    return CurrBufAddr;
}
