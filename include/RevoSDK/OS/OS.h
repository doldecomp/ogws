#ifndef REVOSDK_OS_H
#define REVOSDK_OS_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

volatile u32 BUS_SPEED : 0x800000f8;

UNKTYPE OSRegisterVersion(const char *);

#ifdef __cplusplus
}
#endif
#endif