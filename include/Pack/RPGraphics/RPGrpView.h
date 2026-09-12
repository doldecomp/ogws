#ifndef RP_GRAPHICS_VIEW_H
#define RP_GRAPHICS_VIEW_H
#include <Pack/types_pack.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpCamera;
class RPGrpScreen;

/**
 * @brief Base class for renderer views
 */
class RPGrpView {
public:
    /**
     * @brief View class type
     */
    enum EType {
        EType_Render3D, //!< RPGrpViewRender3D
        EType_Render2D, //!< RPGrpViewRender2D
    };

    /**
     * @brief Projection type
     */
    enum EProjType {
        EProjType_Persp, //!< Perspective
        EProjType_Ortho, //!< Orthographic
        EProjType_Max,
    };

    /**
     * @brief View clipper
     */
    class Clipper {
    private:
        //! Left clipping plane
        nw4r::math::VEC3 l; // at 0x0
        //! Top clipping plane
        nw4r::math::VEC3 t; // at 0xC
        //! Right clipping plane
        nw4r::math::VEC3 r; // at 0x18
        //! Bottom clipping plane
        nw4r::math::VEC3 b; // at 0x24

        char unk30[0x48 - 0x30];

    public:
        /**
         * @brief Destructor
         */
        virtual ~Clipper() {} // at 0x8

        /**
         * @brief Re-calculates this clipper's clipping planes
         *
         * @param pScreen Screen rendering surface
         */
        void Calc(const RPGrpScreen* pScreen) DECOMP_DONT_INLINE;

        /**
         * @brief Tests whether the specified bounding sphere falls within the
         * view frustum
         *
         * @param pScreen Screen rendering surface
         * @param rPos Bounding sphere position
         * @param radius Bounding sphere radius
         */
        bool Clip(const RPGrpScreen* pScreen, const nw4r::math::VEC3& rPos,
                  f32 radius);
    };

    /**
     * @brief Screen post-effect
     */
    class ScreenEffect {
    private:
        //! Color to apply through multiply blending
        GXColor mColorMultiply; // at 0x0
        //! Color to apply through addition blending
        GXColor mColorAdd; // at 0x4
        //! Color to apply through normal blending
        GXColor mColorBlend; // at 0x8

        //! Blur effect horizontal offset
        f32 mBlurOffset; // at 0xC
        //! Blur effect transparency
        u8 mBlurAlpha; // at 0x10

    public:
        /**
         * @brief Constructor
         */
        ScreenEffect();

        /**
         * @brief Destructor
         */
        virtual ~ScreenEffect() {} // at 0x8

        /**
         * @brief Draws this effect to the specified screen
         *
         * @param pScreen Screen rendering surface
         */
        void Draw(const RPGrpScreen* pScreen);

        /**
         * @brief Sets the color applied through multiply blending
         *
         * @param rColor Multiply color
         */
        void SetColorMultiply(const GXColor& rColor) {
            mColorMultiply = rColor;
        }

        /**
         * @brief Sets the color applied through addition blending
         *
         * @param rColor Addition color
         */
        void SetColorAdd(const GXColor& rColor) {
            mColorAdd = rColor;
        }

        /**
         * @brief Sets the color applied through normal blending
         *
         * @param rColor Normal blend color
         */
        void SetColorBlend(const GXColor& rColor) {
            mColorBlend = rColor;
        }

        /**
         * @brief Sets the horizontal offset of the blur effect's copies
         *
         * @param offset Horizontal offset
         */
        void SetBlurOffset(f32 offset) {
            mBlurOffset = offset;
        }

        /**
         * @brief Sets the transparency of the blur effect
         *
         * @param alpha Blur effect transparency
         */
        void SetBlurAlpha(u8 alpha) {
            mBlurAlpha = alpha;
        }
    };

protected:
    /**
     * @brief Renderer view flags
     */
    enum {
        //! View will be updated and rendered
        EFlag_SysCalc = 1 << 0,

        //! Update color when clearing the framebuffer
        EFlag_FillBufferColor = 1 << 1,
        //! Update alpha when clearing the framebuffer
        EFlag_FillBufferAlpha = 1 << 2,
        //! Update depth when clearing the framebuffer
        EFlag_FillBufferTexture = 1 << 3,

        EFlag_SysDraw = 1 << 4,
        EFlag_9 = 1 << 9,
    };

protected:
    //! Renderer view ID
    u8 mViewNo; // at 0x0
    //! Model scene ID
    u8 mDrawScene; // at 0x1
    char unk2[0x4 - 0x2];

    //! Renderer view flags
    u16 mFlags; // at 0x4

