#ifndef NW4R_SND_STRM_FILE_H
#define NW4R_SND_STRM_FILE_H
#include <nw4r/snd/snd_Common.h>
#include <nw4r/snd/snd_Util.h>
#include <nw4r/types_nw4r.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace snd {
namespace detail {
namespace StrmFile {

struct StrmDataInfo {
    char dummy[0x34];
};

struct TrackTable {
    char dummy[0x4];
};

struct ChannelTable {
    char dummy[0x4];
};

struct Header {
    ut::BinaryFileHeader fileHeader; // at 0x0
    u32 headBlockOffset;             // at 0x10
    u32 headBlockSize;               // at 0x14
    u32 adpcBlockOffset;             // at 0x18
    u32 adpcBlockSize;               // at 0x1C
    u32 dataBlockOffset;             // at 0x20
    u32 dataBlockSize;               // at 0x24
};

struct HeadBlock {
    ut::BinaryBlockHeader blockHeader;                             // at 0x0
    Util::DataRef<StrmDataInfo, void, void, void> refDataHeader;   // at 0x8
    Util::DataRef<TrackTable, void, void, void> refTrackTable;     // at 0x10
    Util::DataRef<ChannelTable, void, void, void> refChannelTable; // at 0x18
};

} // namespace StrmFile

struct StrmInfo {
    u8 format;               // at 0x0
    u8 loopFlag;             // at 0x1
    u8 numChannels;          // at 0x2
    int sampleRate;          // at 0x4
    u16 blockHeaderOffset;   // at 0x8
    u32 loopStart;           // at 0xC
    u32 loopEnd;             // at 0x10
    u32 dataOffset;          // at 0x14
    u32 numBlocks;           // at 0x18
    u32 blockSize;           // at 0x1C
    u32 blockSamples;        // at 0x20
    u32 lastBlockSize;       // at 0x24
    u32 lastBlockSamples;    // at 0x28
    u32 lastBlockPaddedSize; // at 0x2C
    u32 adpcmDataInterval;   // at 0x30
    u32 adpcmDataSize;       // at 0x34
};

class StrmFileReader {
public:
public:
    StrmFileReader();

    bool IsAvailable() const {
        return mHeader != NULL;
    }

    bool ReadStrmInfo(StrmInfo* pStrmInfo) const;
    bool ReadAdpcmInfo(AdpcmInfo* pAdpcmInfo, int channel) const;

private:
    const StrmFile::Header* mHeader;       // at 0x0
    const StrmFile::HeadBlock* mHeadBlock; // at 0x4
};

class StrmFileLoader {
public:
    StrmFileLoader(ut::FileStream& rFileStream) : mStream(rFileStream) {}

    bool ReadStrmInfo(StrmInfo* pStrmInfo) const {
        if (!mReader.IsAvailable()) {
            return false;
        }

        return mReader.ReadStrmInfo(pStrmInfo);
    }

    bool ReadAdpcmInfo(AdpcmInfo* pAdpcmInfo, int channel) const {
        if (!mReader.IsAvailable()) {
            return false;
        }

        return mReader.ReadAdpcmInfo(pAdpcmInfo, channel);
    }

    bool LoadFileHeader(void* pHeader, u32 size);
    bool ReadAdpcBlockData(u16* pYN1, u16* pYN2, int block, int channels);

private:
    ut::FileStream& mStream; // at 0x0
    StrmFileReader mReader;  // at 0x4
};

} // namespace detail
} // namespace snd
} // namespace nw4r

#endif