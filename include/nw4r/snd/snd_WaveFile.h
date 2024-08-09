#ifndef NW4R_SND_WAVE_FILE_H
#define NW4R_SND_WAVE_FILE_H
#include "snd_Common.h"
#include "snd_Util.h"
#include "types_nw4r.h"
#include "ut_binaryFileFormat.h"

namespace nw4r {
namespace snd {
namespace detail {

struct WaveData {
    u8 sampleFormat;                        // at 0x0
    u8 loopFlag;                            // at 0x1
    u8 numChannels;                         // at 0x2
    int sampleRate;                         // at 0x4
    u32 loopStart;                          // at 0x8
    u32 loopEnd;                            // at 0xC
    ChannelParam channelParam[CHANNEL_MAX]; // at 0x10
};

struct WaveFile {
    struct WaveInfo {};

    typedef Util::DataRef<WaveInfo, void, void, void> Region;
};

struct WaveFileReader {
    WaveFileReader(const WaveFile::WaveInfo*);
    bool ReadWaveParam(WaveData*, const void*) const;
};

} // namespace detail
} // namespace snd
} // namespace nw4r

#endif