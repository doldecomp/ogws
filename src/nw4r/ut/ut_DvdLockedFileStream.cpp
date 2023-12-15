#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/ut.h>
#include <revolution/OS.h>

namespace nw4r {
namespace ut {

NW4R_UT_RTTI_DEF_DERIVED(DvdLockedFileStream, DvdFileStream);

OSMutex DvdLockedFileStream::sMutex;
bool DvdLockedFileStream::sInitialized = false;

void DvdLockedFileStream::InitMutex_() {
    BOOL enabled = OSDisableInterrupts();

    if (!sInitialized) {
        OSInitMutex(&sMutex);
        sInitialized = true;
    }

    OSRestoreInterrupts(enabled);
}

DvdLockedFileStream::DvdLockedFileStream(s32 entrynum)
    : DvdFileStream(entrynum) {
    InitMutex_();
}

DvdLockedFileStream::DvdLockedFileStream(const DVDFileInfo* info, bool close)
    : DvdFileStream(info, close) {
    InitMutex_();
}

DvdLockedFileStream::~DvdLockedFileStream() {}

s32 DvdLockedFileStream::Read(void* dst, u32 size) {
    OSLockMutex(&sMutex);
    s32 result = DvdFileStream::Read(dst, size);
    OSUnlockMutex(&sMutex);
    return result;
}

s32 DvdLockedFileStream::Peek(void* dst, u32 size) {
    OSLockMutex(&sMutex);
    s32 result = DvdFileStream::Peek(dst, size);
    OSUnlockMutex(&sMutex);
    return result;
}

} // namespace ut
} // namespace nw4r
