#ifndef EGG_CORE_DVD_FILE_H
#define EGG_CORE_DVD_FILE_H
#include <egg/types_egg.h>

#include <egg/core/eggFile.h>

#include <nw4r/ut.h>

#include <revolution/DVD.h>
#include <revolution/OS.h>

namespace EGG {

class DvdFile : public File {
public:
    static void initialize();

    DvdFile();
    virtual ~DvdFile(); // at 0x8

    virtual bool open(const char* pPath);                     // at 0xC
    virtual bool open(s32 entryNum);                          // at 0x20
    virtual bool open(const char* pPath, void* pMultiHandle); // at 0x24

    virtual void close(); // at 0x10

    virtual s32 readData(void* pDst, s32 size, s32 offset);        // at 0x14
    virtual s32 writeData(const void* pSrc, s32 size, s32 offset); // at 0x18

    virtual u32 getFileSize() const {
        return mAsyncContext.fileInfo.size;
    }; // at 0x1C

    void initiate();

    DVDFileInfo* getFileInfo() {
        return &mAsyncContext.fileInfo;
    }
    s32 getStatus() const {
        return DVDGetCommandBlockStatus(&mAsyncContext.cmdBlock);
    }

private:
    struct AsyncContext {
        union {
            DVDFileInfo fileInfo;     // at 0x0
            DVDCommandBlock cmdBlock; // at 0x0
        };
        DvdFile* pFile; // at 0x3C
    };

private:
    s32 sync();

    static void doneProcess(s32 result, DVDFileInfo* pFileInfo);

private:
    OSMutex mSyncMutex;  // at 0x8
    OSMutex mAsyncMutex; // at 0x20

    OSThread* mAsyncThread;     // at 0x38
    AsyncContext mAsyncContext; // at 0x3C
    OSMessageQueue mAsyncQueue; // at 0x7C
    OSMessage mAsyncBuffer[1];  // at 0x9C

    OSMessageQueue mSyncQueue; // at 0xA0
    OSMessage mSyncBuffer[1];  // at 0xC0
    OSThread* mSyncThread;     // at 0xC4

    nw4r::ut::Link mLink; // at 0xC8

    static nw4r::ut::List sDvdList;
    static bool sIsInitialized;
};

} // namespace EGG

#endif
