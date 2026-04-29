#ifndef RVL_SDK_MTX_GEO_TYPES_H
#define RVL_SDK_MTX_GEO_TYPES_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    f32 x, y, z;
} Vec;
typedef Vec* VecPtr;
typedef const Vec* CVecPtr;
typedef Vec Point3d;
typedef Vec* Point3dPtr;
typedef const Vec* CPoint3dPtr;

typedef struct {
    s16 x, y, z;
} S16Vec;
typedef S16Vec* S16VecPtr;
typedef const S16Vec* CS16VecPtr;

typedef struct {
    f32 x, y;
} Vec2;
typedef Vec2* Vec2Ptr;
typedef const Vec2* CVec2Ptr;

typedef struct {
    f32 x, y, z, w;
} Quaternion;
typedef Quaternion* QuaternionPtr;
typedef const Quaternion* CQuaternionPtr;
typedef Quaternion Qtrn;
typedef Quaternion* QtrnPtr;
typedef const Quaternion* CQtrnPtr;

typedef f32 Mtx[3][4];
typedef f32 (*MtxPtr)[4];
typedef const f32 (*CMtxPtr)[4];

typedef f32 ROMtx[4][3];
typedef f32 (*ROMtxPtr)[3];
typedef const f32 (*CROMtxPtr)[3];

typedef f32 Mtx44[4][4];
typedef f32 (*Mtx44Ptr)[4];
typedef const f32 (*CMtx44Ptr)[4];

typedef struct {
    u32 numMtx;
    MtxPtr stackBase;
    MtxPtr stackPtr;
} MtxStack;
typedef MtxStack* MtxStackPtr;
typedef const MtxStack* CMtxStackPtr;

#ifdef __cplusplus
}
#endif
#endif
