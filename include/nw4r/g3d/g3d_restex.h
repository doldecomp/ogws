#ifndef NW4R_G3D_RESTEX_H
#define NW4R_G3D_RESTEX_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_rescommon.h>

#include <revolution/GX.h>

namespace nw4r {
namespace g3d {

struct ResTexData {
    ResBlockHeaderData header; // at 0x0
    u32 revision;              // at 0x8
    s32 toResFileData;         // at 0xC
    s32 toTexData;             // at 0x10
    s32 name;                  // at 0x14
    u32 flag;                  // at 0x18
    u16 width;                 // at 0x1C
    u16 height;                // at 0x1E
    union {
        GXTexFmt fmt;
        GXCITexFmt cifmt;
    }; // at 0x20
    u32 mipmap_level;  // at 0x24
    f32 min_lod;       // at 0x28
    f32 max_lod;       // at 0x2C
    s32 original_path; // at 0x30
    s32 toResUserData; // at 0x34
};

class ResTex : public ResCommon<ResTexData> {
public:
    static const u32 SIGNATURE = 'TEX0';
    static const int REVISION = 1;

public:
    ResTex(void* pData) : ResCommon(pData) {}

    bool CheckRevision() const {
        return ref().revision == REVISION;
    }

    bool GetTexObjParam(void**, u16*, u16*, GXTexFmt*, f32*, f32*, u8*) const;
    bool GetTexObjCIParam(void**, u16*, u16*, GXCITexFmt*, f32*, f32*,
                          u8*) const;
    void Init();
};

} // namespace g3d
} // namespace nw4r

#endif
