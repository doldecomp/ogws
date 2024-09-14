#ifndef NW4R_G3D_RESANMCAMERA_H
#define NW4R_G3D_RESANMCAMERA_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_anmcamera.h>
#include <nw4r/g3d/g3d_resanm.h>
#include <nw4r/g3d/g3d_rescommon.h>

namespace nw4r {
namespace g3d {

struct ResAnmCameraDataTypedef {};

struct ResAnmCameraData : ResAnmCameraDataTypedef {
    u32 size;                  // at 0x0
    s32 toResAnmScnData;       // at 0x4
    s32 name;                  // at 0x8
    u32 id;                    // at 0xC
    u32 refNumber;             // at 0x10
    GXProjectionType projType; // at 0x14
    u32 flags;                 // at 0x18
    s32 toResUserData;         // at 0x1C
    ResAnmData posX;           // at 0x20
    ResAnmData posY;           // at 0x24
    ResAnmData posZ;           // at 0x28
    ResAnmData aspect;         // at 0x2C
    ResAnmData near;           // at 0x30
    ResAnmData far;            // at 0x34
    ResAnmData rotX;           // at 0x38
    ResAnmData rotY;           // at 0x3C
    ResAnmData rotZ;           // at 0x40
    ResAnmData aimX;           // at 0x44
    ResAnmData aimY;           // at 0x48
    ResAnmData aimZ;           // at 0x4C
    ResAnmData twist;          // at 0x50
    ResAnmData perspFovy;      // at 0x54
    ResAnmData orthoHeight;    // at 0x58
};

class ResAnmCamera : public ResCommon<ResAnmCameraData>,
                     public ResAnmCameraDataTypedef {
public:
    ResAnmCamera(void* pData) : ResCommon(pData) {}

    void GetAnmResult(CameraAnmResult* pResult, f32 frame) const;
};

} // namespace g3d
} // namespace nw4r

#endif
