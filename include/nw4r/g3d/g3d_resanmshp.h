#ifndef NW4R_G3D_RESANMSHP_H
#define NW4R_G3D_RESANMSHP_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_resanm.h>
#include <nw4r/g3d/g3d_rescommon.h>

namespace nw4r {
namespace g3d {

// Forward declarations
struct ShpAnmResult;

struct ResAnmShpAnmData {
    u32 flags;                 // at 0x0
    s32 name;                  // at 0x4
    u16 baseShapeVtxIdx;       // at 0x8
    u16 numKeyShape;           // at 0xA
    u32 constFlags;            // at 0xC
    s32 toAnmIdxToVtxIdxTable; // at 0x10
    ResAnmData anms[1];        // at 0x14
};

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
    NW4R_G3D_RESOURCE_FUNC_DEF(ResAnmShp);

    u32 GetRevision() const {
        return ref().revision;
    }

    bool CheckRevision() const {
        return GetRevision() == REVISION;
    }

    void GetAnmResult(ShpAnmResult* pResult, u32 id, f32 frame,
                      const ShpAnmVtxSet* pShapeArray) const;

    const ResAnmShpAnmData* GetShapeAnm(int i) const {
        return static_cast<ResAnmShpAnmData*>(
            ofs_to_obj<ResDic>(ref().toShpDataDic)[i]);
    }
    const ResAnmShpAnmData* GetShapeAnm(u32 i) const {
        return static_cast<ResAnmShpAnmData*>(
            ofs_to_obj<ResDic>(ref().toShpDataDic)[i]);
    }

    u32 GetShapeAnmNumEntries() const {
        return ofs_to_obj<ResDic>(ref().toShpDataDic).GetNumData();
    }

    const s32* GetVtxNameArray() const {
        return ofs_to_ptr<s32>(ref().toVtxNameArray);
    }

    int GetNumFrame() const {
        return ref().info.numFrame;
    }

    int GetNumVtxNames() const {
        return ref().info.numVtxName;
    }

    AnmPolicy GetAnmPolicy() const {
        return ref().info.policy;
    }
};

} // namespace g3d
} // namespace nw4r

#endif