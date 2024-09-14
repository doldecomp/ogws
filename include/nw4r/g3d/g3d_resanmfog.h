#ifndef NW4R_G3D_RESANMFOG_H
#define NW4R_G3D_RESANMFOG_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_resanm.h>
#include <nw4r/g3d/g3d_rescommon.h>

#include <revolution/GX.h>

namespace nw4r {
namespace g3d {

// Forward declarations
struct FogAnmResult;

struct ResAnmFogData {
    u32 size;              // at 0x0
    s32 toResAnmScnData;   // at 0x4
    s32 name;              // at 0x8
    u32 id;                // at 0xC
    u32 refNumber;         // at 0x10
    u32 flags;             // at 0x14
    GXFogType type;        // at 0x18
    ResAnmData startz;     // at 0x1C
    ResAnmData endz;       // at 0x20
    ResColorAnmData color; // at 0x24
};

class ResAnmFog : public ResCommon<ResAnmFogData> {
public:
    ResAnmFog(void* pData) : ResCommon(pData) {}

    void GetAnmResult(FogAnmResult* pResult, f32 frame) const;

    u32 GetID() const {
        return ref().id;
    }
};

} // namespace g3d
} // namespace nw4r

#endif
