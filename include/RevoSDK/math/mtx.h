#ifndef REVOSDK_MATH_MTX_H
#define REVOSDK_MATH_MTX_H
#ifdef __cplusplus
extern "C" {
#endif
#include <types.h>
#include <RevoSDK/math/mtxvec.h>

void PSMTXIdentity(float[3][4]);
void PSMTXCopy(const float[3][4], float[3][4]);
void PSMTXInverse(const float[3][4], float[3][4]);
void PSMTXConcat(const float[3][4], const float[3][4], float[3][4]);
void PSMTXRotAxisRad(float[3][4], const Vec *, float);
void PSMTXScaleApply(const float[3][4], float[3][4], float, float, float);

void C_MTXLookAt(float[3][4], Vec *, Vec *, Vec *);
void C_MTXLightOrtho(float[3][4], float, float, float, float, float, float, float, float);
void C_MTXLightFrustum(float[3][4], float, float, float, float, float, float, float, float, float);
void C_MTXLightPerspective(float[3][4], float, float, float, float, float, float);

#ifdef __cplusplus
}
#endif
#endif