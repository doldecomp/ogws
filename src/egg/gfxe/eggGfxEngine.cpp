#include <egg/gfxe.h>

namespace EGG {

GfxEngine* GfxEngine::spInstance = NULL;

void GfxEngine::initialize(u16 width, u16 height, Heap* pHeap) {
#line 43
    EGG_ASSERT(spInstance == NULL);

    if (pHeap == NULL) {
        pHeap = Heap::getCurrentHeap();
    }

    spInstance = new (pHeap) GfxEngine();

#line 56
    EGG_ASSERT(spInstance);

    StateGX::initialize();
    StateGX::setEfbWidth(width);
    StateGX::setEfbHeight(height);

    u16 maxX[Screen::TV_MODE_MAX] = {608, 832};
    u16 maxY[Screen::TV_MODE_MAX] = {StateGX::getEfbHeight(),
                                     StateGX::getEfbHeight()};

    Screen::Initialize(maxX, maxY, NULL);
    Screen::SetTVModeDefault();

    G3DUtility::initialize(G3D_HEAP_SIZE, pHeap);
    DrawGX::Initialize(pHeap);
    LightTexture::initialize(LIGHT_TEXTURE_MAX, pHeap);
    TextureBuffer::initialize(width * height * 0xC, pHeap);
}

void GfxEngine::beginDraw() {
    StateGX::frameInit();
    StateGX::doResetStateCache();
    StateGX::setDefaultTexColor(BaseSystem::getDisplay()->getClearColor());

    G3DUtility::clearTempMem();
}

GfxEngine::GfxEngine() : unk4(NULL) {
    unk4 = new UnkStruct();
}

GfxEngine::~GfxEngine() {}

DECOMP_FORCEACTIVE(eggGfxEngine_cpp,
                  "interlace < cVFilter_Max",
                  "progressive < cVFilter_Max");

} // namespace EGG
