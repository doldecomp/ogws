#ifndef RVL_FACE_LIBRARY_INTERNAL_TYPES_H
#define RVL_FACE_LIBRARY_INTERNAL_TYPES_H
#include <RVLFaceLib/RFL_Types.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Common types used throughout many RFL files.
 *
 * To avoid circular depencies, common structures and all enums have been moved
 * here.
 *
 * Everything is organized in alphabetical order (when possible, otherwise
 * dependency order).
 */

/**
 * Common enums
 */

typedef enum {
    RFLiArcID_Beard,
    RFLiArcID_Eye,
    RFLiArcID_Eyebrow,
    RFLiArcID_Faceline,
    RFLiArcID_FaceTex,
    RFLiArcID_ForeHead,
    RFLiArcID_Glass,
    RFLiArcID_GlassTex,
    RFLiArcID_Hair,
    RFLiArcID_Mask,
    RFLiArcID_Mole,
    RFLiArcID_Mouth,
    RFLiArcID_Mustache,
    RFLiArcID_Nose,
    RFLiArcID_Nline,
    RFLiArcID_NlineTex,
    RFLiArcID_Cap,
    RFLiArcID_CapTex,
    RFLiArcID_Max
} RFLiArcID;

typedef enum {
    RFLiAsyncTag_WriteFile,
    RFLiAsyncTag_WriteCloseFile,
    RFLiAsyncTag_ReadFile,
    RFLiAsyncTag_ReadCloseFile,
    RFLiAsyncTag_ReadCache,
    RFLiAsyncTag_ReadCacheClose,
    RFLiAsyncTag_WriteHDBFile,
    RFLiAsyncTag_WriteHDBFileClose,
    RFLiAsyncTag_ReadHDBFile,
    RFLiAsyncTag_ReadHDBFileClose,
    RFLiAsyncTag_CreateAsync,
    RFLiAsyncTag_OpenAsync,
    RFLiAsyncTag_SeekAsync,
    RFLiAsyncTag_ReadAsync,
    RFLiAsyncTag_WriteAsync,
    RFLiAsyncTag_CloseAsync,
    RFLiAsyncTag_GetLengthAsync,
    RFLiAsyncTag_DeleteAsync,
    RFLiAsyncTag_CreateDirAsync,

    RFLiAsyncTag_Max
} RFLiAsyncTag;

typedef enum {
    RFLiFileBrokenType_DBNotFound,
    RFLiFileBrokenType_DBBroken,
    RFLiFileBrokenType_ResBroken,
    RFLiFileBrokenType_Corrupt,

    RFLiFileBrokenType_Max
} RFLiFileBrokenType;

typedef enum {
    RFLiFileType_Database,
    RFLiFileType_Resource,

    RFLiFileType_Max
} RFLiFileType;

typedef enum {
    RFLi_MASKRSL_32 = 32,
    RFLi_MASKRSL_64 = 64,
    RFLi_MASKRSL_128 = 128,
    RFLi_MASKRSL_256 = 256
} RFLi_MASKRSL;

typedef enum {
    RFLiOpenType_Multi,
    RFLiOpenType_Single,
    RFLiOpenType_Opened
} RFLiOpenType;

typedef enum {
    RFLiPartsShp_Nose,
    RFLiPartsShp_Forehead,
    RFLiPartsShp_Faceline,
    RFLiPartsShp_Hair,
    RFLiPartsShp_Cap,
    RFLiPartsShp_Beard,
    RFLiPartsShp_Noseline,
    RFLiPartsShp_Mask,
    RFLiPartsShp_Glass,

    RFLiPartsShp_Max
} RFLiPartsShp;

typedef enum {
    RFLiPartsShpTex_Face,
    RFLiPartsShpTex_Cap,
    RFLiPartsShpTex_Noseline,
    RFLiPartsShpTex_Glass,

    RFLiPartsShpTex_Max
} RFLiPartsShpTex;

typedef enum {
    RFLiPartsTex_Eye,
    RFLiPartsTex_Eyebrow,
    RFLiPartsTex_Mouth,
    RFLiPartsTex_Mustache,
    RFLiPartsTex_Mole,

    RFLiPartsTex_Max
} RFLiPartsTex;

/**
 * Common typedefs
 */

typedef void (*RFLiSystemCallback)(void);
typedef void (*RFLiAccessCallback)(void);
typedef void (*RFLiAlarmCallback)(RFLiFileType type);
typedef void (*RFLiDatabaseCallback)(void);

#ifdef __cplusplus
}
#endif
#endif
