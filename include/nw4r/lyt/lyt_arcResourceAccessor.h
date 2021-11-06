#ifndef NW4R_LYT_ARCRESOURCEACCESSOR_H
#define NW4R_LYT_ARCRESOURCEACCESSOR_H
#include "types_nw4r.h"
#include "ut_LinkList.h"
#include "ut_Font.h"
#include "lyt_resourceAccessor.h"
#include <RevoSDK/ARC/arc.h>
#include <string.h>

#define FONTNAMEBUF_MAX 127

namespace
{
    UNKWORD FindNameResource(ARCHandle *, const char *);
    UNKTYPE GetResourceSub(ARCHandle *, const char *, u32, const char *, u32 *);
}

namespace nw4r
{
    namespace lyt
    {
        struct FontRefLink
        {
            inline FontRefLink() : mNode(), mFont(NULL) {}

            inline ut::Font * GetFont() const
            {
                return mFont;
            }

            inline const char * GetFontName() const
            {
                return mFontName;
            }

            ut::LinkListNode mNode; // at 0x0
            char mFontName[FONTNAMEBUF_MAX]; // at 0x8
            ut::Font *mFont; // at 0x88
        };

        struct ArcResourceAccessor : ResourceAccessor
        {
            ArcResourceAccessor();
            virtual ~ArcResourceAccessor(); // at 0x8
            virtual UNKTYPE GetResource(u32, const char *, u32 *); // at 0x10
            virtual ut::Font * GetFont(const char *); // at 0x14
            bool Attach(void *, const char *);
            
            ARCHandle mHandle; // at 0x4
            void *PTR_0x20;
            ut::LinkList<FontRefLink, 0> mRefList; // at 0x24
            char mName[FONTNAMEBUF_MAX]; // at 0x30
        };

        namespace detail
        {
            ut::Font * FindFont(ut::LinkList<FontRefLink, 0> *, const char *);
        }
    }
}

#endif