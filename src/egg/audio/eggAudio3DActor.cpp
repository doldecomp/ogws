// TODO(kiwi) REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/audio.h>

#include <nw4r/snd.h>

namespace EGG {

nw4r::snd::SoundArchivePlayer* AudioSound3DActor::smCommonPlayer = NULL;
nw4r::snd::Sound3DManager* AudioSound3DActor::smCommon3DManager = NULL;

} // namespace EGG
