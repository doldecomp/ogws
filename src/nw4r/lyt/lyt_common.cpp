#include <nw4r/lyt.h>
#include <nw4r/math.h>
#include <nw4r/ut.h>

#include <revolution/GX.h>

#include <cstring>

namespace nw4r {
namespace lyt {
namespace detail {

/******************************************************************************
 *
 * Utility functions
 *
 ******************************************************************************/
bool EqualsResName(const char* pLhs, const char* pRhs) {
    return std::strncmp(pLhs, pRhs, NW4R_LYT_RES_NAME_LEN) == 0;
}

bool EqualsMaterialName(const char* pLhs, const char* pRhs) {
    return std::strncmp(pLhs, pRhs, NW4R_LYT_MATERIAL_NAME_LEN) == 0;
}

bool TestFileHeader(const res::BinaryFileHeader& rHeader) {
    return rHeader.byteOrder == NW4R_BYTEORDER_BIG &&
           rHeader.version == NW4R_LYT_LIBRARY_VERSION;
}

bool TestFileHeader(const res::BinaryFileHeader& rHeader, u32 signature) {
    return GetSignatureInt(rHeader.signature) == signature &&
           TestFileHeader(rHeader);
}

/******************************************************************************
 *
 * TexCoordAry
 *
 ******************************************************************************/
TexCoordAry::TexCoordAry() : mCap(0), mNum(0), mpData(NULL) {}

void TexCoordAry::Free() {
    if (mpData == NULL) {
        return;
    }

    Layout::FreeMemory(mpData);
    mpData = NULL;

    mCap = 0;
    mNum = 0;
}

void TexCoordAry::Reserve(u8 num) {
    if (mCap >= num) {
        return;
    }

    Free();

    TexCoord* const pCoords =
        static_cast<TexCoord*>(Layout::AllocMemory(num * sizeof(TexCoord)));

    mpData = pCoords;

    if (mpData != NULL) {
        mCap = num;
    }
}

void TexCoordAry::SetSize(u8 num) {
    if (mpData != NULL && num <= mCap) {
        // clang-format off
        static TexCoord pCoords = {
            math::VEC2(0.0f, 0.0f),
            math::VEC2(1.0f, 0.0f),
            math::VEC2(0.0f, 1.0f),
            math::VEC2(1.0f, 1.0f)
        };
        // clang-format on

        for (int j = mNum; j < num; j++) {
            for (int i = 0; i < VERTEXCOLOR_MAX; i++) {
                mpData[j][i] = pCoords[i];
            }
        }

        mNum = num;
    }
}

void TexCoordAry::Copy(const void* pSrc, u8 num) {
    mNum = ut::Max<u8>(mNum, num);
    const TexCoord* pSrcCoords = static_cast<const TexCoord*>(pSrc);

    for (int j = 0; j < num; j++) {
        for (int i = 0; i < VERTEXCOLOR_MAX; i++) {
            mpData[j][i] = pSrcCoords[j][i];
        }
    }
}

/******************************************************************************
 *
 * Utility functions
 *
 ******************************************************************************/
bool IsModulateVertexColor(ut::Color* pColors, u8 glbAlpha) {
    if (glbAlpha != 255) {
        return true;
    }

    if (pColors != NULL && (pColors[VERTEXCOLOR_TL] != 0xFFFFFFFF ||
                            pColors[VERTEXCOLOR_TR] != 0xFFFFFFFF ||
                            pColors[VERTEXCOLOR_BL] != 0xFFFFFFFF ||
                            pColors[VERTEXCOLOR_BR] != 0xFFFFFFFF)) {
        return true;
    }

    return false;
}

ut::Color MultipleAlpha(ut::Color color, u8 alpha) {
    ut::Color result = color;

    if (alpha != 255) {
        result.a = color.a * alpha / 255;
    }

    return result;
}

void MultipleAlpha(ut::Color* pDst, const ut::Color* pSrc, u8 alpha) {
    for (int i = 0; i < VERTEXCOLOR_MAX; i++) {
        pDst[i] = MultipleAlpha(pSrc[i], alpha);
    }
}

void SetVertexFormat(bool modulate, u8 numCoord) {
    GXClearVtxDesc();

    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);

    if (modulate) {
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    }

    for (int i = 0; i < numCoord; i++) {
        GXSetVtxDesc(static_cast<GXAttr>(GX_VA_TEX0 + i), GX_DIRECT);
    }

    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);

    if (modulate) {
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    }

    for (int i = 0; i < numCoord; i++) {
        GXSetVtxAttrFmt(GX_VTXFMT0, static_cast<GXAttr>(GX_VA_TEX0 + i),
                        GX_TEX_ST, GX_F32, 0);
    }
}

void DrawQuad(const math::VEC2& rBase, const Size& rSize, u8 num,
              const TexCoord* pCoords, const ut::Color* pColors) {

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    {
        GXPosition2f32(rBase.x, rBase.y);
        if (pColors != NULL) {
            GXColor1u32(pColors[VERTEXCOLOR_TL]);
        }
        for (int i = 0; i < num; i++) {
            GXTexCoord2f32(pCoords[i][VERTEXCOLOR_TL].x,
                           pCoords[i][VERTEXCOLOR_TL].y);
        }

        GXPosition2f32(rBase.x + rSize.width, rBase.y);
        if (pColors != NULL) {
            GXColor1u32(pColors[VERTEXCOLOR_TR]);
        }
        for (int i = 0; i < num; i++) {
            GXTexCoord2f32(pCoords[i][VERTEXCOLOR_TR].x,
                           pCoords[i][VERTEXCOLOR_TR].y);
        }

        GXPosition2f32(rBase.x + rSize.width, rBase.y + rSize.height);
        if (pColors != NULL) {
            GXColor1u32(pColors[VERTEXCOLOR_BR]);
        }
        for (int i = 0; i < num; i++) {
            GXTexCoord2f32(pCoords[i][VERTEXCOLOR_BR].x,
                           pCoords[i][VERTEXCOLOR_BR].y);
        }

        GXPosition2f32(rBase.x, rBase.y + rSize.height);
        if (pColors != NULL) {
            GXColor1u32(pColors[VERTEXCOLOR_BL]);
        }
        for (int i = 0; i < num; i++) {
            GXTexCoord2f32(pCoords[i][VERTEXCOLOR_BL].x,
                           pCoords[i][VERTEXCOLOR_BL].y);
        }
    }
    GXEnd();
}

void DrawQuad(const math::VEC2& rBase, const Size& rSize, u8 num,
              const TexCoord* pCoords, const ut::Color* pColors, u8 alpha) {

    ut::Color colorWork[VERTEXCOLOR_MAX];

    if (pColors != NULL) {
        MultipleAlpha(colorWork, pColors, alpha);
    }

    DrawQuad(rBase, rSize, num, pCoords, pColors ? colorWork : NULL);
}

} // namespace detail
} // namespace lyt
} // namespace nw4r
