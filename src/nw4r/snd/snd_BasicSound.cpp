#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>

namespace nw4r {
namespace snd {
namespace detail {

NW4R_UT_RTTI_DEF_BASE(BasicSound);

BasicSound::BasicSound()
    : mPlayerHeap(NULL),
      mGeneralHandle(NULL),
      mTempGeneralHandle(NULL),
      mSoundPlayer(NULL),
      mExtSoundPlayer(NULL),
      mParamUpdateCallback(NULL),
      mArgUpdateCallback(NULL),
      mArgAllocCallback(NULL),
      mCallbackArg(NULL),
      mId(0xFFFFFFFF) {}

void BasicSound::InitParam() {
    mIsPause = false;
    mIsPauseFade = false;
    mIsStarting = false;
    mIsStarted = false;
    mIsAutoStop = false;
    mIsFadeOut = false;

    mAutoStopCounter = 0;
    mUpdateCounter = 0;

    mFadeVolume.InitValue(0.0f);
    mPauseFadeVolume.InitValue(1.0f);
    mFadeVolume.SetTarget(1.0f, 1);

    mInitVolume = 1.0f;
    mExtPitch = 1.0f;
    mExtPan = 0.0f;
    mExtSurroundPan = 0.0f;
    mExtVolume.InitValue(1.0f);

    mOutputLine = 1;
    mEnableOutputLine = false;

    mMainOutVolume = 1.0f;
    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        mRemoteOutVolumes[i] = 1.0f;
    }

    mAmbientParam.volume = 1.0f;
    mAmbientParam.pitch = 1.0f;
    mAmbientParam.pan = 0.0f;
    mAmbientParam.surroundPan = 0.0f;
    mAmbientParam.fxSend = 0.0f;
    mAmbientParam.lpf = 0.0f;
    mAmbientParam.priority = 0;
}

void BasicSound::StartPrepared() {
    if (!mIsStarted) {
        mIsStarting = true;
    }
}

void BasicSound::Stop(int frames) {
    BasicPlayer& player = GetBasicPlayer();

    if (frames == 0 || !player.IsActive() || !player.IsStarted() ||
        player.IsPause()) {
        Shutdown();
        return;
    }

    int t = frames * mFadeVolume.GetValue();
    mFadeVolume.SetTarget(0.0f, t);

    SetPlayerPriority(PRIORITY_MIN);
    mIsAutoStop = false;
    mIsPause = false;
    mIsPauseFade = false;
    mIsFadeOut = true;
}

void BasicSound::Pause(bool flag, int frames) {
    BasicPlayer& player = GetBasicPlayer();

    if (flag) {
        int t = frames * mPauseFadeVolume.GetValue();
        mIsPauseFade = true;

        if (t <= 0) {
            t = 1;
        }

        mPauseFadeVolume.SetTarget(0.0f, t);
    } else {
        if (mIsPause != flag) {
            player.Pause(false);
        }

        int t = frames * (1.0f - mPauseFadeVolume.GetValue());
        mIsPauseFade = true;

        if (t <= 0) {
            t = 1;
        }

        mPauseFadeVolume.SetTarget(1.0f, t);
    }

    mIsPause = flag;
}

void BasicSound::SetAutoStopCounter(int count) {
    mAutoStopCounter = count;
    mIsAutoStop = count > 0;
}

void BasicSound::FadeIn(int frames) {
    if (mIsFadeOut) {
        return;
    }

    int t = frames * (1.0f - mFadeVolume.GetValue());
    mFadeVolume.SetTarget(1.0f, t);
}

bool BasicSound::IsPause() const {
    return mIsPause;
}

void BasicSound::Update() {
    BasicPlayer& player = GetBasicPlayer();

    if (mIsAutoStop && player.IsActive()) {
        if (mAutoStopCounter == 0) {
            Stop(0);
            return;
        }

        mAutoStopCounter--;
    }

    bool startPlayer = false;
    if (!mIsStarted) {
        if (!mIsStarting) {
            return;
        }

        if (!IsPrepared()) {
            return;
        }

        startPlayer = true;
    }

    if (player.IsStarted() && mUpdateCounter < 0xFFFFFFFF) {
        mUpdateCounter++;
    }

    if (!player.IsActive()) {
        Shutdown();
        return;
    }

    if (player.IsPause()) {
        return;
    }

    if (mIsPauseFade) {
        mPauseFadeVolume.Update();
    } else {
        mFadeVolume.Update();
        mExtVolume.Update();
    }

    if (mArgUpdateCallback != NULL) {
        mArgUpdateCallback->detail_Update(mCallbackArg, this);
    }

    if (mParamUpdateCallback != NULL) {
        mParamUpdateCallback->detail_Update(&mAmbientParam, mId, this,
                                            mCallbackArg, 0xFFFFFFFF);
    }

    f32 volume;
    f32 pan;
    f32 surroundPan;
    f32 pitch;
    f32 mainOutVol;

    volume = 1.0f;
    volume *= GetInitialVolume();
    volume *= mSoundPlayer->GetVolume();
    if (mExtSoundPlayer != NULL) {
        volume *= mExtSoundPlayer->detail_GetVolume();
    }
    volume *= GetMoveVolume();
    volume *= mFadeVolume.GetValue();
    volume *= mPauseFadeVolume.GetValue();
    volume *= GetAmbientParam().volume;

    pan = 0.0f;
    pan += GetPan();
    pan += GetAmbientParam().pan;

    pitch = 1.0f;
    pitch *= GetPitch();

    surroundPan = 0.0f;
    surroundPan += GetSurroundPan();
    surroundPan += GetAmbientParam().surroundPan;

    mainOutVol = 1.0f;
    mainOutVol *= mSoundPlayer->detail_GetMainOutVolume();
    mainOutVol *= GetMainOutVolume();

    int outputLine = 1;
    if (mSoundPlayer->detail_IsEnabledOutputLine()) {
        outputLine = mSoundPlayer->detail_GetOutputLine();
    }
    if (mEnableOutputLine) {
        outputLine = GetOutputLine();
    }

    f32 remoteOutVol[WPAD_MAX_CONTROLLERS];
    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        remoteOutVol[i] = 1.0f;
        remoteOutVol[i] *= mSoundPlayer->detail_GetRemoteOutVolume(i);
        remoteOutVol[i] *= GetRemoteOutVolume(i);
    }

