#include <nw4r/g3d.h>

namespace nw4r {
namespace g3d {
namespace {

NW4R_G3D_RESFILE_NAME_DEF(Models, "3DModels(NW4R)");
NW4R_G3D_RESFILE_NAME_DEF(Pltts, "Palettes(NW4R)");
NW4R_G3D_RESFILE_NAME_DEF(Textures, "Textures(NW4R)");
NW4R_G3D_RESFILE_NAME_DEF(AnmChr, "AnmChr(NW4R)");
NW4R_G3D_RESFILE_NAME_DEF(AnmVis, "AnmVis(NW4R)");
NW4R_G3D_RESFILE_NAME_DEF(AnmClr, "AnmClr(NW4R)");
NW4R_G3D_RESFILE_NAME_DEF(AnmTexPat, "AnmTexPat(NW4R)");
NW4R_G3D_RESFILE_NAME_DEF(AnmTexSrt, "AnmTexSrt(NW4R)");
NW4R_G3D_RESFILE_NAME_DEF(AnmShp, "AnmShp(NW4R)");
NW4R_G3D_RESFILE_NAME_DEF(AnmScn, "AnmScn(NW4R)");
NW4R_G3D_RESFILE_NAME_DEF(Ext, "External");

} // namespace

/******************************************************************************
 *
 * ResMdl
 *
 ******************************************************************************/
ResMdl ResFile::GetResMdl(const char* pName) const {
    void* pResMdlDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_Models)];

    if (pResMdlDicData != NULL) {
        return ResMdl(ResDic(pResMdlDicData)[pName]);
    }

    return ResMdl(NULL);
}

ResMdl ResFile::GetResMdl(int i) const {
    void* pResMdlDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_Models)];

    if (pResMdlDicData != NULL) {
        return ResMdl(ResDic(pResMdlDicData)[i]);
    }

    return ResMdl(NULL);
}

ResMdl ResFile::GetResMdl(u32 i) const {
    return GetResMdl(static_cast<int>(i));
}

/******************************************************************************
 *
 * ResPltt
 *
 ******************************************************************************/
ResPltt ResFile::GetResPltt(const char* pName) const {
    void* pResPlttDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_Pltts)];

    if (pResPlttDicData != NULL) {
        return ResPltt(ResDic(pResPlttDicData)[pName]);
    }

    return ResPltt(NULL);
}

ResPltt ResFile::GetResPltt(ResName name) const {
    void* pResPlttDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_Pltts)];

    if (pResPlttDicData != NULL) {
        return ResPltt(ResDic(pResPlttDicData)[name]);
    }

    return ResPltt(NULL);
}

ResPltt ResFile::GetResPltt(int i) const {
    void* pResPlttDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_Pltts)];

    if (pResPlttDicData != NULL) {
        return ResPltt(ResDic(pResPlttDicData)[i]);
    }

    return ResPltt(NULL);
}

ResPltt ResFile::GetResPltt(u32 i) const {
    return GetResPltt(static_cast<int>(i));
}

/******************************************************************************
 *
 * ResTex
 *
 ******************************************************************************/
ResTex ResFile::GetResTex(const char* pName) const {
    void* pResTexDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_Textures)];

    if (pResTexDicData != NULL) {
        return ResTex(ResDic(pResTexDicData)[pName]);
    }

    return ResTex(NULL);
}

ResTex ResFile::GetResTex(ResName name) const {
    void* pResTexDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_Textures)];

    if (pResTexDicData != NULL) {
        return ResTex(ResDic(pResTexDicData)[name]);
    }

    return ResTex(NULL);
}

ResTex ResFile::GetResTex(int i) const {
    void* pResTexDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_Textures)];

    if (pResTexDicData != NULL) {
        return ResTex(ResDic(pResTexDicData)[i]);
    }

    return ResTex(NULL);
}

ResTex ResFile::GetResTex(u32 i) const {
    return GetResTex(static_cast<int>(i));
}

/******************************************************************************
 *
 * ResAnmChr
 *
 ******************************************************************************/
