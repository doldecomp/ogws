#include <revolution/GX.h>
#include <revolution/OS.h>
#include <string.h>

static GXFifoObj DisplayListFifo;
static GXData __savedGXdata;
static GXFifoObj OldCPUFifo;

void GXBeginDisplayList(void* list, u32 size) {
    GXFifoObjImpl* impl = (GXFifoObjImpl*)&DisplayListFifo;

    if (gxdt->gxDirtyFlags != 0) {
        __GXSetDirtyState();
    }

    if (gxdt->dlistSave) {
        memcpy(&__savedGXdata, gxdt, sizeof(GXData));
    }

    impl->base = list;
    impl->end = (u8*)list + size - 4;
    impl->size = size;
    impl->count = 0;
    impl->readPtr = list;
    impl->writePtr = list;

    gxdt->dlistActive = TRUE;

    GXGetCPUFifo(&OldCPUFifo);
    GXSetCPUFifo(&DisplayListFifo);
    GXResetWriteGatherPipe();
}

u32 GXEndDisplayList(void) {
    u8 wrap;
    BOOL enabled;
    u32 ctrl;

    GXGetCPUFifo(&DisplayListFifo);
    wrap = GXGetFifoWrap(&DisplayListFifo);
    GXSetCPUFifo(&OldCPUFifo);

    if (gxdt->dlistSave) {
        enabled = OSDisableInterrupts();

        ctrl = gxdt->cpCtrlReg;
        memcpy(gxdt, &__savedGXdata, sizeof(GXData));
        gxdt->cpCtrlReg = ctrl;

        OSRestoreInterrupts(enabled);
    }

    gxdt->dlistActive = FALSE;

    if (!wrap) {
        return GXGetFifoCount(&DisplayListFifo);
    }

    return 0;
}

void GXCallDisplayList(void* list, u32 size) {
    if (gxdt->gxDirtyFlags != 0) {
        __GXSetDirtyState();
    }

    if (gxdt->WORD_0x0 == 0) {
        __GXSendFlushPrim();
    }

    WGPIPE.c = GX_FIFO_CMD_CALL_DL;
    WGPIPE.p = list;
    WGPIPE.i = size;
}
