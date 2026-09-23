#ifndef EGG_UTIL_EXCEPTION_H
#define EGG_UTIL_EXCEPTION_H
#include <egg/types_egg.h>

namespace EGG {

class Exception {
public:
    static Exception* create(u16 width, u16 height, u16 attr, Heap* pHeap);
    static void setPadInfo(const u16* pPadInfo);
#if defined(VERSION_RSPE01_00)
    static void* sException; // placeholder type
    static void* sMapFileBuffer;
#endif
};

} // namespace EGG

#endif
