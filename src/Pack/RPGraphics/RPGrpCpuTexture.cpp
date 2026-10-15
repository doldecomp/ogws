#include <RPGraphics.h>

RPGrpCpuTexture::RPGrpCpuTexture()
    : mFlags(NULL),
      mWrapT(GX_CLAMP),
      mWrapS(GX_CLAMP),
      mMagFilter(GX_LINEAR),
      mMinFilter(GX_LINEAR) {}

void blendColor(GXColor* pColor, const GXColor& c1, const GXColor& c2,
                f32 scale) {

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

void makeGradationTable(RPGrpCpuTexture::EGradationKind kind, GXColor* pTable,
                        u16 tableSize, u16 tableStart, u16 tableGoal,
                        const GXColor& c1, const GXColor& c2) {

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
        case RPGrpCpuTexture::GRADATION_LINEAR: {
            break;
        }

        case RPGrpCpuTexture::GRADATION_QUADRATIC: {
            scale *= scale;
            break;
        }

        case RPGrpCpuTexture::GRADATION_CUBIC: {
            scale *= scale;
            scale *= scale;
            break;
        }

        case RPGrpCpuTexture::GRADATION_QUARTIC: {
            scale *= scale;
            scale *= scale;
            scale *= scale;
            break;
        }

        case RPGrpCpuTexture::GRADATION_QUINTIC: {
            scale *= scale;
            scale *= scale;
            scale *= scale;
            scale *= scale;
            break;
        }

        case RPGrpCpuTexture::GRADATION_QUADRATIC_EASEOUT: {
            f32 minusOne = scale - 1.0f;
            scale = -minusOne * minusOne + 1.0f;
            break;
        }

        case RPGrpCpuTexture::GRADATION_QUARTIC_EASEOUT: {
            f32 minusOne = scale - 1.0f;
            scale = -minusOne * minusOne * minusOne * minusOne + 1.0f;
            break;
        }
        }

        blendColor(&pTable[i], c1, c2, scale);
    }
}

void RPGrpCpuTexture::configure() {
    mFlags = cFlag_Configured;
}

void RPGrpCpuTexture::getTexObj(GXTexObj* pObj) const {
    GXInitTexObj(pObj, getBuffer(), getWidth(), getHeight(), getFormat(),
                 getWrapS(), getWrapT(), GX_FALSE);

    GXInitTexObjLOD(pObj, getMinFilter(), getMagFilter(), 0.0f, 0.0f, 0.0f,
                    GX_FALSE, GX_FALSE, GX_ANISO_1);
}

void RPGrpCpuTexture::load(GXTexMapID map) {
    GXTexObj obj;
    getTexObj(&obj);

    GXLoadTexObj(&obj, map);
}

void RPGrpCpuTexture::invalidate() const {
    DCInvalidateRange(mpBuffer, getTexBufferSize());
}

void RPGrpCpuTexture::flush() const {
    DCFlushRange(mpBuffer, getTexBufferSize());
}

u32 RPGrpCpuTexture::getTexBufferSize() const {
    return GXGetTexBufferSize(getWidth(), getHeight(), getFormat(), GX_FALSE,
                              1);
}

void RPGrpCpuTexture::initResTIMG() const {
    RPGrpResTIMG* pHeader = getHeader();

    pHeader->format = getFormat();
    pHeader->transparency = RPGrpResTIMG::JUT_TRANSPARENCY_DISABLE;
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
    pHeader->imageOffset = sizeof(RPGrpResTIMG);
}

void RPGrpCpuTexture::fillGradationTable(EGradationKind kind, int dir,
                                         u16 tableStart, u16 tableGoal,
                                         const GXColor& c1, const GXColor& c2,
                                         bool wrap, bool setAll) {

    bool isSLine = dir == 's' || dir == 'S';

    u16 tableSize = isSLine ? getWidth() : getHeight();

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
            setColor(y, x, table[x]);
        }
    }
    flush();
}

void RPGrpCpuTexture::alloc() {
    u8* pBuffer = new (32) u8[getTexBufferSize()];
    setBuffer(pBuffer);
}

void RPGrpCpuTexture::allocWithHeaderDebug() {

    u8* pBuffer = new (32) u8[getTexBufferSize() + sizeof(RPGrpResTIMG)];

    setBuffer(pBuffer + sizeof(RPGrpResTIMG));
    setFlag(cFlag_HasHeader);
    initResTIMG();
}

void RPGrpCpuTexture::setColor(u16 x, u16 y, GXColor color) {
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
