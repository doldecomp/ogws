#include <revolution/MEM.h>

#define MEM_EXP_HEAP_MAGIC 'EXPH'
#define MEM_EXP_HEAP_MBLOCK_FREE 'FR'
#define MEM_EXP_HEAP_MBLOCK_USED 'UD'

// Size of base and expandable heap head
#define MEM_EXP_HEAP_HEAD_SIZE (sizeof(MEMiHeapHead) + sizeof(MEMiExpHeapHead))

static MEMiExpHeapHead*
GetExpHeapHeadPtrFromHeapHead_(const MEMiHeapHead* heap) {
    return AddU32ToPtr(heap, sizeof(MEMiHeapHead));
}

static MEMiHeapHead*
GetHeapHeadPtrFromExpHeapHead_(const MEMiExpHeapHead* exp) {
    return SubU32ToPtr(exp, sizeof(MEMiHeapHead));
}

static void SetAllocMode_(MEMiExpHeapHead* exp, u16 mode) {
    exp->allocMode = mode;
}

static u16 GetAllocMode_(const MEMiExpHeapHead* exp) {
    return exp->allocMode;
}

static MEMiExpHeapMBlock* GetMBlockHeadPtr_(void* memBlock) {
    return SubU32ToPtr(memBlock, sizeof(MEMiExpHeapMBlock));
}

static const MEMiExpHeapMBlock* GetMBlockHeadCPtr_(const void* memBlock) {
    return SubU32ToCPtr(memBlock, sizeof(MEMiExpHeapMBlock));
}

static void* GetMemPtrForMBlock_(MEMiExpHeapMBlock* mblock) {
    return AddU32ToPtr(mblock, sizeof(MEMiExpHeapMBlock));
}

static void* GetMBlockEndAddr_(MEMiExpHeapMBlock* mblock) {
    return AddU32ToPtr(GetMemPtrForMBlock_(mblock), mblock->size);
}

static s32 GetAlignmentForMBlock_(const MEMiExpHeapMBlock* mblock) {
    return mblock->align;
}

static MEMiExpHeapMBlock* RemoveMBlock_(MEMiExpHeapMBlockList* list,
                                        MEMiExpHeapMBlock* mblock) {
    MEMiExpHeapMBlock* prev;
    MEMiExpHeapMBlock* next;

    prev = mblock->prev;
    next = mblock->next;

    // Fix prev link
    if (prev != NULL) {
        prev->next = next;
    } else {
        list->head = next;
    }

    // Fix next link
    if (next != NULL) {
        next->prev = prev;
    } else {
        list->tail = prev;
    }

    return prev;
}

static void GetRegionOfMBlock_(void** region, MEMiExpHeapMBlock* mblock) {
    region[0] = SubU32ToPtr(mblock, GetAlignmentForMBlock_(mblock));
    region[1] = GetMBlockEndAddr_(mblock);
}

static MEMiExpHeapMBlock* InitMBlock_(void** region, u16 state) {
    MEMiExpHeapMBlock* mblock;
    mblock = (MEMiExpHeapMBlock*)region[0];

    mblock->state = state;
    mblock->settings = 0;
    mblock->size = GetOffsetFromPtr(GetMemPtrForMBlock_(mblock), region[1]);
    mblock->prev = NULL;
    mblock->next = NULL;

    return mblock;
}

static MEMiExpHeapMBlock* InitFreeMBlock_(void** region) {
    return InitMBlock_(region, MEM_EXP_HEAP_MBLOCK_FREE);
}

