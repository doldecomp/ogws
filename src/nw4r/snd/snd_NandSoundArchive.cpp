#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>
#include <nw4r/ut.h>
#include <revolution/NAND.h>

namespace nw4r {
namespace snd {

class NandSoundArchive::NandFileStream : public ut::NandFileStream {
public:
    NandFileStream(const NANDFileInfo* pFileInfo, u32 offset, u32 size);
    NandFileStream(const char* pPath, u32 offset, u32 size);
    virtual ~NandFileStream() {} // at 0xC

    virtual s32 Read(void* pDst, u32 size); // at 0x14

    virtual u32 GetSize() const {
        return mSize;
    } // at 0x40

    virtual void Seek(s32, u32); // at 0x44

    virtual u32 Tell() const {
        return ut::NandFileStream::Tell() - mOffset;
    } // at 0x58

private:
    s32 mOffset; // at 0x16C
    s32 mSize;   // at 0x170
};

NandSoundArchive::NandSoundArchive() : mOpen(false) {}

NandSoundArchive::~NandSoundArchive() {
    Close();
}

bool NandSoundArchive::Open(const char* pPath) {
    if (mOpen) {
        Close();
    }

    if (NANDOpen(pPath, &mFileInfo, 1)) {
        return false;
    }

    mOpen = true;

    if (!LoadFileHeader()) {
        return false;
    }

    char currentDir[64];
    NANDGetCurrentDir(currentDir);
    u32 currDirLen = strlen(currentDir);

    char extRoot[256];
    strncpy(extRoot, currentDir, currDirLen + 1);

    for (int i = strlen(pPath) - 1; i >= 0; i--) {
        if (pPath[i] == '/' || pPath[i] == '\\') {
            // @bug Long path can overflow extRoot buffer
            strncat(extRoot, pPath, i);
            extRoot[currDirLen + i] = '\0';
            break;
        }
    }

    SetExternalFileRoot(extRoot);
    return true;
}

void NandSoundArchive::Close() {
    if (mOpen) {
        NANDClose(&mFileInfo);
        mOpen = false;
    }

    Shutdown();
}

ut::FileStream* NandSoundArchive::OpenStream(void* pBuffer, int size,
                                             u32 offset, u32 length) const {
    if (!mOpen) {
        return NULL;
    }

    if (size < sizeof(NandFileStream)) {
        return NULL;
    }

    return new (pBuffer) NandFileStream(&mFileInfo, offset, length);
}

ut::FileStream* NandSoundArchive::OpenExtStream(void* pBuffer, int size,
                                                const char* pExtPath,
                                                u32 offset, u32 length) const {
    if (!mOpen) {
        return NULL;
    }

    if (size < sizeof(NandFileStream)) {
        return NULL;
    }

    NandFileStream* pExtStream =
        new (pBuffer) NandFileStream(pExtPath, offset, length);

    if (!pExtStream->IsAvailable()) {
        pExtStream->~NandFileStream();
        return NULL;
    }

    return pExtStream;
}

int NandSoundArchive::detail_GetRequiredStreamBufferSize() const {
    return sizeof(NandFileStream);
}

bool NandSoundArchive::LoadFileHeader() {
    // TODO: How is this calculated?
    u8 headerArea[ROUND_UP(sizeof(detail::SoundArchiveFile::Header), 32) + 40];

    static const u32 headerAlignSize =
        ut::RoundUp(sizeof(detail::SoundArchiveFile::Header), 32);

    void* pFile = ut::RoundUp<u8>(headerArea, 32);

    if (NANDSeek(&mFileInfo, 0, NAND_SEEK_BEG) != NAND_RESULT_OK) {
        return false;
    }

    u32 bytesRead = NANDRead(&mFileInfo, pFile, headerAlignSize);
    if (bytesRead != headerAlignSize) {
        return false;
    }

    mFileReader.Init(pFile);
    Setup(&mFileReader);

    return true;
}

bool NandSoundArchive::LoadHeader(void* pBuffer, u32 size) {
    u32 infoSize = mFileReader.GetInfoChunkSize();
    s32 infoOffset = mFileReader.GetInfoChunkOffset();
    // TODO: Fakematch
    s32* new_var = &infoOffset;

    if (size < infoSize) {
        return false;
    }

    s32 currOffset = NANDSeek(&mFileInfo, *new_var, NAND_SEEK_BEG);
    if (currOffset != infoOffset) {
        return false;
    }

    u32 bytesRead = NANDRead(&mFileInfo, pBuffer, infoSize);
    if (bytesRead != infoSize) {
        return false;
    }

    mFileReader.SetInfoChunk(pBuffer, infoSize);
    return true;
}

bool NandSoundArchive::LoadLabelStringData(void* pBuffer, u32 size) {
    u32 labelSize = mFileReader.GetLabelStringChunkSize();
    s32 labelOffset = mFileReader.GetLabelStringChunkOffset();
    // TODO: Fakematch
    s32* new_var = &labelOffset;

    if (size < labelSize) {
        return false;
    }

    s32 currOffset = NANDSeek(&mFileInfo, *new_var, NAND_SEEK_BEG);
    if (currOffset != labelOffset) {
        return false;
    }

    u32 bytesRead = NANDRead(&mFileInfo, pBuffer, labelSize);
    if (bytesRead != labelSize) {
        return false;
    }

    mFileReader.SetStringChunk(pBuffer, labelSize);
    return true;
}

NandSoundArchive::NandFileStream::NandFileStream(const NANDFileInfo* pFileInfo,
                                                 u32 offset, u32 size)
    : ut::NandFileStream(pFileInfo, NAND_ACCESS_READ, false),
      mOffset(offset),
      mSize(size) {

    if (IsAvailable()) {
        if (mSize == 0) {
            mSize = ut::NandFileStream::GetSize();
        }

        ut::NandFileStream::Seek(mOffset, SEEK_BEG);
    }
}

NandSoundArchive::NandFileStream::NandFileStream(const char* pPath, u32 offset,
                                                 u32 size)
    : ut::NandFileStream(pPath, NAND_ACCESS_READ),
      mOffset(offset),
      mSize(size) {

    if (IsAvailable()) {
        if (mSize == 0) {
            mSize = ut::NandFileStream::GetSize();
        }

        ut::NandFileStream::Seek(mOffset, SEEK_BEG);
    }
}

s32 NandSoundArchive::NandFileStream::Read(void* pDst, u32 size) {
    u32 endOffset = mOffset + mSize;
    u32 startOffset = ut::NandFileStream::Tell();

    if (startOffset + size > endOffset) {
        size = ut::RoundUp(endOffset - ut::NandFileStream::Tell(), 32);
    }

    s32 bytesRead = ut::NandFileStream::Read(pDst, size);
    DCStoreRange(pDst, size);

    return bytesRead;
}

void NandSoundArchive::NandFileStream::Seek(s32 offset, u32 origin) {
    switch (origin) {
    case SEEK_BEG:
        offset += mOffset;
        break;

    case SEEK_CUR:
        offset += ut::NandFileStream::Tell();
        break;

    case SEEK_END:
        offset = mOffset + mSize - offset;
        break;

    default:
        return;
    }

    if (offset < mOffset) {
        offset = mOffset;
    } else if (offset > mOffset + mSize) {
        offset = mOffset + mSize;
    }

    ut::NandFileStream::Seek(offset, SEEK_BEG);
}

// clang-format off
DECOMP_FORCEACTIVE(snd_NandSoundArchive_cpp,
                   NandSoundArchive::NandFileStream::GetSize,
                   NandSoundArchive::NandFileStream::Tell);
// clang-format on

} // namespace snd
} // namespace nw4r
