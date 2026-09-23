#ifndef RP_GRAPHICS_VIEW_RENDER_3D_H
#define RP_GRAPHICS_VIEW_RENDER_3D_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics/RPGrpView.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpCamera;

/**
 * @brief Renderer view for 3D graphics
 */
class RPGrpViewRender3D : public RPGrpView {
public:
    /**
     * @brief Constructor
     *
     * @param no View ID
     */
    explicit RPGrpViewRender3D(u8 no);

    /**
     * @brief Gets the type of this view
     */
    virtual EType GetType() const override { // at 0xC
        return EType_Render3D;
    }

    /**
     * @brief Attaches a new camera to this view
     *
     * @param pCamera New camera
     * @return Previously attached camera
     */
    virtual RPGrpCamera* AttachCamera(RPGrpCamera* pCamera) override;

    /**
     * @brief Gets the camera currently attached to this view
     */
    virtual RPGrpCamera* GetCamera() const override { // at 0x14
        return mpCamera;
    }

    /**
     * @brief Updates this view's state
     */
    virtual void Calc() override; // at 0x1C

    /**
     * @brief Prepares this view for a new frame
     */
    virtual void PrepareDraw() override; // at 0x20

    /**
     * @brief Renders the contents of this view
     */
    virtual void Draw() override; // at 0x24

    /**
     * @brief Prepares this view for a new render pass
     */
    virtual void PrepareDrawGX() override; // at 0x28

private:
    //! Camera attached to this view
    RPGrpCamera* mpCamera; // at 0x20

    u8 unk24;
};

//! @}

#endif
