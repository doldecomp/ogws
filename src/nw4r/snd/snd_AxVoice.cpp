#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <cstring>
#include <nw4r/snd.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace snd {
namespace detail {

AxVoice::AxVoice()
    : mWaveData(NULL),
      mFirstMixUpdate(false),
      mReserveForFree(false),
      mCallback(NULL),
      mCallbackArg(NULL) {}

AxVoice::~AxVoice() {}

void AxVoice::Setup(const void* wave, Format fmt, int rate) {
    ut::AutoInterruptLock lock;

    mWaveData = wave;
    mFormat = fmt;
    mSampleRate = rate;

    std::memset(&mMixPrev, 0, sizeof(MixParam));
    mFirstMixUpdate = true;
}

bool AxVoice::IsPlayFinished() const {
    ut::AutoInterruptLock lock;

    if (mWaveData == NULL) {
        return false;
    }

    u32 dspAddr = GetCurrentPlayingDspAddress();
    const void* buffer = AxManager::GetInstance().GetZeroBufferAddress();
    u32 samples = GetDspAddressBySample(buffer, 0, mFormat);

    u32 addr = samples;

    switch (mFormat) {
    case FORMAT_ADPCM:
        addr += 0x200;
        break;
    case FORMAT_PCM8:
        addr += 0x100;
        break;
    case FORMAT_PCM16:
        addr += 0x80;
        break;
    }

    if (samples <= dspAddr && dspAddr < addr) {
        return true;
    }

    return false;
}

void AxVoice::SetLoopStart(const void* base, u32 samples) {
    ut::AutoInterruptLock lock;

    if (!mVpb.IsAvailable()) {
        return;
    }

    u32 addr = GetDspAddressBySample(base, samples, mFormat);
    mVpb.SetVoiceLoopAddr(addr);
}

void AxVoice::SetLoopEnd(const void* base, u32 samples) {
    ut::AutoInterruptLock lock;

    if (!mVpb.IsAvailable()) {
        return;
    }

    u32 addr = GetDspAddressBySample(base, samples - 1, mFormat);
    mVpb.SetVoiceEndAddr(addr);
}

void AxVoice::SetLoopFlag(bool loop) {
    ut::AutoInterruptLock lock;

    if (!mVpb.IsAvailable()) {
        return;
    }

    mVpb.SetVoiceLoop(loop);
}

void AxVoice::StopAtPoint(const void* base, u32 samples) {
    ut::AutoInterruptLock lock;

    if (!mVpb.IsAvailable()) {
        return;
    }

    const void* buffer = AxManager::GetInstance().GetZeroBufferAddress();
    u32 begin = GetDspAddressBySample(buffer, 0, mFormat);
    u32 end = GetDspAddressBySample(base, samples - 1, mFormat);

    mVpb.SetVoiceLoopAddr(begin);
    mVpb.SetVoiceEndAddr(end);
    mVpb.SetVoiceLoop(false);
}

bool AxVoice::IsDataAddressCoverd(const void* begin, const void* end) const {
    ut::AutoInterruptLock lock;

    if (!mVpb.IsAvailable()) {
        return false;
    }

    return mWaveData != NULL && (begin <= mWaveData && mWaveData <= end);
}

u32 AxVoice::GetCurrentPlayingSample() const {
    ut::AutoInterruptLock lock;

    if (!mVpb.IsAvailable()) {
        return 0;
    }

    if (mWaveData == NULL) {
        return 0;
    }

    if (IsPlayFinished()) {
        u32 end = GetLoopEndDspAddress();
        u32 samples = GetSampleByDspAddress(mWaveData, end, mFormat);
        return samples + 1;
    }

    u32 now = GetCurrentPlayingDspAddress();
    u32 samples = GetSampleByDspAddress(mWaveData, now, mFormat);
    return samples;
}

u32 AxVoice::GetCurrentPlayingDspAddress() const {
    return mVpb.GetCurrentAddress();
}

u32 AxVoice::GetLoopEndDspAddress() const { return mVpb.GetEndAddress(); }

void AxVoice::VoiceCallback(void* arg) {
    ut::AutoInterruptLock lock;

    AXVPB* vpb = static_cast<AXVPB*>(arg);
    AxVoice* self = reinterpret_cast<AxVoice*>(vpb->userContext);

    self->mVpb.Clear();
    AxVoiceManager::GetInstance().ReserveForFreeAxVoice(self);
}

u32 AxVoice::GetDspAddressBySample(const void* base, u32 samples, Format fmt) {
    if (base != NULL) {
        base = OSCachedToPhysical(base);
    }

    u32 addr = 0;

    switch (fmt) {
    case FORMAT_ADPCM:
        addr =
            samples / AX_ADPCM_SAMPLES_PER_FRAME * AX_ADPCM_NIBBLES_PER_FRAME +
            samples % AX_ADPCM_SAMPLES_PER_FRAME +
            reinterpret_cast<u32>(base) * sizeof(u16) + sizeof(u16);
        break;
    case FORMAT_PCM8:
        addr = reinterpret_cast<u32>(base) + samples;
        break;
    case FORMAT_PCM16:
        addr = reinterpret_cast<u32>(base) / sizeof(u16) + samples;
        break;
    }

    return addr;
}

u32 AxVoice::GetSampleByDspAddress(const void* base, u32 addr, Format fmt) {
    if (base != NULL) {
        base = OSCachedToPhysical(base);
    }

    u32 samples = 0;

    switch (fmt) {
    case FORMAT_ADPCM:
        samples = addr - reinterpret_cast<u32>(base) * sizeof(u16);
        samples =
            samples % AX_ADPCM_NIBBLES_PER_FRAME +
            samples / AX_ADPCM_NIBBLES_PER_FRAME * AX_ADPCM_SAMPLES_PER_FRAME -
            sizeof(u16);
        break;
    case FORMAT_PCM8:
        samples = addr - reinterpret_cast<u32>(base);
        break;
    case FORMAT_PCM16:
        samples = addr - reinterpret_cast<u32>(base) / sizeof(u16);
        break;
    }

    return samples;
}

u32 AxVoice::GetSampleByByte(u32 addr, Format fmt) {
    u32 samples = 0;
    u32 frac;

    switch (fmt) {
    case FORMAT_ADPCM:
        samples = addr / AX_ADPCM_FRAME_SIZE * AX_ADPCM_SAMPLES_PER_FRAME;
        frac = addr % AX_ADPCM_FRAME_SIZE;
        if (frac != 0) {
            samples += (frac - 1) * sizeof(u16);
        }
        break;
    case FORMAT_PCM8:
        samples = addr;
        break;
    case FORMAT_PCM16:
        samples = addr / sizeof(u16);
        break;
    }

    return samples;
}

void AxVoice::SetPriority(u32 prio) { mVpb.SetVoicePriority(prio); }

void AxVoice::SetVoiceType(VoiceType type) { mVpb.SetVoiceType(type); }

void AxVoice::EnableRemote(bool enable) { mVpb.SetVoiceRmtOn(enable); }

void AxVoice::ResetDelta() {
    ut::AutoInterruptLock lock;

    if (!mVpb.IsAvailable()) {
        return;
    }

    mVpb.UpdateDelta();

    AXPBMIX mix;

    mix.vL = mMixPrev.vL;
    mix.vDeltaL = 0;

    mix.vR = mMixPrev.vR;
    mix.vDeltaR = 0;

    mix.vAuxAL = mMixPrev.vAuxAL;
    mix.vDeltaAuxAL = 0;

    mix.vAuxAR = mMixPrev.vAuxAR;
    mix.vDeltaAuxAR = 0;

    mix.vAuxBL = mMixPrev.vAuxBL;
    mix.vDeltaAuxBL = 0;

    mix.vAuxBR = mMixPrev.vAuxBR;
    mix.vDeltaAuxBR = 0;

    mix.vAuxCL = mMixPrev.vAuxCL;
    mix.vDeltaAuxCL = 0;

    mix.vAuxCR = mMixPrev.vAuxCR;
    mix.vDeltaAuxCR = 0;

    mix.vS = mMixPrev.vS;
    mix.vDeltaS = 0;

    mix.vAuxAS = mMixPrev.vAuxAS;
    mix.vDeltaAuxAS = 0;

    mix.vAuxBS = mMixPrev.vAuxBS;
    mix.vDeltaAuxBS = 0;

    mix.vAuxCS = mMixPrev.vAuxCS;
    mix.vDeltaAuxCS = 0;

    mVpb.SetVoiceMix(mix, true);
}

void AxVoice::SetAddr(bool loop, const void* wave, u32 offset, u32 loopStart,
                      u32 loopEnd) {
    ut::AutoInterruptLock lock;

    u32 startAddr;
    u32 endAddr;
    u32 loopAddr;
    const void* buffer;

    if (!mVpb.IsAvailable()) {
        return;
    }

    if (offset > loopEnd) {
        buffer = AxManager::GetInstance().GetZeroBufferAddress();
        loop = false;

        startAddr = GetDspAddressBySample(buffer, 0, mFormat);
        loopAddr = GetDspAddressBySample(buffer, 0, mFormat);
        endAddr = GetDspAddressBySample(buffer, 1, mFormat);
    } else {
        if (loop) {
            loopAddr = GetDspAddressBySample(wave, loopStart, mFormat);
        } else {
            buffer = AxManager::GetInstance().GetZeroBufferAddress();
            loopAddr = GetDspAddressBySample(buffer, 0, mFormat);
        }

        startAddr = GetDspAddressBySample(wave, offset, mFormat);
        endAddr = GetDspAddressBySample(wave, loopEnd - 1, mFormat);
    }

    AXPBADDR addr;

    addr.loopFlag = loop;
    addr.format = mFormat;

    addr.loopAddressHi = loopAddr >> 16 & 0xFFFF;
    addr.loopAddressLo = loopAddr & 0xFFFF;

    addr.endAddressHi = endAddr >> 16 & 0xFFFF;
    addr.endAddressLo = endAddr & 0xFFFF;

    addr.currentAddressHi = startAddr >> 16 & 0xFFFF;
    addr.currentAddressLo = startAddr & 0xFFFF;

    mVpb.SetVoiceAddr(addr);
}

void AxVoice::SetSrcType(SrcType type, f32 pitch) {
    ut::AutoInterruptLock lock;

    if (!mVpb.IsAvailable()) {
        return;
    }

    if (type == SRC_4TAP_AUTO) {
        f32 ratio = GetDspRatio(pitch);

        if (ratio > 4.0f / 3.0f) {
            type = SRC_4TAP_8K;
        } else if (ratio > 1.0f) {
            type = SRC_4TAP_12K;
        } else {
            type = SRC_4TAP_16K;
        }
    }

    mVpb.SetVoiceSrcType(type);
}

void AxVoice::SetAdpcm(const AdpcmParam* param) {
    ut::AutoInterruptLock lock;
    AXPBADPCM adpcm;

    if (!mVpb.IsAvailable()) {
        return;
    }

    switch (mFormat) {
    case FORMAT_ADPCM:
        std::memcpy(adpcm.a, param->coef, sizeof(adpcm.a));
        adpcm.gain = param->gain;
        adpcm.pred_scale = param->pred_scale;
        adpcm.yn1 = param->yn1;
        adpcm.yn2 = param->yn2;
        break;
    case FORMAT_PCM16:
        std::memset(adpcm.a, 0, sizeof(adpcm.a));
        adpcm.gain = 0x800;
        adpcm.pred_scale = 0;
        adpcm.yn1 = 0;
        adpcm.yn2 = 0;
        break;
    case FORMAT_PCM8:
        std::memset(adpcm.a, 0, sizeof(adpcm.a));
        adpcm.gain = 0x100;
        adpcm.pred_scale = 0;
        adpcm.yn1 = 0;
        adpcm.yn2 = 0;
        break;
    }

    mVpb.SetVoiceAdpcm(adpcm);
}

void AxVoice::SetAdpcmLoop(const AdpcmLoopParam* param) {
    ut::AutoInterruptLock lock;
    AXPBADPCMLOOP loop;

    if (!mVpb.IsAvailable()) {
        return;
    }

    if (mFormat == FORMAT_ADPCM) {
        loop.loop_pred_scale = param->loop_pred_scale;
        loop.loop_yn1 = param->loop_yn1;
        loop.loop_yn2 = param->loop_yn2;
    } else {
        loop.loop_pred_scale = 0;
        loop.loop_yn1 = 0;
        loop.loop_yn2 = 0;
    }

    mVpb.SetVoiceAdpcmLoop(loop);
}

bool AxVoice::SetMix(const MixParam& param) {
    ut::AutoInterruptLock lock;

    if (!mVpb.IsAvailable()) {
        return false;
    }

    if (mFirstMixUpdate || !IsRun()) {
        mMixPrev = param;
        mFirstMixUpdate = false;
    }

    bool needUpdate = false;

    if (mMixPrev.vL != param.vL) {
        needUpdate = true;
    }

    if (mMixPrev.vR != param.vR) {
        needUpdate = true;
    }

    if (mMixPrev.vS != param.vS) {
        needUpdate = true;
    }

    if (mMixPrev.vAuxAL != param.vAuxAL) {
        needUpdate = true;
    }

    if (mMixPrev.vAuxAR != param.vAuxAR) {
        needUpdate = true;
    }

    if (mMixPrev.vAuxAS != param.vAuxAS) {
        needUpdate = true;
    }

    if (mMixPrev.vAuxBL != param.vAuxBL) {
        needUpdate = true;
    }

    if (mMixPrev.vAuxBR != param.vAuxBR) {
        needUpdate = true;
    }

    if (mMixPrev.vAuxBS != param.vAuxBS) {
        needUpdate = true;
    }

    if (mMixPrev.vAuxCL != param.vAuxCL) {
        needUpdate = true;
    }

    if (mMixPrev.vAuxCR != param.vAuxCR) {
        needUpdate = true;
    }

    if (mMixPrev.vAuxCS != param.vAuxCS) {
        needUpdate = true;
    }

    AXPBMIX mix;

    mix.vL = mMixPrev.vL;
    mix.vR = mMixPrev.vR;
    mix.vS = mMixPrev.vS;

    mix.vAuxAL = mMixPrev.vAuxAL;
    mix.vAuxAR = mMixPrev.vAuxAR;
    mix.vAuxAS = mMixPrev.vAuxAS;

    mix.vAuxBL = mMixPrev.vAuxBL;
    mix.vAuxBR = mMixPrev.vAuxBR;
    mix.vAuxBS = mMixPrev.vAuxBS;

    mix.vAuxCL = mMixPrev.vAuxCL;
    mix.vAuxCR = mMixPrev.vAuxCR;
    mix.vAuxCS = mMixPrev.vAuxCS;

    int vDeltaL = CalcAxvpbDelta(mMixPrev.vL, param.vL);
    int vDeltaR = CalcAxvpbDelta(mMixPrev.vR, param.vR);
    int vDeltaS = CalcAxvpbDelta(mMixPrev.vS, param.vS);

    int vDeltaAuxAL = CalcAxvpbDelta(mMixPrev.vAuxAL, param.vAuxAL);
    int vDeltaAuxAR = CalcAxvpbDelta(mMixPrev.vAuxAR, param.vAuxAR);
    int vDeltaAuxAS = CalcAxvpbDelta(mMixPrev.vAuxAS, param.vAuxAS);

    int vDeltaAuxBL = CalcAxvpbDelta(mMixPrev.vAuxBL, param.vAuxBL);
    int vDeltaAuxBR = CalcAxvpbDelta(mMixPrev.vAuxBR, param.vAuxBR);
    int vDeltaAuxBS = CalcAxvpbDelta(mMixPrev.vAuxBS, param.vAuxBS);

    int vDeltaAuxCL = CalcAxvpbDelta(mMixPrev.vAuxCL, param.vAuxCL);
    int vDeltaAuxCR = CalcAxvpbDelta(mMixPrev.vAuxCR, param.vAuxCR);
    int vDeltaAuxCS = CalcAxvpbDelta(mMixPrev.vAuxCS, param.vAuxCS);

    mix.vDeltaL = vDeltaL;
    mix.vDeltaR = vDeltaR;
    mix.vDeltaS = vDeltaS;

    mix.vDeltaAuxAL = vDeltaAuxAL;
    mix.vDeltaAuxAR = vDeltaAuxAR;
    mix.vDeltaAuxAS = vDeltaAuxAS;

    mix.vDeltaAuxBL = vDeltaAuxBL;
    mix.vDeltaAuxBR = vDeltaAuxBR;
    mix.vDeltaAuxBS = vDeltaAuxBS;

    mix.vDeltaAuxCL = vDeltaAuxCL;
    mix.vDeltaAuxCR = vDeltaAuxCR;
    mix.vDeltaAuxCS = vDeltaAuxCS;

    mVpb.SetVoiceMix(mix, false);

    if (param.vL == 0 || vDeltaL == 0) {
        mMixPrev.vL = param.vL;
    } else {
        mMixPrev.vL += vDeltaL * AX_SAMPLES_PER_FRAME;
    }

    if (param.vR == 0 || vDeltaR == 0) {
        mMixPrev.vR = param.vR;
    } else {
        mMixPrev.vR += vDeltaR * AX_SAMPLES_PER_FRAME;
    }

    if (param.vS == 0 || vDeltaS == 0) {
        mMixPrev.vS = param.vS;
    } else {
        mMixPrev.vS += vDeltaS * AX_SAMPLES_PER_FRAME;
    }

    if (param.vAuxAL == 0 || vDeltaAuxAL == 0) {
        mMixPrev.vAuxAL = param.vAuxAL;
    } else {
        mMixPrev.vAuxAL += vDeltaAuxAL * AX_SAMPLES_PER_FRAME;
    }

    if (param.vAuxAR == 0 || vDeltaAuxAR == 0) {
        mMixPrev.vAuxAR = param.vAuxAR;
    } else {
        mMixPrev.vAuxAR += vDeltaAuxAR * AX_SAMPLES_PER_FRAME;
    }

    if (param.vAuxAS == 0 || vDeltaAuxAS == 0) {
        mMixPrev.vAuxAS = param.vAuxAS;
    } else {
        mMixPrev.vAuxAS += vDeltaAuxAS * AX_SAMPLES_PER_FRAME;
    }

    if (param.vAuxBL == 0 || vDeltaAuxBL == 0) {
        mMixPrev.vAuxBL = param.vAuxBL;
    } else {
        mMixPrev.vAuxBL += vDeltaAuxBL * AX_SAMPLES_PER_FRAME;
    }

    if (param.vAuxBR == 0 || vDeltaAuxBR == 0) {
        mMixPrev.vAuxBR = param.vAuxBR;
    } else {
        mMixPrev.vAuxBR += vDeltaAuxBR * AX_SAMPLES_PER_FRAME;
    }

    if (param.vAuxBS == 0 || vDeltaAuxBS == 0) {
        mMixPrev.vAuxBS = param.vAuxBS;
    } else {
        mMixPrev.vAuxBS += vDeltaAuxBS * AX_SAMPLES_PER_FRAME;
    }

    if (param.vAuxCL == 0 || vDeltaAuxCL == 0) {
        mMixPrev.vAuxCL = param.vAuxCL;
    } else {
        mMixPrev.vAuxCL += vDeltaAuxCL * AX_SAMPLES_PER_FRAME;
    }

    if (param.vAuxCR == 0 || vDeltaAuxCR == 0) {
        mMixPrev.vAuxCR = param.vAuxCR;
    } else {
        mMixPrev.vAuxCR += vDeltaAuxCR * AX_SAMPLES_PER_FRAME;
    }

    if (param.vAuxCS == 0 || vDeltaAuxCS == 0) {
        mMixPrev.vAuxCS = param.vAuxCS;
    } else {
        mMixPrev.vAuxCS += vDeltaAuxCS * AX_SAMPLES_PER_FRAME;
    }

    return needUpdate;
}

void AxVoice::SetRmtMix(const RemoteMixParam& param) {
    AXPBRMTMIX mix;

    mix.vMain0 = param.vMain0;
    mix.vDeltaMain0 = 0;

    mix.vAux0 = param.vAux0;
    mix.vDeltaAux0 = 0;

    mix.vMain1 = param.vMain1;
    mix.vDeltaMain1 = 0;

    mix.vAux1 = param.vAux1;
    mix.vDeltaAux1 = 0;

    mix.vMain2 = param.vMain2;
    mix.vDeltaMain2 = 0;

    mix.vAux2 = param.vAux2;
    mix.vDeltaAux2 = 0;

    mix.vMain3 = param.vMain3;
    mix.vDeltaMain3 = 0;

    mix.vAux3 = param.vAux3;
    mix.vDeltaAux3 = 0;

    mVpb.SetVoiceRmtMix(mix);
}

void AxVoice::SetSrc(f32 ratio, bool initial) {
    ut::AutoInterruptLock lock;

    if (!mVpb.IsAvailable()) {
        return;
    }

    if (initial) {
        ratio = GetDspRatio(ratio);
        u32 ratioBits = 65536 * ratio;

        AXPBSRC src;

        src.ratioHi = ratioBits >> 16 & 0xFFFF;
        src.ratioLo = ratioBits & 0xFFFF;

        src.currentAddressFrac = 0;

        src.last_samples[0] = 0;
        src.last_samples[1] = 0;
        src.last_samples[2] = 0;
        src.last_samples[3] = 0;

        mVpb.SetVoiceSrc(src);
    } else {
        ratio = GetDspRatio(ratio);
        mVpb.SetVoiceSrcRatio(ratio);
    }
}

void AxVoice::SetVe(f32 volume, f32 initVolume) {
    ut::AutoInterruptLock lock;

    if (!mVpb.IsAvailable()) {
        return;
    }

    mVpb.SetVoiceVe(32767 * volume, 32767 * initVolume);
}

void AxVoice::SetLpf(u16 freq) {
    ut::AutoInterruptLock lock;

    if (!mVpb.IsAvailable()) {
        return;
    }

    if (freq >= 16000) {
        AXPBLPF lpf;
        lpf.on = 0;
        lpf.yn1 = 0;
        mVpb.SetVoiceLpf(lpf);
    } else if (mVpb.IsLpfEnable()) {
        u16 a0, b0;
        AXGetLpfCoefs(freq, &a0, &b0);
        mVpb.SetVoiceLpfCoefs(a0, b0);
    } else {
        AXPBLPF lpf;
        lpf.on = AX_PB_LPF_ON;
        lpf.yn1 = 0;
        AXGetLpfCoefs(freq, &lpf.a0, &lpf.b0);
        mVpb.SetVoiceLpf(lpf);
    }
}

void AxVoice::SetRemoteFilter(u8 filter) {
    ut::AutoInterruptLock lock;

    if (!mVpb.IsAvailable()) {
        return;
    }

    if (filter == 0) {
        AXPBRMTIIR iir;
        iir.lpf.on = 0;

        mVpb.SetVoiceRmtIIR(iir);
    } else if (mVpb.IsRmtIirEnable()) {
        u16 b0, b1, b2, a1, a2;
        Util::GetRemoteFilterCoefs(filter, &b0, &b1, &b2, &a1, &a2);

        mVpb.SetVoiceRmtIIRCoefs(AX_PB_BIQUAD_ON, b0, b1, b2, a1, a2);
    } else {
        AXPBRMTIIR iir;
        iir.biquad.on = AX_PB_BIQUAD_ON;
        iir.biquad.xn1 = 0;
        iir.biquad.xn2 = 0;
        iir.biquad.yn1 = 0;
        iir.biquad.yn2 = 0;

        Util::GetRemoteFilterCoefs(filter, &iir.biquad.b0, &iir.biquad.b1,
                                   &iir.biquad.b2, &iir.biquad.a1,
                                   &iir.biquad.a2);
        mVpb.SetVoiceRmtIIR(iir);
    }
}

void AxVoice::CalcOffsetAdpcmParam(u16* outPredScale, u16* outYn1, u16* outYn2,
                                   u32 offset, const void* data,
                                   const AdpcmParam& param) {
    AXPBADPCM adpcm;
    std::memcpy(adpcm.a, param.coef, sizeof(adpcm.a));
    adpcm.gain = param.gain;
    adpcm.pred_scale = param.pred_scale;
    adpcm.yn1 = param.yn1;
    adpcm.yn2 = param.yn2;

    u32 addr = GetDspAddressBySample(data, 0, FORMAT_ADPCM);
    u32 end = GetDspAddressBySample(data, offset, FORMAT_ADPCM);

    while (addr < end) {
        if (addr % AX_ADPCM_NIBBLES_PER_FRAME == 0) {
            adpcm.pred_scale =
                *static_cast<u8*>(OSPhysicalToCached(addr / sizeof(u16)));

            addr += sizeof(u16);
        }

        u8 byte = *static_cast<u8*>(OSPhysicalToCached(addr / sizeof(u16)));

        u8 nibble;
        if (addr % sizeof(u16) != 0) {
            nibble = byte & 0x0F;
        } else {
            nibble = byte >> 4;
        }

        DecodeDspAdpcm(&adpcm, nibble);
        addr++;
    }

    *outPredScale = adpcm.pred_scale;
    *outYn1 = adpcm.yn1;
    *outYn2 = adpcm.yn2;
}

void AxVoiceParamBlock::Sync() {
    ut::AutoInterruptLock lock;

    if (!IsAvailable()) {
        return;
    }

    mVpb->pb.ve.currentVolume = mVePrev.currentVolume;

    s16 deltaIn = (mVolume - mVePrev.currentVolume) / AX_SAMPLES_PER_FRAME;
    s16 deltaOut = (deltaIn + (deltaIn > 0 ? 1 : 0) != 0) ? 1 : -1;

    int predIn = mVePrev.currentVolume + (deltaIn * AX_SAMPLES_PER_FRAME);
    int predOut = mVePrev.currentVolume + (deltaOut * AX_SAMPLES_PER_FRAME);

    if (ut::Abs(mVolume - predIn) < ut::Abs(mVolume - predOut)) {
        mVpb->pb.ve.currentDelta = deltaIn;
    } else {
        mVpb->pb.ve.currentDelta = deltaOut;
    }

    if (mVpb->pb.ve.currentDelta == 0 && mVePrev.currentDelta == 0) {
        mVpb->pb.ve.currentVolume = mVolume;
    }

    int nextVolume = mVePrev.currentVolume +
                     (mVpb->pb.ve.currentDelta * AX_SAMPLES_PER_FRAME);

    if (nextVolume < 0) {
        mVpb->pb.ve.currentDelta =
            -mVePrev.currentVolume / AX_SAMPLES_PER_FRAME;
    } else if (nextVolume > 32767) {
        mVpb->pb.ve.currentDelta =
            (32767 - mVePrev.currentVolume) / AX_SAMPLES_PER_FRAME;
    }

    mSync &= ~AX_PBSYNC_VE_DELTA;
    mSync |= AX_PBSYNC_VE;

    mVePrev.currentVolume = mVpb->pb.ve.currentVolume;
    mVePrev.currentDelta = mVpb->pb.ve.currentDelta;

    mVpb->sync |= mSync;
    mSync = 0;
}

bool AxVoiceParamBlock::IsRmtIirEnable() const {
    return IsAvailable() && mVpb->pb.rmtIIR.biquad.on == AX_PB_BIQUAD_ON;
}

AxVoiceParamBlock::AxVoiceParamBlock()
    : mVpb(NULL), mSync(0), mVePrev(), mFirstVeUpdate(false), mVolume(32768) {
    mVePrev.currentVolume = 32768;
    mVePrev.currentDelta = 0;
}

void AxVoiceParamBlock::Set(AXVPB* vpb) {
    mVpb = vpb;
    mSync = 0;
    mFirstVeUpdate = true;
    mVolume = 32768;
    mVePrev.currentVolume = 32768;
    mVePrev.currentDelta = 0;
}

void AxVoiceParamBlock::Clear() {
    mVpb = NULL;
    mSync = 0;
}

void AxVoiceParamBlock::SetVoiceType(u16 type) {
    ut::AutoInterruptLock lock;

    if (!IsAvailable()) {
        return;
    }

    mVpb->pb.type = type;
    mSync |= AX_PBSYNC_TYPE;
}

void AxVoiceParamBlock::SetVoiceVe(u16 volume, u16 initVolume) {
    ut::AutoInterruptLock lock;

    if (!IsAvailable()) {
        return;
    }

    if (mFirstVeUpdate) {
        mVePrev.currentVolume = initVolume;
        mFirstVeUpdate = false;
    }

    mVolume = volume;
}

void AxVoiceParamBlock::SetVoiceMix(const AXPBMIX& mix, bool syncNow) {
    ut::AutoInterruptLock lock;

    if (!IsAvailable()) {
        return;
    }

    const u16* src = reinterpret_cast<const u16*>(&mix);
    u16* dst = reinterpret_cast<u16*>(&mVpb->pb.mix);

    u32 ctrl = 0;

    // vL
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_L;
    }
    // vDeltaL
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_DELTA | AX_MIXER_CTRL_L;
    }
    // vR
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_R;
    }
    // vDeltaR
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_DELTA | AX_MIXER_CTRL_R;
    }

    // vAuxAL
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_AL;
    }
    // vDeltaAuxAL
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_DELTA_A | AX_MIXER_CTRL_AL;
    }
    // vAuxAR
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_AR;
    }
    // vDeltaAuxAR
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_DELTA_A | AX_MIXER_CTRL_AR;
    }

    // vAuxBL
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_BL;
    }
    // vDeltaAuxBL
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_DELTA_B | AX_MIXER_CTRL_BL;
    }
    // vAuxBR
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_BR;
    }
    // vDeltaAuxBR
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_DELTA_B | AX_MIXER_CTRL_BR;
    }

    // vAuxCL
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_CL;
    }
    // vDeltaAuxCL
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_DELTA_C | AX_MIXER_CTRL_CL;
    }
    // vAuxCR
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_CR;
    }
    // vDeltaAuxCR
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_DELTA_C | AX_MIXER_CTRL_CR;
    }

    // vS
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_S;
    }
    // vDeltaS
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_DELTA_S | AX_MIXER_CTRL_S;
    }

    // vAuxAS
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_AS;
    }
    // vDeltaAuxAS
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_DELTA_AS | AX_MIXER_CTRL_AS;
    }

    // vAuxBS
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_BS;
    }
    // vDeltaAuxBS
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_DELTA_BS | AX_MIXER_CTRL_BS;
    }

    // vAuxCS
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_CS;
    }
    // vDeltaAuxCS
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_DELTA_CS | AX_MIXER_CTRL_CS;
    }

    mVpb->pb.mixerCtrl = ctrl;

    if (syncNow) {
        mVpb->sync |= AX_PBSYNC_MIX | AX_PBSYNC_MIXER_CTRL;
    } else {
        mSync |= AX_PBSYNC_MIX | AX_PBSYNC_MIXER_CTRL;
    }
}

