#ifndef NW4R_UT_LOCKED_CACHE_H
#define NW4R_UT_LOCKED_CACHE_H
#include <nw4r/types_nw4r.h>

#include <revolution/OS.h>

namespace nw4r {
namespace ut {
namespace LC {

void Enable();
void Disable();

bool Lock();
void Unlock();

void LoadBlocks(void* pDst, void* pSrc, u32 blocks);
void StoreBlocks(void* pDst, void* pSrc, u32 blocks);
void StoreData(void* pDst, void* pSrc, u32 size);

inline void* GetBase() {
    return reinterpret_cast<void*>(OS_CACHE_BASE);
}

inline void QueueWait(u32 len) {
    LCQueueWait(len);
}

inline void QueueWaitEx(u32 len) {
    while (LCQueueLength() != len) {
        OSYieldThread();
    }
}

} // namespace LC
} // namespace ut
} // namespace nw4r

#endif
