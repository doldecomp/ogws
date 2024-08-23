#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>
#include <nw4r/ut.h>
#include <revolution/DVD.h>

namespace nw4r {
namespace snd {

class DvdSoundArchive::DvdFileStream : public ut::DvdLockedFileStream {
public:
    DvdFileStream(const DVDFileInfo* pFileInfo, u32 offset, u32 size);
    DvdFileStream(s32 entrynum, u32 offset, u32 size);
    virtual ~DvdFileStream() {} // at 0xC

    virtual s32 Read(void* pDst, u32 size);    // at 0x14
    virtual void Seek(s32 offset, u32 origin); // at 0x44

    virtual u32 GetSize() const {
        return mSize;
    } // at 0x40

    virtual u32 Tell() const {
        return ut::DvdFileStream::Tell() - mOffset;
    } // at 0x58

private:
    s32 mOffset; // at 0x70
    s32 mSize;   // at 0x74
};

DvdSoundArchive::DvdSoundArchive() : mOpen(false) {}

DvdSoundArchive::~DvdSoundArchive() {
    Close();
}

bool DvdSoundArchive::Open(s32 entrynum) {
    if (!DVDFastOpen(entrynum, &mFileInfo)) {
        return false;
    }

    mOpen = true;
    return LoadFileHeader();
}

bool DvdSoundArchive::Open(const char* pPath) {
    s32 entrynum = DVDConvertPathToEntrynum(pPath);
    if (entrynum < 0) {
        return false;
    }

    if (!Open(entrynum)) {
        return false;
    }

    char extRoot[256];
    for (int i = strlen(pPath) - 1; i >= 0; i--) {
        if (pPath[i] == '/' || pPath[i] == '\\') {
            // @bug Long path can overflow extRoot buffer
            strncpy(extRoot, pPath, i);
            extRoot[i] = '\0';

            SetExternalFileRoot(extRoot);
            break;
        }
    }

    return true;
}

void DvdSoundArchive::Close() {
    DVDClose(&mFileInfo);
    mOpen = false;
    Shutdown();
}

ut::FileStream* DvdSoundArchive::OpenStream(void* pBuffer, int size, u32 offset,
                                            u32 length) const {
    if (!mOpen) {
        return NULL;
    }

    if (size < sizeof(DvdFileStream)) {
        return NULL;
    }

    return new (pBuffer) DvdFileStream(&mFileInfo, offset, length);
}

ut::FileStream* DvdSoundArchive::OpenExtStream(void* pBuffer, int size,
                                               const char* pExtPath, u32 offset,
                                               u32 length) const {
    if (!mOpen) {
        return NULL;
    }

    if (size < sizeof(DvdFileStream)) {
        return NULL;
    }

    s32 entrynum = DVDConvertPathToEntrynum(pExtPath);
    if (entrynum < 0) {
        return NULL;
    }

    return new (pBuffer) DvdFileStream(entrynum, offset, length);
}

int DvdSoundArchive::detail_GetRequiredStreamBufferSize() const {
    return sizeof(DvdFileStream);
}

bool DvdSoundArchive::LoadFileHeader() {
    // TODO: How is this calculated?
    u8 headerArea[ROUND_UP(sizeof(detail::SoundArchiveFile::Header), 32) + 40];

    static const u32 headerAlignSize =
        ut::RoundUp(sizeof(detail::SoundArchiveFile::Header), 32);

    void* pFile = ut::RoundUp<u8>(headerArea, 32);

    u32 bytesRead =
        DVDReadPrio(&mFileInfo, pFile, headerAlignSize, 0, DVD_PRIO_MEDIUM);
    if (bytesRead != headerAlignSize) {
        return false;
    }

    mFileReader.Init(pFile);
    Setup(&mFileReader);

    return true;
}

bool DvdSoundArchive::LoadHeader(void* pBuffer, u32 size) {
    u32 infoSize = mFileReader.GetInfoChunkSize();
    s32 infoOffset = mFileReader.GetInfoChunkOffset();

    if (size < infoSize) {
        return false;
    }

    u32 bytesRead =
        DVDReadPrio(&mFileInfo, pBuffer, infoSize, infoOffset, DVD_PRIO_MEDIUM);
    if (bytesRead != infoSize) {
        return false;
    }

    mFileReader.SetInfoChunk(pBuffer, infoSize);
    return true;
}

bool DvdSoundArchive::LoadLabelStringData(void* pBuffer, u32 size) {
    u32 labelSize = mFileReader.GetLabelStringChunkSize();
    s32 labelOffset = mFileReader.GetLabelStringChunkOffset();

    if (size < labelSize) {
        return false;
    }

    u32 bytesRead = DVDReadPrio(&mFileInfo, pBuffer, labelSize, labelOffset,
                                DVD_PRIO_MEDIUM);
    if (bytesRead != labelSize) {
        return false;
    }

    mFileReader.SetStringChunk(pBuffer, labelSize);
    return true;
}

DvdSoundArchive::DvdFileStream::DvdFileStream(const DVDFileInfo* pFileInfo,
                                              u32 offset, u32 size)
    : DvdLockedFileStream(pFileInfo, false), mOffset(offset), mSize(size) {
    if (mSize == 0) {
        mSize = ut::DvdFileStream::GetSize();
    }

    ut::DvdFileStream::Seek(mOffset, SEEK_BEG);
}

DvdSoundArchive::DvdFileStream::DvdFileStream(s32 entrynum, u32 offset,
                                              u32 size)
    : DvdLockedFileStream(entrynum), mOffset(offset), mSize(size) {
    if (mSize == 0) {
        mSize = ut::DvdFileStream::GetSize();
    }

    ut::DvdFileStream::Seek(mOffset, SEEK_BEG);
}

s32 DvdSoundArchive::DvdFileStream::Read(void* pDst, u32 size) {
    u32 endOffset = mOffset + mSize;
    u32 startOffset = ut::DvdFileStream::Tell();

    if (startOffset + size > endOffset) {
        size = ut::RoundUp(endOffset - ut::DvdFileStream::Tell(), 32);
    }

    return DvdLockedFileStream::Read(pDst, size);
}

void DvdSoundArchive::DvdFileStream::Seek(s32 offset, u32 origin) {
    switch (origin) {
    case SEEK_BEG:
        offset += mOffset;
        break;

    case SEEK_CUR:
        offset += ut::DvdFileStream::Tell();
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

    ut::DvdFileStream::Seek(offset, SEEK_BEG);
}

// clang-format off
DECOMP_FORCEACTIVE(snd_DvdSoundArchive_cpp,
                   DvdSoundArchive::DvdFileStream::GetSize,
                   DvdSoundArchive::DvdFileStream::Tell,
                   DvdSoundArchive::detail_GetWaveDataFileAddress,
                   DvdSoundArchive::detail_GetFileAddress);
// clang-format on

} // namespace snd
} // namespace nw4r
