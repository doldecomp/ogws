#include <revolution/OS.h>
#include <revolution/PAD.h>

u32 __PADSpec = 0;

BOOL __PADDisableRecalibration(BOOL disable) {
    BOOL enabled = OSDisableInterrupts();
    BOOL old = (OS_PAD_FLAGS & PAD_FLAG_NO_RECALIBRATE) ? TRUE : FALSE;

    OS_PAD_FLAGS &= ~PAD_FLAG_NO_RECALIBRATE;

    if (disable) {
        OS_PAD_FLAGS |= PAD_FLAG_NO_RECALIBRATE;
    }

    OSRestoreInterrupts(enabled);
    return old;
}
