#ifndef RP_GRAPHICS_SCREEN_H
#define RP_GRAPHICS_SCREEN_H
#include <Pack/types_pack.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

<<<<<<< HEAD
=======
// Forward declarations
class RPGrpTexture;

>>>>>>> 082cf7d8 (temp)
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
<<<<<<< HEAD
     * @brief Sets up the screen to draw a solid color quad.
     */
    void BeginDrawQuad() const;

    /**
     * @brief Draws a solid color quad to the screen
     *
     * @param x Quad X position
     * @param y Quad Y position
     * @param width Quad width
     * @param height Quad height
     * @param color Quad color
     */
    void DrawQuad(f32 x, f32 y, f32 width, f32 height, GXColor color);

    /**
     * @brief Sets up the screen to draw a texture quad.
     *
     * @param alpha Does the texture have an alpha channel
=======
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
>>>>>>> 082cf7d8 (temp)
     */
    void BeginDrawQuadTexture(bool alpha) const;

    /**
<<<<<<< HEAD
     * @brief Draws a texture on a quad to the screen
     *
     * @param x Quad X position
     * @param y Quad Y position
     * @param width Quad width
     * @param height Quad height
     * @param pTextureRes Texture image resource
     * @param color Quad color
     */
    void DrawQuadTexture(f32 x, f32 y, f32 width, f32 height,
                         EGG::ResTIMG* pTextureRes, GXColor color);

    /**
     * @brief Initalizes the default screen.
     *
     * @param maxX Maximum X
     * @param maxY Maximun Y
     */
    static void Initialize(const u16 maxX[TV_MODE_MAX],
                           const u16 maxY[TV_MODE_MAX]);

public:
    //! Default screen settings
    static RPGrpScreen g_default_screen;
=======
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
>>>>>>> 082cf7d8 (temp)
};

//! @}

#endif
