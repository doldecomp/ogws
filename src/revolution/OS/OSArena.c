#include <revolution/OS.h>

static void* __OSArenaLo = (void*)-1;
static void* s_mem2ArenaLo = (void*)-1;
static void* __OSArenaHi = NULL;
static void* s_mem2ArenaHi = NULL;

void* OSGetMEM1ArenaHi(void) {
    return __OSArenaHi;
}

void* OSGetMEM2ArenaHi(void) {
    return s_mem2ArenaHi;
}

void* OSGetArenaHi(void) {
    return OSGetMEM1ArenaHi();
}

void* OSGetMEM1ArenaLo(void) {
    return __OSArenaLo;
}

void* OSGetMEM2ArenaLo(void) {
    return s_mem2ArenaLo;
}

void* OSGetArenaLo(void) {
    return OSGetMEM1ArenaLo();
}

void OSSetMEM1ArenaHi(void* hi) {
    __OSArenaHi = hi;
}

void OSSetMEM2ArenaHi(void* hi) {
    s_mem2ArenaHi = hi;
}

void OSSetArenaHi(void* hi) {
    OSSetMEM1ArenaHi(hi);
}

void OSSetMEM1ArenaLo(void* lo) {
    __OSArenaLo = lo;
}

void OSSetMEM2ArenaLo(void* lo) {
    s_mem2ArenaLo = lo;
}

void OSSetArenaLo(void* lo) {
    OSSetMEM1ArenaLo(lo);
}

void* OSAllocFromMEM1ArenaLo(size_t size, u32 align) {
    u8* begin = ROUND_UP_PTR(OSGetMEM1ArenaLo(), align);
    u8* end = begin + size;
    end = ROUND_UP_PTR(end, align);
    OSSetMEM1ArenaLo(end);
    return begin;
}
