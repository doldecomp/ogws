#include <nw4r/ef.h>

namespace nw4r {
namespace ef {

ResAnimCurve ResEmitter::GetPtclTrack(u16 idx) {
    return ResAnimCurve(ptr()->GetPtclTrack(idx));
}

} // namespace ef
} // namespace nw4r
