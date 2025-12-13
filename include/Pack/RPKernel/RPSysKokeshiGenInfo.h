#ifndef RP_KERNEL_KOKESHI_GEN_INFO_H
#define RP_KERNEL_KOKESHI_GEN_INFO_H
#include <Pack/RPKernel/RPSysKokeshiLocation.h>
#include <Pack/RPKernel/RPSysKokeshiManager.h>

#include <RVLFaceLib.h>

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
    //! Mii location (only for GenType_Info)
    RPSysKokeshiLocation mLocation; // at 0x8

    //! Body model to use
    u16 mBodyType; // at 0x18
    //! Hand model to use
    u32 mHandType; // at 0x1C

    //! Renderer view ID
    u8 mViewNo; // at 0x20

    u32 mModelFlags; // at 0x24

    u32 mBufferOption; // at 0x28

    //! Texture width for icons
    u16 mTexWidth; // at 0x2C
    //! Texture height for icons
    u16 mTexHeight; // at 0x2E

    //! Resolution of models and textures
    RFLResolution mResolution; // at 0x30
    //! Facial expressions to support
    u32 mExprFlag; // at 0x34

    // Use mipmapping to downscale the icon texture
    BOOL mMipMap;
    //! Whether to use the favorite color as the icon clear color
    BOOL mUseFavoriteColor; // at 0x3C
    //! Display clear color for icons
    GXColor mClearColor; // at 0x40
    //! Camera setup for icons
    RPSysKokeshiManager::IconView mIconView; // at 0x44
    //! Facial expression to use for icons
    RFLExpression mIconExpression; // at 0x48
    //! Whether to outline icons
    BOOL mMakeEdge; // at 0x4C

    GXColor unk50;
    u16 unk54;

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

    u32 GetModelFlags() const {
        return mModelFlags;
    }
    void SetModelFlags(u32 modelFlags) {
        modelFlags = modelFlags;
    }

    u32 GetBufferOption() const {
        return mBufferOption;
    }
    void SetBufferOption(u32 bufferOption) {
        mBufferOption = bufferOption;
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

    const RPSysKokeshiLocation& GetLocation() const {
        return mLocation;
    }
    void SetLocation(const RPSysKokeshiLocation& rLocation) {
        mLocation = rLocation;
    }
};

//! @}

#endif
