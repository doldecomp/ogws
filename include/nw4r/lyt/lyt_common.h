#ifndef NW4R_LYT_COMMON_H
#define NW4R_LYT_COMMON_H
#include <nw4r/types_nw4r.h>

#include <nw4r/lyt/lyt_types.h>

#include <nw4r/math.h>
#include <nw4r/ut.h>

#include <revolution/GX.h>

namespace nw4r {
namespace lyt {

// Forward declarations
class ResourceAccessor;

/******************************************************************************
 *
 * VertexColor
 *
 ******************************************************************************/
enum VertexColor {
    VERTEXCOLOR_TL,
    VERTEXCOLOR_TR,
    VERTEXCOLOR_BL,
    VERTEXCOLOR_BR,

    VERTEXCOLOR_MAX
};

/******************************************************************************
 *
 * TevColor
 *
 ******************************************************************************/
enum TevColor {
    TEVCOLOR_1,
    TEVCOLOR_2,
    TEVCOLOR_3,

    TEVCOLOR_MAX
};

/******************************************************************************
 *
 * TevKColor
 *
 ******************************************************************************/
enum TevKColor {
    TEVKCOLOR_1,
    TEVKCOLOR_2,
    TEVKCOLOR_3,
    TEVKCOLOR_4,

    TEVKCOLOR_MAX
};

/******************************************************************************
 *
 * AnimTargetColor
 *
 ******************************************************************************/
enum AnimTargetColor {
    ANIMTARGET_VERTEXCOLOR_TL_RED,
    ANIMTARGET_VERTEXCOLOR_TL_GREEN,
    ANIMTARGET_VERTEXCOLOR_TL_BLUE,
    ANIMTARGET_VERTEXCOLOR_TL_ALPHA,

    ANIMTARGET_VERTEXCOLOR_TR_RED,
    ANIMTARGET_VERTEXCOLOR_TR_GREEN,
    ANIMTARGET_VERTEXCOLOR_TR_BLUE,
    ANIMTARGET_VERTEXCOLOR_TR_ALPHA,

    ANIMTARGET_VERTEXCOLOR_BL_RED,
    ANIMTARGET_VERTEXCOLOR_BL_GREEN,
    ANIMTARGET_VERTEXCOLOR_BL_BLUE,
    ANIMTARGET_VERTEXCOLOR_BL_ALPHA,

    ANIMTARGET_VERTEXCOLOR_BR_RED,
    ANIMTARGET_VERTEXCOLOR_BR_GREEN,
    ANIMTARGET_VERTEXCOLOR_BR_BLUE,
    ANIMTARGET_VERTEXCOLOR_BR_ALPHA,

    ANIMTARGET_VERTEXCOLOR_MAX
};

namespace detail {

/******************************************************************************
 *
 * Vertex colors
 *
 ******************************************************************************/
inline u8 GetVtxColorElement(const ut::Color* pColors, u32 idx) {
    return reinterpret_cast<const u8*>(
        &pColors[idx / VERTEXCOLOR_MAX])[idx % 4];
}
inline void SetVtxColorElement(ut::Color* pColors, u32 idx, u8 value) {
    reinterpret_cast<u8*>(&pColors[idx / VERTEXCOLOR_MAX])[idx % 4] = value;
}

/******************************************************************************
 *
 * Positioning
 *
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

/******************************************************************************
 *
 * TexCoordAry
 *
 ******************************************************************************/
typedef math::VEC2 TexCoord[VERTEXCOLOR_MAX];

class TexCoordAry {
public:
    TexCoordAry();

    void Free();
    void Reserve(u8 num);
    void SetSize(u8 num);
    void Copy(const void* pDst, u8 num);

    bool IsEmpty() const {
        return mCap == 0;
    }

    u8 GetSize() const {
        return mNum;
    }

    TexCoord* GetArray() const {
        return mpData;
    }

private:
    u8 mCap; // at 0x0
    u8 mNum; // at 0x1
    TexCoord* mpData;
};

/******************************************************************************
 *
 * Utility functions
 *
 ******************************************************************************/
inline bool IsCITexelFormat(GXTexFmt format) {
    return format == GX_TF_C4 || format == GX_TF_C8 || format == GX_TF_C14X2;
}

bool EqualsResName(const char* pLhs, const char* pRhs);
bool EqualsMaterialName(const char* pLhs, const char* pRhs);

bool IsModulateVertexColor(ut::Color* pColors, u8 glbAlpha);

ut::Color MultipleAlpha(ut::Color color, u8 alpha);
void MultipleAlpha(ut::Color* pDst, const ut::Color* pSrc, u8 alpha);

void SetVertexFormat(bool modulate, u8 numCoord);

void DrawQuad(const math::VEC2& rBase, const Size& rSize, u8 numCoord,
              const TexCoord* pCoords, const ut::Color* pColors);
void DrawQuad(const math::VEC2& rBase, const Size& rSize, u8 numCoord,
              const TexCoord* pCoords, const ut::Color* pColors, u8 alpha);

} // namespace detail
} // namespace lyt
} // namespace nw4r

#endif
