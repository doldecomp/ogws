#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/ut.h>

namespace nw4r {
namespace ut {

NW4R_UT_RTTI_DEF_BASE(IOStream);

bool IOStream::ReadAsync(void* pDst, u32 size, AsyncCallback pCallback,
                         void* pCallbackArg) {
#pragma unused(pDst)
#pragma unused(size)
#pragma unused(pCallback)
#pragma unused(pCallbackArg)
    return false;
}

void IOStream::Write(const void* pSrc, u32 size) {
#pragma unused(pSrc)
#pragma unused(size)
}

bool IOStream::WriteAsync(const void* pSrc, u32 size, AsyncCallback pCallback,
                          void* pCallbackArg) {
#pragma unused(pSrc)
#pragma unused(size)
#pragma unused(pCallback)
#pragma unused(pCallbackArg)
    return false;
}

bool IOStream::IsBusy() const {
    return false;
}

} // namespace ut
} // namespace nw4r
