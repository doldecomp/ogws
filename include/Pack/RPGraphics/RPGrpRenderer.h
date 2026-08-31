#ifndef RP_GRAPHICS_RENDERER_H
#define RP_GRAPHICS_RENDERER_H
#include <Pack/types_pack.h>

#include <egg/core.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class IRPGrpDrawObject;
class RPGrpScreen;

/**
 * @brief Rendering engine
 */
class RPGrpRenderer {
public:
    //! Maximum number of renderer views
    static const int MAX_VIEW = 32;
public:
    enum E_RENDERPASS {
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
        RENDERPASS_NULL
    };

    enum E_VIEW {
        VIEW_29 = 29,
        VIEW_31 = 31,
    };

    //TODO(ThePlayerRolo): Replace this
    struct unk_88 {
        u8 _0; // at 0x0
        u8 _1; // at 0x1
    };
public:
    /**
     * @brief Gets the currently active manager instance
     */
    static RPGrpRenderer* GetCurrent() {
        return spCurrent;
    }

    /**
     * @brief Gets the screen currently being rendered to
     */
    static RPGrpScreen* GetCurrentScreen() {
        return spCurrentScreen;
    }

    /**
     * @brief Gets the ID of the view currently being rendered
     */
    static E_VIEW GetCurrentViewID() {
        return (E_VIEW)sCurrentViewID;
    }

    /**
     * @brief Gets the current render pass of the renderer
     */
    static E_RENDERPASS GetCurrentRenderPass() {
        return sCurrentRenderPass;
    }

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

    void PreCalculate();
    void PostCalculate();
    void CalculateInPause();
    void CreateView2D(E_VIEW, RPGrpScreen*);

    unk_88* get_88() {
        return _88;
    }
private:
    u8 _0[0x88]; // at 0x0
    unk_88* _88; // at 0x88
private:
    //! Allocator used for model-related allocations
    static RPGrpRenderer* spCurrent;

    //! Screen currently being rendered to
    static RPGrpScreen* spCurrentScreen;

    //! Current view being rendered
    static u8 sCurrentViewID;

    //! Current pass of the renderer
    static E_RENDERPASS sCurrentRenderPass;
};

//! @}

#endif
