#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/ut.h>

namespace nw4r {
namespace ut {

NW4R_UT_RTTI_DEF_BASE(IOStream);

bool IOStream::ReadAsync(void* dst, u32 size, AsyncCallback callback,
                         void* arg) {
#pragma unused(dst)
#pragma unused(size)
#pragma unused(callback)
#pragma unused(arg)
    return false;
}

void IOStream::Write(const void* src, u32 size) {
#pragma unused(src)
#pragma unused(size)
}

bool IOStream::WriteAsync(const void* src, u32 size, AsyncCallback callback,
                          void* arg) {
#pragma unused(src)
#pragma unused(size)
#pragma unused(callback)
#pragma unused(arg)
    return false;
}

bool IOStream::IsBusy() const { return false; }

} // namespace ut
} // namespace nw4r
