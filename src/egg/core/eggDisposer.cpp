// TODO(kiwi) REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>

namespace EGG {

Disposer::Disposer() {
    mContainHeap = Heap::findContainHeap(this);

    if (mContainHeap != NULL) {
        mContainHeap->appendDisposer(this);
    }
}

Disposer::~Disposer() {
    if (mContainHeap != NULL) {
        mContainHeap->removeDisposer(this);
    }
}

} // namespace EGG
