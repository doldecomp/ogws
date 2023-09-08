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

void GXInitTexObj(GXTexObj* obj, void* image, u16 w, u16 h, GXTexFmt fmt,
                  GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, GXBool mipmap);
void GXInitTexObjCI(GXTexObj*, void*, u16, u16, GXTexFmt, GXTexWrapMode,
                    GXTexWrapMode, GXBool, u32);
void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt,
                     f32 min_lod, f32 max_lod, f32 lod_bias, GXBool bias_clamp,
                     GXBool do_edge_lod, GXAnisotropy max_aniso);

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
