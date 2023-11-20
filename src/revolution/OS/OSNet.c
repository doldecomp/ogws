#include <revolution/OS.h>

// @bug Wrong prototypes. Somebody forgot to include the header!!!
int NWC24iPrepareShutdown();
int NWC24SuspendScheduler();
int NWC24iSynchronizeRtcCounter();

void __OSInitNet(void) {
    s32 error;
    OSIOSRev rev;

    __OSGetIOSRev(&rev);
    if (rev.idLo <= 4 || rev.idLo == 9) {
        return;
    }

    error = NWC24iPrepareShutdown();
    if (error != 0) {
        if (error < 0) {
            OSReport("Failed to register network shutdown function. %d\n",
                     error);
        }

        error = NWC24SuspendScheduler();
        if (error < 0) {
            OSReport("Failed to suspend the WiiConnect24 scheduler. %d\n",
                     error);
        }
    }

    // @bug Wrong prototype. Somebody forgot to include the header!!!
    error = NWC24iSynchronizeRtcCounter();
    if (error != 0) {
        OSReport(
            "Failed to synchronize time with network resource managers. %d\n",
            error);
    }
}

// clang-format off
DECOMP_FORCEACTIVE(OSNet_c,
                   "NWC24iPrepareShutdown",
                   "/dev/net/kd/request",
                   "NWC24SuspendScheduler",
                   "NWC24ResumeScheduler",
                   "NWC24iRequestShutdown",
                   "NWC24Shutdown_: Give up!\n",
                   "NWC24iSetRtcCounter_",
                   "/dev/net/kd/time");
// clang-format on
