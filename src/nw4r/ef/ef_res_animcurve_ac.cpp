#include <nw4r/ef.h>

namespace nw4r {
namespace ef {

void ResAnimCurve::SetStop(bool stop) {
    AnimCurveHeader* pHeader = ptr();

    if (stop) {
        pHeader->processFlag |= AnimCurveHeader::PROC_FLAG_STOP;
    } else {
        pHeader->processFlag &= ~AnimCurveHeader::PROC_FLAG_STOP;
    }
}

} // namespace ef
} // namespace nw4r
