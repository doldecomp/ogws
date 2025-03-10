#ifndef NW4R_LYT_RESOURCES_H
#define NW4R_LYT_RESOURCES_H
#include <nw4r/types_nw4r.h>

#include <nw4r/lyt/lyt_types.h>

namespace nw4r {
namespace lyt {
namespace res {

/******************************************************************************
 *
 * BinaryFileHeader
 *
 ******************************************************************************/
struct BinaryFileHeader {
    char signature[4]; // at 0x0
    u16 byteOrder;     // at 0x4
    u16 version;       // at 0x6
    u32 fileSize;      // at 0x8
    u16 headerSize;    // at 0xC
    u16 dataBlocks;    // at 0xE
};

/******************************************************************************
 *
 * DataBlockHeader
 *
 ******************************************************************************/
struct DataBlockHeader {
    char kind[4]; // at 0x0
    u32 size;     // at 0x4
};

/******************************************************************************
 *
 * Texture
 *
 ******************************************************************************/
struct Texture {
    u32 nameStrOffset;         // at 0x0
    u8 type;                   // at 0x4
    u8 PADDING_0x5[0x8 - 0x5]; // at 0x5
};
/******************************************************************************
 *
 * TextureList
 *
 ******************************************************************************/
struct TextureList {
    res::DataBlockHeader blockHeader; // at 0x0
    u16 texNum;                       // at 0x8
    u8 PADDING_0xA[0xC - 0xA];        // at 0xA
};

/******************************************************************************
 *
 * Font
 *
 ******************************************************************************/
struct Font {
    u32 nameStrOffset;         // at 0x0
    u8 type;                   // at 0x4
    u8 PADDING_0x5[0x8 - 0x5]; // at 0x5
};
/******************************************************************************
 *
 * FontList
 *
 ******************************************************************************/
struct FontList {
    res::DataBlockHeader blockHeader; // at 0x0
    u16 fontNum;                      // at 0x8
    u8 PADDING_0xA[0xC - 0xA];        // at 0xA
};

/******************************************************************************
 *
 * MaterialList
 *
 ******************************************************************************/
struct MaterialList {
    res::DataBlockHeader blockHeader; // at 0x0
    u16 materialNum;                  // at 0x8
    u8 PADDING_0xA[0xC - 0xA];        // at 0xA
};

/******************************************************************************
 *
 * TexMap
 *
 ******************************************************************************/
struct TexMap {
    u16 texIdx; // at 0x0
    u8 wrapS;   // at 0x2
    u8 wrapT;   // at 0x3
};

} // namespace res

/******************************************************************************
 *
 * ResBlockSet
 *
 ******************************************************************************/
struct ResBlockSet {
    const res::TextureList* pTextureList;   // at 0x0
    const res::FontList* pFontList;         // at 0x4
    const res::MaterialList* pMaterialList; // at 0x8
    ResourceAccessor* pResAccessor;         // at 0xC
};

/******************************************************************************
 *
 * MaterialResourceNum
 *
 ******************************************************************************/
struct MaterialResourceNum {
    u32 bits;

    u8 GetTexMapNum() const {
        return detail::GetBits(bits, 0, 4);
    }
    u8 GetTexSRTNum() const {
        return detail::GetBits(bits, 4, 4);
    }
    u8 GetTexCoordGenNum() const {
        return detail::GetBits(bits, 8, 4);
    }
    bool HasTevSwapTable() const {
        return detail::TestBit(bits, 12);
    }
    u8 GetIndTexSRTNum() const {
        return detail::GetBits(bits, 13, 2);
    }
    u8 GetIndTexStageNum() const {
        return detail::GetBits(bits, 15, 3);
    }
    u8 GetTevStageNum() const {
        return detail::GetBits(bits, 18, 5);
    }
    bool HasAlphaCompare() const {
        return detail::TestBit(bits, 23);
    }
    bool HasBlendMode() const {
        return detail::TestBit(bits, 24);
    }
    u8 GetChanCtrlNum() const {
        return detail::GetBits(bits, 25, 1);
    }
    u8 GetMatColNum() const {
        return detail::GetBits(bits, 27, 1);
    }
};

} // namespace lyt
} // namespace nw4r

#endif
