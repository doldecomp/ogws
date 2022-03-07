#ifndef TYPES_EGG_H
#define TYPES_EGG_H
#include <types.h>

namespace EGG
{
    // gfx
    struct CapTexture;
    struct CpuTexture;
    struct DrawGX;
    struct DrawPathBase;
    struct Fog;
    struct FogManager;
    struct G3DUtility;
    struct GXUtility;
    struct IDrawGX;
    struct IScnProc;
    struct PostEffectBase;
    struct PostEffectBlur;
    struct PostEffectBlurGather;
    struct ResTIMG;
    struct eggScreen;
    struct ScreenEffectBase;
    struct StateGX;
    struct StateGX;
    struct TextureBuffer;

    // math
    template <typename T> struct Math;
    struct Matrix33f;
    struct Matrix34f;
    struct Matrix44f;
    struct Quatf;
    struct Vector2f;
    struct Vector3f;

    // core
    struct Allocator;
    struct Archive;
    struct AsyncDisplay;
    struct CntFile;
    struct ColorFader;
    struct Decomp;
    struct Display;
    struct Disposer;
    struct DvdFile;
    struct DvdRipper;
    struct ExpHeap;
    struct Fader;
    struct FrmHeap;
    struct Heap;
    struct Scene;
    struct SceneManager;
    template <typename T> struct TBitFlag;
    struct Thread;
    struct Video;
    struct Xfb;
    struct XfbManager;

    // audio
    struct ArcPlayer;
    struct IAudioMgr;
    struct SimpleAudioMgr;
    struct SoundHeapMgr;

    // util
    struct Exception;
    struct MsgRes;
}

#endif