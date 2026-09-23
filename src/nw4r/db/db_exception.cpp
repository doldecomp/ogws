#include <nw4r/db.h>

#include <revolution/BASE.h>
#include <revolution/VI.h>

#include <cstring>

namespace nw4r {
namespace db {

//! Forward declarations

static void ErrorHandler_(u16 error, OSContext* context, u32 dsisr, u32 dar);

static void* RunThread_(void* arg);

static void DumpException_(const ExceptionCallbackParam* exPtr);

static void Exception_Printf_(const char* fmt, ...);

static void PrintContext_(u16 error, const OSContext* context, u32 dsisr,
                          u32 dar);

static void ShowMainInfo_(u16 error, const OSContext* context, u32 dsisr,
                          u32 dar);

static void setFPException(u32 type);

static ExceptionHead sException;
// TODO(texline) why?
static u8 sThreadBuffer[16384];
static OSMessage sMsgBuffer[1];

static const char* CPU_EXP_NAME[] = {
    "SYSTEM RESET",       "MACHINE CHECK",    "DSI",     "ISI",
    "EXTERNAL INTERRUPT", "ALIGNMENT",        "PROGRAM", "FLOATING POINT",
    "DECREMENTER",        "SYSTEM CALL",      "TRACE",   "PERFORMACE MONITOR",
    "BREAK POINT",        "SYSTEM INTERRUPT",
    "THERMAL INTERRUPT", // unused
    "PROTECTION",         "FLOATING POINT"};

void Exception_Init() {
    memset(&sException, 0, sizeof(ExceptionHead));
    sException.callback = NULL;
    sException.console = NULL;
    sException.dispInfo = EXCEPTION_INFO_DEFAULT;
    sException.frameMemory = NULL;
    sException.renderMode = NULL;

    OSCreateThread(&sException.thread, RunThread_, NULL, sThreadBuffer + 16384,
                   16384, 0, OS_THREAD_DETACHED);

    OSInitMessageQueue(&sException.msgQueue, &sMsgBuffer[0], 1);
    OSResumeThread(&sException.thread);

    OSSetErrorHandler(OS_ERR_DSI, (OSErrorHandler)ErrorHandler_);
    OSSetErrorHandler(OS_ERR_ISI, (OSErrorHandler)ErrorHandler_);
    OSSetErrorHandler(OS_ERR_ALIGNMENT, (OSErrorHandler)ErrorHandler_);
    OSSetErrorHandler(OS_ERR_PROTECTION, (OSErrorHandler)ErrorHandler_);

    setFPException(NULL);
}

void ErrorHandler_(u16 error, OSContext* context, u32 dsisr, u32 dar) {
    ExceptionCallbackParam exCallbackObject;

    sException.msr = PPCMfmsr();
    sException.fpscr = context->fpscr;
    OSFillFPUContext(context);
    OSSetErrorHandler(error, NULL);

    if (error == OS_ERR_PROTECTION) {
        OSProtectRange(0, 0, 0, 3);
        OSProtectRange(1, 0, 0, 3);
        OSProtectRange(2, 0, 0, 3);
        OSProtectRange(3, 0, 0, 3);
    }

    exCallbackObject.error = error;
    exCallbackObject.context = context;
    exCallbackObject.dsisr = dsisr;
    exCallbackObject.dar = dar;

    OSSendMessage(&sException.msgQueue, (OSMessage)(&exCallbackObject),
                  OS_MSG_BLOCKING);
    OSEnableScheduler();
    OSYieldThread();
    OSDisableScheduler();
}

void* RunThread_(void* arg) {
//! OSCreateThread needs a voidptr parameter.
#pragma unused(arg)
    u32 msr = PPCMfmsr();
    msr &= ~(MSR_FE0 | MSR_FE1);
    PPCMtmsr(msr);
    {
        OSMessage msg;

        OSReceiveMessage(&sException.msgQueue, &msg, OS_MSG_BLOCKING);
        OSDisableInterrupts();
        VISetPreRetraceCallback(NULL);
        VISetPostRetraceCallback(NULL);
        if (sException.console) {
            VISetBlack(FALSE);
            VIFlush();
        }
        DumpException_((ExceptionCallbackParam*)msg);
    }
    return NULL;
}

void DumpException_(const ExceptionCallbackParam* exPtr) {
    u16 error = exPtr->error;
    const OSContext* context = exPtr->context;
    u32 dsisr = exPtr->dsisr;
    u32 dar = exPtr->dar;

    if (error < OS_ERR_MAX) {
        sException.stackPointer = context->gprs[1];
    }
    if (sException.console) {
        sException.frameMemory =
            detail::DirectPrint_SetupFB(sException.renderMode);
    }
    while (true) {
        PrintContext_(error, context, dsisr, dar);
    }
}

void Exception_Printf_(const char* fmt, ...) {
    const GXRenderModeObj* rMode = sException.renderMode;
    {
        va_list vlist;
        va_start(vlist, fmt);
        vprintf(fmt, vlist);
        va_end(vlist);
    }
    if (sException.console) {
        void* fb = VIGetCurrentFrameBuffer();
        DirectPrint_ChangeXfb(fb, rMode->fbWidth, rMode->xfbHeight);

        va_list vlist;
        va_start(vlist, fmt);
        Console_VFPrintf(CONSOLE_OUTPUT_DISPLAY, sException.console, fmt,
                         vlist);
        va_end(vlist);
    }
}

void PrintContext_(u16 error, const OSContext* context, u32 dsisr, u32 dar) {
    if (error > OS_ERR_MAX) {
        Exception_Printf_("******** USER HALT ********\nFrameMemory:%XH\n",
                          sException.frameMemory);
    } else {
        Exception_Printf_(
            "******** EXCEPTION OCCURRED! ********\nFrameMemory:%XH\n",
            sException.frameMemory);
    }
    {
        if (sException.dispInfo & EXCEPTION_INFO_MAIN) {
            Exception_Printf_("---MainInfo---\n");
            ShowMainInfo_(error, context, dsisr, dar);
        }
    }
}

void ShowMainInfo_(u16 error, const OSContext* context, u32 dsisr, u32 dar) {
    if (error < OS_ERR_MAX) {
        Exception_Printf_("CONTEXT:%08XH  (%s EXCEPTION)\n", context,
                          CPU_EXP_NAME[error]);
    } else {
        Exception_Printf_("CONTEXT:%08XH\n", context);
    }
    if (error == OS_ERR_FP_EXCEPTION) {
        u32 fpscr = sException.fpscr;
        // TODO(texline): how is this calculated?
        fpscr &= (fpscr << 22) & 0x3E000000 | 0x1F80700;
        if (fpscr & FPSCR_VX) {
            Exception_Printf_(" FPE: Invalid operation\n");
            if (sException.fpscr & FPSCR_VXSNAN) {
                Exception_Printf_(" SNaN\n");
            }
            if (sException.fpscr & FPSCR_VXISI) {
                Exception_Printf_(" Infinity - Infinity\n");
            }
            if (sException.fpscr & FPSCR_VXIDI) {
                Exception_Printf_(" Infinity / Infinity\n");
            }
            if (sException.fpscr & FPSCR_VXZDZ) {
                Exception_Printf_(" 0 / 0\n");
            }
            if (sException.fpscr & FPSCR_VXIMZ) {
                Exception_Printf_(" Infinity * 0\n");
            }
            if (sException.fpscr & FPSCR_VXVC) {
                Exception_Printf_(" Invalid compare\n");
            }
            if (sException.fpscr & FPSCR_VXSOFT) {
                Exception_Printf_(" Software request\n");
            }
            if (sException.fpscr & FPSCR_VXSQRT) {
                Exception_Printf_(" Invalid square root\n");
            }
            if (sException.fpscr & FPSCR_VXCVI) {
                Exception_Printf_(" Invalid integer convert\n");
            }
        }
        if (fpscr & FPSCR_OX) {
            Exception_Printf_(" FPE: Overflow\n");
        }
        if (fpscr & FPSCR_UX) {
            Exception_Printf_(" FPE: Underflow\n");
        }
        if (fpscr & FPSCR_ZX) {
            Exception_Printf_(" FPE: Zero division\n");
        }
        if (fpscr & FPSCR_XX) {
            Exception_Printf_(" FPE: Inexact result\n");
        }
    }
    Exception_Printf_("SRR0:   %08XH   SRR1:%08XH\n", context->srr0,
                      context->srr1);
    Exception_Printf_("DSISR:  %08XH   DAR: %08XH\n", dsisr, dar);
}

void setFPException(u32 type) {
    __OSFpscrEnableBits = type;
    if (type) {
        (void)OSSetErrorHandler(OS_ERR_FP_EXCEPTION,
                                (OSErrorHandler)ErrorHandler_);

    } else {
        (void)OSSetErrorHandler(OS_ERR_FP_EXCEPTION, NULL);
    }
}

} // namespace db
} // namespace nw4r
