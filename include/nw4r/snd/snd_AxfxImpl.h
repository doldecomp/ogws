#ifndef NW4R_SND_AXFX_IMPL_H
#define NW4R_SND_AXFX_IMPL_H
#include <nw4r/types_nw4r.h>
#include <revolution/AXFX.h>
#include <revolution/MEM.h>

namespace nw4r {
namespace snd {
namespace detail {

struct AxfxImpl {
    bool mIsActive;      // at 0x0
    MEMiHeapHead* mHeap; // at 0x4
    u32 mAllocCount;     // at 0x8

    AxfxImpl() : mIsActive(false), mHeap(NULL), mAllocCount(0) {}

    u32 GetHeapTotalSize() {
        if (mHeap == NULL) {
            return 0;
        }

        return MEMGetHeapTotalSize(mHeap);
    }

    bool CreateHeap(void* buffer, u32 size);
    void DestroyHeap();
    void HookAlloc(AXFXAllocHook* allocHook, AXFXFreeHook* freeHook);
    void RestoreAlloc(AXFXAllocHook allocHook, AXFXFreeHook freeHook);

    static const u32 HEAP_SIZE_MIN = MEM_FRM_HEAP_MIN_SIZE + 32;

    static AxfxImpl* mCurrentFx;
    static u32 mAllocatedSize;

    static void* Alloc(u32 size);
    static void Free(void* block);
};

} // namespace detail
} // namespace snd
} // namespace nw4r

#endif