static MEMiHeapHead* InitExpHeap_(MEMiHeapHead* heap, void* end, u16 opt) {
    MEMiExpHeapMBlock* mblock;
    MEMiExpHeapHead* exp;
    void* region[2];

    exp = GetExpHeapHeadPtrFromHeapHead_(heap);
    MEMiInitHeapHead(heap, MEM_EXP_HEAP_MAGIC,
                     AddU32ToPtr(heap, MEM_EXP_HEAP_HEAD_SIZE), end, opt);
    exp->group = 0;
    exp->SHORT_0x12 = 0;
    SetAllocMode_(exp, MEM_EXP_HEAP_ALLOC_FAST);

    region[0] = heap->start;
    region[1] = heap->end;

    mblock = InitFreeMBlock_(region);
    exp->freeMBlocks.head = mblock;
    exp->freeMBlocks.tail = mblock;

    exp->usedMBlocks.head = NULL;
    exp->usedMBlocks.tail = NULL;

    return heap;
}

// Non-matching
static void* AllocUsedBlockFromFreeBlock_(MEMiExpHeapHead* exp,
                                          MEMiExpHeapMBlock* mblock,
                                          void* memPtr, u32 size,
                                          u16 allocDir) {
}

static void* AllocFromHead_(MEMiHeapHead* heap, u32 size, s32 align) {
    MEMiExpHeapMBlock* it;
    MEMiExpHeapHead* exp;
    MEMiExpHeapMBlock* bestBlk;
    u32 bestBlkSize;
    void* bestBlkMemPtr;
    BOOL isFastAlloc;

    exp = GetExpHeapHeadPtrFromHeapHead_(heap);
    isFastAlloc = GetAllocMode_(exp) == MEM_EXP_HEAP_ALLOC_FAST;
    bestBlk = 0;
    bestBlkSize = 0xFFFFFFFF;
    bestBlkMemPtr = 0;

    for (it = exp->freeMBlocks.head; it != NULL; it = it->next) {
        void* start = GetMemPtrForMBlock_(it);
        void* alignStart = ROUND_UP_PTR(GetUIntPtr(start), align);
        u32 padding = GetOffsetFromPtr(start, alignStart);

        if (it->size >= size + padding && bestBlkSize > it->size) {
            bestBlk = it;
            bestBlkSize = it->size;
            bestBlkMemPtr = alignStart;

            if (isFastAlloc || bestBlkSize == size) {
                break;
            }
        }
    }

    return bestBlk != NULL ? AllocUsedBlockFromFreeBlock_(
                                 exp, bestBlk, bestBlkMemPtr, size, 0)
                           : NULL;
}

// Non-matching
static void* AllocFromTail_(MEMiHeapHead* heap, u32 size, s32 align) {
    MEMiExpHeapMBlock* it;
    MEMiExpHeapHead* exp;
    MEMiExpHeapMBlock* bestBlk;
    u32 bestBlkSize;
    void* bestBlkMemPtr;
    BOOL isFastAlloc;

    exp = GetExpHeapHeadPtrFromHeapHead_(heap);
    isFastAlloc = GetAllocMode_(exp) == MEM_EXP_HEAP_ALLOC_FAST;
    bestBlk = 0;
    bestBlkSize = 0xFFFFFFFF;
    bestBlkMemPtr = 0;

    for (it = exp->freeMBlocks.tail; it != NULL; it = it->prev) {
        void* start = GetMemPtrForMBlock_(it);
        void* end = ROUND_DOWN_PTR(
            GetUIntPtr(SubU32ToPtr(AddU32ToPtr(start, it->size), size)), align);

        if (ComparePtr(end, start) >= 0 && bestBlkSize > it->size) {
            bestBlk = it;
            bestBlkSize = it->size;
            bestBlkMemPtr = end;

            if (isFastAlloc || bestBlkSize == size) {
                break;
            }
        }
    }

    return bestBlk != NULL ? AllocUsedBlockFromFreeBlock_(
                                 exp, bestBlk, bestBlkMemPtr, size, 1)
                           : NULL;
}

// Non-matching
static void RecycleRegion_(MEMiExpHeapHead* exp, void** region) {
}

