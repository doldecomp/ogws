#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace snd {
namespace detail {

/**
 * Dummy class to instantiate necessary weak functions
 */

#ifndef __DECOMP_NON_MATCHING
class MidiSeqPlayer : public SeqPlayer {
private:
    MidiSeqPlayer();

    // Dummy implementation, must prevent instantiating SeqPlayer version
    virtual void ChannelCallback(Channel* pChannel) {
#pragma unused(pChannel)
    }
};

MidiSeqPlayer::MidiSeqPlayer() {}
#endif

} // namespace detail
} // namespace snd
} // namespace nw4r
