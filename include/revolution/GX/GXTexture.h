#ifndef RVL_SDK_GX_TEXTURE_H
#define RVL_SDK_GX_TEXTURE_H
#include <types.h>

#include <revolution/GX/GXInternal.h>
#include <revolution/GX/GXTypes.h>
#ifdef __cplusplus
extern "C" {
#endif

GX_PUBLIC_STRUCT_DECL(GXTexObj, 32);
GX_PUBLIC_STRUCT_DECL(GXTlutObj, 0x0C);

GX_PUBLIC_STRUCT_DECL(GXTexRegion, 16);
GX_PUBLIC_STRUCT_DECL(GXTlutRegion, 16);

typedef GXTexRegion* (*GXTexRegionCallback)(const GXTexObj* pObj,
                                            GXTexMapID map);

typedef GXTlutRegion* (*GXTlutRegionCallback)(u32 id);

void __GXSetSUTexRegs(void);

void GXInitTexObj(GXTexObj* obj, void* image, u16 w, u16 h, GXTexFmt fmt,
                  GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, GXBool mipmap);
void GXInitTexObjCI(GXTexObj*, void*, u16, u16, GXTexFmt, GXTexWrapMode,
                    GXTexWrapMode, GXBool, u32);
void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt,
                     f32 min_lod, f32 max_lod, f32 lod_bias, GXBool bias_clamp,
                     GXBool do_edge_lod, GXAnisotropy max_aniso);

void GXInitTexObjWrapMode(GXTexObj* obj, GXTexWrapMode wrap_s,
                          GXTexWrapMode wrap_t);

void GXInitTexObjFilter(GXTexObj* obj, GXTexFilter min_filt,
                        GXTexFilter mag_filt);

void GXGetTexObjAll(GXTexObj* obj, void* image_ptr, u16* width, u16* height,
                    GXTexFmt* format, GXTexWrapMode* wrap_s,
                    GXTexWrapMode* wrap_t, GXBool* mipmap);

void GXGetTexObjLODAll(GXTexObj* obj, GXTexFilter* min_filt,
                       GXTexFilter* mag_filt, f32* minLod, f32* maxLod,
                       f32* lodBias, GXBool* biasClampEnable,
                       GXBool* edgeLodEnable, GXAnisotropy* anisotropy);

GXTexWrapMode GXGetTexObjWrapS(GXTexObj* obj);
GXTexWrapMode GXGetTexObjWrapT(GXTexObj* obj);

u16 GXGetTexObjWidth(const GXTexObj* obj);
u16 GXGetTexObjHeight(const GXTexObj* obj);
GXTexFmt GXGetTexObjFmt(const GXTexObj* obj);
GXBool GXGetTexObjMipMap(const GXTexObj* obj);

void GXLoadTexObj(const GXTexObj*, GXTexMapID);

void GXInitTexObjTlut(GXTexObj*, u32);
u32 GXGetTexObjTlut(GXTexObj*);

void GXInitTlutObj(GXTlutObj*, void*, GXTlutFmt, u16);

void GXLoadTlut(GXTlutObj*, u32);

void GXInvalidateTexAll(void);

void GXInitTexCacheRegion(GXTexRegion* pRegion, GXBool is_32b_mipmap,
                          u32 tmem_even, GXTexCacheSize size_even, u32 tmem_odd,
                          GXTexCacheSize size_odd);

void GXInitTlutRegion(GXTlutRegion* pRegion, u32 tmem_addr,
                      GXTlutSize tlut_size);

GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback callback);
GXTlutRegionCallback GXSetTlutRegionCallback(GXTlutRegionCallback callback);

u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, GXBool mipmap,
                       u8 max_lod);

void GXSetTexCoordScaleManually(GXTexCoordID coord, GXBool enable, u16 ss,
                                u16 ts);

void GXSetTexCoordCylWrap(GXTexCoordID coord, GXBool s_enable, GXBool t_enable);

#ifdef __cplusplus
}
#endif
#endif
