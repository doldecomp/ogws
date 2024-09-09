#ifndef NW4R_UT_DVD_FILE_STREAM_H
#define NW4R_UT_DVD_FILE_STREAM_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ut/ut_FileStream.h>

#include <revolution/DVD.h>

namespace nw4r {
namespace ut {

class DvdFileStream : public FileStream {
public:
    NW4R_UT_RTTI_DECL(DvdFileStream);

public:
    explicit DvdFileStream(s32 entrynum);
    DvdFileStream(const DVDFileInfo* pInfo, bool close);
    virtual ~DvdFileStream(); // at 0xC

    bool Open(s32 entrynum);
    bool Open(const DVDFileInfo* pInfo, bool close);

    void SetPriority(s32 priority) {
        mPriority = priority;
    }

    virtual void Close(); // at 0x10

    virtual s32 Read(void* pDst, u32 size); // at 0x14
    virtual bool ReadAsync(void* pDst, u32 size, StreamCallback pCallback,
                           void* pCallbackArg); // at 0x18

    virtual s32 Peek(void* pDst, u32 size); // at 0x5C
    virtual bool PeekAsync(void* pDst, u32 size, StreamCallback pCallback,
                           void* pCallbackArg); // at 0x60

    virtual void Seek(s32 offset, u32 origin); // at 0x44

    virtual void Cancel(); // at 0x48
    virtual bool CancelAsync(StreamCallback pCallback,
                             void* pCallbackArg); // at 0x4C

    virtual bool IsBusy() const {
        return mIsBusy;
    } // at 0x24

    virtual u32 Tell() const {
        return mFilePosition.Tell();
    } // at 0x58
    virtual u32 GetSize() const {
        return mFilePosition.GetFileSize();
    } // at 0x40

    virtual bool CanAsync() const {
        return true;
    } // at 0x28
    virtual bool CanSeek() const {
        return true;
    } // at 0x50
    virtual bool CanRead() const {
        return true;
    } // at 0x2C
    virtual bool CanWrite() const {
        return false;
    } // at 0x30
    virtual bool CanCancel() const {
        return true;
    } // at 0x54

    virtual u32 GetOffsetAlign() const {
        return 4;
    } // at 0x34
    virtual u32 GetSizeAlign() const {
        return 32;
    } // at 0x38
    virtual u32 GetBufferAlign() const {
        return 32;
    } // at 0x3C

private:
    struct DvdFileStreamInfo {
        DVDFileInfo dvdInfo;   // at 0x0
        DvdFileStream* stream; // at 0x3C
    };

private:
    static void DvdAsyncCallback_(s32 result, DVDFileInfo* pInfo);
    static void DvdCBAsyncCallback_(s32 result, DVDCommandBlock* pBlock);

    void Initialize_();
    u32 AdjustReadLength_(u32 len);

private:
    FilePosition mFilePosition;     // at 0x14
    StreamCallback mCancelCallback; // at 0x1C
    void* mCancelArg;               // at 0x20
    volatile bool mIsCanceling;     // at 0x24
    DvdFileStreamInfo mFileInfo;    // at 0x28
    s32 mPriority;                  // at 0x68
    volatile bool mIsBusy;          // at 0x6C
    bool mCloseOnDestroyFlg;        // at 0x6D
    bool mCloseEnableFlg;           // at 0x6E
};

} // namespace ut
} // namespace nw4r
#endif
