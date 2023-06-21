#ifndef REVOSDK_OS_ERROR_H
#define REVOSDK_OS_ERROR_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

#define OSError(...) OSPanic(__FILE__, __LINE__, __VA_ARGS__)
#define OSAssert(exp, ...)                                                     \
    if (!(exp))                                                                \
    OSPanic(__FILE__, __LINE__, __VA_ARGS__)

DECL_WEAK void OSReport(const char* msg, ...);
DECL_WEAK void OSPanic(const char* file, int line, const char* msg, ...);

#ifdef __cplusplus
}
#endif
#endif