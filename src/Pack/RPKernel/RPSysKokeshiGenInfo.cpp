#include <Pack/RPKernel.h>

#include <RVLFaceLib.h>

/**
 * @brief Constructor
 */
RPSysKokeshiGenInfo::RPSysKokeshiGenInfo() {
    mGenType = RPSysKokeshiManager::GenType_None;
    mPlayerNo = 0;
    mBodyType = 0;
    mHandType = RPSysKokeshiManager::HandType_Sphere;
    mViewNo = 1;
    mModelFlags = 0;
    mBufferOption = 0;
    mTexWidth = 128;
    mTexHeight = 128;
    mResolution = RFLResolution_128;
    mExprFlag = RFLExpFlag_Normal;
    mMipMap = false;
    mUseFavoriteColor = false;
    mClearColor.r = mClearColor.g = mClearColor.b = mClearColor.a = 0;
    mIconView = RPSysKokeshiManager::IconView_Front;
    mIconExpression = RFLExp_Normal;
    mMakeEdge = false;
    unk50.r = unk50.g = unk50.b = unk50.a = 0;
    unk54 = 0;
}

/**
 * @brief Destructor
 */
RPSysKokeshiGenInfo::~RPSysKokeshiGenInfo() {}