ResAnmChr ResFile::GetResAnmChr(const char* pName) const {
    void* pResAnmChrDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmChr)];

    if (pResAnmChrDicData != NULL) {
        return ResAnmChr(ResDic(pResAnmChrDicData)[pName]);
    }

    return ResAnmChr(NULL);
}

ResAnmChr ResFile::GetResAnmChr(int i) const {
    void* pResAnmChrDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmChr)];

    if (pResAnmChrDicData != NULL) {
        return ResAnmChr(ResDic(pResAnmChrDicData)[i]);
    }

    return ResAnmChr(NULL);
}

ResAnmChr ResFile::GetResAnmChr(u32 i) const {
    return GetResAnmChr(static_cast<int>(i));
}

/******************************************************************************
 *
 * ResAnmVis
 *
 ******************************************************************************/
ResAnmVis ResFile::GetResAnmVis(const char* pName) const {
    void* pResAnmVisDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmVis)];

    if (pResAnmVisDicData != NULL) {
        return ResAnmVis(ResDic(pResAnmVisDicData)[pName]);
    }

    return ResAnmVis(NULL);
}

ResAnmVis ResFile::GetResAnmVis(int i) const {
    void* pResAnmVisDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmVis)];

    if (pResAnmVisDicData != NULL) {
        return ResAnmVis(ResDic(pResAnmVisDicData)[i]);
    }

    return ResAnmVis(NULL);
}

ResAnmVis ResFile::GetResAnmVis(u32 i) const {
    return GetResAnmVis(static_cast<int>(i));
}

/******************************************************************************
 *
 * ResAnmClr
 *
 ******************************************************************************/
ResAnmClr ResFile::GetResAnmClr(const char* pName) const {
    void* pResAnmClrDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmClr)];

    if (pResAnmClrDicData != NULL) {
        return ResAnmClr(ResDic(pResAnmClrDicData)[pName]);
    }

    return ResAnmClr(NULL);
}

ResAnmClr ResFile::GetResAnmClr(int i) const {
    void* pResAnmClrDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmClr)];

    if (pResAnmClrDicData != NULL) {
        return ResAnmClr(ResDic(pResAnmClrDicData)[i]);
    }

    return ResAnmClr(NULL);
}

ResAnmClr ResFile::GetResAnmClr(u32 i) const {
    return GetResAnmClr(static_cast<int>(i));
}

/******************************************************************************
 *
 * ResAnmTexPat
 *
 ******************************************************************************/
ResAnmTexPat ResFile::GetResAnmTexPat(const char* pName) const {
    void* pResAnmTexPatDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmTexPat)];

    if (pResAnmTexPatDicData != NULL) {
        return ResAnmTexPat(ResDic(pResAnmTexPatDicData)[pName]);
    }

    return ResAnmTexPat(NULL);
}

ResAnmTexPat ResFile::GetResAnmTexPat(int i) const {
    void* pResAnmTexPatDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmTexPat)];

    if (pResAnmTexPatDicData != NULL) {
        return ResAnmTexPat(ResDic(pResAnmTexPatDicData)[i]);
    }

    return ResAnmTexPat(NULL);
}

ResAnmTexPat ResFile::GetResAnmTexPat(u32 i) const {
    return GetResAnmTexPat(static_cast<int>(i));
}

/******************************************************************************
 *
 * ResAnmTexSrt
 *
 ******************************************************************************/
ResAnmTexSrt ResFile::GetResAnmTexSrt(const char* pName) const {
    void* pResAnmTexSrtDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmTexSrt)];

    if (pResAnmTexSrtDicData != NULL) {
        return ResAnmTexSrt(ResDic(pResAnmTexSrtDicData)[pName]);
    }

    return ResAnmTexSrt(NULL);
}

ResAnmTexSrt ResFile::GetResAnmTexSrt(int i) const {
    void* pResAnmTexSrtDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmTexSrt)];

    if (pResAnmTexSrtDicData != NULL) {
        return ResAnmTexSrt(ResDic(pResAnmTexSrtDicData)[i]);
    }

    return ResAnmTexSrt(NULL);
}

ResAnmTexSrt ResFile::GetResAnmTexSrt(u32 i) const {
    return GetResAnmTexSrt(static_cast<int>(i));
}

