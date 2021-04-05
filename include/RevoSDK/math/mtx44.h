#ifndef REVOSDK_MATH_MTX44_H
#define REVOSDK_MATH_MTX44_H
#ifdef __cplusplus
extern "C" {
#endif
#include <types.h>

UNKTYPE C_MTXPerspective(float, float, float, float, float[4][4]);
UNKTYPE C_MTXFrustum(float, float, float, float, float, float, float[4][4]);
UNKTYPE C_MTXOrtho(float, float, float, float, float, float, float[4][4]);

#ifdef __cplusplus
}
#endif
#endif