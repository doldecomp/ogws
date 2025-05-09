#include <nw4r/snd.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace snd {
namespace detail {

bool StrmFileReader::IsValidFileHeader(const void* pStrmBin) {
    const ut::BinaryFileHeader* pFileHeader =
        static_cast<const ut::BinaryFileHeader*>(pStrmBin);

    if (pFileHeader->signature != SIGNATURE) {
        return false;
    }

    if (pFileHeader->version < NW4R_VERSION(1, 0)) {
        return false;
    }

    if (pFileHeader->version > VERSION) {
        return false;
    }

    return true;
}

StrmFileReader::StrmFileReader() : mHeader(NULL), mHeadBlock(NULL) {}

void StrmFileReader::Setup(const void* pStrmBin) {
    if (!IsValidFileHeader(pStrmBin)) {
        return;
    }

    mHeader = static_cast<const StrmFile::Header*>(pStrmBin);

    mHeadBlock = static_cast<const StrmFile::HeadBlock*>(
        ut::AddOffsetToPtr(mHeader, mHeader->headBlockOffset));

    (void)Util::GetDataRefAddress0(
        mHeadBlock->refDataHeader,
        &mHeadBlock->refDataHeader); // debug leftover
}

bool StrmFileReader::ReadStrmInfo(StrmInfo* pStrmInfo) const {
    const StrmFile::StrmDataInfo* pStrmData = Util::GetDataRefAddress0(
        mHeadBlock->refDataHeader, &mHeadBlock->refDataHeader);

    pStrmInfo->format = pStrmData->format;
    pStrmInfo->loopFlag = pStrmData->loopFlag;
    pStrmInfo->numChannels = pStrmData->numChannels;
    pStrmInfo->sampleRate =
        (pStrmData->sampleRate24 << 16) + pStrmData->sampleRate;
    pStrmInfo->blockHeaderOffset = pStrmData->blockHeaderOffset;
    pStrmInfo->loopStart = pStrmData->loopStart;
    pStrmInfo->loopEnd = pStrmData->loopEnd;
    pStrmInfo->dataOffset = pStrmData->dataOffset;
    pStrmInfo->numBlocks = pStrmData->numBlocks;
    pStrmInfo->blockSize = pStrmData->blockSize;
    pStrmInfo->blockSamples = pStrmData->blockSamples;
    pStrmInfo->lastBlockSize = pStrmData->lastBlockSize;
    pStrmInfo->lastBlockSamples = pStrmData->lastBlockSamples;
    pStrmInfo->lastBlockPaddedSize = pStrmData->lastBlockPaddedSize;
    pStrmInfo->adpcmDataInterval = pStrmData->adpcmDataInterval;
    pStrmInfo->adpcmDataSize = pStrmData->adpcmDataSize;

    return true;
}

bool StrmFileReader::ReadAdpcmInfo(AdpcmInfo* pAdpcmInfo, int channels) const {
    const StrmFile::StrmDataInfo* pStrmData = Util::GetDataRefAddress0(
        mHeadBlock->refDataHeader, &mHeadBlock->refDataHeader);

    if (pStrmData->format != WaveFile::FORMAT_ADPCM) {
        return false;
    }

    const StrmFile::ChannelTable* pChannelTable = Util::GetDataRefAddress0(
        mHeadBlock->refChannelTable, &mHeadBlock->refDataHeader);

    if (channels >= pChannelTable->channelCount) {
        return false;
    }

    const StrmFile::ChannelInfo* pChannelInfo = Util::GetDataRefAddress0(
        pChannelTable->refChannelHeader[channels], &mHeadBlock->refDataHeader);

    const AdpcmInfo* pSrcInfo = Util::GetDataRefAddress0(
        pChannelInfo->refAdpcmInfo, &mHeadBlock->refDataHeader);

    *pAdpcmInfo = *pSrcInfo;
    return true;
}

bool StrmFileLoader::LoadFileHeader(void* pStrmBin, u32 size) {
    u8 headerArea[HEADER_ALIGNED_SIZE + 32];
    u32 bytesRead;

    mStream.Seek(0, ut::FileStream::SEEK_BEG);
    bytesRead = mStream.Read(ut::RoundUp(headerArea, 32), HEADER_ALIGNED_SIZE);
    if (bytesRead != HEADER_ALIGNED_SIZE) {
        return false;
    }

    StrmFile::Header* pHeader =
        static_cast<StrmFile::Header*>(ut::RoundUp(headerArea, 32));

    StrmFileReader reader;
    if (!reader.IsValidFileHeader(pHeader)) {
        return false;
    }

    if (pHeader->adpcBlockOffset > size) {
        return false;
    }

    u32 loadSize = pHeader->headBlockOffset + pHeader->headBlockSize;

    mStream.Seek(0, ut::FileStream::SEEK_BEG);
    bytesRead = mStream.Read(pStrmBin, loadSize);
    if (bytesRead != loadSize) {
        return false;
    }

    mReader.Setup(pStrmBin);
    return true;
}

bool StrmFileLoader::ReadAdpcBlockData(u16* pYN1, u16* pYN2, int block,
                                       int channels) {
    if (!mReader.IsAvailable()) {
        return false;
    }

    s32 offset = mReader.GetAdpcBlockOffset() +
                 block * channels * (2 * sizeof(u16)) +
                 sizeof(ut::BinaryBlockHeader);

    mStream.Seek(offset, ut::FileStream::SEEK_BEG);

    u16 buffer[StrmPlayer::StrmHeader::STRM_CHANNEL_MAX * 2] ALIGN(32);
    // @bug Read size not validated
    mStream.Read(buffer, sizeof(buffer));

    for (int i = 0; i < channels; i++) {
        pYN1[i] = buffer[i * 2];
        pYN2[i] = buffer[i * 2 + 1];
    }

    return true;
}

} // namespace detail
} // namespace snd
} // namespace nw4r
