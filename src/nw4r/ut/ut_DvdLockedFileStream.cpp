#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/ut.h>

#include <revolution/OS.h>

namespace nw4r {
namespace ut {

NW4R_UT_RTTI_DEF_DERIVED(DvdLockedFileStream, DvdFileStream);

bool DvdLockedFileStream::sInitialized = false;
OSMutex DvdLockedFileStream::sMutex;

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

DvdLockedFileStream::DvdLockedFileStream(const DVDFileInfo* pInfo, bool close)
    : DvdFileStream(pInfo, close) {
    InitMutex_();
}

DvdLockedFileStream::~DvdLockedFileStream() {}

s32 DvdLockedFileStream::Read(void* pDst, u32 size) {
    OSLockMutex(&sMutex);
    s32 result = DvdFileStream::Read(pDst, size);
    OSUnlockMutex(&sMutex);
    return result;
}

s32 DvdLockedFileStream::Peek(void* pDst, u32 size) {
    OSLockMutex(&sMutex);
    s32 result = DvdFileStream::Peek(pDst, size);
    OSUnlockMutex(&sMutex);
    return result;
}

} // namespace ut
} // namespace nw4r
