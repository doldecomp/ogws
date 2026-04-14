#ifndef RP_GRAPHICS_SCREEN_H
#define RP_GRAPHICS_SCREEN_H
#include <Pack/types_pack.h>

#include <egg/gfxe.h>

//! @addtogroup rp_graphics
//! @{

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
    virtual ~RPGrpScreen() override; // at 0x8

    /**
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
     */
    void BeginDrawQuadTexture(bool alpha) const;

    /**
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
};

#endif
