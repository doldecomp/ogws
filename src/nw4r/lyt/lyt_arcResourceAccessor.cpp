#pragma ipa file
#include "lyt_arcResourceAccessor.h"
#include <string.h>
#include <RevoSDK/ARC/arc.h>

namespace nw4r
{
    namespace lyt
    {
        FontRefLink::FontRefLink() : mFont(NULL) {}

        void FontRefLink::Set(const char *name, ut::Font *font)
        {
            strcpy(mFontName, name);
            mFont = font;
        }

        ArcResourceAccessor::ArcResourceAccessor() : mArchive(NULL)
        {

        }

        bool ArcResourceAccessor::Attach(void *archive, const char *rootDir)
        {
            if (!ARCInitHandle(archive, &mHandle)) return false;

            mArchive = archive;
            strncpy(mRootDir, rootDir, FONTNAMEBUF_MAX);
            mRootDir[FONTNAMEBUF_MAX] = '\0';

            return true;
        }

        UNKTYPE * ArcResourceAccessor::GetResource(u32 r4, const char *r5, u32 *r6)
        {
            return GetResourceSub(&mHandle, mRootDir, r4, r5, r6);
        }

        ut::Font * ArcResourceAccessor::GetFont(const char *name)
        {
            return detail::FindFont(&mRefList, name);
        }
    }
}