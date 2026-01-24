#ifndef RP_AUDIO_SND_AUDIO_MGR_H
#define RP_AUDIO_SND_AUDIO_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

#include <egg/audio.h>
#include <egg/core.h>

#include <nw4r/snd.h>

//! @addtogroup rp_audio
//! @{

/**
 * @brief RP sound manager (BGM, SFX, etc.)
 */
class RPSndAudioMgr : public EGG::ExpAudioMgr {
    RP_SINGLETON_DECL_EX(RPSndAudioMgr);

public:
    u32 getUserParam(const nw4r::snd::SoundArchivePlayer& rPlayer,
                     u32 id) const;

    u32 getPlayerNum() const {
        return mPlayerNum;
    }

private:
    char unk8A0[0x968 - 0x8A0];
    u32 mPlayerNum; // at 0x968
};

//! @}

#endif
