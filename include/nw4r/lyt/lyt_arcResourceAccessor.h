#ifndef NW4R_LYT_ARC_RESOURCE_ACCESSOR_H
#define NW4R_LYT_ARC_RESOURCE_ACCESSOR_H
#include "types_nw4r.h"
#include "ut_LinkList.h"
#include "ut_Font.h"
#include "lyt_resourceAccessor.h"
#include <RevoSDK/ARC/arc.h>
#include <string.h>

#define FONTNAMEBUF_MAX 127

namespace nw4r
{
    namespace lyt
    {
        class FontRefLink
        {
        public:
            FontRefLink();
            ~FontRefLink() {}

            void Set(const char *, ut::Font *);

            ut::Font * GetFont() const
            {
                return mFont;
            }

            const char * GetFontName() const
            {
                return mFontName;
            }

        private:
            ut::LinkListNode mNode; // at 0x0
            char mFontName[FONTNAMEBUF_MAX]; // at 0x8
            ut::Font *mFont; // at 0x88
        };

        class ArcResourceAccessor : public ResourceAccessor
        {
        public:
            ArcResourceAccessor();
            virtual ~ArcResourceAccessor() {} // at 0x8
            virtual UNKTYPE * GetResource(u32, const char *, u32 *); // at 0xC
            virtual ut::Font * GetFont(const char *); // at 0x10
            
            bool Attach(void *, const char *);
            void * Detach()
            {
                void *old = mArchive;
                mArchive = NULL;
                
                return old;
            }

            bool IsAttached() const { return (mArchive != NULL); }

            void RegistFont(FontRefLink *pLink)
            {
                mRefList.PushBack(pLink);
            }
            void UnregistFont(FontRefLink *pLink)
            {
                mRefList.Erase(pLink);
            }

        private:
            ARCHandle mHandle; // at 0x4
            void *mArchive; // at 0x8
            ut::LinkList<FontRefLink, 0> mRefList; // at 0x24
            char mRootDir[FONTNAMEBUF_MAX]; // at 0x30
        };

        namespace detail
        {
            static ut::Font * FindFont(ut::LinkList<FontRefLink, 0> *pList, const char *name)
            {
                ut::LinkList<FontRefLink, 0>::Iterator it = pList->GetBeginIter();
                for (; it != pList->GetEndIter(); it++)
                {
                    if (strcmp(name, it->GetFontName()) == 0) return it->GetFont();
                }

                return NULL;
            }
        }
    }
}

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
            if (entry.node_type != RX_ARCHIVE_FILE)
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
            ARCFile file;

            ARCFastOpen(pHandle, entrynum, &file);
            void *start = ARCGetStartAddrInMem(&file);

            if (pSize != NULL) *pSize = ARCGetLength(&file);

            ARCClose(&file);
            return start;
        }

        return NULL;
    }
}

#endif