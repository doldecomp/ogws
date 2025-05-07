#ifndef EGG_CORE_DISPOSER_H
#define EGG_CORE_DISPOSER_H
#include <egg/types_egg.h>

#include <nw4r/ut.h>

namespace EGG {

class Disposer {
    friend class Heap;

public:
    Disposer();
    virtual ~Disposer(); // at 0x8

private:
    Heap* mContainHeap;   // at 0x4
    nw4r::ut::Link mLink; // at 0x8
};

} // namespace EGG

#endif
