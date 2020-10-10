#ifndef REVOSDK_MTX_H
#define REVOSDK_MTX_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void PSMTXIdentity(UNKTYPE *);
void PSMTXCopy(const UNKTYPE *, UNKTYPE *);

#ifdef __cplusplus
}
#endif
#endif