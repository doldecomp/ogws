#ifndef RVL_FACE_LIBRARY_INTERNAL_MAKE_RANDOM_FACE_H
#define RVL_FACE_LIBRARY_INTERNAL_MAKE_RANDOM_FACE_H
#include <RVLFaceLib/RFLi_Types.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void RFLi_MakeRandomFace(RFLiCharInfo* info, RFLSex sex, RFLAge age,
                         RFLRace race);

#ifdef __cplusplus
}
#endif
#endif
