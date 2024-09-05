#ifndef NW4R_SND_VOICE_MANAGER_H
#define NW4R_SND_VOICE_MANAGER_H
#include <nw4r/snd/snd_Common.h>
#include <nw4r/snd/snd_Voice.h>
#include <nw4r/types_nw4r.h>

namespace nw4r {
namespace snd {
namespace detail {

class VoiceManager {
public:
    static const int VOICE_MAX = AX_VOICE_MAX;
    static const int WORK_SIZE_MAX = VOICE_MAX * sizeof(Voice);

public:
    static VoiceManager& GetInstance();

    u32 GetRequiredMemSize();

    void Setup(void* pWork, u32 workSize);
    void Shutdown();
    void StopAllVoices();

    Voice* AllocVoice(int channels, int voices, int prio,
                      Voice::VoiceCallback pCallback, void* pCallbackArg);
    void FreeVoice(Voice* pVoice);

    const VoiceList& GetVoiceList() const {
        return mPriorityList;
    }

    void UpdateAllVoices();
    void NotifyVoiceUpdate();
    void AppendVoiceList(Voice* pVoice);
    void RemoveVoiceList(Voice* pVoice);

    void ChangeVoicePriority(Voice* pVoice);
    void UpdateEachVoicePriority(const VoiceList::Iterator& rBegin,
                                 const VoiceList::Iterator& rEnd);
    void UpdateAllVoicesSync(u32 syncFlag);
    int DropLowestPriorityVoice(int prio);

private:
    VoiceManager();
    ~VoiceManager() {}

private:
    bool mInitialized;       // at 0x0
    VoiceList mPriorityList; // at 0x4
    VoiceList mFreeList;     // at 0x10
};

} // namespace detail
} // namespace snd
} // namespace nw4r

#endif
