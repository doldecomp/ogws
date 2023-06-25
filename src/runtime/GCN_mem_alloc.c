#include <revolution/OS.h>
#include <runtime/GCN_mem_alloc.h>

void __sys_free(void* block) {
    void* start;
    void* end;
    s32 heap;

    if (__OSCurrHeap == -1) {
        OSReport("GCN_Mem_Alloc.c : InitDefaultHeap. No Heap Available\n");
        OSReport("Metrowerks CW runtime library initializing default heap\n");

        start = OSGetArenaLo();
        end = (0, OSGetArenaHi());

        start = OSInitAlloc(start, end, 1);
        OSSetArenaLo(start);

        start = ROUND_UP_PTR(start, 32);
        end = ROUND_DOWN_PTR(end, 32);

        heap = OSCreateHeap(start, end);
        OSSetCurrentHeap(heap);

        OSSetArenaLo(end);
    }

    OSFreeToHeap(__OSCurrHeap, block);
}