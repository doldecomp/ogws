#pragma use_lmw_stmw on
#include "eggDvdRipper.h"
#include "eggDvdFile.h"
#include "eggHeap.h"
#include "eggAssert.h"
#include "ut_algorithm.h"
#include <RevoSDK/VI/vi.h>
#include <RevoSDK/OS/OSCache.h>

namespace EGG
{
    void * DvdRipper::loadToMainRAM(const char *path, u8 *dest, Heap *heap,
        EAllocDirection allocDir, u32 pos, u32 *r8, u32 *pSize)
    {
        DvdFile d;
        return (!d.open(path)) ? NULL : loadToMainRAM(&d, dest, heap, allocDir, pos, r8, pSize);
    }

    #ifdef __DECOMP_NON_MATCHING
    void * DvdRipper::loadToMainRAM(DvdFile *dvdFile, u8 *dest, Heap *heap,
        EAllocDirection allocDir, u32 pos, u32 *r8, u32 *pSize)
    {
        u32 fileSize;
        bool allocSuccess = false; // Steals r29 from fileSize, should be in r30
        fileSize = dvdFile->getFileSize();
        if (pSize) *pSize = fileSize;
        u32 alignedSize = ut::RoundUp<u32>(fileSize, 32);

        if (!dest)
        {
            u32 dist = alignedSize - pos;
            u32 align = -32;
            if (allocDir == ALLOC_FORWARD) align = 32;

            dest = static_cast<u8 *>(Heap::alloc(dist, align, heap));
            allocSuccess = true;
        }

        if (!dest)
        {
            EGG_PRINT("heap allocation Failed: %d (heap %p)\n", alignedSize - pos, heap);
            return NULL;
        }

        s32 result;
        if (pos)
        {
            u8 buf[32];
            while (true)
            {
                result = DVDReadPrio(&dvdFile->mFileInfo, ut::RoundUp<void *>(buf, 32), 32, pos, 2);

                if (result >= 0) break;

                if ((result == -3) || (sErrorRetry == false))
                {
                    if (allocSuccess)
                    {
                        Heap::free(dest, NULL);
                    }
                    return NULL;
                }

                VIWaitForRetrace();
            }

            DCInvalidateRange(ut::RoundUp<void *>(buf, 32), 32);
        }

        while (true)
        {
            result = DVDReadPrio(&dvdFile->mFileInfo, dest, alignedSize - pos, pos, 2);

            if (result >= 0) break;

            if ((result == -3) || (sErrorRetry == false))
            {
                EGG_PRINT("readFailed : %d\n", result);

                if (allocSuccess)
                {
                    Heap::free(dest, NULL);
                }
                return NULL;
            }

            VIWaitForRetrace();
        }

        if (r8)
        {
            *r8 = alignedSize - pos;
        }

        return dest;
    }
    #else
    #error This file has yet to be decompiled accurately. Use "eggDvdRipper.s" instead.
    #endif

    UNKWORD DvdFile::getFileSize() const
    {
        return mFileInfo.mFileSize;
    }

    bool DvdRipper::sErrorRetry = true;
}

const char *eggDvdRipper_asserts = "read Header Failed\n";