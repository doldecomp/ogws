#include <nw4r/g3d.h>

namespace nw4r {
namespace g3d {

/******************************************************************************
 *
 * ResByteCode
 *
 ******************************************************************************/
const u8* ResMdl::GetResByteCode(const char* pName) const {
    return static_cast<u8*>(ofs_to_obj<ResDic>(ref().toResByteCodeDic)[pName]);
}

/******************************************************************************
 *
 * ResNode
 *
 ******************************************************************************/
ResNode ResMdl::GetResNode(const char* pName) const {
    return ResNode(ofs_to_obj<ResDic>(ref().toResNodeDic)[pName]);
}

ResNode ResMdl::GetResNode(const ResName name) const {
    return ResNode(ofs_to_obj<ResDic>(ref().toResNodeDic)[name]);
}

ResNode ResMdl::GetResNode(int i) const {
    return ResNode(ofs_to_obj<ResDic>(ref().toResNodeDic)[i]);
}

ResNode ResMdl::GetResNode(u32 i) const {
    return ResNode(ofs_to_obj<ResDic>(ref().toResNodeDic)[i]);
}

u32 ResMdl::GetResNodeNumEntries() const {
    return ofs_to_obj<ResDic>(ref().toResNodeDic).GetNumData();
}

/******************************************************************************
 *
 * RexVtxPos
 *
 ******************************************************************************/
ResVtxPos ResMdl::GetResVtxPos(const ResName name) const {
    return ResVtxPos(ofs_to_obj<ResDic>(ref().toResVtxPosDic)[name]);
}

ResVtxPos ResMdl::GetResVtxPos(int i) const {
    return ResVtxPos(ofs_to_obj<ResDic>(ref().toResVtxPosDic)[i]);
}

ResVtxPos ResMdl::GetResVtxPos(u32 i) const {
    return ResVtxPos(ofs_to_obj<ResDic>(ref().toResVtxPosDic)[i]);
}

u32 ResMdl::GetResVtxPosNumEntries() const {
    return ofs_to_obj<ResDic>(ref().toResVtxPosDic).GetNumData();
}

/******************************************************************************
 *
 * ResVtxNrm
 *
 ******************************************************************************/
ResVtxNrm ResMdl::GetResVtxNrm(const ResName name) const {
    return ResVtxNrm(ofs_to_obj<ResDic>(ref().toResVtxNrmDic)[name]);
}

ResVtxNrm ResMdl::GetResVtxNrm(int i) const {
    return ResVtxNrm(ofs_to_obj<ResDic>(ref().toResVtxNrmDic)[i]);
}

ResVtxNrm ResMdl::GetResVtxNrm(u32 i) const {
    return ResVtxNrm(ofs_to_obj<ResDic>(ref().toResVtxNrmDic)[i]);
}

u32 ResMdl::GetResVtxNrmNumEntries() const {
    return ofs_to_obj<ResDic>(ref().toResVtxNrmDic).GetNumData();
}

/******************************************************************************
 *
 * ResVtxClr
 *
 ******************************************************************************/
ResVtxClr ResMdl::GetResVtxClr(const ResName name) const {
    return ResVtxClr(ofs_to_obj<ResDic>(ref().toResVtxClrDic)[name]);
}

ResVtxClr ResMdl::GetResVtxClr(int i) const {
    return ResVtxClr(ofs_to_obj<ResDic>(ref().toResVtxClrDic)[i]);
}

ResVtxClr ResMdl::GetResVtxClr(u32 i) const {
    return ResVtxClr(ofs_to_obj<ResDic>(ref().toResVtxClrDic)[i]);
}

u32 ResMdl::GetResVtxClrNumEntries() const {
    return ofs_to_obj<ResDic>(ref().toResVtxClrDic).GetNumData();
}

/******************************************************************************
 *
 * ResVtxTexCoord
 *
 ******************************************************************************/
ResVtxTexCoord ResMdl::GetResVtxTexCoord(int i) const {
    return ResVtxTexCoord(ofs_to_obj<ResDic>(ref().toResVtxTexCoordDic)[i]);
}

u32 ResMdl::GetResVtxTexCoordNumEntries() const {
    return ofs_to_obj<ResDic>(ref().toResVtxTexCoordDic).GetNumData();
}

/******************************************************************************
 *
 * ResMat
 *
 ******************************************************************************/
ResMat ResMdl::GetResMat(const char* pName) const {
    return ResMat(ofs_to_obj<ResDic>(ref().toResMatDic)[pName]);
}

ResMat ResMdl::GetResMat(const ResName name) const {
    return ResMat(ofs_to_obj<ResDic>(ref().toResMatDic)[name]);
}

ResMat ResMdl::GetResMat(int i) const {
    return ResMat(ofs_to_obj<ResDic>(ref().toResMatDic)[i]);
}

ResMat ResMdl::GetResMat(u32 i) const {
    return ResMat(ofs_to_obj<ResDic>(ref().toResMatDic)[i]);
}

u32 ResMdl::GetResMatNumEntries() const {
    return ofs_to_obj<ResDic>(ref().toResMatDic).GetNumData();
}

/******************************************************************************
 *
 * ResShp
 *
 ******************************************************************************/
ResShp ResMdl::GetResShp(const char* pName) const {
    return ResShp(ofs_to_obj<ResDic>(ref().toResShpDic)[pName]);
}

ResShp ResMdl::GetResShp(int i) const {
    return ResShp(ofs_to_obj<ResDic>(ref().toResShpDic)[i]);
}

ResShp ResMdl::GetResShp(u32 i) const {
    return ResShp(ofs_to_obj<ResDic>(ref().toResShpDic)[i]);
}

u32 ResMdl::GetResShpNumEntries() const {
    return ofs_to_obj<ResDic>(ref().toResShpDic).GetNumData();
}

/******************************************************************************
 *
 * ResTexPlttInfo
 *
 ******************************************************************************/
ResTexPlttInfo ResMdl::GetResTexPlttInfoOffsetFromTexName(int i) const {
    return ResTexPlttInfo(
        ofs_to_obj<ResDic>(ref().toResTexNameToTexPlttInfoDic)[i]);
}

u32 ResMdl::GetResTexPlttInfoOffsetFromTexNameNumEntries() const {
    return ofs_to_obj<ResDic>(ref().toResTexNameToTexPlttInfoDic).GetNumData();
}

/******************************************************************************
 *
 * ResMdl
 *
 ******************************************************************************/
bool ResMdl::Bind(const ResFile file) {
    u32 i;
    bool success = true;

    u32 matNum = GetResMatNumEntries();
    for (i = 0; i < matNum; i++) {
        success = GetResMat(i).Bind(file) && success;
    }

    return success;
}

void ResMdl::Release() {
    u32 i;

    u32 matNum = GetResMatNumEntries();
    for (i = 0; i < matNum; i++) {
        GetResMat(i).Release();
    }
}

void ResMdl::Init() {
    u32 i;

    u32 matNum = GetResMatNumEntries();
    for (i = 0; i < matNum; i++) {
        GetResMat(i).Init();
    }

    u32 shpNum = GetResShpNumEntries();
    for (i = 0; i < shpNum; i++) {
        GetResShp(i).Init();
    }

    u32 vtxPosNum = GetResVtxPosNumEntries();
    for (i = 0; i < vtxPosNum; i++) {
        GetResVtxPos(i).Init();
    }

    u32 vtxNrmNum = GetResVtxNrmNumEntries();
    for (i = 0; i < vtxNrmNum; i++) {
        GetResVtxNrm(i).Init();
    }

    u32 vtxClrNum = GetResVtxClrNumEntries();
    for (i = 0; i < vtxClrNum; i++) {
        GetResVtxClr(i).Init();
    }

    u32 texCoordNum = GetResVtxTexCoordNumEntries();
    for (i = 0; i < texCoordNum; i++) {
        GetResVtxTexCoord(i).Init();
    }
}

void ResMdl::Terminate() {
    u32 i;

    u32 shpNum = GetResShpNumEntries();
    for (i = 0; i < shpNum; i++) {
        GetResShp(i).Terminate();
    }
}

} // namespace g3d
} // namespace nw4r
