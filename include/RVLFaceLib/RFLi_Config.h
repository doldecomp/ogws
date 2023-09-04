#ifndef RVL_FACE_LIBRARY_INTENRAL_CONFIG_H
#define RVL_FACE_LIBRARY_INTERNAL_CONFIG_H
#include <RVLFaceLib/RFLi_Types.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Char data constraints
 */

#define RFLi_MAX_FACELINE_TYPE 7
#define RFLi_MAX_FACELINE_COLOR 5
#define RFLi_MAX_FACELINE_TEXTURE 11

#define RFLi_MAX_HAIR_TYPE 71
#define RFLi_MAX_HAIR_COLOR 7

#define RFLi_MAX_EYE_TYPE 47
#define RFLi_MAX_EYE_COLOR 5
#define RFLi_MAX_EYE_SCALE 7
#define RFLi_MAX_EYE_ROTATE 7
#define RFLi_MAX_EYE_X 12
#define RFLi_MAX_EYE_Y 18

#define RFLi_MAX_EYEBROW_TYPE 23
#define RFLi_MAX_EYEBROW_COLOR 7
#define RFLi_MAX_EYEBROW_SCALE 8
#define RFLi_MAX_EYEBROW_ROTATE 11
#define RFLi_MAX_EYEBROW_X 12
#define RFLi_MIN_EYEBROW_Y 3
#define RFLi_MAX_EYEBROW_Y 18

#define RFLi_MAX_NOSE_TYPE 11
#define RFLi_MAX_NOSE_SCALE 8
#define RFLi_MAX_NOSE_Y 18

#define RFLi_MAX_MOUTH_TYPE 23
#define RFLi_MAX_MOUTH_COLOR 2
#define RFLi_MAX_MOUTH_SCALE 8
#define RFLi_MAX_MOUTH_Y 18

#define RFLi_MAX_BEARD_MUSTACHE 3
#define RFLi_MAX_BEARD_TYPE 3
#define RFLi_MAX_BEARD_COLOR 7
#define RFLi_MAX_BEARD_SCALE 8
#define RFLi_MAX_BEARD_Y 16

#define RFLi_MAX_GLASS_TYPE 8
#define RFLi_MAX_GLASS_COLOR 5
#define RFLi_MAX_GLASS_SCALE 7
#define RFLi_MAX_GLASS_Y 20

#define RFLi_MAX_MOLE_TYPE 1
#define RFLi_MAX_MOLE_SCALE 8
#define RFLi_MAX_MOLE_X 16
#define RFLi_MAX_MOLE_Y 30

#define RFLi_MAX_BODY_HEIGHT 128
#define RFLi_MAX_BODY_BUILD 128

/**
 * Create ID
 */

#define RFLi_CREATE_ID_TEMPORARY 0x20000000
#define RFLi_CREATE_ID_NOT_SPECIAL 0x80000000

/**
 * Tables
 */

static const u8 RFLi_EYE_ROT_OFFSET[50] = {
    29, 28, 28, 28, 29, 28, 28, 28, 29, 28, 28, 28, 28, 29, 29, 28, 28,
    28, 29, 29, 28, 29, 28, 29, 29, 28, 29, 28, 28, 29, 28, 28, 28, 29,
    29, 29, 28, 28, 29, 29, 29, 28, 28, 29, 29, 29, 29, 29, 28, 28};

static const u8 RFLi_EYEBROW_ROT_OFFSET[24] = {26, 26, 27, 25, 26, 25, 26, 25,
                                               28, 25, 26, 24, 27, 27, 26, 26,
                                               25, 25, 26, 26, 27, 26, 25, 27};

#ifdef __cplusplus
}
#endif
#endif
