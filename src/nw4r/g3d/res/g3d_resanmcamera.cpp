#include <nw4r/g3d.h>

namespace nw4r {
namespace g3d {

void ResAnmCamera::GetAnmResult(CameraAnmResult* pResult, f32 frame) const {
    const ResAnmCameraData& r = ref();
    u32 flags = r.flags;

    bool constantPosX = (flags & FLAG_POS_X_CONSTANT) != 0;
    bool constantPosY = (flags & FLAG_POS_Y_CONSTANT) != 0;
    bool constantPosZ = (flags & FLAG_POS_Z_CONSTANT) != 0;

    bool constantAspect = (flags & FLAG_ASPECT_CONSTANT) != 0;
    bool constantNear = (flags & FLAG_NEAR_CONSTANT) != 0;
    bool constantFar = (flags & FLAG_FAR_CONSTANT) != 0;

    CameraType type = static_cast<CameraType>(flags & FLAG_CAMERA_TYPE_MASK);

    pResult->flags = flags & FLAG_ANM_RESULT_MASK;
    pResult->projType = r.projType;

    pResult->pos.x = detail::GetResAnmResult(&r.posX, frame, constantPosX);
    pResult->pos.y = detail::GetResAnmResult(&r.posY, frame, constantPosY);
    pResult->pos.z = detail::GetResAnmResult(&r.posZ, frame, constantPosZ);

    pResult->aspect = detail::GetResAnmResult(&r.aspect, frame, constantAspect);
    pResult->near = detail::GetResAnmResult(&r.near, frame, constantNear);
    pResult->far = detail::GetResAnmResult(&r.far, frame, constantFar);

    switch (type) {
    case CAMERATYPE_ROTATE: {
        bool constantRotX = (flags & FLAG_ROT_X_CONSTANT) != 0;
        bool constantRotY = (flags & FLAG_ROT_Y_CONSTANT) != 0;
        bool constantRotZ = (flags & FLAG_ROT_Z_CONSTANT) != 0;

        pResult->rotate.rot.x =
            detail::GetResAnmResult(&r.rotX, frame, constantRotX);
        pResult->rotate.rot.y =
            detail::GetResAnmResult(&r.rotY, frame, constantRotY);
        pResult->rotate.rot.z =
            detail::GetResAnmResult(&r.rotZ, frame, constantRotZ);
        break;
    }

    case CAMERATYPE_AIM: {
        bool constantAimX = (flags & FLAG_AIM_X_CONSTANT) != 0;
        bool constantAimY = (flags & FLAG_AIM_Y_CONSTANT) != 0;
        bool constantAimZ = (flags & FLAG_AIM_Z_CONSTANT) != 0;
        bool constantTwist = (flags & FLAG_TWIST_CONSTANT) != 0;

        pResult->aim.aim.x =
            detail::GetResAnmResult(&r.aimX, frame, constantAimX);
        pResult->aim.aim.y =
            detail::GetResAnmResult(&r.aimY, frame, constantAimY);
        pResult->aim.aim.z =
            detail::GetResAnmResult(&r.aimZ, frame, constantAimZ);
        pResult->aim.twist =
            detail::GetResAnmResult(&r.twist, frame, constantTwist);
        break;
    }

    default: {
        break;
    }
    }

    switch (r.projType) {
    case GX_PERSPECTIVE: {
        bool constantFovy = (flags & FLAG_PERSP_FOVY_CONSTANT) != 0;

        pResult->perspFovy =
            detail::GetResAnmResult(&r.perspFovy, frame, constantFovy);
        break;
    }

    case GX_ORTHOGRAPHIC: {
        bool constantHeight = (flags & FLAG_ORTHO_HEIGHT_CONSTANT) != 0;

        pResult->orthoHeight =
            detail::GetResAnmResult(&r.orthoHeight, frame, constantHeight);
        break;
    }

    default: {
        break;
    }
    }
}

} // namespace g3d
} // namespace nw4r
