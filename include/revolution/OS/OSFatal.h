#ifndef RVL_SDK_OS_FATAL_H
#define RVL_SDK_OS_FATAL_H
#include <revolution/GX/GXTypes.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void OSFatal(GXColor textColor, GXColor bgColor, const char* msg);

#ifdef __cplusplus
}
#endif
#endif
