#ifndef NW4R_G3D_RESFILE_H
#define NW4R_G3D_RESFILE_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_resanmchr.h>
#include <nw4r/g3d/g3d_resanmclr.h>
#include <nw4r/g3d/g3d_resanmscn.h>
#include <nw4r/g3d/g3d_resanmshp.h>
#include <nw4r/g3d/g3d_resanmtexpat.h>
#include <nw4r/g3d/g3d_resanmtexsrt.h>
#include <nw4r/g3d/g3d_resanmvis.h>
#include <nw4r/g3d/g3d_rescommon.h>
#include <nw4r/g3d/g3d_resmdl.h>
#include <nw4r/g3d/g3d_respltt.h>
#include <nw4r/g3d/g3d_restex.h>

#include <nw4r/ut.h>

namespace nw4r {
namespace g3d {

struct ResTopLevelDictData {
    ut::BinaryBlockHeader header; // at 0x0
    ResDicData topLevel;          // at 0x8
};

struct ResFileData {
    ut::BinaryFileHeader fileHeader; // at 0x0
    ResTopLevelDictData dict;        // at 0x10
};

class ResFile : public ResCommon<ResFileData> {
public:
    explicit ResFile(void* pData) : ResCommon(pData) {}

    void Init();
    void Terminate();
    bool CheckRevision() const;

    bool Bind(ResFile file);
    void Release();

    bool Bind() {
        return Bind(*this);
    }

    ResMdl GetResMdl(const char* pName) const;
    ResMdl GetResMdl(int i) const;
    ResMdl GetResMdl(u32 i) const;

    ResPltt GetResPltt(const char* pName) const;
    ResPltt GetResPltt(ResName name) const;
    ResPltt GetResPltt(int i) const;
    ResPltt GetResPltt(u32 i) const;

    ResTex GetResTex(const char* pName) const;
    ResTex GetResTex(ResName name) const;
    ResTex GetResTex(int i) const;
    ResTex GetResTex(u32 i) const;

    ResAnmChr GetResAnmChr(const char* pName) const;
    ResAnmChr GetResAnmChr(int i) const;
    ResAnmChr GetResAnmChr(u32 i) const;

    ResAnmVis GetResAnmVis(const char* pName) const;
    ResAnmVis GetResAnmVis(int i) const;
    ResAnmVis GetResAnmVis(u32 i) const;

    ResAnmClr GetResAnmClr(const char* pName) const;
    ResAnmClr GetResAnmClr(int i) const;
    ResAnmClr GetResAnmClr(u32 i) const;

    ResAnmTexPat GetResAnmTexPat(const char* pName) const;
    ResAnmTexPat GetResAnmTexPat(int i) const;
    ResAnmTexPat GetResAnmTexPat(u32 i) const;

    ResAnmTexSrt GetResAnmTexSrt(const char* pName) const;
    ResAnmTexSrt GetResAnmTexSrt(int i) const;
    ResAnmTexSrt GetResAnmTexSrt(u32 i) const;

    ResAnmShp GetResAnmShp(const char* pName) const;
    ResAnmShp GetResAnmShp(int i) const;
    ResAnmShp GetResAnmShp(u32 i) const;

    ResAnmScn GetResAnmScn(const char* pName) const;
    ResAnmScn GetResAnmScn(int i) const;
    ResAnmScn GetResAnmScn(u32 i) const;

    u32 GetResMdlNumEntries() const;
    u32 GetResPlttNumEntries() const;
    u32 GetResTexNumEntries() const;
    u32 GetResAnmChrNumEntries() const;
    u32 GetResAnmVisNumEntries() const;
    u32 GetResAnmClrNumEntries() const;
    u32 GetResAnmTexPatNumEntries() const;
    u32 GetResAnmTexSrtNumEntries() const;
    u32 GetResAnmShpNumEntries() const;
    u32 GetResAnmScnNumEntries() const;
};

} // namespace g3d
} // namespace nw4r

#endif
