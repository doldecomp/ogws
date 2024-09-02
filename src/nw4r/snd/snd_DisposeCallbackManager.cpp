#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>

namespace nw4r {
namespace snd {
namespace detail {

DisposeCallbackManager& DisposeCallbackManager::GetInstance() {
    ut::AutoInterruptLock lock;
    static DisposeCallbackManager instance;
    return instance;
}

DisposeCallbackManager::DisposeCallbackManager() {}

void DisposeCallbackManager::RegisterDisposeCallback(
    DisposeCallback* pCallback) {
    mCallbackList.PushBack(pCallback);
}

void DisposeCallbackManager::UnregisterDisposeCallback(
    DisposeCallback* pCallback) {
    mCallbackList.Erase(pCallback);
}

void DisposeCallbackManager::Dispose(void* pData, u32 size, void* pArg) {
#pragma unused(pArg)

    const void* start = pData;
    const void* end = static_cast<u8*>(pData) + size;

    DisposeCallbackList::Iterator it =
        GetInstance().mCallbackList.GetBeginIter();

    while (it != GetInstance().mCallbackList.GetEndIter()) {
        DisposeCallbackList::Iterator curr = it++;
        curr++->InvalidateData(start, end);
    }
}

void DisposeCallbackManager::DisposeWave(void* pData, u32 size, void* pArg) {
#pragma unused(pArg)

    const void* start = pData;
    const void* end = static_cast<u8*>(pData) + size;

    DisposeCallbackList::Iterator it =
        GetInstance().mCallbackList.GetBeginIter();

    while (it != GetInstance().mCallbackList.GetEndIter()) {
        DisposeCallbackList::Iterator curr = it++;
        curr++->InvalidateWaveData(start, end);
    }
}

} // namespace detail
} // namespace snd
} // namespace nw4r