/******************************************************************************
 *
 * ResAnmShp
 *
 ******************************************************************************/
ResAnmShp ResFile::GetResAnmShp(const char* pName) const {
    void* pResAnmShpDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmShp)];

    if (pResAnmShpDicData != NULL) {
        return ResAnmShp(ResDic(pResAnmShpDicData)[pName]);
    }

    return ResAnmShp(NULL);
}

ResAnmShp ResFile::GetResAnmShp(int i) const {
    void* pResAnmShpDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmShp)];

    if (pResAnmShpDicData != NULL) {
        return ResAnmShp(ResDic(pResAnmShpDicData)[i]);
    }

    return ResAnmShp(NULL);
}

ResAnmShp ResFile::GetResAnmShp(u32 i) const {
    return GetResAnmShp(static_cast<int>(i));
}

/******************************************************************************
 *
 * ResAnmScn
 *
 ******************************************************************************/
ResAnmScn ResFile::GetResAnmScn(const char* pName) const {
    void* pResAnmScnDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmScn)];

    if (pResAnmScnDicData != NULL) {
        return ResAnmScn(ResDic(pResAnmScnDicData)[pName]);
    }

    return ResAnmScn(NULL);
}

ResAnmScn ResFile::GetResAnmScn(int i) const {
    void* pResAnmScnDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmScn)];

    if (pResAnmScnDicData != NULL) {
        return ResAnmScn(ResDic(pResAnmScnDicData)[i]);
    }

    return ResAnmScn(NULL);
}

ResAnmScn ResFile::GetResAnmScn(u32 i) const {
    return GetResAnmScn(static_cast<int>(i));
}

/******************************************************************************
 *
 * Miscellaneous
 *
 ******************************************************************************/
u32 ResFile::GetResMdlNumEntries() const {
    void* pResMdlDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_Models)];

    if (pResMdlDicData != NULL) {
        return ResDic(pResMdlDicData).GetNumData();
    }

    return 0;
}

u32 ResFile::GetResPlttNumEntries() const {
    void* pResPlttDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_Pltts)];

    if (pResPlttDicData != NULL) {
        return ResDic(pResPlttDicData).GetNumData();
    }

    return 0;
}

u32 ResFile::GetResTexNumEntries() const {
    void* pResTexDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_Textures)];

    if (pResTexDicData != NULL) {
        return ResDic(pResTexDicData).GetNumData();
    }

    return 0;
}

u32 ResFile::GetResAnmChrNumEntries() const {
    void* pResAnmChrDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmChr)];

    if (pResAnmChrDicData != NULL) {
        return ResDic(pResAnmChrDicData).GetNumData();
    }

    return 0;
}

u32 ResFile::GetResAnmVisNumEntries() const {
    void* pResAnmVisDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmVis)];

    if (pResAnmVisDicData != NULL) {
        return ResDic(pResAnmVisDicData).GetNumData();
    }

    return 0;
}

u32 ResFile::GetResAnmClrNumEntries() const {
    void* pResAnmClrDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmClr)];

    if (pResAnmClrDicData != NULL) {
        return ResDic(pResAnmClrDicData).GetNumData();
    }

    return 0;
}

u32 ResFile::GetResAnmTexPatNumEntries() const {
    void* pResAnmTexPatDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmTexPat)];

    if (pResAnmTexPatDicData != NULL) {
        return ResDic(pResAnmTexPatDicData).GetNumData();
    }

    return 0;
}

u32 ResFile::GetResAnmTexSrtNumEntries() const {
    void* pResAnmTexSrtDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmTexSrt)];

    if (pResAnmTexSrtDicData != NULL) {
        return ResDic(pResAnmTexSrtDicData).GetNumData();
    }

    return 0;
}

u32 ResFile::GetResAnmShpNumEntries() const {
    void* pResAnmShpDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmShp)];

    if (pResAnmShpDicData != NULL) {
        return ResDic(pResAnmShpDicData).GetNumData();
    }

    return 0;
}

u32 ResFile::GetResAnmScnNumEntries() const {
    void* pResAnmScnDicData = ResDic(const_cast<ResDicData*>(
        &ref().dict.topLevel))[ResName(&ResNameData_AnmScn)];

    if (pResAnmScnDicData != NULL) {
        return ResDic(pResAnmScnDicData).GetNumData();
    }

    return 0;
}

