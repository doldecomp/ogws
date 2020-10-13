#ifndef REVOSDK_MATH_MTXVEC_H
#define REVOSDK_MATH_MTXVEC_H
#ifdef __cplusplus
extern "C" {
#endif
#include <types.h>

void PSMTXMultVec(const float[3][4], const struct Vec *, struct Vec *);

#ifdef __cplusplus
}
#endif
#endif