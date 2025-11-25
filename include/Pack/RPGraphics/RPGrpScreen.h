#ifndef RP_GRAPHICS_SCREEN_H
#define RP_GRAPHICS_SCREEN_H
#include <Pack/types_pack.h>

#include <egg/gfxe.h>

/**
 * @brief Screen extension
 */
class RPGrpScreen : public EGG::Screen {
public:
    /**
     * @brief Constructor
     * @note The far Z defaults to 100,000
     */
    RPGrpScreen() {
        SetFarZ(100000.0f);
    }

    /**
     * @brief Constructor
     *
     * @param x X position
     * @param y Y position
     * @param width Screen width
     * @param height Screen height
     * @param pParent Parent screen
     * @param canvasMode Coordinate system
     */
    RPGrpScreen(f32 x, f32 y, f32 width, f32 height,
                const Screen* pParent = NULL,
                CanvasMode canvasMode = CANVASMODE_LU)
        : EGG::Screen(x, y, width, height, pParent, canvasMode) {}

    /**
     * @brief Destructor
     */
    virtual ~RPGrpScreen(); // at 0x8
};

#endif
