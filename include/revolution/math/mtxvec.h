#ifndef REVOSDK_MATH_MTXVEC_H
#define REVOSDK_MATH_MTXVEC_H
#ifdef __cplusplus
extern "C" {
#endif
#include <types.h>
#include <mtx.h>

void PSMTXMultVec(const Mtx, const struct Vec *, struct Vec *);

#ifdef __cplusplus
}
#endif
#endif