void AxVoiceParamBlock::SetVoiceLoop(u16 loop) {
    ut::AutoInterruptLock lock;

    if (!IsAvailable()) {
        return;
    }

    mVpb->pb.addr.loopFlag = loop;

    if (!(mVpb->sync & AX_PBSYNC_ADDR)) {
        mVpb->sync |= AX_PBSYNC_LOOP_FLAG;
    }
}

void AxVoiceParamBlock::SetVoiceLoopAddr(u32 addr) {
    ut::AutoInterruptLock lock;

    if (!IsAvailable()) {
        return;
    }

    mVpb->pb.addr.loopAddressHi = addr >> 16 & 0xFFFF;
    mVpb->pb.addr.loopAddressLo = addr & 0xFFFF;

    if (!(mVpb->sync & AX_PBSYNC_ADDR)) {
        mVpb->sync |= AX_PBSYNC_LOOP_ADDR;
    }
}

void AxVoiceParamBlock::SetVoiceEndAddr(u32 addr) {
    ut::AutoInterruptLock lock;

    if (!IsAvailable()) {
        return;
    }

    mVpb->pb.addr.endAddressHi = addr >> 16 & 0xFFFF;
    mVpb->pb.addr.endAddressLo = addr & 0xFFFF;

    if (!(mVpb->sync & AX_PBSYNC_ADDR)) {
        mVpb->sync |= AX_PBSYNC_END_ADDR;
    }
}

