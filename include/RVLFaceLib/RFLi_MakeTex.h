#ifndef RVL_FACE_LIBRARY_INTERNAL_MAKE_TEX_H
#define RVL_FACE_LIBRARY_INTERNAL_MAKE_TEX_H
#include <RVLFaceLib/RFLi_Types.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void RFLiMakeTexture(const RFLiCharInfo* info, u8** texBuffer,
                     RFLResolution res);

RFLi_MASKRSL RFLiGetMaxMaskRsl(RFLResolution);

u32 RFLiGetMaskBufSize(RFLResolution);

#ifdef __cplusplus
}
#endif
#endif
