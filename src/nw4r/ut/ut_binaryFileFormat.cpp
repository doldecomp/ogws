#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/ut.h>

namespace nw4r {
namespace ut {

bool IsValidBinaryFile(const BinaryFileHeader* header, u32 magic, u16 version,
                       u16 numBlocks) {
    if (header->magic != magic) {
        return false;
    }

    if (header->byteOrder != NW4R_BYTEORDER_BIG) {
        return false;
    }

    if (header->version != version) {
        return false;
    }

    if (header->fileSize <
        sizeof(BinaryFileHeader) + (numBlocks * sizeof(BinaryBlockHeader))) {
        return false;
    }

    if (header->numBlocks < numBlocks) {
        return false;
    }

    return true;
}

} // namespace ut
} // namespace nw4r
