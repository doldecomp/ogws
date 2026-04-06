#ifndef EGG_CORE_DVD_RIPPER_H
#define EGG_CORE_DVD_RIPPER_H
#include <egg/types_egg.h>

namespace EGG {

class DvdRipper {
public:
    enum EAllocDirection { ALLOC_DIR_TAIL, ALLOC_DIR_HEAD };

public:
    static u8* loadToMainRAM(const char* pPath, u8* pBuffer, Heap* pHeap,
                             EAllocDirection allocDir, u32 offset = 0,
                             u32* pRead = NULL, u32* pSize = NULL);

    static u8* loadToMainRAM(DvdFile* pFile, u8* pBuffer, Heap* pHeap,
                             EAllocDirection allocDir, u32 offset = 0,
                             u32* pRead = NULL, u32* pSize = NULL);

private:
    static bool sErrorRetry;
};

} // namespace EGG

#endif
