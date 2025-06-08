#ifndef EGG_CORE_DISPOSER_H
#define EGG_CORE_DISPOSER_H
#include <egg/types_egg.h>

#include <nw4r/ut.h>

namespace EGG {

// Forward declarations
class Heap;

class Disposer {
    friend class Heap;

public:
    Disposer();
    virtual ~Disposer(); // at 0x8

private:
    Heap* mContainHeap; // at 0x4

public:
    NW4R_UT_LIST_LINK_DECL(); // at 0x8
};

} // namespace EGG

#endif
