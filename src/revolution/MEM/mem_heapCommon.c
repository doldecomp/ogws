#include <revolution/MEM.h>
#include <revolution/OS.h>

static BOOL sRootListInitialized;
static MEMList sRootList;
static OSMutex sRootMutex;

static MEMiHeapHead* FindContainHeap_(MEMList* list, const void* memBlock) {
    MEMiHeapHead* heap = NULL;

    while (heap = (MEMiHeapHead*)MEMGetNextListObject(list, heap)) {
        if (GetUIntPtr(heap->start) <= GetUIntPtr(memBlock) &&
            GetUIntPtr(memBlock) < GetUIntPtr(heap->end)) {
            MEMiHeapHead* recursive = FindContainHeap_(&heap->list, memBlock);
            if (recursive != NULL) {
                return recursive;
            }
            return heap;
        }
    }

    return NULL;
}

static MEMList* FindListContainHeap_(MEMiHeapHead* heap) {
    MEMList* list = &sRootList;
    MEMiHeapHead* result = FindContainHeap_(&sRootList, heap);
    if (result != NULL) {
        list = &result->list;
    }
    return list;
}

void MEMiInitHeapHead(MEMiHeapHead* heap, u32 magic, void* start, void* end,
                      u16 opt) {
    heap->magic = magic;
    heap->start = start;
    heap->end = end;
    heap->attribute = 0;
    SetOptForHeap(heap, opt);
    MEMInitList(&heap->list, offsetof(MEMiHeapHead, link));

    if (!sRootListInitialized) {
        MEMInitList(&sRootList, offsetof(MEMiHeapHead, link));
        OSInitMutex(&sRootMutex);
        sRootListInitialized = TRUE;
    }

    OSInitMutex(&heap->mutex);

    OSLockMutex(&sRootMutex);
    MEMAppendListObject(FindListContainHeap_(heap), heap);
    OSUnlockMutex(&sRootMutex);
}

void MEMiFinalizeHeap(MEMiHeapHead* heap) {
    OSLockMutex(&sRootMutex);
    MEMRemoveListObject(FindListContainHeap_(heap), heap);
    OSUnlockMutex(&sRootMutex);
    heap->magic = 0;
}

MEMiHeapHead* MEMFindContainHeap(const void* memBlock) {
    return FindContainHeap_(&sRootList, memBlock);
}
