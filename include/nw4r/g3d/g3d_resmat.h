#ifndef NW4R_G3D_RESMAT_H
#define NW4R_G3D_RESMAT_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_rescommon.h>
#include <nw4r/g3d/g3d_respltt.h>
#include <nw4r/g3d/g3d_restex.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

namespace nw4r {
namespace g3d {

/******************************************************************************
 *
 * ResGenMode
 *
 ******************************************************************************/
struct ResGenModeData {
    u8 nTexGens;         // at 0x0
    u8 nChans;           // at 0x1
    u8 nTevs;            // at 0x2
    u8 nInds;            // at 0x3
    GXCullMode cullMode; // at 0x4
};

class ResGenMode : public ResCommon<ResGenModeData> {
public:
    explicit ResGenMode(void* pData) : ResCommon(pData) {}
};

/******************************************************************************
 *
 * ResMatMisc
 *
 ******************************************************************************/
struct ResMatMiscData {
    bool zCompLoc;              // at 0x0
    s8 light_set_idx;           // at 0x1
    s8 fog_idx;                 // at 0x2
    u8 _;                       // at 0x3
    u8 indirect_method[4];      // at 0x4
    s8 normal_map_ref_light[4]; // at 0x8
};

class ResMatMisc : public ResCommon<ResMatMiscData> {
public:
    explicit ResMatMisc(void* pData) : ResCommon(pData) {}
};

/******************************************************************************
 *
 * ResTexPlttInfo
 *
 ******************************************************************************/
struct ResTexPlttInfoData {
    s32 nameTex;            // at 0x0
    s32 namePltt;           // at 0x4
    ResTexData* pTexData;   // at 0x8
    ResPlttData* pPlttData; // at 0xC
    GXTexMapID mapID;       // at 0x10
    GXTlut tlutID;          // at 0x14
    GXTexWrapMode wrap_s;   // at 0x18
    GXTexWrapMode wrap_t;   // at 0x1C
    GXTexFilter min_filt;   // at 0x20
    GXTexFilter mag_filt;   // at 0x24
    f32 lod_bias;           // at 0x28
    GXAnisotropy max_aniso; // at 0x2C
    bool bias_clamp;        // at 0x30
    bool do_edge_lod;       // at 0x31
    u8 _0;                  // at 0x32
    u8 _1;                  // at 0x33
};

class ResTexPlttInfo : public ResCommon<ResTexPlttInfoData> {
public:
    explicit ResTexPlttInfo(void* pData) : ResCommon(pData) {}
};

/******************************************************************************
 *
 * ResMatTexCoordGen
 *
 ******************************************************************************/
struct ResMatTexCoordGenData {};

class ResMatTexCoordGen : public ResCommon<ResMatTexCoordGenData> {
public:
    explicit ResMatTexCoordGen(void* pData) : ResCommon(pData) {}

    bool GXGetTexCoordGen2(GXTexCoordID, GXTexGenType*, GXTexGenSrc*, u8*,
                           u32*);
    void GXSetTexCoordGen2(GXTexCoordID, GXTexGenType, GXTexGenSrc, u8, u32);
    void DCStore(bool);
};

/******************************************************************************
 *
 * ResMatDL
 *
 ******************************************************************************/
struct ResMatDLData {
    char UNK_0x0[0xE0];
    ResMatTexCoordGenData texCoordGenData; // at 0xE0
};

/******************************************************************************
 *
 * ResTexObj
 *
 ******************************************************************************/
struct ResTexObjData {};

class ResTexObj : public ResCommon<ResTexObjData> {
public:
    explicit ResTexObj(void* pData) : ResCommon(pData) {}
};

/******************************************************************************
 *
 * ResTlutObj
 *
 ******************************************************************************/
struct ResTlutObjData {};

class ResTlutObj : public ResCommon<ResTlutObjData> {
public:
    explicit ResTlutObj(void* pData) : ResCommon(pData) {}
};

/******************************************************************************
 *
 * ResTexSrt
 *
 ******************************************************************************/
struct ResTexSrtData {};

class ResTexSrt : public ResCommon<ResTexSrtData> {
public:
    explicit ResTexSrt(void* pData) : ResCommon(pData) {}

    void SetMapMode(u32, u32, int, int);
};

/******************************************************************************
 *
 * ResMatChan
 *
 ******************************************************************************/
struct Chan {
    u32 flag;           // at 0x0
    GXColor matColor;   // at 0x4
    GXColor ambColor;   // at 0x8
    u32 paramChanCtrlC; // at 0xC
    u32 paramChanCtrlA; // at 0x10
};

struct ResChanData {
    Chan chan[2]; // at 0x0
};

class ResMatChan : public ResCommon<ResChanData> {
public:
    explicit ResMatChan(void* pData) : ResCommon(pData) {}
};

/******************************************************************************
 *
 * ResMat
 *
 ******************************************************************************/
struct ResMatData {
    u32 size;                   // at 0x0
    s32 toResMdlData;           // at 0x4
    s32 name;                   // at 0x8
    u32 id;                     // at 0xC
    u32 flag;                   // at 0x10
    ResGenModeData genMode;     // at 0x14
    ResMatMiscData misc;        // at 0x1C
    s32 toResTevData;           // at 0x28
    u32 numResTexPlttInfo;      // at 0x2C
    s32 toResTexPlttInfo;       // at 0x30
    s32 toResUserData;          // at 0x34
    s32 toResMatDLData;         // at 0x38
    ResTexObjData texObjData;   // at 0x3C
    ResTlutObjData tlutObjData; // at 0x140
    ResTexSrtData texSrtData;   // at 0x1A4
    ResChanData chan;           // at 0x3EC
};

class ResMat : public ResCommon<ResMatData> {
public:
    explicit ResMat(void* pData) : ResCommon(pData) {}

    ResTexSrt GetResTexSrt() {
        return ResTexSrt(&ref().texSrtData);
    }

    ResMatTexCoordGen GetResMatTexCoordGen() {
        ResMatDLData* dlData = ofs_to_ptr<ResMatDLData>(ref().toResMatDLData);
        return ResMatTexCoordGen(&dlData->texCoordGenData);
    }

    bool Bind(ResFile);
    UNKTYPE Release();
    UNKTYPE Init();
};
} // namespace g3d
} // namespace nw4r

#endif