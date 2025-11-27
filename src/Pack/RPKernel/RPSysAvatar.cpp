#include <Pack/RPKernel.h>
#include <Pack/RPUtility.h>

#include <RVLFaceLib.h>
#include <cwchar>

/**
 * @brief Constructor
 *
 * @param pGenInfo Mii generation parameters
 */
RPSysAvatar::RPSysAvatar(const RPSysKokeshiGenInfo* pGenInfo) {
    mGenInfo = *pGenInfo;
}

/**
 * @brief Destructor
 */
RPSysAvatar::~RPSysAvatar() {}

/**
 * @brief Loads the assets necessary for this avatar
 *
 * @param pOverloadInfo Overload parameters
 */
void RPSysAvatar::LoadResource(const RPSysKokeshiOverloadInfo* pOverloadInfo) {
    if (pOverloadInfo == NULL) {
        return;
    }

    mOverloadInfo = *pOverloadInfo;
}

/**
 * @brief Gets the RFL favorite color of this avatar
 */
GXColor RPSysAvatar::GetFavoriteColor() const {
    return RFLGetFavoriteColor(
        static_cast<RFLFavoriteColor>(mAdditionalInfo.color));
}

/**
 * @brief Handles post-constructor initialization
 */
void RPSysAvatar::Construct() {}

/**
 * @brief Registers this avatar with the kokeshi manager
 */
void RPSysAvatar::Setup() {
    RPSysKokeshiManager* pKokeshiManager = RP_GET_INSTANCE(RPSysKokeshiManager);

    RPSysKokeshiLocation location = mGenInfo.GetLocation();
    pKokeshiManager->GetAdditionalInfo(location, &mAdditionalInfo);

    // Guest names are not part of the character data
    if (location.GetDataSource() == RFLDataSource_Default) {
        std::wcscpy(mAdditionalInfo.name,
                    pKokeshiManager->GetGuestName(location.GetIndex()));
    }

    // Middle database Miis have their physical appearance randomized
    if (location.GetDataSource() == RFLDataSource_Middle &&
        location.GetMiddleDB()->GetStoredNum() <= location.GetIndex()) {

        mAdditionalInfo.height = RPUtlRandom::getU32(RFL_MAX_BODY_HEIGHT);
        mAdditionalInfo.build = RPUtlRandom::getU32(RFL_MAX_BODY_BUILD);
    }

    pKokeshiManager->RegistLocation(location);
}
