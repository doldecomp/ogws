#ifndef NW4R_G3D_RESMDL_H
#define NW4R_G3D_RESMDL_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_rescommon.h>
#include <nw4r/g3d/g3d_resdict.h>
#include <nw4r/g3d/g3d_resmat.h>
#include <nw4r/g3d/g3d_resnode.h>
#include <nw4r/g3d/g3d_resshp.h>
#include <nw4r/g3d/g3d_resvtx.h>

#include <nw4r/math.h>

namespace nw4r {
namespace g3d {

/******************************************************************************
 *
 * ResMdlInfo
 *
 ******************************************************************************/
struct ResMdlInfoDataTypedef {
    enum ScalingRule {
        SCALINGRULE_STANDARD,
        SCALINGRULE_SOFTIMAGE,
        SCALINGRULE_MAYA
    };

    enum TexMatrixMode {
        TEXMATRIXMODE_MAYA,
        TEXMATRIXMODE_XSI,
        TEXMATRIXMODE_3DSMAX
    };

    enum EnvelopeMatrixMode {
        EVPMATRIXMODE_NORMAL,
        EVPMATRIXMODE_APPROX,
        EVPMATRIXMODE_EXACT
    };
};

struct ResMdlInfoData : ResMdlInfoDataTypedef {
    u32 size;                   // at 0x0
    s32 toResMdlData;           // at 0x4
    ScalingRule scaling_rule;   // at 0x8
    TexMatrixMode tex_mtx_mode; // at 0xC
    s32 vertex_size;            // at 0x10
    s32 triangle_size;          // at 0x14
    s32 original_path;          // at 0x18
    u32 numViewMtx;             // at 0x1C
    bool need_nrm_mtx_array;    // at 0x20
    bool need_tex_mtx_array;    // at 0x21
    bool is_valid_volume;       // at 0x22
    u8 envelope_mtx_mode;       // at 0x23
    s32 toMtxIDToNodeID;        // at 0x24
    math::_VEC3 volume_min;     // at 0x28
    math::_VEC3 volume_max;     // at 0x34
};

class ResMdlInfo : public ResCommon<ResMdlInfoData>,
                   public ResMdlInfoDataTypedef {
public:
    explicit ResMdlInfo(void* pData) : ResCommon(pData) {}
};

/******************************************************************************
 *
 * ResMdl
 *
 ******************************************************************************/
struct ResMdlData {
    ResBlockHeaderData header;         // at 0x0
    u32 revision;                      // at 0x8
    s32 toResFileData;                 // at 0xC
    s32 toResByteCodeDic;              // at 0x10
    s32 toResNodeDic;                  // at 0x14
    s32 toResVtxPosDic;                // at 0x18
    s32 toResVtxNrmDic;                // at 0x1C
    s32 toResVtxClrDic;                // at 0x20
    s32 toResVtxTexCoordDic;           // at 0x24
    s32 toResMatDic;                   // at 0x28
    s32 toResTevDic;                   // at 0x2C
    s32 toResShpDic;                   // at 0x30
    s32 toResTexNameToTexPlttInfoDic;  // at 0x34
    s32 toResPlttNameToTexPlttInfoDic; // at 0x38
    s32 name;                          // at 0x3C
    ResMdlInfoData info;               // at 0x40
};

class ResMdl : public ResCommon<ResMdlData> {
public:
    static const u32 SIGNATURE = 'MDL0';
    static const int REVISION = 9;

public:
    explicit ResMdl(void* pData) : ResCommon(pData) {}

    void Init();
    void Terminate();

    bool Bind(ResFile file);
    void Release();

    u32 GetRevision() const {
        return ref().revision;
    }

    bool CheckRevision() const {
        return GetRevision() == REVISION;
    }

    u8* GetResByteCode(const char* pName) const;

    ResNode GetResNode(const char* pName) const;
    ResNode GetResNode(ResName name) const;
    ResNode GetResNode(int i) const;
    ResNode GetResNode(u32 i) const;
    u32 GetResNodeNumEntries() const;

    ResVtxPos GetResVtxPos(ResName name) const;
    ResVtxPos GetResVtxPos(int i) const;
    ResVtxPos GetResVtxPos(u32 i) const;
    u32 GetResVtxPosNumEntries() const;

    ResVtxNrm GetResVtxNrm(ResName name) const;
    ResVtxNrm GetResVtxNrm(int i) const;
    ResVtxNrm GetResVtxNrm(u32 i) const;
    u32 GetResVtxNrmNumEntries() const;

    ResVtxClr GetResVtxClr(ResName name) const;
    ResVtxClr GetResVtxClr(int i) const;
    ResVtxClr GetResVtxClr(u32 i) const;
    u32 GetResVtxClrNumEntries() const;

    ResVtxTexCoord GetResVtxTexCoord(int i) const;
    u32 GetResVtxTexCoordNumEntries() const;

    ResMat GetResMat(const char* pName) const;
    ResMat GetResMat(ResName name) const;
    ResMat GetResMat(int i) const;
    ResMat GetResMat(u32 i) const;
    u32 GetResMatNumEntries() const;

    ResShp GetResShp(const char* pName) const;
    ResShp GetResShp(int i) const;
    ResShp GetResShp(u32 i) const;
    u32 GetResShpNumEntries() const;

    ResTexPlttInfo GetResTexPlttInfoOffsetFromTexName(int i) const;
    u32 GetResTexPlttInfoOffsetFromTexNameNumEntries() const;

    ResMdlInfo GetResMdlInfo() {
        return ResMdlInfo(&ref().info);
    }
    ResMdlInfo GetResMdlInfo() const {
        return ResMdlInfo(const_cast<ResMdlInfoData*>(&ref().info));
    }
};

} // namespace g3d
} // namespace nw4r

#endif
