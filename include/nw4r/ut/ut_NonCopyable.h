#ifndef NW4R_UT_NON_COPYABLE_H
#define NW4R_UT_NON_COPYABLE_H
#include "types_nw4r.h"

namespace nw4r
{
    namespace ut
    {
        class NonCopyable
        {
        public:
            NonCopyable() {}
            ~NonCopyable() {}
        };
    }
}

#endif