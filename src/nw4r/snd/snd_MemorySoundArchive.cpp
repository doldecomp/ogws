#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>
#include <nw4r/ut.h>

namespace nw4r {
namespace snd {

class MemorySoundArchive::MemoryFileStream : public ut::FileStream {
public:
    MemoryFileStream(const void* pBuffer, u32 size);
    virtual ~MemoryFileStream() {}

    virtual void Close();
    virtual s32 Read(void* pDst, u32 size);    // at 0x14
    virtual void Seek(s32 offset, u32 origin); // at 0x44

    virtual u32 GetSize() const {
        return mSize;
    } // at 0x40

    virtual u32 Tell() const {
        return mOffset;
    } // at 0x58

    virtual bool CanWrite() const {
        return false;
    } // at 0x30

    virtual bool CanRead() const {
        return true;
    } // at 0x2C

    virtual bool CanAsync() const {
        return false;
    } // at 0x28

    virtual bool CanCancel() const {
        return true;
    } // at 0x54

    virtual bool CanSeek() const {
        return true;
    } // at 0x50

private:
    const void* mData; // at 0x14
    u32 mSize;         // at 0x18
    u32 mOffset;       // at 0x1C
};

MemorySoundArchive::MemorySoundArchive() : mData(NULL) {}

MemorySoundArchive::~MemorySoundArchive() {}

bool MemorySoundArchive::Setup(const void* pBuffer) {
    mFileReader.Init(pBuffer);
    SoundArchive::Setup(&mFileReader);

    const void* pInfoChunk =
        ut::AddOffsetToPtr(pBuffer, mFileReader.GetInfoChunkOffset());

    mFileReader.SetInfoChunk(pInfoChunk, mFileReader.GetInfoChunkSize());

    const void* pStringChunk =
        ut::AddOffsetToPtr(pBuffer, mFileReader.GetLabelStringChunkOffset());

    mFileReader.SetStringChunk(pStringChunk,
                               mFileReader.GetLabelStringChunkSize());

    mData = pBuffer;
    return true;
}

void MemorySoundArchive::Shutdown() {
    mData = NULL;
    SoundArchive::Shutdown();
}

const void* MemorySoundArchive::detail_GetFileAddress(u32 id) const {
    SoundArchive::FilePos filePos;
    if (!detail_ReadFilePos(id, 0, &filePos)) {
        return NULL;
    }

    SoundArchive::GroupInfo groupInfo;
    if (!detail_ReadGroupInfo(filePos.groupId, &groupInfo)) {
        return NULL;
    }

    SoundArchive::GroupItemInfo groupItemInfo;
    if (!detail_ReadGroupItemInfo(filePos.groupId, filePos.index,
                                  &groupItemInfo)) {
        return NULL;
    }

    if (groupInfo.extFilePath != NULL) {
        return NULL;
    }

    return ut::AddOffsetToPtr(mData, groupInfo.offset + groupItemInfo.offset);
}

const void* MemorySoundArchive::detail_GetWaveDataFileAddress(u32 id) const {
    SoundArchive::FilePos filePos;
    if (!detail_ReadFilePos(id, 0, &filePos)) {
        return NULL;
    }

    SoundArchive::GroupInfo groupInfo;
    if (!detail_ReadGroupInfo(filePos.groupId, &groupInfo)) {
        return NULL;
    }

    SoundArchive::GroupItemInfo groupItemInfo;
    if (!detail_ReadGroupItemInfo(filePos.groupId, filePos.index,
                                  &groupItemInfo)) {
        return NULL;
    }

    if (groupInfo.extFilePath != NULL) {
        return NULL;
    }

    return ut::AddOffsetToPtr(mData, groupInfo.waveDataOffset +
                                         groupItemInfo.waveDataOffset);
}

MemorySoundArchive::MemoryFileStream::MemoryFileStream(const void* pBuffer,
                                                       u32 size)
    : mData(pBuffer), mSize(size), mOffset(0) {}

ut::FileStream* MemorySoundArchive::OpenStream(void* pBuffer, int size,
                                               u32 offset, u32 length) const {
    if (mData == NULL) {
        return NULL;
    }

    if (size < sizeof(MemoryFileStream)) {
        return NULL;
    }

    return new (pBuffer)
        MemoryFileStream(ut::AddOffsetToPtr(mData, offset), length);
}

ut::FileStream* MemorySoundArchive::OpenExtStream(void* pBuffer, int size,
                                                  const char* pExtPath,
                                                  u32 offset,
                                                  u32 length) const {
    return NULL;
}

int MemorySoundArchive::detail_GetRequiredStreamBufferSize() const {
    return sizeof(MemoryFileStream);
}

void MemorySoundArchive::MemoryFileStream::Close() {
    mData = NULL;
    mSize = 0;
    mOffset = 0;
}

s32 MemorySoundArchive::MemoryFileStream::Read(void* pDst, u32 size) {
    u32 bytesRead = ut::Min(size, mSize - mOffset);
    memcpy(pDst, ut::AddOffsetToPtr(mData, mOffset), bytesRead);

    return bytesRead;
}

void MemorySoundArchive::MemoryFileStream::Seek(s32 offset, u32 origin) {
    switch (origin) {
    case SEEK_BEG:
        mOffset = offset;
        break;

    case SEEK_CUR:
        mOffset += offset;
        break;

    case SEEK_END:
        mOffset = mSize - offset;
        break;

    default:
        return;
    }
}

// clang-format off
DECOMP_FORCEACTIVE(snd_MemorySoundArchive_cpp,
                   MemorySoundArchive::MemoryFileStream::GetSize,
                   MemorySoundArchive::MemoryFileStream::Tell,
                   MemorySoundArchive::MemoryFileStream::CanWrite,
                   MemorySoundArchive::MemoryFileStream::CanRead,
                   MemorySoundArchive::MemoryFileStream::CanAsync,
                   MemorySoundArchive::MemoryFileStream::CanCancel,
                   MemorySoundArchive::MemoryFileStream::CanSeek);
// clang-format on

} // namespace snd
} // namespace nw4r
