#ifndef NW4R_G3D_RESANMLIGHT_H
#define NW4R_G3D_RESANMLIGHT_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_resanm.h>
#include <nw4r/g3d/g3d_rescommon.h>

namespace nw4r {
namespace g3d {

struct ResAnmLightDataTypedef {};

struct ResAnmLightData : ResAnmLightDataTypedef {
    u32 size;                    // at 0x0
    s32 toResAnmScnData;         // at 0x4
    s32 name;                    // at 0x8
    u32 id;                      // at 0xC
    u32 refNumber;               // at 0x10
    u32 specLightObjIdx;         // at 0x14
    s32 toResUserData;           // at 0x18
    u32 flags;                   // at 0x1C
    ResBoolAnmFramesData enable; // at 0x20
    ResAnmData posX;             // at 0x24
    ResAnmData posY;             // at 0x28
    ResAnmData posZ;             // at 0x2C
    ResColorAnmData color;       // at 0x30
    ResAnmData aimX;             // at 0x34
    ResAnmData aimY;             // at 0x38
    ResAnmData aimZ;             // at 0x3C
    GXDistAttnFn distFunc;       // at 0x40
    ResAnmData refDistance;      // at 0x44
    ResAnmData refBrightness;    // at 0x48
    GXSpotFn spotFunc;           // at 0x4C
    ResAnmData cutoff;           // at 0x50
    ResColorAnmData specColor;   // at 0x54
    ResAnmData shininess;        // at 0x58
};

class ResAnmLight : public ResCommon<ResAnmLightData>,
                    public ResAnmLightDataTypedef {
public:
    ResAnmLight(void* pData) : ResCommon(pData) {}

    u32 GetID() const {
        return ref().id;
    }
};

} // namespace g3d
} // namespace nw4r

#endif
