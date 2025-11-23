#ifndef RVL_SDK_EXI_UART_H
#define RVL_SDK_EXI_UART_H
#include <types.h>

#include <revolution/EXI/EXICommon.h>
#ifdef __cplusplus
extern "C" {
#endif

void __OSEnableBarnacle(EXIChannel chan, u32 dev);

#ifdef __cplusplus
}
#endif
#endif
