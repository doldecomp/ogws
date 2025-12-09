#include <egg/gfxe.h>

namespace EGG {

DrawPathBase::DrawPathBase() {}

void DrawPathBase::calc() {
    if (isEnable()) {
        copyFromAnother(IDrawGX::getScreen());
        internalCalc();
    }
}

void DrawPathBase::scnProcDraw(u16 step) {
    if (isEnable()) {
        internalDraw(step);
    }
}

} // namespace EGG
