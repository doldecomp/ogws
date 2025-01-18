#ifndef RVL_SDK_MTX_VEC_H
#define RVL_SDK_MTX_VEC_H
#include <revolution/MTX/mtx.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void PSVECAdd(const Vec* a, const Vec* b, Vec* sum);
void PSVECScale(const Vec* in, Vec* out, f32 scale);
void PSVECNormalize(const Vec* in, Vec* out);
f32 PSVECMag(const Vec* v);
f32 PSVECDotProduct(const Vec* a, const Vec* b);
void PSVECCrossProduct(const Vec* a, const Vec* b, Vec* prod);
f32 PSVECSquareDistance(const Vec* a, const Vec* b);
void C_VECHalfAngle(const Vec* a, const Vec* b, Vec* half);

#ifdef __cplusplus
}
#endif
#endif
