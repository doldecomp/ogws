#include <nw4r/g3d.h>

namespace nw4r {
namespace g3d {

bool ResAnmVis::GetAnmResult(u32 id, f32 frame) const {
    const ResAnmVisAnmData* pAnmData = GetNodeAnm(id);
    const ResAnmVisInfoData& rInfoData = ref().info;

    if (pAnmData->flags & ResAnmVisAnmData::FLAG_ANM_IS_CONSTANT) {
        return pAnmData->flags & ResAnmVisAnmData::FLAG_ANM_CONSTANT_VALUE;
    }

    f32 fClippedFrame = detail::ClipFrame(rInfoData, frame);
    int iClippedFrame = static_cast<int>(math::FFloor(fClippedFrame));

    return detail::GetResBoolAnmFramesResult(&pAnmData->visibility,
                                             iClippedFrame);
}

} // namespace g3d
} // namespace nw4r
