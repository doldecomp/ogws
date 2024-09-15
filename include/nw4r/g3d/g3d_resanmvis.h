#ifndef NW4R_G3D_RESANMVIS_H
#define NW4R_G3D_RESANMVIS_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_resanm.h>
#include <nw4r/g3d/g3d_rescommon.h>
#include <nw4r/g3d/g3d_resdict.h>

namespace nw4r {
namespace g3d {

struct ResAnmVisAnmData {
    s32 name;                        // at 0x0
    u32 flags;                       // at 0x4
    ResBoolAnmFramesData visibility; // at 0x8

    enum Flag {
        FLAG_ANM_CONSTANT_VALUE = (1 << 0),
        FLAG_ANM_IS_CONSTANT = (1 << 1)
    };
};

struct ResAnmVisInfoData {
    u16 numFrame;     // at 0x0
    u16 numNode;      // at 0x2
    AnmPolicy policy; // at 0x4
};

struct ResAnmVisData {
    ResBlockHeaderData header; // at 0x0
    u32 revision;              // at 0x8
    s32 toResFileData;         // at 0xC
    s32 toVisDataDic;          // at 0x10
    s32 name;                  // at 0x14
    s32 original_path;         // at 0x18
    ResAnmVisInfoData info;    // at 0x1C
};

class ResAnmVis : public ResCommon<ResAnmVisData> {
public:
    static const u32 SIGNATURE = 'VIS0';
    static const int REVISION = 3;

public:
    ResAnmVis(void* pData) : ResCommon(pData) {}

    u32 GetRevision() const {
        return ref().revision;
    }

    bool CheckRevision() const {
        return GetRevision() == REVISION;
    }

    bool GetAnmResult(u32 id, f32 frame) const;

    const ResAnmVisAnmData* GetNodeAnm(int i) const {
        return static_cast<ResAnmVisAnmData*>(
            ofs_to_obj<ResDic>(ref().toVisDataDic)[i]);
    }
    const ResAnmVisAnmData* GetNodeAnm(u32 i) const {
        return static_cast<ResAnmVisAnmData*>(
            ofs_to_obj<ResDic>(ref().toVisDataDic)[i]);
    }

    int GetNumFrame() const {
        return ref().info.numFrame;
    }

    int GetNumNode() const {
        return ref().info.numNode;
    }

    AnmPolicy GetAnmPolicy() const {
        return ref().info.policy;
    }
};

} // namespace g3d
} // namespace nw4r

#endif
