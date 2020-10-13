#ifndef REVOSDK_MATH_MTX_H
#define REVOSDK_MATH_MTX_H
#ifdef __cplusplus
extern "C" {
#endif
#include <types.h>

void PSMTXIdentity(float[3][4]);
void PSMTXCopy(const float[3][4], float[3][4]);
void PSMTXInverse(const float[3][4], float[3][4]);
void PSMTXConcat(const float[3][4], const float[3][4], float[3][4]);
void PSMTXScaleApply(const float[3][4], float[3][4], float, float, float);

#ifdef __cplusplus
}
#endif
#endif