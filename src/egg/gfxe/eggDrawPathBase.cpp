#include <egg/gfxe.h>

namespace EGG {

DrawPathBase::DrawPathBase() {}

void DrawPathBase::calc() {
    if (isVisible()) {
        copyFromAnother(IDrawGX::getScreen());
        internalCalc();
    }
}

void DrawPathBase::scnProcDraw(u16 step) {
    if (isVisible()) {
        internalDraw(step);
    }
}

} // namespace EGG