void AxVoiceParamBlock::SetVoiceAdpcm(const AXPBADPCM& adpcm) {
    ut::AutoInterruptLock lock;

    if (!IsAvailable()) {
        return;
    }

    std::memcpy(&mVpb->pb.adpcm, &adpcm, sizeof(AXPBADPCM));
    mSync |= AX_PBSYNC_ADPCM;
}

void AxVoiceParamBlock::SetVoiceSrcType(u32 type) {
    ut::AutoInterruptLock lock;

    if (!IsAvailable()) {
        return;
    }

    switch (type) {
    case AxVoice::SRC_NONE:
        mVpb->pb.srcSelect = 2;
        break;
    case AxVoice::SRC_LINEAR:
        mVpb->pb.srcSelect = 1;
        break;
    case AxVoice::SRC_4TAP_8K:
        mVpb->pb.srcSelect = 0;
        mVpb->pb.coefSelect = 0;
        break;
    case AxVoice::SRC_4TAP_12K:
        mVpb->pb.srcSelect = 0;
        mVpb->pb.coefSelect = 1;
        break;
    case AxVoice::SRC_4TAP_16K:
        mVpb->pb.srcSelect = 0;
        mVpb->pb.coefSelect = 2;
        break;
    }

    mSync |= AX_PBSYNC_SELECT;
}

