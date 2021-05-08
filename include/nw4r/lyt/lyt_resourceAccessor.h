#ifndef NW4R_LYT_RESOURCEACCESSOR_H
#define NW4R_LYT_RESOURCEACCESSOR_H
#include "types_nw4r.h"
#include "ut_Font.h"

namespace nw4r
{
    namespace lyt
    {
        struct ResourceAccessor
        {
            ResourceAccessor();
            virtual ~ResourceAccessor();
            virtual void GetResource(u32, const char *, u32 *) = 0;
            virtual ut::Font * GetFont(const char *);
        };
    }
}

#endif