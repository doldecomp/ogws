#ifndef NW4R_SND_VOICE_MANAGER_H
#define NW4R_SND_VOICE_MANAGER_H
#include <nw4r/snd/snd_Voice.h>
#include <nw4r/types_nw4r.h>

namespace nw4r {
namespace snd {
namespace detail {

class VoiceManager {
public:
    static VoiceManager& GetInstance();

    const VoiceList& GetVoiceList() const {
        return mPriorityList;
    }

    Voice* AllocVoice(int, int, int, Voice::VoiceCallback, void*);
    void FreeVoice(Voice*);

    void ChangeVoicePriority(Voice*);

    void UpdateAllVoices();
    void NotifyVoiceUpdate();
    UNKTYPE UpdateAllVoicesSync(u32);

private:
    bool mInitialized;       // at 0x0
    VoiceList mPriorityList; // at 0x4
    VoiceList mFreeList;     // at 0x10
};

} // namespace detail
} // namespace snd
} // namespace nw4r

#endif
