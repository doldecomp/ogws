// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>
#include <egg/prim.h>

#include <cstring>

namespace EGG {

nw4r::ut::List Archive::sArchiveList;
bool Archive::sIsArchiveListInitialized = false;

Archive::Archive() {
    mRefCount = 1;
    mMountType = MOUNT_TYPE_NONE;
    std::memset(&mHandle, 0, sizeof(ARCHandle));
    appendList(this);
}

Archive::~Archive() {
    removeList(this);
}

bool Archive::initHandle(void* arcBinary) {
#line 61
    EGG_ASSERT(arcBinary != NULL);

    return ARCInitHandle(arcBinary, &mHandle);
}

Archive* Archive::findArchive(void* pArcBinary) {
    Archive* pArchive = NULL;

    if (sIsArchiveListInitialized) {
        NW4R_UT_LIST_FOREACH(Archive, it, sArchiveList, {
            if (it->mHandle.archiveStartAddr == pArcBinary) {
                pArchive = it;
                break;
            }
        });
    }

    return pArchive;
}

void Archive::appendList(Archive* pArchive) {
    if (!sIsArchiveListInitialized) {
        nw4r::ut::List_Init(&sArchiveList, offsetof(Archive, mLink));
        sIsArchiveListInitialized = true;
    }

    nw4r::ut::List_Append(&sArchiveList, pArchive);
}

void Archive::removeList(Archive* pArchive) {
    nw4r::ut::List_Remove(&sArchiveList, pArchive);
}

Archive* Archive::mount(void* arcBinary, Heap* pHeap, int align) {
#line 147
    EGG_ASSERT(arcBinary != NULL);

    Archive* archive = findArchive(arcBinary);

    if (archive == NULL) {
        archive = new (pHeap, align) Archive();

#line 159
        EGG_ASSERT(archive != NULL);

        bool success = archive->initHandle(arcBinary);

        if (success) {
            archive->mMountType = MOUNT_TYPE_MEMORY;
        } else {
            archive->mMountType = MOUNT_TYPE_NONE;
        }

        if (!success) {
#line 166
            EGG_ASSERT(false);

            delete archive;
            archive = NULL;
        }

    } else {
        archive->mRefCount++;
    }

    return archive;
}

void* Archive::getFile(const char* pPath, FileInfo* pInfo) {
    void* pStartAddr = NULL;

    ARCFileInfo info;
    bool success = ARCOpen(&mHandle, pPath, &info);

    if (success) {
        if (mMountType == MOUNT_TYPE_MEMORY) {
            pStartAddr = ARCGetStartAddrInMem(&info);
        }

        if (pInfo != NULL) {
            pInfo->mStartOffset = ARCGetStartOffset(&info);
            pInfo->mLength = ARCGetLength(&info);
        }
    }

    ARCClose(&info);
    return pStartAddr;
}

DECOMP_FORCEACTIVE(eggArchive_cpp,
                  "not mount this archive",
                  "openResult",
                  "param",
                  "/",
                  "(totalArray - 1) >= *numFiles_p",
                  "RestSizePathBuf >= NextDirNameLength",
                  "file",
                  "fileInfo");

} // namespace EGG
