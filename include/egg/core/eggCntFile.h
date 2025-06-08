#ifndef EGG_CORE_CNT_FILE_H
#define EGG_CORE_CNT_FILE_H
#include <egg/types_egg.h>

#include <egg/core/eggFile.h>

#include <egg/prim.h>

#include <nw4r/ut.h>

#include <revolution/CNT.h>
#include <revolution/OS.h>

namespace EGG {

class CntFile : public File {
public:
    CntFile();
    virtual ~CntFile(); // at 0x8

    virtual bool open(const char* /* pPath */) {
#line 57
        EGG_ASSERT(false);
        return false;
    } // at 0xC

    bool open(const char* pPath, CNTHandle* pHandle);

    virtual void close(); // at 0x10

    virtual s32 readData(void* pDst, s32 size, s32 offset);        // at 0x14
    virtual s32 writeData(const void* pSrc, s32 size, s32 offset); // at 0x18

    virtual u32 getFileSize() const {
        return contentGetLengthNAND(&mAsyncContext.fileInfo);
    }; // at 0x1C

    void initiate();

private:
    struct AsyncContext {
        CNTFileInfo fileInfo; // at 0x0
        CNTHandle* pHandle;   // at 0x10
        CntFile* pFile;       // at 0x14
    };

private:
    OSMutex mSyncMutex;  // at 0x8
    OSMutex mAsyncMutex; // at 0x20

    OSThread* mAsyncThread;     // at 0x38
    AsyncContext mAsyncContext; // at 0x3C
    OSMessageQueue mAsyncQueue; // at 0x54
    OSMessage mAsyncBuffer[1];  // at 0x74

    OSMessageQueue mSyncQueue; // at 0x78
    OSMessage mSyncBuffer[1];  // at 0x98
    OSThread* mSyncThread;     // at 0x9C

    nw4r::ut::Link mNode; // at 0xA0

    static nw4r::ut::List sCntList;
    static bool sIsInitialized;
};

} // namespace EGG

#endif
