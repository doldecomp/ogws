#ifndef NW4R_G3D_RESANMCLR_H
#define NW4R_G3D_RESANMCLR_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_resanm.h>
#include <nw4r/g3d/g3d_rescommon.h>
#include <nw4r/g3d/g3d_resdict.h>

namespace nw4r {
namespace g3d {

struct ResAnmClrInfoData {
    u16 numFrame;     // at 0x0
    u16 numMaterial;  // at 0x2
    AnmPolicy policy; // at 0x4
};

struct ResAnmClrAnmData {
    u32 mask;              // at 0x0
    ResColorAnmData color; // at 0x4
};

struct ResAnmClrMatData {
    s32 name;                 // at 0x0
    u32 flags;                // at 0x4
    ResAnmClrAnmData anms[1]; // at 0x8

    static const int NUM_OF_CLA_COLOR = 11;

    // Two bits in 'flags' for each animation
    enum Flag { FLAG_ANM_EXISTS = (1 << 0), FLAG_ANM_CONSTANT = (1 << 1) };
};

struct ResAnmClrData {
    ResBlockHeaderData header; // at 0x0
    u32 revision;              // at 0x8
    s32 toResFileData;         // at 0xC
    s32 toClrDataDic;          // at 0x10
    s32 name;                  // at 0x14
    s32 original_path;         // at 0x18
    ResAnmClrInfoData info;    // at 0x1C
};

class ResAnmClr : public ResCommon<ResAnmClrData> {
public:
    static const u32 SIGNATURE = 'CLR0';
    static const int REVISION = 3;

public:
    ResAnmClr(void* pData) : ResCommon(pData) {}

    u32 GetRevision() const {
        return ref().revision;
    }

    bool CheckRevision() const {
        return ref().revision == REVISION;
    }

    void GetAnmResult(ClrAnmResult* pResult, u32 id, f32 frame) const;

    const ResAnmClrMatData* GetMatAnm(int id) const {
        return static_cast<ResAnmClrMatData*>(
            ofs_to_obj<ResDic>(ref().toClrDataDic)[id]);
    }
    const ResAnmClrMatData* GetMatAnm(u32 id) const {
        return static_cast<ResAnmClrMatData*>(
            ofs_to_obj<ResDic>(ref().toClrDataDic)[id]);
    }

    int GetNumFrame() const {
        return ref().info.numFrame;
    }

    int GetNumMaterial() const {
        return ref().info.numMaterial;
    }

    AnmPolicy GetAnmPolicy() const {
        return ref().info.policy;
    }
};

} // namespace g3d
} // namespace nw4r

#endif
