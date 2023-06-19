#ifndef REVOSDK_MATH_MTX_H
#define REVOSDK_MATH_MTX_H
#ifdef __cplusplus
extern "C" {
#endif
#include <types.h>

typedef float Mtx[3][4];

void PSMTXIdentity(Mtx);
void PSMTXCopy(const Mtx, Mtx);
void PSMTXInverse(const Mtx, Mtx);
void PSMTXConcat(const Mtx, const Mtx, Mtx);
void PSMTXRotAxisRad(Mtx, const struct Vec *, float);
void PSMTXTransApply(const Mtx, Mtx, float, float, float);
void PSMTXScale(Mtx, float, float, float);
void PSMTXScaleApply(const Mtx, Mtx, float, float, float);

void C_MTXLookAt(Mtx, struct Vec *, struct Vec *, struct Vec *);
void C_MTXLightOrtho(Mtx, float, float, float, float, float, float, float, float);
void C_MTXLightFrustum(Mtx, float, float, float, float, float, float, float, float, float);
void C_MTXLightPerspective(Mtx, float, float, float, float, float, float);

#ifdef __cplusplus
}
#endif
#endif