#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/ut.h>

namespace nw4r {
namespace ut {
namespace {

bool IsSJISLeadByte(u8 byte) {
    return (byte >= 0x81 && byte < 0xA0) || byte >= 0xE0;
}

} // namespace

u16 CharStrmReader::ReadNextCharUTF8() {
    u16 ret;

    if ((GetChar<u8>(0) & 0x80) == 0) {
        ret = GetChar<u8>(0);
        StepStrm<u8>(1);
    } else if ((GetChar<u8>(0) & 0xE0) == 0xC0) {
        ret = ((GetChar<u8>(0) & 0x1F) << 6) | (GetChar<u8>(1) & 0x3F);
        StepStrm<u8>(2);
    } else {
        ret = ((GetChar<u8>(0) & 0x1F) << 12) | ((GetChar<u8>(1) & 0x3F) << 6) |
              (GetChar<u8>(2) & 0x3F);
        StepStrm<u8>(3);
    }

    return ret;
}

u16 CharStrmReader::ReadNextCharUTF16() {
    u16 ret = GetChar<u16>(0);
    StepStrm<u16>(1);
    return ret;
}

u16 CharStrmReader::ReadNextCharCP1252() {
    u16 ret = GetChar<u8>(0);
    StepStrm<u8>(1);
    return ret;
}

u16 CharStrmReader::ReadNextCharSJIS() {
    u16 ret;

    if (IsSJISLeadByte(GetChar<u8>(0))) {
        ret = (GetChar<u8>(0) << 8) | GetChar<u8>(1);
        StepStrm<u8>(2);
    } else {
        ret = GetChar<u8>(0);
        StepStrm<u8>(1);
    }

    return ret;
}

} // namespace ut
} // namespace nw4r