bool ResFile::Bind(const ResFile file) {
    u32 i;
    bool success = true;

    u32 mdlNum = GetResMdlNumEntries();
    for (i = 0; i < mdlNum; i++) {
        success = GetResMdl(i).Bind(file) && success;
    }

    u32 anmTexPatNum = GetResAnmTexPatNumEntries();
    for (i = 0; i < anmTexPatNum; i++) {
        // @bug Success value clobbered by most recent result
        success = GetResAnmTexPat(i).Bind(file);
    }

    return success;
}

void ResFile::Release() {
    u32 i;

    u32 mdlNum = GetResMdlNumEntries();
    for (i = 0; i < mdlNum; i++) {
        GetResMdl(i).Release();
    }

    u32 anmTexPatNum = GetResAnmTexPatNumEntries();
    for (i = 0; i < anmTexPatNum; i++) {
        GetResAnmTexPat(i).Release();
    }
}

void ResFile::Init() {
    u32 i;

    u32 mdlNum = GetResMdlNumEntries();
    for (i = 0; i < mdlNum; i++) {
        GetResMdl(i).Init();
    }

    u32 texNum = GetResTexNumEntries();
    for (i = 0; i < texNum; i++) {
        GetResTex(i).Init();
    }

    u32 plttNum = GetResPlttNumEntries();
    for (i = 0; i < plttNum; i++) {
        GetResPltt(i).Init();
    }
}

void ResFile::Terminate() {
    u32 i;

    u32 mdlNum = GetResMdlNumEntries();
    for (i = 0; i < mdlNum; i++) {
        GetResMdl(i).Terminate();
    }
}

bool ResFile::CheckRevision() const {
    u32 i;

    u32 mdlNum = GetResMdlNumEntries();
    for (i = 0; i < mdlNum; i++) {
        if (!GetResMdl(i).CheckRevision()) {
            return false;
        }
    }

    u32 texNum = GetResTexNumEntries();
    for (i = 0; i < texNum; i++) {
        if (!GetResTex(i).CheckRevision()) {
            return false;
        }
    }

    u32 plttNum = GetResPlttNumEntries();
    for (i = 0; i < plttNum; i++) {
        if (!GetResPltt(i).CheckRevision()) {
            return false;
        }
    }

    u32 anmChrNum = GetResAnmChrNumEntries();
    for (i = 0; i < anmChrNum; i++) {
        if (!GetResAnmChr(i).CheckRevision()) {
            return false;
        }
    }

    u32 anmVisNum = GetResAnmVisNumEntries();
    for (i = 0; i < anmVisNum; i++) {
        if (!GetResAnmVis(i).CheckRevision()) {
            return false;
        }
    }

    u32 anmClrNum = GetResAnmClrNumEntries();
    for (i = 0; i < anmClrNum; i++) {
        if (!GetResAnmClr(i).CheckRevision()) {
            return false;
        }
    }

    u32 anmTexPatNum = GetResAnmTexPatNumEntries();
    for (i = 0; i < anmTexPatNum; i++) {
        if (!GetResAnmTexPat(i).CheckRevision()) {
            return false;
        }
    }

    u32 anmTexSrtNum = GetResAnmTexSrtNumEntries();
    for (i = 0; i < anmTexSrtNum; i++) {
        if (!GetResAnmTexSrt(i).CheckRevision()) {
            return false;
        }
    }

    u32 anmShpNum = GetResAnmShpNumEntries();
    for (i = 0; i < anmShpNum; i++) {
        if (!GetResAnmShp(i).CheckRevision()) {
            return false;
        }
    }

    u32 anmScnNum = GetResAnmScnNumEntries();
    for (i = 0; i < anmScnNum; i++) {
        if (!GetResAnmScn(i).CheckRevision()) {
            return false;
        }
    }

    return true;
}

} // namespace g3d
} // namespace nw4r

// clang-format off
DECOMP_FORCEACTIVE(g3d_resfile_cpp,
                   nw4r::g3d::ResNameData_Ext);
// clang-format on
