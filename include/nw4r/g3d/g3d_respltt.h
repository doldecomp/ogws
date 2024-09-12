#ifndef NW4R_G3D_RESPLTT_H
#define NW4R_G3D_RESPLTT_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_rescommon.h>

#include <revolution/GX.h>

namespace nw4r {
namespace g3d {

struct ResPlttData {
    ResBlockHeaderData header; // at 0x0
    u32 revision;              // at 0x8
    s32 toResFileData;         // at 0xC
    s32 toPlttData;            // at 0x10
    s32 name;                  // at 0x14
    GXTlutFmt fmt;             // at 0x18
    u16 numEntries;            // at 0x1C
    u16 dummy_;                // at 0x1E
    s32 original_path;         // at 0x20
    s32 toResUserData;         // at 0x24
};

class ResPltt : public ResCommon<ResPlttData> {
public:
    static const u32 SIGNATURE = 'PLT0';
    static const int REVISION = 1;

public:
    ResPltt(void* pData) : ResCommon(pData) {}

    bool CheckRevision() const {
        return ref().revision == REVISION;
    }

    void DCStore(bool sync);
};

} // namespace g3d
} // namespace nw4r

#endif