void AxVoiceParamBlock::SetVoiceSrc(const AXPBSRC& src) {
    ut::AutoInterruptLock lock;

    if (!IsAvailable()) {
        return;
    }

    std::memcpy(&mVpb->pb.src, &src, sizeof(AXPBSRC));
    mSync &= ~AX_PBSYNC_SRC_RATIO;
    mSync |= AX_PBSYNC_SRC;
}

void AxVoiceParamBlock::SetVoiceSrcRatio(f32 ratio) {
    ut::AutoInterruptLock lock;

    if (!IsAvailable()) {
        return;
    }

    u32 ratioU32 = 65536 * ratio;
    mVpb->pb.src.ratioHi = ratioU32 >> 16 & 0xFFFF;
    mVpb->pb.src.ratioLo = ratioU32 & 0xFFFF;

    if (!(mSync & AX_PBSYNC_SRC)) {
        mSync |= AX_PBSYNC_SRC_RATIO;
    }
}

void AxVoiceParamBlock::SetVoiceAdpcmLoop(const AXPBADPCMLOOP& loop) {
    ut::AutoInterruptLock lock;

    if (!IsAvailable()) {
        return;
    }

    std::memcpy(&mVpb->pb.adpcmLoop, &loop, sizeof(AXPBADPCMLOOP));
    mSync |= AX_PBSYNC_ADPCM_LOOP;
}