MEMiHeapHead* MEMCreateExpHeapEx(void* start, u32 size, u16 opt) {
    void* end = AddU32ToPtr(start, size);

    // Heap range
    end = ROUND_DOWN_PTR(end, 4);
    start = ROUND_UP_PTR(start, 4);

    // Ensure valid heap
    if (GetUIntPtr(start) > GetUIntPtr(end) ||
        GetOffsetFromPtr(start, end) < MEM_EXP_HEAP_MIN_SIZE) {
        return NULL;
    }

    return InitExpHeap_(start, end, opt);
}

MEMiHeapHead* MEMDestroyExpHeap(MEMiHeapHead* heap) {
    MEMiFinalizeHeap(heap);
    return heap;
}

void* MEMAllocFromExpHeapEx(MEMiHeapHead* heap, u32 size, s32 align) {
    void* memBlock;

    if (size == 0) {
        size = 1;
    }
    size = ROUND_UP(size, 4);

    LockHeap(heap);

    // Alignment sign determines alloc direction
    if (align >= 0) {
        memBlock = AllocFromHead_(heap, size, align);
    } else {
        memBlock = AllocFromTail_(heap, size, -align);
    }

    UnlockHeap(heap);

    return memBlock;
}

// Non-matching
u32 MEMResizeForMBlockExpHeap(MEMiHeapHead* heap, void* memBlock, u32 size) {
}

void MEMFreeToExpHeap(MEMiHeapHead* heap, void* memBlock) {
    MEMiExpHeapMBlock* mblock;
    MEMiExpHeapHead* exp;
    void* region[2];

    if (memBlock == NULL) {
        return;
    }

    exp = GetExpHeapHeadPtrFromHeapHead_(heap);
    mblock = GetMBlockHeadPtr_(memBlock);

    LockHeap(heap);

    GetRegionOfMBlock_(region, mblock);
    RemoveMBlock_(&exp->usedMBlocks, mblock);
    RecycleRegion_(exp, region);

    UnlockHeap(heap);
}

u32 MEMGetAllocatableSizeForExpHeapEx(MEMiHeapHead* heap, s32 align) {
    MEMiExpHeapMBlock* it;
    MEMiExpHeapHead* exp;
    u32 smallestPadding;
    u32 biggestSize;

    align = __abs(align);
    exp = GetExpHeapHeadPtrFromHeapHead_(heap);

    LockHeap(heap);

    biggestSize = 0;
    smallestPadding = 0xFFFFFFFF;
    for (it = exp->freeMBlocks.head; it != NULL; it = it->next) {
        // MBlock buffer region
        void* start = GetMemPtrForMBlock_(it);
        void* alignStart = ROUND_UP_PTR(GetUIntPtr(start), align);
        void* end = GetMBlockEndAddr_(it);

        if (alignStart < end) {
            u32 size = GetOffsetFromPtr(alignStart, end);
            u32 padding = GetOffsetFromPtr(start, alignStart);

            // MBlock with new best size, or same as best size + less alignment
            // padding
            if (biggestSize < size ||
                (biggestSize == size && smallestPadding > padding)) {
                biggestSize = size;
                smallestPadding = padding;
            }
        }
    }

    UnlockHeap(heap);
    return biggestSize;
}

u32 MEMAdjustExpHeap(MEMiHeapHead* heap) {
    MEMiExpHeapMBlock* mblock;
    MEMiExpHeapHead* exp;
    u32 size;

    exp = GetExpHeapHeadPtrFromHeapHead_(heap);
    LockHeap(heap);

    mblock = exp->freeMBlocks.tail;
    // No free blocks
    if (mblock == NULL) {
        size = 0;
    }
    // Last free block
    else if (AddU32ToPtr(mblock, mblock->size + sizeof(MEMiExpHeapMBlock)) !=
             heap->end) {
        size = 0;
    }
    // Shrink heap by the last free block
    else {
        RemoveMBlock_(&exp->freeMBlocks, mblock);
        heap->end =
            SubU32ToPtr(heap->end, mblock->size + sizeof(MEMiExpHeapMBlock));
        // New adjusted size
        size = GetOffsetFromPtr(heap, heap->end);
    }

    UnlockHeap(heap);

    return size;
}
