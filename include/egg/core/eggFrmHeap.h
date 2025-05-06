#ifndef EGG_CORE_FRM_HEAP_H
#define EGG_CORE_FRM_HEAP_H
#include <egg/types_egg.h>

#include <egg/core/eggDisposer.h>
#include <egg/core/eggHeap.h>

namespace EGG {

class FrmHeap : public Heap {
public:
    static FrmHeap* create(void* pHeapStart, u32 size, u16 opt)
        DECOMP_DONT_INLINE;
    static FrmHeap* create(u32 size, Heap* pParentHeap, u16 opt);

    FrmHeap(MEMiHeapHead* pHeapHandle);
    virtual ~FrmHeap(); // at 0x8

    virtual EHeapKind getHeapKind() const {
        return HEAP_KIND_FRAME;
    } // at 0xC

    virtual void initAllocator(Allocator* pAllocator,
                               s32 align = 4); // at 0x10

    virtual void* alloc(u32 size, s32 align = 4); // at 0x14
    virtual void free(void* pBlock);              // at 0x18
    virtual void destroy();                       // at 0x1C

    virtual u32 resizeForMBlock(void* pBlock, u32 size); // at 0x20
    virtual u32 getAllocatableSize(s32 align = 4);       // at 0x24
    virtual u32 adjust();                                // at 0x28
};

} // namespace EGG

#endif
