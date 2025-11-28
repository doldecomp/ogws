#include <Pack/RPKernel.h>

#include <RVLFaceLib.h>

/**
 * @brief Constructor
 */
RPSysMiddleDBGenInfo::RPSysMiddleDBGenInfo()
    : mType(RFLMiddleDBType_Random),
      mSize(0),
      mGenderMask(RFLSex_All),
      mAgeMask(RFLAge_All),
      mRaceMask(RFLRace_All),
      mpMiiManager(NULL) {}

/**
 * @brief Destructor
 */
RPSysMiddleDBGenInfo::~RPSysMiddleDBGenInfo() {}
