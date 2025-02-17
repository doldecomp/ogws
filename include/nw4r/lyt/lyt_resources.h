#ifndef NW4R_LYT_RESOURCES_H
#define NW4R_LYT_RESOURCES_H
#include <nw4r/types_nw4r.h>

namespace nw4r {
namespace lyt {
namespace res {

/******************************************************************************
 *
 * DataBlockHeader
 *
 ******************************************************************************/
struct DataBlockHeader {
    char kind[4]; // at 0x0
    u32 size;     // at 0x4
};

} // namespace res

/******************************************************************************
 *
 * ResBlockSet
 *
 ******************************************************************************/
struct TextureList {
    res::DataBlockHeader blockHeader; // at 0x0
    u16 texNum;                       // at 0x8
    u8 PADDING_0xA[0xC - 0xA];        // at 0xA
};
struct FontList {
    res::DataBlockHeader blockHeader; // at 0x0
    u16 fontNum;                      // at 0x8
    u8 PADDING_0xA[0xC - 0xA];        // at 0xA
};
struct MaterialList {
    res::DataBlockHeader blockHeader; // at 0x0
    u16 materialNum;                  // at 0x8
    u8 PADDING_0xA[0xC - 0xA];        // at 0xA
};

struct ResBlockSet {
    const TextureList* pTextureList;   // at 0x0
    const FontList* pFontList;         // at 0x4
    const MaterialList* pMaterialList; // at 0x8
    ResourceAccessor* pResAccessor;    // at 0xC
};

} // namespace lyt
} // namespace nw4r

#endif
