#ifndef RVL_SDK_OS_ERROR_H
#define RVL_SDK_OS_ERROR_H
#include <types.h>

#include <decomp/assertion.h>

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct OSContext OSContext;

// TODO(kiwi) Switch over OS_ERROR uses to OS_PANIC
#define OS_ERROR(...) OSPanic(__FILE__, __LINE__, __VA_ARGS__)

#define OS_PANIC(...) DECOMP_ASSERT(OS_PANIC_IMPL, LINES_DUMMY, __VA_ARGS__)
#define OS_PANIC_IMPL(file, line, ...) OSPanic(file, line, __VA_ARGS__)

#define OS_ASSERT(exp, ...)                                                    \
    if (!(exp))                                                                \
    OSPanic(__FILE__, __LINE__, __VA_ARGS__)

typedef enum {
    OS_ERROR_SYSTEM_RESET,
    OS_ERROR_MACHINE_CHECK,
    OS_ERROR_DSI,
    OS_ERROR_ISI,
    OS_ERROR_EXTERNAL_INTERRUPT,
    OS_ERROR_ALIGNMENT,
    OS_ERROR_PROGRAM,
    OS_ERROR_FLOATING_POINT,
    OS_ERROR_DECREMENTER,
    OS_ERROR_SYSTEM_CALL,
    OS_ERROR_TRACE,
    OS_ERROR_PERFORMACE_MONITOR, // typo
    OS_ERROR_BREAKPOINT,
    OS_ERROR_SYSTEM_INTERRUPT,
    OS_ERROR_THERMAL_INTERRUPT,
    OS_ERROR_PROTECTION,
    OS_ERROR_FPE,

    OS_ERROR_MAX
} OSErrorType;

typedef void (*OSErrorHandler)(u16 error, OSContext* ctx, u32 dsisr, u32 dar,
                               ...);

extern OSErrorHandler __OSErrorTable[OS_ERROR_MAX];
extern u32 __OSFpscrEnableBits;

/* DECL_WEAK */ void OSReport(const char* msg, ...);
/* DECL_WEAK */ void OSVReport(const char* msg, va_list argv);
/* DECL_WEAK */ void OSPanic(const char* file, int line, const char* msg, ...);

OSErrorHandler OSSetErrorHandler(u16 error, OSErrorHandler handler);
void __OSUnhandledException(u8 error, OSContext* ctx, u32 dsisr, u32 dar);

#ifdef __cplusplus
}
#endif
#endif
