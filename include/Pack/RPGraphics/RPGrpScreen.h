#ifndef RP_GRAPHICS_SCREEN_H
#define RP_GRAPHICS_SCREEN_H
#include <Pack/types_pack.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpTexture;

/**
 * @brief Screen rendering surface
 */
class RPGrpScreen : public EGG::Screen {
public:
    /**
     * @brief Initializes the screen system
     *
     * @param maxX Screen width limits for all TV modes
     * @param maxY Screen height limits for all TV modes
     */
    static void Initialize(const u16 maxX[TV_MODE_MAX],
                           const u16 maxY[TV_MODE_MAX]);

    /**
     * @brief Constructor
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
                const EGG::Screen* pParent = NULL,
                CanvasMode canvasMode = CANVASMODE_LU)
        : EGG::Screen(x, y, width, height, pParent, canvasMode) {}

    /**
     * @brief Configures the GX rendering state to draw a quad
     */
    void BeginDrawQuad() const;

    /**
     * @brief Draws a colored quad to this screen
     *
     * @param x1 Left point of the quad
     * @param y1 Top point of the quad
     * @param x2 Right point of the quad
     * @param y2 Bottom point of the quad
     * @param color Fill color
     */
    void DrawQuad(f32 x1, f32 y1, f32 x2, f32 y2, GXColor color) const;

    /**
     * @brief Configures the GX rendering state to draw a textured quad
     *
     * @param alpha Whether to enable the raster alpha channel
     */
    void BeginDrawQuadTexture(bool alpha) const;

    /**
     * @brief Draws a textured quad to this screen
     * @details It is assumed the texture has already been loaded to GX_TEXMAP0.
     *
     * @param x1 Left point of the quad
     * @param y1 Top point of the quad
     * @param x2 Right point of the quad
     * @param y2 Bottom point of the quad
     * @param color Material color
     */
    void DrawQuadTexture(f32 x1, f32 y1, f32 x2, f32 y2, GXColor color) const;

    /**
     * @brief Draws a textured quad to this screen
     *
     * @param x1 Left point of the quad
     * @param y1 Top point of the quad
     * @param x2 Right point of the quad
     * @param y2 Bottom point of the quad
     * @param rTexture Fill texture
     * @param color Material color
     */
    void DrawQuadTexture(f32 x1, f32 y1, f32 x2, f32 y2,
                         const RPGrpTexture& rTexture, GXColor color) const;

    /**
     * @brief Draws a textured quad to this screen
     *
     * @param x1 Left point of the quad
     * @param y1 Top point of the quad
     * @param x2 Right point of the quad
     * @param y2 Bottom point of the quad
     * @param pResTIMG Fill texture
     * @param color Material color
     */
    void DrawQuadTexture(f32 x1, f32 y1, f32 x2, f32 y2,
                         const EGG::ResTIMG* pResTIMG, GXColor color) const;

    /**
     * @brief Accesses the root of the screen hierarchy
     */
    static RPGrpScreen& GetRootScreen() {
        return sRootScreen;
    }

private:
    //! Screen hierarchy root
    static RPGrpScreen sRootScreen;
};

//! @}

#endif
