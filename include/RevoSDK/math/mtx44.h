#ifndef REVOSDK_MATH_MTX44_H
#define REVOSDK_MATH_MTX44_H
#ifdef __cplusplus
extern "C" {
#endif
#include <types.h>

typedef float Mtx44[4][4];

UNKTYPE C_MTXPerspective(float, float, float, float, Mtx44);
UNKTYPE C_MTXFrustum(float, float, float, float, float, float, Mtx44);
UNKTYPE C_MTXOrtho(float, float, float, float, float, float, Mtx44);

#ifdef __cplusplus
}
#endif
#endif