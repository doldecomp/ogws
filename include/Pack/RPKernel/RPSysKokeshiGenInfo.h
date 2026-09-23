#ifndef RP_KERNEL_KOKESHI_GEN_INFO_H
#define RP_KERNEL_KOKESHI_GEN_INFO_H
#include <Pack/RPKernel/RPSysKokeshiLocation.h>
#include <Pack/RPKernel/RPSysKokeshiManager.h>

#include <RVLFaceLib.h>

#include <revolution/GX.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Mii generation parameters
 */
class RPSysKokeshiGenInfo {
private:
    //! Type of Mii to generate
    RPSysKokeshiManager::GenType mGenType; // at 0x0
    //! Player slot ID
    u8 mPlayerNo; // at 0x4
    //! Mii storage location
    RPSysKokeshiLocation mLocation; // at 0x8

    //! Body model to use
    u16 mBodyType; // at 0x18
    //! Hand model to use
    u32 mHandType; // at 0x1C

    //! Renderer view ID
    u8 mViewNo; // at 0x20
    //! RP model type option flags
    u32 mTypeOption; // at 0x24
    //! NW4R model buffer option flags
    u32 mBufferOption; // at 0x28

    //! Texture width for icons
    u16 mIconWidth; // at 0x2C
    //! Texture height for icons
    u16 mIconHeight; // at 0x2E

    //! Resolution of models and textures
    RFLResolution mResolution; // at 0x30
    //! Facial expressions to support
    u32 mExprFlag; // at 0x34

    // Use mipmapping to downscale the icon texture
    BOOL mIconMipMap; // at 0x38
    //! Background type to use for icons
    RFLIconBGType mIconBGType; // at 0x3C
    //! Background color to use for icons
    GXColor mIconBGColor; // at 0x40
    //! Camera viewpoint to use for icons
    RPSysKokeshiManager::IconView mIconView; // at 0x44
    //! Facial expression to use for icons
    RFLExpression mIconExpression; // at 0x48
    //! Whether to draw an outline around icons
    BOOL mIconEdge; // at 0x4C
    //! Edge color to use for icons
    GXColor mIconEdgeColor; // at 0x50
    //! Width of the edge outline for icons
    u16 mIconEdgeWidth; // at 0x54

public:
    /**
     * @brief Constructor
     */
    RPSysKokeshiGenInfo();

    /**
     * @brief Destructor
     */
    virtual ~RPSysKokeshiGenInfo(); // at 0x8

    RPSysKokeshiManager::GenType GetGenType() const {
        return mGenType;
    }
    void SetGenType(RPSysKokeshiManager::GenType genType) {
        mGenType = genType;
    }

    u8 GetPlayerNo() const {
        return mPlayerNo;
    }
    void SetPlayerNo(u8 playerNo) {
        mPlayerNo = playerNo;
    }

    u16 GetBodyType() const {
        return mBodyType;
    }
    void SetBodyType(u16 bodyType) {
        mBodyType = bodyType;
    }

    u32 GetHandType() const {
        return mHandType;
    }
    void SetHandType(u32 handType) {
        mHandType = handType;
    }

    u8 GetViewNo() const {
        return mViewNo;
    }
    void SetViewNo(u8 viewNo) {
        mViewNo = viewNo;
    }

    u32 GetTypeOption() const {
        return mTypeOption;
    }
    void SetTypeOption(u32 typeOption) {
        mTypeOption = typeOption;
    }

    u32 GetBufferOption() const {
        return mBufferOption;
    }
    void SetBufferOption(u32 bufferOption) {
        mBufferOption = bufferOption;
    }

    u16 GetIconWidth() const {
        return mIconWidth;
    }
    void SetIconWidth(u16 width) {
        mIconWidth = width;
    }

    u16 GetIconHeight() const {
        return mIconHeight;
    }
    void SetIconHeight(u16 height) {
        mIconHeight = height;
    }

    RFLResolution GetResolution() const {
        return mResolution;
    }
    void SetResolution(RFLResolution resolution) {
        mResolution = resolution;
    }

    u32 GetExpressionFlag() const {
        return mExprFlag;
    }
    void SetExpressionFlag(u32 exprFlag) {
        mExprFlag = exprFlag;
    }

    bool GetIconMipMap() const {
        return mIconMipMap;
    }
    void SetIconMipMap(bool mipMap) {
        mIconMipMap = mipMap;
    }

    RFLIconBGType GetIconBGType() const {
        return mIconBGType;
    }
    void SetIconBGType(RFLIconBGType bgType) {
        mIconBGType = bgType;
    }

    const GXColor& GetIconBGColor() const {
        return mIconBGColor;
    }
    void SetIconBGColor(const GXColor& rColor) {
        mIconBGColor = rColor;
    }

    RPSysKokeshiManager::IconView GetIconView() const {
        return mIconView;
    }
    void SetIconView(RPSysKokeshiManager::IconView view) {
        mIconView = view;
    }

    RFLExpression GetIconExpression() const {
        return mIconExpression;
    }
    void SetIconExpression(RFLExpression expr) {
        mIconExpression = expr;
    }

    bool GetIconEdge() const {
        return mIconEdge;
    }
    void SetIconEdge(bool edge) {
        mIconEdge = edge;
    }

    const GXColor& GetIconEdgeColor() const {
        return mIconEdgeColor;
    }
    void SetIconEdgeColor(const GXColor& rColor) {
        mIconEdgeColor = rColor;
    }

    u16 GetIconEdgeWidth() const {
        return mIconEdgeWidth;
    }
    void SetIconEdgeWidth(u16 width) {
        mIconEdgeWidth = width;
    }

    const RPSysKokeshiLocation& GetLocation() const {
        return mLocation;
    }
    void SetLocation(const RPSysKokeshiLocation& rLocation) {
        mLocation = rLocation;
    }
};

//! @}

#endif
