#include <nw4r/g3d.h>

namespace nw4r {
namespace g3d {

void ResAnmAmbLight::GetAnmResult(AmbLightAnmResult* pResult, f32 frame) const {
    const ResAnmAmbLightData& r = ref();

    u32 flags = r.flags;
    bool constant = (flags & ResAnmAmbLightData::FLAG_CONSTANT) != 0;

    const ResAnmScnInfoData& rInfoData =
        ofs_to_ptr<ResAnmScnData>(r.toResAnmScnData)->info;

    f32 clippedFrame = detail::ClipFrame(rInfoData, frame);

    pResult->flags = flags & ResAnmAmbLightData::FLAG_ANM_RESULT_MASK;
    pResult->color =
        detail::GetResColorAnmResult(&r.color, clippedFrame, constant);
}

} // namespace g3d
} // namespace nw4r
