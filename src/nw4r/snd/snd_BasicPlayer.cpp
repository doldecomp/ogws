#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>

namespace nw4r {
namespace snd {
namespace detail {

BasicPlayer::BasicPlayer() : mId(-1) { InitParam(); }

void BasicPlayer::InitParam() {
    // TODO: Fakematch
    mPan = 1.0f;

    mPan = 0.0f;
    mVolume = 1.0f;
    mPitch = 1.0f;
    mSurroundPan = 0.0f;
    mLpfFreq = 0.0f;
    mRemoteFilter = 0;
    mPanMode = PAN_MODE_DUAL;
    mPanCurve = PAN_CURVE_SQRT;
    mOutputLine = 1;
    mMainSend = 0.0f;
    mMainOutVolume = 1.0f;

    for (int i = 0; i < AUX_BUS_NUM; i++) {
        mFxSend[i] = 0.0f;
    }

    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        mRemoteOutVolume[i] = 1.0f;
        mRemoteSend[i] = 0.0f;
        mRemoteFxSend[i] = 0.0f;
    }
}

void BasicPlayer::SetFxSend(AuxBus bus, f32 send) { mFxSend[bus] = send; }

f32 BasicPlayer::GetFxSend(AuxBus bus) const { return mFxSend[bus]; }

void BasicPlayer::SetRemoteOutVolume(int remote, f32 vol) {
    mRemoteOutVolume[remote] = vol;
}

f32 BasicPlayer::GetRemoteOutVolume(int remote) const {
    return mRemoteOutVolume[remote];
}

f32 BasicPlayer::GetRemoteSend(int remote) const { return mRemoteSend[remote]; }

f32 BasicPlayer::GetRemoteFxSend(int remote) const {
    return mRemoteFxSend[remote];
}

} // namespace detail
} // namespace snd
} // namespace nw4r
