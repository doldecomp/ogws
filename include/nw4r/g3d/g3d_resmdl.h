#ifndef NW4R_G3D_RESMDL_H
#define NW4R_G3D_RESMDL_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_rescommon.h>
#include <nw4r/g3d/g3d_resdict.h>
#include <nw4r/g3d/g3d_resnode.h>

namespace nw4r {
namespace g3d {

struct ResMdlData {
    ResBlockHeaderData header;        // at 0x0
    u32 revision;                     // at 0x8
    s32 toResFileData;                // at 0xC
    s32 toResByteCodeDic;             // at 0x10
    s32 toResNodeDic;                 // at 0x14
    s32 toResVtxPosDic;               // at 0x18
    s32 toResVtxNrmDic;               // at 0x1C
    s32 toResVtxClrDic;               // at 0x20
    s32 toResVtxTexCoordDic;          // at 0x24
    s32 toResMatDic;                  // at 0x28
    s32 toResTevDic;                  // at 0x2C
    s32 toResShpDic;                  // at 0x30
    s32 toResTexNameToTexPlttInfoDic; // at 0x34
};

class ResMdl : public ResCommon<ResMdlData> {
public:
    static const u32 SIGNATURE = 'MDL0';
    static const int REVISION = 9;

public:
    ResMdl(void* pData) : ResCommon(pData) {}

    bool CheckRevision() const {
        return ref().revision == REVISION;
    }

    u8* GetResByteCode(const char*) const;

    ResNode GetResNode(const char*) const;
    ResNode GetResNode(ResName) const;
    ResNode GetResNode(int) const;
    ResNode GetResNode(u32) const;
    u32 GetResNodeNumEntries() const;

    ResVtxPos GetResVtxPos(ResName) const;
    ResVtxPos GetResVtxPos(int) const;
    ResVtxPos GetResVtxPos(u32) const;
    u32 GetResVtxPosNumEntries() const;

    ResVtxNrm GetResVtxNrm(ResName) const;
    ResVtxNrm GetResVtxNrm(int) const;
    ResVtxNrm GetResVtxNrm(u32) const;
    u32 GetResVtxNrmNumEntries() const;

    ResVtxClr GetResVtxClr(ResName) const;
    ResVtxClr GetResVtxClr(int) const;
    ResVtxClr GetResVtxClr(u32) const;
    u32 GetResVtxClrNumEntries() const;

    ResVtxTexCoord GetResVtxTexCoord(int) const;
    u32 GetResVtxTexCoordNumEntries() const {
        return ofs_to_obj<ResDic>(ref().toResVtxTexCoordDic).GetNumData();
    }

    ResMat GetResMat(const char*) const;
    ResMat GetResMat(ResName) const;
    ResMat GetResMat(int) const;
    ResMat GetResMat(u32) const;
    u32 GetResMatNumEntries() const;

    ResShp GetResShp(const char*) const;
    ResShp GetResShp(int) const;
    ResShp GetResShp(u32) const;
    u32 GetResShpNumEntries() const;

    ResTexPlttInfo GetResTexPlttInfoOffsetFromTexName(int) const;
    u32 GetResTexPlttInfoOffsetFromTexNameNumEntries() const;

    bool Bind(ResFile);
    void Release();
    void Init();
    void Terminate();
};

} // namespace g3d
} // namespace nw4r

#endif
