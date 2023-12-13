#include "lyt_common.h"
#include "lyt_layout.h"
#include "lyt_pane.h"
#include "ut_algorithm.h"
#include "ut_color.h"
#include "math_types.h"
#include <string.h>
#include <revolution/GX.h>

namespace nw4r
{
    using namespace math;
    using namespace ut;

    namespace lyt
    {
        namespace detail
        {
            bool EqualsResName(const char *s1, const char *s2)
            {
                return (strncmp(s1, s2, NW4R_RES_NAME_SIZE) == 0);
            }
            
            bool EqualsMaterialName(const char *s1, const char *s2)
            {
                return (strncmp(s1, s2, NW4R_MAT_NAME_SIZE) == 0);
            }

            bool TestFileHeader(const res::BinaryFileHeader& header)
            {
                return ((header.byteOrder == NW4R_BYTEORDER_BIG) && (header.version == 8));
            }

            bool TestFileHeader(const res::BinaryFileHeader& header, u32 magic)
            {
                return ((magic == header.magic) && TestFileHeader(header));
            }

            TexCoordAry::TexCoordAry() : mCap(0), mSize(0), mTexCoords(NULL) {}

            void TexCoordAry::Free()
            {
                if (mTexCoords != NULL)
                {
                    Layout::DeleteArray<VEC2>(*mTexCoords, mCap * TEXCOORD_VTX_COUNT);

                    mTexCoords = NULL;
                    mCap = 0;
                    mSize = 0;
                }
            }

            void TexCoordAry::Reserve(u8 num)
            {
                if (mCap < num)
                {
                    Free();

                    mTexCoords = (TexCoordData *)Layout::NewArray<VEC2>(num * TEXCOORD_VTX_COUNT);
                    if (mTexCoords != NULL) mCap = num;
                }
            }

            void TexCoordAry::SetSize(u8 size)
            {
                if (mTexCoords != NULL && size <= mCap)
                {
                    static TexCoordData texCoords =
                    {
                        VEC2(0.0f, 0.0f),
                        VEC2(1.0f, 0.0f),
                        VEC2(0.0f, 1.0f),
                        VEC2(1.0f, 1.0f)
                    };

                    for (int i = mSize; i < size; i++)
                    {
                        for (int j = 0; j < TEXCOORD_VTX_COUNT; j++)
                        {
                            mTexCoords[i][j] = texCoords[j];
                        }
                    }

                    mSize = size;
                }
            }

            void TexCoordAry::Copy(const void *src, u8 n)
            {
                mSize = Max<u8>(mSize, n);

                const TexCoordData *tsrc = (const TexCoordData *)src;
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < TEXCOORD_VTX_COUNT; j++)
                    {
                        mTexCoords[i][j] = tsrc[i][j];
                    }
                }
            }

            bool IsModulateVertexColor(Color *vertexClrs, u8 c)
            {
                if (c != 255) return true;

                if ((vertexClrs != NULL) &&
                ((vertexClrs[0] != 0xFFFFFFFF) || (vertexClrs[1] != 0xFFFFFFFF) ||
                (vertexClrs[2] != 0xFFFFFFFF) || (vertexClrs[3] != 0xFFFFFFFF)))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }

            void MultipleAlpha(Color *dest, const Color *src, u8 alpha)
            {
                for (int i = 0; i < TEXCOORD_VTX_COUNT; i++)
                {
                    dest[i] = MultipleAlpha(src[i], alpha);
                }
            }

            Color MultipleAlpha(Color col, u8 alpha)
            {
                Color newCol = col;
                if (alpha != 255)
                {
                    newCol.a = (col.a * alpha) / 255;
                }

                return newCol;
            }

            void SetVertexFormat(bool bColor, u8 n)
            {
                GXClearVtxDesc();

                GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
                if (bColor) GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);

                for (int i = 0; i < n; i++)
                {
                    GXSetVtxDesc((GXAttr)(GX_VA_TEX0 + i), GX_DIRECT);
                }

                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
                if (bColor) GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);

                for (int i = 0; i < n; i++)
                {
                    GXSetVtxAttrFmt(GX_VTXFMT0, (GXAttr)(GX_VA_TEX0 + i), GX_TEX_ST, GX_F32, 0);
                }
            }

            void DrawQuad(const VEC2 &pos, const Size &size, u8 c, const TexCoordData *tc, const Color *vertexClrs)
            {
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);

                GXPosition2f32(pos.x, pos.y);
                if (vertexClrs != NULL) 
                {
                    GXColor1u32(vertexClrs[0]);
                }
                for (int i = 0; i < c; i++)
                {
                    GXTexCoord2f32(tc[i][0].x, tc[i][0].y);
                }

                GXPosition2f32(pos.x + size.x, pos.y);
                if (vertexClrs != NULL) 
                {
                    GXColor1u32(vertexClrs[1]);
                }
                for (int i = 0; i < c; i++)
                {
                    GXTexCoord2f32(tc[i][1].x, tc[i][1].y);
                }

                GXPosition2f32(pos.x + size.x, pos.y + size.y);
                if (vertexClrs != NULL) 
                {
                    GXColor1u32(vertexClrs[3]);
                }
                for (int i = 0; i < c; i++)
                {
                    GXTexCoord2f32(tc[i][3].x, tc[i][3].y);
                }

                GXPosition2f32(pos.x, pos.y + size.y);
                if (vertexClrs != NULL) 
                {
                    GXColor1u32(vertexClrs[2]);
                }
                for (int i = 0; i < c; i++)
                {
                    GXTexCoord2f32(tc[i][2].x, tc[i][2].y);
                }

                GXEnd();
            }

            void DrawQuad(const VEC2 &pos, const Size &size, u8 c, const TexCoordData *tc, const Color *vertexClrs, u8 alpha)
            {
                Color tempClrs[TEXCOORD_VTX_COUNT];
                if (vertexClrs)
                {
                    MultipleAlpha(tempClrs, vertexClrs, alpha);
                }

                const Color *forUse = vertexClrs ? tempClrs : NULL;
                DrawQuad(pos, size, c, tc, forUse);
            }
        }
    }
}