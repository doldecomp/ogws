#ifndef RVL_SDK_MTX_MTX_H
#define RVL_SDK_MTX_MTX_H
#include <types.h>

#include <revolution/MTX/GeoTypes.h>
#ifdef __cplusplus
extern "C" {
#endif

// mtx.c

void C_MTXIdentity(MtxPtr m);
void PSMTXIdentity(MtxPtr m);
void C_MTXCopy(CMtxPtr src, MtxPtr dst);
void PSMTXCopy(CMtxPtr src, MtxPtr dst);
void C_MTXConcat(CMtxPtr a, CMtxPtr b, MtxPtr ab);
void PSMTXConcat(CMtxPtr mA, CMtxPtr mB, MtxPtr mAB);
void C_MTXConcatArray(CMtxPtr a, CMtxPtr srcBase, MtxPtr dstBase, u32 count);
void PSMTXConcatArray(CMtxPtr a, CMtxPtr srcBase, MtxPtr dstBase, u32 count);
void C_MTXTranspose(CMtxPtr src, MtxPtr xPose);
void PSMTXTranspose(CMtxPtr src, MtxPtr xPose);
u32 C_MTXInverse(CMtxPtr src, MtxPtr inv); // DWARF reveals it's not BOOL
u32 PSMTXInverse(CMtxPtr src, MtxPtr inv);
u32 C_MTXInvXpose(CMtxPtr src, MtxPtr invX); // DWARF reveals it's not BOOL
u32 PSMTXInvXpose(CMtxPtr src, MtxPtr invX);
void C_MTXRotRad(MtxPtr m, char axis, f32 rad);
void PSMTXRotRad(MtxPtr m, char axis, f32 rad);
void C_MTXRotTrig(MtxPtr m, char axis, f32 sinA, f32 cosA);
void PSMTXRotTrig(MtxPtr m, char axis, f32 sinA, f32 cosA);
void C_MTXRotAxisRad(MtxPtr m, CVecPtr axis, f32 rad);
void PSMTXRotAxisRad(MtxPtr m, CVecPtr axis, f32 rad);
void C_MTXTrans(MtxPtr m, f32 xT, f32 yT, f32 zT);
void PSMTXTrans(MtxPtr m, f32 xT, f32 yT, f32 zT);
void C_MTXTransApply(CMtxPtr src, MtxPtr dst, f32 xT, f32 yT, f32 zT);
void PSMTXTransApply(CMtxPtr src, MtxPtr dst, f32 xT, f32 yT, f32 zT);
void C_MTXScale(MtxPtr m, f32 xS, f32 yS, f32 zS);
void PSMTXScale(MtxPtr m, f32 xS, f32 yS, f32 zS);
void C_MTXScaleApply(CMtxPtr src, MtxPtr dst, f32 xS, f32 yS, f32 zS);
void PSMTXScaleApply(CMtxPtr src, MtxPtr dst, f32 xS, f32 yS, f32 zS);
void C_MTXQuat(MtxPtr m, CQuaternionPtr q);
void PSMTXQuat(MtxPtr m, CQuaternionPtr q);
void C_MTXReflect(MtxPtr m, CVecPtr point, CVecPtr normal);
void PSMTXReflect(MtxPtr m, CVecPtr point, CVecPtr normal);
void C_MTXLookAt(MtxPtr m, CVecPtr camPos, CVecPtr camUp, CPoint3dPtr target);
void C_MTXLightFrustum(MtxPtr m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 scaleS,
                       f32 scaleT, f32 transS, f32 transT);
void C_MTXLightPerspective(MtxPtr m, f32 fovY, f32 aspect, f32 scaleS,
                           f32 scaleT, f32 transS, f32 transT);
void C_MTXLightOrtho(MtxPtr m, f32 t, f32 b, f32 l, f32 r, f32 scaleS,
                     f32 scaleT, f32 transS, f32 transT);

#define MTXIdentity PSMTXIdentity
#define MTXCopy PSMTXCopy
#define MTXConcat PSMTXConcat
#define MTXConcatArray PSMTXConcatArray
#define MTXTranspose PSMTXTranspose
#define MTXInverse PSMTXInverse
#define MTXInvXpose PSMTXInvXpose
#define MTXRotRad PSMTXRotRad
#define MTXRotTrig PSMTXRotTrig
#define MTXRotAxisRad PSMTXRotAxisRad
#define MTXTrans PSMTXTrans
#define MTXTransApply PSMTXTransApply
#define MTXScale PSMTXScale
#define MTXScaleApply PSMTXScaleApply
#define MTXQuat PSMTXQuat
#define MTXReflect PSMTXReflect
#define MTXLookAt C_MTXLookAt
#define MTXLightFrustum C_MTXLightFrustum
#define MTXLightPerspective C_MTXLightPerspective
#define MTXLightOrtho C_MTXLightOrtho

// mtxvec.c

void C_MTXMultVec(CMtxPtr m, CVecPtr src, VecPtr dst);
void PSMTXMultVec(CMtxPtr m, CVecPtr src, VecPtr dst);
void C_MTXMultVecArray(CMtxPtr m, CVecPtr srcBase, VecPtr dstBase, u32 count);
void PSMTXMultVecArray(CMtxPtr m, CVecPtr srcBase, VecPtr dstBase, u32 count);
void C_MTXMultVecSR(CMtxPtr m, CVecPtr src, VecPtr dst);
void PSMTXMultVecSR(CMtxPtr m, CVecPtr src, VecPtr dst);
void C_MTXMultVecArraySR(CMtxPtr m, CVecPtr srcBase, VecPtr dstBase, u32 count);
void PSMTXMultVecArraySR(CMtxPtr m, CVecPtr srcBase, VecPtr dstBase, u32 count);

#define MTXMultVec PSMTXMultVec
#define MTXMultVecArray PSMTXMultVecArray
#define MTXMultVecSR PSMTXMultVecSR
#define MTXMultVecArraySR PSMTXMultVecArraySR

// mtxstack.c

void MTXInitStack(MtxStackPtr sPtr, u32 numMtx);
MtxPtr MTXPush(MtxStackPtr sPtr, CMtxPtr m);
MtxPtr MTXPushFwd(MtxStackPtr sPtr, CMtxPtr m);
MtxPtr MTXPushInv(MtxStackPtr sPtr, CMtxPtr m);
MtxPtr MTXPushInvXpose(MtxStackPtr sPtr, CMtxPtr m);
MtxPtr MTXPop(MtxStackPtr sPtr);
MtxPtr MTXGetStackPtr(MtxStackPtr sPtr);

// vec.c

void C_VECAdd(CVecPtr a, CVecPtr b, VecPtr ab);
void PSVECAdd(CVecPtr vec1, CVecPtr vec2, VecPtr dst);
void C_VECSubtract(CVecPtr a, CVecPtr b, VecPtr a_b);
void PSVECSubtract(CVecPtr vec1, CVecPtr vec2, VecPtr dst);
void C_VECScale(CVecPtr src, VecPtr dst, f32 scale);
void PSVECScale(CVecPtr src, VecPtr dst, f32 mult);
void C_VECNormalize(CVecPtr src, VecPtr unit);
void PSVECNormalize(CVecPtr src, VecPtr unit);
f32 C_VECSquareMag(CVecPtr v);
f32 PSVECSquareMag(CVecPtr vec1);
f32 C_VECMag(CVecPtr v);
f32 PSVECMag(CVecPtr v);
f32 C_VECDotProduct(CVecPtr a, CVecPtr b);
f32 PSVECDotProduct(CVecPtr vec1, CVecPtr vec2);
void C_VECCrossProduct(CVecPtr a, CVecPtr b, VecPtr axb);
void PSVECCrossProduct(CVecPtr vec1, CVecPtr vec2, VecPtr dst);
void C_VECHalfAngle(CVecPtr a, CVecPtr b, VecPtr half);
void C_VECReflect(CVecPtr src, CVecPtr normal, VecPtr dst);
f32 C_VECSquareDistance(CVecPtr a, CVecPtr b);
f32 PSVECSquareDistance(CVecPtr a, CVecPtr b);
f32 C_VECDistance(CVecPtr a, CVecPtr b);
f32 PSVECDistance(CVecPtr a, CVecPtr b);

#define VECAdd PSVECAdd
#define VECSubtract PSVECSubtract
#define VECScale PSVECScale
#define VECNormalize PSVECNormalize
#define VECSquareMag PSVECSquareMag
#define VECMag PSVECMag
#define VECDotProduct PSVECDotProduct
#define VECCrossProduct PSVECCrossProduct
#define VECHalfAngle C_VECHalfAngle
#define VECReflect C_VECReflect
#define VECSquareDistance PSVECSquareDistance
#define VECDistance PSVECDistance

// quat.c

void C_QUATAdd(CQuaternionPtr p, CQuaternionPtr q, QuaternionPtr r);
void PSQUATAdd(CQuaternionPtr p, CQuaternionPtr q, QuaternionPtr r);
void C_QUATSubtract(CQuaternionPtr p, CQuaternionPtr q, QuaternionPtr r);
void PSQUATSubtract(CQuaternionPtr p, CQuaternionPtr q, QuaternionPtr r);
void C_QUATMultiply(CQuaternionPtr p, CQuaternionPtr q, QuaternionPtr pq);
void PSQUATMultiply(CQuaternionPtr p, CQuaternionPtr q, QuaternionPtr pq);
void C_QUATScale(CQuaternionPtr q, QuaternionPtr r, f32 scale);
void PSQUATScale(CQuaternionPtr q, QuaternionPtr r, f32 mult);
f32 C_QUATDotProduct(CQuaternionPtr p, CQuaternionPtr q);
f32 PSQUATDotProduct(CQuaternionPtr p, CQuaternionPtr q);
void C_QUATNormalize(CQuaternionPtr src, QuaternionPtr unit);
void PSQUATNormalize(CQuaternionPtr src, QuaternionPtr unit);
void C_QUATInverse(CQuaternionPtr src, QuaternionPtr inv);
void PSQUATInverse(CQuaternionPtr src, QuaternionPtr inv);
void C_QUATDivide(CQuaternionPtr p, CQuaternionPtr q, QuaternionPtr r);
void PSQUATDivide(CQuaternionPtr p, CQuaternionPtr q, QuaternionPtr r);
void C_QUATExp(CQuaternionPtr q, QuaternionPtr r);
void C_QUATLogN(CQuaternionPtr q, QuaternionPtr r);
void C_QUATMakeClosest(CQuaternionPtr q, CQuaternionPtr qto, QuaternionPtr r);
void C_QUATRotAxisRad(QuaternionPtr r, CVecPtr axis, f32 rad);
void C_QUATMtx(QuaternionPtr r, CMtxPtr m);
void C_QUATLerp(CQuaternionPtr p, CQuaternionPtr q, QuaternionPtr r, f32 t);
void C_QUATSlerp(CQuaternionPtr p, CQuaternionPtr q, QuaternionPtr r, f32 t);
void C_QUATSquad(CQuaternionPtr p, CQuaternionPtr a, CQuaternionPtr b,
                 CQuaternionPtr q, QuaternionPtr r, f32 t);
void C_QUATCompA(CQuaternionPtr qprev, CQuaternionPtr q, CQuaternionPtr qnext,
                 QuaternionPtr a);

#define QUATAdd PSQUATAdd
#define QUATSubtract PSQUATSubtract
#define QUATMultiply PSQUATMultiply
#define QUATScale PSQUATScale
#define QUATDotProduct PSQUATDotProduct
#define QUATNormalize PSQUATNormalize
#define QUATInverse PSQUATInverse
#define QUATDivide PSQUATDivide
#define QUATExp C_QUATExp
#define QUATLogN C_QUATLogN
#define QUATMakeClosest C_QUATMakeClosest
#define QUATRotAxisRad C_QUATRotAxisRad
#define QUATMtx C_QUATMtx
#define QUATLerp C_QUATLerp
#define QUATSlerp C_QUATSlerp
#define QUATSquad C_QUATSquad
#define QUATCompA C_QUATCompA

// psmtx.c

void PSMTXReorder(const f32* src, f32* dst);
void PSMTXROMultVecArray(CROMtxPtr m, CVecPtr srcBase, VecPtr dstBase,
                         u32 count);

#define MTXReorder PSMTXReorder
#define MTXROMultVecArray PSMTXROMultVecArray

#ifdef __cplusplus
}
#endif
#endif
