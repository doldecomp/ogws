#ifndef NW4R_LYT_COMMON_H
#define NW4R_LYT_COMMON_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ut.h>

#include <revolution/GX.h>

namespace nw4r {
namespace lyt {

// Forward declarations
class ResourceAccessor;

/******************************************************************************
 *
 * Implementation details
 *
 ******************************************************************************/
namespace detail {

/******************************************************************************
 * Utility functions
 ******************************************************************************/
bool EqualsResName(const char* pLhs, const char* pRhs);
bool EqualsMaterialName(const char* pLhs, const char* pRhs);

inline bool IsCITexelFormat(GXTexFmt format) {
    return format == GX_TF_C4 || format == GX_TF_C8 || format == GX_TF_C14X2;
}

/******************************************************************************
 * Positioning
 ******************************************************************************/
enum HorizontalPosition {
    HORIZONTALPOSITION_LEFT,
    HORIZONTALPOSITION_CENTER,
    HORIZONTALPOSITION_RIGHT,
    HORIZONTALPOSITION_MAX
};
enum VerticalPosition {
    VERTICALPOSITION_TOP,
    VERTICALPOSITION_CENTER,
    VERTICALPOSITION_BOTTOM,
    VERTICALPOSITION_MAX
};

inline u8 GetHorizontalPosition(u8 packed) {
    return packed % HORIZONTALPOSITION_MAX;
}
inline u8 GetVerticalPosition(u8 packed) {
    return packed / HORIZONTALPOSITION_MAX;
}

inline void SetHorizontalPosition(u8* pPacked, u8 value) {
    *pPacked = GetVerticalPosition(*pPacked) * HORIZONTALPOSITION_MAX + value;
}
inline void SetVerticalPosition(u8* pPacked, u8 value) {
    *pPacked = value * HORIZONTALPOSITION_MAX + GetHorizontalPosition(*pPacked);
}

} // namespace detail

/******************************************************************************
 *
 * Binary resources
 *
 ******************************************************************************/
namespace res {

/******************************************************************************
 * DataBlockHeader
 ******************************************************************************/
struct DataBlockHeader {
    char kind[4]; // at 0x0
    u32 size;     // at 0x4
};

} // namespace res

/******************************************************************************
 * Resource blocks
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
