#ifndef RP_KERNEL_KOKESHI_ICON_H
#define RP_KERNEL_KOKESHI_ICON_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics.h>
#include <Pack/RPKernel/RPSysAvatar.h>
#include <Pack/RPKernel/RPSysKokeshiManager.h>

#include <RVLFaceLib.h>

#include <egg/core.h>
#include <egg/gfx.h>

#include <nw4r/g3d.h>

#include <revolution/GX.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Mii face icon
 */
class RPSysKokeshiIcon : public RPSysAvatar {
public:
    /**
     * @brief Light map texture index
     */
    enum ELightMap {
        ELightMap_lm_0, //!< "lm_0.bti" texture
        ELightMap_lm_1, //!< "lm_1.bti" texture

        ELightMap_Max
    };

public:
    /**
     * @brief Constructor
     *
     * @param pGenInfo Mii generation parameters
     */
    explicit RPSysKokeshiIcon(const RPSysKokeshiGenInfo* pGenInfo);

    /**
     * @brief Destructor
     */
    virtual ~RPSysKokeshiIcon() override; // at 0x8

    /**
     * @brief Loads the assets necessary for this avatar
     *
     * @param pOverloadInfo Overload parameters
     */
    virtual void LoadResource(const RPSysKokeshiOverloadInfo* pOverloadInfo =
                                  NULL) override; // at 0xC

    /**
     * @brief Applies all lightmap textures to this avatar
     *
     * @param drawScene Draw scene index
     */
    virtual void ApplyLightTexture(u8 drawScene) override; // at 0x10

    /**
     * @brief Gets the texture created for this icon
     */
    EGG::ResTIMG* GetResTIMG();

    /**
     * @brief Gets the Mii capture texture
     */
    EGG::CapTexture* GetCapTexture() const {
        return mpCapTexture;
    }

private:
    /**
     * @brief Configures a model for use with icon rendering
     *
     * @param pModel Mii model
     */
    static void SetupModel(RPGrpModel* pModel);

    /**
     * @brief Creates a cap texture for icon rendering
     *
     * @param width Texture width
     * @param height Texture height
     * @param format Texture format
     */
    void InitCapTexture(u16 width, u16 height, GXTexFmt format);

    /**
     * @brief Configures a NW4R camera to capture view this icon's model
     *
     * @param cam G3D camera
     * @param width Texture width
     * @param height Texture heigth
     * @param view Icon viewpoint
     */
    void SetupCamera(nw4r::g3d::Camera cam, u16 width, u16 height,
                     RPSysKokeshiManager::IconView view);

    /**
     * @brief Prepares the GP rendering state
     */
    void BeginMakeTexture() const;

    /**
     * @brief Renders this icon and captures it to a texture
     *
     * @param pModel Mii model
     * @param rLocation Mii storage location
     * @param pAllocator Memory allocator
     * @param width Texture width
     * @param height Texture height
     * @param format Texture format
     * @param bgType Background color type
     * @param bgColor Background color (for RFLIconBG_Direct)
     * @param view Icon viewpoint
     */
    void MakeTexture(RPGrpModel* pModel, const RPSysKokeshiLocation& rLocation,
                     EGG::Allocator* pAllocator, u16 width, u16 height,
                     GXTexFmt format, RFLIconBGType bgType, GXColor bgColor,
                     RPSysKokeshiManager::IconView view);

    /**
     * @brief Finalizes the GP rendering state
     */
    void EndMakeTexture() const;

    /**
     * @brief Renders an outline in the icon around the Mii's face
     */
    void MakeEdge();

    /**
     * @brief Applies the background color to the icon texture
     *
     * @param rLocation Mii storage location
     * @param width Texture width
     * @param height Texture height
     * @param format Texture format
     * @param bgType Background color type
     * @param bgColor Background color (for RFLIconBG_Direct)
     */
    void ModifyBgColor(const RPSysKokeshiLocation& rLocation, u16 width,
                       u16 height, GXTexFmt format, RFLIconBGType bgType,
                       GXColor bgColor);

    /**
     * @brief Handles post-constructor initialization
     */
    void Construct();

private:
    //! Lightmap texture file names
    static const char* LIGHT_TEXTURE_FILE_NAMES[ELightMap_Max];

private:
    //! Mii capture texture
    EGG::CapTexture* mpCapTexture; // at 0xA4
};

//! @}

#endif
