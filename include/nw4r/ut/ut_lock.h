#ifndef NW4R_UT_LOCK_H
#define NW4R_UT_LOCK_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ut/ut_NonCopyable.h>

#include <revolution/OS.h>

namespace nw4r {
namespace ut {
namespace detail {

/******************************************************************************
 *
 * Mutex lock functions
 *
 ******************************************************************************/
inline void Lock(OSMutex& rMutex) {
    OSLockMutex(&rMutex);
}
inline void Unlock(OSMutex& rMutex) {
    OSUnlockMutex(&rMutex);
}

/******************************************************************************
 *
 * AutoLock
 *
 ******************************************************************************/
template <typename T> class AutoLock : private NonCopyable {
public:
    explicit AutoLock(T& rLockObj) : mLockObj(rLockObj) {
        Lock(mLockObj);
    }
    ~AutoLock() {
        Unlock(mLockObj);
    }

private:
    T& mLockObj; // at 0x0
};

} // namespace detail

/******************************************************************************
 *
 * AutoInterruptLock
 *
 ******************************************************************************/
class AutoInterruptLock : private NonCopyable {
public:
    AutoInterruptLock() : mOldState(OSDisableInterrupts()) {}
    ~AutoInterruptLock() {
        OSRestoreInterrupts(mOldState);
    }

private:
    BOOL mOldState; // at 0x0
};

} // namespace ut
} // namespace nw4r

#endif