void AxVoiceParamBlock::SetVoiceLpf(const AXPBLPF& lpf) {
    ut::AutoInterruptLock lock;

    if (!IsAvailable()) {
        return;
    }

    std::memcpy(&mVpb->pb.lpf, &lpf, sizeof(AXPBLPF));
    mSync |= AX_PBSYNC_LPF;
}

void AxVoiceParamBlock::SetVoiceLpfCoefs(u16 a0, u16 b0) {
    ut::AutoInterruptLock lock;

    if (!IsAvailable()) {
        return;
    }

    mVpb->pb.lpf.a0 = a0;
    mVpb->pb.lpf.b0 = b0;
    mSync |= AX_PBSYNC_LPF_COEFS;
}

void AxVoiceParamBlock::SetVoiceRmtOn(u16 on) {
    ut::AutoInterruptLock lock;

    if (!IsAvailable()) {
        return;
    }

    mVpb->pb.remote = on;
    mSync |= AX_PBSYNC_REMOTE;
}

void AxVoiceParamBlock::SetVoiceRmtMix(const AXPBRMTMIX& mix) {
    ut::AutoInterruptLock lock;

    if (!IsAvailable()) {
        return;
    }

    u16* dst = reinterpret_cast<u16*>(&mVpb->pb.rmtMix);
    const u16* src = reinterpret_cast<const u16*>(&mix);

    u16 ctrl = 0;

    // vMain0
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_RMT_M0;
    }
    // vDeltaMain0
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_RMT_DELTA_M0;
    }
    // vAux0
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_RMT_A0;
    }
    // vDeltaAux0
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_RMT_DELTA_A0;
    }

    // vMain1
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_RMT_M1;
    }
    // vDeltaMain1
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_RMT_DELTA_M1;
    }
    // vAux1
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_RMT_A1;
    }
    // vDeltaAux1
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_RMT_DELTA_A1;
    }

    // vMain2
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_RMT_M2;
    }
    // vDeltaMain2
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_RMT_DELTA_M2;
    }
    // vAux2
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_RMT_A2;
    }
    // vDeltaAux2
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_RMT_DELTA_A2;
    }

    // vMain3
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_RMT_M3;
    }
    // vDeltaMain3
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_RMT_DELTA_M3;
    }
    // vAux3
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_RMT_A3;
    }
    // vDeltaAux3
    if ((*dst++ = *src++) != 0) {
        ctrl |= AX_MIXER_CTRL_RMT_DELTA_A3;
    }

    mVpb->pb.rmtMixerCtrl = ctrl;
    mSync |= AX_PBSYNC_RMT_MIXER_CTRL | AX_PBSYNC_RMTMIX;
}

