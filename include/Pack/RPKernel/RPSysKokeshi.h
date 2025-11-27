#ifndef RP_KERNEL_KOKESHI_H
#define RP_KERNEL_KOKESHI_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics.h>
#include <Pack/RPKernel/RPSysAvatar.h>

#include <egg/math.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Mii avatar model
 */
class RPSysKokeshi : public RPSysAvatar {
public:
    /**
     * @brief Constructor
     *
     * @param pGenInfo Mii generation parameters
     */
    explicit RPSysKokeshi(const RPSysKokeshiGenInfo* pGenInfo);

    /**
     * @brief Destructor
     */
    virtual ~RPSysKokeshi() override; // at 0x8

    /**
     * @brief Loads the assets necessary for this avatar
     *
     * @param pOverloadInfo Overload parameters
     */
    virtual void LoadResource(const RPSysKokeshiOverloadInfo* pOverloadInfo =
                                  NULL) override; // at 0xC

    /**
     * @brief Applies a generated light texture to this avatar
     *
     * @param idx Lightmap texture index
     */
    virtual void ApplyLightTexture(u8 idx) override; // at 0x10

    /**
     * @brief Gets the transformation matrix of the head joint/node
     *
     * @param[out] pMtx Transformation matrix
     */
    void GetHeadJointMtx(EGG::Matrix34f* pMtx);

    /**
     * @brief Gets the transformation matrix of the left hand joint/node
     *
     * @param[out] pMtx Transformation matrix
     */
    void GetLeftHandJointMtx(EGG::Matrix34f* pMtx);

    /**
     * @brief Gets the transformation matrix of the right hand joint/node
     *
     * @param[out] pMtx Transformation matrix
     */
    void GetRightHandJointMtx(EGG::Matrix34f* pMtx);

private:
    /**
     * @brief Handles post-constructor initialization
     */
    void Construct();

private:
    RPGrpModel* mpNigaoeModel;    // at 0xA4
    RPGrpModel* mpBodyModel;      // at 0xA8
    RPGrpModel* mpLeftHandModel;  // at 0xAC
    RPGrpModel* mpRightHandModel; // at 0xB0
};

//! @}

#endif
