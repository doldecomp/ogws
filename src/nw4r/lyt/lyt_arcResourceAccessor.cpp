#pragma ipa file
#include "lyt_arcResourceAccessor.h"
#include <string.h>
#include <revolution/ARC/arc.h>

namespace
{
    UNKWORD FindNameResource(ARCHandle *pHandle, const char *name)
    {
        UNKWORD resource = -1;
        ARCDir dir;
        ARCEntry entry;
        
        ARCOpenDir(pHandle, ".", &dir);
        while (ARCReadDir(&dir, &entry))
        {
            if (entry.type != ARC_ENTRY_FILE)
            {
                ARCChangeDir(pHandle, entry.name);
                resource = FindNameResource(pHandle, name);
                ARCChangeDir(pHandle, "..");
                if (resource != -1) break;
            }
            else
            {
                if (stricmp(name, entry.name) == 0)
                {
                    resource = entry.path;
                    break;
                }
            }
        }

        ARCCloseDir(&dir);
        return resource;
    }

    UNKTYPE * GetResourceSub(ARCHandle *pHandle, const char *rootDir, u32 filetype, const char *filename, u32 *pSize)
    {
        s32 entrynum = -1;

        if (ARCConvertPathToEntrynum(pHandle, rootDir) != -1 && ARCChangeDir(pHandle, rootDir))
        {
            // Usually 'timg', RP checks for 'font'
            if (filetype == 0)
            {
                entrynum = FindNameResource(pHandle, filename);
            }
            else
            {
                char path[5];
                path[0] = filetype >> 24;
                path[1] = filetype >> 16;
                path[2] = filetype >> 8;
                path[3] = filetype >> 0;
                path[4] = '\0';

                if (ARCConvertPathToEntrynum(pHandle, path) != -1)
                {
                    if (ARCChangeDir(pHandle, path))
                    {
                        entrynum = ARCConvertPathToEntrynum(pHandle, filename);
                        ARCChangeDir(pHandle, "..");
                    }
                }
            }

            ARCChangeDir(pHandle, "..");
        }

        if (entrynum != -1)
        {
            ARCFileInfo info;

            ARCFastOpen(pHandle, entrynum, &info);
            void *start = ARCGetStartAddrInMem(&info);

            if (pSize != NULL) *pSize = ARCGetLength(&info);

            ARCClose(&info);
            return start;
        }

        return NULL;
    }
}

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

        UNKTYPE * ArcResourceAccessor::GetResource(u32 filetype, const char *filename, u32 *pSize)
        {
            return GetResourceSub(&mHandle, mRootDir, filetype, filename, pSize);
        }

        ut::Font * ArcResourceAccessor::GetFont(const char *name)
        {
            return detail::FindFont(&mRefList, name);
        }
    }
}