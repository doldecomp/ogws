#ifndef REVOSDK_MATH_MTX44_H
#define REVOSDK_MATH_MTX44_H
#ifdef __cplusplus
extern "C" {
#endif
#include <types.h>

typedef float Mtx44[4][4];

UNKTYPE C_MTXPerspective(Mtx44, float, float, float, float);
UNKTYPE C_MTXFrustum(Mtx44, float, float, float, float, float, float);
UNKTYPE C_MTXOrtho(Mtx44, float, float, float, float, float, float);

#ifdef __cplusplus
}
#endif
#endif