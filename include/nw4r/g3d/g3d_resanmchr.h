#ifndef NW4R_G3D_RESANMCHR_H
#define NW4R_G3D_RESANMCHR_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_resanm.h>
#include <nw4r/g3d/g3d_rescommon.h>
#include <nw4r/g3d/g3d_resmdl.h>

#include <nw4r/math.h>

namespace nw4r {
namespace g3d {

struct ChrAnmResult {
    u32 flags;       // at 0x0
    math::VEC3 s;    // at 0x4
    math::VEC3 rawR; // at 0x10
    math::MTX34 rt;  // at 0x1C

    // TODO: Give these better names
    enum Flag {
        FLAG_ANM_EXISTS = (1 << 0),
        FLAG_1 = (1 << 1),
        FLAG_2 = (1 << 2),
        FLAG_3 = (1 << 3),
        FLAG_4 = (1 << 4),
        FLAG_5 = (1 << 5),
        FLAG_6 = (1 << 6),
        FLAG_7 = (1 << 7),
        FLAG_8 = (1 << 8),
        FLAG_9 = (1 << 9),
        FLAG_10 = (1 << 10),
        FLAG_11 = (1 << 11),

        FLAG_31 = (1 << 31),
    };
};

struct ResAnmChrInfoData {
    u16 numFrame;            // at 0x0
    u16 numNode;             // at 0x2
    AnmPolicy policy;        // at 0x4
    ScalingRule scalingRule; // at 0x8
};

struct ResAnmChrData {
    ResBlockHeaderData header; // at 0x0
    u32 revision;              // at 0x8
    s32 toResFileData;         // at 0xC
    s32 toChrDataDic;          // at 0x10
    s32 name;                  // at 0x14
    s32 original_path;         // at 0x18
    ResAnmChrInfoData info;    // at 0x1C
};

class ResAnmChr : public ResCommon<ResAnmChrData> {
public:
    static const u32 SIGNATURE = 'CHR0';
    static const int REVISION = 4;

public:
    NW4R_G3D_RESOURCE_FUNC_DEF(ResAnmChr);

    u32 GetRevision() const {
        return ref().revision;
    }

    bool CheckRevision() const {
        return GetRevision() == REVISION;
    }
};

} // namespace g3d
} // namespace nw4r

#endif
