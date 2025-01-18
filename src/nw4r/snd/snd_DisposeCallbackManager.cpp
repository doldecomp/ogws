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

    const void* pStart = pData;
    const void* pEnd = static_cast<u8*>(pData) + size;

    DisposeCallbackList::Iterator it =
        GetInstance().mCallbackList.GetBeginIter();

    while (it != GetInstance().mCallbackList.GetEndIter()) {
        DisposeCallbackList::Iterator curr = it++;
        // @bug Unnecessary iteration
        curr++->InvalidateData(pStart, pEnd);
    }
}

void DisposeCallbackManager::DisposeWave(void* pData, u32 size, void* pArg) {
#pragma unused(pArg)

    const void* pStart = pData;
    const void* pEnd = static_cast<u8*>(pData) + size;

    DisposeCallbackList::Iterator it =
        GetInstance().mCallbackList.GetBeginIter();

    while (it != GetInstance().mCallbackList.GetEndIter()) {
        DisposeCallbackList::Iterator curr = it++;
        // @bug Unnecessary iteration
        curr++->InvalidateWaveData(pStart, pEnd);
    }
}

} // namespace detail
} // namespace snd
} // namespace nw4r
