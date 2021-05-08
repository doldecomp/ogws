#pragma use_lmw_stmw on
#include "eggArchive.h"
#include "eggAssert.h"
#include "eggHeap.h"

namespace EGG
{
    using namespace nw4r;

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
                if (node->mHandle.mHeader == (ARCHeader *)arcBinary)
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
            
            #line 61
            EGG_ASSERT(arcBinary != NULL);

            bool success = ARCInitHandle(arcBinary, &archive->mHandle);
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
        ARCFile file;
        
        bool openResult = ARCOpen(&mHandle, name, &file);
        if (openResult)
        {
            if (INT_0x10 == 1)
            {
                startAddr = ARCGetStartAddrInMem(&file);
            }
            if (fileInfo)
            {
                fileInfo->mArcStartOffset = ARCGetStartOffset(&file);
                fileInfo->mArcLength = ARCGetLength(&file);
            }
        }

        ARCClose(&file);
        return startAddr;
    }

    ut::List Archive::sArchiveList;
    bool Archive::sIsArchiveListInitialized;
}

const char * eggArchive_asserts[] = {"not mount this archive", "openResult", "param", "/",
    "(totalArray - 1) >= *numFiles_p", "RestSizePathBuf >= NextDirNameLength", "file", "fileInfo"};
