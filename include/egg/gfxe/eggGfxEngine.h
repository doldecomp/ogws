#ifndef EGG_GFXE_GFX_ENGINE_H
#define EGG_GFXE_GFX_ENGINE_H
#include <egg/types_egg.h>

namespace EGG {

// Forward declarations
class Heap;

class GfxEngine {
private:
    struct UnkStruct {};

private:
    UnkStruct* unk4;
    char unk8[0xC - 0x8];

public:
    static void initialize(u16 width, u16 height, Heap* pHeap);
    static void beginDraw();

    GfxEngine();
    virtual ~GfxEngine(); // at 0x8

private:
    static const u32 G3D_HEAP_SIZE = 0x6000;
    static const u32 LIGHT_TEXTURE_MAX = 32;

private:
    static GfxEngine* spInstance;
};

} // namespace EGG

#endif
