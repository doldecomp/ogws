#include "eggGfxEngine.h"
#include "eggHeap.h"
#include "eggStateGX.h"
#include "eggScreen.h"
#include "eggG3DUtility.h"
#include "eggDrawGX.h"
#include "eggLightTexture.h"
#include "eggTextureBuffer.h"
#include "eggSystem.h"
#include "eggDisplay.h"

namespace EGG
{
    void GfxEngine::initialize(u16 w, u16 h, Heap *heap)
    {
        #line 43
        EGG_ASSERT(spInstance == NULL);

        if (heap == NULL)
            heap = Heap::getCurrentHeap();

        spInstance = new (heap, 4) GfxEngine();
        #line 56
        EGG_ASSERT(spInstance);

        StateGX::initialize();
        StateGX::setEfbWidth(w);
        StateGX::setEfbHeight(h);

        const u16 maxX[] = { 608, 832 };
        const u16 maxY[] = { StateGX::getEfbHeight(), StateGX::getEfbHeight() };
        Screen::Initialize(maxX, maxY, NULL);
        Screen::SetTVModeDefault();

        G3DUtility::initialize(0x6000, heap);
        DrawGX::Initialize(heap);
        LightTexture::initialize(32, heap);
        TextureBuffer::initialize(w * h * 0xC, heap);
    }

    void GfxEngine::beginDraw()
    {
        StateGX::frameInit();
        StateGX::doResetStateCache();

        Display *disp = BaseSystem::getDisplay();
        StateGX::setDefaultTexColor(disp->getClearColor());

        G3DUtility::clearTempMem();
    }

    GfxEngine::GfxEngine() :
        PTR_0x4(NULL)
    {
        PTR_0x4 = new char[1];
    }

    GfxEngine::~GfxEngine()
    {
    }

    GfxEngine *GfxEngine::spInstance = NULL;
}
