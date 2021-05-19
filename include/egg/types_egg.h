#ifndef TYPES_EGG_H
#define TYPES_EGG_H
#include <types.h>

namespace EGG
{
    template <typename T> struct Math;
    struct Matrix34f;
    struct Quatf;
    struct Vector3f;

    template <typename T> struct TBitFlag;

    struct ExpHeap;
    struct FrmHeap;
    struct Heap;

    struct Disposer;

    struct Allocator;
    struct Thread;

    struct Fader;
    struct ColorFader;

    struct Xfb;
    struct XfbManager;

    struct Archive;

    struct MsgRes;
}

#endif