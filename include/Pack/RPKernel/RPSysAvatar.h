#ifndef RP_KERNEL_AVATAR_H
#define RP_KERNEL_AVATAR_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel/RPSysKokeshiGenInfo.h>
#include <Pack/RPKernel/RPSysKokeshiOverloadInfo.h>
#include <Pack/RPKernel/RP_DEBUG_STUB_1.h>

#include <RVLFaceLib.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Base class for Mii avatars
 */
class RPSysAvatar : public RP_DEBUG_STUB_1 {
public:
    /**
     * @brief Light map texture index
     */
    enum ELightMap {
        ELightMap_lm_0,
        ELightMap_lm_1,
    };

public:
    /**
     * @brief Constructor
     *
     * @param pGenInfo Mii generation parameters
     */
    explicit RPSysAvatar(const RPSysKokeshiGenInfo* pGenInfo);

    /**
     * @brief Destructor
     */
    virtual ~RPSysAvatar() override; // at 0x8

    /**
     * @brief Loads the assets necessary for this avatar
     *
     * @param pOverloadInfo Overload parameters
     */
    virtual void LoadResource(
        const RPSysKokeshiOverloadInfo* pOverloadInfo = NULL); // at 0xC

    /**
     * @brief Applies a generated light texture to this avatar
     *
     * @param idx Lightmap texture index
     */
    virtual void ApplyLightTexture(u8 idx) = 0; // at 0x10

    /**
     * @brief Gets the RFL favorite color of this avatar
     */
    GXColor GetFavoriteColor() const;

protected:
    /**
     * @brief Handles post-constructor initialization
     */
    void Construct();

    /**
     * @brief Registers this avatar with the kokeshi manager
     */
    void Setup();

protected:
    //! Mii generation parameters
    RPSysKokeshiGenInfo mGenInfo; // at 0x4
    //! Generation overload parameters
    RPSysKokeshiOverloadInfo mOverloadInfo; // at 0x60
    //! Additional info from face library
    RFLAdditionalInfo mAdditionalInfo; // at 0x68
};

//! @}

#endif
