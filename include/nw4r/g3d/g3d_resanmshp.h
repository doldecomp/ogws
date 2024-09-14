#ifndef NW4R_G3D_RESANMSHP_H
#define NW4R_G3D_RESANMSHP_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_resanm.h>
#include <nw4r/g3d/g3d_rescommon.h>

namespace nw4r {
namespace g3d {

struct ResAnmShpInfoData {
    u16 numFrame;     // at 0x0
    u16 numVtxName;   // at 0x2
    AnmPolicy policy; // at 0x4
};

struct ResAnmShpData {
    ResBlockHeaderData header; // at 0x0
    u32 revision;              // at 0x8
    s32 toResFileData;         // at 0xC
    s32 toShpDataDic;          // at 0x10
    s32 toVtxNameArray;        // at 0x14
    s32 name;                  // at 0x18
    s32 original_path;         // at 0x1C
    ResAnmShpInfoData info;    // at 0x20
};

class ResAnmShp : public ResCommon<ResAnmShpData> {
public:
    static const u32 SIGNATURE = 'SHP0';
    static const int REVISION = 3;

public:
    ResAnmShp(void* pData) : ResCommon(pData) {}

    u32 GetRevision() const {
        return ref().revision;
    }

    bool CheckRevision() const {
        return ref().revision == REVISION;
    }
};

} // namespace g3d
} // namespace nw4r

#endif