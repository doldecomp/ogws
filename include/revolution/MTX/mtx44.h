#ifndef RVL_SDK_MTX_MTX44_H
#define RVL_SDK_MTX_MTX44_H
#include <revolution/MTX/mtx.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void C_MTXFrustum(Mtx44 mtx, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void C_MTXPerspective(Mtx44 mtx, f32 fovy, f32 aspect, f32 n, f32 f);
void C_MTXOrtho(Mtx44 mtx, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);

#ifdef __cplusplus
}
#endif
#endif
