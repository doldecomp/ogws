#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/ut.h>

namespace nw4r {
namespace ut {

bool IsValidBinaryFile(const BinaryFileHeader* pHeader, u32 signature,
                       u16 version, u16 minBlocks) {
    if (pHeader->signature != signature) {
        return false;
    }

    if (pHeader->byteOrder != NW4R_BYTEORDER_NATIVE) {
        return false;
    }

    if (pHeader->version != version) {
        return false;
    }

    if (pHeader->fileSize <
        sizeof(BinaryFileHeader) + (minBlocks * sizeof(BinaryBlockHeader))) {
        return false;
    }

    if (pHeader->dataBlocks < minBlocks) {
        return false;
    }

    return true;
}

} // namespace ut
} // namespace nw4r
