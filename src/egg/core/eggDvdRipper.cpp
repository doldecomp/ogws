// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>
#include <egg/prim.h>

#include <revolution/OS.h>
#include <revolution/VI.h>

namespace EGG {

bool DvdRipper::sErrorRetry = true;

u8* DvdRipper::loadToMainRAM(const char* pPath, u8* pBuffer, Heap* pHeap,
                             EAllocDirection allocDir, u32 offset, u32* pRead,
                             u32* pSize) {

    DvdFile file;

    if (!file.open(pPath)) {
        return NULL;
    }

    return loadToMainRAM(&file, pBuffer, pHeap, allocDir, offset, pRead, pSize);
}

u8* DvdRipper::loadToMainRAM(DvdFile* pFile, u8* pBuffer, Heap* pHeap,
                             EAllocDirection allocDir, u32 offset, u32* pRead,
                             u32* pSize) {

    bool allocedBuffer = false;
    u32 fileSize = pFile->getFileSize();

    if (pSize != NULL) {
        *pSize = fileSize;
    }

    fileSize = ROUND_UP(fileSize, 32);

    if (pBuffer == NULL) {
        pBuffer = static_cast<u8*>(Heap::alloc(
            fileSize - offset, allocDir == ALLOC_DIR_HEAD ? 32 : -32, pHeap));

        allocedBuffer = true;
    }

    if (pBuffer == NULL) {
        EGG_PRINT("heap allocation Failed: %d (heap %p)\n", fileSize - offset,
                  pHeap);

        return NULL;
    }

    if (offset > 0) {
        u8 chunk[32 + 31];
        void* const pChunk = ROUND_UP_PTR(chunk, 32);

        while (true) {
            s32 readFailed = DVDReadPrio(pFile->getFileInfo(), pChunk, 32,
                                         offset, DVD_PRIO_MEDIUM);

            if (readFailed >= 0) {
                break;
            }

            if (readFailed == DVD_RESULT_CANCELED || !sErrorRetry) {
                if (allocedBuffer) {
                    Heap::free(pBuffer, NULL);
                }

                return NULL;
            }

            VIWaitForRetrace();
        }

        DCInvalidateRange(pChunk, 32);
    }

    while (true) {
        s32 readFailed =
            DVDReadPrio(pFile->getFileInfo(), pBuffer, fileSize - offset,
                        offset, DVD_PRIO_MEDIUM);

        if (readFailed >= 0) {
            break;
        }

        if (readFailed == DVD_RESULT_CANCELED || !sErrorRetry) {
            EGG_PRINT("readFailed : %d\n", readFailed);

            if (allocedBuffer) {
                Heap::free(pBuffer, NULL);
            }

            return NULL;
        }

        VIWaitForRetrace();
    }

    if (pRead != NULL) {
        *pRead = fileSize - offset;
    }

    return pBuffer;
}

DECOMP_FORCEACTIVE(eggDvdRipper_cpp,
                  "read Header Failed\n");

} // namespace EGG
