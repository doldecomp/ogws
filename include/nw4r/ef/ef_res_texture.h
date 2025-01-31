#ifndef NW4R_EF_RES_TEXTURE_H
#define NW4R_EF_RES_TEXTURE_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/ef_types.h>

namespace nw4r {
namespace ef {

// TODO: Unsure which field is missing
struct TextureData {
    char* name;      // at 0x0
    u16 width;       // at 0x4
    u16 height;      // at 0x6
    u32 dataSize;    // at 0x8
    u8 format;       // at 0xC
    u8 tlutFormat;   // at 0xD
    u16 tlutEntries; // at 0xE
    u32 tlutSize;    // at 0x10
    u8 mipmap;       // at 0x14
    u8 min_filt;     // at 0x15
    u8 mag_filt;     // at 0x16
    u8 reserved[1];  // at 0x17
    // f32 lod_bias;    // at 0x18
    u8* texture; // at 0x18
    u8* tlut;    // at 0x1C
};

class ResTexture {
private:
    TextureData* mData; // at 0x0

public:
    explicit ResTexture(TextureData* pData = NULL) : mData(pData) {}
    explicit ResTexture(const ResTexture& rOther) : mData(rOther.mData) {}

    bool IsValid() const {
        return mData != NULL;
    }

    TextureData* ptr() {
        return mData;
    }
};

} // namespace ef
} // namespace nw4r

#endif
