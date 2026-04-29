#ifndef RVL_SDK_MTX_MTX44_EXT_H
#define RVL_SDK_MTX_MTX44_EXT_H
#include <types.h>

#include <revolution/MTX/GeoTypes.h>
#ifdef __cplusplus
extern "C" {
#endif

// mtx44.c

void C_MTXFrustum(Mtx44Ptr m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void C_MTXPerspective(Mtx44Ptr m, f32 fovY, f32 aspect, f32 n, f32 f);
void C_MTXOrtho(Mtx44Ptr m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void C_MTX44Identity(Mtx44Ptr m);
void PSMTX44Identity(Mtx44Ptr m);
void C_MTX44Copy(CMtx44Ptr src, Mtx44Ptr dst);
void PSMTX44Copy(CMtx44Ptr src, Mtx44Ptr dst);
void C_MTX44Concat(CMtx44Ptr a, CMtx44Ptr b, Mtx44Ptr ab);
void PSMTX44Concat(CMtx44Ptr a, CMtx44Ptr b, Mtx44Ptr ab);
void C_MTX44Transpose(CMtx44Ptr src, Mtx44Ptr xPose);
void PSMTX44Transpose(CMtx44Ptr src, Mtx44Ptr xPose);
u32 C_MTX44Inverse(CMtx44Ptr src, Mtx44Ptr inv);
void C_MTX44Trans(Mtx44Ptr m, f32 xT, f32 yT, f32 zT);
void PSMTX44Trans(Mtx44Ptr m, f32 xT, f32 yT, f32 zT);
void C_MTX44TransApply(CMtx44Ptr src, Mtx44Ptr dst, f32 xT, f32 yT, f32 zT);
void PSMTX44TransApply(CMtx44Ptr src, Mtx44Ptr dst, f32 xT, f32 yT, f32 zT);
void C_MTX44Scale(Mtx44Ptr m, f32 xS, f32 yS, f32 zS);
void PSMTX44Scale(Mtx44Ptr m, f32 xS, f32 yS, f32 zS);
void C_MTX44ScaleApply(CMtx44Ptr src, Mtx44Ptr dst, f32 xS, f32 yS, f32 zS);
void PSMTX44ScaleApply(CMtx44Ptr src, Mtx44Ptr dst, f32 xS, f32 yS, f32 zS);
void C_MTX44RotRad(Mtx44Ptr m, char axis, f32 rad);
void PSMTX44RotRad(Mtx44Ptr m, char axis, f32 rad);
void C_MTX44RotTrig(Mtx44Ptr m, char axis, f32 sinA, f32 cosA);
void PSMTX44RotTrig(Mtx44Ptr m, char axis, f32 sinA, f32 cosA);
void C_MTX44RotAxisRad(MtxPtr m, CVecPtr axis, f32 rad);
void PSMTX44RotAxisRad(MtxPtr m, CVecPtr axis, f32 rad);

#define MTXFrustum C_MTXFrustum
#define MTXPerspective C_MTXPerspective
#define MTXOrtho C_MTXOrtho
#define MTX44Identity PSMTX44Identity
#define MTX44Copy PSMTX44Copy
#define MTX44Concat PSMTX44Concat
#define MTX44Transpose PSMTX44Transpose
#define MTX44Inverse C_MTX44Inverse
#define MTX44Trans PSMTX44Trans
#define MTX44TransApply PSMTX44TransApply
#define MTX44Scale PSMTX44Scale
#define MTX44ScaleApply PSMTX44ScaleApply
#define MTX44RotRad PSMTX44RotRad
#define MTX44RotTrig PSMTX44RotTrig
#define MTX44RotAxisRad PSMTX44RotAxisRad

// mtx44vec.c

void C_MTX44MultVec(CMtx44Ptr m, CVecPtr src, VecPtr dst);
void PSMTX44MultVec(CMtx44Ptr m, CVecPtr src, VecPtr dst);
void C_MTX44MultVecArray(CMtx44Ptr m, CVecPtr srcBase, VecPtr dstBase,
                         u32 count);
void PSMTX44MultVecArray(CMtx44Ptr m, CVecPtr srcBase, VecPtr dstBase,
                         u32 count);
void C_MTX44MultVecSR(CMtx44Ptr m, CVecPtr src, VecPtr dst);
void PSMTX44MultVecSR(CMtx44Ptr m, CVecPtr src, VecPtr dst);
void C_MTX44MultVecArraySR(CMtx44Ptr m, CVecPtr srcBase, VecPtr dstBase,
                           u32 count);
void PSMTX44MultVecArraySR(CMtx44Ptr m, CVecPtr srcBase, VecPtr dstBase,
                           u32 count);

#define MTX44MultVec PSMTX44MultVec
#define MTX44MultVecArray PSMTX44MultVecArray
#define MTX44MultVecSR PSMTX44MultVecSR
#define MTX44MultVecArraySR PSMTX44MultVecArraySR

#ifdef __cplusplus
}
#endif
#endif
