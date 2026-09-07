#ifndef RP_GRAPHICS_RENDERER_H
#define RP_GRAPHICS_RENDERER_H
#include <Pack/types_pack.h>

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
    //! Maximum number of renderer views
    static const int MAX_VIEW = 32;

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
        return mDrawViews[idx];
    }

    /**
     * @brief Gets the screen currently being rendered to
     */
    static RPGrpScreen* GetCurrentScreen() {
        return spCurrentScreen;
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

private:
    //! Allocator used for model-related allocations
    static RPGrpRenderer* spCurrent;

    //! View currently being rendered to
    static RPGrpView* spCurrentView;
    //! Screen currently being rendered to
    static RPGrpScreen* spCurrentScreen;

    char unk0[0xC];
    IRPGrpDrawObject* mpDrawList; // at 0xC
    char unk10[0x14 - 0x10];
    RPGrpView* mDrawViews[MAX_VIEW]; // at 0x14
};

//! @}

#endif