    //! Projection type
    EProjType mProjType; // at 0x8
    //! Framebuffer clear color
    GXColor mClearColor; // at 0xC

    //! Screen rendering surface
    RPGrpScreen* mpScreen; // at 0x10
    u32 unk14;
    //! Screen post-effect
    ScreenEffect* mpScreenEffect; // at 0x18

private:
    //! Default framebuffer clear color
    static GXColor DEFAULT_CLEAR_COLOR;

    //! View clipper instance
    static Clipper sClipper;

public:
    /**
     * @brief Constructor
     *
     * @param no View ID
     */
    explicit RPGrpView(u8 no);

    /**
     * @brief Destructor
     */
    virtual ~RPGrpView() {} // at 0x8

    /**
     * @brief Gets the type of this view
     */
    virtual EType GetType() const = 0; // at 0xC

    /**
     * @brief Attaches a new camera to this view
     *
     * @param pCamera New camera
     * @return Previously attached camera
     */
    virtual RPGrpCamera* AttachCamera(RPGrpCamera* /* pCamera */) { // at 0x10
        return NULL;
    }

    /**
     * @brief Gets the camera currently attached to this view
     */
    virtual RPGrpCamera* GetCamera() const { // at 0x14
        return NULL;
    }

    /**
     * @brief Initializes this view's state
     */
    virtual void Configure(); // at 0x18

    /**
     * @brief Updates this view's state
     */
    virtual void Calc(); // at 0x1C

    /**
     * @brief Prepares this view for a new frame
     */
    virtual void PrepareDraw(); // at 0x20

    /**
     * @brief Renders the contents of this view
     */
    virtual void Draw() = 0; // at 0x24

    /**
     * @brief Prepares this view for a new render pass
     */
    virtual void PrepareDrawGX() {
        SetProjectionGX();
    } // at 0x28

    /**
     * @brief Attaches a screen effect to this view
     */
    void CreateScreenEffect();

    /**
     * @brief Clears the framebuffer of the attached screen
     */
    void ClearBuffer();

    /**
     * @brief Attaches a new screen to this view
     *
     * @param pScreen Screen rendering surface
     * @return Previously attached screen
     */
    RPGrpScreen* AttachScreen(RPGrpScreen* pScreen);

    /**
     * @brief Configures the GX projection matrix
     */
    void SetProjectionGX() const;

    /**
     * @brief Converts a position from world-space to screen-space
     *
     * @param[out] pScreenPos Position in screen-space
     * @param rWorldPos Position in world-space
     */
    void GetWorldToScreen(nw4r::math::VEC3* pScreenPos,
                          const nw4r::math::VEC3& rWorldPos) const;

    /**
     * @brief Converts a position from screen-space to world-space
     *
     * @param[out] pWorldPos Position in world-space
     * @param rScreenPos Position in screen-space
     */
    void GetScreenToWorld(nw4r::math::VEC3* pWorldPos,
                          const nw4r::math::VEC2& rScreenPos) const;

    /**
     * @brief Gets the screen used by this view.
     * @details If no screen is attached, this function returns the root screen.
     */
    RPGrpScreen* GetEnableScreen() const;

    /**
     * @brief Gets the camera used by this view.
     * @details If no camera is attached, this function returns the default
     * camera.
     */
    RPGrpCamera* GetEnableCamera() const;

    /**
     * @brief Tests whether the specified bounding sphere falls within the
     * view frustum
     *
     * @param pScreen Screen rendering surface
     * @param rPos Bounding sphere position
     * @param radius Bounding sphere radius
     */
    bool Clip(const nw4r::math::VEC3& rPos, f32 radius) const;

    /**
     * @brief Sets this view's model scene
     *
     * @param scene Model scene ID
     */
    void SetDrawScene(u8 scene) {
        mDrawScene = scene;
    }

    /**
     * @brief Tests whether this view should be updated
     */
    bool IsSysCalc() const {
        return mFlags & EFlag_SysCalc;
    }

    /**
     * @brief Tests whether this view should be rendered
     */
    bool IsSysDraw() const {
        return mFlags & EFlag_SysDraw;
    }

    /**
     * @brief Gets this view's projection type
     *
     * @return EProjType
     */
    EProjType GetProjType() const {
        return mProjType;
    }

    /**
     * @brief Get this view's framebuffer clear color
     */
    GXColor GetClearColor() const {
        return mClearColor;
    }

    /**
     * @brief Gets the screen attached to this view
     */
    RPGrpScreen* GetScreen() const {
        return mpScreen;
    }

    /**
     * @brief Gets this view's screen post-effect
     */
    ScreenEffect* GetScreenEffect() const {
        return mpScreenEffect;
    }
};

//! @}

#endif
