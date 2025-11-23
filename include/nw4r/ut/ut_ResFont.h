#ifndef NW4R_UT_RES_FONT_H
#define NW4R_UT_RES_FONT_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ut/ut_ResFontBase.h>

namespace nw4r {
namespace ut {

// Forward declarations
struct BinaryFileHeader;

class ResFont : public detail::ResFontBase {
public:
    ResFont();
    virtual ~ResFont(); // at 0x8

    bool SetResource(void* pBuffer);

private:
    static FontInformation* Rebuild(BinaryFileHeader* pHeader);

private:
    static const u32 SIGNATURE = FOURCC('R', 'F', 'N', 'T');
    static const u32 SIGNATURE_UNPACKED = FOURCC('R', 'F', 'N', 'U');

    static const u32 SIGNATURE_FONTINFO = FOURCC('F', 'I', 'N', 'F');
    static const u32 SIGNATURE_TEXGLYPH = FOURCC('T', 'G', 'L', 'P');
    static const u32 SIGNATURE_CHARWIDTH = FOURCC('C', 'W', 'D', 'H');
    static const u32 SIGNATURE_CHARMAP = FOURCC('C', 'M', 'A', 'P');

    // TODO(kiwi) Which block is this?
    static const u32 SIGNATURE_GLGR = FOURCC('G', 'L', 'G', 'R');
};

} // namespace ut
} // namespace nw4r

#endif
