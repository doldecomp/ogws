#include <nw4r/db.h>

#include <revolution/BASE.h>
#include <revolution/GX.h>
#include <revolution/OS.h>
#include <revolution/VI.h>

#include <cstring>

namespace nw4r {
namespace db {

struct ExceptionCallbackParam {
    u16 error;           // at 0x0
    OSContext* pContext; // at 0x4
    u32 dsisr;           // at 0x8
    u32 dar;             // at 0xC
};

// Forward declarations
static void ErrorHandler_(u16 error, OSContext* pContext, u32 dsisr, u32 dar);
static void* RunThread_(void* pArg);
static void* DumpException_(const ExceptionCallbackParam* pParam);
static void PrintContext_(u16 error, const OSContext* pContext, u32 dsisr,
                          u32 dar);
static void ShowStackTrace_(u32 sp);
static void ShowMainInfo_(u16 error, const OSContext* pContext, u32 dsisr,
                          u32 dar);
static void ShowGPR_(const OSContext* pContext);
static void ShowGPRMap_(const OSContext* pContext);
static void ShowSRR0Map_(const OSContext* pContext);
static void ShowFloat_(const OSContext* pContext);
static void SetFPException_(u32 fpscr);
static bool ShowMapInfoSubroutine_(u32 address, bool preNewline);
static void DrawConsoleEndless_(ConsoleHandle console);

struct {
    OSThread thread;                     // at 0x0
    OSMessageQueue msgQueue;             // at 0x318
    void* pFrameMemory;                  // at 0x338
    u32 stackAddr;                       // at 0x33C
    ConsoleHandle console;               // at 0x340
    const GXRenderModeObj* pRenderMode;  // at 0x344
    ExceptionUserCallback pUserCallback; // at 0x348
    void* pUserCallbackArg;              // at 0x34C
    u32 msr;                             // at 0x350
    u32 fpscr;                           // at 0x354
    u16 displayInfo;                     // at 0x358
    u8 unk35A[0x360 - 0x35A];
} sException;

static u8 sThreadBuffer[OS_MEM_KB_TO_B(16)];
static OSMessage sMessageBuffer[1];

const char* CPU_EXP_NAME[OS_ERROR_MAX] = {
    "SYSTEM RESET",       // OS_ERROR_SYSTEM_RESET
    "MACHINE CHECK",      // OS_ERROR_MACHINE_CHECK
    "DSI",                // OS_ERROR_DSI
    "ISI",                // OS_ERROR_ISI
    "EXTERNAL INTERRUPT", // OS_ERROR_EXTERNAL_INTERRUPT
    "ALIGNMENT",          // OS_ERROR_ALIGNMENT
    "PROGRAM",            // OS_ERROR_PROGRAM
    "FLOATING POINT",     // OS_ERROR_FLOATING_POINT
    "DECREMENTER",        // OS_ERROR_DECREMENTER
    "SYSTEM CALL",        // OS_ERROR_SYSTEM_CALL
    "TRACE",              // OS_ERROR_TRACE
    "PERFORMACE MONITOR", // OS_ERROR_PERFORMACE_MONITOR
    "BREAK POINT",        // OS_ERROR_BREAKPOINT
    "SYSTEM INTERRUPT",   // OS_ERROR_SYSTEM_INTERRUPT
    "THERMAL INTERRUPT",  // OS_ERROR_THERMAL_INTERRUPT
    "PROTECTION",         // OS_ERROR_PROTECTION
    "FLOATING POINT",     // OS_ERROR_FPE
};

void Exception_Init() {
    std::memset(&sException, 0, sizeof(sException));

    sException.pUserCallback = NULL;
    sException.console = NULL;

    sException.displayInfo =
        EXCEPTION_DISPLAY_MAININFO | EXCEPTION_DISPLAY_STACKTRACE;

    sException.pFrameMemory = NULL;
    sException.pRenderMode = NULL;

    OSCreateThread(&sException.thread,                    //
                   RunThread_,                            //
                   NULL,                                  //
                   sThreadBuffer + sizeof(sThreadBuffer), //
                   sizeof(sThreadBuffer),                 //
                   OS_PRIORITY_MIN,                       //
                   OS_THREAD_DETACHED);

    OSInitMessageQueue(&sException.msgQueue, sMessageBuffer,
                       ARRAY_SIZE(sMessageBuffer));

    OSResumeThread(&sException.thread);

    // Why make the error handler non-variadic?
    OSSetErrorHandler(OS_ERROR_DSI,
                      reinterpret_cast<OSErrorHandler>(ErrorHandler_));
    OSSetErrorHandler(OS_ERROR_ISI,
                      reinterpret_cast<OSErrorHandler>(ErrorHandler_));
    OSSetErrorHandler(OS_ERROR_ALIGNMENT,
                      reinterpret_cast<OSErrorHandler>(ErrorHandler_));
    OSSetErrorHandler(OS_ERROR_PROTECTION,
                      reinterpret_cast<OSErrorHandler>(ErrorHandler_));

    // Disable floating-point exceptions?
    SetFPException_(0);
}

static void ErrorHandler_(u16 error, OSContext* pContext, u32 dsisr, u32 dar) {
    sException.msr = PPCMfmsr();
    sException.fpscr = pContext->fpscr;
    OSFillFPUContext(pContext);

    OSSetErrorHandler(error, NULL);

    if (error == OS_ERROR_PROTECTION) {
        OSProtectRange(OS_PROTECT_CHANNEL_0, NULL, 0, OS_PROTECT_CONTROL_RDWR);
        OSProtectRange(OS_PROTECT_CHANNEL_1, NULL, 0, OS_PROTECT_CONTROL_RDWR);
        OSProtectRange(OS_PROTECT_CHANNEL_2, NULL, 0, OS_PROTECT_CONTROL_RDWR);
        OSProtectRange(OS_PROTECT_CHANNEL_3, NULL, 0, OS_PROTECT_CONTROL_RDWR);
    }

    ExceptionCallbackParam param;
    param.error = error;
    param.pContext = pContext;
    param.dsisr = dsisr;
    param.dar = dar;

    OSSendMessage(&sException.msgQueue, static_cast<OSMessage>(&param),
                  OS_MSG_BLOCKING);

    OSEnableScheduler();
    OSYieldThread();
    OSDisableScheduler();
}

static void* RunThread_(void* /* pArg */) {
    PPCMtmsr(PPCMfmsr() & ~(MSR_FE0 | MSR_FE1));

    // Thread blocks until error handler is invoked
    OSMessage msg;
    OSReceiveMessage(&sException.msgQueue, &msg, OS_MSG_BLOCKING);

    OSDisableInterrupts();

    VISetPreRetraceCallback(NULL);
    VISetPostRetraceCallback(NULL);

    if (sException.console != NULL) {
        VISetBlack(FALSE);
        VIFlush();
    }

    const ExceptionCallbackParam* pParam =
        reinterpret_cast<ExceptionCallbackParam*>(msg);

    u16 error = pParam->error;
    OSContext* pContext = pParam->pContext;
    u32 dsisr = pParam->dsisr;
    u32 dar = pParam->dar;

    // Fake OS error values are used to signal a halt/panic.
    // Panic is expected to set SP (outside of the panic function itself).
    if (error < OS_ERROR_MAX) {
        sException.stackAddr = pContext->gprs[1];
    }

    if (sException.console != NULL) {
        sException.pFrameMemory =
            detail::DirectPrint_SetupFB(sException.pRenderMode);
    }

    while (true) {
        PrintContext_(error, pContext, dsisr, dar);

        if (sException.console != NULL && DirectPrint_IsActive()) {
            Console_DrawDirect(sException.console);
        }

        if (sException.pUserCallback != NULL) {
            u16 info = sException.displayInfo;

            // The console needs to be re-drawn if the content changes
            do {
                // User callback can choose to terminate the display
                if (!sException.pUserCallback(sException.console,
                                              sException.pUserCallbackArg)) {
                    return NULL;
                }

            } while (info == sException.displayInfo);
        }
        // Default behavior (auto scroll)
        else if (sException.console != NULL) {
            DrawConsoleEndless_(sException.console);
        }
        // Terminal display only
        else {
            break;
        }
    }

    return NULL;
}

static void Exception_Printf_(const char* pFmt, ...) {
    const GXRenderModeObj* pRenderMode = sException.pRenderMode;

    std::va_list argv;
    va_start(argv, pFmt);
    OSVReport(pFmt, argv);
    va_end(argv);

    if (sException.console != NULL) {
        DirectPrint_ChangeXfb(VIGetCurrentFrameBuffer(), pRenderMode->fbWidth,
                              pRenderMode->xfbHeight);

        std::va_list argv;
        va_start(argv, pFmt);
        Console_VFPrintf(CONSOLE_OUTPUT_DISPLAY, sException.console, pFmt,
                         argv);
        va_end(argv);
    }
}

static void PrintContext_(u16 error, const OSContext* pContext, u32 dsisr,
                          u32 dar) {
    // Fake OS error values are used to signal a halt/panic
    if (error < OS_ERROR_MAX) {
        Exception_Printf_("******** EXCEPTION OCCURRED! ********\n"
                          "FrameMemory:%XH\n",
                          sException.pFrameMemory);
    } else {
        Exception_Printf_("******** USER HALT ********\n"
                          "FrameMemory:%XH\n",
                          sException.pFrameMemory);
    }

    if (sException.displayInfo & EXCEPTION_DISPLAY_MAININFO) {
        Exception_Printf_("---MainInfo---\n");
        ShowMainInfo_(error, pContext, dsisr, dar);
    }

    if (sException.displayInfo & EXCEPTION_DISPLAY_GPR) {
        Exception_Printf_("---EXCEPTION_INFO_GPR---\n");
        ShowGPR_(pContext);
    }

    if (sException.displayInfo & EXCEPTION_DISPLAY_SRR0) {
        Exception_Printf_("---EXCEPTION_INFO_SRR0MAP---\n");
        ShowSRR0Map_(pContext);
    }

    if (sException.displayInfo & EXCEPTION_DISPLAY_GPRMAP) {
        Exception_Printf_("---EXCEPTION_INFO_GPRMAP---\n");
        ShowGPRMap_(pContext);
    }

    if (sException.displayInfo & EXCEPTION_DISPLAY_FPR) {
        Exception_Printf_("---EXCEPTION_INFO_FPR---\n");
        ShowFloat_(pContext);
        Exception_Printf_(" MSR:%08XH     FPSCR:%08XH\n", sException.msr,
                          sException.fpscr);
    }

    if (sException.displayInfo & EXCEPTION_DISPLAY_STACKTRACE) {
        Exception_Printf_("---EXCEPTION_INFO_TRACE---\n");
        ShowStackTrace_(sException.stackAddr);
    }

    Exception_Printf_("--------------------------------\n");
}

static void ShowStackTrace_(u32 sp) {
    Exception_Printf_("-------------------------------- TRACE\n");
    Exception_Printf_("Address:   BackChain   LR save\n");

    u32 i;
    u32* it = reinterpret_cast<u32*>(sp);

    for (i = 0; i < 16; i++) {
        if (it == NULL || reinterpret_cast<u32>(it) == 0xFFFFFFFF) {
            break;
        }

        Exception_Printf_("%08X:  %08X    %08X ", it, it[0], it[1]);

        if (!ShowMapInfoSubroutine_(it[1], false)) {
            Exception_Printf_("\n");
        }

        it = reinterpret_cast<u32*>(*it);
    }
}

static void ShowMainInfo_(u16 error, const OSContext* pContext, u32 dsisr,
                          u32 dar) {
    // Fake OS error values are used to signal a halt/panic
    if (error < OS_ERROR_MAX) {
        Exception_Printf_("CONTEXT:%08XH  (%s EXCEPTION)\n", pContext,
                          CPU_EXP_NAME[error]);
    } else {
        Exception_Printf_("CONTEXT:%08XH\n", pContext);
    }

    if (error == OS_ERROR_FPE) {
        u32 fpe = sException.fpscr;

        // clang-format off
        fpe &=
            // Mask away exceptions that are disabled.
            // Overlaps FPSCR_V* bits with FPSCR_*X bits.
            (fpe & (FPSCR_VE | FPSCR_OE | FPSCR_UE | FPSCR_ZE | FPSCR_XE)) << 22
            // Allow invalid-operation (FPSCR_VX) details 
            | FPSCR_VXSNAN | FPSCR_VXISI | FPSCR_VXIDI | FPSCR_VXZDZ | FPSCR_VXIMZ | FPSCR_VXVC
            | FPSCR_VXSOFT | FPSCR_VXSQRT | FPSCR_VXCVI;
        // clang-format on

        if (fpe & FPSCR_VX) {
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

        if (fpe & FPSCR_OX) {
            Exception_Printf_(" FPE: Overflow\n");
        }

        if (fpe & FPSCR_UX) {
            Exception_Printf_(" FPE: Underflow\n");
        }

        if (fpe & FPSCR_ZX) {
            Exception_Printf_(" FPE: Zero division\n");
        }

        if (fpe & FPSCR_XX) {
            Exception_Printf_(" FPE: Inexact result\n");
        }
    }

    Exception_Printf_("SRR0:   %08XH   SRR1:%08XH\n", pContext->srr0,
                      pContext->srr1);

    Exception_Printf_("DSISR:  %08XH   DAR: %08XH\n", dsisr, dar);
}

static void ShowGPR_(const OSContext* pContext) {
    Exception_Printf_("-------------------------------- GPR\n");

    for (int reg = 0; reg < 10; reg++) {
        Exception_Printf_("R%02d:%08XH  R%02d:%08XH  R%02d:%08XH\n", //
                          reg, pContext->gprs[reg],                  //
                          reg + 11, pContext->gprs[reg + 11],        //
                          reg + 22, pContext->gprs[reg + 22]);
    }

    Exception_Printf_("R%02d:%08XH  R%02d:%08XH\n", //
                      10, pContext->gprs[10],       //
                      21, pContext->gprs[21]);
}

static void ShowGPRMap_(const OSContext* pContext) {
    bool anyAddr = false;
    Exception_Printf_("-------------------------------- GPRMAP\n");

    // @bug The value of r31 is never shown
#if defined(BUG_FIX)
    for (int reg = 0; reg <= 31; reg++) {
#else
    for (int reg = 0; reg < 31; reg++) {
#endif
        if (pContext->gprs[reg] < 0x80000000 ||
            pContext->gprs[reg] > 0x82FFFFFF) {
            continue;
        }

        anyAddr = true;
        Exception_Printf_("R%02d: %08XH ", reg, pContext->gprs[reg]);

        if (!ShowMapInfoSubroutine_(pContext->gprs[reg], false)) {
            Exception_Printf_(" no information\n");
        }
    }

    if (!anyAddr) {
        Exception_Printf_("  no register which seem to address.\n");
    }
}

static void ShowSRR0Map_(const OSContext* pContext) {
    Exception_Printf_("-------------------------------- SRR0MAP\n");

    if (pContext->srr0 < 0x80000000 || pContext->srr0 > 0x82FFFFFF) {
        return;
    }

    Exception_Printf_("SRR0: %08XH ", pContext->srr0);

    if (!ShowMapInfoSubroutine_(pContext->srr0, false)) {
        Exception_Printf_(" no information\n");
    }
}

static void ShowFloatSub_(s32 reg, f32 value) {
    if (isnan(value)) {
        Exception_Printf_("F%02d: Nan      ", reg);
    } else if (isinfinite(value)) {
        if (*reinterpret_cast<u8*>(&value) & 0x80) {
            Exception_Printf_("F%02d:+Inf      ", reg);
        } else {
            Exception_Printf_("F%02d:-Inf      ", reg);
        }
    } else if (value == 0.0f) {
        Exception_Printf_("F%02d: 0.0      ", reg);
    } else {
        Exception_Printf_("F%02d:%+.3E", reg, value);
    }
}

static void ShowFloat_(const OSContext* pContext) {
    Exception_Printf_("-------------------------------- FPR\n");

    for (int reg = 0; reg < 10; reg++) {
        ShowFloatSub_(reg, pContext->fprs[reg]);
        Exception_Printf_(" ");

        ShowFloatSub_(reg + 11, pContext->fprs[reg + 11]);
        Exception_Printf_(" ");

        ShowFloatSub_(reg + 22, pContext->fprs[reg + 22]);
        Exception_Printf_("\n");
    }

    ShowFloatSub_(10, pContext->fprs[10]);
    Exception_Printf_(" ");

    ShowFloatSub_(21, pContext->fprs[21]);
    Exception_Printf_("\n");
}

static void SetFPException_(u32 fpscr) {
    __OSFpscrEnableBits = fpscr;

    if (fpscr != 0) {
        OSSetErrorHandler(OS_ERROR_FPE,
                          reinterpret_cast<OSErrorHandler>(ErrorHandler_));
    } else {
        OSSetErrorHandler(OS_ERROR_FPE, NULL);
    }
}

#if defined(NW4R_FEATURE_MAPFILE)
static bool ShowMapInfoSubroutine_(u32 address, bool preNewline) {
    if (address < 0x80000000 || address > 0x82FFFFFF) {
        return false;
    }

    // TODO(kiwi) Where does this number come from?
    u8 buffer[256 + 4];
    bool success = MapFile_QuerySymbol(address, buffer, sizeof(buffer));

    if (success) {
        if (preNewline) {
            Exception_Printf_("\n");
        }

        Exception_Printf_("%s\n", reinterpret_cast<char*>(buffer));
        return true;
    }

    return false;
}
#else
static bool ShowMapInfoSubroutine_(u32 /* address */, bool /* preNewline */) {
    return false;
}
#endif

ConsoleHandle Exception_SetConsole(ConsoleHandle console,
                                   const GXRenderModeObj* pRenderMode) {
    NW4R_NULL_ASSERT(console);

    ConsoleHandle old = sException.console;
    sException.console = console;
    sException.pRenderMode = pRenderMode;
    return old;
}

ConsoleHandle Exception_GetConsole() {
    return sException.console;
}

void Exception_SetUserCallback(ExceptionUserCallback pCallback,
                               void* pCallbackArg) {
    sException.pUserCallback = pCallback;
    sException.pUserCallbackArg = pCallbackArg;
}

u16 Exception_SetDisplayInfo(u16 displayInfo) {
    u16 old = sException.displayInfo;
    sException.displayInfo = displayInfo;
    return old;
}

static void WaitTime_(s32 millis) {
    OSTime start = OSGetTime();

    while (OS_TICKS_TO_MSEC(OSGetTime() - start) < millis) {
        ;
    }
}

static void DrawConsoleEndless_(ConsoleHandle console) {
    s32 head = Console_GetBufferHeadLine(console);

    while (true) {
        s32 total = Console_GetTotalLines(console);
        if (head >= total) {
            head = Console_GetBufferHeadLine(console);
        }

        // @bug Wrong console handle
#if defined(BUG_FIX)
        Console_SetViewBaseLine(console, head);
#else
        Console_SetViewBaseLine(sException.console, head);
#endif

        Console_DrawDirect(console);

        WaitTime_(200);
        head++;
    }
}

} // namespace db
} // namespace nw4r
