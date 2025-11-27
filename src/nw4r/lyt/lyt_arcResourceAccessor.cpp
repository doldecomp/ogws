#include <nw4r/lyt.h>

#include <revolution/ARC.h>

#include <cstring>

/******************************************************************************
 *
 * Utility functions
 *
 ******************************************************************************/
namespace {

s32 FindNameResource(ARCHandle* pHandle, const char* pName) {
    s32 entrynum = -1;

    ARCDir dir;
    ARCOpenDir(pHandle, ".", &dir);

    ARCDirEntry ent;
    while (ARCReadDir(&dir, &ent)) {
        if (ent.isDir) {
            ARCChangeDir(pHandle, ent.name);
            entrynum = FindNameResource(pHandle, pName);
            ARCChangeDir(pHandle, "..");

            if (entrynum != -1) {
                break;
            }
        } else {
            if (std::stricmp(pName, ent.name) == 0) {
                entrynum = ent.entryNum;
                break;
            }
        }
    }

    ARCCloseDir(&dir);
    return entrynum;
}

void* GetResourceSub(ARCHandle* pHandle, const char* pRootDir, u32 type,
                     const char* pName, unsigned long* pSize) {

    s32 entrynum = -1;

    if (ARCConvertPathToEntrynum(pHandle, pRootDir) != -1) {
        if (ARCChangeDir(pHandle, pRootDir)) {
            if (type == 0) {
                entrynum = FindNameResource(pHandle, pName);
            } else {
                char resDir[4 + 1];
                resDir[0] = type >> 24;
                resDir[1] = type >> 16;
                resDir[2] = type >> 8;
                resDir[3] = type >> 0;
                resDir[4] = '\0';

                if (ARCConvertPathToEntrynum(pHandle, resDir) != -1 &&
                    ARCChangeDir(pHandle, resDir)) {

                    entrynum = ARCConvertPathToEntrynum(pHandle, pName);
                    ARCChangeDir(pHandle, "..");
                }
            }

            ARCChangeDir(pHandle, "..");
        }
    }

    if (entrynum != -1) {
        ARCFileInfo info;
        ARCFastOpen(pHandle, entrynum, &info);

        void* pResource = ARCGetStartAddrInMem(&info);

        if (pSize != NULL) {
            *pSize = ARCGetLength(&info);
        }

        ARCClose(&info);
        return pResource;
    }

    return NULL;
}

} // namespace

namespace nw4r {
namespace lyt {

/******************************************************************************
 *
 * Implementation details
 *
 ******************************************************************************/
namespace detail {

ut::Font* FindFont(FontRefLinkList* pFontList, const char* pName) {
    NW4R_UT_LINKLIST_FOREACH (it, *pFontList, {
        if (std::strcmp(pName, it->GetFontName()) == 0) {
            return it->GetFont();
        }
    })

    return NULL;
}

} // namespace detail

/******************************************************************************
 *
 * ArcResourceAccessor
 *
 ******************************************************************************/
ArcResourceAccessor::ArcResourceAccessor() : mArcBuf(NULL) {}

bool ArcResourceAccessor::Attach(void* pArchive, const char* pRootDir) {
    BOOL success = ARCInitHandle(pArchive, &mArcHandle);
    if (!success) {
        return false;
    }

    mArcBuf = pArchive;

    std::strncpy(mResRootDir, pRootDir, ROOTPATH_MAX - 1);
    mResRootDir[ROOTPATH_MAX - 1] = '\0';

    return true;
}

void* ArcResourceAccessor::GetResource(u32 type, const char* pName,
                                       u32* pSize) {

    return GetResourceSub(&mArcHandle, mResRootDir, type, pName, pSize);
}

ut::Font* ArcResourceAccessor::GetFont(const char* pName) {
    return detail::FindFont(&mFontList, pName);
}

} // namespace lyt
} // namespace nw4r
