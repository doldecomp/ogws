#ifndef TYPES_EGG_H
#define TYPES_EGG_H
#include <types.h>

namespace EGG
{
    struct CpuTexture;

    template <typename T> struct Math;
    struct Matrix34f;
    struct Quatf;
    struct Vector3f;

    template <typename T> struct TBitFlag;

    struct ExpHeap;
    struct FrmHeap;
    struct Heap;

    struct Allocator;
    struct Thread;

    struct Fader;
    struct ColorFader;

    struct Xfb;
    struct XfbManager;

    struct DvdFile;
    struct DvdRipper;

    struct Disposer;

    struct Archive;

    struct Decomp;

    struct Display;
    struct AsyncDisplay;

    struct Video;

    struct MsgRes;

    struct Exception;

    struct Scene;
    struct SceneManager;

    struct CntFile;

    struct ArcPlayer;

    struct IAudioMgr;
    struct SoundHeapMgr;
    struct SimpleAudioMgr;
}

#endif