#pragma use_lmw_stmw on
#include "eggArchive.h"
#include "eggAssert.h"
#include "eggHeap.h"

namespace EGG
{
    using namespace nw4r;

    bool Archive::initHandle(void *arcBinary)
    {
        #line 61
        EGG_ASSERT(arcBinary != NULL);

        return ARCInitHandle(arcBinary, &this->mHandle);
    }

    Archive::~Archive()
    {
        removeList(this);
    }

    Archive * Archive::mount(void *arcBinary, Heap *pHeap, int align)
    {
        #line 147
        EGG_ASSERT(arcBinary != NULL);
        
        Archive *archive = NULL;
        if (sIsArchiveListInitialized)
        {
            Archive *node = NULL;

            while (node = (Archive *)ut::List_GetNext(&sArchiveList, node))
            {
                if (node->mHandle.header == (ARCHeader *)arcBinary)
                {
                    archive = node;
                    break;
                }
            }
        }

        if (!archive)
        {
            archive = new (pHeap, align) Archive();
            
            #line 159
            EGG_ASSERT(archive != NULL);

            bool success = archive->initHandle(arcBinary);
            if (success)
            {
                archive->INT_0x10 = 1;
            }
            else
            {
                archive->INT_0x10 = 0;
            }

            if (!success)
            {
                #line 166
                EGG_ASSERT(false);

                delete archive;
                archive = NULL;
            }
        }
        else
        {
            archive->INT_0x14++;
        }

        return archive;
    }

    void * Archive::getFile(const char *name, FileInfo *fileInfo)
    {
        void *startAddr = NULL;
        ARCFileInfo info;
        
        bool openResult = ARCOpen(&mHandle, name, &info);
        if (openResult)
        {
            if (INT_0x10 == 1)
            {
                startAddr = ARCGetStartAddrInMem(&info);
            }
            if (fileInfo)
            {
                fileInfo->mArcStartOffset = ARCGetStartOffset(&info);
                fileInfo->mArcLength = ARCGetLength(&info);
            }
        }

        ARCClose(&info);
        return startAddr;
    }

    ut::List Archive::sArchiveList;
    bool Archive::sIsArchiveListInitialized;
}

const char * eggArchive_asserts[] = {"not mount this archive", "openResult", "param", "/",
    "(totalArray - 1) >= *numFiles_p", "RestSizePathBuf >= NextDirNameLength", "file", "fileInfo"};