    player.SetVolume(volume);
    player.SetPan(pan);
    player.SetSurroundPan(surroundPan);
    player.SetPitch(pitch);
    player.SetOutputLine(outputLine);
    player.SetMainOutVolume(mainOutVol);

    for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++) {
        player.SetRemoteOutVolume(i, remoteOutVol[i]);
    }

    if (mIsFadeOut && mFadeVolume.IsFinished()) {
        mIsFadeOut = false;
        Shutdown();
        return;
    }

    if (mIsPauseFade && mPauseFadeVolume.IsFinished()) {
        mIsPauseFade = false;

        if (mIsPause) {
            player.Pause(mIsPause);
        }
    }

    if (startPlayer && player.Start()) {
        mIsStarted = true;
        mIsStarting = false;
    }
}

void BasicSound::Shutdown() {
    BasicPlayer& player = GetBasicPlayer();

    if (player.IsActive()) {
        if (mIsFadeOut) {
            player.SetVolume(0.0f);
        }

        player.Stop();
    }

    SetId(0xFFFFFFFF);

    if (IsAttachedGeneralHandle()) {
        DetachGeneralHandle();
    }

    if (IsAttachedTempGeneralHandle()) {
        DetachTempGeneralHandle();
    }

    if (IsAttachedTempSpecialHandle()) {
        DetachTempSpecialHandle();
    }

    if (mPlayerHeap != NULL) {
        mSoundPlayer->detail_FreePlayerHeap(this);
    }

    mSoundPlayer->detail_RemovePriorityList(this);
    mSoundPlayer->detail_RemoveSoundList(this);

    if (mExtSoundPlayer != NULL) {
        mExtSoundPlayer->RemoveSoundList(this);
    }

    if (mArgAllocCallback != NULL) {
        mArgAllocCallback->detail_FreeAmbientArg(mCallbackArg, this);
        mCallbackArg = NULL;
    }

    mIsStarted = false;
    mIsFadeOut = false;
}

