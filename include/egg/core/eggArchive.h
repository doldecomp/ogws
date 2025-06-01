#ifndef EGG_CORE_ARCHIVE_H
#define EGG_CORE_ARCHIVE_H
#include <egg/types_egg.h>

#include <egg/core/eggDisposer.h>

#include <nw4r/ut.h>

#include <revolution/ARC.h>

namespace EGG {

// Forward declarations
class Heap;

class Archive : public Disposer {
public:
    enum MountType { MOUNT_TYPE_NONE, MOUNT_TYPE_MEM, MOUNT_TYPE_FST };

    class FileInfo {
        friend class Archive;

    public:
        FileInfo() : mStartOffset(0), mLength(0) {}

        u32 getStartOffset() const {
            return mStartOffset;
        }
        u32 getLength() const {
            return mLength;
        }

    private:
        u32 mStartOffset; // at 0x0
        u32 mLength;      // at 0x4
    };

public:
    static Archive* mount(void* pArcBinary, Heap* pHeap, int align);
    static Archive* findArchive(void* pArcBinary);

    Archive();
    virtual ~Archive(); // at 0x8

    void* getFile(const char* pPath, FileInfo* pInfo);

private:
    bool initHandle(void* pArcBinary);

    static void appendList(Archive* pArchive);
    static void removeList(Archive* pArchive);

private:
    MountType mMountType; // at 0x10
    u32 mRefCount;        // at 0x14
    ARCHandle mHandle;    // at 0x18
    nw4r::ut::Link mLink; // at 0x34

    static nw4r::ut::List sArchiveList;
    static bool sIsArchiveListInitialized;
};

} // namespace EGG

#endif
