#ifndef EGG_AUDIO_AUDIO_FX_MGR_H
#define EGG_AUDIO_AUDIO_FX_MGR_H
#include <egg/types_egg.h>

#include <nw4r/snd.h>

namespace EGG {

// Forward declarations
class ExpHeap;

/******************************************************************************
 *
 * AudioFx
 *
 ******************************************************************************/
class AudioFx {
public:
    enum FxType {
        TYPE_AXFX_NONE,
        TYPE_AXFX_REVERBHI,
        TYPE_AXFX_REVERBHI_DPL2,
        TYPE_AXFX_REVERBSTD,
        TYPE_AXFX_CHORUS,
        TYPE_AXFX_DELAY,

        TYPE_AXFX_MAX
    };

public:
    AudioFx();
    ~AudioFx();

    void init(nw4r::snd::AuxBus bus, void* pHeapBuffer, u32 heapSize);
    bool create(u32 fxType, const void* pParam);
    void destroy();

private:
    // clang-format off
    bool createFxReverbHi(const nw4r::snd::FxReverbHi::ReverbHiParam* pParam);
    bool createFxReverbHiDpl2(const nw4r::snd::FxReverbHiDpl2::ReverbHiDpl2Param* pParam);
    bool createFxChorus(const nw4r::snd::FxChorus::ChorusParam* pParam);
    bool createFxDelay(const nw4r::snd::FxDelay::DelayParam* pParam);
    // clang-format on

private:
    nw4r::snd::FxBase* mFxBase; // at 0x0
    nw4r::snd::AuxBus mAuxBus;  // at 0x4
    const void* mParam;         // at 0x8
    FxType mType;               // at 0xC
    ExpHeap* mHeap;             // at 0x10
    u8* mWorkBuffer;            // at 0x14
};

/******************************************************************************
 *
 * AudioFxMgr
 *
 ******************************************************************************/
class AudioFxMgr {
public:
    struct AudioFxMgrArg {
        u32 heapSize[nw4r::snd::AUX_BUS_NUM]; // at 0x0
    };

public:
    AudioFxMgr();
    ~AudioFxMgr();

    bool initializeFx(nw4r::snd::SoundHeap* pHeap, AudioFxMgrArg* pArg);

    bool setFxReverbHi(nw4r::snd::AuxBus bus,
                       const nw4r::snd::FxReverbHi::ReverbHiParam* pParam);

    bool setFxReverbHiDpl2(
        nw4r::snd::AuxBus bus,
        const nw4r::snd::FxReverbHiDpl2::ReverbHiDpl2Param* pParam);

    bool setFxChorus(nw4r::snd::AuxBus bus,
                     const nw4r::snd::FxChorus::ChorusParam* pParam);

    bool setFxDelay(nw4r::snd::AuxBus bus,
                    const nw4r::snd::FxDelay::DelayParam* pParam);

    void clearFx(nw4r::snd::AuxBus bus);

    // clang-format off
    static const nw4r::snd::FxReverbHi::ReverbHiParam* getDefaultFxReverbHi();
    static const nw4r::snd::FxReverbHiDpl2::ReverbHiDpl2Param* getDefaultFxReverbHiDpl2();
    static const nw4r::snd::FxChorus::ChorusParam* getDefaultFxChorus();
    static const nw4r::snd::FxDelay::DelayParam* getDefaultFxDelay();
    // clang-format on

private:
    AudioFx mAudioFx[nw4r::snd::AUX_BUS_NUM]; // at 0x0

    // clang-format off
    static const nw4r::snd::FxReverbHi::ReverbHiParam sDefaultFxReverbHi;
    static const nw4r::snd::FxReverbHiDpl2::ReverbHiDpl2Param sDefaultFxReverbHiDpl2;
    static const nw4r::snd::FxChorus::ChorusParam sDefaultFxChorus;
    static const nw4r::snd::FxDelay::DelayParam sDefaultFxDelay;
    // clang-format on
};

} // namespace EGG

#endif
