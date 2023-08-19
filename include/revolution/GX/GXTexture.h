#ifndef RVL_SDK_GX_TEXTURE_H
#define RVL_SDK_GX_TEXTURE_H
#include <revolution/GX/GXInternal.h>
#include <revolution/GX/GXTypes.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

GX_DECL_PUBLIC_STRUCT(GXTexObj, 32);
GX_DECL_PUBLIC_STRUCT(GXTlutObj, 32);

void __GXSetSUTexRegs(void);

void GXInitTexObj(GXTexObj*, void*, u16, u16, GXTexFmt, GXTexWrapMode,
                  GXTexWrapMode, u8);
void GXInitTexObjCI(GXTexObj*, void*, u16, u16, GXTexFmt, GXTexWrapMode,
                  GXTexWrapMode, u8, u32);
void GXInitTexObjLOD(GXTexObj*, GXTexFilter, GXTexFilter, f32, f32, f32, u8, u8,
                     GXAnisotropy);

void GXLoadTexObj(GXTexObj*, GXTexMapID);

u32 GXGetTexObjTlut(GXTexObj*);

void GXInitTlutObj(GXTlutObj*, void*, GXTlutFmt, u16);

void GXInvalidateTexAll(void);

// TODO
UNKTYPE GXSetTexCoordScaleManually(UNKWORD, UNKWORD, UNKWORD, UNKWORD);
UNKTYPE GXSetTexCoordCylWrap(UNKWORD, UNKWORD, UNKWORD);

#ifdef __cplusplus
}
#endif
#endif