void AxVoiceParamBlock::SetVoiceRmtIIR(const AXPBRMTIIR& iir) {
    ut::AutoInterruptLock lock;

    if (!IsAvailable()) {
        return;
    }

    std::memcpy(&mVpb->pb.rmtIIR, &iir, sizeof(AXPBRMTIIR));
    mSync |= AX_PBSYNC_RMTIIR;
}

void AxVoiceParamBlock::SetVoiceRmtIIRCoefs(u16 type, ...) {
    ut::AutoInterruptLock lock;

    int i;
    int argc;

    if (!IsAvailable()) {
        return;
    }

    if (type == AX_PB_LPF_ON) {
        argc = 2;
    } else if (type == AX_PB_BIQUAD_ON) {
        argc = 5;
    } else {
        return;
    }

    std::va_list argv;
    u16 coefs[5];

    va_start(argv, type);
    for (i = 0; i < argc; i++) {
        coefs[i] = va_arg(argv, s32);
    }
    va_end(argv);

    if (type == AX_PB_LPF_ON) {
        mVpb->pb.rmtIIR.lpf.a0 = coefs[0];
        mVpb->pb.rmtIIR.lpf.b0 = coefs[1];
        mSync |= AX_PBSYNC_RMTIIR_LPF_COEFS;
    } else {
        mVpb->pb.rmtIIR.biquad.b0 = coefs[0];
        mVpb->pb.rmtIIR.biquad.b1 = coefs[1];
        mVpb->pb.rmtIIR.biquad.b2 = coefs[2];
        mVpb->pb.rmtIIR.biquad.a1 = coefs[3];
        mVpb->pb.rmtIIR.biquad.a2 = coefs[4];
        mSync |= AX_PBSYNC_RMTIIR_BIQUAD_COEFS;
    }
}

void AxVoiceParamBlock::UpdateDelta() {
    ut::AutoInterruptLock lock;

    if (!IsAvailable()) {
        return;
    }

    mVePrev.currentVolume += mVpb->pb.ve.currentDelta * AX_SAMPLES_PER_FRAME;

    mVpb->pb.ve.currentVolume = mVePrev.currentVolume;
    mVpb->pb.ve.currentDelta = 0;

    mVpb->sync |= AX_PBSYNC_VE;
}

} // namespace detail
} // namespace snd
} // namespace nw4r
