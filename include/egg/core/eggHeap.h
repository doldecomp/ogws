#ifndef EGG_CORE_HEAP_H
#define EGG_CORE_HEAP_H
#include <egg/types_egg.h>

#include <egg/core/eggBitFlag.h>
#include <egg/core/eggDisposer.h>

#include <nw4r/ut.h>

#include <revolution/MEM.h>
#include <revolution/OS.h>

namespace EGG {

// Forward declarations
class Allocator;
class ExpHeap;

class Heap : public Disposer {
public:
    enum EHeapKind {
        HEAP_KIND_NONE,
        HEAP_KIND_EXPAND,
        HEAP_KIND_FRAME,
        HEAP_KIND_UNIT,
        HEAP_KIND_ASSERT
    };

public:
    static void initialize();

    static void* alloc(u32 size, int align, Heap* pHeap);
    static void free(void* pBlock, Heap* pHeap);

    explicit Heap(MEMiHeapHead* pHeapHandle);
    virtual ~Heap(); // at 0x8

    virtual EHeapKind getHeapKind() const = 0; // at 0xC

    virtual void initAllocator(Allocator* pAllocator,
                               s32 align = 4) = 0; // at 0x10

    virtual void* alloc(u32 size, s32 align = 4) = 0; // at 0x14
    virtual void free(void* pBlock) = 0;              // at 0x18
    virtual void destroy() = 0;                       // at 0x1C

    virtual u32 resizeForMBlock(void* pBlock, u32 size) = 0; // at 0x20
    virtual u32 getAllocatableSize(s32 align = 4) = 0;       // at 0x24
    virtual u32 adjust() = 0;                                // at 0x28

    static Heap* findHeap(MEMiHeapHead* pHeapHandle);
    Heap* findParentHeap();
    static Heap* findContainHeap(const void* pBlock);

    void dispose();
    Heap* becomeCurrentHeap();

    void* getStartAddress() {
        return this;
    }
    void* getEndAddress() {
        return MEMGetHeapEndAddress(mHeapHandle);
    }
    s32 getTotalSize() {
        return static_cast<u8*>(getEndAddress()) -
               static_cast<u8*>(getStartAddress());
    }

    bool isHeapPointer(void* pBlock) {
        return pBlock >= getStartAddress() && pBlock < getEndAddress();
    }

    void disableAllocation() {
        mFlags.setBit(BIT_DISABLE_ALLOC);
    }
    void enableAllocation() {
        mFlags.resetBit(BIT_DISABLE_ALLOC);
    }
    bool tstDisableAllocation() {
        return mFlags.onBit(BIT_DISABLE_ALLOC);
    }

    void appendDisposer(Disposer* pDisposer) {
        nw4r::ut::List_Append(&mDisposerList, pDisposer);
    }
    void removeDisposer(Disposer* pDisposer) {
        nw4r::ut::List_Remove(&mDisposerList, pDisposer);
    }

    static const nw4r::ut::List& getHeapList() {
        return sHeapList;
    }
    static Heap* getCurrentHeap() {
        return sCurrentHeap;
    }

    static ExpHeap* dynamicCastToExp(Heap* pHeap) {
        if (pHeap->getHeapKind() == HEAP_KIND_EXPAND) {
            return reinterpret_cast<ExpHeap*>(pHeap);
        }

        return NULL;
    }

    static void disableAllocationAllBut(Heap* pHeap) {
        sAllocatableHeap = pHeap;
    }

protected:
    static void* addOffset(void* pBase, u32 offset) {
        return static_cast<u8*>(pBase) + offset;
    }

    void registerHeapBuffer(void* pBuffer) {
        mHeapBuffer = pBuffer;
    }

protected:
    MEMiHeapHead* mHeapHandle; // at 0x10
    void* mHeapBuffer;         // at 0x14
    Heap* mParentHeap;         // at 0x18

private:
    enum {
        BIT_DISABLE_ALLOC,
    };

private:
    TBitFlag<u16> mFlags;         // at 0x1C
    NW4R_UT_LIST_LINK_DECL();     // at 0x20
    nw4r::ut::List mDisposerList; // at 0x28

    static Heap* sCurrentHeap;

    static nw4r::ut::List sHeapList;
    static BOOL sIsHeapListInitialized;
    static OSMutex sRootMutex;

    static Heap* sAllocatableHeap;
};

} // namespace EGG

void* operator new(size_t size);
void* operator new(size_t size, EGG::Heap* pHeap, int align = 4);

void* operator new[](size_t size);
void* operator new[](size_t size, int align);
void* operator new[](size_t size, EGG::Heap* pHeap, int align = 4);

void operator delete(void* pBlock) noexcept;
void operator delete[](void* pBlock) noexcept;

#endif
