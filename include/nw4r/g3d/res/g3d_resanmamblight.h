#ifndef NW4R_G3D_RES_RES_ANM_AMB_LIGHT_H
#define NW4R_G3D_RES_RES_ANM_AMB_LIGHT_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/res/g3d_resanm.h>
#include <nw4r/g3d/res/g3d_rescommon.h>

namespace nw4r {
namespace g3d {

struct AmbLightAnmResult {
    u32 flags; // at 0x0
    u32 color; // at 0x4
};

struct ResAnmAmbLightData {
    u32 size;              // at 0x0
    s32 toResAnmScnData;   // at 0x4
    s32 name;              // at 0x8
    u32 id;                // at 0xC
    u32 refNumber;         // at 0x10
    u32 flags;             // at 0x14
    ResColorAnmData color; // at 0x18

    enum Flag {
        // TODO: Naming
        FLAG_0 = (1 << 0),
        FLAG_1 = (1 << 1),

        FLAG_CONSTANT = (1 << 31),

        // Flags accessible from AmbLightAnmResult
        FLAG_ANM_RESULT_MASK = FLAG_0 | FLAG_1
    };
};

class ResAnmAmbLight : public ResCommon<ResAnmAmbLightData> {
public:
    NW4R_G3D_RESOURCE_FUNC_DEF(ResAnmAmbLight);

    void GetAnmResult(AmbLightAnmResult* pResult, f32 frame) const;

    u32 GetID() const {
        return ref().id;
    }

    u32 GetRefNumber() const {
        return ref().refNumber;
    }
};

} // namespace g3d
} // namespace nw4r

#endif
