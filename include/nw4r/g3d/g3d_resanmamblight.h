#ifndef NW4R_G3D_RESANMAMBLIGHT_H
#define NW4R_G3D_RESANMAMBLIGHT_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_resanm.h>
#include <nw4r/g3d/g3d_rescommon.h>

namespace nw4r {
namespace g3d {

struct ResAnmAmbLightData {
    u32 size;              // at 0x0
    s32 toResAnmScnData;   // at 0x4
    s32 name;              // at 0x8
    u32 id;                // at 0xC
    u32 refNumber;         // at 0x10
    u32 flags;             // at 0x14
    ResColorAnmData color; // at 0x18
};

class ResAnmAmbLight : public ResCommon<ResAnmAmbLightData> {
public:
    explicit ResAnmAmbLight(void* pData) : ResCommon(pData) {}

    u32 GetID() const {
        return ref().id;
    }
};

} // namespace g3d
} // namespace nw4r

#endif
