#ifndef NW4R_EF_LINKED_OBJECT_H
#define NW4R_EF_LINKED_OBJECT_H
#include <nw4r/types_nw4r.h>

#include <nw4r/math.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace ef {

class LinkedObject {
public:
    ut::Link mMemoryLink; // at 0x0
    u32 mObjectID;        // at 0x8
};

} // namespace ef
} // namespace nw4r

#endif
