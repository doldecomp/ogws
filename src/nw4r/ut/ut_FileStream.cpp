#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/ut.h>

namespace nw4r {
namespace ut {

NW4R_UT_RTTI_DEF_DERIVED(FileStream, IOStream);

void FileStream::Cancel() {}

bool FileStream::CancelAsync(StreamCallback pCallback, void* pCallbackArg) {
#pragma unused(pCallback)
#pragma unused(pCallbackArg)
    return true;
}

u32 FileStream::FilePosition::Skip(s32 offset) {
    if (offset != 0) {
        s64 newOffset = mPosition + offset;
        mPosition = Clamp<s64>(newOffset, 0, mFileSize);
    }

    return mPosition;
}

u32 FileStream::FilePosition::Append(s32 offset) {
    s64 newOffset = mPosition + offset;

    if (newOffset < 0) {
        mPosition = 0;
    } else {
        mPosition = newOffset;
        mFileSize = Max(mPosition, mFileSize);
    }

    return mPosition;
}

void FileStream::FilePosition::Seek(s32 offset, u32 origin) {
    switch (origin) {
    case SEEK_BEG: {
        mPosition = 0;
        break;
    }

    case SEEK_END: {
        mPosition = mFileSize;
        break;
    }

    case SEEK_CUR:
    default: {
        break;
    }
    }

    Skip(offset);
}

// clang-format off
DECOMP_FORCEACTIVE(ut_FileStream_cpp,
                   FileStream::GetRuntimeTypeInfo);
// clang-format on

} // namespace ut
} // namespace nw4r
