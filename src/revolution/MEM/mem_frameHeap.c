#include <revolution/MEM.h>
#include <revolution/OS.h>

#define MEM_FRM_HEAP_MAGIC 'FRMH'

// Size of base and frame heap head
#define MEM_FRM_HEAP_HEAD_SIZE (sizeof(MEMiHeapHead) + sizeof(MEMiFrmHeapHead))

static MEMiFrmHeapHead*
GetFrmHeapHeadPtrFromHeapHead_(const MEMiHeapHead* heap) {
    return AddU32ToPtr(heap, sizeof(MEMiHeapHead));
}

static MEMiHeapHead*
GetHeapHeadPtrFromFrmHeapHead_(const MEMiFrmHeapHead* frm) {
    return SubU32ToPtr(frm, sizeof(MEMiHeapHead));
}

static MEMiHeapHead* InitFrameHeap_(MEMiHeapHead* heap, void* end, u16 opt) {
    MEMiFrmHeapHead* frm = GetFrmHeapHeadPtrFromHeapHead_(heap);
    MEMiInitHeapHead(heap, MEM_FRM_HEAP_MAGIC,
                     AddU32ToPtr(heap, MEM_FRM_HEAP_HEAD_SIZE), end, opt);
    frm->head = heap->start;
    frm->tail = heap->end;
    frm->states = NULL;
    return heap;
}

static void* AllocFromHead_(MEMiFrmHeapHead* frm, u32 size, s32 align) {
    void* start;
    void* end;

    // Memory block to be allocated
    start = ROUND_UP_PTR(GetUIntPtr(frm->head), align);
    end = AddU32ToPtr(start, size);

    // Not enough memory
    if (end > frm->tail) {
        return NULL;
    }

    // Fill memory block (clear memory, debug fill, etc.)
    // Depends on heap opt.
    FillAllocMemory(GetHeapHeadPtrFromFrmHeapHead_(frm), frm->head,
                    GetOffsetFromPtr(frm->head, end));
    // Adjust heap
    frm->head = end;

    return start;
}

static void* AllocFromTail_(MEMiFrmHeapHead* frm, u32 size, s32 align) {
    void* start;

    // Memory block to be allocated (starts from tail)
    start = SubU32ToPtr(frm->tail, size);
    start = ROUND_DOWN_PTR(GetUIntPtr(start), align);

    // Not enough memory
    if (start < frm->head) {
        return NULL;
    }

    // Fill memory block (clear memory, debug fill, etc.)
    // Depends on heap opt.
    FillAllocMemory(GetHeapHeadPtrFromFrmHeapHead_(frm), start,
                    GetOffsetFromPtr(start, frm->tail));
    // Adjust heap
    frm->tail = start;

    return start;
}

static void FreeHead_(MEMiHeapHead* heap) {
    MEMiFrmHeapHead* frm;

    frm = GetFrmHeapHeadPtrFromHeapHead_(heap);
    frm->head = heap->start;
    frm->states = NULL;
}

static void FreeTail_(MEMiHeapHead* heap) {
    MEMiFrmHeapState* state;
    MEMiFrmHeapHead* frm;

    frm = GetFrmHeapHeadPtrFromHeapHead_(heap);
    for (state = frm->states; state != NULL; state = state->next) {
        state->tail = heap->end;
    }

    frm->tail = heap->end;
}

MEMiHeapHead* MEMCreateFrmHeapEx(void* start, u32 size, u16 opt) {
    void* end = AddU32ToPtr(start, size);

    // Heap range
    end = ROUND_DOWN_PTR(end, 4);
    start = ROUND_UP_PTR(start, 4);

    // Ensure valid heap
    if (GetUIntPtr(start) > GetUIntPtr(end) ||
        GetOffsetFromPtr(start, end) < MEM_FRM_HEAP_MIN_SIZE) {
        return NULL;
    }

    return InitFrameHeap_(start, end, opt);
}

MEMiHeapHead* MEMDestroyFrmHeap(MEMiHeapHead* heap) {
    MEMiFinalizeHeap(heap);
    return heap;
}

