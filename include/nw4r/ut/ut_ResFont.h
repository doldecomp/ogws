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
    static const u32 SIGNATURE = 'RFNT';
    static const u32 SIGNATURE_UNPACKED = 'RFNU';

    static const u32 SIGNATURE_FONTINFO = 'FINF';
    static const u32 SIGNATURE_TEXGLYPH = 'TGLP';
    static const u32 SIGNATURE_CHARWIDTH = 'CWDH';
    static const u32 SIGNATURE_CHARMAP = 'CMAP';

    // TODO: Which block is this?
    static const u32 SIGNATURE_GLGR = 'GLGR';
};

} // namespace ut
} // namespace nw4r

#endif
