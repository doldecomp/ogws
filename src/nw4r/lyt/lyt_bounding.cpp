#include <nw4r/lyt.h>

namespace nw4r {
namespace lyt {

NW4R_UT_RTTI_DEF_DERIVED(Bounding, Pane);

Bounding::Bounding(const res::Bounding* pRes, const ResBlockSet& rBlockSet)
    : Pane(pRes) {

#pragma unused(rBlockSet)
}

Bounding::~Bounding() {}

void Bounding::DrawSelf(const DrawInfo& rInfo) {
#pragma unused(rInfo)
    // Debug draw stripped out
}

} // namespace lyt
} // namespace nw4r