void* MEMAllocFromFrmHeapEx(MEMiHeapHead* heap, u32 size, s32 align) {
    MEMiFrmHeapHead* frm;
    void* memBlock;

    frm = GetFrmHeapHeadPtrFromHeapHead_(heap);

    if (size == 0) {
        size = 1;
    }
    size = ROUND_UP(size, 4);

    LockHeap(heap);
    // Alignment sign determines alloc direction
    if (align >= 0) {
        memBlock = AllocFromHead_(frm, size, align);
    } else {
        memBlock = AllocFromTail_(frm, size, -align);
    }
    UnlockHeap(heap);

    return memBlock;
}

void MEMFreeToFrmHeap(MEMiHeapHead* heap, u32 flags) {
    LockHeap(heap);
    if (flags & MEM_FRM_HEAP_FREE_TO_HEAD) {
        FreeHead_(heap);
    }
    if (flags & MEM_FRM_HEAP_FREE_TO_TAIL) {
        FreeTail_(heap);
    }
    UnlockHeap(heap);
}

u32 MEMGetAllocatableSizeForFrmHeapEx(MEMiHeapHead* heap, s32 align) {
    MEMiFrmHeapHead* frm;
    BOOL enabled;
    void* start;
    u32 size;

    align = __abs(align);

    enabled = OSDisableInterrupts();
    frm = GetFrmHeapHeadPtrFromHeapHead_(heap);

    start = ROUND_UP_PTR(frm->head, align);

    if (start > frm->tail) {
        size = 0;
    } else {
        size = GetOffsetFromPtr(start, frm->tail);
    }

    OSRestoreInterrupts(enabled);
    return size;
}

BOOL MEMRecordStateForFrmHeap(MEMiHeapHead* heap, u32 id) {
    MEMiFrmHeapState* state;
    MEMiFrmHeapHead* frm;
    BOOL success;
    u8* head;

    LockHeap(heap);
    frm = GetFrmHeapHeadPtrFromHeapHead_(heap);

    // Backup heap head because it is about to change
    head = frm->head;
    state = AllocFromHead_(frm, sizeof(MEMiFrmHeapState), 4);

    if (state == NULL) {
        success = FALSE;
    } else {
        state->id = id;
        state->head = head;
        state->tail = frm->tail;

        state->next = frm->states;
        frm->states = state;

        success = TRUE;
    }

    UnlockHeap(heap);
    return success;
}

BOOL MEMFreeByStateToFrmHeap(MEMiHeapHead* heap, u32 id) {
    MEMiFrmHeapState* state;
    MEMiFrmHeapHead* frm;
    BOOL success;

    LockHeap(heap);
    frm = GetFrmHeapHeadPtrFromHeapHead_(heap);
    state = frm->states;

    // Find specified state
    if (id != 0) {
        for (; state != NULL; state = state->next) {
            if (state->id == id) {
                break;
            }
        }
    }

    if (state == NULL) {
        success = FALSE;
    } else {
        frm->head = state->head;
        frm->tail = state->tail;
        frm->states = state->next;

        success = TRUE;
    }

    UnlockHeap(heap);
    return success;
}

u32 MEMAdjustFrmHeap(MEMiHeapHead* heap) {
    MEMiFrmHeapHead* frm;
    u32 newSize;

    LockHeap(heap);
    frm = GetFrmHeapHeadPtrFromHeapHead_(heap);

    if (GetOffsetFromPtr(frm->tail, heap->end) != 0) {
        newSize = 0;
    } else {
        heap->end = frm->head;
        frm->tail = frm->head;
        newSize = GetOffsetFromPtr(heap, frm->head);
    }

    UnlockHeap(heap);
    return newSize;
}

u32 MEMResizeForMBlockFrmHeap(MEMiHeapHead* heap, void* memBlock, u32 size) {
    MEMiFrmHeapHead* frm;
    u8* newHead;
    u32 offset;

    if (size == 0) {
        size = 1;
    }
    size = ROUND_UP(size, 4);

    LockHeap(heap);
    frm = GetFrmHeapHeadPtrFromHeapHead_(heap);

    offset = GetOffsetFromPtr(memBlock, frm->head);
    newHead = AddU32ToPtr(memBlock, size);

    if (size != offset) {
        if (size > offset) {
            if (GetOffsetFromPtr(frm->tail, newHead) > 0) {
                size = 0;
                goto exit;
            }

            FillAllocMemory(heap, frm->head, size - offset);
        }

        frm->head = newHead;
    }

exit:
    UnlockHeap(heap);
    return size;
}
