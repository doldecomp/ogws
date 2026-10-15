#ifndef RP_GRAPHICS_RENDERER_H
#define RP_GRAPHICS_RENDERER_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpCamera.h>
#include <Pack/RPGraphics/RPGrpViewRender3D.h>

#include <egg/core.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class IRPGrpDrawObject;
class RPGrpScreen;
class RPGrpView;

/**
 * @brief Rendering engine
 */
class RPGrpRenderer {
public:
    enum RenderPassState {
        RENDERPASS_SYSCALC,
        RENDERPASS_SYSDRAW,
        RENDERPASS_DRAWBEFORE,
        RENDERPASS_DRAW,
        RENDERPASS_DRAWDONE,
        RENDERPASS_DRAW2D,
        RENDERPASS_3DOPA,
        RENDERPASS_3DXLU,
        RENDERPASS_SVBEFORE,
        RENDERPASS_SV,
        RENDERPASS_EFFECT_2,
        RENDERPASS_BEGIN,
        RENDERPASS_END,
        RENDERPASS_NULL,
    };

    //! Maximum number of renderer views
    static const int MAX_VIEW = 32;
    static bool sRendering;
    static RenderPassState sRenderPass;

public:
    /**
     * @brief Gets the currently active manager instance
     */
    static RPGrpRenderer* GetCurrent() {
        return spCurrent;
    }

    /**
     * @brief Gets the view currently being rendered to
     */
    static RPGrpView* GetCurrentView() {
        return spCurrentView;
    }

    RPGrpView* GetView(int idx) const {
        return mpDrawViews[idx];
    }

    /**
     * @brief Gets the screen currently being rendered to
     */
    static RPGrpScreen* GetCurrentScreen() {
        return spCurrentScreen;
    }

    /**
     * @brief Sets up a GX context for rendering
     */
    static void Begin();
    static void End();

    static void StartDebugDraw();

    static RPGrpRenderer* Construct(EGG::Allocator* pAllocator, u16 id);

    void Rendering();
    void Destruct();
    void BecomeCurrent();

    void AppendDrawObject(IRPGrpDrawObject* pObject);
    void AppendDrawObject(IRPGrpDrawObject& rObject) {
        AppendDrawObject(&rObject);
    }

    RPGrpViewRender3D* CreateView3D(u8 viewNo, RPGrpCamera* camera,
                                    RPGrpScreen* screen);

    void PreCalculate();
    void PostCalculate();
    void CalculateInPause();

private:
    //! Allocator used for model-related allocations
    static RPGrpRenderer* spCurrent;

    //! View currently being rendered to
    static RPGrpView* spCurrentView;
    //! Screen currently being rendered to
    static RPGrpScreen* spCurrentScreen;

    char unk0[0xC];
    IRPGrpDrawObject* mpDrawList;     // at 0xC
    IRPGrpDrawObject* mpDrawObj;      // at 0x10
    RPGrpView* mpDrawViews[MAX_VIEW]; // at 0x14
};

//! @}

#endif
