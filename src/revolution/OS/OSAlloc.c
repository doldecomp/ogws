#include <revolution/OS.h>

typedef struct OSHeapDescriptor {
    s32 size;                    // at 0x0
    struct OSHeapCell* freeList; // at 0x4
    struct OSHeapCell* usedList; // at 0x8
} OSHeapDescriptor;

typedef struct OSHeapCell {
    struct OSHeapCell* prev;     // at 0x0
    struct OSHeapCell* next;     // at 0x4
    s32 size;                    // at 0x8
    struct OSHeapDescriptor* hd; // at 0xC
    s32 usedSize;                // at 0x10
    char UNK_0x14[0x20 - 0x14];
} OSHeapCell;

volatile s32 __OSCurrHeap = -1;

static void* ArenaEnd = NULL;
static void* ArenaStart = NULL;
static s32 NumHeaps = 0;
static OSHeapDescriptor* HeapArray = NULL;

static OSHeapCell* DLAddFront(OSHeapCell* list, OSHeapCell* child) {
    child->next = list;
    child->prev = NULL;

    if (list != NULL) {
        list->prev = child;
    }

    return child;
}

static OSHeapCell* DLExtract(OSHeapCell* list, OSHeapCell* child) {
    if (child->next != NULL) {
        child->next->prev = child->prev;
    }

    if (child->prev == NULL) {
        return child->next;
    }

    child->prev->next = child->next;
    return list;
}

static OSHeapCell* DLInsert(OSHeapCell* list, OSHeapCell* child) {
    OSHeapCell* prev = NULL;
    OSHeapCell* next = list;

    for (; next != NULL; prev = next, next = next->next) {
        if (child <= next) {
            break;
        }
    }

    child->next = next;
    child->prev = prev;

    if (next != NULL) {
        next->prev = child;

        if ((u8*)child + child->size == (u8*)next) {
            child->size += next->size;
            next = next->next;
            child->next = next;
            if (next != NULL) {
                next->prev = child;
            }
        }
    }

    if (prev != NULL) {
        prev->next = child;

        if ((u8*)prev + prev->size == (u8*)child) {
            prev->size += child->size;
            prev->next = next;
            if (next != NULL) {
                next->prev = prev;
            }
        }

        return list;
    } else {
        return child;
    }
}

void* OSAllocFromHeap(s32 handle, s32 size) {
    OSHeapDescriptor* hd = &HeapArray[handle];
    OSHeapCell* cell;
    u32 avail;

    hd = &HeapArray[handle];
    size = ROUND_UP(size + sizeof(OSHeapCell), 32);

    for (cell = hd->freeList; cell != NULL; cell = cell->next) {
        if (size <= cell->size) {
            break;
        }
    }

    if (cell == NULL) {
        return NULL;
    }

    avail = cell->size - size;
    if (avail < 64) {
        hd->freeList = DLExtract(hd->freeList, cell);
    } else {
        OSHeapCell* adj;
        cell->size = size;

        adj = (OSHeapCell*)((u8*)cell + size);
        adj->size = avail;
        adj->prev = cell->prev;
        adj->next = cell->next;

        if (adj->next != NULL) {
            adj->next->prev = adj;
        }

        if (adj->prev != NULL) {
            adj->prev->next = adj;
        } else {
            hd->freeList = adj;
        }
    }

    hd->usedList = DLAddFront(hd->usedList, cell);
    return (u8*)cell + sizeof(OSHeapCell);
}

void OSFreeToHeap(s32 handle, void* p) {
    OSHeapDescriptor* hd = &HeapArray[handle];
    OSHeapCell* cell = (OSHeapCell*)((u8*)p - sizeof(OSHeapCell));
    hd->usedList = DLExtract(hd->usedList, cell);
    hd->freeList = DLInsert(hd->freeList, cell);
}

s32 OSSetCurrentHeap(s32 handle) {
    s32 old = __OSCurrHeap;
    __OSCurrHeap = handle;
    return old;
}

void* OSInitAlloc(void* start, void* end, s32 numHeaps) {
    u32 headerSize;
    int i;

    headerSize = numHeaps * sizeof(OSHeapDescriptor);
    HeapArray = (OSHeapDescriptor*)start;
    NumHeaps = numHeaps;

    for (i = 0; i < NumHeaps; i++) {
        OSHeapDescriptor* hd = &HeapArray[i];
        hd->size = -1;
        hd->usedList = NULL;
        hd->freeList = NULL;
    }

    __OSCurrHeap = -1;
    ArenaStart = ROUND_UP_PTR((u8*)HeapArray + headerSize, 32);
    ArenaEnd = ROUND_DOWN_PTR(end, 32);

    return ArenaStart;
}

s32 OSCreateHeap(void* start, void* end) {
    s32 handle;

    start = ROUND_UP_PTR(start, 32);
    end = ROUND_DOWN_PTR(end, 32);

    for (handle = 0; handle < NumHeaps; handle++) {
        OSHeapCell* cell = (OSHeapCell*)start;
        OSHeapDescriptor* hd = &HeapArray[handle];
        if (hd->size < 0) {
            hd->size = (uintptr_t)end - (uintptr_t)start;

            cell->prev = NULL;
            cell->next = NULL;
            cell->size = hd->size;

            hd->freeList = cell;
            hd->usedList = NULL;
            return handle;
        }
    }

    return -1;
}
