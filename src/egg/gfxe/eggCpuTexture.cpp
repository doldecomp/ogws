#include <egg/core.h>
#include <egg/gfx.h>
#include <egg/gfxe.h>

#include <revolution/GX.h>

namespace EGG {

DECOMP_FORCEACTIVE(eggCpuTexture_cpp,
                  "eggCpuTexture.cpp",
                  "pColor");

DECOMP_FORCELITERAL(eggCpuTexture_cpp,
                    127.0f, 128.0f, 0.0f);

namespace {

void blendColor(GXColor* pColor, const GXColor& c1, const GXColor& c2,
                f32 scale) {

#line 53
    EGG_ASSERT(pColor);

    if (scale <= 0.0f) {
        *pColor = c1;
    } else if (scale >= 1.0f) {
        *pColor = c2;
    } else {
        pColor->r = c1.r + scale * (c2.r - c1.r);
        pColor->g = c1.g + scale * (c2.g - c1.g);
        pColor->b = c1.b + scale * (c2.b - c1.b);
        pColor->a = c1.a + scale * (c2.a - c1.a);
    }
}

void makeGradationTable(CpuTexture::EGradationKind kind, GXColor* pTable,
                        u16 tableSize, u16 tableStart, u16 tableGoal,
                        const GXColor& c1, const GXColor& c2) {

#line 93
    EGG_ASSERT(tableStart <= tableGoal);
    EGG_ASSERT(tableStart <= tableSize && tableGoal <= tableSize);
    EGG_ASSERT(tableSize <= 1024);

    for (int i = 0; i < tableStart + 1; i++) {
        pTable[i] = c1;
    }

    for (int i = tableGoal - 1; i < tableSize; i++) {
        pTable[i] = c2;
    }

    for (int i = tableStart + 1; i < tableGoal - 1; i++) {
        f32 scale = static_cast<f32>(i - tableStart) /
                    static_cast<f32>(tableGoal - tableStart);

        switch (kind) {
        case CpuTexture::GRADATION_LINEAR: {
            break;
        }

        case CpuTexture::GRADATION_QUADRATIC: {
            scale *= scale;
            break;
        }

        case CpuTexture::GRADATION_CUBIC: {
            scale *= scale;
            scale *= scale;
            break;
        }

        case CpuTexture::GRADATION_QUARTIC: {
            scale *= scale;
            scale *= scale;
            scale *= scale;
            break;
        }

        case CpuTexture::GRADATION_QUINTIC: {
            scale *= scale;
            scale *= scale;
            scale *= scale;
            scale *= scale;
            break;
        }

        case CpuTexture::GRADATION_QUADRATIC_EASEOUT: {
            f32 minusOne = scale - 1.0f;
            scale = -minusOne * minusOne + 1.0f;
            break;
        }

        case CpuTexture::GRADATION_QUARTIC_EASEOUT: {
            f32 minusOne = scale - 1.0f;
            scale = -minusOne * minusOne * minusOne * minusOne + 1.0f;
            break;
        }
        }

        blendColor(&pTable[i], c1, c2, scale);
    }
}

} // namespace

CpuTexture::CpuTexture()
    : mWidth(0),
      mHeight(0),
      mFormat(GX_TF_RGBA8),
      mWrapS(GX_CLAMP),
      mWrapT(GX_CLAMP),
      mMinFilter(GX_LINEAR),
      mMagFilter(GX_LINEAR),
      mpBuffer(NULL) {}

CpuTexture::CpuTexture(u16 width, u16 height, GXTexFmt format)
    : mWidth(width),
      mHeight(height),
      mFormat(format),
      mWrapS(GX_CLAMP),
      mWrapT(GX_CLAMP),
      mMinFilter(GX_LINEAR),
      mMagFilter(GX_LINEAR),
      mpBuffer(NULL) {}

void CpuTexture::configure() {
    mFlags = FLAG_CONFIGURED;
}

void CpuTexture::getTexObj(GXTexObj* pObj) const {
#line 230
    EGG_ASSERT_MSG(checkIsConfigure(), "Please call configure() after construct!");
    EGG_ASSERT(pObj);
    EGG_ASSERT(mpBuffer);

    GXInitTexObj(pObj, getBuffer(), getWidth(), getHeight(), getFormat(),
                 getWrapS(), getWrapT(), GX_FALSE);

    GXInitTexObjLOD(pObj, getMinFilter(), getMagFilter(), 0.0f, 0.0f, 0.0f,
                    GX_FALSE, GX_FALSE, GX_ANISO_1);
}

void CpuTexture::load(GXTexMapID map) {
#line 247
    EGG_ASSERT(mpBuffer);

    GXTexObj obj;
    getTexObj(&obj);

    GXLoadTexObj(&obj, map);
}

void CpuTexture::invalidate() const {
#line 259
    EGG_ASSERT(mpBuffer);

    DCInvalidateRange(mpBuffer, getTexBufferSize());
}

void CpuTexture::flush() const {
#line 268
    EGG_ASSERT(mpBuffer);

    DCFlushRange(mpBuffer, getTexBufferSize());
}

u32 CpuTexture::getTexBufferSize() const {
    return GXGetTexBufferSize(getWidth(), getHeight(), getFormat(), GX_FALSE,
                              1);
}

void CpuTexture::initResTIMG() const {
#line 294
    EGG_ASSERT_MSG(checkIsConfigure(), "Please call configure() after construct!");
    EGG_ASSERT(checkHasHeader());

    ResTIMG* pHeader = getHeader();

    pHeader->format = getFormat();
    pHeader->transparency = JUT_TRANSPARENCY_DISABLE;
    pHeader->width = getWidth();
    pHeader->height = getHeight();
    pHeader->wrapS = getWrapS();
    pHeader->wrapT = getWrapT();
    pHeader->tlutName = GX_TLUT0;
    pHeader->tlutFormat = GX_TL_IA8;
    pHeader->paletteEntryNum = 0;
    pHeader->paletteOffset = 0;
    pHeader->mipMap = GX_FALSE;
    pHeader->edgeLODEnable = GX_FALSE;
    pHeader->biasClampEnable = GX_FALSE;
    pHeader->anisotropy = GX_ANISO_1;
    pHeader->minFilter = getMinFilter();
    pHeader->magFilter = getMagFilter();
    pHeader->minLOD = 0;
    pHeader->maxLOD = 0;
    pHeader->mipMapLevel = 1;
    pHeader->LODBias = 0;
    pHeader->imageOffset = sizeof(ResTIMG);
}

ResTIMG* CpuTexture::getResTIMG() const {
    initResTIMG();
    return getHeader();
}

void CpuTexture::fillNormalMapSphere() {
#line 365
    EGG_ASSERT(getFormat() == GX_TF_RGBA8);

    int width = getWidth();
    int height = getHeight();

    f32 scale = 1.0f;
    f32 radius = scale * width / 2.0f;

    for (u16 y = 0; y < height; y++) {
        for (u16 x = 0; x < width; x++) {
            Vector3f vec;

            // Coordinates relative to the center
            f32 cx = x - (width / 2);
            f32 cy = (height / 2) - y;

            vec.x = cx;
            vec.y = cy;

            // Distance from the center (clamped to edges)
            f32 squaredLength = cx * cx + cy * cy;
            if (squaredLength > radius * radius) {
                squaredLength = radius * radius;
            }

            // Find Z from the Hemisphere equation:
            // x^2 + y^2 + z^2 = r^2
            // z^2 = r^2 - (x^2 + y^2)
            // z = Sqrt(r^2 - (x^2 + y^2))
            vec.z = nw4r::math::FSqrt(radius * radius - squaredLength);

            GXColor color;
            nw4r::math::VEC3Normalize(&vec, &vec);

            color.a = static_cast<int>(vec.x * 128.0f + 127.0f);
            color.b = static_cast<int>(vec.y * 128.0f + 127.0f);
            color.g = static_cast<int>(vec.z * 128.0f + 127.0f);
            color.r = color.a;

            setColor(x, y, color);
        }
    }

    flush();
}

void CpuTexture::fillGradationTable(EGradationKind kind, int dir,
                                    u16 tableStart, u16 tableGoal,
                                    const GXColor& c1, const GXColor& c2,
                                    bool wrap, bool setAll) {

#line 416
    EGG_ASSERT(getBuffer());
    EGG_ASSERT(getFormat() == GX_TF_RGBA8 || getFormat() == GX_TF_I8);

    bool isSLine = dir == 's' || dir == 'S';
#line 420
    EGG_ASSERT(isSLine || dir == 't' || dir == 'T');

    u16 tableSize = isSLine ? getWidth() : getHeight();
#line 422
    EGG_ASSERT(tableSize % 2 == 0);

    u16 tableHeight = isSLine ? getHeight() : getWidth();
    u16 tableMid = tableSize / 2;

    GXColor table[1024];
    makeGradationTable(kind, table, tableSize, tableStart, tableGoal, c1, c2);

    if (wrap) {
        GXColor colors[256];

        for (int i = 0; i < tableSize; i++) {
            colors[i] = table[i < tableMid ? i + tableMid : i - tableMid];
        }

        for (int i = 0; i < tableSize; i++) {
            table[i] = colors[i];
        }
    }

    u16 setStart = setAll ? 0 : tableStart;
    u16 setGoal = setAll ? tableSize : tableGoal;

    for (u16 x = setStart; x < setGoal; x++) {
        for (u16 y = 0; y < tableHeight; y++) {
            if (isSLine) {
                setColor(x, y, table[x]);
            } else {
                setColor(y, x, table[x]);
            }
        }
    }

    flush();
}

void CpuTexture::alloc() {
#line 469
    EGG_ASSERT(getTexBufferSize() > 0);

    u8* pBuffer = new (32) u8[getTexBufferSize()];
#line 471
    EGG_ASSERT(pBuffer);

    setBuffer(pBuffer);
}

void CpuTexture::allocWithHeaderDebug() {
#line 480
    EGG_ASSERT(getTexBufferSize() > 0);

    u8* pBuffer = new (32) u8[getTexBufferSize() + sizeof(ResTIMG)];
#line 482
    EGG_ASSERT(pBuffer);

    setBuffer(pBuffer + sizeof(ResTIMG));
    setFlag(FLAG_HAS_HEADER);
    initResTIMG();
}

void CpuTexture::setColor(u16 x, u16 y, GXColor color) {
#line 497
    EGG_ASSERT(x < getWidth());
    EGG_ASSERT(y < getHeight());
    EGG_ASSERT(getBuffer());

    switch (getFormat()) {
    case GX_TF_RGBA8: {
        int offset = ((x >> 2) + (y >> 2) * (getWidth() / 4)) * 0x40 + // block
                     (y & 3) * 8 + (x & 3) * 2;                        // pixel

        u8* pData = static_cast<u8*>(getBuffer()) + offset;

        pData[0] = color.a;
        pData[1] = color.r;
        pData[32] = color.g;
        pData[33] = color.b;
        break;
    }

    case GX_TF_I8: {
        int offset = (x & 0x7) + (y & 0x3) * 8;                    // pixel
        offset += ((x >> 3) + ((y >> 2) * (getWidth() / 8))) * 32; // block

        u8* pData = static_cast<u8*>(getBuffer()) + offset;

        pData[0] = color.r;
        break;
    }

    default: {
        break;
    }
    }
}

} // namespace EGG
