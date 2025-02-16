#include <nw4r/lyt.h>

#include <revolution/OS.h>

namespace {

NW4R_LIB_VERSION(LYT, "Jun  8 2007", "11:17:26", "0x4199_60831");

} // namespace

namespace nw4r {
namespace lyt {

void LytInit() {
    OSRegisterVersion(NW4R_LYT_Version_);
    OSInitFastCast();
}

} // namespace lyt
} // namespace nw4r
