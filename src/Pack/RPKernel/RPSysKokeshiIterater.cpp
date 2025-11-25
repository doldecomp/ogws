#include <Pack/RPKernel.h>

#include <RVLFaceLib.h>

/**
 * @brief Constructor
 *
 * @param src Mii data source to view
 */
RPSysKokeshiIterater::RPSysKokeshiIterater(RFLDataSource src)
    : mDataSource(src) {

    Reset();
}

/**
 * @brief Destructor
 */
RPSysKokeshiIterater::~RPSysKokeshiIterater() {}

/**
 * @brief Moves the iterator back to the start
 */
void RPSysKokeshiIterater::Reset() {
    mIsInitialized = false;
    mIndex = 0;
}

/**
 * @brief Advances the iterator to the next Mii
 *
 * @return Whether the iterator is valid
 */
bool RPSysKokeshiIterater::Update() {
    bool success = false;

    do {
        if (!Increment()) {
            return false;
        }

        // Need to validate because there are often gaps in the database
        switch (mDataSource) {
        case RFLDataSource_Official: {
            if (RFLIsAvailableOfficialData(mIndex)) {
                success = true;
            }
            break;
        }

        case RFLDataSource_Controller1: {
            if (RFLIsAvailableControllerData(WPAD_CHAN0, mIndex)) {
                success = true;
            }
            break;
        }

        case RFLDataSource_Controller2: {
            if (RFLIsAvailableControllerData(WPAD_CHAN1, mIndex)) {
                success = true;
            }
            break;
        }

        case RFLDataSource_Controller3: {
            if (RFLIsAvailableControllerData(WPAD_CHAN2, mIndex)) {
                success = true;
            }
            break;
        }

        case RFLDataSource_Controller4: {
            if (RFLIsAvailableControllerData(WPAD_CHAN3, mIndex)) {
                success = true;
            }
            break;
        }

        case RFLDataSource_Default: {
            success = true;
            break;
        }

        default: {
            break;
        }
        }
    } while (!success);

    return true;
}

/**
 * @brief Advances the iterator one index
 *
 * @return Whether the iterator is valid
 */
bool RPSysKokeshiIterater::Increment() {
    if (!mIsInitialized) {
        mIsInitialized = true;
        mIndex = 0;
        return true;
    }

    mIndex++;

    switch (mDataSource) {
    case RFLDataSource_Official: {
        if (mIndex >= RFL_DB_CHAR_MAX) {
            return false;
        }
        break;
    }

    case RFLDataSource_Controller1:
    case RFLDataSource_Controller2:
    case RFLDataSource_Controller3:
    case RFLDataSource_Controller4: {
        if (mIndex >= RFL_CTRL_CHAR_MAX) {
            return false;
        }
        break;
    }

    case RFLDataSource_Default: {
        if (mIndex >= RFL_DEFAULT_CHAR_MAX) {
            return false;
        }
        break;
    }

    default: {
        break;
    }
    }

    return true;
}
