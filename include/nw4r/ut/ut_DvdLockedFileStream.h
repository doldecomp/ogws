#ifndef NW4R_UT_DVD_LOCKED_FILE_STREAM_H
#define NW4R_UT_DVD_LOCKED_FILE_STREAM_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ut/ut_DvdFileStream.h>

#include <revolution/OS.h>

namespace nw4r {
namespace ut {

class DvdLockedFileStream : public DvdFileStream {
public:
    NW4R_UT_RTTI_DECL(DvdLockedFileStream);

public:
    explicit DvdLockedFileStream(s32 entrynum);
    DvdLockedFileStream(const DVDFileInfo* pInfo, bool close);
    virtual ~DvdLockedFileStream(); // at 0xC

    virtual s32 Read(void* pDst, u32 size); // at 0x14

    virtual bool ReadAsync(void* /* pDst */, u32 /* size */,
                           StreamCallback /* pCallback */,
                           void* /* pCallbackArg */) {

        return false;
    } // at 0x18

    virtual s32 Peek(void* pDst, u32 size); // at 0x5C

    virtual bool PeekAsync(void* /* pDst */, u32 /* size */,
                           StreamCallback /* pCallback */,
                           void* /* pCallbackArg */) {

        return false;
    } // at 0x60

    virtual bool CanAsync() const {
        return false;
    } // at 0x28

private:
    static void InitMutex_();

private:
    bool mCancelFlag; // at 0x6F

    static bool sInitialized;
    static OSMutex sMutex;
};

} // namespace ut
} // namespace nw4r
#endif
