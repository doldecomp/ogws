#ifndef NW4R_G3D_RESANMCAMERA_H
#define NW4R_G3D_RESANMCAMERA_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_resanm.h>
#include <nw4r/g3d/g3d_rescommon.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

namespace nw4r {
namespace g3d {

struct ResAnmCameraDataTypedef {
    enum CameraType {
        CAMERATYPE_ROTATE,
        CAMERATYPE_AIM,

        CAMERATYPE_MAX
    };

    enum Flag {
        FLAG_CAMERA_TYPE_MASK = (1 << 0),
        // TODO: Naming
        FLAG_1 = (1 << 1),

        FLAG_POS_X_CONSTANT = (1 << 17),
        FLAG_POS_Y_CONSTANT = (1 << 18),
        FLAG_POS_Z_CONSTANT = (1 << 19),

        FLAG_ASPECT_CONSTANT = (1 << 20),
        FLAG_NEAR_CONSTANT = (1 << 21),
        FLAG_FAR_CONSTANT = (1 << 22),

        FLAG_PERSP_FOVY_CONSTANT = (1 << 23),
        FLAG_ORTHO_HEIGHT_CONSTANT = (1 << 24),

        FLAG_AIM_X_CONSTANT = (1 << 25),
        FLAG_AIM_Y_CONSTANT = (1 << 26),
        FLAG_AIM_Z_CONSTANT = (1 << 27),
        FLAG_TWIST_CONSTANT = (1 << 28),

        FLAG_ROT_X_CONSTANT = (1 << 29),
        FLAG_ROT_Y_CONSTANT = (1 << 30),
        FLAG_ROT_Z_CONSTANT = (1 << 31),

        // Flags accessible from CameraAnmResult
        FLAG_ANM_RESULT_MASK = FLAG_CAMERA_TYPE_MASK | FLAG_1
    };
};

struct CameraAnmResult : ResAnmCameraDataTypedef {
    u32 flags;                 // at 0x0
    GXProjectionType projType; // at 0x4
    math::VEC3 pos;            // at 0x8
    f32 aspect;                // at 0x14
    f32 near;                  // at 0x18
    f32 far;                   // at 0x1C

    union {
        struct {
            math::_VEC3 rot; // at 0x20
        } rotate;

        struct {
            math::_VEC3 aim; // at 0x20
            f32 twist;       // at 0x2C
        } aim;
    };

    union {
        f32 perspFovy;   // at 0x30
        f32 orthoHeight; // at 0x30
    };
};

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
    NW4R_G3D_RESOURCE_FUNC_DEF(ResAnmCamera);

    void GetAnmResult(CameraAnmResult* pResult, f32 frame) const;

    u32 GetID() const {
        return ref().id;
    }
};

} // namespace g3d
} // namespace nw4r

#endif
