#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace snd {
namespace detail {

bool SeqFileReader::IsValidFileHeader(const void* pSeqData) {
    const ut::BinaryFileHeader* pFileHeader =
        static_cast<const ut::BinaryFileHeader*>(pSeqData);

    if (pFileHeader->magic != SIGNATURE) {
        return false;
    }

    if (pFileHeader->version < NW4R_VERSION(1, 00)) {
        return false;
    }

    if (pFileHeader->version > VERSION) {
        return false;
    }

    return true;
}

SeqFileReader::SeqFileReader(const void* pSeqData)
    : mHeader(NULL), mDataBlock(NULL) {
    if (!IsValidFileHeader(pSeqData)) {
        return;
    }

    mHeader = static_cast<const SeqFile::Header*>(pSeqData);

    mDataBlock = static_cast<const SeqFile::DataBlock*>(
        ut::AddOffsetToPtr(pSeqData, mHeader->dataBlockOffset));
}

const void* SeqFileReader::GetBaseAddress() const {
    return ut::AddOffsetToPtr(mDataBlock, mDataBlock->baseOffset);
}

} // namespace detail
} // namespace snd
} // namespace nw4r
