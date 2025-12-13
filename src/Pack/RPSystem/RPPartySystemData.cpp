#include <Pack/RPSystem.h>

/**
 * @brief Tests whether the specified minigame is available
 *
 * @param idx Minigame index
 */
bool RPPartySystemData::isGameOpen(s32 idx) const {
    return mGameFlags.onBit(idx);
}