void BasicSound::SetPlayerPriority(int prio) {
    mPriority = prio;

    if (mSoundPlayer != NULL) {
        mSoundPlayer->detail_RemovePriorityList(this);
        mSoundPlayer->detail_InsertPriorityList(this);
    }
}

void BasicSound::SetInitialVolume(f32 vol) {
    mInitVolume = ut::Clamp(vol, 0.0f, 1.0f);
}

void BasicSound::SetVolume(f32 vol, int frames) {
    f32 target = ut::Clamp(vol, 0.0f, 1.0f);
    mExtVolume.SetTarget(target, frames);
}

void BasicSound::SetPitch(f32 pitch) {
    mExtPitch = pitch;
}

void BasicSound::SetPan(f32 pan) {
    mExtPan = pan;
}

void BasicSound::SetSurroundPan(f32 pan) {
    mExtSurroundPan = pan;
}

void BasicSound::SetLpfFreq(f32 freq) {
    GetBasicPlayer().SetLpfFreq(freq);
}

void BasicSound::SetOutputLine(int flag) {
    mOutputLine = flag;
    mEnableOutputLine = true;
}

bool BasicSound::IsEnabledOutputLine() const {
    return mEnableOutputLine;
}

int BasicSound::GetOutputLine() const {
    return mOutputLine;
}

void BasicSound::SetMainOutVolume(f32 vol) {
    mMainOutVolume = ut::Clamp(vol, 0.0f, 1.0f);
}

void BasicSound::SetRemoteOutVolume(int remote, f32 vol) {
    mRemoteOutVolumes[remote] = ut::Clamp(vol, 0.0f, 1.0f);
}

void BasicSound::SetFxSend(AuxBus bus, f32 send) {
    GetBasicPlayer().SetFxSend(bus, send);
}

void BasicSound::SetRemoteFilter(int filter) {
    GetBasicPlayer().SetRemoteFilter(filter);
}

void BasicSound::SetPanMode(PanMode mode) {
    GetBasicPlayer().SetPanMode(mode);
}

void BasicSound::SetPanCurve(PanCurve curve) {
    GetBasicPlayer().SetPanCurve(curve);
}

f32 BasicSound::GetInitialVolume() const {
    return mInitVolume;
}

f32 BasicSound::GetPitch() const {
    return mExtPitch;
}

f32 BasicSound::GetPan() const {
    return mExtPan;
}

f32 BasicSound::GetSurroundPan() const {
    return mExtSurroundPan;
}

f32 BasicSound::GetMainOutVolume() const {
    return mMainOutVolume;
}

f32 BasicSound::GetRemoteOutVolume(int remote) const {
    return mRemoteOutVolumes[remote];
}

void BasicSound::SetAmbientParamCallback(
    AmbientParamUpdateCallback* paramUpdate,
    AmbientArgUpdateCallback* argUpdate, AmbientArgAllocaterCallback* argAlloc,
    void* arg) {
    mParamUpdateCallback = paramUpdate;
    mArgUpdateCallback = argUpdate;
    mArgAllocCallback = argAlloc;
    mCallbackArg = arg;
}

bool BasicSound::IsAttachedGeneralHandle() {
    return mGeneralHandle != NULL;
}

bool BasicSound::IsAttachedTempGeneralHandle() {
    return mTempGeneralHandle != NULL;
}

void BasicSound::DetachGeneralHandle() {
    mGeneralHandle->DetachSound();
}

void BasicSound::DetachTempGeneralHandle() {
    mTempGeneralHandle->DetachSound();
}

void BasicSound::SetId(u32 id) {
    mId = id;
    GetBasicPlayer().SetId(id);
}

} // namespace detail
} // namespace snd
} // namespace nw4r
