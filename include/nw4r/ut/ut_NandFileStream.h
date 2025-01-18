#ifndef NW4R_UT_NAND_FILE_STREAM_H
#define NW4R_UT_NAND_FILE_STREAM_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ut/ut_FileStream.h>

#include <revolution/NAND.h>

namespace nw4r {
namespace ut {

class NandFileStream : public FileStream {
public:
    NW4R_UT_RTTI_DECL(NandFileStream);

public:
    NandFileStream(const char* pPath, u32 mode);
    NandFileStream(const NANDFileInfo* pInfo, u32 mode, bool enableClose);
    virtual ~NandFileStream(); // at 0xC

    bool Open(const char* pPath, u32 mode);
    bool Open(const NANDFileInfo* pInfo, u32 mode, bool enableClose)
        DECOMP_DONT_INLINE;

    virtual void Close(); // at 0x10

    virtual s32 Read(void* pDst, u32 size); // at 0x14
    virtual bool ReadAsync(void* pDst, u32 size, StreamCallback pCallback,
                           void* pCallbackArg); // at 0x18

    virtual void Write(const void* pSrc, u32 size); // at 0x1C
    virtual bool WriteAsync(const void* pSrc, u32 size,
                            StreamCallback pCallback,
                            void* pCallbackArg); // at 0x20

    virtual void Seek(s32 offset, u32 origin); // at 0x44

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
        return mCanRead;
    } // at 0x2C
    virtual bool CanWrite() const {
        return mCanWrite;
    } // at 0x30
    virtual bool CanCancel() const {
        return false;
    } // at 0x54

    virtual u32 GetOffsetAlign() const {
        return 1;
    } // at 0x34
    virtual u32 GetSizeAlign() const {
        return 32;
    } // at 0x38
    virtual u32 GetBufferAlign() const {
        return 32;
    } // at 0x3C

private:
    struct NandFileStreamInfo {
        NANDCommandBlock nandBlock; // at 0x0
        NANDFileInfo nandInfo;      // at 0xB8
        NandFileStream* stream;     // at 0x144
    };

private:
    static void NandAsyncCallback_(s32 result, NANDCommandBlock* pBlock);

    void Initialize_();

private:
    FilePosition mFilePosition;   // at 0x14
    NandFileStreamInfo mFileInfo; // at 0x1C
    bool mCanRead;                // at 0x164
    bool mCanWrite;               // at 0x165
    volatile bool mIsBusy;        // at 0x166
    bool mCloseOnDestroyFlg;      // at 0x167
    bool mCloseEnableFlg;         // at 0x168
};

} // namespace ut
} // namespace nw4r

#endif
