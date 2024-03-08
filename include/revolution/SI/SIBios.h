#ifndef RVL_SDK_SI_SIBIOS_H
#define RVL_SDK_SI_SIBIOS_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void SIInit(void);

void SISetXY(u32 x, u32 y);

#ifdef __cplusplus
}
#endif
#endif
