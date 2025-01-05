#include <nw4r/g3d.h>

namespace nw4r {
namespace g3d {

void ResAnmLight::GetAnmResult(LightAnmResult* pResult, f32 frame) const {
    const ResAnmLightData& r = ref();
    u32 flags = r.flags;

    const ResAnmScnInfoData& rInfoData =
        ofs_to_ptr<ResAnmScnData>(r.toResAnmScnData)->info;

    f32 clippedFrame = detail::ClipFrame(rInfoData, frame);

    pResult->flags = flags & FLAG_ANM_RESULT_MASK;

    bool enableConstant = (flags & FLAG_ENABLE_CONSTANT) != 0;
    if (!enableConstant) {
        int iClippedFrame = static_cast<int>(math::FFloor(clippedFrame));

        bool enable = detail::GetResBoolAnmResult(&r.enable, iClippedFrame);
        if (enable) {
            pResult->flags |= FLAG_ENABLE;
        }
    }

    if (pResult->flags & FLAG_ENABLE) {
        LightType type = static_cast<LightType>(flags & FLAG_LIGHT_TYPE_MASK);

        bool hasSpecular = (flags & FLAG_SPECULAR) != 0;
        bool hasAim = type != LIGHTTYPE_POINT || hasSpecular;

        bool constantPosX = (flags & FLAG_POS_X_CONSTANT) != 0;
        bool constantPosY = (flags & FLAG_POS_Y_CONSTANT) != 0;
        bool constantPosZ = (flags & FLAG_POS_Z_CONSTANT) != 0;
        bool constantColor = (flags & FLAG_COLOR_CONSTANT) != 0;

        pResult->pos.x = detail::GetResAnmResult(&r.posX, frame, constantPosX);
        pResult->pos.y = detail::GetResAnmResult(&r.posY, frame, constantPosY);
        pResult->pos.z = detail::GetResAnmResult(&r.posZ, frame, constantPosZ);
        pResult->color =
            detail::GetResColorAnmResult(&r.color, clippedFrame, constantColor);

        if (hasAim) {
            bool constantAimX = (flags & FLAG_AIM_X_CONSTANT) != 0;
            bool constantAimY = (flags & FLAG_AIM_Y_CONSTANT) != 0;
            bool constantAimZ = (flags & FLAG_AIM_Z_CONSTANT) != 0;

            pResult->aim.x =
                detail::GetResAnmResult(&r.aimX, frame, constantAimX);
            pResult->aim.y =
                detail::GetResAnmResult(&r.aimY, frame, constantAimY);
            pResult->aim.z =
                detail::GetResAnmResult(&r.aimZ, frame, constantAimZ);
        }

        switch (type) {
        case LIGHTTYPE_POINT: {
            bool refDistanceConstant =
                (flags & FLAG_REF_DISTANCE_CONSTANT) != 0;
            bool refBrightnessConstant =
                (flags & FLAG_REF_BRIGHTNESS_CONSTANT) != 0;

            pResult->distFunc = r.distFunc;

            pResult->refDistance = detail::GetResAnmResult(
                &r.refDistance, frame, refDistanceConstant);

            pResult->refBrightness = detail::GetResAnmResult(
                &r.refBrightness, frame, refBrightnessConstant);
            break;
        }

        case LIGHTTYPE_DIRECTIONAL: {
            break;
        }

        case LIGHTTYPE_SPOT: {
            bool cutoffConstant = (flags & FLAG_CUTOFF_CONSTANT) != 0;
            bool refDistanceConstant =
                (flags & FLAG_REF_DISTANCE_CONSTANT) != 0;
            bool refBrightnessConstant =
                (flags & FLAG_REF_BRIGHTNESS_CONSTANT) != 0;

            pResult->distFunc = r.distFunc;
            pResult->spotFunc = r.spotFunc;

            pResult->cutoff =
                detail::GetResAnmResult(&r.cutoff, frame, cutoffConstant);

            pResult->refDistance = detail::GetResAnmResult(
                &r.refDistance, frame, refDistanceConstant);

            pResult->refBrightness = detail::GetResAnmResult(
                &r.refBrightness, frame, refBrightnessConstant);
            break;
        }
        }

        if (hasSpecular) {
            bool specColorConstant = (flags & FLAG_SPEC_COLOR_CONSTANT) != 0;
            bool shininessConstant = (flags & FLAG_SHININESS_CONSTANT) != 0;

            pResult->specColor = detail::GetResColorAnmResult(
                &r.specColor, clippedFrame, specColorConstant);

            pResult->shininess =
                detail::GetResAnmResult(&r.shininess, frame, shininessConstant);

            pResult->specIdx = r.specLightObjIdx;
        }
    }
}

} // namespace g3d
} // namespace nw4r
