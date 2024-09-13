#ifndef NW4R_G3D_CPU_H
#define NW4R_G3D_CPU_H
#include <nw4r/types_nw4r.h>

#include <revolution/OS.h>

namespace nw4r {
namespace g3d {
namespace DC {

inline void StoreRange(void* pBase, u32 size) {
    DCStoreRange(pBase, size);
}

inline void StoreRangeNoSync(void* pBase, u32 size) {
    DCStoreRangeNoSync(pBase, size);
}

inline void FlushRangeNoSync(void* pBase, u32 size) {
    DCFlushRangeNoSync(pBase, size);
}

inline void InvalidateRange(void* pBase, u32 size) {
    DCInvalidateRange(pBase, size);
}

} // namespace DC

namespace detail {

void Copy32ByteBlocks(void*, const void*, u32);
void ZeroMemory32ByteBlocks(void*, u32);

} // namespace detail
} // namespace g3d
} // namespace nw4r

#endif