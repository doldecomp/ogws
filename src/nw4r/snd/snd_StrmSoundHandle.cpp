#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>

namespace nw4r {
namespace snd {

void StrmSoundHandle::DetachSound() {
    if (IsAttachedSound()) {
        if (mSound->mTempSpecialHandle == this) {
            mSound->mTempSpecialHandle = NULL;
        }
    }

    if (mSound != NULL) {
        mSound = NULL;
    }
}

} // namespace snd
} // namespace nw4r
