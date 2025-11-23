// TODO(kiwi) REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/util.h>

namespace EGG {

// Stripped from release
Exception* Exception::create(u16 width, u16 height, u16 attr, Heap* pHeap) {
#pragma unused(width)
#pragma unused(height)
#pragma unused(attr)
#pragma unused(pHeap)

    return NULL;
}

// Stripped from release
void Exception::setPadInfo(const u16* pPadInfo) {
#pragma unused(pPadInfo)
}

} // namespace EGG
