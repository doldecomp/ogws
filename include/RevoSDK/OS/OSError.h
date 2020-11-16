#ifndef REVOSDK_OS_ERROR_H
#define REVOSDK_OS_ERROR_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

UNKTYPE OSReport(const char *, ...);
UNKTYPE OSPanic(const char *, UNKWORD, const char *, ...);
#define OSError(...) OSPanic(__FILE__,__LINE__,__VA_ARGS__)

#ifdef __cplusplus
}
#endif
#endif